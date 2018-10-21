const tape = require('tape');
const mjpage = require('../lib/main.js').mjpage;

tape('HTML: fontface url', function(t) {
    t.plan(2);
    const input = '$$x^2$$';
    mjpage(input, {
        format: ["TeX"]
    }, {
        html: true,
        css: true
    }, function(output) {
        t.ok(output.indexOf('https://cdn.mathjax.org/mathjax/latest/fonts/HTML-CSS/'), 'Default font URL')
    });
    mjpage(input, {
        format: ["TeX"]
    }, {
        html: true,
        css: true,
        fontUrl: 'https://example.com/'
    }, function(output) {
        t.ok(output.indexOf('https://example.com'), 'Custom font URL')
    });
});
