# mathjax-node [![Build Status](https://travis-ci.org/mathjax/MathJax-node.svg?branch=develop)](https://travis-ci.org/mathjax/MathJax-node)

This repository contains a library that provides an API to call [MathJax](https://github.com/mathjax/mathjax) from Node.js programs. The API converts individual math expressions (in any of MathJax's input formats) into HTML (with CSS), SVG, or MathML code.

Use

```
npm install mathjax-node
```

to install mathjax-node and its dependencies.

**Note:**
The current version of mathjax-node requires Node.js v6 or later, and uses jsdom version 11.

## Getting started

mathjax-node provides a library, `./lib/main.js`. Below is a very minimal example for using it - the tests and the examples mentioned above provide more advanced examples.

```javascript
// a simple TeX-input example
var mjAPI = require("mathjax-node");
mjAPI.config({
  MathJax: {
    // traditional MathJax configuration
  }
});
mjAPI.start();

var yourMath = 'E = mc^2';

mjAPI.typeset({
  math: yourMath,
  format: "TeX", // or "inline-TeX", "MathML"
  mml:true,      // or svg:true, or html:true
}, function (data) {
  if (!data.errors) {console.log(data.mml)}
  // will produce:
  // <math xmlns="http://www.w3.org/1998/Math/MathML" display="block">
  //   <mi>E</mi>
  //   <mo>=</mo>
  //   <mi>m</mi>
  //   <msup>
  //     <mi>c</mi>
  //     <mn>2</mn>
  //   </msup>
  // </math>
});
```

## Documentation

mathjax-node exports three methods, `config`, `start`, `typeset`.

### `config(options)`

The `config` method is used to set _global_ configuration options. Its default options are

```javascript
{
  displayMessages: false,    // determines whether Message.Set() calls are logged
  displayErrors:   true,     // determines whether error messages are shown on the console
  undefinedCharError: false, // determines whether "unknown characters" (i.e., no glyph in the configured fonts) are saved in the error array
  extensions: '',            // a convenience option to add MathJax extensions
  fontURL: 'https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.2/fonts/HTML-CSS', // for webfont urls in the CSS for HTML output
  paths: {},                  // configures custom path variables (e.g., for third party extensions, cf. test/config-third-party-extensions.js)
  MathJax: { }               // standard MathJax configuration options, see https://docs.mathjax.org for more detail.
}
```

**Note.** Changes to these options require a restart of the API using the `start()` method (see below).

### `start()`

The `start` method start (and restarts) mathjax-node. This allows reconfiguration.

**Note.** This is done automatically when `typeset` is first called (see below).

### `typeset(options[, callback])`

The `typeset` method is the main method of mathjax-node. It expects a configuration object `options` and optionally a callback.

If no `callback` is passed, it will return a Promise.

Once called, `typeset` can be called repeatedly and will optionally store information across calls (see `state` below).

The following are the default input options.

```javascript
{
  ex: 6,                          // ex-size in pixels
  width: 100,                     // width of container (in ex) for linebreaking and tags
  useFontCache: true,             // use <defs> and <use> in svg output?
  useGlobalCache: false,          // use common <defs> for all equations?
  linebreaks: false,              // automatic linebreaking
  equationNumbers: "none",        // automatic equation numbering ("none", "AMS" or "all")
  cjkCharWidth: 13,               // width of CJK character

  math: "",                       // the math string to typeset
  format: "TeX",                  // the input format (TeX, inline-TeX, AsciiMath, or MathML)
  xmlns: "mml",                   // the namespace to use for MathML

  html: false,                    // generate HTML output
  htmlNode: false,                // generate HTML output as jsdom node
  css: false,                     // generate CSS for HTML output
  mml: false,                     // generate MathML output
  mmlNode: false,                 // generate MathML output as jsdom node
  svg: false,                     // generate SVG output
  svgNode: false,                 // generate SVG output as jsdom node

  speakText: true,                // add textual alternative (for TeX/asciimath the input string, for MathML a dummy string)

  state: {},                      // an object to store information from multiple calls (e.g., <defs> if useGlobalCache, counter for equation numbering if equationNumbers ar )
  timeout: 10 * 1000,             // 10 second timeout before restarting MathJax
}
```

### `Promise.resolve(result,options)` / `Promise.reject(errors)` / `callback(result, options)`

mathjax-node returns two objects to `Promise.resolve` or `callback`: a `result` object and the original input `options`.

The `result` object will contain (at most) the following structure:

```javascript
{
  errors:                     // an array of MathJax error messages if any errors occurred
  mml:                        // a string of MathML markup if requested
  mmlNode:                    // a jsdom node of MathML markup if requested
  html:                       // a string of HTML markup if requested
  htmlNode:                   // a jsdom node of HTML markup if requested
  css:                        // a string of CSS if HTML was requested
  svg:                        // a string of SVG markup if requested
  svgNode:                    // a jsdom node of SVG markup if requested
  style:                      // a string of CSS inline style if SVG requested
  height:                     // a string containing the height of the SVG output if SVG was requested
  width:                      // a string containing the width of the SVG output if SVG was requested
  speakText:                  // a string of speech text if requested

  state: {                    // the state object (if useGlobalCache or equationNumbers is set)
           glyphs:            // a collection of glyph data
           defs :             // a string containing SVG def elements
           AMS: {
                startNumber:  // the current starting equation number
                labels:       // the set of labels
                IDs:          // IDs used in previous equations
             }
         }
}
```

If the `errors` array is non-empty, the Promise will reject, and be passed the `errors` array.

The `options` contains the configuration object passed to `typeset`; this can be useful for passing other data along or for identifying which `typeset()` call is associated with this (`callback`) call (in case you use the same `callback` function for more than one `typeset()`).

## Change History

### Breaking Changes in v2.0:

mathjax-node v2.0 makes breaking changes as follows:

- [CHANGED] mathjax-node now requires version 6 of Node.js (the minimum used to be Node.js version 4).
- [CHANGED] mathjax-node now uses version 10 of jsdom.  Since the jsdom API changed from 9 to 10, that means if you used jsdom in your code that calls mathjax-node, you may need to update how you call jsdom.


### Breaking Changes in v1.0:

mathjax-node v1.0 makes breaking changes to the following features from the pre-releases.

- [CHANGED] `lib/mj-single.js` has been renamed to `lib/main.js` (and set as `main` in `package.json`, i.e., `require('mathjax-node')` will load it.
- [REMOVED] `lib/mj-page.js` (API for processing HTML-fragments) and related CLI tools
- [REMOVED] speech-rule-engine integration
- [REMOVED] PNG generation
- [REMOVED] CLI tools in `bin/`

These features can easily be recreated in separate modules for greater flexibility. For examples, see

- [mathjax-node-cli](https://github.com/mathjax/mathjax-node-cli/)
- [mathjax-node-page](https://github.com/pkra/mathjax-node-page/)
- [mathjax-node-sre](https://github.com/pkra/mathjax-node-sre)
- [mathjax-node-svg2png](https://github.com/pkra/mathjax-node-svg2png)

---

Be sure to also check out other [projects on NPM that depend on mathjax-node](https://www.npmjs.com/browse/depended/mathjax-node).

