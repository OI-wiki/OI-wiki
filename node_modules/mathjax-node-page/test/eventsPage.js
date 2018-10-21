const tape = require('tape');
const mjpage = require('../lib/main.js').mjpage;

const input = '\\[\\LaTeX\\]';

tape('Check page conversion events', function(t) {
    t.plan(3);
    mjpage(input, {
        format: ["TeX"]
    }, {
        svg: true
    }, function(output) {
        t.ok(output, 'output was provided');
    })
    .on('beforeSerialization', function(document, css) {
        t.ok(document && document.body.innerHTML, 'document is jsdom node with non-empty contents');
        t.ok(css && typeof css === 'string', 'css argument is provided to beforeSerialization handler');
    });
});
