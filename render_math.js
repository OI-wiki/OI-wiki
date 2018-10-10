const mjpage = require("mathjax-node-page").mjpage;
const fs = require("fs");

filename = process.argv[2];
try {
  console.log("Starts rendering: ", filename);
  let input = fs.readFileSync(filename, "utf-8");
  mjpage(
    input
      .replace(
        /\<span class=\"MathJax\_Preview\"\>.+?\<\/span\>\<script type="math\/tex"\>/gi,
        `<script type="math/tex">`
      )
      .replace(/\<div class=\"MathJax_Preview\"\>[\s\S]*?\<\/div\>/gi, ""),
    {
      format: ["TeX"]
    },
    { svg: true, ex: 8, cjkCharWidth: 18, linebreaks: true },
    function(output) {
      console.log("Finished rendering: ", filename);
      fs.writeFileSync(filename, output, "utf-8");
    }
  );
} catch (e) {
  console.log(e);
}
