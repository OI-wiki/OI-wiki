const Promise = require('bluebird');
const { join, dirname } = require('path');
const { listDir, readFile, writeFile } = require('hexo-fs');
const { green, red, yellow, bgRed } = require('chalk');

const distDir = join(dirname(__dirname) + '/site');
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

async function main() {
  const doTask = fn => fn();

  const items = await listDir(distDir).map(item => {
    return () => {
      if (item.endsWith('.html')) {
        let START_TIME, END_TIME;
        const filename = join(distDir, item);

        readFile(filename).then(content => {
          START_TIME = +new Date();

          const preProcesed = content
            .replace(/<span class="MathJax_Preview">.+?<\/span><script type="math\/tex">/gi, '<script type="math/tex">')
            .replace(/<div class="MathJax_Preview">[\s\S]*?<\/div>/gi, '');

          return mathJaxRenderer(preProcesed);
        }).then(result => {
          END_TIME = +new Date();
          console.log(`${green('INFO')}  ${yellow(item)} rendered finished (${(END_TIME - START_TIME) / 1000}s).`);
          return writeFile(filename, result);
        }, e => {
          throw new Error(e);
        }).catch(e => {
          console.error(`${bgRed('ERROR')} ${yellow(item)} ${red(`rendered failed`)}, detailed error see below:`);
          console.error(e);
        });
      }

      return;
    }
  });

  Promise.all(Promise.each(items, doTask));
}

main();
