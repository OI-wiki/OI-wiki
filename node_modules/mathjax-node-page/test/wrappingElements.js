const tape = require('tape');
const mjpage = require('../lib/main.js').mjpage;
const jsdom = require('jsdom');
const { JSDOM } = jsdom;

tape('Math gets wrapping span with correct class', function(t) {
    t.plan(2);
    const input = '\\(a\\) \\[a\\] <math display="block"><mi>a</mi></math> <math><mi>a</mi></math>';
    const expected_1 = 4;
    const expected_2 = 2;
    mjpage(input, {
        format: ["TeX", "MathML"]
    }, {
        svg: true,
        useGlobalCache: true
    }, function(output) {
      const document = new JSDOM(output).window.document;
      const result_1 = document.querySelectorAll('.mjpage').length;
      const result_2 = document.querySelectorAll('.mjpage__block').length;
      t.equal(result_1, expected_1, 'Wrapping spans with base class');
      t.equal(result_2, expected_2, 'Wrapping spans with block element class');
    });
});
