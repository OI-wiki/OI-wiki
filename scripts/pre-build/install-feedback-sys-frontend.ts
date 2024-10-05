import util from "util";
import child_process from "child_process";
import fs from "fs";
import path from "path";
import { createHash } from "node:crypto";

const execFileAsync = util.promisify(child_process.execFile);

async function getLatestCommitHash(): Promise<string> {
  const { stdout: hash } = await execFileAsync("bash", ["-c", `git log -1 --pretty=format:%H`], {
    env: {
      ...process.env
    }
  });
  return hash.trim();
}
const JS_SOURCE_FILE = "../node_modules/oiwiki-feedback-sys-frontend/dist/oiwiki-feedback-sys-frontend.umd.cjs";
const JS_TARGET_FILE = "assets/javascripts/oiwiki-feedback-sys-frontend.js";
const CSS_SOURCE_FILE = "../node_modules/oiwiki-feedback-sys-frontend/dist/style.css";
const CSS_TARGET_FILE = "assets/stylesheets/oiwiki-feedback-sys-frontend.css";

const CONTENT_SCRIPT_TARGET_FILE = "_static/js/oiwiki-feedback-sys-frontend.js";

const MKDOCS_CONFIG_FILE = "../mkdocs.yml";

const API_ENDPOINT = "https://feedback-sys.mgt.moe/";

const docsDir = path.resolve("docs");

console.log(`Copying oiwiki-feedback-sys-frontend script to ${JS_TARGET_FILE}...`);
const jsDestFile = path.join(docsDir, JS_TARGET_FILE);
await fs.promises.mkdir(path.dirname(jsDestFile), { recursive: true });
await fs.promises.copyFile(path.resolve(docsDir, JS_SOURCE_FILE), jsDestFile);
console.log(`Copying oiwiki-feedback-sys-frontend css to ${CSS_TARGET_FILE}...`);
const cssDestFile = path.join(docsDir, CSS_TARGET_FILE);
await fs.promises.mkdir(path.dirname(cssDestFile), { recursive: true });
await fs.promises.copyFile(path.resolve(docsDir, CSS_SOURCE_FILE), cssDestFile);

console.log(`Injecting variables to oiwiki-feedback-sys-frontend content script ${CONTENT_SCRIPT_TARGET_FILE}...`);
const contentScriptFile = path.join(docsDir, CONTENT_SCRIPT_TARGET_FILE);
await fs.promises.writeFile(
  contentScriptFile,
  (await fs.promises.readFile(contentScriptFile, "utf-8"))
    .replace("{apiEndpoint}", API_ENDPOINT)
    .replace("{commitHash}", await getLatestCommitHash()),
  "utf-8"
);

const jsContent = fs.promises.readFile(jsDestFile, "utf-8");
const cssContent = fs.promises.readFile(cssDestFile, "utf-8");
const contentScriptContent = fs.promises.readFile(contentScriptFile, "utf-8");

const jsFileMd5 = createHash("md5")
  .update(await jsContent)
  .digest("hex");
const cssFileMd5 = createHash("md5")
  .update(await cssContent)
  .digest("hex");
const contentScriptMd5 = createHash("md5")
  .update(await contentScriptContent)
  .digest("hex");

console.log(`Updating mkdocs.yml...`);
const mkdocsConfigFile = path.join(docsDir, MKDOCS_CONFIG_FILE);
await fs.promises.writeFile(
  mkdocsConfigFile,
  (
    await fs.promises.readFile(mkdocsConfigFile, "utf-8")
  )
    .replace("{OIWikiFeedbackSystemFrontendJS}", path.relative(docsDir, jsDestFile) + "?v=" + jsFileMd5)
    .replace("{OIWikiFeedbackSystemFrontendCSS}", path.relative(docsDir, cssDestFile) + "?v=" + cssFileMd5)
    .replace(
      "{OIWikiFeedbackSystemFrontendContentScript}",
      path.relative(docsDir, contentScriptFile) + "?v=" + contentScriptMd5
    ),
  "utf-8"
);
