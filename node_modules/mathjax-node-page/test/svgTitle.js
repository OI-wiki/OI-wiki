const tape = require('tape');
const mjpage = require('../lib/main.js').mjpage;
const jsdom = require('jsdom');
const { JSDOM } = jsdom;
const exec = require('child_process').exec

tape('SVG tags get titles by default in lib', function(t) {
    t.plan(1);
    const input = '\\(a^2 + b^2 = c^2\\)';
    const expected = 1;
    mjpage(input, {
        format: ['TeX']
    }, {
        svg: true
    }, function(output) {
      const document = new JSDOM(output).window.document;
      const result = document.querySelectorAll('title').length;
      t.equal(result, expected, 'There is a title tag');
    });
});


tape('SVG tags get titles by default in cli', function(t) {
    t.plan(1);
    let child = exec('echo "\\(a^2 + b^2 = c^2\\)" | node ./bin/mjpage',
      function (error, stdout, stderr) {
        t.equal(stdout.indexOf("title") > -1, true, 'There is a title tag');
    });


});
