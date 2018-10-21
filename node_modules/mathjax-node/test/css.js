var tape = require('tape');
var mjAPI = require("../lib/main.js");

tape('CSS output', function(t) {
    t.plan(3);

    mjAPI.typeset({
        math: tex,
        format: "TeX",
        css: true
    }, function(data) {
        t.ok(data.css, 'css output while no other output');
    });

    var tex = 'x';

    mjAPI.typeset({
        math: tex,
        format: "TeX",
        css: true,
        svg: true
    }, function(data) {
        t.ok(data.css, 'css output created alongside SVG output');
        t.ok(data.svg, 'svg output is created');
    });

});
