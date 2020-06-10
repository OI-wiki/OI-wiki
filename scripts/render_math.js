const Promise = require('bluebird');
const { join, dirname } = require('path');
const { listDir, readFile, writeFile } = require('hexo-fs');
const { green, red, yellow, bgRed } = require('chalk');
const log = require('fancy-log');

const { mjpage } = require('mathjax-node-page');
const { promisify } = require('util');

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

const distDir = join(dirname(__dirname) + '/site');

async function main() {
  const doTask = fn => fn();

  const items = await listDir(distDir).map(item => {
    return async () => {
      const START_TIME = +new Date();
      if (item.endsWith('.html')) {
        const filename = join(distDir, item);
        const content = await readFile(filename);

        const preProcesed = content
          .replace(/<span class="MathJax_Preview">.+?<\/span><script type="math\/tex">/gi, '<script type="math/tex">')
          .replace(/<div class="MathJax_Preview">[\s\S]*?<\/div>/gi, '');

        let result = null;

        try {
          result = await mathJaxRenderer(preProcesed);
        } catch (e) {
          log.error(`${bgRed('ERROR')} ${yellow(item)} ${red(`rendered failed`)}, detailed error see below:`);
          console.error(e);
        }

        if (result) {
          log(`${green('INFO')}  ${yellow(item)} rendered finished (${+new Date() - START_TIME}ms).`);
          return writeFile(filename, result)
        };

        return;
      }

      return;
    }
  });

  Promise.all(Promise.map(items, doTask, { concurrency: 10 }));
}

main();
