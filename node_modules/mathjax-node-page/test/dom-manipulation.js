const tape = require('tape');
const fs = require('fs');
const mjpage = require('../lib/main.js').mjpage;

const input = '\\[\\LaTeX\\]';

tape('DOM manipulations (issue 7)', function(t) {
    t.plan(2);
    mjpage(input, {
        format: ["TeX"]
    }, {
        svg: true
    }, function(output) {
        t.ok(output.search('<span class="mjpage mjpage__block">changed</span>') !== -1,
          'formula was properly modified through afterConversion hook');
        t.ok(output.search('<span class="test"></span>') !== -1,
          'DOM was modified through beforeSerialization hook');
    })
    .on('beforeSerialization', function(document, css) {
        // append test element
        const testEl = document.createElement('span');
        testEl.className = "test";
        document.body.appendChild(testEl);
    })
    .on('afterConversion', function(parsedFormula) {
        parsedFormula.node.innerHTML = "changed";
    });
});
