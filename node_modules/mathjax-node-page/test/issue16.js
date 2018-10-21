const tape = require('tape');
const mjpage = require('../lib/main.js').mjpage;

tape('Document without math (issue 16)', function(t) {
    t.plan(2);
    const input = '';
    mjpage(input, {
        format: ["TeX"]
    }, {
        svg: true,
        useGlobalCache: true
    }, function(output) {
        t.ok(output.indexOf('<defs id="MathJax_SVG_glyphs">') === -1, '<defs> not added')
    });
    mjpage(input, {
        format: ["TeX"]
    }, {
        html: true
    }, function(output) {
        t.ok(output.indexOf('<style') === -1, 'style not added')
    });
});
