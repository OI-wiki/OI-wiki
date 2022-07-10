import bluebird from "bluebird";
import { join, dirname } from "path";
import chalk from "chalk";
import hexoFs from "hexo-fs";
import { cpus } from "os";
import WorkerPool from "./worker-pool.js";
import url from "url";

const { all } = bluebird;
const { green } = chalk;
const { listDir } = hexoFs;

const __dirname = dirname(url.fileURLToPath(import.meta.url));
const distDir = join(process.cwd() + "/site");
const workerPath = join(__dirname + "/render_math_worker.ts");

// Maxmize CPU performance
const cpuNums = cpus().length;
console.log(`${green("INFO")}  ${cpuNums} CPU Threads detected, using ${cpuNums} threads`);

const pool = new WorkerPool(workerPath, cpuNums);
const START_TIME = +new Date();

all(
  listDir(distDir).map(async item => {
    if (item.endsWith(".html")) {
      const filename = join(distDir, item);
      await pool.run(filename);
    }
  })
).then(() => {
  pool.destroy();

  const END_TIME = +new Date();
  console.log(`${green("INFO")}  MathJax rendered finished in ${(END_TIME - START_TIME) / 1000}s.`);
});
