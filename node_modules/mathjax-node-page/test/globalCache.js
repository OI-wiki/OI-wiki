const tape = require('tape');
const mjpage = require('../lib/main.js').mjpage;

tape('Support globalCache', function(t) {
    const input = '$$\\LaTeX$$';
    t.plan(1);
    mjpage(input, {
        format: ["TeX"]
    }, {
        svg: true,
        useGlobalCache: true
    }, function(output) {
        t.ok(output.indexOf('<defs id="MathJax_SVG_glyphs">') > -1, '<defs> present')
    });
});
