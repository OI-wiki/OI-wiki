import fs from "fs";
import { Octokit } from "octokit";

import { AuthorsCache, AuthorUserMap } from "./authors-cache.js";

const GITHUB_REPO = "OI-wiki/OI-wiki";
const AUTHORS_FILE = "authors.json";

// Increase this value carefully since it should cause API token limit exceeded
const fetchConcurrency = Number(process.argv[2]) || 1;

async function fetchUserMap(since: string): Promise<AuthorsCache> {
  console.log(`Fetching commits newer than: ${since || "(fetch all)"}`);

  const octokit = new Octokit({
    auth: process.env.GITHUB_TOKEN
  });

  const result: AuthorUserMap = {};
  let latestCommitTime = 0;
  for (let i = 1; ; i += fetchConcurrency) {
    const responses = await Promise.all(
      Array(fetchConcurrency)
        .fill(null)
        .map((_, j) => i + j)
        .map(page =>
          octokit.request(`GET /repos/${GITHUB_REPO}/commits`, {
            per_page: 100,
            page,
            ...(since ? { since } : {})
          })
        )
    );
    const data = responses.flatMap(response => response.data);
    if (data.length === 0) break;

    for (const item of data) {
      const commitTime = +new Date(item.commit.committer.date);
      if (latestCommitTime < commitTime) {
        latestCommitTime = commitTime;
      }

      const email = item.commit.author.email.toLowerCase();
      const name = item.commit.author.name;
      if (name.includes("[bot]")) continue;
      if (!(email in result))
        result[email] = {
          name,
          githubUsername: item.author && item.author.login ? item.author.login : undefined
        };
    }
  }

  return {
    latestCommitTime: new Date(latestCommitTime).toISOString(),
    userMap: result
  };
}

// Read cached old data (if exists)
let lastLastestCommitTime = "";
let oldUserMap = {};
try {
  const oldData = JSON.parse(fs.readFileSync(AUTHORS_FILE, "utf-8"));
  lastLastestCommitTime = !Number.isNaN(+new Date(oldData.latestCommitTime)) ? oldData.latestCommitTime : "";
  if (lastLastestCommitTime)
    oldUserMap = Object.prototype.toString.call(oldData.userMap) === "[object Object]" ? oldData.userMap : {};
} catch {}

// Fetch data from newer commits only
const result = await fetchUserMap(lastLastestCommitTime);

// Merge old data
result.userMap = { ...oldUserMap, ...result.userMap };

// Sort by emails
result.userMap = Object.fromEntries(
  Object.keys(result.userMap)
    .sort()
    .map(key => [key, result.userMap[key]])
);

fs.writeFileSync(AUTHORS_FILE, JSON.stringify(result, null, 2));
