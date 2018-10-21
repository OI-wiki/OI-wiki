var tape = require('tape');
var mjAPI = require("../lib/main.js");

tape('basic test: check typeset promise API', function (t) {
    t.plan(2);

    mjAPI.config({displayErrors: false});

    var tex = '';

    //
    // promise resolved
    //
    mjAPI.typeset({
        math: tex,
        format: "TeX",
        mml: true
    }).then((result) => t.ok(result.mml, 'Typset promise resolved on success'));

    //
    // promise frejected
    //
    mjAPI.typeset({
        math: tex,
        format: "MathML",
        mml: true
    }).catch((error) => t.ok(error, 'Typeset promise rejected on error'));

    //
    // reset configuration
    //
    mjAPI.typeset({math: '', format: 'TeX', mml: true}, () => {
        mjAPI.config({displayErrors: true});
    });

});
