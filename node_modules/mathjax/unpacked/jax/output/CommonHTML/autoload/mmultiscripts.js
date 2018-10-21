/* -*- Mode: Javascript; indent-tabs-mode:nil; js-indent-level: 2 -*- */
/* vim: set ts=2 et sw=2 tw=80: */

/*************************************************************
 *
 *  MathJax/jax/output/CommonHTML/autoload/mmultiscripts.js
 *  
 *  Implements the CommonHTML output for <mmultiscripts> elements.
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
      CHTML = MathJax.OutputJax.CommonHTML;

  MML.mmultiscripts.Augment({
    toCommonHTML: function (node,options) {
      var stretch = (options||{}).stretch;
      if (!stretch) {
        node = this.CHTMLcreateNode(node);
        this.CHTMLhandleStyle(node);
        this.CHTMLgetVariant();
        this.CHTMLhandleScale(node);
      }
      CHTML.BBOX.empty(this.CHTML);

      //
      //  Get base node
      //
      var base, bbox;
      if (stretch) {
        base = CHTML.getNode(node,"mjx-base");
      } else {
        this.CHTMLaddChild(node,0,{type:"mjx-base", noBBox:true, forceChild:true});
        base = node.firstChild;
      }
      bbox = this.CHTMLbboxFor(0);
      if (bbox.ic) {
          bbox.R -= bbox.ic;         // remove IC (added by mo and mi)
          if (!stretch) base.style.marginRight = CHTML.Em(-bbox.ic);
          delta = 1.3*bbox.ic + .05; // make faked IC be closer to expeted results
      }
      
      //
      //  Collect scripts into horizontal boxes and add them into the node
      //
      var BOX = {}, BBOX = {};
      this.CHTMLgetScripts(BOX,BBOX,stretch,node);
      var sub = BOX.sub, sup = BOX.sup, presub = BOX.presub, presup = BOX.presup;
      var sbox = BBOX.sub, Sbox = BBOX.sup, pbox = BBOX.presub, Pbox = BBOX.presup;
      if (!stretch) this.CHTMLaddBoxes(node,base,BOX);
      
      //
      //  Get the initial values for the variables
      //
      var values = this.getValues("scriptlevel","scriptsizemultiplier");
      var sscale = (this.Get("scriptlevel") < 3 ? values.scriptsizemultiplier : 1);
      var ex = CHTML.TEX.x_height, s = CHTML.TEX.scriptspace;
      var q = CHTML.TEX.sup_drop * sscale, r = CHTML.TEX.sub_drop * sscale;
      var u = bbox.h - q, v = bbox.d + r, delta = 0, p;
      var bmml = this.data[this.base];
      if (bmml && (bmml.type === "mi" || bmml.type === "mo")) {
        if (CHTML.isChar(bmml.data.join("")) && bbox.rscale === 1 && !bbox.sH &&
          !bmml.Get("largeop")) {u = v = 0}
      }
      values = this.getValues("displaystyle","subscriptshift","superscriptshift","texprimestyle");
      values.subscriptshift   = (values.subscriptshift === ""   ? 0 : this.CHTMLlength2em(values.subscriptshift));
      values.superscriptshift = (values.superscriptshift === "" ? 0 : this.CHTMLlength2em(values.superscriptshift));

      var dx = (presub ? s+pbox.w : presup ? s+Pbox.w-delta : 0);
      this.CHTML.combine(bbox,dx,0); var x = this.CHTML.w;

      //
      //  Place the scripts as needed
      //
      if (!sup && !presup) {
        v = Math.max(v,CHTML.TEX.sub1,values.subscriptshift);
        if (sub)    v = Math.max(v,sbox.h-(4/5)*ex);
        if (presub) v = Math.max(v,pbox.h-(4/5)*ex);
        if (sub)    this.CHTMLplaceSubOnly(sub,sbox,x,v,s);
        if (presub) this.CHTMLplacePresubOnly(presub,pbox,v,s);
      } else {
        if (!sub && !presub) {
          p = CHTML.TEX[(values.displaystyle ? "sup1" : (values.texprimestyle ? "sup3" : "sup2"))];
          u = Math.max(u,p,values.superscriptshift);
          if (sup)    u = Math.max(u,Sbox.d+(1/4)*ex);
          if (presup) u = Math.max(u,Pbox.d+(1/4)*ex);
          if (sup)    this.CHTMLplaceSupOnly(sup,Sbox,x,delta,u,s);
          if (presup) this.CHTMLplacePresupOnly(presup,Pbox,delta,u,s);
        } else {
          v = Math.max(v,CHTML.TEX.sub2);
          var t = CHTML.TEX.rule_thickness;
          var h = (sbox||pbox).h, d = (Sbox||Pbox).d;
          if (presub) h = Math.max(h,pbox.h);
          if (presup) d = Math.max(d,Pbox.d);
          if ((u - d) - (h - v) < 3*t) {
            v = 3*t - u + d + h; q = (4/5)*ex - (u - d);
            if (q > 0) {u += q; v -= q}
          }
          u = Math.max(u,values.superscriptshift);
          v = Math.max(v,values.subscriptshift);
          if (sup) {
            if (sub) {this.CHTMLplaceSubSup(sub,sbox,sup,Sbox,x,delta,u,v,s)}
                else {this.CHTMLplaceSupOnly(sup,Sbox,x,delta,u,s)}
          } else if (sub) {this.CHTMLplaceSubOnly(sub,sbox,x,v,s)}
          if (presup) {
            if (presub) {this.CHTMLplacePresubPresup(presub,pbox,presup,Pbox,delta,u,v,s)}
                   else {this.CHTMLplacePresupOnly(presup,Pbox,delta,u,s)}
          } else if (presub) {this.CHTMLplacePresubOnly(presub,pbox,v,s)}
        }
      }
      this.CHTML.clean();
      this.CHTMLhandleSpace(node);
      this.CHTMLhandleBBox(node);
      this.CHTMLhandleColor(node);
      return node;
    },
    //
    //  Get the subscript, superscript, presubscript, and presuperscript
    //  boxes, with proper spacing, and computer their bounding boxes.
    //
    CHTMLgetScripts: function (BOX,BBOX,stretch,node) {
      if (stretch) {
        BOX.sub = CHTML.getNode(node,"mjx-sub");
        BOX.sup = CHTML.getNode(node,"mjx-sup");
        BOX.presub = CHTML.getNode(node,"mjx-presub");
        BOX.presup = CHTML.getNode(node,"mjx-presup");
        BBOX.sub = this.CHTMLbbox.sub;
        BBOX.sup = this.CHTMLbbox.sup;
        BBOX.presub = this.CHTMLbbox.presub;
        BBOX.presup = this.CHTMLbbox.presup;
        return;
      }
      this.CHTMLbbox = BBOX;  // save for when stretched
      var state = {i:1, w:0, BOX:BOX, BBOX:BBOX}, m = this.data.length;
      var sub = "sub", sup = "sup";
      while (state.i < m) {
        if ((this.data[state.i]||{}).type === "mprescripts") {
          state.i++; state.w = 0;
          sub = "presub"; sup = "presup";
        } else {
          var sbox = this.CHTMLaddScript(sub,state,node);
          var Sbox = this.CHTMLaddScript(sup,state,node);
          var w = Math.max((sbox ? sbox.rscale*sbox.w : 0),(Sbox ? Sbox.rscale*Sbox.w : 0));
          this.CHTMLpadScript(sub,w,sbox,state);
          this.CHTMLpadScript(sup,w,Sbox,state);
          state.w += w;
        }
      }
      if (BBOX.sub) BBOX.sub.clean();
      if (BBOX.sup) BBOX.sup.clean();
      if (BBOX.presub) BBOX.presub.clean();
      if (BBOX.presup) BBOX.presup.clean();
    },
    //
    //  Add a script to the proper box, creating the box if needed,
    //  and padding the box to account for any <none/> elements.
    //  Return the bounding box for the script for later use.
    //
    CHTMLaddScript: function (type,state,node) {
      var BOX, BBOX, data = this.data[state.i];
      if (data && data.type !== "none" && data.type !== "mprescripts") {
        BOX = state.BOX[type];
        if (!BOX) {
          //
          //  Add the box to the node temporarily so that it is in the DOM
          //  (so that CHTMLnodeElement() can be used in the toCommonHTML() below).
          //  See issue #1480.
          //
          BOX = state.BOX[type] = CHTML.addElement(node,"mjx-"+type);
          BBOX = state.BBOX[type] = CHTML.BBOX.empty();
          if (state.w) {
            BOX.style.paddingLeft = CHTML.Em(state.w);
            BBOX.w = BBOX.r = state.w; BBOX.x = state.w;
          }
        }
        data.toCommonHTML(BOX);
        BBOX = data.CHTML;
      }
      if (data && data.type !== "mprescripts") state.i++;
      return BBOX;
    },
    //
    //  Add padding to the script box to make match the width of the
    //  super- or subscript that is above or below it, and adjust the
    //  bounding box for the script row.  If these are pre-scripts,
    //  right-justify the scripts, otherwise, left-justify them.
    //
    CHTMLpadScript: function (type,w,bbox,state) {
      if (!bbox) bbox = {w:0, fake:1, rscale:1};
      var BBOX = state.BBOX[type], dx = 0, dw = 0;
      if (BBOX) {
        if (bbox.rscale*bbox.w < w) {
          var BOX = state.BOX[type]; dw = w-bbox.rscale*bbox.w;
          var space = CHTML.Element("mjx-spacer",{style:{width:CHTML.Em(dw)}});
          if (type.substr(0,3) === "pre" && !bbox.fake) {
            BOX.insertBefore(space,BOX.lastChild);
            dx = dw; dw = 0;
          } else {
            BOX.appendChild(space);
          }
        }
        if (bbox.fake) {BBOX.w += dx} else {BBOX.combine(bbox,BBOX.w+dx,0)}
        BBOX.w += dw;
      }
    },
    //
    //  Add the boxes into the main node, creating stacks when needed
    //
    CHTMLaddBoxes: function (node,base,BOX) {
      var sub = BOX.sub, sup = BOX.sup, presub = BOX.presub, presup = BOX.presup;
      if (presub && presup) {
        var prestack = CHTML.Element("mjx-prestack"); node.insertBefore(prestack,base);
        prestack.appendChild(presup); prestack.appendChild(presub);
      } else {
        if (presub) node.insertBefore(presub,base);
        if (presup) node.insertBefore(presup,base);
      }
      if (sub && sup) {
        var stack = CHTML.addElement(node,"mjx-stack");
        stack.appendChild(sup); stack.appendChild(sub);
      } else {
        if (sub) node.appendChild(sub);
        if (sup) node.appendChild(sup);
      }
    },
    //
    //  Handle positioning the various scripts
    //
    CHTMLplaceSubOnly: function (sub,sbox,x,v,s) {
      sub.style.verticalAlign = CHTML.Em(-v);
      sub.style.marginRight = CHTML.Em(s); sbox.w += s;
      this.CHTML.combine(sbox,x,-v);
    },
    CHTMLplaceSupOnly: function (sup,Sbox,x,delta,u,s) {
      sup.style.verticalAlign = CHTML.Em(u);
      sup.style.paddingLeft = CHTML.Em(delta);
      sup.style.paddingRight = CHTML.Em(s); Sbox.w += s;
      this.CHTML.combine(Sbox,x+delta,u);
    },
    CHTMLplaceSubSup: function (sub,sbox,sup,Sbox,x,delta,u,v,s) {
      sub.style.paddingRight = CHTML.Em(s); sbox.w += s;
      sup.style.paddingBottom = CHTML.Em(u+v-Sbox.d-sbox.h);
      sup.style.paddingLeft = CHTML.Em(delta+(Sbox.x||0));
      sup.style.paddingRight = CHTML.Em(s); Sbox.w += s;
      sup.parentNode.style.verticalAlign = CHTML.Em(-v);
      this.CHTML.combine(sbox,x,-v);
      this.CHTML.combine(Sbox,x+delta,u);
    },
    CHTMLplacePresubOnly: function (presub,pbox,v,s) {
      presub.style.verticalAlign = CHTML.Em(-v);
      presub.style.marginLeft = CHTML.Em(s);
      this.CHTML.combine(pbox,s,-v);
    },
    CHTMLplacePresupOnly: function (presup,Pbox,delta,u,s) {
      presup.style.verticalAlign = CHTML.Em(u);
      presup.style.paddingLeft = CHTML.Em(s);
      presup.style.paddingRight = CHTML.Em(-delta);
      this.CHTML.combine(Pbox,s,u);
    },
    CHTMLplacePresubPresup: function (presub,pbox,presup,Pbox,delta,u,v,s) {
      presub.style.paddingLeft = CHTML.Em(s);
      presup.style.paddingBottom = CHTML.Em(u+v-Pbox.d-pbox.h);
      presup.style.paddingLeft = CHTML.Em(delta+s+(Pbox.x||0));
      presup.style.paddingRight = CHTML.Em(-delta);
      presup.parentNode.style.verticalAlign = CHTML.Em(-v);
      this.CHTML.combine(pbox,s,-v);
      this.CHTML.combine(Pbox,s+delta,u);
    },
    //
    //  Handle stretchy bases
    //
    CHTMLstretchH: MML.mbase.CHTMLstretchH,
    CHTMLstretchV: MML.mbase.CHTMLstretchV
  });
  
  MathJax.Hub.Startup.signal.Post("CommonHTML mmultiscripts Ready");
  MathJax.Ajax.loadComplete(CHTML.autoloadDir+"/mmultiscripts.js");
});

