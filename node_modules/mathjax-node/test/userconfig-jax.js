var tape = require('tape');
var mjAPI = require('../lib/main.js');

tape('User configuration with jax array', function (t) {
    t.plan(1);

    mjAPI.config({
        MathJax: {
            jax: ["input/MathML", "output/SVG"]
        }
    });
    mjAPI.start();

    mjAPI.typeset({
        math: '<math><mn>1</mn></math>',
        format: 'MathML',
        svg: true
    }, function (data) {
        t.ok(!data.errors, 'No errors');
        //
        // reset configuration
        //
        mjAPI.config({MathJax: {}});
        mjAPI.start();
    });

});
