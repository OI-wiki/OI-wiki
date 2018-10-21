/* -*- Mode: Javascript; indent-tabs-mode:nil; js-indent-level: 2 -*- */
/* vim: set ts=2 et sw=2 tw=80: */

/*************************************************************
 *
 *  MathJax/jax/output/CommonHTML/autoload/menclose.js
 *  
 *  Implements the CommonHTML output for <menclose> elements.
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
  
  var SVGNS = "http://www.w3.org/2000/svg";
  var ARROWX = 4, ARROWDX = 1, ARROWY = 2;

  MML.menclose.Augment({
    toCommonHTML: function (node) {
      var values = this.getValues("notation","thickness","padding");
      if (values.thickness == null) values.thickness = ".075em";
      if (values.padding == null)   values.padding   = ".2em";
      //
      //  Get DOM nodes
      //
      node = this.CHTMLdefaultNode(node,{childNodes:"mjx-box", forceChild:true});
      var child = node.firstChild, cbox = this.CHTMLbboxFor(0);
      //
      //  Get the padding and rule thickness
      //
      var p = this.CHTMLlength2em(values.padding,1/CHTML.em);   // padding for enclosure
      var t = this.CHTMLlength2em(values.thickness,1/CHTML.em); // thickness of lines
      t = Math.max(1,Math.round(t*CHTML.em))/CHTML.em;
      var SOLID = CHTML.Px(t)+" solid";
      var bb = {L:p, R:p, T:p, B:p, H:cbox.h+p, D:cbox.d+p, W:cbox.w+2*p};
      child.style.padding = CHTML.Em(p);
      //
      //  Eliminate duplicate notations.
      // 
      var notations = MathJax.Hub.SplitList(values.notation), notation = {};
      for (var i = 0, m = notations.length; i < m; i++) notation[notations[i]] = true;
      if (notation[MML.NOTATION.UPDIAGONALARROW]) delete notation[MML.NOTATION.UPDIAGONALSTRIKE];
      //
      //  Add the needed notations
      //
      for (var n in notation) {
        if (notation.hasOwnProperty(n)) {
          if (this.CHTMLnotation[n] && this.CHTMLnotation.hasOwnProperty(n))
            this.CHTMLnotation[n].call(this,child,cbox,bb,p,t,SOLID);
        }
      }
      //
      //  Adjust the bounding box
      //
      var BBOX = this.CHTML;
      BBOX.w += bb.L + bb.R; BBOX.r += BBOX.L; if (BBOX.w > BBOX.r) BBOX.r = BBOX.w;
      BBOX.h += bb.T; if (BBOX.h > BBOX.t) BBOX.t = BBOX.h;
      BBOX.d += bb.B; if (BBOX.d > BBOX.b) BBOX.b = BBOX.d;

      return node;
    },
    //
    //  The various notations and their implementations
    //
    CHTMLnotation: {
      
      /********************************************************/
      
      box: function (child,cbox,bb,p,t,SOLID) {
        p -= t;
        child.style.padding = CHTML.Em(p);
        child.style.border = SOLID;
      },

      /********************************************************/
      
      roundedbox: function (child,cbox,bb,p,t,SOLID) {
        var r = Math.min(cbox.w,cbox.h+cbox.d+2*p)/4;
        CHTML.addElement(child.parentNode,"mjx-box",{
          style: {
            padding:CHTML.Em(p-t), border:SOLID, "border-radius":CHTML.Em(r),
            height:CHTML.Em(cbox.h+cbox.d), "vertical-align":CHTML.Em(-bb.D),
            width:CHTML.Em(cbox.w), "margin-left":CHTML.Em(-bb.W)
          }
        });
      },

      /********************************************************/
      
      circle: function (child,cbox,bb,p,t,SOLID) {
        var H = bb.H, D = bb.D, W = bb.W;
        var svg = this.CHTMLsvg(child,bb,t);
        this.CHTMLsvgElement(svg.firstChild,"ellipse",{
          rx:CHTML.Px(W/2-t/2), ry:CHTML.Px((H+D)/2-t/2),
          cx:CHTML.Px(W/2),   cy:CHTML.Px((H+D)/2)
        });
      },

      /********************************************************/
      
      left: function (child,cbox,bb,p,t,SOLID) {
        child.style.borderLeft = SOLID;
        child.style.paddingLeft = CHTML.Em(p-t);
      },

      /********************************************************/
      
      right: function (child,cbox,bb,p,t,SOLID) {
        child.style.borderRight = SOLID;
        child.style.paddingRight = CHTML.Em(p-t);
      },

      /********************************************************/
      
      top: function (child,cbox,bb,p,t,SOLID) {
        child.style.borderTop = SOLID;
        child.style.paddingTop = CHTML.Em(p-t);
      },

      /********************************************************/
      
      bottom: function (child,cbox,bb,p,t,SOLID) {
        child.style.borderBottom = SOLID;
        child.style.paddingBottom = CHTML.Em(p-t);
      },

      /********************************************************/
      
      actuarial: function (child,cbox,bb,p,t,SOLID) {
        child.style.borderTop = child.style.borderRight = SOLID;
        child.style.paddingTop = child.style.paddingRight = CHTML.Em(p-t);
      },

      /********************************************************/
      
      madruwb: function (child,cbox,bb,p,t,SOLID) {
        child.style.borderBottom = child.style.borderRight = SOLID;
        child.style.paddingBottom = child.style.paddingRight = CHTML.Em(p-t);
      },

      /********************************************************/
      
      verticalstrike: function (child,cbox,bb,p,t,SOLID) {
        CHTML.addElement(child.parentNode,"mjx-box",{
          style: {
            "border-left":SOLID,
            height:CHTML.Em(bb.H+bb.D), "vertical-align":CHTML.Em(-bb.D),
            width:CHTML.Em(cbox.w/2+p-t/2), "margin-left":CHTML.Em(-cbox.w/2-p-t/2)
          }
        });
      },

      /********************************************************/
      
      horizontalstrike: function (child,cbox,bb,p,t,SOLID) {
        CHTML.addElement(child.parentNode,"mjx-box",{
          style: {
            "border-top":SOLID,
            height:CHTML.Em((bb.H+bb.D)/2-t/2), "vertical-align":CHTML.Em(-bb.D),
            width:CHTML.Em(bb.W), "margin-left":CHTML.Em(-bb.W)
          }
        });
      },

      /********************************************************/
      
      updiagonalstrike: function (child,cbox,bb,p,t,SOLID) {
        var H = bb.H, D = bb.D, W = bb.W;
        var svg = this.CHTMLsvg(child,bb,t);
        this.CHTMLsvgElement(svg.firstChild,"line",{
          x1:CHTML.Px(t/2), y1:CHTML.Px(H+D-t), x2:CHTML.Px(W-t), y2:CHTML.Px(t/2)
        });
      },

      /********************************************************/
      
      downdiagonalstrike: function (child,cbox,bb,p,t,SOLID) {
        var H = bb.H, D = bb.D, W = bb.W;
        var svg = this.CHTMLsvg(child,bb,t);
        this.CHTMLsvgElement(svg.firstChild,"line",{
          x1:CHTML.Px(t/2), y1:CHTML.Px(t/2), x2:CHTML.Px(W-t), y2:CHTML.Px(H+D-t)
        });
      },

      /********************************************************/
      
      updiagonalarrow: function (child,cbox,bb,p,t,SOLID) {
        var H = bb.H + bb.D - t, W = bb.W - t/2;
        var a = Math.atan2(H,W)*(-180/Math.PI).toFixed(3);
        var R = Math.sqrt(H*H + W*W);
        var svg = this.CHTMLsvg(child,bb,t);
        var g = this.CHTMLsvgElement(svg.firstChild,"g",{
          fill:"currentColor",
          transform:"translate("+this.CHTMLpx(t/2)+" "+this.CHTMLpx(H+t/2)+") rotate("+a+")"
        });
        var x = t * ARROWX, dx = t * ARROWDX, y = t * ARROWY;
        this.CHTMLsvgElement(g,"line",{
          x1:CHTML.Px(t/2), y1:0, x2:CHTML.Px(R-x), y2:0
        });
        this.CHTMLsvgElement(g,"path",{
          d: "M "+this.CHTMLpx(R-x)+",0 " +
             "L "+this.CHTMLpx(R-x-dx)+","+this.CHTMLpx(y) +
             "L "+this.CHTMLpx(R)+",0 " +
             "L "+this.CHTMLpx(R-x-dx)+","+this.CHTMLpx(-y),
          stroke:"none"
        });
      },

      /********************************************************/
      
      phasorangle: function (child,cbox,bb,p,t,SOLID) {
        var P = p, H = bb.H, D = bb.D;
        p = (H+D)/2;
        var W = bb.W + p - P; bb.W = W; bb.L = p;
        child.style.margin = "0 0 0 "+CHTML.Em(p-P);
        var svg = this.CHTMLsvg(child,bb,t);
        this.CHTMLsvgElement(svg.firstChild,"path",{
          d: "M "+this.CHTMLpx(p)+",1 " +
             "L 1,"+this.CHTMLpx(H+D-t)+" L "+this.CHTMLpx(W)+","+this.CHTMLpx(H+D-t)
        });
      },

      /********************************************************/
      
      longdiv: function (child,cbox,bb,p,t,SOLID) {
        bb.W += 1.5*p; bb.L += 1.5*p;
        var H = bb.H, D = bb.D, W = bb.W;
        child.style.margin = "0 0 0 "+CHTML.Em(1.5*p);
        var svg = this.CHTMLsvg(child,bb,t);
        this.CHTMLsvgElement(svg.firstChild,"path",{
          d: "M "+this.CHTMLpx(W)+",1 L 1,1 "+
             "a"+this.CHTMLpx(p)+","+this.CHTMLpx((H+D)/2-t/2)+" 0 0,1 1,"+this.CHTMLpx(H+D-1.5*t)
        });
      },

      /********************************************************/
      
      radical: function (child,cbox,bb,p,t,SOLID) {
        bb.W += 1.5*p; bb.L += 1.5*p;
        var H = bb.H, D = bb.D, W = bb.W;
        child.style.margin = "0 0 0 "+CHTML.Em(1.5*p);
        var svg = this.CHTMLsvg(child,bb,t);
        this.CHTMLsvgElement(svg.firstChild,"path",{
          d: "M 1,"+this.CHTMLpx(.6*(H+D)) +
             " L "+this.CHTMLpx(p)+","+this.CHTMLpx(H+D) +
             " L "+this.CHTMLpx(2*p)+",1 L "+this.CHTMLpx(W)+",1"
        });
      }

      /********************************************************/
      
    },
    
    //
    //  Pixels with no "px"
    //
    CHTMLpx: function (m) {
      m *= CHTML.em;
      if (Math.abs(m) < .1) return "0";
      return m.toFixed(1).replace(/\.0$/,"");
    },
    
    //
    //  Create the SVG element and position it over the 
    //  contents
    //
    CHTMLsvg: function (node,bbox,t) {
      if (!svg) {
        var svg = document.createElementNS(SVGNS,"svg");
        if (svg.style) {
          svg.style.width = CHTML.Em(bbox.W);
          svg.style.height = CHTML.Em(bbox.H+bbox.D);
          svg.style.verticalAlign = CHTML.Em(-bbox.D);
          svg.style.marginLeft = CHTML.Em(-bbox.W);
        }
        this.CHTMLsvgElement(svg,"g",{"stroke-width":CHTML.Px(t)});
        node.parentNode.appendChild(svg);
      }
      return svg;
    },
    //
    //  Add an SVG element to the given svg node
    //
    CHTMLsvgElement: function (svg,type,def) {
      var obj = document.createElementNS(SVGNS,type); obj.isMathJax = true;
      if (def) {for (var id in def) {if (def.hasOwnProperty(id)) {obj.setAttributeNS(null,id,def[id].toString())}}}
      svg.appendChild(obj);
      return obj;
    }
  });
  
  //
  //  Just use default toCommonHTML for EI8
  //
  if (!document.createElementNS) delete MML.menclose.prototype.toCommonHTML;
  
  MathJax.Hub.Startup.signal.Post("CommonHTML menclose Ready");
  MathJax.Ajax.loadComplete(CHTML.autoloadDir+"/menclose.js");
});

