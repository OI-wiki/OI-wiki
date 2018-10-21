/* -*- Mode: Javascript; indent-tabs-mode:nil; js-indent-level: 2 -*- */
/* vim: set ts=2 et sw=2 tw=80: */

/*************************************************************
 *
 *  MathJax/jax/output/SVG/autoload/mtable.js
 *  
 *  Implements the SVG output for <mtable> elements.
 *
 *  ---------------------------------------------------------------------
 *  
 *  Copyright (c) 2011-2018 The MathJax Consortium
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

MathJax.Hub.Register.StartupHook("SVG Jax Ready",function () {
  var VERSION = "2.7.5";
  var MML = MathJax.ElementJax.mml,
      SVG = MathJax.OutputJax.SVG,
      BBOX = SVG.BBOX;
  
  MML.mtable.Augment({
    toSVG: function (span) {
      this.SVGgetStyles();
      var svg = this.SVG(), scale = this.SVGgetScale(svg);
      if (this.data.length === 0) {this.SVGsaveData(svg);return svg}
      var values = this.getValues("columnalign","rowalign","columnspacing","rowspacing",
                                  "columnwidth","equalcolumns","equalrows",
                                  "columnlines","rowlines","frame","framespacing",
                                  "align","useHeight","width","side","minlabelspacing");
      //  Handle relative width as fixed width in relation to container
      if (values.width.match(/%$/))
        {svg.width = values.width = SVG.Em((SVG.cwidth/1000)*(parseFloat(values.width)/100))}

      var mu = this.SVGgetMu(svg);
      var LABEL = -1;

      var H = [], D = [], W = [], A = [], C = [], i, j, J = -1,
          m, M, s, row, cell, mo, HD;
      var LH = SVG.FONTDATA.lineH * scale * values.useHeight,
          LD = SVG.FONTDATA.lineD * scale * values.useHeight;

      //
      //  Create cells and measure columns and rows
      //
      for (i = 0, m = this.data.length; i < m; i++) {
        row = this.data[i]; s = (row.type === "mlabeledtr" ? LABEL : 0);
        A[i] = []; H[i] = LH; D[i] = LD;
        for (j = s, M = row.data.length + s; j < M; j++) {
          if (W[j] == null) {
            if (j > J) {J = j}
            C[j] = BBOX.G();
            W[j] = -SVG.BIGDIMEN;
          }
          cell = row.data[j-s];
          A[i][j] = cell.toSVG();
//          if (row.data[j-s].isMultiline) {A[i][j].style.width = "100%"}
          if (cell.isEmbellished()) {
            mo = cell.CoreMO();
            var min = mo.Get("minsize",true);
            if (min) {
              if (mo.SVGcanStretch("Vertical")) {
                HD = mo.SVGdata.h + mo.SVGdata.d;
                if (HD) {
                  min = SVG.length2em(min,mu,HD);
                  if (min*mo.SVGdata.h/HD > H[i]) {H[i] = min*mo.SVGdata.h/HD}
                  if (min*mo.SVGdata.d/HD > D[i]) {D[i] = min*mo.SVGdata.d/HD}
                }
              } else if (mo.SVGcanStretch("Horizontal")) {
                min = SVG.length2em(min,mu,mo.SVGdata.w);
                if (min > W[j]) {W[j] = min}
              }
            }
          }
          if (A[i][j].h > H[i]) {H[i] = A[i][j].h}
          if (A[i][j].d > D[i]) {D[i] = A[i][j].d}
          if (A[i][j].w > W[j]) {W[j] = A[i][j].w}
        }
      }

      //
      //  Determine spacing and alignment
      //
      var SPLIT = MathJax.Hub.SplitList;
      var CSPACE = SPLIT(values.columnspacing),
          RSPACE = SPLIT(values.rowspacing),
          CALIGN = SPLIT(values.columnalign),
          RALIGN = SPLIT(values.rowalign),
          CLINES = SPLIT(values.columnlines),
          RLINES = SPLIT(values.rowlines),
          CWIDTH = SPLIT(values.columnwidth),
          RCALIGN = [];
      for (i = 0, m = CSPACE.length; i < m; i++) {CSPACE[i] = SVG.length2em(CSPACE[i],mu)}
      for (i = 0, m = RSPACE.length; i < m; i++) {RSPACE[i] = SVG.length2em(RSPACE[i],mu)}
      while (CSPACE.length <  J) {CSPACE.push(CSPACE[CSPACE.length-1])}
      while (CALIGN.length <= J) {CALIGN.push(CALIGN[CALIGN.length-1])}
      while (CLINES.length <  J) {CLINES.push(CLINES[CLINES.length-1])}
      while (CWIDTH.length <= J) {CWIDTH.push(CWIDTH[CWIDTH.length-1])}
      while (RSPACE.length <  A.length) {RSPACE.push(RSPACE[RSPACE.length-1])}
      while (RALIGN.length <= A.length) {RALIGN.push(RALIGN[RALIGN.length-1])}
      while (RLINES.length <  A.length) {RLINES.push(RLINES[RLINES.length-1])}
      if (C[LABEL]) {
        CALIGN[LABEL] = (values.side.substr(0,1) === "l" ? "left" : "right");
        CSPACE[LABEL] = -W[LABEL];
      }
      //
      //  Override row data
      //
      for (i = 0, m = A.length; i < m; i++) {
        row = this.data[i]; RCALIGN[i] = [];
        if (row.rowalign) {RALIGN[i] = row.rowalign}
        if (row.columnalign) {
          RCALIGN[i] = SPLIT(row.columnalign);
          while (RCALIGN[i].length <= J) {RCALIGN[i].push(RCALIGN[i][RCALIGN[i].length-1])}
        }
      }

      //
      //  Handle equal heights
      //
      if (values.equalrows) {
        // FIXME:  should really be based on row align (below is for baseline)
        var Hm = Math.max.apply(Math,H), Dm = Math.max.apply(Math,D);
        for (i = 0, m = A.length; i < m; i++)
          {s = ((Hm + Dm) - (H[i] + D[i])) / 2;  H[i] += s; D[i] += s}
      }

      //  FIXME:  do background colors for entire cell (include half the intercolumn space?)
      
      //
      //  Determine array total height
      //
      HD = H[0] + D[A.length-1];
      for (i = 0, m = A.length-1; i < m; i++)
        {HD += Math.max(0,D[i]+H[i+1]+RSPACE[i])}
      //
      //  Determine frame and line sizes
      //
      var fx = 0, fy = 0, fW, fH = HD;
      if (values.frame !== "none" ||
         (values.columnlines+values.rowlines).match(/solid|dashed/)) {
        var frameSpacing = SPLIT(values.framespacing);
        if (frameSpacing.length != 2) {
          // invalid attribute value: use the default.
          frameSpacing = SPLIT(this.defaults.framespacing);
        }
        fx = SVG.length2em(frameSpacing[0],mu);
        fy = SVG.length2em(frameSpacing[1],mu);
        fH = HD + 2*fy; // fW waits until svg.w is determined
      }
      //
      //  Compute alignment
      //
      var Y, fY, n = "";
      if (typeof(values.align) !== "string") {values.align = String(values.align)}
      if (values.align.match(/(top|bottom|center|baseline|axis)( +(-?\d+))?/))
        {n = RegExp.$3||""; values.align = RegExp.$1} else {values.align = this.defaults.align}
      if (n !== "") {
        //
        //  Find the height of the given row
        //
        n = parseInt(n);
        if (n < 0) {n = A.length + 1 + n}
        if (n < 1) {n = 1} else if (n > A.length) {n = A.length}
        Y = 0; fY = -(HD + fy) + H[0];
        for (i = 0, m = n-1; i < m; i++) {
          // FIXME:  Should handle values.align for final row
          var dY = Math.max(0,D[i]+H[i+1]+RSPACE[i]);
          Y += dY; fY += dY;
        }
      } else {
        Y = ({
          top:    -(H[0] + fy),
          bottom:   HD + fy - H[0],
          center:   HD/2 - H[0],
          baseline: HD/2 - H[0],
          axis:     HD/2 + SVG.TeX.axis_height*scale - H[0]
        })[values.align];
        fY = ({
          top:      -(HD + 2*fy),
          bottom:   0,
          center:   -(HD/2 + fy),
          baseline: -(HD/2 + fy),
          axis:     SVG.TeX.axis_height*scale - HD/2 - fy
        })[values.align];
      }
            
      var WW, WP = 0, Wt = 0, Wp = 0, p = 0, f = 0, P = [], F = [], Wf = 1;
      //
      if (values.equalcolumns && values.width !== "auto") {
        //
        //  Handle equalcolumns for percent-width and fixed-width tables
        //

        //  Get total width minus column spacing
        WW = SVG.length2em(values.width,mu);
        for (i = 0, m = Math.min(J,CSPACE.length); i < m; i++) {WW -= CSPACE[i]}
        //  Determine individual column widths
        WW /= J;
        for (i = 0, m = Math.min(J+1,CWIDTH.length); i < m; i++) {W[i] = WW}
      } else {
        //
        //  Get column widths for fit and percentage columns
        //
        //  Calculate the natural widths and percentage widths,
        //    while keeping track of the fit and percentage columns
        for(i = 0, m = Math.min(J+1,CWIDTH.length); i < m; i++) {
          if (CWIDTH[i] === "auto") {Wt += W[i]}
          else if (CWIDTH[i] === "fit") {F[f] = i; f++; Wt += W[i]}
          else if (CWIDTH[i].match(/%$/))
            {P[p] = i; p++; Wp += W[i]; WP += SVG.length2em(CWIDTH[i],mu,1)}
          else {W[i] = SVG.length2em(CWIDTH[i],mu); Wt += W[i]}
        }
        // Get the full width (excluding inter-column spacing)
        if (values.width === "auto") {
          if (WP > .98) {Wf = Wp/(Wt+Wp); WW = Wt + Wp} else {WW = Wt / (1-WP)}
        } else {
          WW = Math.max(Wt + Wp, SVG.length2em(values.width,mu));
          for (i = 0, m = Math.min(J,CSPACE.length); i < m; i++) {WW -= CSPACE[i]}
        }
        //  Determine the relative column widths
        for (i = 0, m = P.length; i < m; i++) {
          W[P[i]] = SVG.length2em(CWIDTH[P[i]],mu,WW*Wf); Wt += W[P[i]];
        }
        //  Stretch fit columns, if any, otherwise stretch (or shrink) everything
        if (Math.abs(WW - Wt) > .01) {
          if (f && WW > Wt) {
            WW = (WW - Wt) / f; for (i = 0, m = F.length; i < m; i++) {W[F[i]] += WW}
          } else {WW = WW/Wt; for (j = 0; j <= J; j++) {W[j] *= WW}}
        }
        //
        //  Handle equal columns
        //
        if (values.equalcolumns) {
          var Wm = Math.max.apply(Math,W);
          for (j = 0; j <= J; j++) {W[j] = Wm}
        }
      }
      
      //
      //  Lay out array columns
      //
      var y = Y, dy, align; s = (C[LABEL] ? LABEL : 0);
      for (j = s; j <= J; j++) {
        C[j].w = W[j];
        for (i = 0, m = A.length; i < m; i++) {
          if (A[i][j]) {
            s = (this.data[i].type === "mlabeledtr" ? LABEL : 0);
            cell = this.data[i].data[j-s];
	    if (cell.SVGcanStretch("Horizontal")) {
	      A[i][j] = cell.SVGstretchH(W[j]);
	    } else if (cell.SVGcanStretch("Vertical")) {
	      mo = cell.CoreMO();
	      var symmetric = mo.symmetric; mo.symmetric = false;
	      A[i][j] = cell.SVGstretchV(H[i],D[i]);
	      mo.symmetric = symmetric;
	    }
            align = cell.rowalign||this.data[i].rowalign||RALIGN[i];
            dy = ({top:    H[i] - A[i][j].h,
                   bottom: A[i][j].d - D[i],
                   center: ((H[i]-D[i]) - (A[i][j].h-A[i][j].d))/2,
                   baseline: 0, axis: 0})[align] || 0; // FIXME:  handle axis better?
            align = (cell.columnalign||RCALIGN[i][j]||CALIGN[j])
            C[j].Align(A[i][j],align,0,y+dy);
          }
          if (i < A.length-1) {y -= Math.max(0,D[i]+H[i+1]+RSPACE[i])}
        }
        y = Y;
      }

      //
      //  Place the columns and add column lines
      //
      var lw = 1.5*SVG.em;
      var x = fx - lw/2;
      for (j = 0; j <= J; j++) {
        svg.Add(C[j],x,0); x += W[j] + CSPACE[j];
        if (CLINES[j] !== "none" && j < J && j !== LABEL)
        {svg.Add(BBOX.VLINE(fH,lw,CLINES[j]),x-CSPACE[j]/2,fY)}
      }
      svg.w += fx; svg.d = -fY; svg.h = fH+fY;
      fW = svg.w;
      
      //
      //  Add frame
      //
      if (values.frame !== "none") {
        svg.Add(BBOX.HLINE(fW,lw,values.frame),0,fY+fH-lw);
        svg.Add(BBOX.HLINE(fW,lw,values.frame),0,fY);
        svg.Add(BBOX.VLINE(fH,lw,values.frame),0,fY);
        svg.Add(BBOX.VLINE(fH,lw,values.frame),fW-lw,fY);
      }

      //
      //  Add row lines
      //
      y = Y - lw/2;
      for (i = 0, m = A.length-1; i < m; i++) {
        dy = Math.max(0,D[i]+H[i+1]+RSPACE[i]);
        if (RLINES[i] !== MML.LINES.NONE && RLINES[i] !== "")
          {svg.Add(BBOX.HLINE(fW,lw,RLINES[i]),0,y-D[i]-(dy-D[i]-H[i+1])/2)}
        y -= dy;
      }
      
      //
      //  Finish the table
      //
      svg.Clean();
      this.SVGhandleSpace(svg);
      this.SVGhandleColor(svg);
      
      //
      //  Place the labels, if any
      //
      if (C[LABEL]) {
        svg.tw = Math.max(svg.w,svg.r) - Math.min(0,svg.l);
        var indent = this.getValues("indentalignfirst","indentshiftfirst","indentalign","indentshift");
        if (indent.indentalignfirst !== MML.INDENTALIGN.INDENTALIGN) {indent.indentalign = indent.indentalignfirst}
        if (indent.indentalign === MML.INDENTALIGN.AUTO) {indent.indentalign = this.displayAlign}
        if (indent.indentshiftfirst !== MML.INDENTSHIFT.INDENTSHIFT) {indent.indentshift = indent.indentshiftfirst}
        if (indent.indentshift === "auto" || indent.indentshift === "") {indent.indentshift = "0"}
        var shift = SVG.length2em(indent.indentshift,mu,SVG.cwidth);
        var labelspace = SVG.length2em(values.minlabelspacing,mu,SVG.cwidth);
        var labelW = labelspace + C[LABEL].w, labelshift = 0, tw = svg.w;
        var dIndent = SVG.length2em(this.displayIndent,mu,SVG.cwidth);
        s = (CALIGN[LABEL] === MML.INDENTALIGN.RIGHT ? -1 : 1);
        if (indent.indentalign === MML.INDENTALIGN.CENTER) {
          var dx = (SVG.cwidth-tw)/2; shift += dIndent;
          if (labelW + s*labelshift > dx + s*shift) {
            indent.indentalign = CALIGN[LABEL];
            shift = s*(labelW + s*labelshift); tw += labelW + Math.max(0,shift);
          }
        } else if (CALIGN[LABEL] === indent.indentalign) {
          if (dIndent < 0) {labelshift = s*dIndent; dIndent = 0}
          shift += s*dIndent; if (labelW > s*shift) shift = s*labelW; shift += labelshift;
          tw += s*shift;
        } else {
          shift -= s*dIndent;
          if (tw - s*shift + labelW > SVG.cwidth) {
            shift = s*(tw + labelW - SVG.cwidth);
            if (s*shift > 0) {tw = SVG.cwidth + s*shift; shift = 0}
          }
        }
        var eqn = svg; svg = this.SVG();
        svg.hasIndent = true;
        svg.w = svg.r = Math.max(tw,SVG.cwidth); 
        svg.Align(C[LABEL],CALIGN[LABEL],0,0,labelshift);
        svg.Align(eqn,indent.indentalign,0,0,shift);
        svg.tw = tw;
      }
      
      this.SVGsaveData(svg);
      return svg;
    },
    SVGhandleSpace: function (svg) {
      if (!this.hasFrame && !svg.width) {svg.x = svg.X = 167}
      this.SUPER(arguments).SVGhandleSpace.call(this,svg);
    }
  });
  
  MML.mtd.Augment({
    toSVG: function (HW,D) {
      var svg = this.svg = this.SVG();
      if (this.data[0]) {
        svg.Add(this.SVGdataStretched(0,HW,D));
        svg.Clean();
      }
      this.SVGhandleColor(svg);
      this.SVGsaveData(svg);
      return svg;
    }
  });

  MathJax.Hub.Startup.signal.Post("SVG mtable Ready");
  MathJax.Ajax.loadComplete(SVG.autoloadDir+"/mtable.js");
  
});

