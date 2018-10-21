var tape = require('tape');
var mjAPI = require("../lib/main.js");
var JSDOM = require('jsdom').JSDOM;

tape('HTML output should remove automatically generated IDs', function(t) {
    t.plan(2);

    var tex = 'a \\\\ b';
    var expected = '100ex';

    mjAPI.typeset({
        math: tex,
        format: "TeX",
        html: true
    }, function(data) {
        var document = new JSDOM(data.html).window.document;
        var id = document.querySelector('[id^="MJXc-Node-"]');
        var frame = document.querySelector('[id^="MathJax-Element-"]');
        t.notOk(id, 'automatic ids successfully removed');
        t.notOk(frame, 'MathJax-Element-[n]-frame id successfully removed');
    });

});
