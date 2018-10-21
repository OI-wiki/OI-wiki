/* -*- Mode: Javascript; indent-tabs-mode:nil; js-indent-level: 2 -*- */
/* vim: set ts=2 et sw=2 tw=80: */

/*************************************************************
 *
 *  MathJax/extensions/mml2jax.js
 *  
 *  Implements the MathML to Jax preprocessor that locates <math> nodes
 *  within the text of a document and replaces them with SCRIPT tags
 *  for processing by MathJax.
 *
 *  ---------------------------------------------------------------------
 *  
 *  Copyright (c) 2010-2018 The MathJax Consortium
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

MathJax.Extension.mml2jax = {
  version: "2.7.5",
  config: {
    preview: "mathml"       // Use the <math> element as the
                            //   preview.  Set to "none" for no preview,
                            //   set to "alttext" to use the alttext attribute
                            //   of the <math> element, set to "altimg" to use
                            //   an image described by the altimg* attributes
                            //   or set to an array specifying an HTML snippet
                            //   to use a fixed preview for all math

  },
  MMLnamespace: "http://www.w3.org/1998/Math/MathML",
  
  PreProcess: function (element) {
    if (!this.configured) {
      this.config = MathJax.Hub.CombineConfig("mml2jax",this.config);
      if (this.config.Augment) {MathJax.Hub.Insert(this,this.config.Augment)}
      this.InitBrowser();
      this.configured = true;
    }
    if (typeof(element) === "string") {element = document.getElementById(element)}
    if (!element) {element = document.body}
    var mathArray = [];
    //
    //  Handle all math tags with no namespaces
    //
    this.PushMathElements(mathArray,element,"math");
    //
    //  Handle math with namespaces in XHTML
    //
    this.PushMathElements(mathArray,element,"math",this.MMLnamespace);
    //
    //  Handle math with namespaces in HTML
    //
    var i, m;
    if (typeof(document.namespaces) !== "undefined") {
      //
      // IE namespaces are listed in document.namespaces
      //
      try {
        for (i = 0, m = document.namespaces.length; i < m; i++) {
          var ns = document.namespaces[i];
          if (ns.urn === this.MMLnamespace)
            {this.PushMathElements(mathArray,element,ns.name+":math")}
        }
      } catch (err) {}
    } else {
      //
      //  Everybody else
      //  
      var html = document.getElementsByTagName("html")[0];
      if (html) {
        for (i = 0, m = html.attributes.length; i < m; i++) {
          var attr = html.attributes[i];
          if (attr.nodeName.substr(0,6) === "xmlns:" && attr.nodeValue === this.MMLnamespace)
            {this.PushMathElements(mathArray,element,attr.nodeName.substr(6)+":math")}
        }
      }
    }
    this.ProcessMathArray(mathArray);
  },
  
  PushMathElements: function (array,element,name,namespace) {
    var math, preview = MathJax.Hub.config.preRemoveClass;
    if (namespace) {
      if (!element.getElementsByTagNameNS) return;
      math = element.getElementsByTagNameNS(namespace,name);
    } else {
      math = element.getElementsByTagName(name);
    }
    for (var i = 0, m = math.length; i < m; i++) {
      var parent = math[i].parentNode;
      if (parent && parent.className !== preview &&
         !parent.isMathJax && !math[i].prefix === !namespace) array.push(math[i]);
    }
  },
  
  ProcessMathArray: function (math) {
    var i, m = math.length;
    if (m) {
      if (this.MathTagBug) {
        for (i = 0; i < m; i++) {
          if (math[i].nodeName === "MATH") {this.ProcessMathFlattened(math[i])}
                                      else {this.ProcessMath(math[i])}
        }
      } else {
        for (i = 0; i < m; i++) {this.ProcessMath(math[i])}
      }
    }
  },
  
  ProcessMath: function (math) {
    var parent = math.parentNode;
    if (!parent || parent.className === MathJax.Hub.config.preRemoveClass) return;
    var script = document.createElement("script");
    script.type = "math/mml";
    parent.insertBefore(script,math);
    if (this.AttributeBug) {
      var html = this.OuterHTML(math);
      if (this.CleanupHTML) {
        html = html.replace(/<\?import .*?>/i,"").replace(/<\?xml:namespace .*?\/>/i,"");
        html = html.replace(/&nbsp;/g,"&#xA0;");
      }
      MathJax.HTML.setScript(script,html); parent.removeChild(math);
    } else {
      var span = MathJax.HTML.Element("span"); span.appendChild(math);
      MathJax.HTML.setScript(script,span.innerHTML);
    }
    if (this.config.preview !== "none") {this.createPreview(math,script)}
  },
  
  ProcessMathFlattened: function (math) {
    var parent = math.parentNode;
    if (!parent || parent.className === MathJax.Hub.config.preRemoveClass) return;
    var script = document.createElement("script");
    script.type = "math/mml";
    parent.insertBefore(script,math);
    var mml = "", node, MATH = math;
    while (math && math.nodeName !== "/MATH") {
      node = math; math = math.nextSibling;
      mml += this.NodeHTML(node);
      node.parentNode.removeChild(node);
    }
    if (math && math.nodeName === "/MATH") {math.parentNode.removeChild(math)}
    script.text = mml + "</math>";
    if (this.config.preview !== "none") {this.createPreview(MATH,script)}
  },
  
  NodeHTML: function (node) {
    var html, i, m;
    if (node.nodeName === "#text") {
      html = this.quoteHTML(node.nodeValue);
    } else if (node.nodeName === "#comment") {
      html = "<!--" + node.nodeValue + "-->"
    } else {
      // In IE, outerHTML doesn't properly quote attributes, so quote them by hand
      // In Opera, HTML special characters aren't quoted in attributes, so quote them
      html = "<"+node.nodeName.toLowerCase();
      for (i = 0, m = node.attributes.length; i < m; i++) {
        var attribute = node.attributes[i];
        if (attribute.specified && attribute.nodeName.substr(0,10) !== "_moz-math-") {
          // Opera 11.5 beta turns xmlns into xmlns:xmlns, so put it back (*** check after 11.5 is out ***)
          html += " "+attribute.nodeName.toLowerCase().replace(/xmlns:xmlns/,"xmlns")+"=";
          var value = attribute.nodeValue; // IE < 8 doesn't properly set style by setAttributes
          if (value == null && attribute.nodeName === "style" && node.style) {value = node.style.cssText}
          html += '"'+this.quoteHTML(value)+'"';
        }
      }
      html += ">";
      // Handle internal HTML (possibly due to <semantics> annotation or missing </math>)
      if (node.outerHTML != null && node.outerHTML.match(/(.<\/[A-Z]+>|\/>)$/)) {
        for (i = 0, m = node.childNodes.length; i < m; i++)
          {html += this.OuterHTML(node.childNodes[i])}
        html += "</"+node.nodeName.toLowerCase()+">";
      }
    }
    return html;
  },
  OuterHTML: function (node) {
    if (node.nodeName.charAt(0) === "#") {return this.NodeHTML(node)}
    if (!this.AttributeBug) {return node.outerHTML}
    var html = this.NodeHTML(node);
    for (var i = 0, m = node.childNodes.length; i < m; i++)
      {html += this.OuterHTML(node.childNodes[i]);}
    html += "</"+node.nodeName.toLowerCase()+">";
    return html;
  },
  quoteHTML: function (string) {
    if (string == null) {string = ""}
    return string.replace(/&/g,"&#x26;").replace(/</g,"&lt;").replace(/>/g,"&gt;").replace(/\"/g,"&quot;");
  },
  
  createPreview: function (math,script) {
    var preview = this.config.preview;
    if (preview === "none") return;
    var isNodePreview = false;
    var previewClass = MathJax.Hub.config.preRemoveClass;
    if ((script.previousSibling||{}).className === previewClass) return;
    if (preview === "mathml") {
      isNodePreview = true;
      // mathml preview does not work with IE < 9, so fallback to alttext.
      if (this.MathTagBug) {preview = "alttext"} else {preview = math.cloneNode(true)}
    }
    if (preview === "alttext" || preview === "altimg") {
      isNodePreview = true;
      var alttext = this.filterPreview(math.getAttribute("alttext"));
      if (preview === "alttext") {
        if (alttext != null) {preview = MathJax.HTML.TextNode(alttext)} else {preview = null}
      } else {
        var src = math.getAttribute("altimg");
        if (src != null) {
          // FIXME: use altimg-valign when display="inline"?
          var style = {width: math.getAttribute("altimg-width"), height: math.getAttribute("altimg-height")};
          preview = MathJax.HTML.Element("img",{src:src,alt:alttext,style:style});
        } else {preview = null}
      }
    }
    if (preview) {
      var span;
      if (isNodePreview) {
        span = MathJax.HTML.Element("span",{className:previewClass});
        span.appendChild(preview);
      } else {
        span = MathJax.HTML.Element("span",{className:previewClass},preview);
      }
      script.parentNode.insertBefore(span,script);
    }
  },
  
  filterPreview: function (text) {return text},
  
  InitBrowser: function () {
    var test = MathJax.HTML.Element("span",{id:"<", className: "mathjax", innerHTML: "<math><mi>x</mi><mspace /></math>"});
    var html = test.outerHTML || "";
    this.AttributeBug = html !== "" && !(
      html.match(/id="&lt;"/) &&           // "<" should convert to "&lt;"
      html.match(/class="mathjax"/) &&     // IE leaves out quotes
      html.match(/<\/math>/)               // Opera 9 drops tags after self-closing tags
    );
    this.MathTagBug = test.childNodes.length > 1;    // IE < 9 flattens unknown tags
    this.CleanupHTML = MathJax.Hub.Browser.isMSIE;   // remove namespace and other added tags
  }

};

//
// We register the preprocessors with the following priorities:
// - mml2jax.js: 5
// - jsMath2jax.js: 8
// - asciimath2jax.js, tex2jax.js: 10 (default)
// See issues 18 and 484 and the other *2jax.js files.
// 
MathJax.Hub.Register.PreProcessor(["PreProcess",MathJax.Extension.mml2jax],5);
MathJax.Ajax.loadComplete("[MathJax]/extensions/mml2jax.js");
