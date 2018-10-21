/* -*- Mode: Javascript; indent-tabs-mode:nil; js-indent-level: 2 -*- */
/* vim: set ts=2 et sw=2 tw=80: */

/*************************************************************
 *
 *  MathJax/jax/output/CommonHTML/autoload/mglyph.js
 *  
 *  Implements the CommonHTML output for <mglyph> elements.
 *
 *  ---------------------------------------------------------------------
 *  
 *  Copyright (c) 2015-2018 The MathJax Consortium
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

MathJax.Hub.Register.StartupHook("CommonHTML Jax Ready",function () {
  var VERSION = "2.7.5";
  var MML = MathJax.ElementJax.mml,
      CHTML = MathJax.OutputJax.CommonHTML,
      LOCALE = MathJax.Localization;
  
  MML.mglyph.Augment({
    toCommonHTML: function (node,options) {
      var values = this.getValues("src","width","height","valign","alt");
      node = this.CHTMLcreateNode(node);
      this.CHTMLhandleStyle(node);
      this.CHTMLhandleScale(node);
      if (values.src === "") {
        var index = this.Get("index");
        this.CHTMLgetVariant();
        if (index && this.CHTMLvariant.style)
          this.CHTMLhandleText(node,String.fromCharCode(index),this.CHTMLvariant);
      } else {
        var bbox = this.CHTML;
        if (!bbox.img) bbox.img = MML.mglyph.GLYPH[values.src];
        if (!bbox.img) {
          bbox.img = MML.mglyph.GLYPH[values.src] = {img: new Image(), status: "pending"};
          bbox.img.img.onload  = MathJax.Callback(["CHTMLimgLoaded",this]);
          bbox.img.img.onerror = MathJax.Callback(["CHTMLimgError",this]);
          bbox.img.img.src = values.src;
          MathJax.Hub.RestartAfter(bbox.img.img.onload);
        }
        if (bbox.img.status !== "OK") {
          var err = MML.Error(LOCALE._(["MathML","BadMglyph"],"Bad mglyph: %1",values.src));
          err.data[0].data[0].mathsize = "75%";
          this.Append(err); err.toCommonHTML(node); this.data.pop();
          bbox.combine(err.CHTML,0,0,1);
        } else {
          var img = CHTML.addElement(node,"img",{
            isMathJax:true, src:values.src, alt:values.alt, title:values.alt
          });
          var w = values.width, h = values.height;
          var W = bbox.img.img.width/CHTML.em, H = bbox.img.img.height/CHTML.em;
          var WW = W, HH = H;
          if (w !== "") {W = this.CHTMLlength2em(w,WW); H = (WW ? W/WW * HH : 0)}
          if (h !== "") {H = this.CHTMLlength2em(h,HH); if (w === "") W = (HH ? H/HH * WW : 0)}
          img.style.width  = CHTML.Em(W); bbox.w = bbox.r = W;
          img.style.height = CHTML.Em(H); bbox.h = bbox.t = H;
          if (values.valign) {
            bbox.d = bbox.b = -this.CHTMLlength2em(values.valign,HH);
            img.style.verticalAlign = CHTML.Em(-bbox.d);
            bbox.h -= bbox.d; bbox.t = bbox.h;
          }
        }
      }
      this.CHTMLhandleSpace(node);
      this.CHTMLhandleBBox(node);
      this.CHTMLhandleColor(node);
      return node;
    },
    CHTMLimgLoaded: function (event,status) {
      if (typeof(event) === "string") status = event;
      this.CHTML.img.status = (status || "OK");
    },
    CHTMLimgError: function () {this.CHTML.img.img.onload("error")}
  },{
    GLYPH: {}    // global list of all loaded glyphs
  });
  
  MathJax.Hub.Startup.signal.Post("CommonHTML mglyph Ready");
  MathJax.Ajax.loadComplete(CHTML.autoloadDir+"/mglyph.js");
});

