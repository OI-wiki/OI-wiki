/* -*- Mode: Javascript; indent-tabs-mode:nil; js-indent-level: 2 -*- */
/* vim: set ts=2 et sw=2 tw=80: */

/*************************************************************
 *
 *  MathJax/extensions/TeX/AMSmath.js
 *
 *  Implements AMS math environments and macros.
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

MathJax.Extension["TeX/AMSmath"] = {
  version: "2.7.5",
  
  number: 0,        // current equation number
  startNumber: 0,   // current starting equation number (for when equation is restarted)
  IDs: {},          // IDs used in previous equations
  eqIDs: {},        // IDs used in this equation
  labels: {},       // the set of labels
  eqlabels: {},     // labels in the current equation
  refs: []          // array of jax with unresolved references
};

MathJax.Hub.Register.StartupHook("TeX Jax Ready",function () {
  
  var MML = MathJax.ElementJax.mml,
      TEX = MathJax.InputJax.TeX,
      AMS = MathJax.Extension["TeX/AMSmath"];

  var TEXDEF = TEX.Definitions,
      STACKITEM = TEX.Stack.Item,
      CONFIG = TEX.config.equationNumbers;
      
  var COLS = function (W) {
    var WW = [];
    for (var i = 0, m = W.length; i < m; i++) 
      {WW[i] = TEX.Parse.prototype.Em(W[i])}
    return WW.join(" ");
  };
  
  //
  //  Get the URL of the page (for use with formatURL) when there
  //  is a <base> element on the page.
  //  
  var baseURL = (document.getElementsByTagName("base").length === 0) ? "" :
                String(document.location).replace(/#.*$/,"");

  
  /******************************************************************************/
  
  TEXDEF.Add({
    mathchar0mo: {
      iiiint:     ['2A0C',{texClass: MML.TEXCLASS.OP}]
    },
    
    macros: {
      mathring:   ['Accent','2DA'],  // or 0x30A
      
      nobreakspace: 'Tilde',
      negmedspace:    ['Spacer',MML.LENGTH.NEGATIVEMEDIUMMATHSPACE],
      negthickspace:  ['Spacer',MML.LENGTH.NEGATIVETHICKMATHSPACE],
      
//    intI:       ['Macro','\\mathchoice{\\!}{}{}{}\\!\\!\\int'],
//    iint:       ['MultiIntegral','\\int\\intI'],          // now in core TeX input jax
//    iiint:      ['MultiIntegral','\\int\\intI\\intI'],    // now in core TeX input jax
//    iiiint:     ['MultiIntegral','\\int\\intI\\intI\\intI'], // now in mathchar0mo above
      idotsint:   ['MultiIntegral','\\int\\cdots\\int'],
      
//    dddot:      ['Macro','\\mathop{#1}\\limits^{\\textstyle \\mathord{.}\\mathord{.}\\mathord{.}}',1],
//    ddddot:     ['Macro','\\mathop{#1}\\limits^{\\textstyle \\mathord{.}\\mathord{.}\\mathord{.}\\mathord{.}}',1],
      dddot:      ['Accent','20DB'],
      ddddot:     ['Accent','20DC'],
      
      sideset:    ['Macro','\\mathop{\\mathop{\\rlap{\\phantom{#3}}}\\nolimits#1\\!\\mathop{#3}\\nolimits#2}',3],
      
      boxed:      ['Macro','\\fbox{$\\displaystyle{#1}$}',1],
      
      tag:         'HandleTag',
      notag:       'HandleNoTag',
      label:       'HandleLabel',
      ref:         'HandleRef',
      eqref:       ['HandleRef',true],
      
      substack:   ['Macro','\\begin{subarray}{c}#1\\end{subarray}',1],
      
      injlim:     ['NamedOp','inj&thinsp;lim'],
      projlim:    ['NamedOp','proj&thinsp;lim'],
      varliminf:  ['Macro','\\mathop{\\underline{\\mmlToken{mi}{lim}}}'],
      varlimsup:  ['Macro','\\mathop{\\overline{\\mmlToken{mi}{lim}}}'],
      varinjlim:  ['Macro','\\mathop{\\underrightarrow{\\mmlToken{mi}{lim}}}'],
      varprojlim: ['Macro','\\mathop{\\underleftarrow{\\mmlToken{mi}{lim}}}'],
      
      DeclareMathOperator: 'HandleDeclareOp',
      operatorname:        'HandleOperatorName',
      SkipLimits:          'SkipLimits',
      
      genfrac:     'Genfrac',
      frac:       ['Genfrac',"","","",""],
      tfrac:      ['Genfrac',"","","",1],
      dfrac:      ['Genfrac',"","","",0],
      binom:      ['Genfrac',"(",")","0",""],
      tbinom:     ['Genfrac',"(",")","0",1],
      dbinom:     ['Genfrac',"(",")","0",0],
      
      cfrac:       'CFrac',
      
      shoveleft:  ['HandleShove',MML.ALIGN.LEFT],
      shoveright: ['HandleShove',MML.ALIGN.RIGHT],
      
      xrightarrow: ['xArrow',0x2192,5,6],
      xleftarrow:  ['xArrow',0x2190,7,3]
    },
    
    environment: {
      align:         ['AMSarray',null,true,true,  'rlrlrlrlrlrl',COLS([0,2,0,2,0,2,0,2,0,2,0])],
      'align*':      ['AMSarray',null,false,true, 'rlrlrlrlrlrl',COLS([0,2,0,2,0,2,0,2,0,2,0])],
      multline:      ['Multline',null,true],
      'multline*':   ['Multline',null,false],
      split:         ['AMSarray',null,false,false,'rl',COLS([0])],
      gather:        ['AMSarray',null,true,true,  'c'],
      'gather*':     ['AMSarray',null,false,true, 'c'],
      
      alignat:       ['AlignAt',null,true,true],
      'alignat*':    ['AlignAt',null,false,true],
      alignedat:     ['AlignAt',null,false,false],

      aligned:       ['AlignedAMSArray',null,null,null,'rlrlrlrlrlrl',COLS([0,2,0,2,0,2,0,2,0,2,0]),".5em",'D'],
      gathered:      ['AlignedAMSArray',null,null,null,'c',null,".5em",'D'],

      subarray:      ['Array',null,null,null,null,COLS([0]),"0.1em",'S',1],
      smallmatrix:   ['Array',null,null,null,'c',COLS([1/3]),".2em",'S',1],
      
      'equation':    ['EquationBegin','Equation',true],
      'equation*':   ['EquationBegin','EquationStar',false],

      eqnarray:      ['AMSarray',null,true,true, 'rcl',"0 "+MML.LENGTH.THICKMATHSPACE,".5em"],
      'eqnarray*':   ['AMSarray',null,false,true,'rcl',"0 "+MML.LENGTH.THICKMATHSPACE,".5em"]
    },
    
    delimiter: {
      '\\lvert':     ['007C',{texClass:MML.TEXCLASS.OPEN}],
      '\\rvert':     ['007C',{texClass:MML.TEXCLASS.CLOSE}],
      '\\lVert':     ['2016',{texClass:MML.TEXCLASS.OPEN}],
      '\\rVert':     ['2016',{texClass:MML.TEXCLASS.CLOSE}]
    }
  },null,true);
    

  /******************************************************************************/
  
  TEX.Parse.Augment({

    /*
     *  Add the tag to the environment (to be added to the table row later)
     */
    HandleTag: function (name) {
      var star = this.GetStar();
      var arg = this.trimSpaces(this.GetArgument(name)), tag = arg;
      if (!star) {arg = CONFIG.formatTag(arg)}
      var global = this.stack.global; global.tagID = tag;
      if (global.notags) {
        TEX.Error(["CommandNotAllowedInEnv",
                   "%1 not allowed in %2 environment",
                   name,global.notags]
        );
      }
      if (global.tag) {TEX.Error(["MultipleCommand","Multiple %1",name])}
      global.tag = MML.mtd.apply(MML,this.InternalMath(arg)).With({id:CONFIG.formatID(tag)});
    },
    HandleNoTag: function (name) {
      if (this.stack.global.tag) {delete this.stack.global.tag}
      this.stack.global.notag = true;  // prevent auto-tagging
    },
    
    /*
     *  Record a label name for a tag
     */
    HandleLabel: function (name) {
      var global = this.stack.global, label = this.GetArgument(name);
      if (label === "") return;
      if (!AMS.refUpdate) {
        if (global.label) {TEX.Error(["MultipleCommand","Multiple %1",name])}
        global.label = label;
        if (AMS.labels[label] || AMS.eqlabels[label])
          {TEX.Error(["MultipleLabel","Label '%1' multiply defined",label])}
        AMS.eqlabels[label] = {tag:"???", id:""}; // will be replaced by tag value later
      }
    },
    
    /*
     *  Handle a label reference
     */
    HandleRef: function (name,eqref) {
      var label = this.GetArgument(name);
      var ref = AMS.labels[label] || AMS.eqlabels[label];
      if (!ref) {ref = {tag:"???",id:""}; AMS.badref = !AMS.refUpdate}
      var tag = ref.tag; if (eqref) {tag = CONFIG.formatTag(tag)}
      this.Push(MML.mrow.apply(MML,this.InternalMath(tag)).With({
        href:CONFIG.formatURL(ref.id,baseURL), "class":"MathJax_ref"
      }));
    },
    
    /*
     *  Handle \DeclareMathOperator
     */
    HandleDeclareOp: function (name) {
      var limits = (this.GetStar() ? "" : "\\nolimits\\SkipLimits");
      var cs = this.trimSpaces(this.GetArgument(name));
      if (cs.charAt(0) == "\\") {cs = cs.substr(1)}
      var op = this.GetArgument(name);
      op = op.replace(/\*/g,'\\text{*}').replace(/-/g,'\\text{-}');
      this.setDef(cs, ['Macro', '\\mathop{\\rm '+op+'}'+limits]);
    },
    
    HandleOperatorName: function (name) {
      var limits = (this.GetStar() ? "" : "\\nolimits\\SkipLimits");
      var op = this.trimSpaces(this.GetArgument(name));
      op = op.replace(/\*/g,'\\text{*}').replace(/-/g,'\\text{-}');
      this.string = '\\mathop{\\rm '+op+'}'+limits+" "+this.string.slice(this.i);
      this.i = 0;
    },
    
    SkipLimits: function (name) {
      var c = this.GetNext(), i = this.i;
      if (c === "\\" && ++this.i && this.GetCS() !== "limits") this.i = i;
    },

    /*
     *  Record presence of \shoveleft and \shoveright
     */
    HandleShove: function (name,shove) {
      var top = this.stack.Top();
      if (top.type !== "multline") {
        TEX.Error(["CommandInMultline",
                   "%1 can only appear within the multline environment",name]);
      }
      if (top.data.length) {
        TEX.Error(["CommandAtTheBeginingOfLine",
                   "%1 must come at the beginning of the line",name]);
      }
      top.data.shove = shove;
    },
    
    /*
     *  Handle \cfrac
     */
    CFrac: function (name) {
      var lr  = this.trimSpaces(this.GetBrackets(name,"")),
          num = this.GetArgument(name),
          den = this.GetArgument(name);
      var frac = MML.mfrac(TEX.Parse('\\strut\\textstyle{'+num+'}',this.stack.env).mml(),
                           TEX.Parse('\\strut\\textstyle{'+den+'}',this.stack.env).mml());
      lr = ({l:MML.ALIGN.LEFT, r:MML.ALIGN.RIGHT,"":""})[lr];
      if (lr == null)
        {TEX.Error(["IllegalAlign","Illegal alignment specified in %1",name])}
      if (lr) {frac.numalign = frac.denomalign = lr}
      this.Push(frac);
    },
    
    /*
     *  Implement AMS generalized fraction
     */
    Genfrac: function (name,left,right,thick,style) {
      if (left  == null) {left  = this.GetDelimiterArg(name)}
      if (right == null) {right = this.GetDelimiterArg(name)}
      if (thick == null) {thick = this.GetArgument(name)}
      if (style == null) {style = this.trimSpaces(this.GetArgument(name))}
      var num = this.ParseArg(name);
      var den = this.ParseArg(name);
      var frac = MML.mfrac(num,den);
      if (thick !== "") {frac.linethickness = thick}
      if (left || right) {frac = TEX.fixedFence(left,frac.With({texWithDelims:true}),right)}
      if (style !== "") {
        var STYLE = (["D","T","S","SS"])[style];
        if (STYLE == null)
          {TEX.Error(["BadMathStyleFor","Bad math style for %1",name])}
        frac = MML.mstyle(frac);
        if (STYLE === "D") {frac.displaystyle = true; frac.scriptlevel = 0}
          else {frac.displaystyle = false; frac.scriptlevel = style - 1}
      }
      this.Push(frac);
    },

    /*
     *  Implements multline environment (mostly handled through STACKITEM below)
     */
    Multline: function (begin,numbered) {
      this.Push(begin); this.checkEqnEnv();
      return STACKITEM.multline(numbered,this.stack).With({
        arraydef: {
          displaystyle: true,
          rowspacing: ".5em",
          width: TEX.config.MultLineWidth, columnwidth:"100%",
          side: TEX.config.TagSide,
          minlabelspacing: TEX.config.TagIndent
        }
      });
    },

    /*
     *  Handle AMS aligned environments
     */
    AMSarray: function (begin,numbered,taggable,align,spacing) {
      this.Push(begin); if (taggable) {this.checkEqnEnv()}
      align = align.replace(/[^clr]/g,'').split('').join(' ');
      align = align.replace(/l/g,'left').replace(/r/g,'right').replace(/c/g,'center');
      return STACKITEM.AMSarray(begin.name,numbered,taggable,this.stack).With({
        arraydef: {
          displaystyle: true,
          rowspacing: ".5em",
          columnalign: align,
          columnspacing: (spacing||"1em"),
          rowspacing: "3pt",
          side: TEX.config.TagSide,
          minlabelspacing: TEX.config.TagIndent
        }
      });
    },
    
    AlignedAMSArray: function (begin) {
      var align = this.GetBrackets("\\begin{"+begin.name+"}");
      return this.setArrayAlign(this.AMSarray.apply(this,arguments),align);
    },

    /*
     *  Handle alignat environments
     */
    AlignAt: function (begin,numbered,taggable) {
      var n, valign, align = "", spacing = [];
      if (!taggable) {valign = this.GetBrackets("\\begin{"+begin.name+"}")}
      n = this.GetArgument("\\begin{"+begin.name+"}");
      if (n.match(/[^0-9]/)) {
        TEX.Error(["PositiveIntegerArg","Argument to %1 must me a positive integer",
                  "\\begin{"+begin.name+"}"]);
      }
      while (n > 0) {align += "rl"; spacing.push("0em 0em"); n--}
      spacing = spacing.join(" ");
      if (taggable) {return this.AMSarray(begin,numbered,taggable,align,spacing)}
      var array = this.AMSarray(begin,numbered,taggable,align,spacing);
      return this.setArrayAlign(array,valign);
    },
    
    /*
     *  Handle equation environment
     */
    EquationBegin: function (begin,force) {
      this.checkEqnEnv();
      this.stack.global.forcetag = (force && CONFIG.autoNumber !== "none");
      return begin;
    },
    EquationStar: function (begin,row) {
      this.stack.global.tagged = true; // prevent automatic tagging
      return row;
    },
    
    /*
     *  Check for bad nesting of equation environments
     */
    checkEqnEnv: function () {
      if (this.stack.global.eqnenv)
        {TEX.Error(["ErroneousNestingEq","Erroneous nesting of equation structures"])}
      this.stack.global.eqnenv = true;
    },
    
    /*
     *  Handle multiple integrals (make a mathop if followed by limits)
     */
    MultiIntegral: function (name,integral) {
      var next = this.GetNext();
      if (next === "\\") {
        var i = this.i; next = this.GetArgument(name); this.i = i;
        if (next === "\\limits") {
          if (name === "\\idotsint") {integral = "\\!\\!\\mathop{\\,\\,"+integral+"}"}
                           else {integral = "\\!\\!\\!\\mathop{\\,\\,\\,"+integral+"}"}
        }
      }
      this.string = integral + " " + this.string.slice(this.i);
      this.i = 0;
    },
    
    /*
     *  Handle stretchable arrows
     */
    xArrow: function (name,chr,l,r) {
      var def = {width: "+"+(l+r)+"mu", lspace: l+"mu"};
      var bot = this.GetBrackets(name),
          top = this.ParseArg(name);
      var arrow = MML.mo(MML.chars(String.fromCharCode(chr))).With({
        stretchy: true, texClass: MML.TEXCLASS.REL
      });
      var mml = MML.munderover(arrow);
      mml.SetData(mml.over,MML.mpadded(top).With(def).With({voffset:".15em"}));
      if (bot) {
        bot = TEX.Parse(bot,this.stack.env).mml()
        mml.SetData(mml.under,MML.mpadded(bot).With(def).With({voffset:"-.24em"}));
      }
      this.Push(mml.With({subsupOK:true}));
    },
    
    /*
     *  Get a delimiter or empty argument
     */
    GetDelimiterArg: function (name) {
      var c = this.trimSpaces(this.GetArgument(name));
      if (c == "") return null;
      if (c in TEXDEF.delimiter) return c;
      TEX.Error(["MissingOrUnrecognizedDelim","Missing or unrecognized delimiter for %1",name]);
    },
    
    /*
     *  Get a star following a control sequence name, if any
     */
    GetStar: function () {
      var star = (this.GetNext() === "*");
      if (star) {this.i++}
      return star;
    }
    
  });
  
  /******************************************************************************/
  
  STACKITEM.Augment({
    /*
     *  Increment equation number and form tag mtd element
     */
    autoTag: function () {
      var global = this.global;
      if (!global.notag) {
        AMS.number++; global.tagID = CONFIG.formatNumber(AMS.number.toString());
        var mml = TEX.Parse("\\text{"+CONFIG.formatTag(global.tagID)+"}",{}).mml();
        global.tag = MML.mtd(mml).With({id:CONFIG.formatID(global.tagID)});
      }
    },
  
    /*
     *  Get the tag and record the label, if any
     */
    getTag: function () {
      var global = this.global, tag = global.tag; global.tagged = true;
      if (global.label) {
        if (CONFIG.useLabelIds) {tag.id = CONFIG.formatID(global.label)}
        AMS.eqlabels[global.label] = {tag:global.tagID, id:tag.id};        
      }
      //
      //  Check for repeated ID's (either in the document or as
      //  a previous tag) and find a unique related one. (#240)
      //
      if (document.getElementById(tag.id) || AMS.IDs[tag.id] || AMS.eqIDs[tag.id]) {
        var i = 0, ID;
        do {i++; ID = tag.id+"_"+i}
          while (document.getElementById(ID) || AMS.IDs[ID] || AMS.eqIDs[ID]);
        tag.id = ID; if (global.label) {AMS.eqlabels[global.label].id = ID}
      }
      AMS.eqIDs[tag.id] = 1;
      this.clearTag();
      return tag;
    },
    clearTag: function () {
      var global = this.global;
      delete global.tag; delete global.tagID; delete global.label;
    },

    /*
     *  If the initial child, skipping any initial space or
     *  empty braces (TeXAtom with child being an empty inferred row),
     *  is an <mo>, precede it by an empty <mi> to force the <mo> to
     *  be infix.
     */
    fixInitialMO: function (data) {
      for (var i = 0, m = data.length; i < m; i++) {
        if (data[i] && (data[i].type !== "mspace" &&
           (data[i].type !== "texatom" || (data[i].data[0] && data[i].data[0].data.length)))) {
          if (data[i].isEmbellished()) data.unshift(MML.mi());
          break;
        }
      }
    }
  });
  
  /*
   *  Implement multline environment via a STACKITEM
   */
  STACKITEM.multline = STACKITEM.array.Subclass({
    type: "multline",
    Init: function (numbered,stack) {
      this.SUPER(arguments).Init.apply(this);
      this.numbered = (numbered && CONFIG.autoNumber !== "none");
      this.save = {notag: stack.global.notag};
      stack.global.tagged = !numbered && !stack.global.forcetag; // prevent automatic tagging in starred environments
    },
    EndEntry: function () {
      if (this.table.length) {this.fixInitialMO(this.data)}
      var mtd = MML.mtd.apply(MML,this.data);
      if (this.data.shove) {mtd.columnalign = this.data.shove}
      this.row.push(mtd);
      this.data = [];
    },
    EndRow: function () {
      if (this.row.length != 1) {
        TEX.Error(["MultlineRowsOneCol",
                   "The rows within the %1 environment must have exactly one column",
                   "multline"]);
      }
      this.table.push(this.row); this.row = [];
    },
    EndTable: function () {
      this.SUPER(arguments).EndTable.call(this);
      if (this.table.length) {
        var m = this.table.length-1, i, label = -1;
        if (!this.table[0][0].columnalign) {this.table[0][0].columnalign = MML.ALIGN.LEFT}
        if (!this.table[m][0].columnalign) {this.table[m][0].columnalign = MML.ALIGN.RIGHT}
        if (!this.global.tag && this.numbered) {this.autoTag()}
        if (this.global.tag && !this.global.notags) {
          label = (this.arraydef.side === "left" ? 0 : this.table.length - 1);
          this.table[label] = [this.getTag()].concat(this.table[label]);
        }
        for (i = 0, m = this.table.length; i < m; i++) {
          var mtr = (i === label ? MML.mlabeledtr : MML.mtr);
          this.table[i] = mtr.apply(MML,this.table[i]);
        }
      }
      this.global.notag  = this.save.notag;
    }
  });
  
  /*
   *  Save data about numbering and taging equations, and add
   *  tags at the ends of rows.
   */
  STACKITEM.AMSarray = STACKITEM.array.Subclass({
    type: "AMSarray",
    Init: function (name,numbered,taggable,stack) {
      this.SUPER(arguments).Init.apply(this);
      this.numbered = (numbered && CONFIG.autoNumber !== "none");
      this.save = {notags: stack.global.notags, notag: stack.global.notag};
      stack.global.notags = (taggable ? null : name);
      stack.global.tagged = !numbered && !stack.global.forcetag; // prevent automatic tagging in starred environments
    },
    EndEntry: function () {
      if (this.row.length % 2 === 1) {this.fixInitialMO(this.data)}
      this.row.push(MML.mtd.apply(MML,this.data));
      this.data = [];
    },
    EndRow: function () {
      var mtr = MML.mtr;
      if (!this.global.tag && this.numbered) {this.autoTag()}
      if (this.global.tag && !this.global.notags) {
        this.row = [this.getTag()].concat(this.row);
        mtr = MML.mlabeledtr;
      } else {this.clearTag()}
      if (this.numbered) {delete this.global.notag}
      this.table.push(mtr.apply(MML,this.row)); this.row = [];
    },
    EndTable: function () {
      this.SUPER(arguments).EndTable.call(this);
      this.global.notags = this.save.notags;
      this.global.notag  = this.save.notag;
    }
  });
  
  //
  //  Look for \tag on a formula and make an mtable to include it
  //
  STACKITEM.start.Augment({
    oldCheckItem: STACKITEM.start.prototype.checkItem,
    checkItem: function (item) {
      if (item.type === "stop") {
        var mml = this.mmlData(), global = this.global;
        if (AMS.display && !global.tag && !global.tagged && !global.isInner &&
            (CONFIG.autoNumber === "all" || global.forcetag)) {this.autoTag()}
        if (global.tag) {
          var row = [this.getTag(),MML.mtd(mml)];
          var def = {
            side: TEX.config.TagSide,
            minlabelspacing: TEX.config.TagIndent,
            displaystyle: "inherit"   // replaced by TeX input jax Translate() function with actual value
          };
          mml = MML.mtable(MML.mlabeledtr.apply(MML,row)).With(def);
        }
        return STACKITEM.mml(mml);
      }
      return this.oldCheckItem.call(this,item);
    }
  });
  
  /******************************************************************************/

  /*
   *  Add pre- and post-filters to handle the equation number maintenance.
   */
  TEX.prefilterHooks.Add(function (data) {
    AMS.display = data.display;
    AMS.number = AMS.startNumber;  // reset equation numbers (in case the equation restarted)
    AMS.eqlabels = {};
    AMS.eqIDs = {}; 
    AMS.badref = false;
    if (AMS.refUpdate) {AMS.number = data.script.MathJax.startNumber}
  });
  TEX.postfilterHooks.Add(function (data) {
    data.script.MathJax.startNumber = AMS.startNumber;
    AMS.startNumber = AMS.number;                // equation numbers for next equation
    MathJax.Hub.Insert(AMS.IDs,AMS.eqIDs);       // save IDs from this equation
    MathJax.Hub.Insert(AMS.labels,AMS.eqlabels); // save labels from this equation
    if (AMS.badref && !data.math.texError) {AMS.refs.push(data.script)}  // reprocess later
  },100);
  
  MathJax.Hub.Register.MessageHook("Begin Math Input",function () {
    AMS.refs = [];                 // array of jax with bad references
    AMS.refUpdate = false;
  });
  MathJax.Hub.Register.MessageHook("End Math Input",function (message) {
    if (AMS.refs.length) {
      AMS.refUpdate = true;
      for (var i = 0, m = AMS.refs.length; i < m; i++)
        {AMS.refs[i].MathJax.state = MathJax.ElementJax.STATE.UPDATE}
      return MathJax.Hub.processInput({
        scripts:AMS.refs,
        start: new Date().getTime(),
        i:0, j:0, jax:{}, jaxIDs:[]
      });
    }
    return null;
  });
  
  //
  //  Clear the equation numbers and labels
  //
  TEX.resetEquationNumbers = function (n,keepLabels) {
    AMS.startNumber = (n || 0);
    if (!keepLabels) {
      AMS.labels = {};
      AMS.IDs = {};
    }
  }

  /******************************************************************************/

  MathJax.Hub.Startup.signal.Post("TeX AMSmath Ready");
  
});

MathJax.Ajax.loadComplete("[MathJax]/extensions/TeX/AMSmath.js");
