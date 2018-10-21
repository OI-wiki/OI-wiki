const tape = require('tape');
const mjpage = require('../lib/main.js').mjpage;
const jsdom = require('jsdom');
const { JSDOM } = jsdom;

tape('Do not disrupt newcommands while handling forward-looking refs (issue 69)', function(t) {
    t.plan(1);
    // NOTE I couldn't come up with a more minimal example with the old bad sort
    const input = `
        \\[\\newcommand{\\cL}{\\mathcal{L}}\\]
        \\(\\cL_\\theta\\)
        \\(\\cL \\)
        \\(\\theta\\)
        \\(\\theta(\\cdot,\\cdot)\\)
        \\(\\theta(\\cdot,\\cdot)\\)
        \\(\\cL _\\theta\\)
        \\(\\cL _\\theta\\)
        \\(0\\)
        \\(\\varphi\\)
        \\(1\\)
        \\(\\psi\\)`;
    mjpage(input, {
        format: ['TeX'],
        displayErrors: true
    }, {
        svg: true
    }, function(output) {
        const document = new JSDOM(output).window.document;
        let expected = true;
        for (let node of document.querySelectorAll('.mjpage')){
            if (node.innerHTML === '') expected = false;
        }
        t.ok(expected, 'No error occurred');
    });
});
