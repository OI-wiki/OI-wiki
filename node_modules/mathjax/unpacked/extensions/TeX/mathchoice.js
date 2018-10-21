/* -*- Mode: Javascript; indent-tabs-mode:nil; js-indent-level: 2 -*- */
/* vim: set ts=2 et sw=2 tw=80: */

/*************************************************************
 *
 *  MathJax/extensions/TeX/mathchoice.js
 *  
 *  Implements the \mathchoice macro (rarely used)
 *
 *  ---------------------------------------------------------------------
 *  
 *  Copyright (c) 2009-2018 The MathJax Consortium
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

MathJax.Hub.Register.StartupHook("TeX Jax Ready",function () {
  var VERSION = "2.7.5";

  var MML = MathJax.ElementJax.mml;
  var TEX = MathJax.InputJax.TeX;
  var TEXDEF = TEX.Definitions;
  
  TEXDEF.Add({macros: {mathchoice: 'MathChoice'}},null,true);

  TEX.Parse.Augment({
    MathChoice: function (name) {
      var D  = this.ParseArg(name),
          T  = this.ParseArg(name),
          S  = this.ParseArg(name),
          SS = this.ParseArg(name);
      this.Push(MML.TeXmathchoice(D,T,S,SS));
    }
  });
  
  MML.TeXmathchoice = MML.mbase.Subclass({
    type: "TeXmathchoice", notParent: true,
    choice: function () {
      if (this.selection != null) return this.selection;
      if (this.choosing) return 2; // prevent infinite loops:  see issue #1151
      this.choosing = true;
      var selection = 0, values = this.getValues("displaystyle","scriptlevel");
      if (values.scriptlevel > 0) {selection = Math.min(3,values.scriptlevel+1)}
        else {selection = (values.displaystyle ? 0 : 1)}
      // only cache the result if we are actually in place in a <math> tag.
      var node = this.inherit; while (node && node.type !== "math") node = node.inherit;
      if (node) this.selection = selection;
      this.choosing = false;
      return selection;
    },
    selected: function () {return this.data[this.choice()]},
    setTeXclass: function (prev) {return this.selected().setTeXclass(prev)},
    isSpacelike: function () {return this.selected().isSpacelike()},
    isEmbellished: function () {return this.selected().isEmbellished()},
    Core: function () {return this.selected()},
    CoreMO: function () {return this.selected().CoreMO()},
    toHTML: function (span) {
      span = this.HTMLcreateSpan(span);
      span.bbox = this.Core().toHTML(span).bbox;
      // Firefox doesn't correctly handle a span with a negatively sized content,
      //   so move marginLeft to main span (this is a hack to get \iiiint to work).
      //   FIXME:  This is a symptom of a more general problem with Firefox, and
      //           there probably needs to be a more general solution (e.g., modifying
      //           HTMLhandleSpace() to get the width and adjust the right margin to
      //           compensate for negative-width contents)
      if (span.firstChild && span.firstChild.style.marginLeft) {
        span.style.marginLeft = span.firstChild.style.marginLeft;
        span.firstChild.style.marginLeft = "";
      }
      return span;
    },
    toSVG: function () {
      var svg = this.Core().toSVG();
      this.SVGsaveData(svg);
      return svg;
    },
    toCommonHTML: function (node) {
      node = this.CHTMLcreateNode(node);
      this.CHTMLhandleStyle(node);
      this.CHTMLhandleColor(node);
      this.CHTMLaddChild(node,this.choice(),{});
      return node;
    },
    toPreviewHTML: function(span) {
      span = this.PHTMLcreateSpan(span);
      this.PHTMLhandleStyle(span);
      this.PHTMLhandleColor(span);
      this.PHTMLaddChild(span,this.choice(),{});
      return span;
    }
  });
  
  MathJax.Hub.Startup.signal.Post("TeX mathchoice Ready");
  
});

MathJax.Ajax.loadComplete("[MathJax]/extensions/TeX/mathchoice.js");
