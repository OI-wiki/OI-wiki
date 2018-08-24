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
  messageStyle: "none"
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

var textLength = (document.getElementsByClassName('md-content__inner')[0].textContent.slice(0, -document.getElementById('gitment_container').textContent.length - document.getElementById('__comments').textContent.length).replace(/\s/g, '').length);
var ti = Math.round(textLength / 400);
var cur = document.getElementsByClassName('page-time')[0]
cur.innerHTML = `<p>本页面共 ${textLength} 字，预计阅读需要 ${ti} 分钟</p>`;