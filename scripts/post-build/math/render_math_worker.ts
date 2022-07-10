import { isMainThread, parentPort } from "worker_threads";

if (isMainThread) {
  throw new Error("Its not a worker");
}

import Promise from "bluebird";
import hexoFs from "hexo-fs";
import chalk from "chalk";

import mathjaxNodePage from "mathjax-node-page";
import { promisify } from "util";

const { readFile, writeFile } = hexoFs;
const { green, red, yellow, bgRed } = chalk;
const { mjpage } = mathjaxNodePage;

mjpage[promisify.custom] = input => {
  return new Promise((resolve, reject) => {
    try {
      mjpage(
        input,
        {
          format: ["TeX"]
        },
        { svg: true, ex: 8, cjkCharWidth: 18, linebreaks: true },
        resolve
      );
    } catch (e) {
      reject(e);
    }
  });
};

const mathJaxRenderer = promisify(mjpage);

async function renderMathJax(filename) {
  const START_TIME = +new Date();

  const content = await readFile(filename);

  const preProcessed = content
    .replace(/<span class="MathJax_Preview">.+?<\/span><script type="math\/tex">/gi, '<script type="math/tex">')
    .replace(/<div class="MathJax_Preview">[\s\S]*?<\/div>/gi, "");

  let result = null;

  try {
    result = await mathJaxRenderer(preProcessed);
  } catch (e) {
    console.error(`${bgRed("ERROR")} ${yellow(filename)} ${red(`rendered failed`)}, detailed error see below:`);
    console.error(e);
  }

  if (result) {
    const END_TIME = +new Date();
    console.log(`${green("INFO")}  ${yellow(filename)} rendered finished (${(END_TIME - START_TIME) / 1000}s).`);
    return writeFile(filename, result);
  }

  return;
}

parentPort.on("message", async filename => {
  await renderMathJax(filename);
  parentPort.postMessage("Done");
});
