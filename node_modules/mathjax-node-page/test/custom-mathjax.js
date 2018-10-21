const tape = require('tape');
const fs = require('fs');
const mjpage = require('../lib/main.js');

const input = '\\[\\LaTeX\\]';

function spy() {
    function func() {
        func.calls++;
    }
    func.calls = 0;
    return func;
}

function typesetStub() {
    function func(conf, cb) {
        func.calls++;
        let res = {};
        res.mml = res.html = res.svg = conf.math;
        setTimeout(() => cb(res), 0);
    }
    func.calls = 0;
    return func;
}

tape('User can pass custom mathjax-node', function(t) {
    t.plan(3);

    const mjnode = {
        config: spy(),
        start: spy(),
        typeset: typesetStub()
    };

    mjpage.init(mjnode);

    mjpage.mjpage(input, {
        format: ["TeX"]
    }, {
        svg: true
    }, function(output) {
        t.ok(output.indexOf(input.slice(2,-2))!==-1, 'Output equals input with custom mjNode');
        t.ok(mjnode.config.calls === 1, 'config function called once');
        t.ok(mjnode.typeset.calls === 2, 'typeset function called twice (one dummy call in the end)');
        mjpage.init();  // reset for other tests
    });
});
