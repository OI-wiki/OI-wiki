var tape = require('tape');
var mjAPI = require("../lib/main.js");

tape('mmlNode should not produce mml', function(t) {
    t.plan(1);

    var tex = 'x';

    mjAPI.typeset({
        math: tex,
        format: "TeX",
        mmlNode: true
    }, function(data) {
        t.ok(data.mml === undefined, 'mml not generated');
    });

});
