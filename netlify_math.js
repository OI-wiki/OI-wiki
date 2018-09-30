const mjpage = require("mathjax-node-page").mjpage;
const fs = require("fs");
const path = require("path");
var async = require("async");

function fromDir(startPath, filter, callback) {
  // console.log('Starting from dir '+startPath+'/');
  if (!fs.existsSync(startPath)) {
    console.log("no dir ", startPath);
    return;
  }
  var files = fs.readdirSync(startPath);
  var arr = [];
  for (var i = 0; i < files.length; i++)
    if (files[i] != ".") {
      const filename = path.join(startPath, files[i]);
      var stat = fs.lstatSync(filename);
      if (stat.isDirectory()) {
        fromDir(filename, filter, function(res) {
          arr = arr.concat(res);
        }); //recurse
      } else if (filename.indexOf(filter) >= 0) {
        arr.push(filename);
        // console.log(filename);
      }
    }
  callback(arr);
}
// fromDir('./site/math/mobius', '.html');
// arr = [];
fromDir("./site/", ".html", function(res) {
  // console.log(arr);
  // console.log('??');
  async.each(
    res,
    function(filename, cb) {
      try {
        console.log("Starts rendering: ", filename);
        let input = fs.readFileSync(filename, "utf-8");
        mjpage(
          input
            .replace(
              /\<span class=\"MathJax\_Preview\"\>.+?\<\/span\>\<script type="math\/tex"\>/gi,
              `<script type="math/tex">`
            )
            .replace(
              /\<div class=\"MathJax_Preview\"\>[\s\S]*?\<\/div\>/gi,
              ""
            ),
          {
            format: ["TeX"]
          },
          { svg: true, ex: 8, cjkCharWidth: 18, linebreaks: true },
          function(output) {
            // console.log(output); // resulting HTML string
            // console.log(filename)
            console.log("Finished rendering: ", filename);
            fs.writeFileSync(filename, output, "utf-8");
          }
        );
        cb();
      } catch (e) {
        console.log(e);
        throw e;
      }
    },
    function(err) {
      if (err) {
        console.log("A file failed to process");
      } else {
        console.log("All files have been processed successfully");
      }
    }
  );
});

// console.log(typeof input.text)
// input = input.replace(/\<span class=\"MathJax\_Preview\"\>.+?\<\/span\>\<script type="math\/tex"\>/gi, `<script type="math/tex">`)
