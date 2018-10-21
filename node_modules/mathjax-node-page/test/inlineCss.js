/**
 * Created by Roman Spiridonov <romars@phystech.edu> on 8/25/2017.
 */
const tape = require('tape');
const mjpage = require('../lib/main.js').mjpage;

const input = '\\[\\LaTeX\\]';

tape('inlineCss config option', function(t) {
    t.plan(8);
    mjpage(input, {
        format: ["TeX"]
    }, {
        svg: true
    }, function(output) {
        t.ok(output.indexOf('<style') !== -1, 'inlineCss adds css for svg when true by default');
    });

    mjpage(input, {
        format: ["TeX"]
    }, {
        html: true
    }, function(output) {
        t.ok(output.indexOf('<style') !== -1, 'inlineCss adds css for html when true default');
    });

    mjpage(input, {
        format: ["TeX"]
    }, {
        mml: true
    }, function(output) {
        t.ok(output.indexOf('<style') === -1, 'inline css is not added for mathml');
    }).on('beforeSerialization', function(document, css) {
        t.equal(css, undefined, 'inline css is not added for mathml');
    });

    mjpage(input, {
        format: ["TeX"]
    }, {
        svg: true
    }, function(output) {
        t.ok(output.indexOf('<style') !== -1, 'inlineCss is false should not add inline css for svg');
    }).on('beforeSerialization', function(document, css) {
        t.ok(css, 'css is provided to beforeSerialization feedback for svg')
    });

    mjpage(input, {
        format: ["TeX"]
    }, {
        html: true
    }, function(output) {
        t.ok(output.indexOf('<style') !== -1, 'inlineCss is false should not add inline css for html');
    }).on('beforeSerialization', function(document, css) {
        t.ok(css, 'css is provided to beforeSerialization feedback for html')
    });
});
