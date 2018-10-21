var tape = require('tape');
var mjAPI = require("../lib/main.js");
var mjVersion = require('../package-lock.json').dependencies['mathjax'].version

tape('basic configuration: check fontURL', function (t) {
    t.plan(2);

    var tex = 'a';

    mjAPI.typeset({
        math: tex,
        format: "TeX",
        css: true,
        htmlNode: true
    }, function (result, data) {
        var mjVersion = result.htmlNode.ownerDocument.defaultView.MathJax.version;
        var URL = 'https://cdnjs.cloudflare.com/ajax/libs/mathjax/' + mjVersion + '/fonts/HTML-CSS';
        t.ok(result.css.indexOf(URL) > -1, 'Default fontURL');

        //
        // reconfigure
        //
        mjAPI.config({
            fontURL: 'https://example.com'
        });
        mjAPI.start();

        //
        // Next test
        //

        mjAPI.typeset({
            math: 'a',
            format: "TeX",
            css: true,
        }, function (result, data) {
            t.ok(result.css.indexOf('https://example.com') > -1, 'Configuring fontURL');
            //
            // reconfigure
            //
            mjAPI.config({fontURL: ''});
            mjAPI.start();
        });

    });
});
