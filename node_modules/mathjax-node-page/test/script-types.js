const tape = require('tape');
const mjpage = require('../lib/main.js').mjpage;
const jsdom = require('jsdom');
const { JSDOM } = jsdom;

tape('Custom script types are processed correctly', function(t) {
    t.plan(4);
    const inlineInput = '<script type="math/tex"> e^{i\\pi} = -1</script>';
    mjpage(inlineInput, {
        format: ['TeX']
    }, {
        svg: true
    }, function(output) {
			const window = new JSDOM(output).window;
			const expected = window.document.querySelector('.mjpage');
      t.ok(expected, '"math/tex" treated as inline');
    });

    const displayInput = '<script type="math/tex; mode=display"> e^{i\\pi} = -1</script>';
    mjpage(displayInput, {
        format: ['TeX']
    }, {
        svg: true
    }, function(output) {
			const window = new JSDOM(output).window;
			const expected = window.document.querySelector('.mjpage__block');
      t.ok(expected, '"math/tex; mode=display" treated as block');
    });

    const asciiInput = '<script type="math/asciimath">alpha</script>';
    mjpage(displayInput, {
        format: ['TeX']
    }, {
        svg: true
    }, function(output) {
			const window = new JSDOM(output).window;
			const expected = window.document.querySelector('.mjpage');
      t.ok(expected, '"math/asciimath" treated as asciimath');
    });

    const crazyCaseInput = '<script type="math/blarg"> e^{i\\pi} = -1</script>';
    mjpage(crazyCaseInput, {
        format: ['TeX']
    }, {
        svg: true
    }, function(output) {
			const window = new JSDOM(output).window;
			const expected = window.document.querySelector('.mjpage');
      t.notOk(expected, 'Other scripts are ignored');
    });

});
