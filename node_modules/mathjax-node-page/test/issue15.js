const tape = require('tape');
const mjpage = require('../lib/main.js').mjpage;

const exec = require('child_process').exec
tape('Configuration option for jsdom (issue 15)', function(t) {
    const input = '<script>console.log("error")</script>';
    t.plan(1);
    const expected = `<html><head><script>console.log(error)</script></head><body>\n</body></html>`;

    let child = exec(`cat test/data/issue15.html | node ./bin/mjpage`,
      function (error, stdout, stderr) {
        t.equal(stdout, expected, 'Virtual Console not activated');
    });
});
