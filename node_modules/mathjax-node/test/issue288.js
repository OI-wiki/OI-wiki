var tape = require('tape');
var mjAPI = require("../lib/main.js");

tape('HTML output when requesting both SVG and HTML', function(t) {
    t.plan(2);

    var tex = 'x';

    mjAPI.typeset({
        math: tex,
        format: "TeX",
        htmlNode: true,
        svgNode: true
    }, function(data) {
        t.equal(data.htmlNode.className, 'mjx-chtml MJXc-display', 'htmlNode output is correct');
    });

    mjAPI.typeset({
        math: tex,
        format: "TeX",
        html: true,
        svgNode: true
    }, function(data) {
        t.ok(data.html, 'html output is present')
    });

});
