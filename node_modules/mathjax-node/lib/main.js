/*********************************************************************
 *
 *  main.js
 *
 *  Implements an API to MathJax in Node.js so that MathJax can be
 *  used server-side to generate HTML+CSS, SVG, or MathML.
 *
 *  This API converts single math expressions while giving control
 *  over the input format, the SVG font caching, and a number of other
 *  features.
 *
 * ----------------------------------------------------------------------
 *
 *  Copyright (c) 2014--2016 The MathJax Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

var http = require('http');
var fs = require('fs');
var path = require('path');
var url = require('url');
var jsdom = require('jsdom');
var JSDOM = jsdom.JSDOM;
var isFullwidthCodePoint = require('is-fullwidth-code-point');

require('./patch/jsdom.js').patch(JSDOM);  //  Fix some bugs in jsdom

var displayMessages = false;      // don't log Message.Set() calls
var displayErrors = true;         // show error messages on the console
var undefinedChar = false;        // unknown characters are not saved in the error array
var extensions = '';              // no additional extensions used
var paths = {};                   // additional paths (for third party extensions)
var fontURL = '';  // location of web fonts for CHTML

var defaults = {
  ex: 6,                          // ex-size in pixels
  width: 100,                     // width of container (in ex) for linebreaking and tags
  useFontCache: true,             // use <defs> and <use> in svg output?
  useGlobalCache: false,          // use common <defs> for all equations?
  linebreaks: false,              // do linebreaking?
  equationNumbers: "none",        // or "AMS" or "all"
  cjkCharWidth: 13,               // width of CJK character

  math: "",                       // the math to typeset
  format: "TeX",                  // the input format (TeX, inline-TeX, AsciiMath, or MathML)
  xmlns: "mml",                   // the namespace to use for MathML

  html: false,                    // return HTML output?
  htmlNode: false,             // DOM element for HTML output?
  css: false,                     // return CSS for HTML output?
  mml: false,                     // return mml output?
  mmlNode: false,              // DOM element for MML output?
  svg: false,                     // return svg output?
  svgNode: false,              // DOM element for SVG output?
  speakText: true,               // add spoken annotations
  timeout: 10 * 1000,             // 10 second timeout before restarting MathJax
};

//
//  The MathJax server states
//
var STATE = {
  STOPPED: 1,          // no DOM or MathJax available
  STARTED: 2,          // DOM loaded, MathJax starting up
  READY:   3,          // MathJax initialized and ready to process math
  BUSY:    4,          // MathJax currently processing math
  RESTART: 5,          // start() called while MathJax is starting up
};

//
// The MathJaxPath is normaized against file:/// so that Windows paths are correct
//
var MathJaxPath = url.resolve("file:///","file:"+require.resolve('mathjax'));
var MathJaxConfig;                   // configuration for when starting MathJax
var MathJax;                         // filled in once MathJax is loaded
var serverState = STATE.STOPPED;     // nothing loaded yet
var timer;                           // used to reset MathJax if it runs too long

var document, window, content, html; // the DOM elements

var queue = [];       // queue of typesetting requests of the form [data,callback]
var data, callback, originalData;   // the current queue item
var errors = [];      // errors collected durring the typesetting
var sErrors = [];     // errors collected durring MathJax startup
var ID = 0;           // id for this SVG element

//
//  The delimiters used for each of the input formats
//
var TYPES = {
  TeX: "tex; mode=display",
  "inline-TeX": "tex",
  AsciiMath: "asciimath",
  MathML: "mml"
};

var CHTMLSTYLES;         // filled in when CommonHTML is loaded

/********************************************************************/

//
//  Create the DOM window and set up the console wtihin it
//  Add an error handler to trap unexpected errors (requires
//    modifying jsdom)
//  Add a <div> where we can put the math to be typeset
//    and typeset math in the three formats we use (to force
//    the jax to be loaded completely)
//
function GetWindow() {
  var virtualConsole = new jsdom.VirtualConsole();
  virtualConsole.sendTo(console);
  window = new JSDOM('',{
    virtualConsole: virtualConsole,
    userAgent: "Node.js",
    runScripts: "dangerously",
    resources: "usable"
  }).window;
  document = window.document;
  html = document.firstChild;
  window.addEventListener("error",function (event) {AddError("Error: "+event.error.stack)});
  content = document.body.appendChild(document.createElement("div"));
  content.id = "MathJax_Content";
  content.innerHTML = '<script type="math/tex">x</script>' +
                      '<script type="math/asciimath">x</script>' +
                      '<script type="math/mml"><math><mi>x</mi></math></script>';
}

//
//  Set up a Mathjax configuration within the window
//
function ConfigureMathJax() {
  window.MathJax = {
    //
    //  Load all input jax and preprocessors
    //  Load AMS extensions and the autoload extension for TeX
    //  Create stand-alone SVG elements with font caches by default
    //    (users can override that)
    //
    jax: ["input/TeX", "input/MathML", "input/AsciiMath", "output/SVG", "output/CommonHTML"],
    extensions: ["toMathML.js"],
    TeX: {extensions: window.Array("AMSmath.js","AMSsymbols.js","autoload-all.js")},
    SVG: {useFontCache: true, useGlobalCache: false, EqnChunk: 1000000, EqnDelay: 0},
    CommonHTML: {EqnChunk: 1000000, EqnDelay: 0, undefinedFamily:"monospace"},

    //
    //  This gets run before MathJax queues any actions
    //
    AuthorInit: function () {
      MathJax = window.MathJax;

      // Add custom paths to configuration
      for (let key in paths) {
        MathJax.Ajax.config.path[key] = paths[key];
      }

      delete MathJax.Hub.config.styles;               // don't need any styles
      MathJax.Hub.Startup.MenuZoom = function () {};  // don't load menu or zoom code
      MathJax.Extension.MathEvents = {
        Event:{}, Touch:{}, Hover:{}                  // fake structure to avid errors
      };
      MathJax.Ajax.loaded[MathJax.Ajax.fileURL("[MathJax]/extensions/MathEvents.js")] = true;

      //
      //  When creating stylesheets, no need to wait for them
      //  to become active, so just do the callback
      //
      MathJax.Ajax.timer.create = function (callback,node) {
        callback = MathJax.Callback(callback);
        callback(this.STATUS.OK);
        return callback;
      };

      //
      //  Use the console for messages, if we are requesting them
      //
      MathJax.Message.Set = function (text,n,delay) {
        if (displayMessages && n !== 0) {
          if (text instanceof window.Array)
            {text = MathJax.Localization._.apply(MathJax.Localization,text)}
          console.error(text);
        }
      };
      MathJax.Message.Clear = function () {};
      MathJax.Message.Remove = function () {};
      MathJax.Message.Init = function () {};

      //
      //  Trap Math Processing Errors
      //
      MathJax.Hub.Register.MessageHook("Math Processing Error",function (message) {
        AddError("Math Processing Error: "+message[2].message);
      });
      MathJax.Hub.Register.MessageHook("SVG Jax - unknown char",function (message) {
        AddError("SVG - Unknown character: U+"+message[1].toString(16).toUpperCase()+
                    " in "+(message[2].fonts||["unknown"]).join(","),!undefinedChar);
      });
      MathJax.Hub.Register.MessageHook("CommonHTML Jax - unknown char",function (message) {
        AddError("CHTML - Unknown character: U+"+message[1].toString(16).toUpperCase()+
                    " in "+(message[2].fonts||["unknown"]).join(","),!undefinedChar);
      });
      MathJax.Hub.Register.MessageHook("MathML Jax - unknown node type",function (message) {
        AddError("MathML - Unknown node type: "+message[1]);
      });
      MathJax.Hub.Register.MessageHook("MathML Jax - parse error",function (message) {
        AddError("MathML - "+message[1]);
      });
      MathJax.Hub.Register.MessageHook("AsciiMath Jax - parse error",function (message) {
        AddError("AsciiMath parse error: "+message[1]);
      });
      MathJax.Hub.Register.MessageHook("TeX Jax - parse error",function (message) {
        AddError("TeX parse error: "+message[1]);
      });
      MathJax.Hub.Register.MessageHook("file load error",function (message) {
        AddError("File load error: "+message[1]);
      });

      //
      //  Set the delays to 0 (we don't need to update the screen)
      //
      MathJax.Hub.processSectionDelay = 0;
      MathJax.Hub.processUpdateTime = 10000000;  // don't interrupt processing of output
      MathJax.Hub.processUpdateDelay = 0;

      //
      //  Adjust the SVG output jax
      //
      MathJax.Hub.Register.StartupHook("SVG Jax Config",function () {
        var SVG = MathJax.OutputJax.SVG, HTML = MathJax.HTML;

        //
        //  Don't need the styles
        //
        delete SVG.config.styles

        SVG.Augment({
          //
          //  Set up the default ex-size and width
          //
          InitializeSVG: function () {
            this.pxPerInch    = 96;
            this.defaultEx    = 6;
            this.defaultWidth = 100;
          },
          //
          //  Adjust preTranslate() to not try to find the ex-size or
          //  the container widths.
          //
          preTranslate: function (state) {
            var scripts = state.jax[this.id], i, m = scripts.length,
                script, prev, span, div, jax, ex, em,
                maxwidth = 100000, relwidth = false, cwidth,
                linebreak = this.config.linebreaks.automatic,
                width = this.config.linebreaks.width;
            //
            //  Loop through the scripts
            //
            for (i = 0; i < m; i++) {
              script = scripts[i]; if (!script.parentNode) continue;
              //
              //  Remove any existing output
              //
              prev = script.previousSibling;
              if (prev && String(prev.className).match(/^MathJax(_SVG)?(_Display)?( MathJax(_SVG)?_Processing)?$/))
                {prev.parentNode.removeChild(prev)}
              //
              //  Add the span, and a div if in display mode,
              //  then mark it as being processed
              //
              jax = script.MathJax.elementJax; if (!jax) continue;
              jax.SVG = {display: (jax.root.Get("display") === "block")}
              span = div = HTML.Element("span",{
                style: {"font-size": this.config.scale+"%", display:"inline-block"},
                className:"MathJax_SVG", id:jax.inputID+"-Frame", isMathJax:true, jaxID:this.id
              });
              if (jax.SVG.display) {
                div = HTML.Element("div",{className:"MathJax_SVG_Display"});
                div.appendChild(span);
              }
              div.className += " MathJax_SVG_Processing";
              script.parentNode.insertBefore(div,script);
              //
              //  Set SVG data for jax
              //
              jax.SVG.ex = ex = (data||defaults).ex;
              jax.SVG.em = em = ex / SVG.TeX.x_height * 1000; // scale ex to x_height
              jax.SVG.cwidth = width / em * 1000;
              jax.SVG.lineWidth = (linebreak ? width / em * 1000 : SVG.BIGDIMEN);
            }
            //
            //  Set state variables used for displaying equations in chunks
            //
            state.SVGeqn = state.SVGlast = 0; state.SVGi = -1;
            state.SVGchunk = this.config.EqnChunk;
            state.SVGdelay = false;
          }
        });

        //
        //  TEXT boxes use getBBox, which isn't implemented, so
        //  use a monspace font and fake the size.  Since these
        //  are used only for error messages and undefined characters,
        //  this should be good enough for now.
        //
        SVG.BBOX.TEXT.Augment({
          Init: function (scale,text,def) {
            if (!def) {def = {}}; def.stroke = "none";
            if (def["font-style"] === "") delete def["font-style"];
            if (def["font-weight"] === "") delete def["font-weight"];
            this.SUPER(arguments).Init.call(this,def);
            SVG.addText(this.element,text);
            // tweaking font fallback behavior: https://github.com/mathjax/MathJax-node/issues/299
            var textWidth = text.split('')
              .map(function(c) { return isFullwidthCodePoint(c.codePointAt()) ? data.cjkCharWidth : 8.5 })
              .reduce(function(a, b) { return a + b }, 0);
            var bbox = {width: textWidth, height: 18, y: -12};
            scale *= 1000/SVG.em;
            this.element.setAttribute("font-family","monospace");
            this.element.setAttribute("transform","scale("+scale+") matrix(1 0 0 -1 0 0)");
            this.w = this.r = bbox.width*scale; this.l = 0;
            this.h = this.H = -bbox.y*scale;
            this.d = this.D = (bbox.height + bbox.y)*scale;
          }
        });

        //
        //  Don't have mglyph load images
        //
        MathJax.Hub.Register.StartupHook("SVG mglyph Ready",function () {
          var MML = MathJax.ElementJax.mml;
          var MGLYPH = MML.mglyph;
          var TOSVG = MGLYPH.prototype.toSVG;
          MGLYPH.Augment({
            toSVG: function (variant,scale) {
              var values = this.getValues("src","width","height");
              if (values.src !== "" && !MGLYPH.GLYPH[values.src]) {
                if (!values.width || !values.height) {
                  AddError("mglyphs must have explicit width and height in mathjax-node");
                }
                MGLYPH.GLYPH[values.src] = {
                  img: {SRC: values.src, width: 0, height: 0},
                  status: "OK"
                };
              }
              return TOSVG.apply(this,arguments);
            }
          });
        });

      });

      //
      //  Adjust the CommonHTML output jax
      //
      MathJax.Hub.Register.StartupHook("CommonHTML Jax Config",function () {
        var CHTML = MathJax.OutputJax.CommonHTML, HTML = MathJax.HTML;

        //
        //  Don't need these styles
        //
        var STYLES = CHTML.config.styles;
        delete STYLES["#MathJax_CHTML_Tooltip"];
        delete STYLES[".MJXc-processing"];
        delete STYLES[".MJXc-processed"];
        delete STYLES[".mjx-chartest"];
        delete STYLES[".mjx-chartest .mjx-char"];
        delete STYLES[".mjx-chartest .mjx-box"];
        delete STYLES[".mjx-test"];
        delete STYLES[".mjx-ex-boxtest"];
        //  fontURL to current MathJax version
        if (!fontURL){
          fontURL = 'https://cdnjs.cloudflare.com/ajax/libs/mathjax/' + MathJax.version + '/fonts/HTML-CSS';
        }
        CHTML.Augment({
          webfontDir: fontURL,
          //
          //  Set up the default ex-size and width
          //
          getDefaultExEm: function () {
            var styles = document.head.getElementsByTagName("style");
            CHTMLSTYLES = styles[styles.length-1].innerHTML;
            this.pxPerInch    = 96;
            this.defaultEx    = 6;
            this.defaultEm    = 6 / CHTML.TEX.x_height * 1000;
            this.defaultWidth = 100;
          },
          //
          //  Adjust preTranslate() to not try to find the ex-size or
          //  the container widths.
          //
          preTranslate: function (state) {
            var scripts = state.jax[this.id], i, m = scripts.length,
                script, prev, node, jax, ex, em,
                maxwidth = 100000, relwidth = false, cwidth = 0,
                linebreak = this.config.linebreaks.automatic,
                width = this.config.linebreaks.width;
            //
            //  Loop through the scripts
            //
            for (i = 0; i < m; i++) {
              script = scripts[i]; if (!script.parentNode) continue;
              //
              //  Remove any existing output
              //
              prev = script.previousSibling;
              if (prev && prev.className && String(prev.className).substr(0,9) === "mjx-chtml")
                prev.parentNode.removeChild(prev);
              //
              //  Add the node for the math and mark it as being processed
              //
              jax = script.MathJax.elementJax; if (!jax) continue;
              jax.CHTML = {display: (jax.root.Get("display") === "block")}
              node = CHTML.Element("mjx-chtml",{
                id:jax.inputID+"-Frame", isMathJax:true, jaxID:this.id
              });
              if (jax.CHTML.display) {
                //
                // Zoom box requires an outer container to get the positioning right.
                //
                var NODE = CHTML.Element("mjx-chtml",{className:"MJXc-display",isMathJax:false});
                NODE.appendChild(node); node = NODE;
              }

              node.className += " MJXc-processing";
              script.parentNode.insertBefore(node,script);
              //
              //  Set CHTML data for jax
              //
              jax.CHTML.ex = ex = (data||defaults).ex;
              jax.CHTML.em = jax.CHTML.outerEm = em = ex / CHTML.TEX.x_height; // scale ex to x_height
              jax.CHTML.cwidth = width / em;
              jax.CHTML.lineWidth = (linebreak ? width / em : 1000000);
              jax.CHTML.scale = 1; jax.CHTML.fontsize = "100%";
            }
            //
            //  Set state variables used for displaying equations in chunks
            //
            state.CHTMLeqn = state.CHTMLlast = 0; state.CHTMLi = -1;
            state.CHTMLchunk = this.config.EqnChunk;
            state.CHTMLdelay = false;
          },

          //
          //  We are using a monospaced font, so fake the size
          //
          getHDW: function (c,name,styles) {
            return {h:.8, d:.2, w:c.length*.5};
          }

        });

        //
        //  Don't have mglyph load images
        //
        MathJax.Hub.Register.StartupHook("CommonHTML mglyph Ready",function () {
          var MML = MathJax.ElementJax.mml;
          var MGLYPH = MML.mglyph;
          var TOCHTML = MGLYPH.prototype.toCommonHTML;
          MGLYPH.Augment({
            toCommonHTML: function (node,options) {
              var values = this.getValues("src","width","height");
              if (values.src !== "" && !MGLYPH.GLYPH[values.src]) {
                if (!values.width || !values.height) {
                  AddError("mglyphs must have explicit width and height in mathjax-node");
                }
                MGLYPH.GLYPH[values.src] = {
                  img: {SRC: values.src, width: 0, height: 0},
                  status: "OK"
                };
              }
              return TOCHTML.apply(this,arguments);
            }
          });
        });

      });

      //
      //  Set up None output jax (for when only MathML output is needed)
      //
      MathJax.Hub.Register.StartupHook("End Jax", function () {
        MathJax.OutputJax.None = MathJax.OutputJax({
          id: "None",
          preTranslate: function () {},
          Translate: function () {},
          postTranslate: function () {}
        });
        MathJax.OutputJax.None.loadComplete("jax.js");
        MathJax.OutputJax.None.Register("jax/mml");
      });

      //
      //  Reset the color extension after `autoload-all`
      //
      if (MathJax.AuthorConfig.extensions.indexOf("TeX/color.js") == -1 && MathJax.AuthorConfig.extensions.indexOf("TeX/autoload-all.js") == -1) {
              MathJax.Hub.Register.StartupHook("TeX autoload-all Ready",function () {
                var macros = MathJax.InputJax.TeX.Definitions.macros;
                macros.color = "Color";
                delete macros.textcolor;
                delete macros.colorbox;
                delete macros.fcolorbox;
                delete macros.definecolor;
              });
            }

      //
      //  Start the typesetting queue when MathJax is ready
      //    (reseting the counters so that the initial math doesn't affect them)
      //
      MathJax.Hub.Register.StartupHook("End",function () {
        if (MathJax.OutputJax.SVG.resetGlyphs) MathJax.OutputJax.SVG.resetGlyphs(true);
        MathJax.ElementJax.mml.ID = 0;
        if (serverState === STATE.RESTART) {
          setTimeout(RestartMathJax, 100);
        } else {
          serverState = STATE.READY;
          MathJax.Hub.Queue(
            function () {sErrors = errors},
            StartQueue
          );
        }
      });
    }
  };

  if (extensions) {
    //
    // Parse added extensions list and add to standard ones
    //
    var extensionList = extensions.split(/\s*,\s*/);
    for (var i = 0; i < extensionList.length; i++) {
      var matches = extensionList[i].match(/^(.*?)(\.js)?$/);
      window.MathJax.extensions.push(matches[1] + '.js');
    }
  }

  //
  //  Turn arrays into jsdom window arrays
  //  (so "instanceof Array" will identify them properly)
  //
  var adjustArrays = function (obj) {
    for (var id in obj) {if (obj.hasOwnProperty(id)) {
      if (obj[id] instanceof Array) {
        var A = window.Array();
        obj[id] = A.concat.apply(A,obj[id]);
      } else if (typeof obj[id] === "object") {
        adjustArrays(obj[id]);
      }
    }}
  }
  if (MathJaxConfig) {
    adjustArrays(MathJaxConfig);
    // merge the defaults into the user configuration (to sanitize)
    window.MathJax = Insert(Insert({},MathJaxConfig),window.MathJax);
    if (MathJaxConfig.extensions) {
      window.MathJax.extensions = window.MathJax.extensions.concat(MathJaxConfig.extensions);
    }
  }
}

//
//  Insert one objects into another
//
function Insert(dst,src) {
  for (var id in src) {if (src.hasOwnProperty(id)) {
    // allow for concatenation of arrays?
    if (typeof src[id] === 'object' && !(src[id] instanceof Array) &&
       (typeof dst[id] === 'object' || typeof dst[id] === 'function'))
         {Insert(dst[id],src[id])} else {dst[id] = src[id]}
  }}
  return dst;
}

//
//  Load MathJax into the DOM
//
function StartMathJax() {
  serverState = STATE.STARTED;
  var script = document.createElement("script");
  script.src = MathJaxPath;
  script.onerror = function () {AddError("Can't load MathJax.js from "+MathJaxPath)};
  document.head.appendChild(script);
}

/********************************************************************/

//
//  Return an error value (and report it to console)
//
function ReportError(message,currentCallback) {
  AddError(message);
  (currentCallback||callback)({errors: errors});
}

//
//  Add an error to the error list and display it on the console
//
function AddError(message,nopush) {
  if (displayErrors) console.error(message);
  if (!nopush) errors.push(message);
}


/********************************************************************/

//
//  Creates the MathML output (taking MathJax resets
//  into account)
//
function GetMML(result) {
  if (!data.mml && !data.mmlNode) return;
  var jax = MathJax.Hub.getAllJax()[0];
  if (data.speakText && !jax.root.alttext) {
    jax.root.alttext = result.speakText;
    var attrNames = jax.root.attrNames;
    if (attrNames && attrNames.indexOf("alttext") === -1) {
      attrNames.push("alttext");
    }
  }
  try {
    var mml = jax.root.toMathML('',jax);
  } catch(err) {
    if (!err.restart) {throw err;} // an actual error
    return MathJax.Callback.After(window.Array(GetMML,result),err.restart);
  }
  if (data.mml) result.mml = mml;
  if (data.mmlNode) result.mmlNode = JSDOM.fragment(mml).firstChild;
}

//
//  Creates speech string and updates the MathML to include it, if needed
//
function GetSpeech(result) {
  if (!data.speakText) return;
  result.speakText = "Equation";
  if (data.format !== "MathML") result.speakText = data.math;
  else {
    var jax = MathJax.Hub.getAllJax()[0];
    if (jax.root.alttext) result.speakText = jax.root.alttext;
  }
}

//
//  Create HTML and CSS output, if requested
//
function GetHTML(result) {
  if (data.css) result.css = CHTMLSTYLES;
  if (!data.html && !data.htmlNode) return;
  var jax = MathJax.Hub.getAllJax()[0]; if (!jax) return;
  var script = jax.SourceElement(), html = script.previousSibling;

  // add speech text if there isn't one
  if (data.speakText){
    var labelTarget = html.querySelector('.mjx-math');
    for (child of labelTarget.childNodes) child.setAttribute("aria-hidden",true);
    if (!labelTarget.getAttribute("aria-label")){
    labelTarget.setAttribute("aria-label",result.speakText);
    }
  }
  // remove automatically generated IDs
  var ids = html.querySelectorAll('[id^="MJXc-Node-"]');
  for (var i = 0; i < ids.length; i++){
    ids[i].removeAttribute("id");
  }
  // remove extreneous frame element
  var frame = html.querySelector('[id^="MathJax-Element-"]');
  if (frame){
    // in display-mode, the frame is inside the display-style wrapper
    html.insertBefore(frame.firstChild, frame);
    html.removeChild(frame);
  }
  else{
    // otherwise (inline-mode) the frame is the root element
    html.removeAttribute("id");
  }
  if (data.html) result.html = html.outerHTML;
  if (data.htmlNode) result.htmlNode = html;
}

//
//  Create SVG output, if requested
//
function GetSVG(result) {
  if (!data.svg && !data.svgNode) return;
  var jax = MathJax.Hub.getAllJax()[0]; if (!jax) return;
  var script = jax.SourceElement(),
      svg = script.previousSibling.getElementsByTagName("svg")[0];
  svg.setAttribute("xmlns","http://www.w3.org/2000/svg");

  //
  //  Add the speech text and mark the SVG appropriately
  //
  if (data.speakText){
    for (var i=0, m=svg.childNodes.length; i < m; i++)
      svg.childNodes[i].setAttribute("aria-hidden",true);
    // Note: if aria-label exists, getSpeech preserved it in speakText
    // remove aria-label since labelled-by title is preferred
    svg.removeAttribute("aria-label");
    ID++; var id = "MathJax-SVG-"+ID+"-Title";
    svg.setAttribute("aria-labelledby",id);
    var node = MathJax.HTML.Element("title",{id:id},[result.speakText]);
    svg.insertBefore(node,svg.firstChild);
  }

  if (data.svg){
    //
    //  SVG data is modified to add linebreaks for readability,
    //  and to put back the xlink namespace that is removed in HTML5
    //
    var svgdata = svg.outerHTML.replace(/><([^/])/g,">\n<$1")
                               .replace(/(<\/[a-z]*>)(?=<\/)/g,"$1\n")
                               .replace(/(<(?:use|image) [^>]*)(href=)/g,' $1xlink:$2');

    //
    //  Add the requested data to the results
    //
    result.svg = svgdata;
  }
  if (data.svgNode) result.svgNode = svg;
  result.width = svg.getAttribute("width");
  result.height = svg.getAttribute("height");
  result.style =  svg.style.cssText;
}

/********************************************************************/

//
//  Start typesetting the queued expressions
//
function StartQueue() {
  data = callback = originalData = null;       //  clear existing equation, if any
  errors = sErrors; sErrors = [];              //  clear any errors
  if (!queue.length) return;    //  return if nothing to do

  serverState = STATE.BUSY;
  var result = {}, $$ = window.Array;

  //
  //  Get the math data and callback
  // and set the content with the proper script type
  //
  var item = queue.shift();
  data = item[0]; callback = item[1]; originalData = item[2];
  content.innerHTML = "";
  MathJax.HTML.addElement(content,"script",{type: "math/"+TYPES[data.format]},[data.math]);
  html.setAttribute("xmlns:"+data.xmlns,"http://www.w3.org/1998/Math/MathML");

  //
  //  Set the SVG and TeX parameters
  //  according to the requested data
  //
  var CHTML = MathJax.OutputJax.CommonHTML,
      SVG = MathJax.OutputJax.SVG,
      TEX = MathJax.InputJax.TeX,
      HUB = MathJax.Hub;

  SVG.defaultEx = CHTML.defaultEx = data.ex;
  SVG.defaultWidth = CHTMLdefaultWidth = data.width * data.ex;
  SVG.config.linebreaks.automatic = CHTML.config.linebreaks.automatic = data.linebreaks;
  SVG.config.linebreaks.width = CHTML.config.linebreaks.width = data.width * data.ex;
  SVG.config.useFontCache = data.useFontCache;
  SVG.config.useGlobalCache = data.useGlobalCache;
  TEX.config.equationNumbers.autoNumber = data.equationNumbers;

  //
  // Set the state from data.state or clear it
  //
  GetState(data.state);

  //
  // Get the renderer to use
  //
  var renderer = (
      (data.html || data.htmlNode || data.css) ? "CommonHTML" :
          (data.svg || data.svgNode) ? "SVG" : "None"
  );

  //
  //  Set up a timeout timer to restart MathJax if it runs too long,
  //  Then push the Typeset call, the MathML, speech, and SVG calls,
  //  and our TypesetDone routine
  //
  timer = setTimeout(RestartMathJax,data.timeout);
  HUB.Queue(
    $$(SetRenderer,renderer),
    $$("Process",HUB),
    $$(TypesetDone,result),
    $$(GetSpeech,result),
    $$(GetMML,result),
    $$(GetHTML,result),
    $$(RerenderSVG,result),
    $$(GetSVG,result),
    $$(ReturnResult,result)
  );
}

//
//  Update the MathJax values from the state,
//  or clear them if there is no state.
//
function GetState(state) {
  var SVG = MathJax.OutputJax.SVG,
      TEX = MathJax.InputJax.TeX,
      MML = MathJax.ElementJax.mml,
      AMS = MathJax.Extension["TeX/AMSmath"],
      HUB = MathJax.Hub, HTML = MathJax.HTML,
      GLYPH = (SVG.BBOX||{}).GLYPH;

  if (state && state.AMS) {
    AMS.startNumber = state.AMS.startNumber;
    AMS.labels = state.AMS.labels;
    AMS.IDs = state.AMS.IDs;
    MML.SUPER.ID = state.mmlID;
    GLYPH.glyphs = state.glyphs;
    GLYPH.defs = state.defs;
    GLYPH.n = state.n;
    ID = state.ID;
  } else {
    if (state) {state.AMS = {}}
    if (SVG.resetGlyphs) SVG.resetGlyphs(true);
    if (data.useGlobalCache) {
      state.glyphs = {};
      state.defs = HTML.Element("defs");
      state.n = 0;
    }
    if (TEX.resetEquationNumbers) TEX.resetEquationNumbers();
    MML.SUPER.ID = ID = 0;
    MathJax.OutputJax.CommonHTML.ID = 0;
  }
}

//
//  When the expression is typeset,
//    clear the timeout timer, if any,
//    and update the MathJax state,
//
function TypesetDone(result) {
  if (timer) {clearTimeout(timer); timer = null}
  html.removeAttribute("xmlns:"+data.xmlns);
}

//
//  Return the result object, and
//  do the next queued expression
//
function ReturnResult(result) {
  if (errors.length) {
    result.errors = errors;
  }
  var state = data.state;
  if (state) {
    var AMS = MathJax.Extension["TeX/AMSmath"];
    var GLYPH = (MathJax.OutputJax.SVG||{}).BBOX.GLYPH;
    state.AMS.startNumber = AMS.startNumber;
    state.AMS.labels = AMS.labels;
    state.AMS.IDs = AMS.IDs;
    state.mmlID = MathJax.ElementJax.mml.SUPER.ID;
    state.glyphs = GLYPH.glyphs;
    state.defs = GLYPH.defs;
    state.n = GLYPH.n;
    state.ID = ID;
  }
  serverState = STATE.READY;
  callback(result, originalData);
  if (serverState === STATE.READY) StartQueue();
}

//
//  Set the MathJax renderer
//
function SetRenderer(renderer) {
  return MathJax.Hub.setRenderer(renderer);
}

function RerenderSVG(result) {
  if ((data.html || data.htmlNode || data.css) && (data.svg || data.svgNode)) {
    timer = setTimeout(RestartMathJax,data.timeout);
    var queue = MathJax.Callback.Queue(), $$ = window.Array;
    return queue.Push(
      $$(SetRenderer,"SVG"),
      $$("Rerender",MathJax.Hub),
      $$(TypesetDone,result)
    );
  }
}


/********************************************************************/

//
//  If MathJax times out, discard the DOM
//  and load a new one (get a fresh MathJax)
//
function RestartMathJax() {
  if (timer) {
    MathJax.Hub.queue.queue = [];  // clear MathJax queue, so pending operations won't fire
    MathJax = timer = window = document = html = content = null;
    ReportError("Timeout waiting for MathJax:  restarting");
  }
  serverState = STATE.STOPPED;
  GetWindow();
  ConfigureMathJax();
  StartMathJax();
}

/********************************************************************/

//
//  The API call to typeset an equation
//
//     %%% cache results?
//     %%% check types and values of parameters
//

// callback API for compatibility with MathJax
var cbTypeset = function (data, callback) {
  if (!callback || typeof(callback) !== "function") {
    if (displayErrors) console.error("Missing callback");
    return;
  }
  var options = {};
  for (var id in defaults) {if (defaults.hasOwnProperty(id)) {
    options[id] = (data.hasOwnProperty(id) ? data[id]: defaults[id]);
  }}
  if (data.state) {options.state = data.state}
  if (!TYPES[options.format]) {ReportError("Unknown format: "+options.format,callback); return}
  queue.push([options,callback,Object.assign({},data)]);
  if (serverState == STATE.STOPPED) {RestartMathJax()}
  if (serverState == STATE.READY) StartQueue();
}

// main API, callback and promise compatible
exports.typeset = function (data, callback) {
    if (callback) cbTypeset(data, callback);
    else return new Promise(function (resolve, reject) {
        cbTypeset(data, function (output, input) {
            if (output.errors) reject(output.errors);
            else resolve(output, input);
        });
    });
};

//
//  Manually start MathJax (this is done automatically
//  when the first typeset() call is made), but delay
//  restart if we are already starting up (prevents
//  multiple calls to start() from causing confusion).
//
exports.start = function () {
  if (serverState === STATE.STARTED) {
    serverState = STATE.RESTART;
  } else if (serverState !== STATE.ABORT) {
    RestartMathJax();
  }
}

//
//  Configure MathJax and the API
//  You can pass additional configuration options to MathJax using the
//    MathJax property, and can set displayErrors and displayMessages
//    that control the display of error messages, and extensions to add
//    additional MathJax extensions to the base or to sub-categories.
//
//  E.g.
//     mjAPI.config({
//       MathJax: {SVG: {font: "STIX-Web"}},
//       displayErrors: false,
//       extensions: 'Safe,TeX/noUndefined'
//     });
//
exports.config = function (config) {
  if (config.displayMessages != null)    {displayMessages = config.displayMessages}
  if (config.displayErrors != null)      {displayErrors   = config.displayErrors}
  if (config.undefinedCharError != null) {undefinedChar   = config.undefinedCharError}
  if (config.extensions != null)         {extensions      = config.extensions}
  if (config.paths != null)              {paths           = config.paths}
  if (config.fontURL != null)            {fontURL         = config.fontURL}
  if (config.MathJax) {
    // strip MathJax config blocks to avoid errors
    if (config.MathJax.config) delete config.MathJax.config
    MathJaxConfig = config.MathJax
  }
}
