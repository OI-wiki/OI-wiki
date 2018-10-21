# mathjax-node-page [![Build Status](https://travis-ci.org/pkra/mathjax-node-page.svg?branch=master)](https://travis-ci.org/pkra/mathjax-node-page)

[![Greenkeeper badge](https://badges.greenkeeper.io/pkra/mathjax-node-page.svg)](https://greenkeeper.io/)

This Node.js module builds on [mathjax-node](https://github.com/mathjax/mathjax-node) and provides processing of larger content fragments

## installation

Use

```
npm install mathjax-node-page
```

to install mathjax-node-page and its dependencies.

## Usage

mathjax-node-page exports `mjpage` which expects four parameters:

```javascript
mjpage(input, mjpageConfig, mjnodeConfig, callback)
```

Where `input` is a string with HTML, `pageConfig` specifies page-wide options, and `mjnodeConfig` expects mathjax-node configuration options.

The defaults for `pageConfig` are

```javascript
{
    format: ["MathML", "TeX", "AsciiMath"], // determines type of pre-processors to run
    output: '', // global override for output option; 'svg', 'html' or 'mml'
    tex: {}, // configuration options for tex pre-processor, cf. lib/tex.js
    ascii: {}, // configuration options for ascii pre-processor, cf. lib/ascii.js
    singleDollars: false, // allow single-dollar delimiter for inline TeX
    fragment: false, // return body.innerHTML instead of full document
    cssInline: true,  // determines whether inline css should be added
    jsdom: {... }, // jsdom-related options
    displayMessages: false, // determines whether Message.Set() calls are logged
    displayErrors: false, // determines whether error messages are shown on the console
    undefinedCharError: false, // determines whether unknown characters are saved in the error array
    extensions: '', // a convenience option to add MathJax extensions
    fontURL: 'https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.2/fonts/HTML-CSS', // for webfont urls in the CSS for HTML output
    MathJax: {} // options MathJax configuration, see https://docs.mathjax.org
}
```
and where `mjnodeConfig` represents mathjax-node configuration options, the defaults are.

```javascript
{
  ex: 6, // ex-size in pixels
  width: 100, // width of math container (in ex) for linebreaking and tags
  useFontCache: true, // use <defs> and <use> in svg output?
  useGlobalCache: false, // use common <defs> for all equations?
  state: mjstate, // track global state
  linebreaks: false, // do linebreaking?
  equationNumbers: "none", // or "AMS" or "all"
  math: "", // the math to typeset
  html: false, // generate HTML output?
  css: false, // generate CSS for HTML output?
  mml: false, // generate mml output?
  svg: false, // generate svg output?
  speakText: true, // add spoken annotations to output?
  timeout: 10 * 1000, // 10 second timeout before restarting MathJax
}
```

## Advanced usage
### mathjax-node customization
mathjax-node-page exports `init` function that allows you to pass in a custom `mathjax-node`  (for example, [mathjax-node-svg2png](https://github.com/pkra/mathjax-node-svg2png)).
```javascript
const mjnode = require('mathjax-node-svg2png');
mjpage.init(mjnode);
```

If your custom mathjax-node provides new output options, you can add them by calling `addOutput`. As a second parameter, you can pass custom output handler, which is a function that modifies a DOM element with the conversion result.  The default output handler behavior is to write contents to `wrapper.innerHTML`.
```javascript
mjpage.addOutput('png', (wrapper, data) => {
	wrapper.innerHTML = `<img src="${data}">`;
});
// ...now you can use standard mathjax-node-page API
```

Reset to default mathjax-node behavior by calling `init` with empty parameters. Ensure that all your current mathjax-node-page tasks have been completed before calling it.
```javascript
mjpage.init();  // reset back to default mathjax-node
```

### Events
`mjpage` runs jobs which inherit `EventEmitter` and provide the following event hooks.
Add the corresponding event handlers to manipulate the input/output and DOM before/after conversion.

All the event handlers are destroyed when job ends to prevent memory leaks.

#### Formula conversion events
* `beforeConversion` -> `handler(parsedFormula)`: runs before individual formula conversion started, but after initial DOM processing. All the formulas are wrapped in `<script type="...">` tags, where `@type` is one of the following:
```javascript
const scripts = document.querySelectorAll(`
    script[type="math/TeX"],
    script[type="math/inline-TeX"],
    script[type="math/AsciiMath"],
    script[type="math/MathML"],
    script[type="math/MathML-block"]`
);
```
* `afterConersion` -> `handler(parsedFormula)`: runs after individual formula conversion completed and DOM was changed. Formula DOM node is a `<span class="mjpage...">` wrapper whose contents are the conversion result.

All formula conversion events pass `ParsedFormula` instance to the event handler.

```javascript
{
    id, // index of formula on the page
    jobID, // mjpage job ID; formulas belonging to the same page run have the same jobID
    node, // DOM node with the formula (contents change before and after conversion)
    sourceFormula, // the source formula
    sourceFormat, // the source formula format (e.g. "inline-TeX")
    outputFormula, // the converted formula result from mathjax-node typeset function; use outputFormula[outputFormat] to get the resulting formula string
    outputFormat // the resulting formula format (e.g. "svg")
}
```

#### Page conversion events
* `beforeSerialiation` -> `handler(document, css`): runs when converted page DOM was prepared immediately before serialization. Use to manipulate resulting page DOM. The event handler receives `document` node (jsdom) and page `css`.

`mjpage` function callback receives result after the DOM serialization.

#### Example
```javascript
mjpage(input, {
    format: ["TeX"]
}, {
    svg: true
}, function(output) {
    // output is your final result
})
.on('afterConversion', function(parsedFormula) {
    // manipulate parsed result and DOM at your will
    // see description of parsedFormula object above
});
```



## CLI

mathjax-node-page installs a CLI tool. Run `mjpage` to print usage instructions.

### Example

```javascript
const mjpage = require('../lib/main.js').mjpage;
const fs = require('fs');
const input = fs.readFileSync('input.html');

mjpage(input, {format: ["TeX"]}, {svg: true}, function(output) {
    console.log(output); // resulting HTML string
});
```
