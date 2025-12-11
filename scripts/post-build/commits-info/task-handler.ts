import util from "util";
import child_process from "child_process";
import chalk from "chalk";
import { HTMLElement } from "node-html-parser";
import fetch from "node-fetch";
import * as path from "node:path";
import * as fs from "node:fs/promises";
import * as nodegit from "nodegit";

import { AuthorsCache, AuthorUserMap, fetchAuthors } from "./authors-cache.js";
import { TaskHandler, log } from "../html-postprocess.js";

const execFileAsync = util.promisify(child_process.execFile);

type CommitInfo = { commitDate: Date; authors: { name: string; email: string }[] };

// async function readCommitsLogRepoPath(repoRelPath: string): Promise<CommitInfo[]> {
//   const { stdout: log } = await execFileAsync(
//     "bash",
//     [
//       "-c",
//       `git log --follow --date=iso-strict '--pretty=format:D|%cI%nA|%aN|%aE%n%b' "$FILENAME" \
// | awk 'BEGIN{IGNORECASE=1} \
//   /^D\\|/{print; next} \
//   /^A\\|/{print; next} \
//   /^[[:space:]]*Co-Authored-By[[:space:]]*:/ { \
//     if (match($0, /^[[:space:]]*Co-Authored-By[[:space:]]*:[[:space:]]*(.+)[[:space:]]*<([^>]+)>[[:space:]]*$/, m)) { \
//       print "C|" m[1] "|" m[2]; \
//     } \
//   }'`
//     ],
//     { env: { ...process.env, FILENAME: repoRelPath } }
//   );

//   const lines = log
//     .split("\n")
//     .map(s => s.trim())
//     .filter(Boolean);
//   const commits: CommitInfo[] = [];
//   let current: CommitInfo | null = null;

//   for (const line of lines) {
//     if (line.startsWith("D|")) {
//       if (current) commits.push(current);
//       current = { commitDate: new Date(line.slice(2)), authors: [] };
//     } else if (line.startsWith("A|") || line.startsWith("C|")) {
//       if (!current) continue;
//       const parts = line.split("|"); // ["A","name","email"] or ["C","name","email"]
//       const name = (parts[1] || "").trim();
//       const email = (parts[2] || "").trim().toLowerCase();
//       if (name && email) current.authors.push({ name, email });
//     }
//   }
//   if (current) commits.push(current);

//   return commits;
// }

async function readCommitsLogRepoPath(repoRelPath: string): Promise<CommitInfo[]> {
  const repo = await nodegit.Repository.open(".");
  const walker = repo.createRevWalk();
  const commits = await walker.fileHistoryWalk(repoRelPath, 5000);

  const results: CommitInfo[] = [];

  for (const entry of commits) {
    const commit = entry.commit;
    const commitDate = commit.date();
    const mainAuthor = {
      name: commit.author().name(),
      email: commit.author().email().toLowerCase()
    };

    const authors = [mainAuthor];
    const trailers = nodegit.Message.trailers(commit.message());

    for (const tr of trailers) {
      if (tr.key.toLowerCase() !== "co-authored-by") continue;

      const m = tr.value.match(/(.+?)\s*<([^>]+)>/);
      if (!m) continue;

      authors.push({
        name: m[1].trim(),
        email: m[2].trim().toLowerCase()
      });
    }

    results.push({ commitDate, authors });
  }

  return results;
}

async function readCommitsLogFromRef(refPath: string) {
  const clean = refPath.replace(/^\/+/, "");
  const repoRel = path.posix.join("docs", clean);
  return readCommitsLogRepoPath(repoRel);
}

async function findIncludedPaths(refPath: string): Promise<string[]> {
  const clean = refPath.replace(/^\/+/, ""); // "math/fft.md"
  const mdRepoRel = path.posix.join("docs", clean); // "docs/math/fft.md"
  let content = "";
  try {
    content = await fs.readFile(mdRepoRel, "utf-8");
  } catch {
    return [];
  }

  const includes: string[] = [];
  const re = /--8<--\s*"(.*?)"/g;
  let m: RegExpExecArray | null;
  while ((m = re.exec(content))) {
    const raw = m[1].trim();
    let repoRel: string;

    if (raw.startsWith("docs/")) {
      repoRel = raw;
    } else if (raw.startsWith("/")) {
      repoRel = path.posix.join("docs", raw.replace(/^\/+/, ""));
    } else {
      const mdDir = path.posix.dirname(mdRepoRel);
      repoRel = path.posix.normalize(path.posix.join(mdDir, raw));
    }

    if (repoRel.startsWith("docs/")) {
      includes.push(repoRel);
    }
  }

  return Array.from(new Set(includes));
}

const GITHUB_REPO = "OI-wiki/OI-wiki";
const AUTHORS_CACHE_URL = `https://raw.githubusercontent.com/${GITHUB_REPO}/authors-cache/authors.json`;
const AUTHORS_EXCLUDED = ["24OI-Bot", "OI-wiki"];

export const taskHandler = new (class implements TaskHandler<AuthorUserMap> {
  async globalInitialize() {
    log("Ensuring full Git history");
    child_process.execSync("(git rev-parse --is-shallow-repository | grep false >/dev/null) || git fetch --unshallow", {
      stdio: "inherit"
    });

    log(`Fetching authors cache from ${chalk.yellow(AUTHORS_CACHE_URL)}`);
    const authorsCache = (await (await fetch(AUTHORS_CACHE_URL)).json()) as AuthorsCache;

    log(`Fetching authors of commits newer than: ${chalk.yellow(authorsCache.latestCommitTime)}`);
    return (await fetchAuthors(authorsCache)).userMap;
  }

  userMap: AuthorUserMap;

  async initialize(userMap: AuthorUserMap) {
    this.userMap = userMap;
  }

  async process(document: HTMLElement) {
    const $ = document.querySelector.bind(document);
    const $$ = document.querySelectorAll.bind(document);

    $("html").setAttribute("lang", "zh-Hans");

    // The path of .md file relative to /docs, starting with a leading "/"
    const sourceFilePath = ($(".page_edit_url").getAttribute("href") || "").split("?ref=")[1];
    if (sourceFilePath) {
      // Set link to git history
      $(".edit_history").setAttribute("href", `https://github.com/${GITHUB_REPO}/commits/master/docs${sourceFilePath}`);

      const commitsLogMain = await readCommitsLogFromRef(sourceFilePath);

      const includeRepoPaths = await findIncludedPaths(sourceFilePath);
      const includeLogs = await Promise.all(includeRepoPaths.map(p => readCommitsLogRepoPath(p)));

      const allLogs = [commitsLogMain, ...includeLogs].flat();

      // "本页面最近更新"
      const ts = allLogs.map(l => +l.commitDate).filter(Number.isFinite);
      if (ts.length === 0) {
        $(".facts_modified").textContent = "无更新";
      } else {
        const latestDate = new Date(Math.max(...ts));
        $(".facts_modified").textContent =
          latestDate.toLocaleDateString("zh-CN", { timeZone: "Asia/Shanghai", hour12: false }) +
          " " +
          latestDate.toLocaleTimeString("zh-CN", { timeZone: "Asia/Shanghai", hour12: false });
      }

      const frontMatter = $(".page_contributors")
        .textContent.trim()
        .split(",")
        .map(s => s.trim())
        .filter(Boolean)
        .map(u => `${u}\ngithub`);

      const fromGit = allLogs
        .flatMap(c => c.authors)
        .map(({ name, email }) => {
          const info = this.userMap[email];
          if (info?.githubUsername) return `${info.githubUsername}\ngithub`;
          return `${(info?.name || name).trim()}\ntext`;
        });

      const counts = [...frontMatter, ...fromGit].reduce<Record<string, number>>((acc, key) => {
        if (AUTHORS_EXCLUDED.some(ex => `${ex.toLowerCase()}\ngithub` === key.toLowerCase())) return acc;
        acc[key] = (acc[key] || 0) + 1;
        return acc;
      }, {});

      const ordered = Object.entries(counts)
        .sort(([a1, c1], [a2, c2]) => (c1 !== c2 ? c2 - c1 : a1.toLowerCase().localeCompare(a2.toLowerCase())))
        .map(([key]) => key);

      $(".page_contributors").innerHTML = ordered
        .map(token => {
          const [label, typ] = token.split("\n");
          if (typ === "github") {
            return `<a href="https://github.com/${label}" target="_blank" rel="noopener noreferrer">${label}</a>`;
          }
          return `${label}`;
        })
        .join(", ");
    } else {
      // Pages without source
      $(".edit_history").setAttribute("href", `https://github.com/${GITHUB_REPO}/commits/master`);
      $(".facts_modified").textContent = "无更新";
      $(".page_contributors").textContent = "（自动生成）";
      $(".page_edit_url").setAttribute("href", "#");
    }
  }
})();
