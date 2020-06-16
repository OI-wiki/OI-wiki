const { Worker } = require('worker_threads');
const Promise = require('bluebird');

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

  destroy() {
    for (let i = 0; i < this.numOfThreads; i++) {
      if (this._activeWorkers[i]) {
        throw new Error(`Thread ${i} is still working`);
      }
      this._workers[i].terminate();
    }
  }

  // Check if any idle workers
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

module.exports = WorkerPool;
