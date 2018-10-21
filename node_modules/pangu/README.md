# 為什麼你們就是不能加個空格呢？

[![](http://img.shields.io/travis/vinta/pangu.js.svg?style=flat-square)](https://travis-ci.org/vinta/pangu.js)
[![](https://img.shields.io/codecov/c/github/vinta/pangu.js/master.svg?style=flat-square)](https://codecov.io/github/vinta/pangu.js)
[![](https://img.shields.io/npm/v/pangu.svg?style=flat-square)](https://www.npmjs.com/package/pangu)
[![](https://img.shields.io/badge/made%20with-%e2%9d%a4-ff69b4.svg?style=flat-square)](https://vinta.ws)

如果你跟我一樣，每次看到網頁上的中文字和英文、數字、符號擠在一塊，就會坐立難安，忍不住想在它們之間加個空格。這個外掛（支援 Chrome 和 Firefox）正是你在網路世界走跳所需要的東西，它會自動替你在網頁中所有的中文字和半形的英文、數字、符號之間插入空白。

漢學家稱這個空白字元為「盤古之白」，因為它劈開了全形字和半形字之間的混沌。另有研究顯示，打字的時候不喜歡在中文和英文之間加空格的人，感情路都走得很辛苦，有七成的比例會在 34 歲的時候跟自己不愛的人結婚，而其餘三成的人最後只能把遺產留給自己的貓。畢竟愛情跟書寫都需要適時地留白。

與大家共勉之。

## Installation

### for Users

* [Google Chrome](https://chrome.google.com/webstore/detail/paphcfdffjnbcgkokihcdjliihicmbpd) (2016-06-26 updated)
* [Mozilla Firefox](https://github.com/vinta/pangu.js/raw/master/browser_extensions/firefox/paranoid-auto-spacing.user.js) (2015-05-13 updated)

### for Developers

* [pangu.clj](https://github.com/coldnew/pangu.clj) (Clojure)
* [pangu.ex](https://github.com/cataska/pangu.ex) (Elixir)
* [pangu.go](https://github.com/vinta/pangu) (Go)
* [pangu.java](https://github.com/vinta/pangu.java) (Java)
* [pangu.js](https://github.com/vinta/pangu.js) (JavaScript, both Node.js and Browser)
* [pangu.objective-c](https://github.com/Cee/pangu.objective-c) (Objective-C)
* [pangu.php](https://github.com/Kunr/pangu.php) (PHP)
* [pangu.py](https://github.com/vinta/pangu.py) (Python)
* [pangu.rb](https://github.com/dlackty/pangu.rb) (Ruby)
* [pangu.swift](https://github.com/X140Yu/pangu.Swift) (Swift)

## Usage

```bash
$ npm install pangu --save
```

### Browser

```html
<head>
  // Files are located on /node_modules/pangu/dist/browser/
  <script src="pangu.min.js"></script>
</head>
<script>
  var newText = pangu.spacing("Mr.龍島主道：「Let's Party!各位高明博雅君子！」");
  // output: "Mr. 龍島主道：「Let's Party! 各位高明博雅君子！」"

  pangu.spacingPage();
  pangu.spacingElementById('main');
  pangu.spacingElementByClassName('comment');
  pangu.spacingElementByTagName('p');
</script>
```

`pangu.js` is also available on [cdnjs](http://cdnjs.com/libraries/pangu):

```html
<script src="https://cdnjs.cloudflare.com/ajax/libs/pangu/3.3.0/pangu.js"></script>
<script src="https://cdnjs.cloudflare.com/ajax/libs/pangu/3.3.0/pangu.min.js"></script>
```

### Node.js

Learn more on [npm](https://www.npmjs.com/package/pangu).

```js
var pangu = require('pangu'); // ES5
import pangu from 'pangu'; // ES6

pangu.spacing('Sephiroth見他這等神情,也是悚然一驚:不知我這Ultimate Destructive Magic是否對付得了?');
// output: Sephiroth 見他這等神情, 也是悚然一驚: 不知我這 Ultimate Destructive Magic 是否對付得了?

pangu.spacingFile('/path/to/text.txt', function(err, data) {
  // callback
  console.log(data);
});

pangu.spacingFile('/path/to/text.txt').then(function(data) {
  // promise
  console.log(data);
});

const data = pangu.spacingFileSync('/path/to/text.txt');
```

## Testing

You need to install [Node.js](https://vinta.ws/code/install-node-js-via-nvm.html).

```bash
$ git clone git@github.com:vinta/pangu.js.git && cd pangu.js
$ npm install
$ npm run test
```

## License

Released under the [MIT License](http://opensource.org/licenses/MIT).

## Author

* GitHub: [@vinta](https://github.com/vinta)
* Twitter: [@vinta](https://twitter.com/vinta)
* Website: [vinta.ws](https://vinta.ws/)

## Related Projects

* Atom: [atom-pangu](https://github.com/7kfpun/atom-pangu)
* Command-line interface: [pangu-cli](https://github.com/SDLyu/pangu)
* Emacs: [pangu-spacing](http://coldnew.github.io/blog/2013/05/20_5cbb7.html)
* Gulp: [gulp-pangu](https://github.com/7kfpun/gulp-pangu)
* JavaScript: [为什么我就是能这样娴熟地加上空格呢？](https://github.com/Dustland/daft-auto-spacing)
* Node.js: [pangu.node](https://github.com/huei90/pangu.node)
* Ruby: [auto-correct](https://github.com/huacnlee/auto-correct)
* Vim: [pangu.vim](https://github.com/hotoo/pangu.vim)
* WordPress: [Space Lover](https://wordpress.org/plugins/space-lover/)
* 知乎: [Mountain Reviewer](http://zhuanlan.zhihu.com/pointless/19744560)
