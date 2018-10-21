var tape = require('tape');
var mjAPI = require("../lib/main.js");

tape('Output, HTML: linebreaks, manual', function(t) {
    t.plan(1);

    var tex = 'A \\\\ B';
    var expected = '<span class="mjx-chtml MJXc-display"><span class="mjx-math" style="width: 100%;" aria-label="A \\\\ B"><span class="mjx-mrow" style="width: 100%;" aria-hidden="true"><span class="mjx-stack" style="width: 100%; vertical-align: -1.2em;"><span class="mjx-block" style="text-align: center;"><span class="mjx-box"><span class="mjx-mi"><span class="mjx-char MJXc-TeX-math-I" style="padding-top: 0.519em; padding-bottom: 0.298em;">A</span></span></span></span><span class="mjx-block" style="text-align: center; padding-top: 0.467em;"><span class="mjx-box"><span class="mjx-mspace" style="width: 0px; height: 0px;"></span><span class="mjx-mi"><span class="mjx-char MJXc-TeX-math-I" style="padding-top: 0.446em; padding-bottom: 0.298em;">B</span></span></span></span></span></span></span></span>'

    mjAPI.typeset({
        math: tex,
        format: "TeX",
        html: true
    }, function(data) {
        t.equal(data.html, expected, 'HTML output as expected');
    });

});
