var tape = require('tape');
var mjAPI = require("../lib/main.js");
var JSDOM = require('jsdom').JSDOM;

tape('Basic Check: pass jsdom object to output', function(t) {
    t.plan(3);

    var tex = 'x';

    mjAPI.typeset({
        math: tex,
        format: "TeX",
        html: true,
        htmlNode: true,
        svg: true,
        svgNode: true,
        mml: true,
        mmlNode: true
    }, function(data) {
        var window = new JSDOM().window;
        t.ok(data.htmlNode instanceof window.HTMLElement, 'htmlNode is an HTMLElement');
        t.ok(data.svgNode instanceof window.SVGElement, 'svgNode is an SVGElement');
        t.ok(data.mmlNode instanceof window.Element, 'mmlNode is an Element');
    });

});
