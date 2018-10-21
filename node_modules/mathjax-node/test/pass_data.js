var tape = require('tape');
var mjAPI = require("../lib/main.js");

tape('Passing data along', function(t) {
    t.plan(1);

    var tex = 'x';

    mjAPI.typeset({
        math: tex,
        format: "TeX",
        css: true,
        something: 'expected',
    }, function(data, input) {
        t.equal(input.something, 'expected', 'Data was passed along to output');
    });

});
