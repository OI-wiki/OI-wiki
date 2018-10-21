var tape = require('tape');
var mjAPI = require("../lib/main.js");

tape('basic configuration: useFontCache', function (t) {
    t.plan(2);

    var tex = 'a';

    mjAPI.typeset({
        math: tex,
        format: "TeX",
        svg: true,
        useFontCache: false
    }, function (result, data) {
        t.ok(result.svg.indexOf('<use') === -1, 'useFontCache set to false');
    });

    mjAPI.typeset({
        math: tex,
        format: "TeX",
        svg: true,
        useFontCache: true
    }, function (result, data) {
        t.ok(result.svg.indexOf('<use') >  -1, 'useFontCache set to true');
    });

});
