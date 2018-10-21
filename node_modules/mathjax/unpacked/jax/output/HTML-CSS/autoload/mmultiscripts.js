/* -*- Mode: Javascript; indent-tabs-mode:nil; js-indent-level: 2 -*- */
/* vim: set ts=2 et sw=2 tw=80: */

/*************************************************************
 *
 *  MathJax/jax/output/HTML-CSS/autoload/mmultiscripts.js
 *  
 *  Implements the HTML-CSS output for <mmultiscripts> elements.
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

MathJax.Hub.Register.StartupHook("HTML-CSS Jax Ready",function () {
  var VERSION = "2.7.5";
  var MML = MathJax.ElementJax.mml,
      HTMLCSS = MathJax.OutputJax["HTML-CSS"];
  
  MML.mmultiscripts.Augment({
    toHTML: function (span,HW,D) {
      span = this.HTMLcreateSpan(span); var scale = this.HTMLgetScale();
      var stack = HTMLCSS.createStack(span), values;
      var base = HTMLCSS.createBox(stack);
      if (this.data[this.base]) {
        var child = this.data[this.base].toHTML(base);
        if (D != null) {this.data[this.base].HTMLstretchV(base,HW,D)}
        else if (HW != null) {this.data[this.base].HTMLstretchH(base,HW)}
        HTMLCSS.Measured(child,base);
      } else {base.bbox = this.HTMLzeroBBox()}
      var x_height = HTMLCSS.TeX.x_height * scale,
          s = HTMLCSS.TeX.scriptspace * scale * .75;  // FIXME: .75 can be removed when IC is right?

      var BOX = this.HTMLgetScripts(stack,s);
      var sub = BOX[0], sup = BOX[1], presub = BOX[2], presup = BOX[3];

      //
      // <mmultiscripts> children other than the base can be <none/>,
      // <mprescripts/>, <mrow></mrow> etc so try to get HTMLgetScale from the
      // first element with a spanID. See issue 362.
      //
      var sscale = scale;
      for (var i = 1; i < this.data.length; i++) {
        if (this.data[i] && this.data[i].spanID) {
          sscale = this.data[i].HTMLgetScale();
          break;
        }
      }

      var q = HTMLCSS.TeX.sup_drop * sscale, r = HTMLCSS.TeX.sub_drop * sscale;
      var u = base.bbox.h - q, v = base.bbox.d + r, delta = 0, p;
      if (base.bbox.ic) {delta = base.bbox.ic}
      if (this.data[this.base] &&
         (this.data[this.base].type === "mi" || this.data[this.base].type === "mo")) {
        if (HTMLCSS.isChar(this.data[this.base].data.join("")) && base.bbox.scale === 1 &&
            !this.data[this.base].Get("largeop")) {u = v = 0}
      }
      var min = this.getValues("subscriptshift","superscriptshift"), mu = this.HTMLgetMu(span);
      min.subscriptshift   = (min.subscriptshift === ""   ? 0 : HTMLCSS.length2em(min.subscriptshift,mu));
      min.superscriptshift = (min.superscriptshift === "" ? 0 : HTMLCSS.length2em(min.superscriptshift,mu));

      var dx = 0;
      if (presub) {dx = presub.bbox.w+delta} else if (presup) {dx = presup.bbox.w-delta}
      if (dx < 0) {dx = 0};
      HTMLCSS.placeBox(base,dx,0);

      if (!sup && !presup) {
        v = Math.max(v,HTMLCSS.TeX.sub1*scale,min.subscriptshift);
        if (sub)    {v = Math.max(v,sub.bbox.h-(4/5)*x_height)}
        if (presub) {v = Math.max(v,presub.bbox.h-(4/5)*x_height)}
        if (sub)    {HTMLCSS.placeBox(sub,dx+base.bbox.w+s-delta,-v)}
        if (presub) {HTMLCSS.placeBox(presub,0,-v)}
      } else {
        if (!sub && !presub) {
          values = this.getValues("displaystyle","texprimestyle");
          p = HTMLCSS.TeX[(values.displaystyle ? "sup1" : (values.texprimestyle ? "sup3" : "sup2"))];
          u = Math.max(u,p*scale,min.superscriptshift);
          if (sup)    {u = Math.max(u,sup.bbox.d+(1/4)*x_height)}
          if (presup) {u = Math.max(u,presup.bbox.d+(1/4)*x_height)}
          if (sup)    {HTMLCSS.placeBox(sup,dx+base.bbox.w+s,u)}
          if (presup) {HTMLCSS.placeBox(presup,0,u)}
        } else {
          v = Math.max(v,HTMLCSS.TeX.sub2*scale);
          var t = HTMLCSS.TeX.rule_thickness * scale;
          var h = (sub||presub).bbox.h, d = (sup||presup).bbox.d;
          if (presub) {h = Math.max(h,presub.bbox.h)}
          if (presup) {d = Math.max(d,presup.bbox.d)}
          if ((u - d) - (h - v) < 3*t) {
            v = 3*t - u + d + h; q = (4/5)*x_height - (u - d);
            if (q > 0) {u += q; v -= q}
          }
          u = Math.max(u,min.superscriptshift); v = Math.max(v,min.subscriptshift);
          if (sup)    {HTMLCSS.placeBox(sup,dx+base.bbox.w+s,u)}
          if (presup) {HTMLCSS.placeBox(presup,dx+delta-presup.bbox.w,u)}
          if (sub)    {HTMLCSS.placeBox(sub,dx+base.bbox.w+s-delta,-v)}
          if (presub) {HTMLCSS.placeBox(presub,dx-presub.bbox.w,-v)}
        }
      }
      this.HTMLhandleSpace(span);
      this.HTMLhandleColor(span);
      var bbox = span.bbox;
      bbox.dx = dx; bbox.s = s; bbox.u = u; bbox.v = v; bbox.delta = delta;
      bbox.px = dx+base.bbox.w;
      return span;
    },
    HTMLgetScripts: function (stack,s) {
      var sup, sub, BOX = [];
      var i = 1, m = this.data.length, W = 0;
      for (var k = 0; k < 4; k += 2) {
        while (i < m && (this.data[i]||{}).type !== "mprescripts") {
          var box = [null,null,null,null];
          for (var j = k; j < k+2; j++) {
            if (this.data[i] && this.data[i].type !== "none" && this.data[i].type !== "mprescripts") {
              if (!BOX[j]) {
                BOX[j] = HTMLCSS.createBox(stack); BOX[j].bbox = this.HTMLemptyBBox({});
                if (W) {HTMLCSS.createBlank(BOX[j],W); BOX[j].bbox.w = BOX[j].bbox.rw = W}
              }
              box[j] = this.data[i].toHTML(BOX[j]);
            } else {
              box[j] = MathJax.HTML.Element("span",{bbox:this.HTMLemptyBBox({})});
            }
            if ((this.data[i]||{}).type !== "mprescripts") i++;
          }
          var isPre = (k === 2);
          sub = BOX[k]; sup = BOX[k+1];
          if (sub && sup) {
            var w = box[k+1].bbox.w - box[k].bbox.w;
            if (w > 0) {
              if (isPre) {
                this.HTMLmoveColor(box[k],w,1);
                BOX[k].w += w;
              } else {
                HTMLCSS.createBlank(sub,w);
              }
            } else if (w < 0) {
              if (isPre) {
                this.HTMLmoveColor(box[k+1],-w,-1);
                BOX[k+1].w += -w;
              } else {
                HTMLCSS.createBlank(sup,-w);
              }
            }
            this.HTMLcombineBBoxes(box[k],sub.bbox);
            this.HTMLcombineBBoxes(box[k+1],sup.bbox);
            if (w > 0) {
              sub.bbox.w = sup.bbox.w;
              sub.bbox.rw = Math.max(sub.bbox.w,sub.bbox.rw);
            } else if (w < 0) {
              sup.bbox.w = sub.bbox.w;
              sup.bbox.rw = Math.max(sup.bbox.w,sup.bbox.rw);
            }
          } else {
            if (sub) this.HTMLcombineBBoxes(box[k],sub.bbox);
            if (sup) this.HTMLcombineBBoxes(box[k+1],sup.bbox);
          }
          if (sub) {W = sub.bbox.w} else if (sup) {W = sup.bbox.w}
        }
        i++; W = 0;
      }
      for (j = 0; j < 4; j++) {
        if (BOX[j]) {
          BOX[j].bbox.w += s;
          BOX[j].bbox.rw = Math.max(BOX[j].bbox.w,BOX[j].bbox.rw);
          BOX[j].bbox.name = (["sub","sup","presub","presup"])[j];
          this.HTMLcleanBBox(BOX[j].bbox);
        }
      }
      return BOX;
    },
    HTMLmoveColor: function (box,w,sign) {
      var W = w/(box.scale||1);
      box.style.paddingLeft = HTMLCSS.Em(W);
      var color = box.previousSibling;
      if (color && (color.id||"").match(/^MathJax-Color-/)) {
        color.style.marginLeft = HTMLCSS.Em(W+parseFloat(color.style.marginLeft));
        color.style.marginRight = HTMLCSS.Em(sign*(W-parseFloat(color.style.marginRight)));
      }
      
    },
    HTMLstretchH: MML.mbase.HTMLstretchH,
    HTMLstretchV: MML.mbase.HTMLstretchV
  });
  
  MathJax.Hub.Startup.signal.Post("HTML-CSS mmultiscripts Ready");
  MathJax.Ajax.loadComplete(HTMLCSS.autoloadDir+"/mmultiscripts.js");

});

