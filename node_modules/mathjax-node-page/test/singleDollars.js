const tape = require('tape');
const mjpage = require('../lib/main.js').mjpage;

tape('Support singleDollars', function(t) {
    const input = '$\\LaTeX$';
    t.plan(4);
    mjpage(input, {
        format: ["TeX"],
        singleDollars: true
    }, {
        mml: true
    }, function(output) {
        t.ok(output.indexOf(input) === -1, 'When true, input removed')
        t.ok(output.indexOf('<math') > -1, 'When true, output present')
    });
    mjpage(input, {
        format: ["TeX"],
        singleDollars: false
    }, {
        mml: true
    }, function(output) {
        t.ok(output.indexOf(input) > -1, 'When false, input not removed')
        t.ok(output.indexOf('<math') === -1, 'When false, output not present')
    });
});
