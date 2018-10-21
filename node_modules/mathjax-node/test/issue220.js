var tape = require('tape');
var mjAPI = require("../lib/main.js");
var JSDOM = require('jsdom').JSDOM;

tape('displayAlign:left in HTML output', function(t) {
    t.plan(1);

    mjAPI.config({MathJax: {"displayAlign": "left"}});
    mjAPI.start();

    var tex = 'x';
    var expected = "text-align: left;";

    mjAPI.typeset({
        math: tex,
        format: "TeX",
        html: true
    }, function(data) {
        var document = new JSDOM(data.html).window.document;
        var element = document.getElementsByClassName("MJXc-display")[0];
        var result = element.getAttribute('style');
        t.equal(result, expected);
        //
        // reset configuration
        //
        mjAPI.config({MathJax: {}});
        mjAPI.start();
    });

});
