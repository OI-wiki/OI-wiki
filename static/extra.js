window.addEventListener('load', function () {
  var p = localStorage.getItem("data-md-color-primary");
  if (p) {
    document.body.setAttribute('data-md-color-primary', p);
  }
  var a = localStorage.getItem('data-md-color-accent');
  if (a) {
    document.body.setAttribute('data-md-color-accent', a);
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

var url = document.URL.replace(/http\S+\.org\//gi, '').replace(/#\S+$/gi, '').slice(0, -1);
var script = document.createElement('script');
function foo(response) {
  var data = response.data;
  var num = response.data.length;
  if (data && data[0]) {
    var ti = new Date(data[0].commit.author.date).toLocaleString('zh-CN', { timeZone: "Asia/Shanghai", hour12: false });
  
    var author_list = [];
    for (var i = 0; i < num; ++i) {
      author_list.push(data[i].author.login);
    }
    var cnts = author_list.reduce(function (obj, val) {
      obj[val] = (obj[val] || 0) + 1;
      return obj;
    }, {});
    //Use the keys of the object to get all the values of the array
    //and sort those keys by their counts
    var sorted = Object.keys(cnts).sort(function (a, b) {
      return cnts[b] - cnts[a];
    });
    var index = sorted.indexOf('24OI-bot');
    if (index > -1) {
      sorted.splice(index, 1);
    }
    sorted = sorted.map(function(x) {
      return `<a href=https://github.com/${x}>${x}</a>`
    })
    document.getElementsByClassName('facts_modified')[0].innerHTML = (ti);
    document.getElementsByClassName('page_contributors')[0].innerHTML = (sorted.join(', '));
  } else if (!url.endsWith('index')) {
    url += '/index';
    var script = document.createElement('script');
    document.getElementsByClassName('edit_history')[0].setAttribute('href', `https://github.com/24OI/OI-wiki/commits/master/docs/${url}.md`);
    script.src = `https://api.github.com/repos/24OI/OI-WIki/commits?path=docs/${url}.md&callback=foo`;
    document.getElementsByTagName('head')[0].appendChild(script);
  }
}

if (url == "") {
  // HomePage
  document.getElementsByClassName('edit_history')[0].setAttribute('href', `https://github.com/24OI/OI-wiki/commits/master/docs/index.md`);
  script.src = `https://api.github.com/repos/24OI/OI-WIki/commits?path=docs/index.md&callback=foo`;
  document.getElementsByTagName('head')[0].appendChild(script);
} else if (url != "404.htm") {
  document.getElementsByClassName('edit_history')[0].setAttribute('href', `https://github.com/24OI/OI-wiki/commits/master/docs/${url}.md`);
  script.src = `https://api.github.com/repos/24OI/OI-WIki/commits?path=docs/${url}.md&callback=foo`;
  document.getElementsByTagName('head')[0].appendChild(script);
} else {
  document.getElementsByClassName('edit_history')[0].setAttribute('href', `https://github.com/24OI/OI-wiki/commits/master`);
  document.getElementsByClassName('facts_modified')[0].innerHTML = ('最近没更新过这个页面');
  document.getElementsByClassName('page_contributors')[0].innerHTML = ('本页面是自动生成的');
  document.getElementsByClassName('page_edit_url')[0].setAttribute('href', `#`);
}
