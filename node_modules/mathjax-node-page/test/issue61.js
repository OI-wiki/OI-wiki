const tape = require('tape');
const mjpage = require('../lib/main.js').mjpage;
const jsdom = require('jsdom');
const { JSDOM } = jsdom;

tape('(issue 61) global SVG should have a namespace attribute', function(t) {
    t.plan(1);
    const input = `$$a^2$$`;
    mjpage(input, {
        format: ['TeX']
    }, {
        svg: true,
        useGlobalCache: true
    }, function(output) {
      const document = new JSDOM(output).window.document;
      const globalSVG = document.querySelectorAll('svg')[1];
      t.equal(globalSVG.getAttribute('xmlns'), 'http://www.w3.org/2000/svg', 'Issue 61: global SVG should have SVG namespace');
    });
});
