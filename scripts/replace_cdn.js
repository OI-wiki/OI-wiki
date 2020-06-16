const Promise = require('bluebird');
const { join, dirname } = require('path');
const { green } = require('chalk');
const { listDir } = require('hexo-fs');
const { cpus } = require('os');
const WorkerPool = require('./worker-pool');

const distDir = join(dirname(__dirname) + '/site-cdn-pages');
const workerPath = join(__dirname + '/replace_cdn_worker.js');

// Maxmize CPU performance
const cpuNums = cpus().length;
console.log(`${green('INFO')}  ${cpuNums} CPU Threads detected, using ${cpuNums} threads`);

const pool = new WorkerPool(workerPath, cpuNums);

let HTML_NUMS = 0;
const START_TIME = +new Date();

Promise.all(listDir(distDir).map(async item => {
  if (item.endsWith('.html')) {
    const filename = join(distDir, item);
    HTML_NUMS++
    await pool.run(filename);
  }
})).then(() => {
  pool.destroy();

  const END_TIME = +new Date();
  console.log(`${green('INFO')}  CDN replacement for ${HTML_NUMS} html files finished in ${(END_TIME - START_TIME) / 1000}s.`);
})
