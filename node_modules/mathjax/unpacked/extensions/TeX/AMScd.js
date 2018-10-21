/* -*- Mode: Javascript; indent-tabs-mode:nil; js-indent-level: 2 -*- */
/* vim: set ts=2 et sw=2 tw=80: */

/*************************************************************
 *
 *  MathJax/extensions/TeX/AMScd.js
 *  
 *  Implements the CD environment for commutative diagrams.
 *  
 *  ---------------------------------------------------------------------
 *  
 *  Copyright (c) 2013-2018 The MathJax Consortium
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

MathJax.Extension["TeX/AMScd"] = {
  version: "2.7.5",
  config: MathJax.Hub.CombineConfig("TeX.CD",{
    colspace: "5pt",
    rowspace: "5pt",
    harrowsize: "2.75em",
    varrowsize: "1.75em",
    hideHorizontalLabels: false
  })
};

MathJax.Hub.Register.StartupHook("TeX Jax Ready",function () {
  var MML = MathJax.ElementJax.mml,
      TEX = MathJax.InputJax.TeX,
      STACKITEM = TEX.Stack.Item,
      TEXDEF = TEX.Definitions,
      CONFIG = MathJax.Extension["TeX/AMScd"].config;

  TEXDEF.environment.CD = "CD_env";
  TEXDEF.special["@"] = "CD_arrow";
  TEXDEF.macros.minCDarrowwidth = "CD_minwidth";
  TEXDEF.macros.minCDarrowheight = "CD_minheight";

  TEX.Parse.Augment({
    //
    //  Implements \begin{CD}...\end{CD}
    //
    CD_env: function (begin) {
      this.Push(begin);
      return STACKITEM.array().With({
        arraydef: {
          columnalign: "center",
          columnspacing: CONFIG.colspace,
          rowspacing: CONFIG.rowspace,
          displaystyle: true
        },
        minw: this.stack.env.CD_minw || CONFIG.harrowsize,
        minh: this.stack.env.CD_minh || CONFIG.varrowsize
      });
    },

    CD_arrow: function (name) {
      var c = this.string.charAt(this.i);
      if (!c.match(/[><VA.|=]/)) {return this.Other(name)} else {this.i++}

      var top = this.stack.Top();
      if (!top.isa(STACKITEM.array) || top.data.length) {
        this.CD_cell(name);
        top = this.stack.Top();
      }
      //
      //  Add enough cells to place the arrow correctly
      //
      var arrowRow = ((top.table.length % 2) === 1);
      var n = (top.row.length + (arrowRow ? 0 : 1)) % 2;
      while (n) {this.CD_cell(name); n--}

      var mml;
      var hdef = {minsize: top.minw, stretchy:true},
          vdef = {minsize: top.minh, stretchy:true, symmetric:true, lspace:0, rspace:0};

      if (c === ".") {}
      else if (c === "|") {mml = this.mmlToken(MML.mo("\u2225").With(vdef))}
      else if (c === "=") {mml = this.mmlToken(MML.mo("=").With(hdef))}
      else {
        //
        //  for @>>> @<<< @VVV and @AAA, get the arrow and labels
        //
        var arrow = {">":"\u2192", "<":"\u2190", V:"\u2193", A:"\u2191"}[c];
        var a = this.GetUpTo(name+c,c),
            b = this.GetUpTo(name+c,c);

        if (c === ">" || c === "<") {
          //
          //  Lay out horizontal arrows with munderover if it has labels
          //
          mml = MML.mo(arrow).With(hdef);
          if (!a) {a = "\\kern "+top.minw} // minsize needs work
          if (a || b) {
            var pad = {width:"+11mu", lspace:"6mu"};
            mml = MML.munderover(this.mmlToken(mml));
            if (a) {
              a = TEX.Parse(a,this.stack.env).mml();
              mml.SetData(mml.over,MML.mpadded(a).With(pad).With({voffset:".1em"}));
            }
            if (b) {
              b = TEX.Parse(b,this.stack.env).mml();
              mml.SetData(mml.under,MML.mpadded(b).With(pad));
            }
            if (CONFIG.hideHorizontalLabels)
              {mml = MML.mpadded(mml).With({depth:0, height:".67em"})}
          }
        } else {
          //
          //  Lay out vertical arrows with mrow if there are labels
          //
          mml = arrow = this.mmlToken(MML.mo(arrow).With(vdef));
          if (a || b) {
            mml = MML.mrow();
            if (a) {mml.Append(TEX.Parse("\\scriptstyle\\llap{"+a+"}",this.stack.env).mml())}
            mml.Append(arrow.With({texClass: MML.TEXCLASS.ORD}));
            if (b) {mml.Append(TEX.Parse("\\scriptstyle\\rlap{"+b+"}",this.stack.env).mml())}
          }
        }
      }
      if (mml) {this.Push(mml)};
      this.CD_cell(name);
    },
    CD_cell: function (name) {
      var top = this.stack.Top();
      if ((top.table||[]).length % 2 === 0 && (top.row||[]).length === 0) {
        //
        // Add a strut to the first cell in even rows to get
        // better spacing of arrow rows.
        // 
        this.Push(MML.mpadded().With({height:"8.5pt",depth:"2pt"}));
      }
      this.Push(STACKITEM.cell().With({isEntry:true, name:name}));
    },

    CD_minwidth: function (name) {
      this.stack.env.CD_minw = this.GetDimen(name);
    },
    CD_minheight: function (name) {
      this.stack.env.CD_minh = this.GetDimen(name);
    }

  });

});

MathJax.Ajax.loadComplete("[MathJax]/extensions/TeX/AMScd.js");
