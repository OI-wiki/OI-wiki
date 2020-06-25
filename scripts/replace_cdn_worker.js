const { isMainThread, parentPort } = require('worker_threads');

if (isMainThread) {
  throw new Error('Its not a worker');
}

const { readFile, writeFile } = require('hexo-fs');

async function replaceStaticFilesCdn(filename) {
  const content = await readFile(filename);

  const result = content.replace(/[^"']*assets[^"']*/g, s => {
    return 'https://cdn-for-oi-wiki.billchn.com/' + s;
  });

  return writeFile(filename, result);
}

parentPort.on('message', async filename => {
  await replaceStaticFilesCdn(filename);
  parentPort.postMessage('Done');
});
