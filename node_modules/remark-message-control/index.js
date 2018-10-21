'use strict';

var control = require('unified-message-control');
var marker = require('mdast-comment-marker');
var xtend = require('xtend');

module.exports = messageControl;

function messageControl(options) {
  var settings = options || {};

  return control(xtend(options, {
    marker: settings.marker || marker,
    test: settings.test || 'html'
  }));
}
