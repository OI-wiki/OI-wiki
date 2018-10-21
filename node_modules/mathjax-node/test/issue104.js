var tape = require('tape');
var mjAPI = require("../lib/main.js");
var JSDOM = require('jsdom').JSDOM;

tape('the SVG width should match the default', function(t) {
  t.plan(1);

  var tex = 'a \\\\ b';
  var expected = '100ex';

  mjAPI.typeset({
    math: tex,
    format: "TeX",
    svg: true
  }, function(data) {
    var window = new JSDOM(data.svg).window;
    var document = window.document;
    var element = window.document.getElementsByTagName("svg")[0];
    var width = element.getAttribute('width');
    t.equal(width, expected);
  });

});
