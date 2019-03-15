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
  if (textLength <= 0) cur.innerHTML = `<p>本页面还在建设中，欢迎参与完善！</p>`;
}

document.getElementsByTagName("html")[0].lang = "zh-Hans"; // change language to `zh-Hans` for Han.js.
