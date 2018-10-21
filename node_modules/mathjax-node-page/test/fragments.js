const tape = require('tape');
const mjpage = require('../lib/main.js').mjpage;

tape('Support fragments', function(t) {
    const input = 'Hello world';
    t.plan(1);
    mjpage(input, {
        format: ["TeX"],
        fragment: true
    }, {
        mml: true
    }, function(output) {
      t.ok(output.indexOf('<body>') === -1, 'present')
    });
});
