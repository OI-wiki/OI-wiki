const tape = require('tape');
tape('TeX input: processEscapes', function(t) {
    t.plan(1);
const mjpage = require('../lib/main.js').mjpage;
mjpage('\\$x\\$', {
    singleDollars: true,
    MathJax: {
        tex2jax: {
            processEscapes: true
        }
    }
}, {
    html: true
}, 
output => t.ok(output.indexOf('<span>$</span>x<span>$</span>') > -1), '\\$ escaped')
});