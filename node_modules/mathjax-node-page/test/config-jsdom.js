const tape = require('tape');
const mjpage = require('../lib/main.js').mjpage;
const exec = require('child_process').exec;

tape('Configuration options for jsdom', function (t) {
    t.plan(4);
    const input = `
        <p>Hello World</p>
        <script> window.onload = function(){ var f = document.createElement('footer'); document.body.appendChild(f);}</script>`;
    mjpage(input, {}, {},
        function (output) {
            t.notOk(output.includes('<footer></footer>'), 'jsdom configuration defaults');
        });
    mjpage(input, {
            jsdom: {
                runScripts: 'dangerously',
                virtualConsole: true
            }
        }, {},
        function (output) {
            t.ok(output.includes('<footer></footer>'), 'jsdom with script execution');
        });
    exec(`cat test/data/config-jsdom-input1.js | node`,
        function (error, stdout, stderr) {
            if (stderr) throw stderr;
            t.equal(stdout, '', 'jsdom: virtual console default off');
        });
    exec(`cat test/data/config-jsdom-input2.js | node`,
        function (error, stdout, stderr) {
            if (stderr) throw stderr;
            t.equal(stdout, 'error\n', 'jsdom: virtual console on');
        });
});
