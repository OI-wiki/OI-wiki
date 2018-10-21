var tape = require('tape');
var mjAPI = require("../lib/main.js");
var JSDOM = require('jsdom').JSDOM;

tape('Generate dummy speechText', function(t) {
    t.plan(9);

    var input1 = 'source';
    var input2 = '<math display="block" alttext="alttext"><mi>x</mi></math>';
    var input3 = '<math display="block"><mi>x</mi></math>';
    var expected1 = 'source';
    var expected2 = 'alttext';
    var expected3 = 'Equation';
    var desc1 = 'source';
    var desc2 = 'original MathML alttext';
    var desc3 = 'default dummy value';

    mjSpeechTest = function(data, expected, desc) {
        var document = new JSDOM(data.html).window.document;
        var element = document.querySelector('.mjx-math');
        var actual = element.getAttribute('aria-label');
        t.equal(actual, expected, 'HTML output contains speechText from ' + desc);
        document = new JSDOM(data.mml).window.document;
        element = document.querySelector('math');
        actual = element.getAttribute('alttext');
        t.equal(actual, expected, 'MathML output contains speechText from ' + desc);
        document = new JSDOM(data.svg).window.document;
        var svgTitle = document.querySelector('title');
        actual = svgTitle.innerHTML;
        t.equal(actual, expected, 'SVG output contains speechText from ' + desc);
    };

    //
    // TeX source
    //
    mjAPI.typeset({
        math: input1,
        format: "TeX",
        html: true,
        svg: true,
        mml: true
    }, function(data) {mjSpeechTest(data, expected1, desc1)});

    //
    // MathML alttext
    //
    mjAPI.typeset({
        math: input2,
        format: "MathML",
        html: true,
        svg: true,
        mml: true
    }, function(data) {mjSpeechTest(data, expected2, desc2)});

    //
    // MathML without alttext
    //
    mjAPI.typeset({
        math: input3,
        format: "MathML",
        html: true,
        svg: true,
        mml: true
    }, function(data) {mjSpeechTest(data, expected3, desc3)});

});
