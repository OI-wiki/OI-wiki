export type AuthorUserMap = Record<string, { name: string; githubUsername: string }>;

export interface AuthorsCache {
  latestCommitTime: string;
  userMap: AuthorUserMap;
}
