const tape = require('tape');
const mjpage = require('../lib/main.js').mjpage;

tape('Configuration option (global) for output', function(t) {
    t.plan(1);
    const input = '$$x$$';
    mjpage(input,
    {
        format: ["TeX"],
        output: "svg"
    },
    {
        svg: false,
        html: true
    },
    function(output) {
        t.ok(output.includes('id="MathJax-SVG-1-Title"'), 'global config overrides')
    });
});
