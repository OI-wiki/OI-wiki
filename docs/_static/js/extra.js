window.MathJax = {
  tex2jax: {
    inlineMath: [['$', '$'], ["\\(", "\\)"]],
    displayMath: [['$$', '$$'], ["\\[", "\\]"]],
    processEscapes: true,
    processEnvironments: true,
    ignoreClass: ".*|",
    processClass: "arithmatex"
  },
  TeX: {
    TagSide: "right",
    TagIndent: ".8em",
    MultLineWidth: "85%",
    equationNumbers: {
      autoNumber: "AMS",
    },
    unicode: {
      fonts: "STIXGeneral,'Arial Unicode MS'"
    }
  },
  showProcessingMessages: false,
  messageStyle: "none",
  jax: ["input/TeX","output/SVG"]
};
window.addEventListener('load', function() { 
    var p=localStorage.getItem("data-md-color-primary");
    if (p){
        document.body.setAttribute('data-md-color-primary',p);
    }
    var a=localStorage.getItem('data-md-color-accent');
    if (a){
        document.body.setAttribute('data-md-color-accent',a);
    }
}, false);

window.dataLayer = window.dataLayer || [];
function gtag(){dataLayer.push(arguments); }
gtag('js', new Date());  
gtag('config', 'UA-124485594-1');

var cur = document.getElementsByClassName('page-time')[0]
if (cur) {
  var comments = document.getElementById('gitment_container');
  var pos = 0;
  if (comments) {
    pos -= comments.textContent.length;
  }
  comments = document.getElementById('__comments');
  if (comments) {
    pos -= comments.textContent.length;
  }
  var textLength = 0;
  if (pos < 0) textLength = (document.getElementsByClassName('md-content__inner')[0].textContent.slice(0, pos).replace(/\s/g, '').length - document.getElementsByTagName('h1')[0].textContent.replace(/\s/g, '').length - document.getElementsByClassName('page-copyright')[0].textContent.replace(/\s/g, '').length - 4);
  else textLength = (document.getElementsByClassName('md-content__inner')[0].textContent.replace(/\s/g, '').length - document.getElementsByTagName('h1')[0].textContent.replace(/\s/g, '').length - document.getElementsByClassName('page-copyright')[0].textContent.replace(/\s/g, '').length - 4);
  var ti = Math.ceil(textLength / 400);
  cur.innerHTML = `<p>本页面共 ${textLength} 字，预计阅读需要 ${ti} 分钟</p>`;
}
