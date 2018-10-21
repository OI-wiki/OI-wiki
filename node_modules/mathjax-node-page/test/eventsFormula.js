/**
 * Created by Roman Spiridonov <romars@phystech.edu> on 8/24/2017.
 */
const tape = require('tape');
const fs = require('fs');
const mjpage = require('../lib/main.js').mjpage;

const input = '\\[\\LaTeX_1\\] $$\\LaTeX_2$$';

tape('Check events for formula conversions', function(t) {
    t.plan(2+7*4);
    let callCount = 0;
    let jobID;
    mjpage(input, {
        format: ["TeX"]
    }, {
        svg: true
    }, function(output) {
        t.equal(callCount, 4, '4 events emitted');
        t.ok(output.match(/<svg[\s\S]*?>/ig).length === 2, 'Output has two SVG formulas');
    })
    .on('beforeConversion', function(parsedFormula) {
        callCount++;
        jobID = parsedFormula.jobID;
        t.equal(parsedFormula.id, Math.floor(callCount / 2), 'id represents consecutive number of formula on the page');
        t.ok(parsedFormula.node.toString() === '[object HTMLScriptElement]' &&
          parsedFormula.node.innerHTML === parsedFormula.sourceFormula, 'DOM node is passed and is a script wrapper with source formula');
        t.equal(typeof parsedFormula.jobID, 'number', 'jobID exists and is a number');
        if(callCount % 2 === 0) {
            t.ok(parsedFormula.sourceFormula === '\\LaTeX_2', "source formula is correct");
        } else {
            t.ok(parsedFormula.sourceFormula === '\\LaTeX_1', "source formula is correct");
        }
        t.ok(parsedFormula.sourceFormat === 'TeX');
        t.equal(parsedFormula.outputFormula, null, 'output formula is null on beforeConversion');
        t.equal(parsedFormula.outputFormat, 'svg', 'output format is svg');
    })
    .on('afterConversion', function(parsedFormula) {
        callCount++;
        t.equal(parsedFormula.id, Math.floor((callCount - 1) / 2), 'id represents consecutive number of formula on the page');
        t.ok(parsedFormula.node.toString() === '[object HTMLSpanElement]' &&
          parsedFormula.node.children.length > 0, 'DOM node wrapper contains is not empty');
        t.equal(parsedFormula.jobID, jobID, 'jobID is the same');
        if(callCount === 2) {
            t.ok(parsedFormula.sourceFormula === '\\LaTeX_1', "source formula is correct");
        } else {  // callCount === 4
            t.ok(parsedFormula.sourceFormula === '\\LaTeX_2', "source formula is correct");
        }
        t.ok(parsedFormula.sourceFormat === 'TeX');
        t.ok(parsedFormula.outputFormula[parsedFormula.outputFormat].match(/<svg[\s\S]*?>/ig).length === 1,
          'output formula converted successfully');
        t.equal(parsedFormula.outputFormat, 'svg', 'output format is svg');
    });
});
