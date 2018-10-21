var tape = require('tape');
var mjAPI = require("../lib/main.js");

tape('User config: autoload-all should enable color extension', function(t) {
    t.plan(1);

    mjAPI.config( {
        extensions: 'TeX/autoload-all', // a convenience option to add MathJax extensions
    });
    mjAPI.start();

    var tex = '\\definecolor{myorange}{RGB}{255,165,100}\\color{myorange}e^{i \\pi}\\color{Black} = -1';

    mjAPI.typeset({
        math: tex,
        format: "inline-TeX",
        mml: true
    }, function(data) {
        t.ok(!data.errors, 'definecolor should be a known function');
        //
        // reset configuration
        //
        mjAPI.config({extenstion: ''});
        mjAPI.start();
    });

});
