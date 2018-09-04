const mjpage = require("mathjax-node-page").mjpage;
const fs = require("fs");
const path = require("path");
function fromDir(startPath, filter) {
  // console.log('Starting from dir '+startPath+'/');
  if (!fs.existsSync(startPath)) {
    console.log("no dir ", startPath);
    return;
  }
  var files = fs.readdirSync(startPath);
  for (var i = 0; i < files.length; i++)
    if (files[i] != ".") {
      const filename = path.join(startPath, files[i]);
      var stat = fs.lstatSync(filename);
      if (stat.isDirectory()) {
        fromDir(filename, filter); //recurse
      } else if (filename.indexOf(filter) >= 0) {
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
              format: ["TeX"],
              Mathjax: {
                font: "STIX-Web",
                SVG: {
                  undefinedFamily: '"Arial Unicode MS", Arial, sans-serif'
                }
              }
            },
            { svg: true, ex: 8, cjkCharWidth: 18 },
            function(output) {
              // console.log(output); // resulting HTML string
              // console.log(filename)
              console.log("Finished rendering: ", filename);
              fs.writeFileSync(filename, output, "utf-8");
            }
          );
        } catch (e) {
          console.log(e);
        }
      }
    }
}
// fromDir('./site/math/mobius', '.html');
fromDir("./site/", ".html");
// console.log(typeof input.text)
// input = input.replace(/\<span class=\"MathJax\_Preview\"\>.+?\<\/span\>\<script type="math\/tex"\>/gi, `<script type="math/tex">`)
