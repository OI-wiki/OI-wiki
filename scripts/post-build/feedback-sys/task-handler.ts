import util from "util";
import child_process from "child_process";
import fetch from "node-fetch";

import { TaskHandler, log } from "../html-postprocess.js";

const execFileAsync = util.promisify(child_process.execFile);

const API_ENDPOINT = "{API_ENDPOINT}";

async function getLatestCommitHash(): Promise<string> {
  const { stdout: hash } = await execFileAsync("bash", ["-c", `git log -1 --pretty=format:%H`], {
    env: {
      ...process.env
    }
  });
  return hash.trim();
}

async function updateCommitHash() {
  const secret = process.env.ADMINISTRATOR_SECRET;
  if (!secret) {
    log("ADMINISTRATOR_SECRET is not set, skipping commit hash update...");
    return;
  }
  const hash = await getLatestCommitHash();
  log(`Updating commit hash to ${hash}...`);
  const res = await fetch(API_ENDPOINT + "meta/commithash", {
    method: "PUT",
    headers: {
      Authorization: `Bearer ${secret}`,
      "Content-Type": "application/json"
    },
    body: JSON.stringify({ commit_hash: hash })
  });
  if (!res.ok) {
    throw new Error(`Failed to update commit hash: ${await res.text()}`);
  }
}

export const taskHandler = new (class implements TaskHandler {
  async globalInitialize() {
    log(`Fetching latest commit hash...`);
    const commitHash = await getLatestCommitHash();
    log(`Got latest commit hash: ${commitHash}`);

    await updateCommitHash();
  }
  async process() {}
})();
