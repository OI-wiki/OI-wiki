var tape = require('tape');
var mjAPI = require('../lib/main.js');

tape('Options "extension": multiple extensions', function(t) {
  t.plan(1);
  mjAPI.config({
    extensions: 'TeX/autoload-all.js, TeX/color.js'
  });
  mjAPI.typeset(
    {
      math: 'E = mc^2',
      format: 'TeX',
      mml: true
    },
    function(data) {
      t.notOk(
        data.errors,
        'Config block with multiple extensions throws no error'
      );
    }
  );
});
