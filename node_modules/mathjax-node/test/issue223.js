var tape = require('tape');
var mjAPI = require("../lib/main.js");
var JSDOM = require('jsdom').JSDOM;

tape('displayIndent:left in HTML output', function(t) {
    t.plan(2);

    mjAPI.config({MathJax: {displayIndent: '10em'}});
    mjAPI.start();
    
    var first = 'x';
    var second = 'x \\tag{1}'
    expected = "10em";

    //
    // basic text
    //  
    mjAPI.typeset({
        math: first,
        format: "TeX",
        html: true
    }, function(data) {
        var document = new JSDOM(data.html).window.document;
        var element = document.getElementsByClassName('MJXc-display')[0];
        var result = element.style.marginLeft;
        t.ok((result === expected), 'style includes a margin');
    });

    //
    // test for mlabeledtr
    //
    mjAPI.typeset({
        math: second,
        format: "TeX",
        html: true
    }, function(data) {
        var document = new JSDOM(data.html).window.document;
        var element = document.getElementsByClassName('mjx-table')[0];
        var result = element.style.marginLeft;
        t.ok((result === expected), 'style includes a margin');
        //
        // reset configuration
        //
        mjAPI.config({MathJax: {}});
        mjAPI.start();
    });

});
