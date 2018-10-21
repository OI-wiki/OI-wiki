var tape = require('tape');
var mjAPI = require("../lib/main.js");
var JSDOM = require('jsdom').JSDOM;

tape('color extension should be reset', function(t) {
    t.plan(3);

    mjAPI.config({displayErrors: false});

    var tex = '\\colorbox{green}{x}';
    var tex2 = '\\color{red}{x}x';

    mjAPI.typeset({
        math: tex,
        format: "TeX",
        mml: true
    }, function(data) {
        t.ok(data.errors, 'Color extension disabled');
    });

    mjAPI.typeset({
        math: tex2,
        format: "TeX",
        mml: true
    }, function(data) {
        var document = new JSDOM(data.mml).window.document;
        var mstyle = document.querySelector('mstyle');
        t.ok(document.querySelectorAll('mi')[0].parentNode === mstyle, 'Color macro behaves correctly (1 of 2)');
        t.notOk(document.querySelectorAll('mi')[1].parentNode === mstyle, 'Color macro behaves correctly (2 of 2)');
        mjAPI.config({displayErrors: true});  // reset configuration
    });

});
