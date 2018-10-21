const tape = require('tape');
const mjpage = require('../lib/main.js').mjpage;
const jsdom = require('jsdom');
const { JSDOM } = jsdom;

tape('(issue 61) global SVG should have a namespace attribute', function(t) {
    t.plan(1);
    const input = `In equation \\eqref{eq_sample}, we find the value of an
    interesting integral:
    \\begin{equation}
      a\\label{eq_sample}\\tag{My Equation}
    \\end{equation}`;
    mjpage(input, {
        format: ['TeX']
    }, {
        html: true
    }, function(output) {
      const document = new JSDOM(output).window.document;
      t.equal(document.querySelector('a').getAttribute('href'), '#mjx-eqn-eq_sample', 'Issue 61: global SVG should have SVG namespace');
    });
});
