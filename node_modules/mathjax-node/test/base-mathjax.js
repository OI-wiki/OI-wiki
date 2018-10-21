var tape = require('tape');
var mjAPI = require("../lib/main.js");

tape('basic test: check MathJax core', function(t) {
    t.plan(2);

    var tex = '';

    mjAPI.typeset({
        math: tex,
        format: "TeX",
        mml: true
    }, function(result,data) {
        t.ok(result.mml, 'MathJax core seems ok');
        t.ok(data.format, 'MathJax input preserved');
    });

});
