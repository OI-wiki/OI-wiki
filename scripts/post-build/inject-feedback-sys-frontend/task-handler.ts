import fs from "fs";
import path from "path";
import util from "util";
import child_process from "child_process";
import fetch from "node-fetch";
import { createHash } from "node:crypto";
import { HTMLElement } from "node-html-parser";

import { TaskHandler, log } from "../html-postprocess.js";

const execFileAsync = util.promisify(child_process.execFile);

type GlobalData = {
  commitHash: string;
  jsFileMd5: string;
  cssFileMd5: string;
};

const OFFSET_INJECTION_REVIEW_JS_SOURCE_FILE =
  "../node_modules/oiwiki-feedback-sys-frontend/dist/oiwiki-feedback-sys-frontend.umd.cjs";
const OFFSET_INJECTION_REVIEW_JS_TARGET_FILE = "assets/javascripts/oiwiki-feedback-sys-frontend.js";
const OFFSET_INJECTION_REVIEW_CSS_SOURCE_FILE = "../node_modules/oiwiki-feedback-sys-frontend/dist/style.css";
const OFFSET_INJECTION_REVIEW_CSS_TARGET_FILE = "assets/stylesheets/oiwiki-feedback-sys-frontend.css";

const OFFSET_INJECTION_REVIEW_CONTENT_SCRIPT_TARGET_FILE = "_static/js/oiwiki-feedback-sys-frontend.js";

const API_ENDPOINT = "https://cloudflare-workers.hikarilan.workers.dev/";

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

export const taskHandler = new (class implements TaskHandler<GlobalData> {
  async globalInitialize(siteDir: string): Promise<GlobalData> {
    log(`Fetching latest commit hash...`);
    const commitHash = await getLatestCommitHash();
    log(`Got latest commit hash: ${commitHash}`);

    log(`Copying oiwiki-feedback-sys-frontend script to ${OFFSET_INJECTION_REVIEW_JS_TARGET_FILE}...`);
    const jsDestFile = path.join(siteDir, OFFSET_INJECTION_REVIEW_JS_TARGET_FILE);
    await fs.promises.mkdir(path.dirname(jsDestFile), { recursive: true });
    await fs.promises.copyFile(path.resolve(siteDir, OFFSET_INJECTION_REVIEW_JS_SOURCE_FILE), jsDestFile);
    log(`Copying oiwiki-feedback-sys-frontend css to ${OFFSET_INJECTION_REVIEW_CSS_TARGET_FILE}...`);
    const cssDestFile = path.join(siteDir, OFFSET_INJECTION_REVIEW_CSS_TARGET_FILE);
    await fs.promises.mkdir(path.dirname(cssDestFile), { recursive: true });
    await fs.promises.copyFile(path.resolve(siteDir, OFFSET_INJECTION_REVIEW_CSS_SOURCE_FILE), cssDestFile);

    log(
      `Injecting api endpoint to oiwiki-feedback-sys-frontend content script ${OFFSET_INJECTION_REVIEW_CONTENT_SCRIPT_TARGET_FILE}...`
    );
    const contentScriptFile = path.join(siteDir, OFFSET_INJECTION_REVIEW_CONTENT_SCRIPT_TARGET_FILE);
    await fs.promises.writeFile(
      contentScriptFile,
      (await fs.promises.readFile(contentScriptFile, "utf-8")).replace("{apiEndpoint}", API_ENDPOINT),
      "utf-8"
    );

    await updateCommitHash();

    const jsContent = fs.promises.readFile(jsDestFile, "utf-8");
    const cssContent = fs.promises.readFile(cssDestFile, "utf-8");

    return {
      commitHash,
      jsFileMd5: createHash("md5")
        .update(await jsContent)
        .digest("hex"),
      cssFileMd5: createHash("md5")
        .update(await cssContent)
        .digest("hex")
    };
  }

  globalData: GlobalData;
  siteDir: string;

  async initialize(globalInitializationResult: GlobalData, siteDir: string) {
    this.globalData = globalInitializationResult;
    this.siteDir = siteDir;
  }

  async process(document: HTMLElement, filePath: string) {
    document
      .querySelector("body")
      .insertAdjacentHTML(
        "beforeend",
        `<script>sessionStorage.setItem("commitHash", "${this.globalData.commitHash}")</script>`
      );

    const htmlFilePathToRoot = path.relative(this.siteDir, filePath);
    const cssFilePathToHtml = path.relative(path.dirname(htmlFilePathToRoot), OFFSET_INJECTION_REVIEW_CSS_TARGET_FILE);
    const jsFilePathToHtml = path.relative(path.dirname(htmlFilePathToRoot), OFFSET_INJECTION_REVIEW_JS_TARGET_FILE);

    document
      .querySelector("head")
      .insertAdjacentHTML(
        "beforeend",
        `<link rel="stylesheet" href="${cssFilePathToHtml}?v=${this.globalData.cssFileMd5}">`
      );
    document
      .querySelector("head")
      .insertAdjacentHTML("beforeend", `<script src="${jsFilePathToHtml}?v=${this.globalData.jsFileMd5}"></script>`);
  }
})();
