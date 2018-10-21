var tape = require('tape');
var mjAPI = require("../lib/main.js");

tape('SVG output: add xlink to href in <image>', function(t) {
    t.plan(1);

    var mml = '<math><mglyph src="equation.svg" width="319pt" height="14pt"></mglyph></math>';
    var expected = /xlink:href/;

    mjAPI.typeset({
        math: mml,
        format: "MathML",
        svg: true
    }, function(data) {
        t.ok(data.svg.match(expected));
    });

});
