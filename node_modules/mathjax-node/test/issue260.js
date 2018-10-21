var tape = require('tape');
var mjAPI = require('../lib/main.js');

tape('getSVG should increment state.ID', function(t) {
    t.plan(1);

    var mml = '<math><mn>1</mn></math>';
    var state = {};

    mjAPI.typeset({
        math: mml,
        format: 'MathML',
        speakText: true,
        svg: true,
        state: state}, function(data) {});
    mjAPI.typeset({
        math: mml,
        format: 'MathML',
        speakText: true,
        svg: true,
        state: state
    }, function(data) {
        t.equal(state.ID, 2, 'state.ID incremented')
    });

});
