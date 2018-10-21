const tape = require('tape');
const mjpage = require('../lib/main.js').mjpage;

tape('Configuration for mathjax-node', function (t) {
    t.plan(1);
    const input = '$$x$$';
    const expected = 1;
    mjpage(input, {
        format: ['TeX'],
        MathJax: {
            SVG: {
                font: "STIX-Web"
            }
        }
    }, {
        svg: true
    }, function (output) {
        t.ok(output.indexOf('STIXWEBMAINI'), 'Configuration');
    });
});