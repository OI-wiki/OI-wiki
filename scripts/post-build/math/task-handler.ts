import chalk from "chalk";
import mathjaxNodePage from "mathjax-node-page";
import { HTMLElement } from "node-html-parser";
import { promisify } from "util";

import { TaskHandler } from "../html-postprocess.js";

const { red, yellow, bgRed } = chalk;
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

async function renderMathJax(content: string, filename: string) {
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

  if (result) return result;

  return content;
}

export const taskHandler = new (class implements TaskHandler<void> {
  async process(document: HTMLElement, filePath: string) {
    document.innerHTML = await renderMathJax(document.innerHTML, filePath);
  }
})();
