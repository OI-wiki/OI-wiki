import util from "util";
import child_process from "child_process";
import chalk from "chalk";
import { HTMLElement } from "node-html-parser";
import fetch from "node-fetch";

import { AuthorsCache, AuthorUserMap, fetchAuthors } from "./authors-cache.js";
import { TaskHandler, log } from "../html-postprocess.js";

const execFileAsync = util.promisify(child_process.execFile);

async function readCommitsLog(sourceFilePath: string): Promise<{ commitDate: Date; authorEmails: string[] }[]> {
  const { stdout: log } = await execFileAsync(
    "bash",
    [
      "-c",
      /**
       * Format:
       *
       * >Date
       * <AuthorEmail
       * <CoAuthorEmail
       * <...
       * >Date
       * <AuthorEmail
       * <...
       */
      `git log --follow '--pretty=format:D %cD%n<%aE%n%w(0,2,2)%b' $FILENAME | sed -nE 's/^(D (.+)|(<.+)|  Co-Authored-By: .+?(<.+)>)/\\2\\3\\4/pi'`
    ],
    {
      env: {
        ...process.env,
        FILENAME: `docs${sourceFilePath}`
      }
    }
  );

  const commits = log.trim().slice(1).split("\n>");
  return commits.map(commit => {
    /**
     * Format:
     *
     * Date
     * >AuthorEmail
     * >CoAuthorEmail
     * >...
     */
    const [dateLine, ...emailLines] = commit.split("\n");
    return {
      commitDate: new Date(dateLine),
      authorEmails: Array.from(new Set(emailLines.map(emailLine => emailLine.slice(1).toLowerCase())))
    };
  });
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

      const commitsLog = await readCommitsLog(sourceFilePath);

      // "本页面最近更新"
      const latestDate = new Date(
        commitsLog.map(l => +new Date(l.commitDate)).reduce((latest, current) => Math.max(latest, current))
      );
      $(".facts_modified").textContent =
        latestDate.toLocaleDateString("zh-CN", { timeZone: "Asia/Shanghai", hour12: false }) +
        " " +
        latestDate.toLocaleTimeString("zh-CN", { timeZone: "Asia/Shanghai", hour12: false });

      // "本页面贡献者"
      const authors = Object.entries(
        // Commit count by author
        [
          // From markdown front-matter
          ...$(".page_contributors")
            .textContent.trim()
            .split(",")
            .map(username => `${username.trim()}\ngithub`),
          // From git history
          ...commitsLog
            .flatMap(l => l.authorEmails)
            .filter(email => email in this.userMap)
            .map(
              email =>
                this.userMap[email].githubUsername
                  ? `${this.userMap[email].githubUsername}\ngithub` // GitHub username
                  : `${this.userMap[email].name}\ngit\n${email}` // Git name (when email not linked with GitHub)
            )
        ].reduce<Record<string, number>>((count, author) => {
          if (AUTHORS_EXCLUDED.some(excluded => `${excluded.toLowerCase()}\ngithub` === author.toLowerCase()))
            return count;

          count[author] = (count[author] || 0) + 1;
          return count;
        }, {})
      )
        .sort(([author1, count1], [author2, count2]) => {
          // Sort DESC by commit count
          if (count1 !== count2) return count2 - count1;
          else return author1.toLowerCase() < author2.toLowerCase() ? -1 : 1;
        })
        .map(([author]) => author);
      $(".page_contributors").innerHTML = authors
        .map(author => {
          const [name, type, email] = author.split("\n");
          return type === "github"
            ? `<a href="https://github.com/${name}" target="_blank">${name}</a>`
            : `<a href="mailto:${email}" target="_blank">${name}</a>`;
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
