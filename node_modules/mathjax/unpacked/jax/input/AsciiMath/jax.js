/* -*- Mode: Javascript; indent-tabs-mode:nil; js-indent-level: 2 -*- */
/* vim: set ts=2 et sw=2 tw=80: */

/*************************************************************
 *
 *  MathJax/jax/input/AsciiMath/jax.js
 *  
 *  An Input Jax for AsciiMath notation 
 *  (see http://www1.chapman.edu/~jipsen/mathml/asciimath.html).
 *  
 *  Originally adapted for MathJax by David Lippman.
 *  Additional work done by Davide P. Cervone.
 *  
 *  The current development repository for AsciiMathML is
 *      https://github.com/mathjax/asciimathml
 *  
 *  A portion of this file is taken from
 *  ASCIIMathML.js Version 2.2 Mar 3, 2014, (c) Peter Jipsen http://www.chapman.edu/~jipsen
 *  and is used by permission of Peter Jipsen, who has agreed to allow us to
 *  release it under the Apache2 license (see below).  That portion is indicated
 *  via comments.
 *  
 *  The remainder falls under the copyright that follows.
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

(function (ASCIIMATH) {

  var MML;  // Filled in later

  //
  //  Make a documentFragment work-alike that uses MML objects
  //  rather than DOM objects.
  //
  var DOCFRAG = MathJax.Object.Subclass({
    firstChild: null,
    lastChild: null,
    Init: function () {
      this.childNodes = [];
    },
    appendChild: function (node) {
      if (node.parent) {node.parent.removeChild(node)}
      if (this.lastChild) {this.lastChild.nextSibling = node}
      if (!this.firstChild) {this.firstChild = node}
      this.childNodes.push(node); node.parent = this;
      this.lastChild = node;
      return node;
    },
    removeChild: function (node) {
      for (var i = 0, m = this.childNodes.length; i < m; i++)
        {if (this.childNodes[i] === node) break}
      if (i === m) return;
      this.childNodes.splice(i,1);
      if (node === this.firstChild) {this.firstChild = node.nextSibling}
      if (node === this.lastChild) {
        if (!this.childNodes.length) {this.lastChild = null}
          else {this.lastChild = this.childNodes[this.childNodes.length-1]}
      }
      if (i) {this.childNodes[i-1].nextSibling = node.nextSibling}
      node.nextSibling = node.parent = null;
      return node;
    },
    replaceChild: function (node,old) {
      for (var i = 0, m = this.childNodes.length; i < m; i++)
        {if (this.childNodes[i] === old) break}
      if (i) {this.childNodes[i-1].nextSibling = node} else {this.firstChild = node}
      if (i >= m-1) {this.lastChild = node}
      this.childNodes[i] = node; node.nextSibling = old.nextSibling;
      old.nextSibling = old.parent = null;
      return old;
    },
    hasChildNodes: function (node) {
      return (this.childNodes.length>0);	    
    },
    toString: function () {return "{"+this.childNodes.join("")+"}"}
  });
  
  var INITASCIIMATH = function () {
    MML = MathJax.ElementJax.mml;
    var MBASEINIT = MML.mbase.prototype.Init;
    
    //
    //  Make MML elements looks like DOM elements (add the
    //  methods that AsciiMath needs)
    //
    MML.mbase.Augment({
      firstChild: null,
      lastChild: null,
      nodeValue: null,
      nextSibling: null,
      Init: function () {
        var obj = MBASEINIT.apply(this,arguments) || this;
        obj.childNodes = obj.data;
        obj.nodeName = obj.type;
        return obj;
      },
      appendChild: function (node) {
        if (node.parent) {node.parent.removeChild(node)}
        var nodes = arguments;
        if (node.isa(DOCFRAG)) {
          nodes = node.childNodes;
          node.data = node.childNodes = [];
          node.firstChild = node.lastChild = null;
        }
        for (var i = 0, m = nodes.length; i < m; i++) {
          node = nodes[i];
          if (this.lastChild) {this.lastChild.nextSibling = node}
          if (!this.firstChild) {this.firstChild = node}
          this.Append(node);
          this.lastChild = node;
        }
        return node;
      },
      removeChild: function (node) {
        for (var i = 0, m = this.childNodes.length; i < m; i++)
          {if (this.childNodes[i] === node) break}
        if (i === m) return;
        this.childNodes.splice(i,1);
        if (node === this.firstChild) {this.firstChild = node.nextSibling}
        if (node === this.lastChild) {
          if (!this.childNodes.length) {this.lastChild = null}
            else {this.lastChild = this.childNodes[this.childNodes.length-1]}
        }
        if (i) {this.childNodes[i-1].nextSibling = node.nextSibling}
        node.nextSibling = node.parent = null;
        return node;
      },
      replaceChild: function (node,old) {
        for (var i = 0, m = this.childNodes.length; i < m; i++)
          {if (this.childNodes[i] === old) break}
        // FIXME:  make this work with DOCFRAG's?
        if (i) {this.childNodes[i-1].nextSibling = node} else {this.firstChild = node}
        if (i >= m-1) {this.lastChild = node}
        this.SetData(i,node); node.nextSibling = old.nextSibling;
        old.nextSibling = old.parent = null;
        return old;
      },
      hasChildNodes: function (node) {
        return (this.childNodes.length>0);	    
      },
      setAttribute: function (name,value) {this[name] = value}
    });
  };
  
  //
  //  Set up to isolate ASCIIMathML.js
  //
  
  var window = {};  // hide the true window
  
  //
  //  Hide the true document, and add functions that
  //  use and produce MML objects instead of DOM objects
  //
  var document = {
    getElementById: true,
    createElementNS: function (ns,type) {
      var node = MML[type]();
      if (type === "mo" && ASCIIMATH.config.useMathMLspacing) {node.useMMLspacing = 0x80}
      return node;
    },
    createTextNode: function (text) {return MML.chars(text).With({nodeValue:text})},
    createDocumentFragment: function () {return DOCFRAG()}
  };
  
  var navigator = {appName: "MathJax"};  // hide the true navigator object
  
/******************************************************************
 *
 *   The following section is ASCIIMathML.js Version 2.2
 *   (c) Peter Jipsen, used with permission.
 *   
 *   Some sections are commented out to save space in the
 *   minified version (but that is not strictly necessary).
 *   
 ******************************************************************/

/*
ASCIIMathML.js
==============
This file contains JavaScript functions to convert ASCII math notation
and (some) LaTeX to Presentation MathML. The conversion is done while the 
HTML page loads, and should work with Firefox and other browsers that can
render MathML.

Just add the next line to your HTML page with this file in the same folder:

<script type="text/javascript" src="ASCIIMathML.js"></script>

Version 2.2 Mar 3, 2014.
Latest version at https://github.com/mathjax/asciimathml
If you use it on a webpage, please send the URL to jipsen@chapman.edu

Copyright (c) 2014 Peter Jipsen and other ASCIIMathML.js contributors

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
//var asciimath = {};

//(function(){
var mathcolor = "blue";        // change it to "" (to inherit) or another color
//var mathfontsize = "1em";      // change to e.g. 1.2em for larger math
//var mathfontfamily = "serif";  // change to "" to inherit (works in IE) 
                               // or another family (e.g. "arial")
//var automathrecognize = false; // writing "amath" on page makes this true
//var checkForMathML = true;     // check if browser can display MathML
//var notifyIfNoMathML = true;   // display note at top if no MathML capability
//var alertIfNoMathML = false;   // show alert box if no MathML capability
//var translateOnLoad = true;    // set to false to do call translators from js 
//var translateASCIIMath = true; // false to preserve `..`
var displaystyle = true;      // puts limits above and below large operators
var showasciiformulaonhover = true; // helps students learn ASCIIMath
var decimalsign = ".";        // change to "," if you like, beware of `(1,2)`!
//var AMdelimiter1 = "`", AMescape1 = "\\\\`"; // can use other characters
//var AMdocumentId = "wikitext" // PmWiki element containing math (default=body)
var fixphi = true;  		//false to return to legacy phi/varphi mapping

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

var isIE = (navigator.appName.slice(0,9)=="Microsoft");
/*
var noMathML = false, translated = false;

if (isIE) { // add MathPlayer info to IE webpages
  document.write("<object id=\"mathplayer\"\
  classid=\"clsid:32F66A20-7614-11D4-BD11-00104BD3F987\"></object>");
  document.write("<?import namespace=\"m\" implementation=\"#mathplayer\"?>");
}

// Add a stylesheet, replacing any previous custom stylesheet (adapted from TW)
function setStylesheet(s) {
	var id = "AMMLcustomStyleSheet";
	var n = document.getElementById(id);
	if(document.createStyleSheet) {
		// Test for IE's non-standard createStyleSheet method
		if(n)
			n.parentNode.removeChild(n);
		// This failed without the &nbsp;
		document.getElementsByTagName("head")[0].insertAdjacentHTML("beforeEnd","&nbsp;<style id='" + id + "'>" + s + "</style>");
	} else {
		if(n) {
			n.replaceChild(document.createTextNode(s),n.firstChild);
		} else {
			n = document.createElement("style");
			n.type = "text/css";
			n.id = id;
			n.appendChild(document.createTextNode(s));
			document.getElementsByTagName("head")[0].appendChild(n);
		}
	}
}

setStylesheet("#AMMLcloseDiv \{font-size:0.8em; padding-top:1em; color:#014\}\n#AMMLwarningBox \{position:absolute; width:100%; top:0; left:0; z-index:200; text-align:center; font-size:1em; font-weight:bold; padding:0.5em 0 0.5em 0; color:#ffc; background:#c30\}");

function init(){
	var msg, warnings = new Array();
	if (document.getElementById==null){
		alert("This webpage requires a recent browser such as Mozilla Firefox");
		return null;
	}
	if (checkForMathML && (msg = checkMathML())) warnings.push(msg);
	if (warnings.length>0) displayWarnings(warnings);
	if (!noMathML) initSymbols();
	return true;
}

function checkMathML(){
  if (navigator.appName.slice(0,8)=="Netscape") 
    if (navigator.appVersion.slice(0,1)>="5") noMathML = null;
    else noMathML = true;
  else if (navigator.appName.slice(0,9)=="Microsoft")
    try {
        var ActiveX = new ActiveXObject("MathPlayer.Factory.1");
        noMathML = null;
    } catch (e) {
        noMathML = true;
    }
  else if (navigator.appName.slice(0,5)=="Opera") 
    if (navigator.appVersion.slice(0,3)>="9.5") noMathML = null;
  else noMathML = true;
//noMathML = true; //uncomment to check
  if (noMathML && notifyIfNoMathML) {
    var msg = "To view the ASCIIMathML notation use Internet Explorer + MathPlayer or Mozilla Firefox 2.0 or later.";
    if (alertIfNoMathML)
       alert(msg);
    else return msg;
  }
}

function hideWarning(){
	var body = document.getElementsByTagName("body")[0];
	body.removeChild(document.getElementById('AMMLwarningBox'));
	body.onclick = null;
}

function displayWarnings(warnings) {
  var i, frag, nd = createElementXHTML("div");
  var body = document.getElementsByTagName("body")[0];
  body.onclick=hideWarning;
  nd.id = 'AMMLwarningBox';
  for (i=0; i<warnings.length; i++) {
	frag = createElementXHTML("div");
	frag.appendChild(document.createTextNode(warnings[i]));
	frag.style.paddingBottom = "1.0em";
	nd.appendChild(frag);
  }
  nd.appendChild(createElementXHTML("p"));
  nd.appendChild(document.createTextNode("For instructions see the "));
  var an = createElementXHTML("a");
  an.appendChild(document.createTextNode("ASCIIMathML"));
  an.setAttribute("href","http://www.chapman.edu/~jipsen/asciimath.html");
  nd.appendChild(an);
  nd.appendChild(document.createTextNode(" homepage"));
  an = createElementXHTML("div");
  an.id = 'AMMLcloseDiv';
  an.appendChild(document.createTextNode('(click anywhere to close this warning)'));
  nd.appendChild(an);
  var body = document.getElementsByTagName("body")[0];
  body.insertBefore(nd,body.childNodes[0]);
}

function translate(spanclassAM) {
  if (!translated) { // run this only once
    translated = true;
    var body = document.getElementsByTagName("body")[0];
    var processN = document.getElementById(AMdocumentId);
    if (translateASCIIMath) AMprocessNode((processN!=null?processN:body), false, spanclassAM);
  }
}
*/
function createElementXHTML(t) {
  if (isIE) return document.createElement(t);
  else return document.createElementNS("http://www.w3.org/1999/xhtml",t);
}

var AMmathml = "http://www.w3.org/1998/Math/MathML";

function AMcreateElementMathML(t) {
  if (isIE) return document.createElement("m:"+t);
  else return document.createElementNS(AMmathml,t);
}

function createMmlNode(t,frag) {
  var node;
  if (isIE) node = document.createElement("m:"+t);
  else node = document.createElementNS(AMmathml,t);
  if (frag) node.appendChild(frag);
  return node;
}

function newcommand(oldstr,newstr) {
  AMsymbols.push({input:oldstr, tag:"mo", output:newstr, tex:null, ttype:DEFINITION});
  refreshSymbols();
}

function newsymbol(symbolobj) {
  AMsymbols.push(symbolobj);
  refreshSymbols();
}

// character lists for Mozilla/Netscape fonts
var AMcal = ["\uD835\uDC9C","\u212C","\uD835\uDC9E","\uD835\uDC9F","\u2130","\u2131","\uD835\uDCA2","\u210B","\u2110","\uD835\uDCA5","\uD835\uDCA6","\u2112","\u2133","\uD835\uDCA9","\uD835\uDCAA","\uD835\uDCAB","\uD835\uDCAC","\u211B","\uD835\uDCAE","\uD835\uDCAF","\uD835\uDCB0","\uD835\uDCB1","\uD835\uDCB2","\uD835\uDCB3","\uD835\uDCB4","\uD835\uDCB5","\uD835\uDCB6","\uD835\uDCB7","\uD835\uDCB8","\uD835\uDCB9","\u212F","\uD835\uDCBB","\u210A","\uD835\uDCBD","\uD835\uDCBE","\uD835\uDCBF","\uD835\uDCC0","\uD835\uDCC1","\uD835\uDCC2","\uD835\uDCC3","\u2134","\uD835\uDCC5","\uD835\uDCC6","\uD835\uDCC7","\uD835\uDCC8","\uD835\uDCC9","\uD835\uDCCA","\uD835\uDCCB","\uD835\uDCCC","\uD835\uDCCD","\uD835\uDCCE","\uD835\uDCCF"];

var AMfrk = ["\uD835\uDD04","\uD835\uDD05","\u212D","\uD835\uDD07","\uD835\uDD08","\uD835\uDD09","\uD835\uDD0A","\u210C","\u2111","\uD835\uDD0D","\uD835\uDD0E","\uD835\uDD0F","\uD835\uDD10","\uD835\uDD11","\uD835\uDD12","\uD835\uDD13","\uD835\uDD14","\u211C","\uD835\uDD16","\uD835\uDD17","\uD835\uDD18","\uD835\uDD19","\uD835\uDD1A","\uD835\uDD1B","\uD835\uDD1C","\u2128","\uD835\uDD1E","\uD835\uDD1F","\uD835\uDD20","\uD835\uDD21","\uD835\uDD22","\uD835\uDD23","\uD835\uDD24","\uD835\uDD25","\uD835\uDD26","\uD835\uDD27","\uD835\uDD28","\uD835\uDD29","\uD835\uDD2A","\uD835\uDD2B","\uD835\uDD2C","\uD835\uDD2D","\uD835\uDD2E","\uD835\uDD2F","\uD835\uDD30","\uD835\uDD31","\uD835\uDD32","\uD835\uDD33","\uD835\uDD34","\uD835\uDD35","\uD835\uDD36","\uD835\uDD37"];

var AMbbb = ["\uD835\uDD38","\uD835\uDD39","\u2102","\uD835\uDD3B","\uD835\uDD3C","\uD835\uDD3D","\uD835\uDD3E","\u210D","\uD835\uDD40","\uD835\uDD41","\uD835\uDD42","\uD835\uDD43","\uD835\uDD44","\u2115","\uD835\uDD46","\u2119","\u211A","\u211D","\uD835\uDD4A","\uD835\uDD4B","\uD835\uDD4C","\uD835\uDD4D","\uD835\uDD4E","\uD835\uDD4F","\uD835\uDD50","\u2124","\uD835\uDD52","\uD835\uDD53","\uD835\uDD54","\uD835\uDD55","\uD835\uDD56","\uD835\uDD57","\uD835\uDD58","\uD835\uDD59","\uD835\uDD5A","\uD835\uDD5B","\uD835\uDD5C","\uD835\uDD5D","\uD835\uDD5E","\uD835\uDD5F","\uD835\uDD60","\uD835\uDD61","\uD835\uDD62","\uD835\uDD63","\uD835\uDD64","\uD835\uDD65","\uD835\uDD66","\uD835\uDD67","\uD835\uDD68","\uD835\uDD69","\uD835\uDD6A","\uD835\uDD6B"];
/*var AMcal = [0xEF35,0x212C,0xEF36,0xEF37,0x2130,0x2131,0xEF38,0x210B,0x2110,0xEF39,0xEF3A,0x2112,0x2133,0xEF3B,0xEF3C,0xEF3D,0xEF3E,0x211B,0xEF3F,0xEF40,0xEF41,0xEF42,0xEF43,0xEF44,0xEF45,0xEF46];
var AMfrk = [0xEF5D,0xEF5E,0x212D,0xEF5F,0xEF60,0xEF61,0xEF62,0x210C,0x2111,0xEF63,0xEF64,0xEF65,0xEF66,0xEF67,0xEF68,0xEF69,0xEF6A,0x211C,0xEF6B,0xEF6C,0xEF6D,0xEF6E,0xEF6F,0xEF70,0xEF71,0x2128];
var AMbbb = [0xEF8C,0xEF8D,0x2102,0xEF8E,0xEF8F,0xEF90,0xEF91,0x210D,0xEF92,0xEF93,0xEF94,0xEF95,0xEF96,0x2115,0xEF97,0x2119,0x211A,0x211D,0xEF98,0xEF99,0xEF9A,0xEF9B,0xEF9C,0xEF9D,0xEF9E,0x2124];*/

var CONST = 0, UNARY = 1, BINARY = 2, INFIX = 3, LEFTBRACKET = 4,
    RIGHTBRACKET = 5, SPACE = 6, UNDEROVER = 7, DEFINITION = 8,
    LEFTRIGHT = 9, TEXT = 10, /*BIG = 11, LONG = 12, STRETCHY = 13,
    MATRIX = 14,*/ UNARYUNDEROVER = 15; // token types

var AMquote = {input:"\"",   tag:"mtext", output:"mbox", tex:null, ttype:TEXT};

var AMsymbols = [
//some greek symbols
{input:"alpha",  tag:"mi", output:"\u03B1", tex:null, ttype:CONST},
{input:"beta",   tag:"mi", output:"\u03B2", tex:null, ttype:CONST},
{input:"chi",    tag:"mi", output:"\u03C7", tex:null, ttype:CONST},
{input:"delta",  tag:"mi", output:"\u03B4", tex:null, ttype:CONST},
{input:"Delta",  tag:"mo", output:"\u0394", tex:null, ttype:CONST},
{input:"epsi",   tag:"mi", output:"\u03B5", tex:"epsilon", ttype:CONST},
{input:"varepsilon", tag:"mi", output:"\u025B", tex:null, ttype:CONST},
{input:"eta",    tag:"mi", output:"\u03B7", tex:null, ttype:CONST},
{input:"gamma",  tag:"mi", output:"\u03B3", tex:null, ttype:CONST},
{input:"Gamma",  tag:"mo", output:"\u0393", tex:null, ttype:CONST},
{input:"iota",   tag:"mi", output:"\u03B9", tex:null, ttype:CONST},
{input:"kappa",  tag:"mi", output:"\u03BA", tex:null, ttype:CONST},
{input:"lambda", tag:"mi", output:"\u03BB", tex:null, ttype:CONST},
{input:"Lambda", tag:"mo", output:"\u039B", tex:null, ttype:CONST},
{input:"lamda", tag:"mi", output:"\u03BB", tex:null, ttype:CONST},
{input:"Lamda", tag:"mo", output:"\u039B", tex:null, ttype:CONST},
{input:"mu",     tag:"mi", output:"\u03BC", tex:null, ttype:CONST},
{input:"nu",     tag:"mi", output:"\u03BD", tex:null, ttype:CONST},
{input:"omega",  tag:"mi", output:"\u03C9", tex:null, ttype:CONST},
{input:"Omega",  tag:"mo", output:"\u03A9", tex:null, ttype:CONST},
{input:"phi",    tag:"mi", output:fixphi?"\u03D5":"\u03C6", tex:null, ttype:CONST},
{input:"varphi", tag:"mi", output:fixphi?"\u03C6":"\u03D5", tex:null, ttype:CONST},
{input:"Phi",    tag:"mo", output:"\u03A6", tex:null, ttype:CONST},
{input:"pi",     tag:"mi", output:"\u03C0", tex:null, ttype:CONST},
{input:"Pi",     tag:"mo", output:"\u03A0", tex:null, ttype:CONST},
{input:"psi",    tag:"mi", output:"\u03C8", tex:null, ttype:CONST},
{input:"Psi",    tag:"mi", output:"\u03A8", tex:null, ttype:CONST},
{input:"rho",    tag:"mi", output:"\u03C1", tex:null, ttype:CONST},
{input:"sigma",  tag:"mi", output:"\u03C3", tex:null, ttype:CONST},
{input:"Sigma",  tag:"mo", output:"\u03A3", tex:null, ttype:CONST},
{input:"tau",    tag:"mi", output:"\u03C4", tex:null, ttype:CONST},
{input:"theta",  tag:"mi", output:"\u03B8", tex:null, ttype:CONST},
{input:"vartheta", tag:"mi", output:"\u03D1", tex:null, ttype:CONST},
{input:"Theta",  tag:"mo", output:"\u0398", tex:null, ttype:CONST},
{input:"upsilon", tag:"mi", output:"\u03C5", tex:null, ttype:CONST},
{input:"xi",     tag:"mi", output:"\u03BE", tex:null, ttype:CONST},
{input:"Xi",     tag:"mo", output:"\u039E", tex:null, ttype:CONST},
{input:"zeta",   tag:"mi", output:"\u03B6", tex:null, ttype:CONST},

//binary operation symbols
//{input:"-",  tag:"mo", output:"\u0096", tex:null, ttype:CONST},
{input:"*",  tag:"mo", output:"\u22C5", tex:"cdot", ttype:CONST},
{input:"**", tag:"mo", output:"\u2217", tex:"ast", ttype:CONST},
{input:"***", tag:"mo", output:"\u22C6", tex:"star", ttype:CONST},
{input:"//", tag:"mo", output:"/",      tex:null, ttype:CONST},
{input:"\\\\", tag:"mo", output:"\\",   tex:"backslash", ttype:CONST},
{input:"setminus", tag:"mo", output:"\\", tex:null, ttype:CONST},
{input:"xx", tag:"mo", output:"\u00D7", tex:"times", ttype:CONST},
{input:"|><", tag:"mo", output:"\u22C9", tex:"ltimes", ttype:CONST},
{input:"><|", tag:"mo", output:"\u22CA", tex:"rtimes", ttype:CONST},
{input:"|><|", tag:"mo", output:"\u22C8", tex:"bowtie", ttype:CONST},
{input:"-:", tag:"mo", output:"\u00F7", tex:"div", ttype:CONST},
{input:"divide",   tag:"mo", output:"-:", tex:null, ttype:DEFINITION},
{input:"@",  tag:"mo", output:"\u2218", tex:"circ", ttype:CONST},
{input:"o+", tag:"mo", output:"\u2295", tex:"oplus", ttype:CONST},
{input:"ox", tag:"mo", output:"\u2297", tex:"otimes", ttype:CONST},
{input:"o.", tag:"mo", output:"\u2299", tex:"odot", ttype:CONST},
{input:"sum", tag:"mo", output:"\u2211", tex:null, ttype:UNDEROVER},
{input:"prod", tag:"mo", output:"\u220F", tex:null, ttype:UNDEROVER},
{input:"^^",  tag:"mo", output:"\u2227", tex:"wedge", ttype:CONST},
{input:"^^^", tag:"mo", output:"\u22C0", tex:"bigwedge", ttype:UNDEROVER},
{input:"vv",  tag:"mo", output:"\u2228", tex:"vee", ttype:CONST},
{input:"vvv", tag:"mo", output:"\u22C1", tex:"bigvee", ttype:UNDEROVER},
{input:"nn",  tag:"mo", output:"\u2229", tex:"cap", ttype:CONST},
{input:"nnn", tag:"mo", output:"\u22C2", tex:"bigcap", ttype:UNDEROVER},
{input:"uu",  tag:"mo", output:"\u222A", tex:"cup", ttype:CONST},
{input:"uuu", tag:"mo", output:"\u22C3", tex:"bigcup", ttype:UNDEROVER},

//binary relation symbols
{input:"!=",  tag:"mo", output:"\u2260", tex:"ne", ttype:CONST},
{input:":=",  tag:"mo", output:":=",     tex:null, ttype:CONST},
{input:"lt",  tag:"mo", output:"<",      tex:null, ttype:CONST},
{input:"<=",  tag:"mo", output:"\u2264", tex:"le", ttype:CONST},
{input:"lt=", tag:"mo", output:"\u2264", tex:"leq", ttype:CONST},
{input:"gt",  tag:"mo", output:">",      tex:null, ttype:CONST},
{input:">=",  tag:"mo", output:"\u2265", tex:"ge", ttype:CONST},
{input:"gt=", tag:"mo", output:"\u2265", tex:"geq", ttype:CONST},
{input:"-<",  tag:"mo", output:"\u227A", tex:"prec", ttype:CONST},
{input:"-lt", tag:"mo", output:"\u227A", tex:null, ttype:CONST},
{input:">-",  tag:"mo", output:"\u227B", tex:"succ", ttype:CONST},
{input:"-<=", tag:"mo", output:"\u2AAF", tex:"preceq", ttype:CONST},
{input:">-=", tag:"mo", output:"\u2AB0", tex:"succeq", ttype:CONST},
{input:"in",  tag:"mo", output:"\u2208", tex:null, ttype:CONST},
{input:"!in", tag:"mo", output:"\u2209", tex:"notin", ttype:CONST},
{input:"sub", tag:"mo", output:"\u2282", tex:"subset", ttype:CONST},
{input:"sup", tag:"mo", output:"\u2283", tex:"supset", ttype:CONST},
{input:"sube", tag:"mo", output:"\u2286", tex:"subseteq", ttype:CONST},
{input:"supe", tag:"mo", output:"\u2287", tex:"supseteq", ttype:CONST},
{input:"-=",  tag:"mo", output:"\u2261", tex:"equiv", ttype:CONST},
{input:"~=",  tag:"mo", output:"\u2245", tex:"cong", ttype:CONST},
{input:"~~",  tag:"mo", output:"\u2248", tex:"approx", ttype:CONST},
{input:"prop", tag:"mo", output:"\u221D", tex:"propto", ttype:CONST},

//logical symbols
{input:"and", tag:"mtext", output:"and", tex:null, ttype:SPACE},
{input:"or",  tag:"mtext", output:"or",  tex:null, ttype:SPACE},
{input:"not", tag:"mo", output:"\u00AC", tex:"neg", ttype:CONST},
{input:"=>",  tag:"mo", output:"\u21D2", tex:"implies", ttype:CONST},
{input:"if",  tag:"mo", output:"if",     tex:null, ttype:SPACE},
{input:"<=>", tag:"mo", output:"\u21D4", tex:"iff", ttype:CONST},
{input:"AA",  tag:"mo", output:"\u2200", tex:"forall", ttype:CONST},
{input:"EE",  tag:"mo", output:"\u2203", tex:"exists", ttype:CONST},
{input:"_|_", tag:"mo", output:"\u22A5", tex:"bot", ttype:CONST},
{input:"TT",  tag:"mo", output:"\u22A4", tex:"top", ttype:CONST},
{input:"|--",  tag:"mo", output:"\u22A2", tex:"vdash", ttype:CONST},
{input:"|==",  tag:"mo", output:"\u22A8", tex:"models", ttype:CONST},

//grouping brackets
{input:"(", tag:"mo", output:"(", tex:"left(", ttype:LEFTBRACKET},
{input:")", tag:"mo", output:")", tex:"right)", ttype:RIGHTBRACKET},
{input:"[", tag:"mo", output:"[", tex:"left[", ttype:LEFTBRACKET},
{input:"]", tag:"mo", output:"]", tex:"right]", ttype:RIGHTBRACKET},
{input:"{", tag:"mo", output:"{", tex:null, ttype:LEFTBRACKET},
{input:"}", tag:"mo", output:"}", tex:null, ttype:RIGHTBRACKET},
{input:"|", tag:"mo", output:"|", tex:null, ttype:LEFTRIGHT},
{input:":|:", tag:"mo", output:"|", tex:null, ttype:CONST},
{input:"|:", tag:"mo", output:"|", tex:null, ttype:LEFTBRACKET},
{input:":|", tag:"mo", output:"|", tex:null, ttype:RIGHTBRACKET},
//{input:"||", tag:"mo", output:"||", tex:null, ttype:LEFTRIGHT},
{input:"(:", tag:"mo", output:"\u2329", tex:"langle", ttype:LEFTBRACKET},
{input:":)", tag:"mo", output:"\u232A", tex:"rangle", ttype:RIGHTBRACKET},
{input:"<<", tag:"mo", output:"\u2329", tex:null, ttype:LEFTBRACKET},
{input:">>", tag:"mo", output:"\u232A", tex:null, ttype:RIGHTBRACKET},
{input:"{:", tag:"mo", output:"{:", tex:null, ttype:LEFTBRACKET, invisible:true},
{input:":}", tag:"mo", output:":}", tex:null, ttype:RIGHTBRACKET, invisible:true},

//miscellaneous symbols
{input:"int",  tag:"mo", output:"\u222B", tex:null, ttype:CONST},
{input:"dx",   tag:"mi", output:"{:d x:}", tex:null, ttype:DEFINITION},
{input:"dy",   tag:"mi", output:"{:d y:}", tex:null, ttype:DEFINITION},
{input:"dz",   tag:"mi", output:"{:d z:}", tex:null, ttype:DEFINITION},
{input:"dt",   tag:"mi", output:"{:d t:}", tex:null, ttype:DEFINITION},
{input:"oint", tag:"mo", output:"\u222E", tex:null, ttype:CONST},
{input:"del",  tag:"mo", output:"\u2202", tex:"partial", ttype:CONST},
{input:"grad", tag:"mo", output:"\u2207", tex:"nabla", ttype:CONST},
{input:"+-",   tag:"mo", output:"\u00B1", tex:"pm", ttype:CONST},
{input:"O/",   tag:"mo", output:"\u2205", tex:"emptyset", ttype:CONST},
{input:"oo",   tag:"mo", output:"\u221E", tex:"infty", ttype:CONST},
{input:"aleph", tag:"mo", output:"\u2135", tex:null, ttype:CONST},
{input:"...",  tag:"mo", output:"...",    tex:"ldots", ttype:CONST},
{input:":.",  tag:"mo", output:"\u2234",  tex:"therefore", ttype:CONST},
{input:":'",  tag:"mo", output:"\u2235",  tex:"because", ttype:CONST},
{input:"/_",  tag:"mo", output:"\u2220",  tex:"angle", ttype:CONST},
{input:"/_\\",  tag:"mo", output:"\u25B3",  tex:"triangle", ttype:CONST},
{input:"'",   tag:"mo", output:"\u2032",  tex:"prime", ttype:CONST},
{input:"tilde", tag:"mover", output:"~", tex:null, ttype:UNARY, acc:true},
{input:"\\ ",  tag:"mo", output:"\u00A0", tex:null, ttype:CONST},
{input:"frown",  tag:"mo", output:"\u2322", tex:null, ttype:CONST},
{input:"quad", tag:"mo", output:"\u00A0\u00A0", tex:null, ttype:CONST},
{input:"qquad", tag:"mo", output:"\u00A0\u00A0\u00A0\u00A0", tex:null, ttype:CONST},
{input:"cdots", tag:"mo", output:"\u22EF", tex:null, ttype:CONST},
{input:"vdots", tag:"mo", output:"\u22EE", tex:null, ttype:CONST},
{input:"ddots", tag:"mo", output:"\u22F1", tex:null, ttype:CONST},
{input:"diamond", tag:"mo", output:"\u22C4", tex:null, ttype:CONST},
{input:"square", tag:"mo", output:"\u25A1", tex:null, ttype:CONST},
{input:"|__", tag:"mo", output:"\u230A",  tex:"lfloor", ttype:CONST},
{input:"__|", tag:"mo", output:"\u230B",  tex:"rfloor", ttype:CONST},
{input:"|~", tag:"mo", output:"\u2308",  tex:"lceiling", ttype:CONST},
{input:"~|", tag:"mo", output:"\u2309",  tex:"rceiling", ttype:CONST},
{input:"CC",  tag:"mo", output:"\u2102", tex:null, ttype:CONST},
{input:"NN",  tag:"mo", output:"\u2115", tex:null, ttype:CONST},
{input:"QQ",  tag:"mo", output:"\u211A", tex:null, ttype:CONST},
{input:"RR",  tag:"mo", output:"\u211D", tex:null, ttype:CONST},
{input:"ZZ",  tag:"mo", output:"\u2124", tex:null, ttype:CONST},
{input:"f",   tag:"mi", output:"f",      tex:null, ttype:UNARY, func:true},
{input:"g",   tag:"mi", output:"g",      tex:null, ttype:UNARY, func:true},

//standard functions
{input:"lim",  tag:"mo", output:"lim", tex:null, ttype:UNDEROVER},
{input:"Lim",  tag:"mo", output:"Lim", tex:null, ttype:UNDEROVER},
{input:"sin",  tag:"mo", output:"sin", tex:null, ttype:UNARY, func:true},
{input:"cos",  tag:"mo", output:"cos", tex:null, ttype:UNARY, func:true},
{input:"tan",  tag:"mo", output:"tan", tex:null, ttype:UNARY, func:true},
{input:"sinh", tag:"mo", output:"sinh", tex:null, ttype:UNARY, func:true},
{input:"cosh", tag:"mo", output:"cosh", tex:null, ttype:UNARY, func:true},
{input:"tanh", tag:"mo", output:"tanh", tex:null, ttype:UNARY, func:true},
{input:"cot",  tag:"mo", output:"cot", tex:null, ttype:UNARY, func:true},
{input:"sec",  tag:"mo", output:"sec", tex:null, ttype:UNARY, func:true},
{input:"csc",  tag:"mo", output:"csc", tex:null, ttype:UNARY, func:true},
{input:"arcsin",  tag:"mo", output:"arcsin", tex:null, ttype:UNARY, func:true},
{input:"arccos",  tag:"mo", output:"arccos", tex:null, ttype:UNARY, func:true},
{input:"arctan",  tag:"mo", output:"arctan", tex:null, ttype:UNARY, func:true},
{input:"coth",  tag:"mo", output:"coth", tex:null, ttype:UNARY, func:true},
{input:"sech",  tag:"mo", output:"sech", tex:null, ttype:UNARY, func:true},
{input:"csch",  tag:"mo", output:"csch", tex:null, ttype:UNARY, func:true},
{input:"exp",  tag:"mo", output:"exp", tex:null, ttype:UNARY, func:true},
{input:"abs",   tag:"mo", output:"abs",  tex:null, ttype:UNARY, rewriteleftright:["|","|"]},
{input:"norm",   tag:"mo", output:"norm",  tex:null, ttype:UNARY, rewriteleftright:["\u2225","\u2225"]},
{input:"floor",   tag:"mo", output:"floor",  tex:null, ttype:UNARY, rewriteleftright:["\u230A","\u230B"]},
{input:"ceil",   tag:"mo", output:"ceil",  tex:null, ttype:UNARY, rewriteleftright:["\u2308","\u2309"]},
{input:"log",  tag:"mo", output:"log", tex:null, ttype:UNARY, func:true},
{input:"ln",   tag:"mo", output:"ln",  tex:null, ttype:UNARY, func:true},
{input:"det",  tag:"mo", output:"det", tex:null, ttype:UNARY, func:true},
{input:"dim",  tag:"mo", output:"dim", tex:null, ttype:CONST},
{input:"mod",  tag:"mo", output:"mod", tex:null, ttype:CONST},
{input:"gcd",  tag:"mo", output:"gcd", tex:null, ttype:UNARY, func:true},
{input:"lcm",  tag:"mo", output:"lcm", tex:null, ttype:UNARY, func:true},
{input:"lub",  tag:"mo", output:"lub", tex:null, ttype:CONST},
{input:"glb",  tag:"mo", output:"glb", tex:null, ttype:CONST},
{input:"min",  tag:"mo", output:"min", tex:null, ttype:UNDEROVER},
{input:"max",  tag:"mo", output:"max", tex:null, ttype:UNDEROVER},
{input:"Sin",  tag:"mo", output:"Sin", tex:null, ttype:UNARY, func:true},
{input:"Cos",  tag:"mo", output:"Cos", tex:null, ttype:UNARY, func:true},
{input:"Tan",  tag:"mo", output:"Tan", tex:null, ttype:UNARY, func:true},
{input:"Arcsin",  tag:"mo", output:"Arcsin", tex:null, ttype:UNARY, func:true},
{input:"Arccos",  tag:"mo", output:"Arccos", tex:null, ttype:UNARY, func:true},
{input:"Arctan",  tag:"mo", output:"Arctan", tex:null, ttype:UNARY, func:true},
{input:"Sinh", tag:"mo", output:"Sinh", tex:null, ttype:UNARY, func:true},
{input:"Cosh", tag:"mo", output:"Cosh", tex:null, ttype:UNARY, func:true},
{input:"Tanh", tag:"mo", output:"Tanh", tex:null, ttype:UNARY, func:true},
{input:"Cot",  tag:"mo", output:"Cot", tex:null, ttype:UNARY, func:true},
{input:"Sec",  tag:"mo", output:"Sec", tex:null, ttype:UNARY, func:true},
{input:"Csc",  tag:"mo", output:"Csc", tex:null, ttype:UNARY, func:true},
{input:"Log",  tag:"mo", output:"Log", tex:null, ttype:UNARY, func:true},
{input:"Ln",   tag:"mo", output:"Ln",  tex:null, ttype:UNARY, func:true},
{input:"Abs",   tag:"mo", output:"abs",  tex:null, ttype:UNARY, notexcopy:true, rewriteleftright:["|","|"]},

//arrows
{input:"uarr", tag:"mo", output:"\u2191", tex:"uparrow", ttype:CONST},
{input:"darr", tag:"mo", output:"\u2193", tex:"downarrow", ttype:CONST},
{input:"rarr", tag:"mo", output:"\u2192", tex:"rightarrow", ttype:CONST},
{input:"->",   tag:"mo", output:"\u2192", tex:"to", ttype:CONST},
{input:">->",   tag:"mo", output:"\u21A3", tex:"rightarrowtail", ttype:CONST},
{input:"->>",   tag:"mo", output:"\u21A0", tex:"twoheadrightarrow", ttype:CONST},
{input:">->>",   tag:"mo", output:"\u2916", tex:"twoheadrightarrowtail", ttype:CONST},
{input:"|->",  tag:"mo", output:"\u21A6", tex:"mapsto", ttype:CONST},
{input:"larr", tag:"mo", output:"\u2190", tex:"leftarrow", ttype:CONST},
{input:"harr", tag:"mo", output:"\u2194", tex:"leftrightarrow", ttype:CONST},
{input:"rArr", tag:"mo", output:"\u21D2", tex:"Rightarrow", ttype:CONST},
{input:"lArr", tag:"mo", output:"\u21D0", tex:"Leftarrow", ttype:CONST},
{input:"hArr", tag:"mo", output:"\u21D4", tex:"Leftrightarrow", ttype:CONST},
//commands with argument
{input:"sqrt", tag:"msqrt", output:"sqrt", tex:null, ttype:UNARY},
{input:"root", tag:"mroot", output:"root", tex:null, ttype:BINARY},
{input:"frac", tag:"mfrac", output:"/",    tex:null, ttype:BINARY},
{input:"/",    tag:"mfrac", output:"/",    tex:null, ttype:INFIX},
{input:"stackrel", tag:"mover", output:"stackrel", tex:null, ttype:BINARY},
{input:"overset", tag:"mover", output:"stackrel", tex:null, ttype:BINARY},
{input:"underset", tag:"munder", output:"stackrel", tex:null, ttype:BINARY},
{input:"_",    tag:"msub",  output:"_",    tex:null, ttype:INFIX},
{input:"^",    tag:"msup",  output:"^",    tex:null, ttype:INFIX},
{input:"hat", tag:"mover", output:"\u005E", tex:null, ttype:UNARY, acc:true},
{input:"bar", tag:"mover", output:"\u00AF", tex:"overline", ttype:UNARY, acc:true},
{input:"vec", tag:"mover", output:"\u2192", tex:null, ttype:UNARY, acc:true},
{input:"dot", tag:"mover", output:".",      tex:null, ttype:UNARY, acc:true},
{input:"ddot", tag:"mover", output:"..",    tex:null, ttype:UNARY, acc:true},
{input:"overarc", tag:"mover", output:"\u23DC", tex:"overparen", ttype:UNARY, acc:true},
{input:"ul", tag:"munder", output:"\u0332", tex:"underline", ttype:UNARY, acc:true},
{input:"ubrace", tag:"munder", output:"\u23DF", tex:"underbrace", ttype:UNARYUNDEROVER, acc:true},
{input:"obrace", tag:"mover", output:"\u23DE", tex:"overbrace", ttype:UNARYUNDEROVER, acc:true},
{input:"text", tag:"mtext", output:"text", tex:null, ttype:TEXT},
{input:"mbox", tag:"mtext", output:"mbox", tex:null, ttype:TEXT},
{input:"color", tag:"mstyle", ttype:BINARY},
{input:"id", tag:"mrow", ttype:BINARY},
{input:"class", tag:"mrow", ttype:BINARY},
{input:"cancel", tag:"menclose", output:"cancel", tex:null, ttype:UNARY},
AMquote,
{input:"bb", tag:"mstyle", atname:"mathvariant", atval:"bold", output:"bb", tex:null, ttype:UNARY},
{input:"mathbf", tag:"mstyle", atname:"mathvariant", atval:"bold", output:"mathbf", tex:null, ttype:UNARY},
{input:"sf", tag:"mstyle", atname:"mathvariant", atval:"sans-serif", output:"sf", tex:null, ttype:UNARY},
{input:"mathsf", tag:"mstyle", atname:"mathvariant", atval:"sans-serif", output:"mathsf", tex:null, ttype:UNARY},
{input:"bbb", tag:"mstyle", atname:"mathvariant", atval:"double-struck", output:"bbb", tex:null, ttype:UNARY, codes:AMbbb},
{input:"mathbb", tag:"mstyle", atname:"mathvariant", atval:"double-struck", output:"mathbb", tex:null, ttype:UNARY, codes:AMbbb},
{input:"cc",  tag:"mstyle", atname:"mathvariant", atval:"script", output:"cc", tex:null, ttype:UNARY, codes:AMcal},
{input:"mathcal", tag:"mstyle", atname:"mathvariant", atval:"script", output:"mathcal", tex:null, ttype:UNARY, codes:AMcal},
{input:"tt",  tag:"mstyle", atname:"mathvariant", atval:"monospace", output:"tt", tex:null, ttype:UNARY},
{input:"mathtt", tag:"mstyle", atname:"mathvariant", atval:"monospace", output:"mathtt", tex:null, ttype:UNARY},
{input:"fr",  tag:"mstyle", atname:"mathvariant", atval:"fraktur", output:"fr", tex:null, ttype:UNARY, codes:AMfrk},
{input:"mathfrak",  tag:"mstyle", atname:"mathvariant", atval:"fraktur", output:"mathfrak", tex:null, ttype:UNARY, codes:AMfrk}
];

function compareNames(s1,s2) {
  if (s1.input > s2.input) return 1
  else return -1;
}

var AMnames = []; //list of input symbols

function initSymbols() {
  var i;
  var symlen = AMsymbols.length;
  for (i=0; i<symlen; i++) {
    if (AMsymbols[i].tex) {
      AMsymbols.push({input:AMsymbols[i].tex,
        tag:AMsymbols[i].tag, output:AMsymbols[i].output, ttype:AMsymbols[i].ttype,
        acc:(AMsymbols[i].acc||false)});
    }
  }
  refreshSymbols();
}

function refreshSymbols(){
  var i;
  AMsymbols.sort(compareNames);
  for (i=0; i<AMsymbols.length; i++) AMnames[i] = AMsymbols[i].input;
}

function define(oldstr,newstr) {
  AMsymbols.push({input:oldstr, tag:"mo", output:newstr, tex:null, ttype:DEFINITION});
  refreshSymbols(); // this may be a problem if many symbols are defined!
}

function AMremoveCharsAndBlanks(str,n) {
//remove n characters and any following blanks
  var st;
  if (str.charAt(n)=="\\" && str.charAt(n+1)!="\\" && str.charAt(n+1)!=" ")
    st = str.slice(n+1);
  else st = str.slice(n);
  for (var i=0; i<st.length && st.charCodeAt(i)<=32; i=i+1);
  return st.slice(i);
}

function position(arr, str, n) {
// return position >=n where str appears or would be inserted
// assumes arr is sorted
  if (n==0) {
    var h,m;
    n = -1;
    h = arr.length;
    while (n+1<h) {
      m = (n+h) >> 1;
      if (arr[m]<str) n = m; else h = m;
    }
    return h;
  } else
    for (var i=n; i<arr.length && arr[i]<str; i++);
  return i; // i=arr.length || arr[i]>=str
}

function AMgetSymbol(str) {
//return maximal initial substring of str that appears in names
//return null if there is none
  var k = 0; //new pos
  var j = 0; //old pos
  var mk; //match pos
  var st;
  var tagst;
  var match = "";
  var more = true;
  for (var i=1; i<=str.length && more; i++) {
    st = str.slice(0,i); //initial substring of length i
    j = k;
    k = position(AMnames, st, j);
    if (k<AMnames.length && str.slice(0,AMnames[k].length)==AMnames[k]){
      match = AMnames[k];
      mk = k;
      i = match.length;
    }
    more = k<AMnames.length && str.slice(0,AMnames[k].length)>=AMnames[k];
  }
  AMpreviousSymbol=AMcurrentSymbol;
  if (match!=""){
    AMcurrentSymbol=AMsymbols[mk].ttype;
    return AMsymbols[mk];
  }
// if str[0] is a digit or - return maxsubstring of digits.digits
  AMcurrentSymbol=CONST;
  k = 1;
  st = str.slice(0,1);
  var integ = true;
  while ("0"<=st && st<="9" && k<=str.length) {
    st = str.slice(k,k+1);
    k++;
  }
  if (st == decimalsign) {
    st = str.slice(k,k+1);
    if ("0"<=st && st<="9") {
      integ = false;
      k++;
      while ("0"<=st && st<="9" && k<=str.length) {
        st = str.slice(k,k+1);
        k++;
      }
    }
  }
  if ((integ && k>1) || k>2) {
    st = str.slice(0,k-1);
    tagst = "mn";
  } else {
    k = 2;
    st = str.slice(0,1); //take 1 character
    tagst = (("A">st || st>"Z") && ("a">st || st>"z")?"mo":"mi");
  }
  if (st=="-" && AMpreviousSymbol==INFIX) {
    AMcurrentSymbol = INFIX;  //trick "/" into recognizing "-" on second parse
    return {input:st, tag:tagst, output:st, ttype:UNARY, func:true};
  }
  return {input:st, tag:tagst, output:st, ttype:CONST};
}

function AMremoveBrackets(node) {
  var st;
  if (!node.hasChildNodes()) { return; }
  if (node.firstChild.hasChildNodes() && (node.nodeName=="mrow" || node.nodeName=="M:MROW")) {
    st = node.firstChild.firstChild.nodeValue;
    if (st=="(" || st=="[" || st=="{") node.removeChild(node.firstChild);
  }
  if (node.lastChild.hasChildNodes() && (node.nodeName=="mrow" || node.nodeName=="M:MROW")) {
    st = node.lastChild.firstChild.nodeValue;
    if (st==")" || st=="]" || st=="}") node.removeChild(node.lastChild);
  }
}

/*Parsing ASCII math expressions with the following grammar
v ::= [A-Za-z] | greek letters | numbers | other constant symbols
u ::= sqrt | text | bb | other unary symbols for font commands
b ::= frac | root | stackrel         binary symbols
l ::= ( | [ | { | (: | {:            left brackets
r ::= ) | ] | } | :) | :}            right brackets
S ::= v | lEr | uS | bSS             Simple expression
I ::= S_S | S^S | S_S^S | S          Intermediate expression
E ::= IE | I/I                       Expression
Each terminal symbol is translated into a corresponding mathml node.*/

var AMnestingDepth,AMpreviousSymbol,AMcurrentSymbol;

function AMparseSexpr(str) { //parses str and returns [node,tailstr]
  var symbol, node, result, i, st,// rightvert = false,
    newFrag = document.createDocumentFragment();
  str = AMremoveCharsAndBlanks(str,0);
  symbol = AMgetSymbol(str);             //either a token or a bracket or empty
  if (symbol == null || symbol.ttype == RIGHTBRACKET && AMnestingDepth > 0) {
    return [null,str];
  }
  if (symbol.ttype == DEFINITION) {
    str = symbol.output+AMremoveCharsAndBlanks(str,symbol.input.length);
    symbol = AMgetSymbol(str);
  }
  switch (symbol.ttype) {  case UNDEROVER:
  case CONST:
    str = AMremoveCharsAndBlanks(str,symbol.input.length);
    return [createMmlNode(symbol.tag,        //its a constant
                             document.createTextNode(symbol.output)),str];
  case LEFTBRACKET:   //read (expr+)
    AMnestingDepth++;
    str = AMremoveCharsAndBlanks(str,symbol.input.length);
    result = AMparseExpr(str,true);
    AMnestingDepth--;
    if (typeof symbol.invisible == "boolean" && symbol.invisible)
      node = createMmlNode("mrow",result[0]);
    else {
      node = createMmlNode("mo",document.createTextNode(symbol.output));
      node = createMmlNode("mrow",node);
      node.appendChild(result[0]);
    }
    return [node,result[1]];
  case TEXT:
      if (symbol!=AMquote) str = AMremoveCharsAndBlanks(str,symbol.input.length);
      if (str.charAt(0)=="{") i=str.indexOf("}");
      else if (str.charAt(0)=="(") i=str.indexOf(")");
      else if (str.charAt(0)=="[") i=str.indexOf("]");
      else if (symbol==AMquote) i=str.slice(1).indexOf("\"")+1;
      else i = 0;
      if (i==-1) i = str.length;
      st = str.slice(1,i);
      if (st.charAt(0) == " ") {
        node = createMmlNode("mspace");
        node.setAttribute("width","1ex");
        newFrag.appendChild(node);
      }
      newFrag.appendChild(
        createMmlNode(symbol.tag,document.createTextNode(st)));
      if (st.charAt(st.length-1) == " ") {
        node = createMmlNode("mspace");
        node.setAttribute("width","1ex");
        newFrag.appendChild(node);
      }
      str = AMremoveCharsAndBlanks(str,i+1);
      return [createMmlNode("mrow",newFrag),str];
  case UNARYUNDEROVER:
  case UNARY:
      str = AMremoveCharsAndBlanks(str,symbol.input.length);
      result = AMparseSexpr(str);
      if (result[0]==null) return [createMmlNode(symbol.tag,
                             document.createTextNode(symbol.output)),str];
      if (typeof symbol.func == "boolean" && symbol.func) { // functions hack
        st = str.charAt(0);
          if (st=="^" || st=="_" || st=="/" || st=="|" || st=="," ||
             (symbol.input.length==1 && symbol.input.match(/\w/) && st!="(")) {
          return [createMmlNode(symbol.tag,
                    document.createTextNode(symbol.output)),str];
        } else {
          node = createMmlNode("mrow",
           createMmlNode(symbol.tag,document.createTextNode(symbol.output)));
          node.appendChild(result[0]);
          return [node,result[1]];
        }
      }
      AMremoveBrackets(result[0]);
      if (symbol.input == "sqrt") {           // sqrt
        return [createMmlNode(symbol.tag,result[0]),result[1]];
      } else if (typeof symbol.rewriteleftright != "undefined") {    // abs, floor, ceil
          node = createMmlNode("mrow", createMmlNode("mo",document.createTextNode(symbol.rewriteleftright[0])));
          node.appendChild(result[0]);
          node.appendChild(createMmlNode("mo",document.createTextNode(symbol.rewriteleftright[1])));
          return [node,result[1]];
      } else if (symbol.input == "cancel") {   // cancel
        node = createMmlNode(symbol.tag,result[0]);
	node.setAttribute("notation","updiagonalstrike");
	return [node,result[1]];
      } else if (typeof symbol.acc == "boolean" && symbol.acc) {   // accent
        node = createMmlNode(symbol.tag,result[0]);
        var accnode = createMmlNode("mo",document.createTextNode(symbol.output));
        if (symbol.input=="vec" && (
		(result[0].nodeName=="mrow" && result[0].childNodes.length==1
			&& result[0].firstChild.firstChild.nodeValue !== null
			&& result[0].firstChild.firstChild.nodeValue.length==1) ||
		(result[0].firstChild.nodeValue !== null
			&& result[0].firstChild.nodeValue.length==1) )) {
			accnode.setAttribute("stretchy",false);
        }
        node.appendChild(accnode);
        return [node,result[1]];
      } else {                        // font change command
        if (!isIE && typeof symbol.codes != "undefined") {
          for (i=0; i<result[0].childNodes.length; i++)
            if (result[0].childNodes[i].nodeName=="mi" || result[0].nodeName=="mi") {
              st = (result[0].nodeName=="mi"?result[0].firstChild.nodeValue:
                              result[0].childNodes[i].firstChild.nodeValue);
              var newst = [];
              for (var j=0; j<st.length; j++)
		  if (st.charCodeAt(j)>64 && st.charCodeAt(j)<91)
		  	newst = newst + symbol.codes[st.charCodeAt(j)-65];
                else if (st.charCodeAt(j)>96 && st.charCodeAt(j)<123)
                	newst = newst + symbol.codes[st.charCodeAt(j)-71];
                else newst = newst + st.charAt(j);
              if (result[0].nodeName=="mi")
                result[0]=createMmlNode("mo").
                          appendChild(document.createTextNode(newst));
              else result[0].replaceChild(createMmlNode("mo").
                               appendChild(document.createTextNode(newst)),
                                           result[0].childNodes[i]);
            }
        }
        node = createMmlNode(symbol.tag,result[0]);
        node.setAttribute(symbol.atname,symbol.atval);
        return [node,result[1]];
      }
  case BINARY:
    str = AMremoveCharsAndBlanks(str,symbol.input.length);
    result = AMparseSexpr(str);
    if (result[0]==null) return [createMmlNode("mo",
                           document.createTextNode(symbol.input)),str];
    AMremoveBrackets(result[0]);
    var result2 = AMparseSexpr(result[1]);
    if (result2[0]==null) return [createMmlNode("mo",
                           document.createTextNode(symbol.input)),str];
    AMremoveBrackets(result2[0]);
    if (['color', 'class', 'id'].indexOf(symbol.input) >= 0) {

      // Get the second argument
    	if (str.charAt(0)=="{") i=str.indexOf("}");
      else if (str.charAt(0)=="(") i=str.indexOf(")");
      else if (str.charAt(0)=="[") i=str.indexOf("]");
    	st = str.slice(1,i);

      // Make a mathml node
    	node = createMmlNode(symbol.tag,result2[0]);

      // Set the correct attribute
      if (symbol.input === "color") node.setAttribute("mathcolor", st)
      else if (symbol.input === "class") node.setAttribute("class", st)
      else if (symbol.input === "id") node.setAttribute("id", st)
   	return [node,result2[1]];
    }
    if (symbol.input=="root" || symbol.output=="stackrel")
      newFrag.appendChild(result2[0]);
    newFrag.appendChild(result[0]);
    if (symbol.input=="frac") newFrag.appendChild(result2[0]);
    return [createMmlNode(symbol.tag,newFrag),result2[1]];
  case INFIX:
    str = AMremoveCharsAndBlanks(str,symbol.input.length);
    return [createMmlNode("mo",document.createTextNode(symbol.output)),str];
  case SPACE:
    str = AMremoveCharsAndBlanks(str,symbol.input.length);
    node = createMmlNode("mspace");
    node.setAttribute("width","1ex");
    newFrag.appendChild(node);
    newFrag.appendChild(
      createMmlNode(symbol.tag,document.createTextNode(symbol.output)));
    node = createMmlNode("mspace");
    node.setAttribute("width","1ex");
    newFrag.appendChild(node);
    return [createMmlNode("mrow",newFrag),str];
  case LEFTRIGHT:
//    if (rightvert) return [null,str]; else rightvert = true;
    AMnestingDepth++;
    str = AMremoveCharsAndBlanks(str,symbol.input.length);
    result = AMparseExpr(str,false);
    AMnestingDepth--;
    st = "";
    if (result[0].lastChild!=null)
      st = result[0].lastChild.firstChild.nodeValue;
    if (st == "|" && str.charAt(0)!==",") { // its an absolute value subterm
      node = createMmlNode("mo",document.createTextNode(symbol.output));
      node = createMmlNode("mrow",node);
      node.appendChild(result[0]);
      return [node,result[1]];
    } else { // the "|" is a \mid so use unicode 2223 (divides) for spacing
      node = createMmlNode("mo",document.createTextNode("\u2223"));
      node = createMmlNode("mrow",node);
      return [node,str];
    }
  default:
//alert("default");
    str = AMremoveCharsAndBlanks(str,symbol.input.length);
    return [createMmlNode(symbol.tag,        //its a constant
                             document.createTextNode(symbol.output)),str];
  }
}

function AMparseIexpr(str) {
  var symbol, sym1, sym2, node, result, underover;
  str = AMremoveCharsAndBlanks(str,0);
  sym1 = AMgetSymbol(str);
  result = AMparseSexpr(str);
  node = result[0];
  str = result[1];
  symbol = AMgetSymbol(str);
  if (symbol.ttype == INFIX && symbol.input != "/") {
    str = AMremoveCharsAndBlanks(str,symbol.input.length);
//    if (symbol.input == "/") result = AMparseIexpr(str); else ...
    result = AMparseSexpr(str);
    if (result[0] == null) // show box in place of missing argument
      result[0] = createMmlNode("mo",document.createTextNode("\u25A1"));
    else AMremoveBrackets(result[0]);
    str = result[1];
//    if (symbol.input == "/") AMremoveBrackets(node);
    underover = (sym1.ttype == UNDEROVER || sym1.ttype == UNARYUNDEROVER);
    if (symbol.input == "_") {
      sym2 = AMgetSymbol(str);
      if (sym2.input == "^") {
        str = AMremoveCharsAndBlanks(str,sym2.input.length);
        var res2 = AMparseSexpr(str);
        AMremoveBrackets(res2[0]);
        str = res2[1];
        node = createMmlNode((underover?"munderover":"msubsup"),node);
        node.appendChild(result[0]);
        node.appendChild(res2[0]);
        node = createMmlNode("mrow",node); // so sum does not stretch
      } else {
        node = createMmlNode((underover?"munder":"msub"),node);
        node.appendChild(result[0]);
      }
    } else if (symbol.input == "^" && underover) {
    	node = createMmlNode("mover",node);
        node.appendChild(result[0]);
    } else {
      node = createMmlNode(symbol.tag,node);
      node.appendChild(result[0]);
    }
    if (typeof sym1.func != 'undefined' && sym1.func) {
    	sym2 = AMgetSymbol(str);
    	if (sym2.ttype != INFIX && sym2.ttype != RIGHTBRACKET) {
    		result = AMparseIexpr(str);
    		node = createMmlNode("mrow",node);
    		node.appendChild(result[0]);
    		str = result[1];
    	}
    }
  }
  return [node,str];
}

function AMparseExpr(str,rightbracket) {
  var symbol, node, result, i,
  newFrag = document.createDocumentFragment();
  do {
    str = AMremoveCharsAndBlanks(str,0);
    result = AMparseIexpr(str);
    node = result[0];
    str = result[1];
    symbol = AMgetSymbol(str);
    if (symbol.ttype == INFIX && symbol.input == "/") {
      str = AMremoveCharsAndBlanks(str,symbol.input.length);
      result = AMparseIexpr(str);
      if (result[0] == null) // show box in place of missing argument
        result[0] = createMmlNode("mo",document.createTextNode("\u25A1"));
      else AMremoveBrackets(result[0]);
      str = result[1];
      AMremoveBrackets(node);
      node = createMmlNode(symbol.tag,node);
      node.appendChild(result[0]);
      newFrag.appendChild(node);
      symbol = AMgetSymbol(str);
    }
    else if (node!=undefined) newFrag.appendChild(node);
  } while ((symbol.ttype != RIGHTBRACKET &&
           (symbol.ttype != LEFTRIGHT || rightbracket)
           || AMnestingDepth == 0) && symbol!=null && symbol.output!="");
  if (symbol.ttype == RIGHTBRACKET || symbol.ttype == LEFTRIGHT) {
//    if (AMnestingDepth > 0) AMnestingDepth--;
    var len = newFrag.childNodes.length;
    if (len>0 && newFrag.childNodes[len-1].nodeName == "mrow"
    	    && newFrag.childNodes[len-1].lastChild
    	    && newFrag.childNodes[len-1].lastChild.firstChild ) { //matrix
    	    //removed to allow row vectors: //&& len>1 &&
    	    //newFrag.childNodes[len-2].nodeName == "mo" &&
    	    //newFrag.childNodes[len-2].firstChild.nodeValue == ","
      var right = newFrag.childNodes[len-1].lastChild.firstChild.nodeValue;
      if (right==")" || right=="]") {
        var left = newFrag.childNodes[len-1].firstChild.firstChild.nodeValue;
        if (left=="(" && right==")" && symbol.output != "}" ||
            left=="[" && right=="]") {
        var pos = []; // positions of commas
        var matrix = true;
        var m = newFrag.childNodes.length;
        for (i=0; matrix && i<m; i=i+2) {
          pos[i] = [];
          node = newFrag.childNodes[i];
          if (matrix) matrix = node.nodeName=="mrow" &&
            (i==m-1 || node.nextSibling.nodeName=="mo" &&
            node.nextSibling.firstChild.nodeValue==",")&&
            node.firstChild.firstChild.nodeValue==left &&
            node.lastChild.firstChild.nodeValue==right;
          if (matrix)
            for (var j=0; j<node.childNodes.length; j++)
              if (node.childNodes[j].firstChild.nodeValue==",")
                pos[i][pos[i].length]=j;
          if (matrix && i>1) matrix = pos[i].length == pos[i-2].length;
        }
        matrix = matrix && (pos.length>1 || pos[0].length>0);
        var columnlines = [];
        if (matrix) {
          var row, frag, n, k, table = document.createDocumentFragment();
          for (i=0; i<m; i=i+2) {
            row = document.createDocumentFragment();
            frag = document.createDocumentFragment();
            node = newFrag.firstChild; // <mrow>(-,-,...,-,-)</mrow>
            n = node.childNodes.length;
            k = 0;
            node.removeChild(node.firstChild); //remove (
            for (j=1; j<n-1; j++) {
              if (typeof pos[i][k] != "undefined" && j==pos[i][k]){
                node.removeChild(node.firstChild); //remove ,
                if (node.firstChild.nodeName=="mrow" && node.firstChild.childNodes.length==1 &&
         	  node.firstChild.firstChild.firstChild.nodeValue=="\u2223") {
         	    //is columnline marker - skip it
         	    if (i==0) { columnlines.push("solid"); }
         	    node.removeChild(node.firstChild); //remove mrow
         	    node.removeChild(node.firstChild); //remove ,
         	    j+=2;
         	    k++;
            	} else if (i==0) { columnlines.push("none"); }
                row.appendChild(createMmlNode("mtd",frag));
                k++;
              } else frag.appendChild(node.firstChild);
            }
            row.appendChild(createMmlNode("mtd",frag));
            if (i==0) { columnlines.push("none"); }
            if (newFrag.childNodes.length>2) {
              newFrag.removeChild(newFrag.firstChild); //remove <mrow>)</mrow>
              newFrag.removeChild(newFrag.firstChild); //remove <mo>,</mo>
            }
            table.appendChild(createMmlNode("mtr",row));
          }
          node = createMmlNode("mtable",table);
          node.setAttribute("columnlines", columnlines.join(" "));
          if (typeof symbol.invisible == "boolean" && symbol.invisible) node.setAttribute("columnalign","left");
          newFrag.replaceChild(node,newFrag.firstChild);
        }
       }
      }
    }
    str = AMremoveCharsAndBlanks(str,symbol.input.length);
    if (typeof symbol.invisible != "boolean" || !symbol.invisible) {
      node = createMmlNode("mo",document.createTextNode(symbol.output));
      newFrag.appendChild(node);
    }
  }
  return [newFrag,str];
}

function parseMath(str,latex) {
  var frag, node;
  AMnestingDepth = 0;
  //some basic cleanup for dealing with stuff editors like TinyMCE adds
  str = str.replace(/&nbsp;/g,"");
  str = str.replace(/&gt;/g,">");
  str = str.replace(/&lt;/g,"<");
  frag = AMparseExpr(str.replace(/^\s+/g,""),false)[0];
  node = createMmlNode("mstyle",frag);
  if (mathcolor != "") node.setAttribute("mathcolor",mathcolor);
  if (mathfontsize != "") {
	  node.setAttribute("fontsize", mathfontsize);
	  node.setAttribute("mathsize", mathfontsize);
  }
  if (mathfontfamily != "") {
	  node.setAttribute("fontfamily", mathfontfamily);
	  node.setAttribute("mathvariant", mathfontfamily);
  }

  if (displaystyle) node.setAttribute("displaystyle","true");
  node = createMmlNode("math",node);
  if (showasciiformulaonhover)                      //fixed by djhsu so newline
    node.setAttribute("title",str.replace(/\s+/g," "));//does not show in Gecko
  return node;
}

/*
function strarr2docFrag(arr, linebreaks, latex) {
  var newFrag=document.createDocumentFragment();
  var expr = false;
  for (var i=0; i<arr.length; i++) {
    if (expr) newFrag.appendChild(parseMath(arr[i],latex));
    else {
      var arri = (linebreaks ? arr[i].split("\n\n") : [arr[i]]);
      newFrag.appendChild(createElementXHTML("span").
      appendChild(document.createTextNode(arri[0])));
      for (var j=1; j<arri.length; j++) {
        newFrag.appendChild(createElementXHTML("p"));
        newFrag.appendChild(createElementXHTML("span").
        appendChild(document.createTextNode(arri[j])));
      }
    }
    expr = !expr;
  }
  return newFrag;
}

function AMautomathrec(str) {
//formula is a space (or start of str) followed by a maximal sequence of *two* or more tokens, possibly separated by runs of digits and/or space.
//tokens are single letters (except a, A, I) and ASCIIMathML tokens
  var texcommand = "\\\\[a-zA-Z]+|\\\\\\s|";
  var ambigAMtoken = "\\b(?:oo|lim|ln|int|oint|del|grad|aleph|prod|prop|sinh|cosh|tanh|cos|sec|pi|tt|fr|sf|sube|supe|sub|sup|det|mod|gcd|lcm|min|max|vec|ddot|ul|chi|eta|nu|mu)(?![a-z])|";
  var englishAMtoken = "\\b(?:sum|ox|log|sin|tan|dim|hat|bar|dot)(?![a-z])|";
  var secondenglishAMtoken = "|\\bI\\b|\\bin\\b|\\btext\\b"; // took if and or not out
  var simpleAMtoken = "NN|ZZ|QQ|RR|CC|TT|AA|EE|sqrt|dx|dy|dz|dt|xx|vv|uu|nn|bb|cc|csc|cot|alpha|beta|delta|Delta|epsilon|gamma|Gamma|kappa|lambda|Lambda|omega|phi|Phi|Pi|psi|Psi|rho|sigma|Sigma|tau|theta|Theta|xi|Xi|zeta"; // uuu nnn?
  var letter = "[a-zA-HJ-Z](?=(?:[^a-zA-Z]|$|"+ambigAMtoken+englishAMtoken+simpleAMtoken+"))|";
  var token = letter+texcommand+"\\d+|[-()[\\]{}+=*&^_%\\\@/<>,\\|!:;'~]|\\.(?!(?:\x20|$))|"+ambigAMtoken+englishAMtoken+simpleAMtoken;
  var re = new RegExp("(^|\\s)((("+token+")\\s?)(("+token+secondenglishAMtoken+")\\s?)+)([,.?]?(?=\\s|$))","g");
  str = str.replace(re," `$2`$7");
  var arr = str.split(AMdelimiter1);
  var re1 = new RegExp("(^|\\s)([b-zB-HJ-Z+*<>]|"+texcommand+ambigAMtoken+simpleAMtoken+")(\\s|\\n|$)","g");
  var re2 = new RegExp("(^|\\s)([a-z]|"+texcommand+ambigAMtoken+simpleAMtoken+")([,.])","g"); // removed |\d+ for now
  for (i=0; i<arr.length; i++)   //single nonenglish tokens
    if (i%2==0) {
      arr[i] = arr[i].replace(re1," `$2`$3");
      arr[i] = arr[i].replace(re2," `$2`$3");
      arr[i] = arr[i].replace(/([{}[\]])/,"`$1`");
    }
  str = arr.join(AMdelimiter1);
  str = str.replace(/((^|\s)\([a-zA-Z]{2,}.*?)\)`/g,"$1`)");  //fix parentheses
  str = str.replace(/`(\((a\s|in\s))(.*?[a-zA-Z]{2,}\))/g,"$1`$3");  //fix parentheses
  str = str.replace(/\sin`/g,"` in");
  str = str.replace(/`(\(\w\)[,.]?(\s|\n|$))/g,"$1`");
  str = str.replace(/`([0-9.]+|e.g|i.e)`(\.?)/gi,"$1$2");
  str = str.replace(/`([0-9.]+:)`/g,"$1");
  return str;
}

function processNodeR(n, linebreaks,latex) {
  var mtch, str, arr, frg, i;
  if (n.childNodes.length == 0) {
   if ((n.nodeType!=8 || linebreaks) &&
    n.parentNode.nodeName!="form" && n.parentNode.nodeName!="FORM" &&
    n.parentNode.nodeName!="textarea" && n.parentNode.nodeName!="TEXTAREA"
      //&&
      //n.parentNode.nodeName!="pre" && n.parentNode.nodeName!="PRE"
    ) {
    str = n.nodeValue;
    if (!(str == null)) {
      str = str.replace(/\r\n\r\n/g,"\n\n");
      str = str.replace(/\x20+/g," ");
      str = str.replace(/\s*\r\n/g," ");
      if(latex) {
// DELIMITERS:
        mtch = (str.indexOf("\$")==-1 ? false : true);
        str = str.replace(/([^\\])\$/g,"$1 \$");
        str = str.replace(/^\$/," \$");	// in case \$ at start of string
        arr = str.split(" \$");
        for (i=0; i<arr.length; i++)
	  arr[i]=arr[i].replace(/\\\$/g,"\$");
      } else {
      mtch = false;
      str = str.replace(new RegExp(AMescape1, "g"),
              function(){mtch = true; return "AMescape1"});
      str = str.replace(/\\?end{?a?math}?/i,
              function(){automathrecognize = false; mtch = true; return ""});
      str = str.replace(/amath\b|\\begin{a?math}/i,
              function(){automathrecognize = true; mtch = true; return ""});
      arr = str.split(AMdelimiter1);
      if (automathrecognize)
        for (i=0; i<arr.length; i++)
          if (i%2==0) arr[i] = AMautomathrec(arr[i]);
      str = arr.join(AMdelimiter1);
      arr = str.split(AMdelimiter1);
      for (i=0; i<arr.length; i++) // this is a problem ************
        arr[i]=arr[i].replace(/AMescape1/g,AMdelimiter1);
      }
      if (arr.length>1 || mtch) {
        if (!noMathML) {
          frg = strarr2docFrag(arr,n.nodeType==8,latex);
          var len = frg.childNodes.length;
          n.parentNode.replaceChild(frg,n);
          return len-1;
        } else return 0;
      }
    }
   } else return 0;
  } else if (n.nodeName!="math") {
    for (i=0; i<n.childNodes.length; i++)
      i += processNodeR(n.childNodes[i], linebreaks,latex);
  }
  return 0;
}

function AMprocessNode(n, linebreaks, spanclassAM) {
  var frag,st;
  if (spanclassAM!=null) {
    frag = document.getElementsByTagName("span")
    for (var i=0;i<frag.length;i++)
      if (frag[i].className == "AM") 
        processNodeR(frag[i],linebreaks,false);
  } else {
    try {
      st = n.innerHTML; // look for AMdelimiter on page
    } catch(err) {}
//alert(st)
    if (st==null || /amath\b|\\begin{a?math}/i.test(st) ||
      st.indexOf(AMdelimiter1+" ")!=-1 || st.slice(-1)==AMdelimiter1 ||
      st.indexOf(AMdelimiter1+"<")!=-1 || st.indexOf(AMdelimiter1+"\n")!=-1) {
      processNodeR(n,linebreaks,false);
    }
  }
}

function generic(){
  if(!init()) return;
  if (translateOnLoad) {
      translate();
  }
};
//setup onload function
if(typeof window.addEventListener != 'undefined'){
  //.. gecko, safari, konqueror and standard
  window.addEventListener('load', generic, false);
}
else if(typeof document.addEventListener != 'undefined'){
  //.. opera 7
  document.addEventListener('load', generic, false);
}
else if(typeof window.attachEvent != 'undefined'){
  //.. win/ie
  window.attachEvent('onload', generic);
}else{
  //.. mac/ie5 and anything else that gets this far
  //if there's an existing onload function
  if(typeof window.onload == 'function'){
    //store it
    var existing = onload;
    //add new onload handler
    window.onload = function(){
      //call existing onload function
      existing();
      //call generic onload function
      generic();
    };
  }else{
    window.onload = generic;
  }
}

//expose some functions to outside
asciimath.newcommand = newcommand;
asciimath.newsymbol = newsymbol;
asciimath.AMprocesssNode = AMprocessNode;
asciimath.parseMath = parseMath;
asciimath.translate = translate;
})();

*/

/******************************************************************
 *
 *   The previous section is ASCIIMathML.js Version 2.2
 *   (c) Peter Jipsen, used with permission.
 *
 ******************************************************************/

showasciiformulaonhover = false;
mathfontfamily = "";
mathcolor = "";
mathfontsize = "";

//
//  Remove remapping of mathvariants to plane1 (MathJax handles that)
//  Change functions to mi rather than mo (to get spacing right)
//
(function () {
  for (var i = 0, m = AMsymbols.length; i < m; i++) {
    if (AMsymbols[i].codes) {delete AMsymbols[i].codes}
    if (AMsymbols[i].func) {AMsymbols[i].tag = "mi"}
  }
})();

//
//  Access to AsciiMath functions and values
//
ASCIIMATH.Augment({
  AM: {
    Init: function () {
      displaystyle = ASCIIMATH.config.displaystyle;
      // Old versions use the "decimal" option, so take it into account if it
      // is defined by the user. See issue 384.
      decimalsign  = (ASCIIMATH.config.decimal || ASCIIMATH.config.decimalsign);
      // unfix phi and varphi, if requested
      if (!ASCIIMATH.config.fixphi) {
        for (var i = 0, m = AMsymbols.length; i < m; i++) {
          if (AMsymbols[i].input === "phi")    {AMsymbols[i].output = "\u03C6"}
          if (AMsymbols[i].input === "varphi") {AMsymbols[i].output = "\u03D5"; i = m}
        }
      }
   
      INITASCIIMATH();
      initSymbols();
    },
    Augment: function (def) {
      for (var id in def) {if (def.hasOwnProperty(id)) {
	switch (id) {
	 case "displaystyle": displaystyle = def[id]; break;
	 case "decimal": decimal = def[id]; break;
	 case "parseMath": parseMath = def[id]; break;
	 case "parseExpr": AMparseExpr = def[id]; break;
	 case "parseIexpr": AMparseIexpr = def[id]; break;
	 case "parseSexpr": AMparseSexpr = def[id]; break;
	 case "removeBrackets": AMremoveBrackets = def[id]; break;
	 case "getSymbol": AMgetSymbol = def[id]; break;
	 case "position": position = def[id]; break;
	 case "removeCharsAndBlanks": AMremoveCharsAndBlanks = def[id]; break;
	 case "createMmlNode": createMmlNode = def[id]; break;
	 case "createElementMathML": AMcreateElementMathML = def[id]; break;
	 case "createElementXHTML": createElementXHTML = def[id]; break;
	 case "initSymbols": initSymbols = def[id]; break;
	 case "refreshSymbols": refreshSymbols = def[id]; break;
	 case "compareNames": compareNames = def[id]; break;
	};
        this[id] = def[id];
      }};
    },
    parseMath:  parseMath,
    parseExpr:  AMparseExpr,
    parseIexpr: AMparseIexpr,
    parseSexr:  AMparseSexpr,
    removeBrackets: AMremoveBrackets,
    getSymbol:  AMgetSymbol,
    position:   position,
    removeCharsAndBlanks: AMremoveCharsAndBlanks,
    createMmlNode: createMmlNode,
    createElementMathML: AMcreateElementMathML,
    createElementXHTML:  createElementXHTML,
    initSymbols: initSymbols,
    refreshSymbols: refreshSymbols,
    compareNames: compareNames,
    
    createDocumentFragment: DOCFRAG,
    document: document,
    
    define: define,
    newcommand: newcommand,
    newsymbol: newsymbol,
    symbols: AMsymbols,
    names: AMnames,
        
    TOKEN: {
      CONST:CONST, UNARY:UNARY, BINARY:BINARY, INFIX:INFIX,
      LEFTBRACKET:LEFTBRACKET, RIGHTBRACKET:RIGHTBRACKET, SPACE:SPACE,
      UNDEROVER:UNDEROVER, DEFINITION:DEFINITION, LEFTRIGHT:LEFTRIGHT, TEXT:TEXT,
      UNARYUNDEROVER:UNARYUNDEROVER
    }
  }
});

//
//  Make minimizer think these have been used
//
var junk = [window, navigator]; junk = null;
  
})(MathJax.InputJax.AsciiMath);


/************************************************************************/

(function (ASCIIMATH) {
  var MML;
  
  ASCIIMATH.Augment({
    sourceMenuTitle: /*_(MathMenu)*/ ["AsciiMathInput","AsciiMath Input"],
    annotationEncoding: "text/x-asciimath",

    prefilterHooks:    MathJax.Callback.Hooks(true),   // hooks to run before processing AsciiMath
    postfilterHooks:   MathJax.Callback.Hooks(true),   // hooks to run after processing AsciiMath

    Translate: function (script) {
      var mml, math = MathJax.HTML.getScript(script);
      var data = {math:math, script:script};
      var callback = this.prefilterHooks.Execute(data); if (callback) return callback;
      math = data.math;
      try {
        mml = this.AM.parseMath(math);
      } catch(err) {
        if (!err.asciimathError) {throw err}
        mml = this.formatError(err,math);
      }
      data.math = MML(mml); this.postfilterHooks.Execute(data);
      return this.postfilterHooks.Execute(data) || data.math;
    },
    formatError: function (err,math,script) {
      var message = err.message.replace(/\n.*/,"");
      MathJax.Hub.signal.Post(["AsciiMath Jax - parse error",message,math,script]);
      return MML.Error(message);
    },
    Error: function (message) {
      throw MathJax.Hub.Insert(Error(message),{asciimathError: true});
    },
    //
    //  Initialize the MML variable and AsciiMath itself
    //
    Startup: function () {
      MML = MathJax.ElementJax.mml;
      this.AM.Init();
    }
  });

  ASCIIMATH.loadComplete("jax.js");
  
})(MathJax.InputJax.AsciiMath);



