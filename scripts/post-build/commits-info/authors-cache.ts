import { Octokit } from "octokit";

export const AUTHORS_FILE = "authors.json";
const GITHUB_REPO = "OI-wiki/OI-wiki";

export type AuthorUserMap = Record<string, { name: string; githubUsername: string }>;

export interface AuthorsCache {
  latestCommitTime: string;
  userMap: AuthorUserMap;
}

export async function fetchAuthors(cachedData: AuthorsCache, fetchConcurrency = 1): Promise<AuthorsCache> {
  cachedData = cachedData || {
    latestCommitTime: undefined,
    userMap: {}
  };

  const since = cachedData.latestCommitTime;

  const octokit = new Octokit({
    auth: process.env.GITHUB_TOKEN
  });

  const result: AuthorUserMap = { ...cachedData.userMap };
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
    userMap: Object.fromEntries(
      Object.keys(result)
        .sort()
        .map(key => [key, result[key]])
    )
  };
}
