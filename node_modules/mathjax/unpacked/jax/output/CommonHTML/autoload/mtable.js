/* -*- Mode: Javascript; indent-tabs-mode:nil; js-indent-level: 2 -*- */
/* vim: set ts=2 et sw=2 tw=80: */

/*************************************************************
 *
 *  MathJax/jax/output/CommonHTML/autoload/mtable.js
 *  
 *  Implements the CommonHTML output for <mtable> elements.
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
      CONFIG = MathJax.Hub.config,
      CHTML = MathJax.OutputJax.CommonHTML,
      SPLIT = MathJax.Hub.SplitList;
  
  var LABEL = -1,
      BIGDIMEN = 1000000;

  MML.mtable.Augment({
    toCommonHTML: function (node) {
      //
      //  Create the table nodes and put them in a table
      //  (so that its bottom is on the baseline, rather than aligned on the top row)
      //
      var state = {rows:[], labels:[], labeled: false};
      node = this.CHTMLdefaultNode(node,{noBBox:true, childOptions:state});
      var table = CHTML.Element("mjx-table");
      while (node.firstChild) table.appendChild(node.firstChild);
      node.appendChild(table);
      //
      //  Get the table attributes
      //
      var values = this.getValues("columnalign","rowalign","columnspacing","rowspacing",
                                  "columnwidth","equalcolumns","equalrows",
                                  "columnlines","rowlines","frame","framespacing",
                                  "align","width","side","minlabelspacing","useHeight");
      var t = CHTML.TEX.min_rule_thickness/CHTML.em;
      state.t = CHTML.Px(t*this.CHTML.scale,1);
      //
      //  Create the table
      //
      this.CHTMLgetBoxSizes(values,state);
      this.CHTMLgetAttributes(values,state);
      this.CHTMLadjustCells(values,state);
      if (values.frame) table.style.border = state.t+" "+values.frame;
      this.CHTMLalignV(values,state,node);
      this.CHTMLcolumnWidths(values,state,node);
      this.CHTMLstretchCells(values,state);
      if (state.labeled) this.CHTMLaddLabels(values,state,node,table);
      //
      //  Set the bounding box (ignores overlapping outside of the table)
      //
      var BBOX = this.CHTML;
      BBOX.w = BBOX.r = state.R;
      BBOX.h = BBOX.t = state.T-state.B;
      BBOX.d = BBOX.b = state.B;
      if (!values.frame && !BBOX.pwidth) {
        node.style.padding = "0 "+CHTML.Em(1/6);
        BBOX.L = BBOX.R = 1/6;
      }
      //
      //  Add any needed space and color
      //
      this.CHTMLhandleSpace(node);
      this.CHTMLhandleBBox(node);
      this.CHTMLhandleColor(node);
      //
      //  Return the completed node
      //
      return node;
    },
    //
    //  Get the natural height, depth, and widths of the rows and columns
    //
    CHTMLgetBoxSizes: function (values,state) {
      var LH = CHTML.FONTDATA.lineH * values.useHeight,
          LD = CHTML.FONTDATA.lineD * values.useHeight;
      var H = [], D = [], W = [], J = -1, i, m;
      for (i = 0, m = this.data.length; i < m; i++) {
        var  row = this.data[i], s = (row.type === "mtr" ? 0 : LABEL);
        H[i] = LH; D[i] = LD;
        for (var j = s, M = row.data.length + s; j < M; j++) {
          if (W[j] == null) {W[j] = -BIGDIMEN; if (j > J) J = j}
          var cbox = row.data[j-s].CHTML;
          if (cbox.h > H[i]) H[i] = cbox.h;
          if (cbox.d > D[i]) D[i] = cbox.d;
          if (cbox.w > W[j]) W[j] = cbox.w;
        }
      }
      if (values.equalrows) {
        state.HD = true;
        var HH = Math.max.apply(Math,H);
        var DD = Math.max.apply(Math,D);
        for (i = 0, m = H.length; i < m; i++) {H[i] = HH; D[i] = DD}
      }
      state.H = H; state.D = D; state.W = W, state.J = J;
    },
    //
    //  Pad the spacing and alignment attributes to match the size of the table
    //
    CHTMLgetAttributes: function (values,state) {
      var CSPACE = SPLIT(values.columnspacing),
          RSPACE = SPLIT(values.rowspacing),
          CALIGN = SPLIT(values.columnalign),
          RALIGN = SPLIT(values.rowalign),
          CLINES = SPLIT(values.columnlines),
          RLINES = SPLIT(values.rowlines),
          CWIDTH = SPLIT(values.columnwidth),
          RCALIGN = [], i, m, J = state.J, M = state.rows.length-1;
      for (i = 0, m = CSPACE.length; i < m; i++) CSPACE[i] = this.CHTMLlength2em(CSPACE[i]);
      for (i = 0, m = RSPACE.length; i < m; i++) RSPACE[i] = this.CHTMLlength2em(RSPACE[i]);
      while (CSPACE.length <  J) CSPACE.push(CSPACE[CSPACE.length-1]);
      while (CALIGN.length <= J) CALIGN.push(CALIGN[CALIGN.length-1]);
      while (CLINES.length <  J) CLINES.push(CLINES[CLINES.length-1]);
      while (CWIDTH.length <= J) CWIDTH.push(CWIDTH[CWIDTH.length-1]);
      while (RSPACE.length <  M) RSPACE.push(RSPACE[RSPACE.length-1]);
      while (RALIGN.length <= M) RALIGN.push(RALIGN[RALIGN.length-1]);
      while (RLINES.length <  M) RLINES.push(RLINES[RLINES.length-1]);
      CALIGN[LABEL] = (values.side.substr(0,1) === "l" ? "left" : "right");
      //
      //  Override aligment data based on row-specific attributes
      //
      for (i = 0; i <= M; i++) {
        var row = this.data[i]; RCALIGN[i] = [];
        if (row.rowalign) RALIGN[i] = row.rowalign;
        if (row.columnalign) {
          RCALIGN[i] = SPLIT(row.columnalign);
          while (RCALIGN[i].length <= J) RCALIGN[i].push(RCALIGN[i][RCALIGN[i].length-1]);
        }
      }
      //
      //  Handle framespacing
      //
      var FSPACE = SPLIT(values.framespacing);
      if (FSPACE.length != 2) FSPACE = SPLIT(this.defaults.framespacing);
      FSPACE[0] = Math.max(0,this.CHTMLlength2em(FSPACE[0]));
      FSPACE[1] = Math.max(0,this.CHTMLlength2em(FSPACE[1]));
      if (values.columnlines.replace(/none/g,"").replace(/ /g,"") !== "" ||
          values.rowlines.replace(/none/g,"").replace(/ /g,"") !== "") values.fspace = true;
      //
      //  Pad arrays so that final column can be treated as all the others
      //
      if (values.frame === MML.LINES.NONE) delete values.frame; else values.fspace = true;
      if (values.frame) {
        FSPACE[0] = Math.max(0,FSPACE[0]);
        FSPACE[1] = Math.max(0,FSPACE[1]);
      }
      if (values.fspace) {
        CSPACE[J] = FSPACE[0]; RSPACE[M] = FSPACE[1];
      } else {
        CSPACE[J] = RSPACE[M] = 0;
      }
      CLINES[J] = RLINES[M] = MML.LINES.NONE;
      //
      //  Save everything in the state
      //
      state.CSPACE = CSPACE; state.RSPACE = RSPACE;
      state.CALIGN = CALIGN; state.RALIGN = RALIGN;
      state.CLINES = CLINES; state.RLINES = RLINES;
      state.CWIDTH = CWIDTH; state.RCALIGN = RCALIGN;
      state.FSPACE = FSPACE;
    },
    //
    //  Add styles to cells to handle borders, spacing, alignment, etc.
    //
    CHTMLadjustCells: function(values,state) {
      var ROWS = state.rows,
          CSPACE = state.CSPACE, CLINES = state.CLINES,
          RSPACE = state.RSPACE, RLINES = state.RLINES,
          CALIGN = state.CALIGN, RALIGN = state.RALIGN,
          RCALIGN = state.RCALIGN;
      CSPACE[state.J] *= 2; RSPACE[ROWS.length-1] *= 2; // since halved below
      var T = "0", B, R, L, border, cbox, align, lastB = 0;
      if (values.fspace) {
        lastB = state.FSPACE[1];
        T = CHTML.Em(state.FSPACE[1]);
      }
      state.RHD = []; state.RH = [];
      for (var i = 0, m = ROWS.length; i < m; i++) {
        var row = ROWS[i], rdata = this.data[i];
        //
        //  Space and borders between rows
        //
        B = RSPACE[i]/2; border = null; L = "0";
        if (RLINES[i] !== MML.LINES.NONE && RLINES[i] !== "") border = state.t+" "+RLINES[i];
        if (border || (CLINES[j] !== MML.LINES.NONE && CLINES[j] !== "")) {
          while (row.length <= state.J) {
            row.push(CHTML.addElement(row.node,"mjx-mtd",null,[['span']]));
          }
        }
        state.RH[i] = lastB + state.H[i];                 // distance to baseline in row
        lastB = Math.max(0,B);
        state.RHD[i] = state.RH[i] + lastB + state.D[i];  // total height of row
        B = CHTML.Em(lastB);
        //
        //  Frame space for initial cell
        //
        if (values.fspace) L = CHTML.Em(state.FSPACE[0]);
        //
        //  The cells in the row
        //
        for (var j = 0, M = row.length; j < M; j++) {
          var s = (rdata.type === "mtr" ? 0 : LABEL);
          var mtd = rdata.data[j-s] || {CHTML: CHTML.BBOX.zero()};
          var cell = row[j].style; cbox = mtd.CHTML;
          //
          //  Space and borders between columns
          //
          R = CSPACE[j]/2;
          if (CLINES[j] !== MML.LINES.NONE) {
            cell.borderRight = state.t+" "+CLINES[j];
            R -= 1/CHTML.em/2;
          }
          R = CHTML.Em(Math.max(0,R));
          cell.padding = T+" "+R+" 0px "+L;
          if (border) cell.borderBottom = border;
          L = R;
          //
          //  Handle vertical alignment
          //
          align = (mtd.rowalign||(this.data[i]||{}).rowalign||RALIGN[i]);
          var H = Math.max(1,cbox.h), D = Math.max(.2,cbox.d),
              HD = (state.H[i]+state.D[i]) - (H+D),
              child = row[j].firstChild.style;
          if (align === MML.ALIGN.TOP) {
            if (HD) child.marginBottom = CHTML.Em(HD);
            cell.verticalAlign = "top";
          } else if (align === MML.ALIGN.BOTTOM) {
            cell.verticalAlign = "bottom";
            if (HD) child.marginTop = CHTML.Em(HD);
          } else if (align === MML.ALIGN.CENTER) {
            if (HD) child.marginTop = child.marginBottom = CHTML.Em(HD/2);
            cell.verticalAlign = "middle";
          } else {
            if (H !== state.H[i]) child.marginTop = CHTML.Em(state.H[i]-H);
          }
          //
          //  Handle horizontal alignment
          //
          align = (mtd.columnalign||RCALIGN[i][j]||CALIGN[j]);
          if (align !== MML.ALIGN.CENTER) cell.textAlign = align;
        }
        row.node.style.height = CHTML.Em(state.RHD[i]);
        T = B;
      }
      CSPACE[state.J] /= 2; RSPACE[ROWS.length-1] /= 2; // back to normal
    },
    //
    //  Align the table vertically according to the align attribute
    //
    CHTMLalignV: function (values,state,node) {
      var n, M = state.rows.length, H = state.H, D = state.D, RSPACE = state.RSPACE;
      //
      //  Get alignment type and row number
      //
      if (typeof(values.align) !== "string") values.align = String(values.align);
      if (values.align.match(/(top|bottom|center|baseline|axis)( +(-?\d+))?/)) {
        n = parseInt(RegExp.$3||"0");
        values.align = RegExp.$1
        if (n < 0) n += state.rows.length + 1;
        if (n > M || n <= 0) n = null;
      } else {
        values.align = this.defaults.align;
      }
      //
      //  Get table height and baseline offset
      //
      var T = 0, B = 0, a = CHTML.TEX.axis_height;
      if (values.fspace) T += state.FSPACE[1];
      if (values.frame) {T += 2/CHTML.em; B += 1/CHTML.em}
      for (var i = 0; i < M; i++) {
        var h = H[i], d = D[i];
        T += h + d + RSPACE[i];
        if (n) {
          if (i === n-1) {
            B += ({top:h+d, bottom:0, center:(h+d)/2,
                   baseline:d, axis:a+d})[values.align] + RSPACE[i];
          }
          if (i >= n) B += h + d + RSPACE[i];
        }
      }
      if (!n) B = ({top:T, bottom:0, center:T/2, baseline:T/2, axis:T/2-a})[values.align];
      //
      //  Place the node and save the values
      //
      if (B) node.style.verticalAlign = CHTML.Em(-B);
      state.T = T; state.B = B;
    },
    //
    //  Determine column widths and set the styles for the columns
    //
    CHTMLcolumnWidths: function (values,state,node) {
      var CWIDTH = state.CWIDTH, CSPACE = state.CSPACE, J = state.J, j;
      var WW = 0, setWidths = false, relWidth = values.width.match(/%$/);
      var i, m, w;
      //
      //  Handle equal columns by adjusting the CWIDTH array
      //
      if (values.width !== "auto" && !relWidth) {
        WW = Math.max(0,this.CHTMLlength2em(values.width,state.R));
        setWidths = true;
      }
      if (values.equalcolumns) {
        if (relWidth) {
          //
          //  Use percent of total (not perfect, but best we can do)
          //
          var p = CHTML.Percent(1/(J+1));
          for (j = 0; j <= J; j++) CWIDTH[j] = p;
        } else {
          //
          //  For width = auto, make all widths equal the widest,
          //  otherwise, for specific width, remove intercolumn space
          //  and divide by number of columns to get widest space.
          //
          w = Math.max.apply(Math,state.W);
          if (values.width !== "auto") {
            var S = (values.fspace ? state.FSPACE[0] + (values.frame ? 2/CHTML.em : 0) : 0);
            for (j = 0; j <= J; j++) S += CSPACE[j];
            w = Math.max((WW-S)/(J+1),w);
          }
          w = CHTML.Em(w);
          for (j = 0; j <= J; j++) CWIDTH[j] = w;
        }
        setWidths = true;
      }
      //
      //  Compute natural table width
      //
      var TW = 0; if (values.fspace) TW = state.FSPACE[0];
      var auto = [], fit = [], percent = [], W = [];
      var row = state.rows[0];
      for (j = 0; j <= J; j++) {
        W[j] = state.W[j];
        if (CWIDTH[j] === "auto") auto.push(j)
        else if (CWIDTH[j] === "fit") fit.push(j)
        else if (CWIDTH[j].match(/%$/)) percent.push(j)
        else W[j] = this.CHTMLlength2em(CWIDTH[j],W[j]);
        TW += W[j] + CSPACE[j];
        if (row[j]) row[j].style.width = CHTML.Em(W[j]);
      }
      if (values.frame) TW += 2/CHTML.em;
      var hasFit = (fit.length > 0);
      //
      //  Adjust widths of columns
      //
      if (setWidths) {
        if (relWidth) {
          //
          //  Attach appropriate widths to the columns
          //  
          for (j = 0; j <= J; j++) {
            cell = row[j].style;
            if (CWIDTH[j] === "auto" && !hasFit) cell.width = "";
            else if (CWIDTH[j] === "fit") cell.width = "";
            else if (CWIDTH[j].match(/%$/)) cell.width = CWIDTH[j];
            else cell.minWidth = cell.maxWidth = cell.width;
          }
        } else {
          //
          //  Compute percentage widths
          //
          if (WW > TW) {
            var extra = 0;
            for (i = 0, m = percent.length; i < m; i++) {
              j = percent[i];
              w = Math.max(W[j],this.CHTMLlength2em(CWIDTH[j],WW));
              extra += w-W[j]; W[j] = w;
              row[j].style.width = CHTML.Em(w);
            }
            TW += extra;
          }
          //
          //  Compute "fit" widths
          //
          if (!hasFit) fit = auto;
          if (WW > TW && fit.length) {
            var dw = (WW - TW) / fit.length;
            for (i = 0, m = fit.length; i < m; i++) {
              j = fit[i]; W[j] += dw;
              row[j].style.width = CHTML.Em(W[j]);
            }
            TW = WW;
          }
        }
      }
      W[LABEL] = state.W[LABEL];
      state.W = W;
      state.R = TW;
      //
      //  Set variable width on DOM nodes
      //
      if (relWidth) {
        node.style.width = this.CHTML.pwidth = "100%";
        this.CHTML.mwidth = CHTML.Em(TW);
        node.firstChild.style.width = values.width;
        node.firstChild.style.margin = "auto";
      }
    },
    //
    //  Stretch any cells that can be stretched
    //
    CHTMLstretchCells: function (values,state) {
      var ROWS = state.rows, H = state.H, D = state.D, W = state.W,
          J = state.J, M = ROWS.length-1;
      for (var i = 0; i <= M; i++) {
        var row = ROWS[i], rdata = this.data[i];
        var h = H[i], d = D[i];
        for (var j = 0; j <= J; j++) {
          var cell = row[j], cdata = rdata.data[j];
          if (!cdata) continue;
          if (cdata.CHTML.stretch === "V") cdata.CHTMLstretchV(h,d);
          else if (cdata.CHTML.stretch === "H") cdata.CHTMLstretchH(cell,W[j]);
        }
      }
    },
    //
    //  Add labels to a table
    //
    CHTMLaddLabels: function (values,state,node,table) {
      //
      //  Get indentation and alignment
      //
      var indent = this.getValues("indentalignfirst","indentshiftfirst","indentalign","indentshift");
      if (indent.indentalignfirst !== MML.INDENTALIGN.INDENTALIGN) indent.indentalign = indent.indentalignfirst;
      if (indent.indentalign === MML.INDENTALIGN.AUTO) indent.indentalign = CONFIG.displayAlign;
      if (indent.indentshiftfirst !== MML.INDENTSHIFT.INDENTSHIFT) indent.indentshift = indent.indentshiftfirst;
      if (indent.indentshift === "auto") indent.indentshift = "0";
      var shift = this.CHTMLlength2em(indent.indentshift,CHTML.cwidth);
      var labelspace = this.CHTMLlength2em(values.minlabelspacing,.8);
      var labelW = labelspace + state.W[LABEL], labelshift = 0, tw = state.R;
      var dIndent = this.CHTMLlength2em(CONFIG.displayIndent,CHTML.cwidth);
      var s = (state.CALIGN[LABEL] === MML.INDENTALIGN.RIGHT ? -1 : 1);
      if (indent.indentalign === MML.INDENTALIGN.CENTER) {
        tw += 2 * (labelW - s*(shift + dIndent));
        shift += dIndent;
      } else if (state.CALIGN[LABEL] === indent.indentalign) {
        if (dIndent < 0) {labelshift = s*dIndent; dIndent = 0}
        shift += s*dIndent; if (labelW > s*shift) shift = s*labelW; shift += labelshift;
        shift *= s; tw += shift;
      } else {
        tw += labelW - s*shift + dIndent;
        shift -= s*dIndent; shift *= -s;
      }
      //
      //  Create boxes for table and labels
      //
      var box = CHTML.addElement(node,"mjx-box",{
        style:{width:"100%","text-align":indent.indentalign}
      }); box.appendChild(table);
      var labels = CHTML.Element("mjx-itable");
      table.style.display = "inline-table"; if (!table.style.width) table.style.width = "auto";
      labels.style.verticalAlign = "top";
      table.style.verticalAlign = CHTML.Em(state.T-state.B-state.H[0]);
      node.style.verticalAlign = "";
      if (shift) {
        if (indent.indentalign === MML.INDENTALIGN.CENTER) {
          table.style.marginLeft = CHTML.Em(shift);
          table.style.marginRight = CHTML.Em(-shift);
        } else {
          var margin = "margin" + (indent.indentalign === MML.INDENTALIGN.RIGHT ? "Right" : "Left");
          table.style[margin] = CHTML.Em(shift);
        }
      }
      //
      //  Add labels on correct side
      //
      if (state.CALIGN[LABEL] === "left") {
        node.insertBefore(labels,box);
        labels.style.marginRight = CHTML.Em(-state.W[LABEL]-labelshift);
        if (labelshift) labels.style.marginLeft = CHTML.Em(labelshift);
      } else {
        node.appendChild(labels);
        labels.style.marginLeft = CHTML.Em(-state.W[LABEL]+labelshift);
      }
      //
      //  Vertically align the labels with their rows
      //
      var LABELS = state.labels, T = 0;
      if (values.fspace) T = state.FSPACE[0] + (values.frame ? 1/CHTML.em : 0);
      for (var i = 0, m = LABELS.length; i < m; i++) {
        if (LABELS[i] && this.data[i].data[0]) {
          labels.appendChild(LABELS[i]);
          var lbox = this.data[i].data[0].CHTML;
          T = state.RH[i] - Math.max(1,lbox.h);
          if (T) LABELS[i].firstChild.firstChild.style.marginTop = CHTML.Em(T);
          LABELS[i].style.height = CHTML.Em(state.RHD[i]);
        } else {
          CHTML.addElement(labels,"mjx-label",{style:{height:CHTML.Em(state.RHD[i])}});
        }
      }
      //
      //  Propagate full-width equations, and reserve room for equation plus label
      //
      node.style.width = this.CHTML.pwidth = "100%";
      node.style.minWidth = this.CHTML.mwidth = CHTML.Em(Math.max(0,tw));
    }
  });
  
  MML.mtr.Augment({
    toCommonHTML: function (node,options) {
      //
      //  Create the row node
      //
      node = this.CHTMLcreateNode(node);
      this.CHTMLhandleStyle(node);
      this.CHTMLhandleScale(node);
      //
      //  Add a new row with no label
      //
      if (!options) options = {rows:[],labels:[]};
      var row = []; options.rows.push(row); row.node = node;
      options.labels.push(null);
      //
      //  Add the cells to the row
      //
      for (var i = 0, m = this.data.length; i < m; i++)
        row.push(this.CHTMLaddChild(node,i,options));
      //
      this.CHTMLhandleColor(node);
      return node;
    }
  });
  MML.mlabeledtr.Augment({
    toCommonHTML: function (node,options) {
      //
      //  Create the row node
      //
      node = this.CHTMLcreateNode(node);
      this.CHTMLhandleStyle(node);
      this.CHTMLhandleScale(node);
      //
      //  Add a new row, and get the label
      //
      if (!options) options = {rows:[],labels:[]};
      var row = []; options.rows.push(row); row.node = node;
      var label = CHTML.Element("mjx-label"); options.labels.push(label);
      this.CHTMLaddChild(label,0,options);
      if (this.data[0]) options.labeled = true;
      //
      //  Add the cells to the row
      //
      for (var i = 1, m = this.data.length; i < m; i++)
        row.push(this.CHTMLaddChild(node,i,options));
      //
      this.CHTMLhandleColor(node);
      return node;
    }
  });
  MML.mtd.Augment({
    toCommonHTML: function (node,options) {
      node = this.CHTMLdefaultNode(node,options);
      CHTML.addElement(node.firstChild,"mjx-strut");  // forces height to 1em (we adjust later)
      //
      //  Determine if this is stretchy or not
      //
      if (this.isEmbellished()) {
        var mo = this.CoreMO(), BBOX = this.CHTML;
        if (mo.CHTMLcanStretch("Vertical")) BBOX.stretch = "V";
        else if (mo.CHTMLcanStretch("Horizontal")) BBOX.stretch = "H";
        if (BBOX.stretch) {
          var min = mo.Get("minsize",true);
          if (min) {
            if (BBOX.stretch === "V") {
              var HD = BBOX.h + BBOX.d;
              if (HD) {
                var r = this.CHTMLlength2em(min,HD)/HD;
                if (r > 1) {BBOX.h *= r; BBOX.d *= r}
              }
            } else {
              BBOX.w = Math.max(BBOX.w,this.CHTMLlength2em(min,BBOX.w));
            }
          }
        }
      }
      return node;
    }
  });

  
  MathJax.Hub.Startup.signal.Post("CommonHTML mtable Ready");
  MathJax.Ajax.loadComplete(CHTML.autoloadDir+"/mtable.js");
});

