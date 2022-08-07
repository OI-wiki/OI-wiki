import fs from "fs";
import path from "path";
import url from "url";
import os from "os";
import { Worker, isMainThread, parentPort, MessagePort } from "worker_threads";
import { parse, HTMLElement } from "node-html-parser";
import klaw from "klaw";
import chalk from "chalk";

const TASKS = ["commits-info", "math"];
const SITE_DIR = "site";

const siteDir = path.resolve(SITE_DIR);

const __filename = url.fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

/**
 * `undefined` in main thread.
 */
export let workerId: number;

export function log(message: string) {
  console.log(`${chalk.green(workerId == null ? "[Main]" : `[Worker ${workerId}]`)} ${message}`);
}

/**
 * All task modules run in worker thread when process HTML files.
 *
 * For each task module, it's loaded in the main thread, and globalInitialize() is called.
 * Then its initialize() is called in each worker thread, wieh the result of global initialize.
 * After all files got processed, each worker's finalize() is called.
 *
 * `siteDir` and `filePath` are **absolute** paths.
 */
export interface TaskHandler<GlobalInitializationResult = unknown> {
  globalInitialize?(siteDir: string): Promise<GlobalInitializationResult>;
  initialize?(globalInitializationResult: GlobalInitializationResult, siteDir: string): Promise<void>;
  process(document: HTMLElement, filePath: string): Promise<void>;
  finalize?(): Promise<void>;
}

/**
 * Load task handlers from corresponding directories with dynamic import.
 */
async function loadTaskHandlers(tasks: string[], onLoaded?: (taskHandler: TaskHandler, i: number) => Promise<void>) {
  return await Promise.all(
    tasks.map(async (task, i) => {
      const taskHandlerFile = path.join(__dirname, task, "task-handler.ts");
      const taskHandler: TaskHandler & { name: string } = (await import(taskHandlerFile)).taskHandler;
      taskHandler.name = task;
      if (onLoaded) {
        await onLoaded(taskHandler, i);
      }
      return taskHandler;
    })
  );
}

/**
 * The message send from main thread to worker thread.
 */
type WorkerMessage =
  | {
      type: "initialize";
      workerId: number;
      tasks: {
        name: string;
        globalInitializationResult: unknown;
      }[];
    }
  | {
      type: "file";
      filePath: string;
    }
  | {
      type: "finalize";
    };

/**
 * The message send from worker thread to main thread.
 */
type WorkerResponseMessage =
  | {
      type: "ready";
    }
  | {
      type: "finished";
      totalTimeByTask: Record<string, number>;
    };

/**
 * Post a message and wait for a "ready" message,
 * or just wait when "messageToPost" is falsy.
 * or just post when "messageToWait" is falsy (no promise returned).
 */
function communicate<
  MessageToPost extends WorkerMessage | WorkerResponseMessage,
  MessageToWait extends WorkerMessage | WorkerResponseMessage,
  TypeToPost extends MessageToPost["type"],
  TypeToWait extends MessageToWait["type"]
>(to: Worker | MessagePort, messageToPost: MessageToPost | TypeToPost, messageToWait: TypeToWait) {
  type ResponseType = MessageToWait & { type: TypeToWait };
  const readyPromise =
    messageToWait &&
    new Promise<ResponseType>(resolve => {
      function onMessage(message: MessageToWait) {
        if (message.type === messageToWait) {
          to.off("message", onMessage);
          resolve(message as ResponseType);
        }
      }
      to.on("message", onMessage);
    });

  if (messageToPost) to.postMessage(typeof messageToPost === "string" ? { type: messageToPost } : messageToPost);
  return readyPromise;
}

/**
 * Measure the execution time of a sync or async operation.
 */
function measureTime<T>(operation: () => T): T extends Promise<any> ? Promise<number> : number {
  const startTime = +new Date();
  const end = () => +new Date() - startTime;

  const returnValue = operation();
  if (Object.prototype.toString.call(returnValue) === "[object Promise]")
    return (returnValue as unknown as Promise<void>).then(end) as any;
  return end() as any;
}

(async () => {
  if (isMainThread) {
    const tasks = process.argv.slice(2);
    tasks.forEach(task => {
      if (!TASKS.includes(task)) {
        log(`No such task: ${task}`);
        process.exit(2);
      }
    });

    // Initialize task handlers (global initialization)
    const taskHandlers = await loadTaskHandlers(tasks);
    const tasksWithGIR = await Promise.all(
      tasks.map(async (task, i) => {
        let globalInitializationResult: unknown;
        if (taskHandlers[i].globalInitialize) {
          const time = await measureTime(async () => {
            globalInitializationResult = await taskHandlers[i].globalInitialize(siteDir);
          });
          log(`Global Initialization of task ${chalk.blueBright(task)} took ${chalk.cyanBright(`${time}ms`)}`);
        }
        return {
          name: task,
          globalInitializationResult
        };
      })
    );

    const workers: Worker[] = [];
    for (let i = 0; i < os.cpus().length; i++) {
      const worker = new Worker(__filename, {
        execArgv: ["--loader", "ts-node/esm"]
      });
      for (const error of ["error", "messageerror"]) {
        worker.on(error, error => {
          log(`Error from worker: ${error.stack}`);
          process.exit(1);
        });
      }
      workers.push(worker);
    }

    // Intialize all workers
    await Promise.all(
      workers.map((worker, workerId) =>
        communicate(
          worker,
          {
            type: "initialize",
            workerId,
            tasks: tasksWithGIR
          },
          "ready"
        )
      )
    );

    // A simple task queue for workers
    const availableWorkers: number[] = [...workers.keys()];
    const fileQueue: {
      filePath: string;
      resolve: () => void;
    }[] = [];
    // If there're any available workers, start consuming the queue
    const tryStartConsumingQueue = async () => {
      if (availableWorkers.length > 0) {
        const i = availableWorkers.pop();
        while (fileQueue.length > 0) {
          const { filePath, resolve } = fileQueue.shift();
          await communicate(
            workers[i],
            {
              type: "file",
              filePath
            },
            "ready"
          );
          resolve();
        }
        availableWorkers.push(i);
      }
    };
    // Run on any available worker or enqueue if none
    const enqueueFile = (filePath: string) =>
      new Promise<void>(resolve => {
        fileQueue.push({ filePath, resolve });

        tryStartConsumingQueue();
      });

    // Wait for processing all files
    await new Promise(resolve => {
      const promises: Promise<void>[] = [];
      klaw(siteDir)
        .on("data", item => {
          if (item.stats.isFile() && item.path.toLowerCase().endsWith(".html")) {
            promises.push(enqueueFile(item.path));
          }
        })
        .on("end", () => Promise.all(promises).then(resolve));
    });

    // Intialize all workers
    const finishedMessages = await Promise.all(workers.map(worker => communicate(worker, "finalize", "finished")));
    const totalTimeByTask = Object.fromEntries(
      tasks.map(task => [task, finishedMessages.reduce((s, message) => s + message.totalTimeByTask[task], 0)])
    );
    const totalTime = Object.entries(totalTimeByTask).reduce((s, [, time]) => s + time, 0);
    log(
      `Took ${Object.entries(totalTimeByTask)
        .map(([taskName, time]) => `${chalk.cyanBright(`${time}ms`)} on task ${chalk.blueBright(taskName)}`)
        .join(", ")}, ${chalk.cyanBright(`${totalTime}ms`)} in total`
    );

    process.exit(0);
  } else {
    const initializeMessage = await communicate(parentPort, null, "initialize");
    workerId = initializeMessage.workerId;

    const totalTimeByTask: Record<string, number> = Object.fromEntries(
      initializeMessage.tasks.map(({ name }) => [name, 0])
    );

    // Load and initialize task handlers
    const taskHandlers = await loadTaskHandlers(
      initializeMessage.tasks.map(task => task.name),
      async (taskHandler, i) => {
        if (taskHandler.initialize) {
          const time = await measureTime(() =>
            taskHandler.initialize(initializeMessage.tasks[i].globalInitializationResult, siteDir)
          );
          totalTimeByTask[initializeMessage.tasks[i].name] += time;
          log(
            `Initialization of task ${chalk.blueBright(initializeMessage.tasks[i].name)} took ${chalk.cyanBright(
              `${time}ms`
            )}`
          );
        }
      }
    );

    // Now this worker is ready
    communicate(parentPort, "ready", null);

    const handleFile = async (filePath: string) => {
      const fileContent = await fs.promises.readFile(filePath, "utf-8");
      const html = parse(fileContent);

      for (const taskHandler of taskHandlers) {
        const time = await measureTime(() => taskHandler.process(html, filePath));
        totalTimeByTask[taskHandler.name] += time;
        log(
          `${chalk.yellow(filePath)} took ${chalk.cyanBright(`${time}ms`)} on task ${chalk.blueBright(
            taskHandler.name
          )}`
        );
      }

      await fs.promises.writeFile(filePath, html.outerHTML, "utf-8");
    };

    // Start consuming the queue
    parentPort.on("message", async (message: WorkerMessage) => {
      if (message.type === "file") {
        await handleFile(message.filePath);
        communicate(parentPort, "ready", null);
      } else if (message.type === "finalize") {
        await Promise.all(
          taskHandlers.map(async taskHandler => {
            if (taskHandler.finalize) {
              const time = await measureTime(() => taskHandler.finalize());
              totalTimeByTask[taskHandler.name] += time;
              log(`Finalization of task ${chalk.blueBright(taskHandler.name)} took ${chalk.cyanBright(`${time}ms`)}`);
            }
          })
        );

        const totalTime = Object.entries(totalTimeByTask).reduce((s, [, time]) => s + time, 0);
        log(
          `Took ${Object.entries(totalTimeByTask)
            .map(([taskName, time]) => `${chalk.cyanBright(`${time}ms`)} on task ${chalk.blueBright(taskName)}`)
            .join(", ")}, ${chalk.cyanBright(`${totalTime}ms`)} in total`
        );
        communicate(parentPort, { type: "finished", totalTimeByTask }, null);
      }
    });
  }
})();
