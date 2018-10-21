const tape = require('tape');
const mjpage = require('../lib/main.js').mjpage;

tape('Support preprocessor configurations', function(t) {
    t.plan(4);

    const input = '%x%';
    mjpage(input, {
        format: ["TeX"],
        MathJax: {
            tex2jax: {
                inlineMath: [
                    ['%', '%']
                ]
            }
        }
    }, {
        mml: true
    }, function(output) {
        t.ok(output.indexOf(input) === -1, 'tex2jax configuration applies')
        t.ok(output.indexOf('<math') > -1, 'output present')
    });
    mjpage(input, {
        format: ["AsciiMath"],
        MathJax: {
            ascii2jax: {
                delimiters: [['%', '%']]
            }
        }
    }, {
        mml: true
    }, function(output) {
        t.ok(output.indexOf(input) === -1, 'input has been removed')
        t.ok(output.indexOf('<math') > -1, 'output present')
    });
});
