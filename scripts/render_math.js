const Promise = require('bluebird');
const { join, dirname } = require('path');
const { listDir, readFile, writeFile } = require('hexo-fs');
const { green, red, yellow, bgRed } = require('chalk');
const log = require('fancy-log');

const { mjpage } = require('mathjax-node-page');

const distDir = join(dirname(__dirname) + '/site');

async function main() {
  const doTask = fn => fn();

  const items = await listDir(distDir).map(item => {
    return () => {
      const START_TIME = +new Date();
      if (item.endsWith('.html')) {
        const filename = join(distDir, item);

        readFile(filename).then(content => {
          const preProcesed = content
            .replace(/<span class="MathJax_Preview">.+?<\/span><script type="math\/tex">/gi, '<script type="math/tex">')
            .replace(/<div class="MathJax_Preview">[\s\S]*?<\/div>/gi, '');

          let result = null;

          mjpage(
            preProcesed,
            {
              format: ["TeX"]
            },
            { svg: true, ex: 8, cjkCharWidth: 18, linebreaks: true, timeout: 20 * 1000 },
            output => { result = output; }
          );

          return result;
        }).then(result => {
          log(`${green('INFO')}  ${yellow(item)} rendered finished (${+new Date() - START_TIME}ms).`);
          return writeFile(filename, result)
        }, e => {
          throw new Error(e);
        }).catch(e => {
          log.error(`${bgRed('ERROR')} ${yellow(item)} ${red(`rendered failed`)}, detailed error see below:`);
          console.error(e);
        });
      }

      return;
    }
  });

  Promise.all(Promise.map(items, doTask, { concurrency: 3 }));
}

main();
