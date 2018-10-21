/* -*- Mode: Javascript; indent-tabs-mode:nil; js-indent-level: 2 -*- */
/* vim: set ts=2 et sw=2 tw=80: */

/*************************************************************
 *
 *  MathJax/extensions/asciimath2jax.js
 *  
 *  Implements the AsciiMath to Jax preprocessor that locates AsciiMath
 *  code within the text of a document and replaces it with SCRIPT tags for
 *  processing by MathJax.
 *
 *  Modified by David Lippman, based on tex2jax.js.
 *  Additional work by Davide P. Cervone.
 *  
 *  ---------------------------------------------------------------------
 *  
 *  Copyright (c) 2012-2018 The MathJax Consortium
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

MathJax.Extension.asciimath2jax = {
  version: "2.7.5",
  config: {
    delimiters: [['`','`']],   // The star/stop delimiter pairs for asciimath code

    skipTags: ["script","noscript","style","textarea","pre","code","annotation","annotation-xml"],
                               // The names of the tags whose contents will not be
                               // scanned for math delimiters

    ignoreClass: "asciimath2jax_ignore",   // the class name of elements whose contents should
                                           // NOT be processed by asciimath2jax.  Note that this
                                           // is a regular expression, so be sure to quote any
                                           // regexp special characters

    processClass: "asciimath2jax_process", // the class name of elements whose contents SHOULD
                                           // be processed when they appear inside ones that
                                           // are ignored.  Note that this is a regular expression,
                                           // so be sure to quote any regexp special characters

    preview: "AsciiMath"       // set to "none" to not insert MathJax_Preview spans
                               //   or set to an array specifying an HTML snippet
                               //   to use the same preview for every equation.

  },
  
  //
  //  Tags to ignore when searching for AsciiMath in the page
  //
  ignoreTags: {
    br: (MathJax.Hub.Browser.isMSIE && document.documentMode < 9 ? "\n" : " "),
    wbr: "",
    "#comment": ""
  },
  
  PreProcess: function (element) {
    if (!this.configured) {
      this.config = MathJax.Hub.CombineConfig("asciimath2jax",this.config);
      if (this.config.Augment) {MathJax.Hub.Insert(this,this.config.Augment)}
      this.configured = true;
    }
    if (typeof(element) === "string") {element = document.getElementById(element)}
    if (!element) {element = document.body}
    if (this.createPatterns()) {this.scanElement(element,element.nextSibling)}
  },
  
  createPatterns: function () {
    var starts = [], i, m, config = this.config; this.match = {};
    if (config.delimiters.length === 0) {return false}
    for (i = 0, m = config.delimiters.length; i < m; i++) {
      starts.push(this.patternQuote(config.delimiters[i][0]));
      this.match[config.delimiters[i][0]] = {
        mode: "",
        end: config.delimiters[i][1],
        pattern: this.endPattern(config.delimiters[i][1])
      };
    }
    this.start = new RegExp(starts.sort(this.sortLength).join("|"),"g");
    this.skipTags = new RegExp("^("+config.skipTags.join("|")+")$","i");
    var ignore = [];
    if (MathJax.Hub.config.preRemoveClass) {ignore.push(MathJax.Hub.config.preRemoveClass)}
    if (config.ignoreClass) {ignore.push(config.ignoreClass)}
    this.ignoreClass = (ignore.length ? new RegExp("(^| )("+ignore.join("|")+")( |$)") : /^$/);
    this.processClass = new RegExp("(^| )("+config.processClass+")( |$)");
    return true;
  },
  
  patternQuote: function (s) {return s.replace(/([\^$(){}+*?\-|\[\]\:\\])/g,'\\$1')},
  
  endPattern: function (end) {
    return new RegExp(this.patternQuote(end)+"|\\\\.","g");
  },
  
  sortLength: function (a,b) {
    if (a.length !== b.length) {return b.length - a.length}
    return (a == b ? 0 : (a < b ? -1 : 1));
  },
  
  scanElement: function (element,stop,ignore) {
    var cname, tname, ignoreChild, process;
    while (element && element != stop) {
      if (element.nodeName.toLowerCase() === '#text') {
        if (!ignore) {element = this.scanText(element)}
      } else {
        cname = (typeof(element.className) === "undefined" ? "" : element.className);
        tname = (typeof(element.tagName)   === "undefined" ? "" : element.tagName);
        if (typeof(cname) !== "string") {cname = String(cname)} // jsxgraph uses non-string class names!
        process = this.processClass.exec(cname);
        if (element.firstChild && !cname.match(/(^| )MathJax/) &&
            (process || !this.skipTags.exec(tname))) {
          ignoreChild = (ignore || this.ignoreClass.exec(cname)) && !process;
          this.scanElement(element.firstChild,stop,ignoreChild);
        }
      }
      if (element) {element = element.nextSibling}
    }
  },
  
  scanText: function (element) {
    if (element.nodeValue.replace(/\s+/,'') == '') {return element}
    var match, prev, pos = 0, rescan;
    this.search = {start: true};
    this.pattern = this.start;
    while (element) {
      rescan = null;
      this.pattern.lastIndex = pos || 0; pos = 0;
      while (element && element.nodeName.toLowerCase() === '#text' &&
            (match = this.pattern.exec(element.nodeValue))) {
        if (this.search.start) {element = this.startMatch(match,element)}
                          else {element = this.endMatch(match,element)}
      }
      if (this.search.matched) element = this.encloseMath(element);
        else if (!this.search.start) rescan = this.search;
      if (element) {
        do {prev = element; element = element.nextSibling}
          while (element && this.ignoreTags[element.nodeName.toLowerCase()] != null);
        if (!element || element.nodeName !== '#text') {
          if (!rescan) return prev;
          element = rescan.open;
          pos = rescan.opos + rescan.olen;
          this.search = {start: true};
          this.pattern = this.start;
        }
      }
    }
    return element;
  },
  
  startMatch: function (match,element) {
    var delim = this.match[match[0]];
    if (delim != null) {
      this.search = {
        end: delim.end, mode: delim.mode,
        open: element, olen: match[0].length,
        opos: this.pattern.lastIndex - match[0].length
      };
      this.switchPattern(delim.pattern);
    }
    return element;
  },
  
  endMatch: function (match,element) {
    if (match[0] == this.search.end) {
      this.search.close = element;
      this.search.cpos = this.pattern.lastIndex;
      this.search.clen = (this.search.isBeginEnd ? 0 : match[0].length);
      this.search.matched = true;
      element = this.encloseMath(element);
      this.switchPattern(this.start);
    }
    return element;
  },
  
  switchPattern: function (pattern) {
    pattern.lastIndex = this.pattern.lastIndex;
    this.pattern = pattern;
    this.search.start = (pattern === this.start);
  },
  
  encloseMath: function (element) {
    var search = this.search, close = search.close, CLOSE, math, next;
    if (search.cpos === close.length) {close = close.nextSibling}
       else {close = close.splitText(search.cpos)}
    if (!close) {CLOSE = close = MathJax.HTML.addText(search.close.parentNode,"")}
    search.close = close;
    math = (search.opos ? search.open.splitText(search.opos) : search.open);
    while ((next = math.nextSibling) && next !== close) {
      if (next.nodeValue !== null) {
        if (next.nodeName === "#comment") {
          math.nodeValue += next.nodeValue.replace(/^\[CDATA\[((.|\n|\r)*)\]\]$/,"$1");
        } else {
          math.nodeValue += math.nextSibling.nodeValue;
        }
      } else {
        var ignore = this.ignoreTags[next.nodeName.toLowerCase()];
        math.nodeValue += (ignore == null ? " " : ignore);
      }
      math.parentNode.removeChild(next);
    }
    var AM = math.nodeValue.substr(search.olen,math.nodeValue.length-search.olen-search.clen);
    math.parentNode.removeChild(math);
    if (this.config.preview !== "none") {this.createPreview(search.mode,AM)}
    math = this.createMathTag(search.mode,AM);
    this.search = {}; this.pattern.lastIndex = 0;
    if (CLOSE) {CLOSE.parentNode.removeChild(CLOSE)}
    return math;
  },
  
  insertNode: function (node) {
    var search = this.search;
    search.close.parentNode.insertBefore(node,search.close);
  },
  
  createPreview: function (mode,asciimath) {
    var previewClass = MathJax.Hub.config.preRemoveClass;
    var preview = this.config.preview;
    if (preview === "none") return;
    if ((this.search.close.previousSibling||{}).className === previewClass) return;
    if (preview === "AsciiMath") {preview = [this.filterPreview(asciimath)]}
    if (preview) {
      preview = MathJax.HTML.Element("span",{className:previewClass},preview);
      this.insertNode(preview);
    }
  },
  
  createMathTag: function (mode,asciimath) {
    var script = document.createElement("script");
    script.type = "math/asciimath" + mode;
    MathJax.HTML.setScript(script,asciimath);
    this.insertNode(script);
    return script;
  },
  
  filterPreview: function (asciimath) {return asciimath}
  
};

// We register the preprocessors with the following priorities:
// - mml2jax.js: 5
// - jsMath2jax.js: 8
// - asciimath2jax.js, tex2jax.js: 10 (default)
// See issues 18 and 484 and the other *2jax.js files.
MathJax.Hub.Register.PreProcessor(["PreProcess",MathJax.Extension.asciimath2jax]);
MathJax.Ajax.loadComplete("[MathJax]/extensions/asciimath2jax.js");
