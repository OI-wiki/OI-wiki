const mjpage = require('./lib/main.js').mjpage;
mjpage('<script>console.log("error")</script>', {}, {}, function () {});
