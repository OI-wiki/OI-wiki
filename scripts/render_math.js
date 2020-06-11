const { Worker } = require('worker_threads');
const Promise = require('bluebird');
const { join, dirname } = require('path');
const { green } = require('chalk');
const { listDir } = require('hexo-fs');

class WorkerPool {
  _workers = [];
  _activeWorkers = [];
  _queue = [];

  constructor(workerPath, numOfThreads) {
    this.workerPath = workerPath;
    this.numOfThreads = numOfThreads;
    this.init();
  }

  init() {
    if (this.numOfThreads < 1) {
      throw new Error('Number of threads should be at least 1');
    }

    for (let i = 0; i < this.numOfThreads; i++) {
      const worker = new Worker(this.workerPath);

      this._workers[i] = worker;
      this._activeWorkers[i] = false;
    }
  }

  // 结束线程池中所有线程
  destroy() {
    for (let i = 0; i < this.numOfThreads; i++) {
      if (this._activeWorkers[i]) {
        throw new Error(`Thread ${i} is still working`);
      }
      this._workers[i].terminate();
    }
  }

  // 检查是否有空闲worker
  checkWorkers() {
    for (let i = 0; i < this.numOfThreads; i++) {
      if (!this._activeWorkers[i]) {
        return i;
      }
    }

    return -1;
  }

  run(getData) {
    return new Promise((resolve, reject) => {
      const restWorkerId = this.checkWorkers();

      const queueItem = {
        getData,
        callback: (error, result) => {
          if (error) {
            return reject(error);
          }
          return resolve(result);
        }
      }

      // No more idle workers
      if (restWorkerId === -1) {
        this._queue.push(queueItem);
        return null;
      }

      // Let idle workers run
      this.runWorker(restWorkerId, queueItem);
    })
  }

  async runWorker(workerId, queueItem) {
    const worker = this._workers[workerId];
    this._activeWorkers[workerId] = true;

    const messageCallback = (result) => {
      queueItem.callback(null, result);
      cleanUp();
    };
    const errorCallback = (error) => {
      queueItem.callback(error);
      cleanUp();
    };

    // Clear up listeners
    const cleanUp = () => {
      worker.removeAllListeners('message');
      worker.removeAllListeners('error');

      this._activeWorkers[workerId] = false;

      if (!this._queue.length) {
        return null;
      }

      this.runWorker(workerId, this._queue.shift());
    }

    // create listeners
    worker.once('message', messageCallback);
    worker.once('error', errorCallback);
    // Send data to other newly created workers
    worker.postMessage(queueItem.getData);
  }
}

const distDir = join(dirname(__dirname) + '/site');
const workerPath = join(__dirname + '/render_math_worker.js');

const pool = new WorkerPool(workerPath, 4);
const START_TIME = +new Date();

Promise.all(listDir(distDir).map(async item => {
  if (item.endsWith('.html')) {
    const filename = join(distDir, item);
    await pool.run(filename);
  }
})).then(() => {
  pool.destroy();

  const END_TIME = +new Date();
  console.log(`${green('INFO')}  MathJax rendered finished in ${(END_TIME - START_TIME) / 1000}s.`);
})
