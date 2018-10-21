var tape = require('tape');
var mjAPI = require("../lib/main.js");
var jsdom = require('jsdom').jsdom;

tape('the SVG output should add dimensions and styles', function(t) {
    t.plan(3);

    var tex = 'a + b';

    mjAPI.typeset({
        math: tex,
        format: "TeX",
        svg: true
    }, function(data) {
        t.ok(data.width, 'Width is present');
        t.ok(data.height, 'Height is present');
        t.ok(data.style, 'Style is present');
    });

});
