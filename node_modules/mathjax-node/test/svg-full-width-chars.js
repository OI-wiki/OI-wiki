var tape = require('tape');
var mjAPI = require("../lib/main.js");

tape('the SVG output should renders full-width characters correctly', function(t) {
    t.plan(1);

    mjAPI.config({displayErrors: false});

    var tex = '\\text{\u62FE\u96F6}^i';

    mjAPI.typeset({
        math: tex,
        format: "TeX",
        svg: true
    }, function(data) {
        t.ok(data.width, '5.133ex', 'Width is correct');
        mjAPI.config({displayErrors: true});  // reset configuration
    });

});
