const tape = require('tape');
const mjpage = require('../lib/main.js').mjpage;
const jsdom = require('jsdom');
const { JSDOM } = jsdom;

tape('Prioritize outputs', function (t) {
    t.plan(2);
    const input = '<math><mi>a</mi></math>';
    mjpage(input, {
        format: ['MathML']
    }, {
        svg: true,
        mml: true,
        html: true
    }, function (output) {
        const document = new JSDOM(output).window.document;
        const result = document.querySelector('svg');
        t.ok(result, 'SVG output has high priority');
    });
    mjpage(input, {
        format: ['MathML']
    }, {
        mml: true,
        html: true
    }, function (output) {
        const document = new JSDOM(output).window.document;
        const result = document.querySelector('.mjx-chtml');
        t.ok(result, 'HTML output has medium priority');
    });
});
