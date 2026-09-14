import { Octokit } from "octokit";

export const AUTHORS_FILE = "authors.json";

export type AuthorUserMap = Record<string, { name: string; githubUsername: string }>;

export interface AuthorsCache {
  latestCommitTime: string;
  userMap: AuthorUserMap;
}

type GitActor = { name: string; email: string; user: { login: string } | null };

type CommitHistoryResponse = {
  repository: {
    defaultBranchRef: {
      target: {
        history: {
          nodes: {
            committedDate: string;
            authors: { nodes: GitActor[] };
          }[];
          pageInfo: { hasNextPage: boolean; endCursor: string };
        };
      };
    };
  };
};

// https://docs.github.com/en/graphql/reference/objects#commit
export async function fetchAuthors(cachedData: AuthorsCache): Promise<AuthorsCache> {
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
  let cursor: string | undefined;
  for (;;) {
    const data = await octokit.graphql<CommitHistoryResponse>(
      `query($owner: String!, $name: String!, $cursor: String, $since: GitTimestamp) {
        repository(owner: $owner, name: $name) {
          defaultBranchRef {
            target {
              ... on Commit {
                history(first: 100, after: $cursor, since: $since) {
                  nodes {
                    committedDate
                    authors(first: 100) { nodes { name email user { login } } }
                  }
                  pageInfo { hasNextPage endCursor }
                }
              }
            }
          }
        }
      }`,
      { owner: "OI-wiki", name: "OI-wiki", cursor, since }
    );

    const history = data.repository.defaultBranchRef.target.history;
    for (const node of history.nodes) {
      const commitTime = +new Date(node.committedDate);
      if (latestCommitTime < commitTime) {
        latestCommitTime = commitTime;
      }

      for (const author of node.authors.nodes) {
        if (!author.name || !author.email || author.name.includes("[bot]")) continue;
        const email = author.email.toLowerCase();
        if (!(email in result))
          result[email] = {
            name: author.name,
            githubUsername: author.user ? author.user.login : undefined
          };
      }
    }
    if (!history.pageInfo.hasNextPage) break;
    cursor = history.pageInfo.endCursor;
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
