const tape = require('tape');
const mjpage = require('../lib/main.js').mjpage;
const jsdom = require('jsdom');
const { JSDOM } = jsdom;

tape('Display math gets centered', function(t) {
    t.plan(1);
    const input = '\\[ e^{i\\pi} = -1 \\]';
    mjpage(input, {
        format: ['TeX']
    }, {
        svg: true
    }, function(output) {
			const window = new JSDOM(output).window
			const style = window.getComputedStyle(window.document.querySelector('.mjpage'))
      t.equal(style.textAlign, "center", 'Equation is centered');
    });
});
