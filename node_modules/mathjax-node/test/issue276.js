var tape = require('tape');
var mjAPI = require("../lib/main.js");
var JSDOM = require('jsdom').JSDOM;

tape('SVG output: physical units', function(t) {
    t.plan(1);

    var mml = '<math><mspace width="1cm"></mspace></math>';

    mjAPI.typeset({
        math: mml,
        format: "MathML",
        svg: true
    }, function(data) {
        var document = new JSDOM(data.svg).window.document;
        var width =  document.querySelector('svg').getAttribute('width');
        t.notEqual(width, '0', '');
    });

});
