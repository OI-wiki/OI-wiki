var tape = require('tape');
var mjAPI = require('../lib/main.js');

tape('Catch errors during startup phase', function(t) {
  t.plan(1);
  mjAPI.config({
    extensions: 'blargh'
  });
  mjAPI.start();
  mjAPI.typeset(
    {
      math: 'x',
      format: 'TeX',
      mml: true
    },
    function(data) {
      t.ok(
        data.errors,
        'Error (loading non-existent extension) is caught in output'
      );
     // reset configuration
     mjAPI.config({
        extensions: ''
      });
      mjAPI.start();
    }
  );
});
