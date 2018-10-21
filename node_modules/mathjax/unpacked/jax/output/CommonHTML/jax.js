/* -*- Mode: Javascript; indent-tabs-mode:nil; js-indent-level: 2 -*- */
/* vim: set ts=2 et sw=2 tw=80: */

/*************************************************************
 *
 *  MathJax/jax/output/CommonHTML/jax.js
 *
 *  Implements the CommonHTML OutputJax that displays mathematics
 *  using HTML and CSS to position the characters from math fonts
 *  in their proper locations.  Unlike the HTML-CSS output jax,
 *  this HTML is browser and OS independent.
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


(function (AJAX,HUB,HTML,CHTML) {
  var MML;
  var isArray = MathJax.Object.isArray;

  var EVENT, TOUCH, HOVER; // filled in later

  var STRUTHEIGHT = 1,
      EFUZZ = .1,                  // overlap needed for stretchy delimiters
      HFUZZ = .025, DFUZZ = .025;  // adjustments to bounding box of character boxes

  var STYLES = {
    ".mjx-chtml": {
      display:           "inline-block",
      "line-height":     0,
      "text-indent":     0,
      "text-align":      "left",
      "text-transform":  "none",
      "font-style":      "normal",
      "font-weight":     "normal",
      "font-size":       "100%",
      "font-size-adjust":"none",
      "letter-spacing":  "normal",
      "word-wrap":       "normal",
      "word-spacing":    "normal",
      "white-space":     "nowrap",
      "float":           "none",
      "direction":       "ltr",
      "max-width":       "none",
      "max-height":      "none",
      "min-width":       0,
      "min-height":      0,
      border:            0,
      margin:            0,
      padding:           "1px 0"
    },
    ".MJXc-display": {
      display:      "block",
      "text-align": "center",
      "margin":     "1em 0",
      padding:      0
    },
    ".mjx-chtml[tabindex]:focus, body :focus .mjx-chtml[tabindex]": {
      display: "inline-table"  // see issues #1282 and #1338
    },
    ".mjx-full-width": {
      "text-align": "center",
      display: "table-cell!important",
      width:   "10000em"
    },

    ".mjx-math":   {
      "display":         "inline-block",
      "border-collapse": "separate",
      "border-spacing":  0
    },
    ".mjx-math *": {
      display:"inline-block",
      "-webkit-box-sizing": "content-box!important",
      "-moz-box-sizing": "content-box!important",
      "box-sizing": "content-box!important",          // override bootstrap settings
      "text-align":"left"
    },

    ".mjx-numerator":   {display:"block", "text-align":"center"},
    ".mjx-denominator": {display:"block", "text-align":"center"},
    ".MJXc-stacked":    {height:0, position:"relative"},
    ".MJXc-stacked > *":  {position: "absolute"},
    ".MJXc-bevelled > *": {display:"inline-block"},
    
    ".mjx-stack":  {display:"inline-block"},
    ".mjx-op":     {display:"block"},
    ".mjx-under":  {display:"table-cell"},
    ".mjx-over":   {display:"block"},
    ".mjx-over > *": {"padding-left":"0px!important", "padding-right":"0px!important"},
    ".mjx-under > *": {"padding-left":"0px!important", "padding-right":"0px!important"},
    
    ".mjx-stack > .mjx-sup": {display:"block"},
    ".mjx-stack > .mjx-sub": {display:"block"},
    ".mjx-prestack > .mjx-presup": {display:"block"},
    ".mjx-prestack > .mjx-presub": {display:"block"},
    
    ".mjx-delim-h > .mjx-char": {display:"inline-block"},
    
    ".mjx-surd": {"vertical-align":"top"},
    
    ".mjx-mphantom *": {visibility:"hidden"},

    ".mjx-merror": {
      "background-color":"#FFFF88",
      color:             "#CC0000",
      border:            "1px solid #CC0000",
      padding:           "2px 3px",
      "font-style":      "normal",
      "font-size":       "90%"
    },
    
    ".mjx-annotation-xml": {"line-height":"normal"},
    
    ".mjx-menclose > svg": {fill:"none", stroke:"currentColor"},

    ".mjx-mtr":    {display:"table-row"},
    ".mjx-mlabeledtr": {display:"table-row"},
    ".mjx-mtd":    {display:"table-cell", "text-align":"center"},
    ".mjx-label":  {display:"table-row"},

    ".mjx-box":    {display:"inline-block"},
    ".mjx-block":  {display:"block"},
    ".mjx-span":   {display:"inline"},
    ".mjx-char":   {display:"block", "white-space":"pre"},
    ".mjx-itable": {display:"inline-table", width:"auto"},
    ".mjx-row":    {display:"table-row"},
    ".mjx-cell":   {display:"table-cell"},
    ".mjx-table":  {display:"table", width:"100%"},
    ".mjx-line":   {display:"block", height:0},
    ".mjx-strut":  {width:0, "padding-top":STRUTHEIGHT+"em"},
    ".mjx-vsize":  {width:0},

    ".MJXc-space1": {"margin-left":".167em"},
    ".MJXc-space2": {"margin-left":".222em"},
    ".MJXc-space3": {"margin-left":".278em"},
    
    ".mjx-chartest": {
      display:"block",
      visibility: "hidden",
      position:"absolute", top:0,
      "line-height":"normal",
      "font-size":"500%"
    },
    ".mjx-chartest .mjx-char": {display:"inline"},
    ".mjx-chartest .mjx-box": {"padding-top": "1000px"},

    ".MJXc-processing": {
      visibility: "hidden", position:"fixed",
      width: 0, height: 0, overflow:"hidden"
    },
    ".MJXc-processed": {display:"none"},
    
    ".mjx-test": {
      "font-style":      "normal",
      "font-weight":     "normal",
      "font-size":       "100%",
      "font-size-adjust":"none",
      "text-indent":     0,
      "text-transform":  "none",
      "letter-spacing":  "normal",
      "word-spacing":    "normal",
      overflow:          "hidden",
      height:            "1px"
    },
    ".mjx-test.mjx-test-display": {
      display: "table!important"
    },
    ".mjx-test.mjx-test-inline": {
      display:           "inline!important",
      "margin-right":    "-1px"
    },
    ".mjx-test.mjx-test-default": {
      display: "block!important",
      clear:   "both"
    },
    ".mjx-ex-box": {
      display: "inline-block!important",
      position: "absolute",
      overflow: "hidden",
      "min-height": 0, "max-height":"none",
      padding:0, border: 0, margin: 0,
      width:"1px", height:"60ex"
    },
    ".mjx-test-inline .mjx-left-box": {
      display: "inline-block",
      width: 0,
      "float":"left"
    },
    ".mjx-test-inline .mjx-right-box": {
      display: "inline-block",
      width: 0,
      "float":"right"
    },
    ".mjx-test-display .mjx-right-box": {
      display: "table-cell!important",
      width: "10000em!important",
      "min-width":0, "max-width":"none",
      padding:0, border:0, margin:0
    },
    
    "#MathJax_CHTML_Tooltip": {
      "background-color": "InfoBackground", color: "InfoText",
      border: "1px solid black",
      "box-shadow": "2px 2px 5px #AAAAAA",         // Opera 10.5
      "-webkit-box-shadow": "2px 2px 5px #AAAAAA", // Safari 3 and Chrome
      "-moz-box-shadow": "2px 2px 5px #AAAAAA",    // Firefox 3.5
      "-khtml-box-shadow": "2px 2px 5px #AAAAAA",  // Konqueror
      padding: "3px 4px",
      "z-index": 401,
      position: "absolute", left: 0, top: 0,
      width: "auto", height: "auto",
      display: "none"
    }

  };
  
  
  /************************************************************/
  
  var BIGDIMEN = 1000000;
  var MAXREMAP = 5;
  var LINEBREAKS = {}, CONFIG = MathJax.Hub.config;

  CHTML.Augment({
    settings: HUB.config.menuSettings,
    config: {styles: STYLES},

    /********************************************/
    
    Config: function () {
      if (!this.require) {this.require = []}
      this.SUPER(arguments).Config.call(this); var settings = this.settings;
      if (settings.scale) {this.config.scale = settings.scale}
      this.require.push(this.fontDir+"/TeX/fontdata.js");
      this.require.push(MathJax.OutputJax.extensionDir+"/MathEvents.js");
      LINEBREAKS = this.config.linebreaks;
    },

    Startup: function () {
      //
      //  Set up event handling
      //
      EVENT = MathJax.Extension.MathEvents.Event;
      TOUCH = MathJax.Extension.MathEvents.Touch;
      HOVER = MathJax.Extension.MathEvents.Hover;
      this.ContextMenu = EVENT.ContextMenu;
      this.Mousedown   = EVENT.AltContextMenu;
      this.Mouseover   = HOVER.Mouseover;
      this.Mouseout    = HOVER.Mouseout;
      this.Mousemove   = HOVER.Mousemove;

      //
      //  Determine pixels per inch
      //
      var div = CHTML.addElement(document.body,"mjx-block",{style:{display:"block",width:"5in"}});
      this.pxPerInch = div.offsetWidth/5; div.parentNode.removeChild(div);

      //
      // Used in preTranslate to get scaling factors and line width
      //
      this.TestSpan = CHTML.Element("mjx-test",{style:{left:"1em"}},
          [["mjx-left-box"],["mjx-ex-box"],["mjx-right-box"]]);

      //
      //  Set up styles and preload web fonts
      //
      return AJAX.Styles(this.config.styles,["InitializeCHTML",this]);
    },
    
    InitializeCHTML: function () {
      this.getDefaultExEm();
      //
      //  If the defaultEm size is zero, it might be that a web font hasn't
      //  arrived yet, so try to wait for it, but don't wait too long.
      //
      if (this.defaultEm) return;
      var ready = MathJax.Callback();
      AJAX.timer.start(AJAX,function (check) {
        if (check.time(ready)) {HUB.signal.Post(["CommonHTML Jax - no default em size"]); return}
        CHTML.getDefaultExEm();
        if (CHTML.defaultEm) {ready()} else {setTimeout(check,check.delay)}
      },this.defaultEmDelay,this.defaultEmTimeout);
      return ready;
    },
    defaultEmDelay: 100,      // initial delay when checking for defaultEm
    defaultEmTimeout: 1000,   // when to stop looking for defaultEm
    getDefaultExEm: function () {
      //
      //  Get the default sizes (need styles in place to do this)
      //
      var test = document.body.appendChild(this.TestSpan.cloneNode(true));
      test.className += " mjx-test-inline mjx-test-default";
      this.defaultEm    = this.getFontSize(test);
      this.defaultEx    = test.childNodes[1].offsetHeight/60;
      this.defaultWidth = Math.max(0,test.lastChild.offsetLeft-test.firstChild.offsetLeft-2);
      document.body.removeChild(test);
    },
    getFontSize: (window.getComputedStyle ? 
      function (node) {
        var style = window.getComputedStyle(node);
        return parseFloat(style.fontSize);
      } :
      //
      //  IE 8 doesn't do getComputedStyle, so use
      //  an alternative approach
      //
      function (node) {
        return node.style.pixelLeft;
      }
    ),
    getMaxWidth: (window.getComputedStyle ?
      function (node) {
        var style = window.getComputedStyle(node);
        if (style.maxWidth !== "none") return parseFloat(style.maxWidth);
        return 0;
      } :
      //
      //  IE 8 doesn't do getComputedStyle, so use
      //  currentStyle, and a hack to get the pixels for
      //  a non-px max-width
      //
      function (node) {
        var max = node.currentStyle.maxWidth;
        if (max !== "none") {
          if (max.match(/\d*px/)) return parseFloat(max);
          var left = node.style.left;
          node.style.left = max; max = node.style.pixelLeft;
          node.style.left = left;
          return max;
        }
        return 0;
      }
    ),

    //
    //  Load data for a font
    //
    loadFont: function (font) {
      HUB.RestartAfter(AJAX.Require(this.fontDir+"/"+font));
    },
    //
    //  Signal that the font data are loaded
    //
    fontLoaded: function (font) {
      if (!font.match(/-|fontdata/)) font += "-Regular";
      if (!font.match(/\.js$/)) font += ".js"
      MathJax.Callback.Queue(
        ["Post",HUB.Startup.signal,"CommonHTML - font data loaded for " + font],
        ["loadComplete",AJAX,this.fontDir+"/"+font]
      );
    },
    
    Element: function (type,def,content) {
      if (type.substr(0,4) === "mjx-") {
        if (!def) def = {};
        if (def.isMathJax == null) def.isMathJax = true;
        if (def.className) def.className = type+" "+def.className; else def.className = type;
        type = "span";
      }
      return this.HTMLElement(type,def,content);
    },
    addElement: function (node,type,def,content) {
      return node.appendChild(this.Element(type,def,content));
    },
    HTMLElement: HTML.Element,
    ucMatch: HTML.ucMatch,
    setScript: HTML.setScript,
    
    //
    //  Look through the direct children of a node for one with the given
    //  type (but if the node has intervening containers for its children,
    //  step into them; note that elements corresponding to MathML nodes
    //  will have id's so we don't step into them).
    //  
    //  This is used by munderover and msubsup to locate their child elements
    //  when they are part of an embellished operator that is being stretched.
    //  We don't use querySelector because we want to find only the direct child
    //  nodes, not nodes that might be nested deeper in the tree (see issue #1447).
    //
    getNode: function (node,type) {
      var name = RegExp("\\b"+type+"\\b");
      var nodes = [];
      while (node) {
        for (var i = 0, m = node.childNodes.length; i < m; i++) {
          var child = node.childNodes[i];
          if (child) {
            if (name.test(child.className)) return child;
            if (child.id === "") nodes.push(child);
          }
        }
        node = nodes.shift();
      }
      return null;
    },

    /********************************************/
    
    preTranslate: function (state) {
      var scripts = state.jax[this.id], i, m = scripts.length,
          script, prev, node, test, jax, ex, em, scale;
      //
      //  Get linebreaking information
      //
      var maxwidth = 100000, relwidth = false, cwidth = 0,
          linebreak = LINEBREAKS.automatic, width = LINEBREAKS.width;
      if (linebreak) {
        relwidth = !!width.match(/^\s*(\d+(\.\d*)?%\s*)?container\s*$/);
        if (relwidth) {width = width.replace(/\s*container\s*/,"")}
          else {maxwidth = this.defaultWidth}
        if (width === "") {width = "100%"}
      }
      //
      //  Loop through the scripts
      //
      for (i = 0; i < m; i++) {
        script = scripts[i]; if (!script.parentNode) continue;
        //
        //  Remove any existing output
        //
        prev = script.previousSibling;
	if (prev && prev.className && String(prev.className).substr(0,9) === "mjx-chtml")
	  prev.parentNode.removeChild(prev);
        if (script.MathJax.preview) script.MathJax.preview.style.display = "none";
        //
        //  Add the node for the math and mark it as being processed
        //
        jax = script.MathJax.elementJax; if (!jax) continue;
        jax.CHTML = {
          display: (jax.root.Get("display") === "block"),
          preview: (jax.CHTML||{}).preview     // in case typeset calls are interleaved
        };
        node = CHTML.Element("mjx-chtml",{
          id:jax.inputID+"-Frame", className:"MathJax_CHTML", isMathJax:true, jaxID:this.id,
          oncontextmenu:EVENT.Menu, onmousedown: EVENT.Mousedown,
          onmouseover:EVENT.Mouseover, onmouseout:EVENT.Mouseout, onmousemove:EVENT.Mousemove,
	  onclick:EVENT.Click, ondblclick:EVENT.DblClick,
          // Added for keyboard accessible menu.
          onkeydown: EVENT.Keydown, tabIndex: HUB.getTabOrder(jax)
        });
        if (jax.CHTML.display) {
          //
          // Zoom box requires an outer container to get the positioning right.
          //
          var NODE = CHTML.Element("mjx-chtml",{className:"MJXc-display",isMathJax:false});
          NODE.appendChild(node); node = NODE;
        }
        if (HUB.Browser.noContextMenu) {
          node.ontouchstart = TOUCH.start;
          node.ontouchend = TOUCH.end;
        }
        //
        node.className += " MJXc-processing";
        script.parentNode.insertBefore(node,script);
        //
        //  Add test nodes for determining scales and linebreak widths
        //
        test = this.TestSpan.cloneNode(true);
        test.className += " mjx-test-" + (jax.CHTML.display ? "display" : "inline");
        script.parentNode.insertBefore(test,script);
      }
      //
      //  Determine the scaling factors for each script
      //  (this only requires one reflow rather than a reflow for each equation)
      //
      for (i = 0; i < m; i++) {
        script = scripts[i]; if (!script.parentNode) continue;
        test = script.previousSibling;
        jax = script.MathJax.elementJax; if (!jax) continue;
        em = CHTML.getFontSize(test);
        ex = test.childNodes[1].offsetHeight/60;
        cwidth = Math.max(0, jax.CHTML.display ? test.lastChild.offsetWidth - 1: 
                  test.lastChild.offsetLeft - test.firstChild.offsetLeft - 2);
        if (ex === 0 || ex === "NaN") {
          ex = this.defaultEx;
          cwidth = this.defaultWidth;
        }
        if (cwidth === 0 && !jax.CHTML.display) cwidth = this.defaultWidth;
        if (relwidth) maxwidth = cwidth;
        scale = (this.config.matchFontHeight ? ex/this.TEX.x_height/em : 1);
        scale = Math.floor(Math.max(this.config.minScaleAdjust/100,scale)*this.config.scale);
        jax.CHTML.scale = scale/100; jax.CHTML.fontSize = scale+"%";
        jax.CHTML.outerEm = em; jax.CHTML.em = this.em = em * scale/100;
        jax.CHTML.ex = ex; jax.CHTML.cwidth = cwidth/this.em;
        jax.CHTML.lineWidth = (linebreak ? this.length2em(width,maxwidth/this.em,1) : maxwidth);
      }
      //
      //  Remove the test spans used for determining scales and linebreak widths
      //
      for (i = 0; i < m; i++) {
        script = scripts[i]; if (!script.parentNode) continue;
        jax = script.MathJax.elementJax; if (!jax) continue;
        script.parentNode.removeChild(script.previousSibling);
        if (script.MathJax.preview) script.MathJax.preview.style.display = "";
      }
      state.CHTMLeqn = state.CHTMLlast = 0; state.CHTMLi = -1;
      state.CHTMLchunk = this.config.EqnChunk;
      state.CHTMLdelay = false;
    },

    /********************************************/
    
    Translate: function (script,state) {
      if (!script.parentNode) return;

      //
      //  If we are supposed to do a chunk delay, do it
      //
      if (state.CHTMLdelay) {
        state.CHTMLdelay = false;
        HUB.RestartAfter(MathJax.Callback.Delay(this.config.EqnChunkDelay));
      }

      //
      //  Get the data about the math
      //
      var jax = script.MathJax.elementJax, math = jax.root,
          node = document.getElementById(jax.inputID+"-Frame");
      if (!node) return;
      this.getMetrics(jax);
      if (this.scale !== 1) node.style.fontSize = jax.CHTML.fontSize;
      //
      //  Typeset the math
      //
      this.initCHTML(math,node);
      this.savePreview(script);
      this.CHTMLnode = node;
      try {
        math.setTeXclass();
        math.toCommonHTML(node);
      } catch (err) {
        while (node.firstChild) node.removeChild(node.firstChild);
        delete this.CHTMLnode;
        this.restorePreview(script);
        throw err;
      }
      delete this.CHTMLnode;
      this.restorePreview(script);
      //
      //  Put it in place, and remove the processing marker
      //
      if (jax.CHTML.display) node = node.parentNode;
      node.className = node.className.replace(/ [^ ]+$/,"");
      //
      //  Hide the math and don't let its preview be removed
      //
      node.className += " MJXc-processed";
      if (script.MathJax.preview) {
        jax.CHTML.preview = script.MathJax.preview;
        delete script.MathJax.preview;
      }
      //
      //  Check if we should show this chunk of equations
      //
      state.CHTMLeqn += (state.i - state.CHTMLi); state.CHTMLi = state.i;
      if (state.CHTMLeqn >= state.CHTMLlast + state.CHTMLchunk) {
        this.postTranslate(state);
        state.CHTMLchunk = Math.floor(state.CHTMLchunk*this.config.EqnChunkFactor);
        state.CHTMLdelay = true;  // delay if there are more scripts
      }
    },

    initCHTML: function (math,node) {},

    //
    //  MathML previews can contain the same ID's as the HTML output,
    //  which confuses CHTMLnodeElement(), so remove the preview temporarily
    //  and restore it after typesetting the math.
    //
    savePreview: function (script) {
      var preview = script.MathJax.preview;
      if (preview && preview.parentNode) {
        script.MathJax.tmpPreview = document.createElement("span");
        preview.parentNode.replaceChild(script.MathJax.tmpPreview,preview);
      }
    },
    restorePreview: function (script) {
      var tmpPreview = script.MathJax.tmpPreview;
      if (tmpPreview) {
        tmpPreview.parentNode.replaceChild(script.MathJax.preview,tmpPreview);
        delete script.MathJax.tmpPreview;
      }
    },
    //
    //  Get the jax metric information
    //
    getMetrics: function(jax) {
      var data = jax.CHTML;
      this.jax = jax;
      this.em = data.em;
      this.outerEm = data.outerEm;
      this.scale = data.scale;
      this.cwidth = data.cwidth;
      this.linebreakWidth = data.lineWidth;
    },

    /********************************************/
    
    postTranslate: function (state) {
      var scripts = state.jax[this.id];
      //
      //  Reveal this chunk of math
      //
      for (var i = state.CHTMLlast, m = state.CHTMLeqn; i < m; i++) {
        var script = scripts[i];
        if (script && script.MathJax.elementJax) {
          //
          //  Remove the processed marker
          //
          script.previousSibling.className = script.previousSibling.className.replace(/ [^ ]+$/,"");
          var data = script.MathJax.elementJax.CHTML;
          //
          //  Remove the preview, if any
          //
          if (data.preview) {
            data.preview.innerHTML = "";
            script.MathJax.preview = data.preview;
            delete data.preview;
          }
        }
      }
      //
      //  Save our place so we know what is revealed
      //
      state.CHTMLlast = state.CHTMLeqn;
    },

    /********************************************/
    
    getJaxFromMath: function (math) {
      if (math.parentNode.className.match(/MJXc-display/)) math = math.parentNode;
      do {math = math.nextSibling} while (math && math.nodeName.toLowerCase() !== "script");
      return HUB.getJaxFor(math);
    },
    getHoverSpan: function (jax,math) {return jax.root.CHTMLnodeElement()},
    getHoverBBox: function (jax,span,math) {
      var bbox = jax.root.CHTML, em = jax.CHTML.outerEm;
      var BBOX = {w:bbox.w*em, h:bbox.h*em, d:bbox.d*em};
      if (bbox.width) {BBOX.width = bbox.width}
      return BBOX;
    },
    
    Zoom: function (jax,span,math,Mw,Mh) {
      //
      //  Re-render at larger size
      //
      this.getMetrics(jax);
      var node = CHTML.addElement(span,"mjx-chtml",{style:{"font-size":Math.floor(CHTML.scale*100)+"%"},isMathJax:false});
      CHTML.CHTMLnode = node;
      this.idPostfix = "-zoom"; jax.root.toCommonHTML(node); this.idPostfix = "";
      //
      //  Adjust margins to prevent overlaps at the edges
      //
      var style = node.style, bbox = jax.root.CHTML;
      if (bbox.t > bbox.h) style.marginTop = CHTML.Em(bbox.t-bbox.h);
      if (bbox.b > bbox.d) style.marginBottom = CHTML.Em(bbox.b-bbox.d);
      if (bbox.l < 0) style.paddingLeft = CHTML.Em(-bbox.l);
      if (bbox.r > bbox.w) style.marginRight = CHTML.Em(bbox.r-bbox.w);
      //
      //  Get height and width of zoomed math and original math
      //
      style.position = "absolute";
      var zW = node.offsetWidth, zH = node.offsetHeight,
          mH = math.firstChild.offsetHeight, mW = math.firstChild.offsetWidth;
      node.style.position = "";
      //
      return {Y:-EVENT.getBBox(span).h, mW:mW, mH:mH, zW:zW, zH:zH};
    },

    Remove: function (jax) {
      var node = document.getElementById(jax.inputID+"-Frame");
      if (node && jax.CHTML.display) node = node.parentNode;
      if (node) node.parentNode.removeChild(node);
      delete jax.CHTML;
    },
    
    /********************************************/
    
    ID: 0, idPostfix: "",
    GetID: function () {this.ID++; return this.ID},
    
    /********************************************/

    MATHSPACE: {
      veryverythinmathspace:  1/18,
      verythinmathspace:      2/18,
      thinmathspace:          3/18,
      mediummathspace:        4/18,
      thickmathspace:         5/18,
      verythickmathspace:     6/18,
      veryverythickmathspace: 7/18,
      negativeveryverythinmathspace:  -1/18,
      negativeverythinmathspace:      -2/18,
      negativethinmathspace:          -3/18,
      negativemediummathspace:        -4/18,
      negativethickmathspace:         -5/18,
      negativeverythickmathspace:     -6/18,
      negativeveryverythickmathspace: -7/18,

      thin: .04,
      medium: .06,
      thick: .1,

      infinity: BIGDIMEN
    },
    SPACECLASS: {
      thinmathspace:   "MJXc-space1",
      mediummathspace: "MJXc-space2",
      thickmathspace:  "MJXc-space3"
    },
    pxPerInch: 96,
    em: 16,
    
    maxStretchyParts: 1000,            // limit the number of parts allowed for
                                       // stretchy operators. See issue 366.

    FONTDEF: {},
    TEXDEF: {
      x_height:         .442,
      quad:             1,
      num1:             .676508,
      num2:             .393732,
      num3:             .44373,
      denom1:           .685951,
      denom2:           .344841,
      sup1:             .412892,
      sup2:             .362892,
      sup3:             .288888,
      sub1:             .15,
      sub2:             .247217,
      sup_drop:         .386108,
      sub_drop:         .05,
      delim1:          2.39,
      delim2:          1.0,
      axis_height:      .25,
      rule_thickness:   .06,
      big_op_spacing1:  .111111,
      big_op_spacing2:  .166666,
      big_op_spacing3:  .2,
      big_op_spacing4:  .45, //.6,  // better spacing for under arrows and braces
      big_op_spacing5:  .1,

      surd_height:      .075,
      
      scriptspace:         .05,
      nulldelimiterspace:  .12,
      delimiterfactor:     901,
      delimitershortfall:   .3,

      min_rule_thickness:  1.25     // in pixels
    },
    
    /********************************************************/
    
    //
    //  True if text holds a single (unicode) glyph
    //
    isChar: function (text) {
      if (text.length === 1) return true;
      if (text.length !== 2) return false;
      var n = text.charCodeAt(0);
      return (n >= 0xD800 && n < 0xDBFF);
    },
    //
    //  Get a unicode character by number (even when it takes two character)
    //
    unicodeChar: function (n) {
      if (n < 0xFFFF) return String.fromCharCode(n);
      n -= 0x10000;
      return String.fromCharCode((n>>10)+0xD800) + String.fromCharCode((n&0x3FF)+0xDC00);
    },
    //
    //  Get the unicode number of a (possibly multi-character) string
    //
    getUnicode: function (string) {
      var n = string.text.charCodeAt(string.i); string.i++;
      if (n >= 0xD800 && n < 0xDBFF) {
        n = (((n-0xD800)<<10)+(string.text.charCodeAt(string.i)-0xDC00))+0x10000;
        string.i++;
      }
      return n;
    },
    //
    //  Get the list of actions for a given character in a given variant
    //  (processing remaps, multi-character results, and so on).  Results are
    //  cached so that future lookups for the same variant/n pair will not
    //  require looking through the data again.
    //
    getCharList: function (variant,n) {
      var id, M, cache = variant.cache, nn = n;
      if (cache[n]) return cache[n];
      if (n > 0xFFFF && this.FONTDATA.RemapPlane1) {
        var nv = this.FONTDATA.RemapPlane1(n,variant);
        n = nv.n; variant = nv.variant;
      }
      var RANGES = this.FONTDATA.RANGES, VARIANT = this.FONTDATA.VARIANT;
      if (n >= RANGES[0].low && n <= RANGES[RANGES.length-1].high) {
        for (id = 0, M = RANGES.length; id < M; id++) {
          if (RANGES[id].name === "alpha" && variant.noLowerCase) continue;
          var N = variant["offset"+RANGES[id].offset];
          if (N && n >= RANGES[id].low && n <= RANGES[id].high) {
            if (RANGES[id].remap && RANGES[id].remap[n]) {
              n = N + RANGES[id].remap[n];
            } else {
              n = n - RANGES[id].low + N;
              if (RANGES[id].add) {n += RANGES[id].add}
            }
            if (variant["variant"+RANGES[id].offset])
              variant = VARIANT[variant["variant"+RANGES[id].offset]];
            break;
          }
        }
      }
      cache[nn] = this.remapChar(variant,n,0);
      return cache[nn];
    },
    remapChar: function (variant,n,N) {
      var list = [], VARIANT = this.FONTDATA.VARIANT;
      if (variant.remap && variant.remap[n]) {
        n = variant.remap[n];
        if (variant.remap.variant) {variant = VARIANT[variant.remap.variant]}
      } else if (this.FONTDATA.REMAP[n] && !variant.noRemap) {
        n = this.FONTDATA.REMAP[n];
      }
      if (isArray(n)) {
        if (n[2]) N = MAXREMAP; // stop remapping
        variant = VARIANT[n[1]]; n = n[0];
      } 
      if (typeof(n) === "string") {
        var string = {text:n, i:0, length:n.length};
        while (string.i < string.length) {
          n = this.getUnicode(string);
          var chars = this.getCharList(variant,n);
          if (chars) list.push.apply(list,chars);
        }
      } else {
        if (variant.cache[n]) {list = variant.cache[n]}
          else {variant.cache[n] = list = this.lookupChar(variant,n,N)}
      }
      return list;
    },
    //
    //  After all remapping has been done, look up a character
    //  in the fonts for a given variant, chaining to other
    //  variants as needed.  Return an undefined character if
    //  it isn't found in the given variant.
    //
    lookupChar: function (variant,n,N) {
      var VARIANT = variant;
      while (variant) {
        for (var i = 0, m = variant.fonts.length; i < m; i++) {
          var font = this.FONTDATA.FONTS[variant.fonts[i]];
          if (typeof(font) === "string") this.loadFont(font);
          var C = font[n];
          if (C) {
            this.fixChar(C,n);
            if (C[5].space) return [{type:"space", w:C[2], font:font}];
            return [{type:"char", font:font, n:n}];
          } else if (font.Extra) {
            this.findBlock(font,n);
          }
        }
        variant = this.FONTDATA.VARIANT[variant.chain];
        if (variant && variant.remap && variant.remap[n] && N++ < MAXREMAP) {
          return this.remapChar(variant,n,N);
        }
      }
      return [this.unknownChar(VARIANT,n)];
    },
    fixChar: function (C,n) {
      if (C.length === 5) C[5] = {};
      if (C.c == null) {
        C[0] /= 1000; C[1] /= 1000; C[2] /= 1000; C[3] /= 1000; C[4] /= 1000;
        C.c = this.unicodeChar(n);
      }
      return C;
    },
    findBlock: function (font,n) {
      var extra = font.Extra, name = font.file, file;
      for (var i = 0, m = extra.length; i < m; i++) {
        if (typeof(extra[i]) === "number") {
          if (n === extra[i]) {file = name; break}
        } else {
          if (n <  extra[i][0]) return;
          if (n <= extra[i][1]) {file = name; break}
        }
      }
      //
      //  Currently this only loads one extra file, but that
      //  might need to be expanded in the future.
      //
      if (file) {delete font.Extra; this.loadFont(name)}
    },
    //
    //  Create a fake font entry for an unknown character.
    //
    unknownChar: function (variant,n) {
      HUB.signal.Post(["CommonHTML Jax - unknown char",n,variant]);
      var id = ""; if (variant.bold) id += "B"; if (variant.italic) id += "I";
      var unknown = this.FONTDATA.UNKNOWN[id||"R"]; // cache of previously measured characters
      if (!unknown[n]) this.getUnknownChar(unknown,n);
      return {type:"unknown", n:n, font:unknown};
    },
    getUnknownChar: function (unknown,n) {
      var c = this.unicodeChar(n);
      var HDW = this.getHDW(c,unknown.className);
      // ### FIXME:  provide a means of setting the height and depth for individual characters
      unknown[n] = [.8,.2,HDW.w,0,HDW.w,{a:Math.max(0,(HDW.h-HDW.d)/2), h:HDW.h, d:HDW.d}];
      unknown[n].c = c;
    },
    styledText: function (variant,text) {
      HUB.signal.Post(["CommonHTML Jax - styled text",text,variant]);
      var style = variant.style;
      var id = "_"+(style["font-family"]||variant.className||"");
      if (style["font-weight"]) id += "_"+style["font-weight"];
      if (style["font-style"])  id += "_"+style["font-style"];
      if (!this.STYLEDTEXT) this.STYLEDTEXT = {};
      if (!this.STYLEDTEXT[id]) this.STYLEDTEXT[id] = {className:variant.className||""};
      var unknown = this.STYLEDTEXT[id];
      if (!unknown["_"+text]) {
        var HDW = this.getHDW(text,variant.className||"",style);
        unknown["_"+text] = [.8,.2,HDW.w,0,HDW.w,{a:Math.max(0,(HDW.h-HDW.d)/2), h:HDW.h, d:HDW.d}];
        unknown["_"+text].c = text;
      }
      return {type:"unknown", n:"_"+text, font:unknown, style:style, rscale:variant.rscale};
    },

    //
    //  Get the height, depth, and width of a character
    //  (height and depth are of the font, not the character).
    //  WARNING:  causes reflow of the page!
    //
    getHDW: function (c,name,styles) {
      var test1 = CHTML.addElement(CHTML.CHTMLnode,"mjx-chartest",{className:name},[["mjx-char",{style:styles},[c]]]);
      var test2 = CHTML.addElement(CHTML.CHTMLnode,"mjx-chartest",{className:name},[["mjx-char",{style:styles},[c,["mjx-box"]]]]);
      test1.firstChild.style.fontSize = test2.firstChild.style.fontSize = "";
      var em = 5*CHTML.em;
      var H1 = test1.offsetHeight, H2 = test2.offsetHeight, W = test1.offsetWidth;
      CHTML.CHTMLnode.removeChild(test1);
      CHTML.CHTMLnode.removeChild(test2);
      if (H2 === 0) {
        em = 5*CHTML.defaultEm;
        var test = document.body.appendChild(document.createElement("div"));
        test.appendChild(test1); test.appendChild(test2);
        H1 = test1.offsetHeight, H2 = test2.offsetHeight, W = test1.offsetWidth;
        document.body.removeChild(test);
      }
      var d = (H2-1000)/em, w = W/em, h = H1/em - d;
      return {h:h, d:d, w:w}
    },
    

    /********************************************************/
    
    //
    //  Process a character list into a given node and return
    //  the updated bounding box.
    //
    addCharList: function (node,list,bbox) {
      var state = {text:"", className:null, a:0};
      for (var i = 0, m = list.length; i < m; i++) {
        var item = list[i];
        if (this.charList[item.type]) (this.charList[item.type])(item,node,bbox,state,m);
      }
      if (state.text !== "") {
        if (node.childNodes.length) {
          this.charList.flushText(node,state);
        } else {
          HTML.addText(node,state.text);
          if (node.className) node.className += " "+state.className;
            else node.className = state.className;
        }
      }
      bbox.b = (state.flushed ? 0 : bbox.a);
    },
    //
    //  The various item types are processed by these
    //  functions.
    //
    charList: {
      //
      //  Character from the known fonts
      //
      "char": function (item,node,bbox,state,m) {
        var font = item.font, remap = (font.remapCombining||{})[item.n];
        if (font.className === state.className) {
          remap = null;
        } else if (state.className || (remap && state.text !== "")) {
          this.flushText(node,state);
        }
        if (!state.a) state.a = font.centerline/1000;
        if (state.a > (bbox.a||0)) bbox.a = state.a;
        state.className = font.className;
        var C = font[item.n];
        if (remap) {
          var FONT = font;
          if (isArray(remap)) {
            FONT = CHTML.FONTDATA.FONTS[remap[1]];
            remap = remap[0];
            if (typeof(FONT) === 'string') CHTML.loadFont(FONT);
          }
          if (FONT[item.n]) CHTML.fixChar(FONT[item.n],item.n);
          C = CHTML.fixChar(FONT[remap],remap);
          state.className = FONT.className;
        }
        state.text += C.c;
        if (bbox.h < C[0]+HFUZZ) bbox.t = bbox.h = C[0]+HFUZZ;
        if (bbox.d < C[1]+DFUZZ) bbox.b = bbox.d = C[1]+DFUZZ;
        if (bbox.l > bbox.w+C[3]) bbox.l = bbox.w+C[3];
        if (bbox.r < bbox.w+C[4]) bbox.r = bbox.w+C[4];
        bbox.w += C[2] * (item.rscale||1);
        if (m == 1 && font.skew && font.skew[item.n]) bbox.skew = font.skew[item.n];
        if (C[5] && C[5].rfix) this.flushText(node,state).style.marginRight = CHTML.Em(C[5].rfix/1000);
        if (remap) {
          //
          //  Remap combining characters to non-combining versions since Safari
          //  handles them differently from everyone else.  (#1709)
          //
          var chr = this.flushText(node,state);
          var r = (FONT[item.n]||font[item.n])[4] - (C[4] - C[2]);
          chr.style.marginLeft = CHTML.Em(-C[2]-r);
          if (r < 0) chr.style.marginRight = CHTML.Em(-r);
        }
      },
      //
      //  Space characters (not actually in the fonts)
      //
      space: function (item,node,bbox,state) {
        if (item.w) {
          if (state.text === "") state.className = item.font.className;
          this.flushText(node,state).style.marginRight = CHTML.Em(item.w);
          bbox.w += item.w;
        }
      },
      //
      //  An unknown character (one not in the font data)
      //
      unknown: function (item,node,bbox,state) {
        (this["char"])(item,node,bbox,state,0);
        var C = item.font[item.n];
        if (C[5].a) {
          state.a = C[5].a;
          if (bbox.a == null || state.a > bbox.a) bbox.a = state.a;
        }
        node = this.flushText(node,state,item.style);
        if (C[2] < 3) node.style.width = CHTML.Em(C[2]); // only force width if not too large (#1718)
      },
      //
      //  Put the pending text into a box of the class, and
      //  reset the data about the text.
      //
      flushText: function (node,state,style) {
        node = CHTML.addElement(node,"mjx-charbox",
          {className:state.className,style:style},[state.text]);
        if (state.a) node.style.paddingBottom = CHTML.Em(state.a);
        state.text = ""; state.className = null; state.a = 0; state.flushed = true;
        return node;
      }
    },

    //
    //  Add the given text (in the given variant) into the given node, and
    //  update the bounding box of the result.  Make sure the node's DOM
    //  bounding box matches the contents.
    //
    handleText: function (node,text,variant,bbox) {
      if (node.childNodes.length === 0) {
        CHTML.addElement(node,"mjx-char");
        bbox = CHTML.BBOX.empty(bbox);
      }
      if (typeof(variant) === "string") variant = this.FONTDATA.VARIANT[variant];
      if (!variant) variant = this.FONTDATA.VARIANT[MML.VARIANT.NORMAL];
      var string = {text:text, i:0, length:text.length}, list = [];
      if (variant.style && string.length) {
        list.push(this.styledText(variant,text));
      } else {
        while (string.i < string.length) {
          var n = this.getUnicode(string);
          list.push.apply(list,this.getCharList(variant,n));
        }
      }
      if (list.length) this.addCharList(node.firstChild,list,bbox);
      bbox.clean();
      if (bbox.d < 0) {bbox.D = bbox.d; bbox.d = 0}
      if (bbox.h - bbox.a) node.firstChild.style[bbox.h - bbox.a < 0 ? "marginTop" : "paddingTop"] = this.EmRounded(bbox.h-bbox.a);
      if (bbox.d > -bbox.b) node.firstChild.style.paddingBottom = this.EmRounded(bbox.d+bbox.b);
      return bbox;
    },

    /********************************************************/

    createDelimiter: function (node,code,HW,BBOX,font) {
      if (!code) {
        var bbox = this.BBOX.zero();
        bbox.w = bbox.r = this.TEX.nulldelimiterspace;
        CHTML.addElement(node,"mjx-box",{style:{width:bbox.w}});
        return bbox;
      }
      if (!(HW instanceof Array)) HW = [HW,HW];
      var hw = HW[1]; HW = HW[0];
      var delim = {alias: code};
      while (delim.alias) {
        code = delim.alias; delim = this.FONTDATA.DELIMITERS[code];
        if (!delim) {delim = {HW: [0,this.FONTDATA.VARIANT[MML.VARIANT.NORMAL]]}}
      }
      if (delim.load) HUB.RestartAfter(AJAX.Require(this.fontDir+"/TeX/fontdata-"+delim.load+".js"));
      for (var i = 0, m = delim.HW.length; i < m; i++) {
        if (delim.HW[i][0] >= HW-.01 || (i == m-1 && !delim.stretch)) {
          if (delim.HW[i][3]) code = delim.HW[i][3];
          bbox = this.createChar(node,[code,delim.HW[i][1]],(delim.HW[i][2]||1),font);
          bbox.offset = .6 * bbox.w;
          if (BBOX) {bbox.scale = BBOX.scale; BBOX.rscale = BBOX.rscale}
          return bbox;
        }
      }
      if (!delim.stretch) return bbox;
      return this["extendDelimiter"+delim.dir](node,hw,delim.stretch,BBOX,font);
    },
    extendDelimiterV: function (node,H,delim,BBOX,font) {
      node = CHTML.addElement(node,"mjx-delim-v"); var tmp = CHTML.Element("span");
      var top, bot, mid, ext, tbox, bbox, mbox, ebox, k = 1, c;
      tbox = this.createChar(tmp,(delim.top||delim.ext),1,font); top = tmp.removeChild(tmp.firstChild);
      bbox = this.createChar(tmp,(delim.bot||delim.ext),1,font); bot = tmp.removeChild(tmp.firstChild);
      mbox = ebox = CHTML.BBOX.zero();
      var h = tbox.h + tbox.d + bbox.h + bbox.d - EFUZZ;
      node.appendChild(top);
      if (delim.mid) {
        mbox = this.createChar(tmp,delim.mid,1,font); mid = tmp.removeChild(tmp.firstChild);
        h += mbox.h + mbox.d; k = 2;
      }
      if (delim.min && H < h*delim.min) H = h*delim.min;
      if (H > h) {
        ebox = this.createChar(tmp,delim.ext,1,font); ext = tmp.removeChild(tmp.firstChild);
        var eH = ebox.h + ebox.d, eh = eH - EFUZZ;
        var n = Math.min(Math.ceil((H-h)/(k*eh)),this.maxStretchyParts);
        if (delim.fullExtenders) H = n*k*eh + h; else eh = (H-h)/(k*n);
        c = ebox.d + ebox.a - eH/2; // for centering of extenders
        ext.style.margin = ext.style.padding = "";
        ext.style.lineHeight = CHTML.Em(eh);
        ext.style.marginBottom = CHTML.Em(c-EFUZZ/2/k);
        ext.style.marginTop = CHTML.Em(-c-EFUZZ/2/k);
        var TEXT = ext.textContent, text = "\n"+TEXT;
        while (--n > 0) TEXT += text;
        ext.textContent = TEXT;
        node.appendChild(ext);
        if (delim.mid) {
          node.appendChild(mid);
          node.appendChild(ext.cloneNode(true));
        }
      } else {
        c = (H-h-EFUZZ) / k;
        top.style.marginBottom = CHTML.Em(c+parseFloat(top.style.marginBottom||"0"));
        if (delim.mid) node.appendChild(mid);
        bot.style.marginTop = CHTML.Em(c+parseFloat(bot.style.marginTop||"0"));
      }
      node.appendChild(bot);
      var vbox = CHTML.BBOX({
        w:  Math.max(tbox.w,ebox.w,bbox.w,mbox.w),
        l: Math.min(tbox.l,ebox.l,bbox.l,mbox.l),
        r: Math.max(tbox.r,ebox.r,bbox.r,mbox.r),
        h: H-bbox.d, d: bbox.d, t: H-bbox.d, b: bbox.d
      });
      vbox.offset = .5 * vbox.w;
      if (BBOX) {vbox.scale = BBOX.scale; vbox.rscale = BBOX.rscale}
      return vbox;
    },
    extendDelimiterH: function (node,W,delim,BBOX,font) {
      node = CHTML.addElement(node,"mjx-delim-h"); var tmp = CHTML.Element("span");
      var left, right, mid, ext, ext2, lbox, rbox, mbox, ebox, k = 1;
      lbox = this.createChar(tmp,(delim.left||delim.rep),1,font); left = tmp.removeChild(tmp.firstChild);
      rbox = this.createChar(tmp,(delim.right||delim.rep),1,font); right = tmp.removeChild(tmp.firstChild);
      ebox = this.createChar(tmp,delim.rep,1,font); ext = tmp.removeChild(tmp.firstChild);
      left.style.marginLeft = CHTML.Em(-lbox.l);
      right.style.marginRight = CHTML.Em(rbox.r-rbox.w);
      node.appendChild(left); 
      var hbox = CHTML.BBOX.zero(); 
      hbox.h = Math.max(lbox.h,rbox.h,ebox.h);
      hbox.d = Math.max(lbox.D||lbox.d,rbox.D||rbox.d,ebox.D||ebox.d);
      var w = (lbox.r - lbox.l) + (rbox.r - rbox.l) - EFUZZ;
      if (delim.mid) {
        mbox = this.createChar(tmp,delim.mid,1,font);
        mid = tmp.removeChild(tmp.firstChild);
        mid.style.marginleft = CHTML.Em(-mbox.l); mid.style.marginRight = CHTML.Em(mbox.r-mbox.w);
        w += mbox.r - mbox.l + EFUZZ; k = 2;
        if (mbox.h > hbox.h) hbox.h = mbox.h;
        if (mbox.d > hbox.d) hbox.d = mbox.d;
      }
      if (delim.min && W < w*delim.min) W = w*delim.min;
      hbox.w = hbox.r = W;
      if (W > w) {
        var eW = ebox.r-ebox.l, ew = eW - EFUZZ;
        var n = Math.min(Math.ceil((W-w)/(k*ew)),this.maxStretchyParts);
        if (delim.fullExtenders) W = n*k*ew + w; else ew = (W-w)/(k*n);
        var c = (eW - ew + EFUZZ/k) / 2; // for centering of extenders
        ext.style.marginLeft = CHTML.Em(-ebox.l-c);
        ext.style.marginRight = CHTML.Em(ebox.r-ebox.w+c);
        ext.style.letterSpacing = CHTML.Em(-(ebox.w-ew));
        left.style.marginRight = CHTML.Em(lbox.r-lbox.w);
        right.style.marginleft = CHTML.Em(-rbox.l);
        var TEXT = ext.textContent, text = TEXT;
        while (--n > 0) TEXT += text;
        ext.textContent = TEXT;
        node.appendChild(ext);
        if (delim.mid) {
          node.appendChild(mid);
          ext2 = node.appendChild(ext.cloneNode(true));
        }
      } else {
        c = (W-w-EFUZZ/k) / 2;
        left.style.marginRight = CHTML.Em(lbox.r-lbox.w+c);
        if (delim.mid) node.appendChild(mid);
        right.style.marginLeft = CHTML.Em(-rbox.l+c);
      }
      node.appendChild(right);
      this.adjustHeights([left,ext,mid,ext2,right],[lbox,ebox,mbox,ebox,rbox],hbox);
      if (BBOX) {hbox.scale = BBOX.scale; hbox.rscale = BBOX.rscale}
      return hbox;
    },
    adjustHeights: function (nodes,box,bbox) {
      //
      //  To get alignment right in horizontal delimiters, we force all
      //  the elements to the same height and depth
      //
      var T = bbox.h, B = bbox.d;
      if (bbox.d < 0) {B = -bbox.d; bbox.D = bbox.d; bbox.d = 0}
      for (var i = 0, m = nodes.length; i < m; i++) if (nodes[i]) {
        nodes[i].style.paddingTop = CHTML.Em(T-box[i].a);
        nodes[i].style.paddingBottom = CHTML.Em(B+box[i].a);
        nodes[i].style.marginTop = nodes[i].style.marginBottom = 0;
      }
    },
    createChar: function (node,data,scale,font) {
      // ### FIXME: handle cache better (by data[1] and font)
      var text = "", variant = {fonts: [data[1]], noRemap:true, cache:{}};
      if (font && font === MML.VARIANT.BOLD && this.FONTDATA.FONTS[data[1]+"-Bold"])
        variant.fonts = [data[1]+"-Bold",data[1]];
      if (typeof(data[1]) !== "string") variant = data[1];
      if (data[0] instanceof Array) {
        for (var i = 0, m = data[0].length; i < m; i++) text += String.fromCharCode(data[0][i]);
      } else text = String.fromCharCode(data[0]);
      if (data[4]) scale *= data[4];
      var bbox = this.handleText(node,text,variant), style = node.firstChild.style;
      if (scale !== 1) style.fontSize = this.Percent(scale);
      if (data[2]) {  // x offset
        style.paddingLeft = this.Em(data[2]);
        bbox.w += data[2]; bbox.r += data[2];
      }
      if (data[3]) {  // y offset
        style.verticalAlign = this.Em(data[3]);
        bbox.h += data[3]; if (bbox.h < 0) bbox.h = 0;
      }
      if (data[5]) {  // extra height
        style.marginTop = this.Em(data[5]);
        bbox.h += data[5]; bbox.t += data[5];
      }
      if (data[6]) {  // extra depth
        style.marginBottom = this.Em(data[6]);
        bbox.d += data[6]; bbox.b += data[6];
      }
      return bbox;
    },

    /********************************************************/
    
    //
    //  ### FIXME: Handle mu's
    //
    length2em: function (length,size,scale) {
      if (typeof(length) !== "string") length = length.toString();
      if (length === "") return "";
      if (length === MML.SIZE.NORMAL) return 1;
      if (length === MML.SIZE.BIG)    return 2;
      if (length === MML.SIZE.SMALL)  return .71;
      if (this.MATHSPACE[length])     return this.MATHSPACE[length];
      var match = length.match(/^\s*([-+]?(?:\.\d+|\d+(?:\.\d*)?))?(pt|em|ex|mu|px|pc|in|mm|cm|%)?/);
      var m = parseFloat(match[1]||"1"), unit = match[2];
      if (size == null) size = 1;  if (!scale) scale = 1;
      scale = 1 /this.em / scale;
      if (unit === "em") return m;
      if (unit === "ex") return m * this.TEX.x_height;
      if (unit === "%")  return m / 100 * size;
      if (unit === "px") return m * scale;
      if (unit === "pt") return m / 10;                 // 10 pt to an em
      if (unit === "pc") return m * 1.2;                // 12 pt to a pc
      scale *= this.pxPerInch;
      if (unit === "in") return m * scale;
      if (unit === "cm") return m * scale / 2.54;       // 2.54 cm to an inch
      if (unit === "mm") return m * scale / 25.4;       // 10 mm to a cm
      if (unit === "mu") return m / 18;                 // 18mu to an em for the scriptlevel
      return m*size;  // relative to given size (or 1em as default)
    },
    thickness2em: function (length,scale) {
      var thick = CHTML.TEX.rule_thickness/(scale||1);
      if (length === MML.LINETHICKNESS.MEDIUM) return thick;
      if (length === MML.LINETHICKNESS.THIN)   return .67*thick;
      if (length === MML.LINETHICKNESS.THICK)  return 1.67*thick;
      return this.length2em(length,thick,scale);
    },

    Em: function (m) {
      if (Math.abs(m) < .001) return "0";
      return (m.toFixed(3).replace(/\.?0+$/,""))+"em";
    },
    EmRounded: function (m) {
      m = (Math.round(m*CHTML.em)+.05)/CHTML.em;
      if (Math.abs(m) < .0006) {return "0em"}
      return m.toFixed(3).replace(/\.?0+$/,"") + "em";
    },
    unEm: function (m) {
      return parseFloat(m);
    },
    Px: function (m,M) {
      m *= this.em;
      if (M && m < M) m = M;
      if (Math.abs(m) < .1) return "0";
      return m.toFixed(1).replace(/\.0$/,"")+"px";
    },
    
    Percent: function (m) {
      return (100*m).toFixed(1).replace(/\.?0+$/,"") + "%";
    },
    
    Transform: function (node,trans,origin) {
      var style = node.style;
      style.transform = style.WebkitTransform = style.MozTransform = style["-ms-transform"] = trans;
      if (origin)
        style.transformOrigin = style.WebkitTransformOrigin =
          style.MozTransformOrigin = style["-ms-transform-origin"] = origin;
    },

    /********************************************************/
    
    arrayEntry: function (a,i) {return a[Math.max(0,Math.min(i,a.length-1))]},

    //
    //  Styles to be removed from style="..." attributes
    //
    removeStyles: ["fontSize","fontFamily","fontWeight","fontStyle","fontVariant","font"]
    
  });

  /**********************************************************/

  CHTML.BBOX = MathJax.Object.Subclass({
    Init: function (def) {
      for (var id in def) {
        if (def.hasOwnProperty(id)) this[id] = def[id];
      }
    },
    clean: function () {
      if (this.h === -BIGDIMEN) this.h = 0;
      if (this.d === -BIGDIMEN) this.d = 0;
      if (this.l ===  BIGDIMEN) this.l = 0;
      if (this.r === -BIGDIMEN) this.r = 0;
      if (this.t === -BIGDIMEN) this.t = 0;
      if (this.b === -BIGDIMEN) this.b = 0;
      if (this.D && this.d > 0) delete this.D;
    },
    rescale: function (scale) {
      this.w *= scale; this.h *= scale; this.d *= scale;
      this.l *= scale; this.r *= scale; this.t *= scale; this.b *= scale;
      if (this.L) this.L *= scale;
      if (this.R) this.R *= scale;
      if (this.D) this.D *= scale;
    },
    combine: function (cbox,x,y) {
      cbox.X = x; cbox.Y = y;  // save for use with line breaking
      var scale = cbox.rscale;
      if (x + scale*cbox.r > this.r) this.r = x + scale*cbox.r;
      if (x + scale*cbox.l < this.l) this.l = x + scale*cbox.l;
      if (x + scale*(cbox.w+(cbox.L||0)+(cbox.R||0)) > this.w)
        this.w  = x + scale*(cbox.w + (cbox.L||0) + (cbox.R||0));
      if (y + scale*cbox.h > this.h) this.h = y + scale*cbox.h;
      if (cbox.D && (this.D == null || scale*cbox.D - y > this.D) && scale*cbox.D > this.d) this.D = scale*cbox.D - y;
        else if (cbox.D == null && this.D) delete this.D;
      if (scale*cbox.d - y > this.d) this.d = scale*cbox.d - y;
      if (y + scale*cbox.t > this.t) this.t = y + scale*cbox.t;
      if (scale*cbox.b - y > this.b) this.b = scale*cbox.b - y;
    },
    append: function (cbox) {
      var scale = cbox.rscale; var x = this.w;
      if (x + scale*cbox.r > this.r) this.r = x + scale*cbox.r;
      if (x + scale*cbox.l < this.l) this.l = x + scale*cbox.l;
      this.w += scale*(cbox.w+(cbox.L||0)+(cbox.R||0)) ;
      if (scale*cbox.h > this.h) this.h = scale*cbox.h;
      if (cbox.D && (this.D == null || scale*cbox.D > this.D) && scale*cbox.D > this.d) this.D = scale*cbox.D;
        else if (cbox.D == null && this.D) delete this.D;
      if (scale*cbox.d > this.d) this.d = scale*cbox.d;
      if (scale*cbox.t > this.t) this.t = scale*cbox.t;
      if (scale*cbox.b > this.b) this.b = scale*cbox.b;
    },
    updateFrom: function (cbox) {
      this.h = cbox.h; this.d = cbox.d; this.w = cbox.w; this.r = cbox.r; this.l = cbox.l;
      this.t = cbox.t; this.b = cbox.b;
      if (cbox.pwidth) this.pwidth = cbox.pwidth;
      if (cbox.D) this.D = cbox.D; else delete this.D;
    },
    adjust: function (m,x,X,M) {
      this[x] += CHTML.length2em(m,1,this.scale);
      if (M == null) {
        if (this[x] > this[X]) this[X] = this[x];
      } else {
        if (this[X] < M) this[X] = M;
      }
    }
  },{
    zero: function () {
      return CHTML.BBOX({h:0, d:0, w:0, l:0, r:0, t:0, b:0, scale:1, rscale:1});
    },
    empty: function (bbox) {
      if (!bbox) bbox = CHTML.BBOX.zero();
      bbox.h = bbox.d = bbox.r = bbox.t = bbox.b = -BIGDIMEN;
      bbox.w = 0; bbox.l = BIGDIMEN;
      delete bbox.pwidth;
      return bbox;
    },
    //
    //  CSS styles that affect BBOXes
    //
    styleAdjust: [
      ["borderTopWidth","h","t"],
      ["borderRightWidth","w","r"],
      ["borderBottomWidth","d","b"],
      ["borderLeftWidth","w","l",0],
      ["paddingTop","h","t"],
      ["paddingRight","w","r"],
      ["paddingBottom","d","b"],
      ["paddingLeft","w","l",0],
    ]
  });
  
  /**********************************************************/

  MathJax.Hub.Register.StartupHook("mml Jax Ready",function () {
    MML = MathJax.ElementJax.mml;

    /********************************************************/
    
    MML.mbase.Augment({
      toCommonHTML: function (node,options) {
        return this.CHTMLdefaultNode(node,options);
      },
      CHTMLmultiline: function () {MML.mbase.CHTMLautoloadFile("multiline")},

      CHTMLdefaultNode: function (node,options) {
        if (!options) options = {};
        node = this.CHTMLcreateNode(node); this.CHTML = CHTML.BBOX.empty();
        this.CHTMLhandleStyle(node);
        if (this.isToken) this.CHTMLgetVariant();
        this.CHTMLhandleScale(node);
        var m = Math.max((options.minChildren||0),this.data.length);
        for (var i = 0; i < m; i++) this.CHTMLaddChild(node,i,options);
        if (!options.noBBox) this.CHTML.clean();
        this.CHTMLhandleSpace(node);
        this.CHTMLhandleBBox(node);
        this.CHTMLhandleColor(node);
        return node;
      },
      CHTMLaddChild: function (node,i,options) {
        var child = this.data[i], cnode;
        var type = options.childNodes;
        if (type instanceof Array) type = type[i]||"span";
        if (child) {
          if (type) node = CHTML.addElement(node,type);
          cnode = child.toCommonHTML(node,options.childOptions);
          if (type && child.CHTML.rscale !== 1) {
            // move scale factor to outer container (which seems to be more accurate)
            node.style.fontSize = node.firstChild.style.fontSize;
            node.firstChild.style.fontSize = "";
          }
          if (!options.noBBox) {
            var bbox = this.CHTML, cbox = child.CHTML;
            bbox.append(cbox);
            if (this.data.length === 1) {
              if (cbox.ic) bbox.ic = cbox.ic;
              if (cbox.skew) bbox.skew = cbox.skew;
            } else {
              delete bbox.ic;
              delete bbox.skew;
            }
            if (cbox.pwidth) bbox.pwidth = cbox.pwidth;
          }
        } else if (options.forceChild) {
          cnode = CHTML.addElement(node,(type||"mjx-box"));
        }
        return cnode;
      },
      
      CHTMLchildNode: function (node,i) {
        node = node.childNodes[i];
        if (node.nodeName.toLowerCase() === "a") node = node.firstChild;
        return node;
      },
      CHTMLcoreNode: function (node) {
        if (this.inferRow && this.data[0]) return this.data[0].CHTMLcoreNode(node.firstChild);
        return this.CHTMLchildNode(node,this.CoreIndex());
      },
      
      CHTMLstretchChildV: function (i,H,D) {
        var data = this.data[i];
        if (data) {
          var bbox = this.CHTML, dbox = data.CHTML;
          if (dbox.stretch || (dbox.stretch == null && data.CHTMLcanStretch("Vertical",H,D))) {
            var w = dbox.w;
            dbox = data.CHTMLstretchV(H,D);
            bbox.w += dbox.w - w;
            if (bbox.w > bbox.r) bbox.r = bbox.w;
            if (dbox.h > bbox.h) bbox.h = dbox.h;
            if (dbox.d > bbox.d) bbox.d = dbox.d;
            if (dbox.t > bbox.t) bbox.t = dbox.t;
            if (dbox.b > bbox.b) bbox.b = dbox.b;
          }
        }
      },
      CHTMLstretchChildH: function (i,W,node) {
        var data = this.data[i];
        if (data) {
          var bbox = this.CHTML, dbox = data.CHTML;
          if (dbox.stretch || (dbox.stretch == null && data.CHTMLcanStretch("Horizontal",W))) {
            var w = dbox.w;
            dbox = data.CHTMLstretchH(this.CHTMLchildNode(node,i),W);
            bbox.w += dbox.w - w;
            if (bbox.w > bbox.r) bbox.r = bbox.w;
            if (dbox.h > bbox.h) bbox.h = dbox.h;
            if (dbox.d > bbox.d) bbox.d = dbox.d;
            if (dbox.t > bbox.t) bbox.t = dbox.t;
            if (dbox.b > bbox.b) bbox.b = dbox.b;
          }
        }
      },
      CHTMLupdateFrom: function (bbox) {
        this.CHTML.updateFrom(bbox);
        if (this.inferRow) this.data[0].CHTML.updateFrom(bbox);
      },

      CHTMLcanStretch: function (direction,H,D) {
        var stretch = false;
        if (this.isEmbellished()) {
          var core = this.Core();
          if (core && core !== this) stretch = core.CHTMLcanStretch(direction,H,D);
        }
        this.CHTML.stretch = stretch;
        return stretch;
      },
      CHTMLstretchV: function (h,d) {
        this.CHTMLupdateFrom(this.Core().CHTMLstretchV(h,d));
        return this.CHTML;
      },
      CHTMLstretchH: function (node,w) {
        this.CHTMLupdateFrom(this.CHTMLstretchCoreH(node,w));
        return this.CHTML;
      },
      CHTMLstretchCoreH: function (node,w) {
        return this.Core().CHTMLstretchH(this.CHTMLcoreNode(node),w);
      },

      CHTMLcreateNode: function (node) {
        if (!this.CHTML) this.CHTML = {};
        this.CHTML = CHTML.BBOX.zero();
        if (this.href) node = CHTML.addElement(node,"a",{href:this.href, isMathJax:true});
        if (!this.CHTMLnodeID) this.CHTMLnodeID = CHTML.GetID();
        var id = (this.id || "MJXc-Node-"+this.CHTMLnodeID)+CHTML.idPostfix;
        return this.CHTMLhandleAttributes(CHTML.addElement(node,"mjx-"+this.type,{id:id}));
      },
      CHTMLnodeElement: function () {
        if (!this.CHTMLnodeID) {return null}
        return document.getElementById((this.id||"MJXc-Node-"+this.CHTMLnodeID)+CHTML.idPostfix);
      },
      
      CHTMLlength2em: function (length,size) {
        return CHTML.length2em(length,size,this.CHTML.scale);
      },
      
      CHTMLhandleAttributes: function (node) {
        if (this["class"]) {
          if (node.className) node.className += " "+this["class"];
            else node.className = this["class"];
        }
        //
        //  Copy RDFa, aria, and other tags from the MathML to the CHTML
        //  output nodes.  Don't copy those in the MML.nocopyAttributes list,
        //  the ignoreMMLattributes configuration list, or anything that
        //  already exists as a property of the node (e.g., no "onlick", etc.)
        //  If a name in the ignoreMMLattributes object is set to false, then
        //  the attribute WILL be copied.
        //
        if (this.attrNames) {
          var copy = this.attrNames, skip = MML.nocopyAttributes, ignore = HUB.config.ignoreMMLattributes;
          var defaults = (this.type === "mstyle" ? MML.math.prototype.defaults : this.defaults);
          for (var i = 0, m = copy.length; i < m; i++) {
            var id = copy[i];
            if (ignore[id] == false || (!skip[id] && !ignore[id] &&
                defaults[id] == null && typeof(node[id]) === "undefined")) {
              node.setAttribute(id,this.attr[id])
            }
          }
        }
        return node;
      },

      CHTMLhandleScale: function (node) {
        var scale = 1, parent = this.parent, pscale = (parent ? parent.CHTML.scale : 1);
        var values = this.getValues("scriptlevel","fontsize");
        values.mathsize = this.Get("mathsize",null,!this.isToken);
        if (values.scriptlevel !== 0) {
          if (values.scriptlevel > 2) values.scriptlevel = 2;
          scale = Math.pow(this.Get("scriptsizemultiplier"),values.scriptlevel);
          values.scriptminsize = CHTML.length2em(this.Get("scriptminsize"),.8,1);
          if (scale < values.scriptminsize) scale = values.scriptminsize;
        }
        if (this.removedStyles && this.removedStyles.fontSize && !values.fontsize)
          values.fontsize = this.removedStyles.fontSize;
        if (values.fontsize && !this.mathsize) values.mathsize = values.fontsize;
        if (values.mathsize !== 1) scale *= CHTML.length2em(values.mathsize,1,1);
        var variant = this.CHTMLvariant;
        if (variant && variant.style && variant.style["font-family"])
          scale *= (CHTML.config.scale/100)/CHTML.scale;
        this.CHTML.scale = scale; pscale = this.CHTML.rscale = scale/pscale;
        if (Math.abs(pscale-1) < .001) pscale = 1;
        if (node && pscale !== 1) node.style.fontSize = CHTML.Percent(pscale);
        return scale;
      },

      CHTMLhandleStyle: function (node) {
        if (!this.style) return;
        var style = node.style;
        style.cssText = this.style; this.removedStyles = {};
        for (var i = 0, m = CHTML.removeStyles.length; i < m; i++) {
          var id = CHTML.removeStyles[i];
          if (style[id]) {
            this.removedStyles[id] = style[id];
            style[id] = "";
          }
        }
      },

      CHTMLhandleBBox: function (node) {
        var BBOX = this.CHTML, style = node.style;
        if (this.data.length === 1 && (this.data[0].CHTML||{}).pwidth) {
          BBOX.pwidth = this.data[0].CHTML.pwidth;
          BBOX.mwidth = this.data[0].CHTML.mwidth;
          style.width = "100%";
        } else if (BBOX.pwidth) {
          BBOX.mwidth = CHTML.Em(BBOX.w);
          style.width = "100%";
        } else if (BBOX.w < 0) {
          style.width = "0px";
          style.marginRight = CHTML.Em(BBOX.w);
        }
        if (!this.style) return;
        // ### FIXME:  adjust for width, height, vertical-align?
        for (var i = 0, m = CHTML.BBOX.styleAdjust.length; i < m; i++) {
          var data = CHTML.BBOX.styleAdjust[i];
          if (data && style[data[0]]) BBOX.adjust(style[data[0]],data[1],data[2],data[3]);
        }
      },

      CHTMLhandleColor: function (node) {
        if (this.mathcolor) {node.style.color = this.mathcolor}
          else if (this.color) {node.style.color = this.color}
        if (this.mathbackground) {node.style.backgroundColor = this.mathbackground}
          else if (this.background) {node.style.backgroundColor = this.background}
      },
      
      CHTMLhandleSpace: function (node) {
        if (!this.useMMLspacing) {
          var space = this.texSpacing();
          if (space !== "") {
            this.CHTML.L = this.CHTMLlength2em(space);
            node.className += " "+CHTML.SPACECLASS[space];
          }
        }
      },

      CHTMLhandleText: function (node,text,variant) {
        if (node.firstChild && !this.CHTML) this.CHTML = CHTML.BBOX.empty();
        this.CHTML = CHTML.handleText(node,text,variant,this.CHTML);
      },
      
      CHTMLgetVariant: function () {
        var values = this.getValues("mathvariant","fontfamily","fontweight","fontstyle"), style;
        values.hasVariant = this.Get("mathvariant",true);  // null if not explicitly specified
        if (this.removedStyles) {
          style = this.removedStyles;
          if (style.fontFamily) values.family = style.fontFamily;
          if (style.fontWeight) values.weight = style.fontWeight;
          if (style.fontStyle)  values.style  = style.fontStyle;
        }
        if (!values.hasVariant) {
          if (values.fontfamily) values.family = values.fontfamily;
          if (values.fontweight) values.weight = values.fontweight;
          if (values.fontstyle)  values.style  = values.fontstyle;
        }
        if (values.weight && values.weight.match(/^\d+$/))
            values.weight = (parseInt(values.weight) > 600 ? "bold" : "normal");
        var variant = values.mathvariant; if (this.variantForm) variant = "-TeX-variant";
        if (values.family && !values.hasVariant) {
          if (!values.weight && values.mathvariant.match(/bold/)) values.weight = "bold";
          if (!values.style && values.mathvariant.match(/italic/)) values.style = "italic";
          this.CHTMLvariant = {fonts:[], noRemap:true, cache:{}, style: {
            "font-family":values.family, "font-weight":values.weight||"normal", "font-style":values.style||"normal"
          }};
          return;
        }
        if (values.weight === "bold") {
          variant = {
            normal:MML.VARIANT.BOLD, italic:MML.VARIANT.BOLDITALIC,
            fraktur:MML.VARIANT.BOLDFRAKTUR, script:MML.VARIANT.BOLDSCRIPT,
            "sans-serif":MML.VARIANT.BOLDSANSSERIF,
            "sans-serif-italic":MML.VARIANT.SANSSERIFBOLDITALIC
          }[variant]||variant;
        } else if (values.weight === "normal") {
          variant = {
            bold:MML.VARIANT.normal, "bold-italic":MML.VARIANT.ITALIC,
            "bold-fraktur":MML.VARIANT.FRAKTUR, "bold-script":MML.VARIANT.SCRIPT,
            "bold-sans-serif":MML.VARIANT.SANSSERIF,
            "sans-serif-bold-italic":MML.VARIANT.SANSSERIFITALIC
          }[variant]||variant;
        }
        if (values.style === "italic") {
          variant = {
            normal:MML.VARIANT.ITALIC, bold:MML.VARIANT.BOLDITALIC,
            "sans-serif":MML.VARIANT.SANSSERIFITALIC,
            "bold-sans-serif":MML.VARIANT.SANSSERIFBOLDITALIC
          }[variant]||variant;
        } else if (values.style === "normal") {
          variant = {
            italic:MML.VARIANT.NORMAL, "bold-italic":MML.VARIANT.BOLD,
            "sans-serif-italic":MML.VARIANT.SANSSERIF,
            "sans-serif-bold-italic":MML.VARIANT.BOLDSANSSERIF
          }[variant]||variant;
        }
        this.CHTMLvariant = CHTML.FONTDATA.VARIANT[variant] ||
                            CHTML.FONTDATA.VARIANT[MML.VARIANT.NORMAL];
      },

      CHTMLbboxFor: function (n) {
        if (this.data[n] && this.data[n].CHTML) return this.data[n].CHTML;
        return CHTML.BBOX.zero();
      },
      //
      //  Debugging function to see if internal BBox matches actual bbox
      //
      CHTMLdrawBBox: function (node,bbox) {
        if (!bbox) bbox = this.CHTML;
        var box = CHTML.Element("mjx-box",
          {style:{opacity:.25,"margin-left":CHTML.Em(-(bbox.w+(bbox.R||0)))}},[
          ["mjx-box",{style:{
            height:CHTML.Em(bbox.h),width:CHTML.Em(bbox.w),
            "background-color":"red"
          }}],
          ["mjx-box",{style:{
            height:CHTML.Em(bbox.d),width:CHTML.Em(bbox.w),
            "margin-left":CHTML.Em(-bbox.w),"vertical-align":CHTML.Em(-bbox.d),
            "background-color":"green"
          }}]
        ]);
        if (node.nextSibling) {node.parentNode.insertBefore(box,node.nextSibling)}
          else {node.parentNode.appendChild(box)}
      },

      CHTMLnotEmpty: function (mml) {
        while (mml && mml.data.length < 2 && (mml.type === "mrow" || mml.type === "texatom"))
          mml = mml.data[0];
        return !!mml;
      }

    },{
      //
      //  Autoload files based on node type or file name
      //
      CHTMLautoload: function () {
        this.constructor.Augment({toCommonHTML: MML.mbase.CHTMLautoloadFail});
	var file = CHTML.autoloadDir+"/"+this.type+".js";
	HUB.RestartAfter(AJAX.Require(file));
      },
      CHTMLautoloadFail: function () {
        throw Error("CommonHTML can't autoload '"+ this.type + "'");
      },
      CHTMLautoloadList: {},
      CHTMLautoloadFile: function (name) {
        if (MML.mbase.CHTMLautoloadList.hasOwnProperty(name)) {
          throw Error("CommonHTML can't autoload file '"+name+"'");
        }
        MML.mbase.CHTMLautoloadList[name] = true;
	var file = CHTML.autoloadDir+"/"+name+".js";
	HUB.RestartAfter(AJAX.Require(file));
      },
      //
      //  For use with embellished operators
      //
      CHTMLstretchV: function (h,d) {
        this.Core().CHTMLstretchV(h,d);
        this.toCommonHTML(this.CHTMLnodeElement(),{stretch:true});
        return this.CHTML;
      },
      CHTMLstretchH: function (node,w) {
        this.CHTMLupdateFrom(this.CHTMLstretchCoreH(node,w));
        this.toCommonHTML(node,{stretch:true});
        return this.CHTML;
      }      
    });

    /********************************************************/
    
    MML.chars.Augment({
      toCommonHTML: function (node,options) {
        this.CHTML = null;
        if (options == null) options = {};
        var text = this.toString();
        if (options.remap) text = options.remap(text,options.remapchars);
        this.CHTMLhandleText(node,text,options.variant||this.parent.CHTMLvariant);
      }
    });
    MML.entity.Augment({
      toCommonHTML: function (node,options) {
        if (options == null) options = {};
        var text = this.toString();
        if (options.remapchars) text = options.remap(text,options.remapchars);
        this.CHTMLhandleText(node,text,options.variant||this.parent.CHTMLvariant);
      }
    });

    /********************************************************/
    
    MML.math.Augment({
      toCommonHTML: function (node) {
        node = this.CHTMLdefaultNode(node);
        if (this.CHTML.w < 0) {
          node.parentNode.style.width = "0px";
          node.parentNode.style.marginRight = CHTML.Em(this.CHTML.w);
        }
        var alttext = this.Get("alttext");
        if (alttext && !node.getAttribute("aria-label")) node.setAttribute("aria-label",alttext);
        if (this.CHTML.pwidth) {
          node.parentNode.style.minWidth = this.CHTML.mwidth||CHTML.Em(this.CHTML.w);
          node.parentNode.className = "mjx-full-width "+node.parentNode.className;
          node.style.width = this.CHTML.pwidth;
        } else if (!this.isMultiline && this.Get("display") === "block") {
          var values = this.getValues("indentalignfirst","indentshiftfirst","indentalign","indentshift");
          if (values.indentalignfirst !== MML.INDENTALIGN.INDENTALIGN) values.indentalign = values.indentalignfirst;
          if (values.indentalign === MML.INDENTALIGN.AUTO) values.indentalign = CONFIG.displayAlign;
          if (values.indentshiftfirst !== MML.INDENTSHIFT.INDENTSHIFT) values.indentshift = values.indentshiftfirst;
          if (values.indentshift === "auto") values.indentshift = "0";
          var shift = this.CHTMLlength2em(values.indentshift,CHTML.cwidth);
          if (CONFIG.displayIndent !== "0") {
            var indent = this.CHTMLlength2em(CONFIG.displayIndent,CHTML.cwidth);
            shift += (values.indentalign === MML.INDENTALIGN.RIGHT ? -indent : indent);
          }
          var styles = node.parentNode.parentNode.style;
          node.parentNode.style.textAlign = styles.textAlign = values.indentalign;
          // ### FIXME: make percentage widths respond to changes in container
          if (shift) {
            shift *= CHTML.em/CHTML.outerEm;
            HUB.Insert(styles,({
              left: {marginLeft: CHTML.Em(shift)},
              right: {marginRight: CHTML.Em(-shift)},
              center: {marginLeft: CHTML.Em(shift), marginRight: CHTML.Em(-shift)}
            })[values.indentalign]);
          }
        }
        return node;
      }
    });
    
    /********************************************************/
    
    MML.mi.Augment({
      toCommonHTML: function (node) {
        node = this.CHTMLdefaultNode(node);
        var bbox = this.CHTML, text = this.data.join("");
        if (bbox.skew != null && !CHTML.isChar(text)) delete bbox.skew;
        if (bbox.r > bbox.w && CHTML.isChar(text) && !this.CHTMLvariant.noIC) {
          bbox.ic = bbox.r - bbox.w; bbox.w = bbox.r;
          node.lastChild.style.paddingRight = CHTML.Em(bbox.ic);
        }
        return node;
      }
    });

    /********************************************************/
    
    MML.mn.Augment({
      CHTMLremapMinus: function (text) {return text.replace(/^-/,"\u2212")},
      toCommonHTML: function (node) {
        node = this.CHTMLdefaultNode(node,{childOptions:{remap:this.CHTMLremapMinus}});
        var bbox = this.CHTML, text = this.data.join("");
        if (bbox.skew != null && !CHTML.isChar(text)) delete bbox.skew;
        if (bbox.r > bbox.w && CHTML.isChar(text) && !this.CHTMLvariant.noIC) {
          bbox.ic = bbox.r - bbox.w; bbox.w = bbox.r;
          node.lastChild.style.paddingRight = CHTML.Em(bbox.ic);
        }
        return node;
      }
    });

    /********************************************************/
    
    MML.mo.Augment({
      toCommonHTML: function (node) {
        node = this.CHTMLcreateNode(node);
        this.CHTMLhandleStyle(node);
        this.CHTMLgetVariant();
        this.CHTMLhandleScale(node);
        CHTML.BBOX.empty(this.CHTML);
        
        var values = this.getValues("displaystyle","largeop");
        values.variant = this.CHTMLvariant;
        values.text = this.data.join("");
        if (values.text == "") {
          if (this.fence) node.style.width = CHTML.Em(CHTML.TEX.nulldelimiterspace);
        } else {
          this.CHTMLadjustAccent(values);
          this.CHTMLadjustVariant(values);

          for (var i = 0, m = this.data.length; i < m; i++) {
            this.CHTMLaddChild(node,i,{childOptions:{
              variant: values.mathvariant,
              remap: this.remap,
              remapchars: values.remapchars
            }});
          }
          if (!CHTML.isChar(values.text)) delete this.CHTML.skew;
            else if (this.CHTML.w === 0 && this.CHTML.l < 0) this.CHTMLfixCombiningChar(node);
          if (values.largeop) this.CHTMLcenterOp(node);
        }

        this.CHTML.clean();
        this.CHTMLhandleBBox(node);
        this.CHTMLhandleSpace(node);
        this.CHTMLhandleColor(node);

        return node;
      },
      CHTMLhandleSpace: function (node) {
        if (this.hasMMLspacing()) {
          var values = this.getValues("scriptlevel","lspace","rspace");
          values.lspace = Math.max(0,this.CHTMLlength2em(values.lspace));
          values.rspace = Math.max(0,this.CHTMLlength2em(values.rspace));
          if (values.scriptlevel > 0) {
            if (!this.hasValue("lspace")) values.lspace = .15;
            if (!this.hasValue("rspace")) values.rspace = .15;
          }
          var core = this, parent = this.Parent();
          while (parent && parent.isEmbellished() && parent.Core() === core)
            {core = parent; parent = parent.Parent(); node = core.CHTMLnodeElement()}
          if (values.lspace) node.style.paddingLeft =  CHTML.Em(values.lspace);
          if (values.rspace) node.style.paddingRight = CHTML.Em(values.rspace);
          this.CHTML.L = values.lspace; this.CHTML.R = values.rspace;
        } else {
          this.SUPER(arguments).CHTMLhandleSpace.apply(this,arguments);
        }
      },
      CHTMLadjustAccent: function (data) {
        var parent = this.CoreParent(); data.parent = parent;
        if (CHTML.isChar(data.text) && parent && parent.isa(MML.munderover)) {
          var over = parent.data[parent.over], under = parent.data[parent.under];
          if (over && this === over.CoreMO() && parent.Get("accent")) {
            data.remapchars = CHTML.FONTDATA.REMAPACCENT;
          } else if (under && this === under.CoreMO() && parent.Get("accentunder")) {
            data.remapchars = CHTML.FONTDATA.REMAPACCENTUNDER;
          }
        }
      },
      CHTMLadjustVariant: function (data) {
        var parent = data.parent,
            isScript = (parent && parent.isa(MML.msubsup) && this !== parent.data[parent.base]);
        if (data.largeop) data.mathvariant = (data.displaystyle ? "-largeOp" : "-smallOp");
        if (isScript) {
          data.remapchars = this.remapChars;
          if (data.text.match(/['`"\u00B4\u2032-\u2037\u2057]/))
            data.mathvariant = "-TeX-variant";  // ### FIXME: handle other fonts
        }
      },
      CHTMLfixCombiningChar: function (node) {
        //
        //  IE doesn't display combining chararacters unless they combine with
        //  something, so put them over a space and remove the space's width
        //
        node = node.firstChild;
        var space = CHTML.Element("mjx-box",{style:{width:".25em","margin-left":"-.25em"}});
        node.insertBefore(space,node.firstChild);
      },
      CHTMLcenterOp: function (node) {
        var bbox = this.CHTML;
        var p = (bbox.h - bbox.d)/2 - CHTML.TEX.axis_height;
        if (Math.abs(p) > .001) node.style.verticalAlign = CHTML.Em(-p);
        bbox.h -= p; bbox.d += p;
        if (bbox.r > bbox.w) {
          bbox.ic = bbox.r - bbox.w; bbox.w = bbox.r;
          node.style.paddingRight = CHTML.Em(bbox.ic);
        }
      },
      CHTMLcanStretch: function (direction,H,D) {
        if (!this.Get("stretchy")) return false;
        var c = this.data.join(""); if (!CHTML.isChar(c)) return false;
        var values = {text: c};
        this.CHTMLadjustAccent(values);
        if (values.remapchars) c = values.remapchars[c]||c;
        c = CHTML.FONTDATA.DELIMITERS[c.charCodeAt(0)];
        var stretch = (c && c.dir === direction.substr(0,1));
        if (stretch) {
          stretch = (this.CHTML.h !== H || this.CHTML.d !== D ||
            !!this.Get("minsize",true) || !!this.Get("maxsize",true));
          if (stretch) this.CHTML.stretch = true;
        }
        return stretch;
      },
      CHTMLstretchV: function (h,d) {
        var node = this.CHTMLnodeElement(), bbox = this.CHTML;
        var values = this.getValues("symmetric","maxsize","minsize");
        //
        //  Determine the height needed
        //
        var H, a = CHTML.TEX.axis_height;
        if (values.symmetric) {H = 2*Math.max(h-a,d+a)} else {H = h + d}
        values.maxsize = this.CHTMLlength2em(values.maxsize,bbox.h+bbox.d);
        values.minsize = this.CHTMLlength2em(values.minsize,bbox.h+bbox.d);
        H = Math.max(values.minsize,Math.min(values.maxsize,H));
        //
        //  If we are not already stretched to this height
        //
        if (H !== bbox.sH) {
          //
          //  Get a delimiter of the proper height and save the height
          //
          if (H != values.minsize)
            {H = [Math.max(H*CHTML.TEX.delimiterfactor/1000,H-CHTML.TEX.delimitershortfall),H]}
          while (node.firstChild) node.removeChild(node.firstChild);
          this.CHTML = bbox = CHTML.createDelimiter(node,this.data.join("").charCodeAt(0),H,bbox);
          bbox.sH = (H instanceof Array ? H[1] : H);
          //
          //  Reposition as needed
          //
          if (values.symmetric) {H = (bbox.h + bbox.d)/2 + a}
            else {H = (bbox.h + bbox.d) * h/(h + d)}
          H -= bbox.h;
          if (Math.abs(H) > .05) {
            node.style.verticalAlign = CHTML.Em(H);
            bbox.h += H; bbox.d -= H; bbox.t += H; bbox.b -= H;
          }
        }
        return this.CHTML;
      },
      CHTMLstretchH: function (node,W) {
        var bbox = this.CHTML;
        var values = this.getValues("maxsize","minsize","mathvariant","fontweight");
        if ((values.fontweight === "bold" || (this.removedStyles||{}).fontWeight === "bold" ||
            parseInt(values.fontweight) >= 600) && !this.Get("mathvariant",true))
                values.mathvariant = MML.VARIANT.BOLD;
        values.maxsize = this.CHTMLlength2em(values.maxsize,bbox.w);
        values.minsize = this.CHTMLlength2em(values.minsize,bbox.w);
        W = Math.max(values.minsize,Math.min(values.maxsize,W));
        if (W !== bbox.sW) {
          while (node.firstChild) node.removeChild(node.firstChild);
          this.CHTML = bbox = CHTML.createDelimiter(node,this.data.join("").charCodeAt(0),W,bbox,values.mathvariant);
          bbox.sW = W;
        }
        return this.CHTML;
      }

    });

    /********************************************************/

    MML.mtext.Augment({
      CHTMLgetVariant: function () {
        if (CHTML.config.mtextFontInherit || this.Parent().type === "merror") {
          var scale = (CHTML.config.scale/100)/CHTML.scale;
          var variant = {cache:{}, fonts:[], className:"MJXc-font-inherit", rscale:scale,
                         style:{"font-size":CHTML.Percent(scale)}};
          var name = this.Get("mathvariant");
          if (name.match(/bold/)) variant.style["font-weight"] = "bold";
          if (name.match(/italic|-tex-mathit/)) variant.style["font-style"] = "italic";
          if (name === "monospace") variant.className += " MJXc-monospace-font";
          if (name === "double-struck") variant.className += " MJXc-double-struck-font";
          if (name.match(/fraktur/)) variant.className += " MJXc-fraktur-font";
          if (name.match(/sans-serif/)) variant.className += " MJXc-sans-serif-font";
          if (name.match(/script/)) variant.className += " MJXc-script-font";
          this.CHTMLvariant = variant;
        } else {
          this.SUPER(arguments).CHTMLgetVariant.call(this);
        }
      }
    });

    /********************************************************/
    
    MML.merror.Augment({
      toCommonHTML: function (node) {
        node = this.CHTMLdefaultNode(node);
        var bbox = this.CHTML;
        //
        //  Adjust for font-size: 90%
        //
        bbox.rescale(.9);
        //
        //  Adjust for padding and border
        //
        bbox.h += 3/CHTML.em; if (bbox.h > bbox.t) bbox.t = bbox.h;
        bbox.d += 3/CHTML.em; if (bbox.d > bbox.b) bbox.b = bbox.d;
        bbox.w += 8/CHTML.em; bbox.r = bbox.w; bbox.l = 0;
        return node;
      }
    });
    
    /********************************************************/
    
    MML.mspace.Augment({
      toCommonHTML: function (node) {
        node = this.CHTMLcreateNode(node);
        this.CHTMLhandleStyle(node);
        this.CHTMLhandleScale(node);
        var values = this.getValues("height","depth","width");
        var w = this.CHTMLlength2em(values.width),
            h = this.CHTMLlength2em(values.height),
            d = this.CHTMLlength2em(values.depth);
        var bbox = this.CHTML;
        bbox.w = bbox.r = w; bbox.h = bbox.t = h; bbox.d = bbox.b = d; bbox.l = 0;
        if (w < 0) {node.style.marginRight = CHTML.Em(w); w = 0}
        node.style.width = CHTML.Em(w);
        node.style.height = CHTML.Em(Math.max(0,h+d));
        if (d) node.style.verticalAlign = CHTML.Em(-d);
        this.CHTMLhandleBBox(node);
        this.CHTMLhandleColor(node);
        return node;
      }
    });

    /********************************************************/
    
    MML.mpadded.Augment({
      toCommonHTML: function (node,options) {
        var child;
        if (options && options.stretch) {
          node = node.firstChild; child = node.firstChild;
        } else {
          node = this.CHTMLdefaultNode(node,{childNodes:"mjx-box", forceChild:true});
          child = node.firstChild; node = CHTML.addElement(node,"mjx-block");
          node.appendChild(child); CHTML.addElement(node,"mjx-strut"); // force proper alignment of short heights
        }
        var cbox = this.CHTMLbboxFor(0);
        var values = this.getValues("width","height","depth","lspace","voffset");
        var x = 0, y = 0, w = cbox.w, h = cbox.h, d = cbox.d;
        child.style.width = 0; child.style.margin = CHTML.Em(-h)+" 0 "+CHTML.Em(-d);
        if (values.width !== "")  w = this.CHTMLdimen(values.width,"w",w,0);
        if (values.height !== "") h = this.CHTMLdimen(values.height,"h",h,0);
        if (values.depth !== "")  d = this.CHTMLdimen(values.depth,"d",d,0);
        if (values.voffset !== "") {
          y = this.CHTMLdimen(values.voffset);
          if (y) {
            child.style.position = "relative";
            child.style.top = CHTML.Em(-y);
          }
        }
        if (values.lspace !== "") {
          x = this.CHTMLdimen(values.lspace);
          if (x) {
            child.style.position = "relative";
            child.style.left = CHTML.Em(x);
          }
        }
        node.style.width = 0;
        node.style.marginTop = CHTML.Em(h-STRUTHEIGHT);
        node.style.padding = "0 "+CHTML.Em(w)+" "+CHTML.Em(d)+" 0";
        var bbox = CHTML.BBOX({w:w, h:h, d:d, l:0, r:w, t:h, b:d,
                               scale:this.CHTML.scale, rscale:this.CHTML.rscale});
        bbox.combine(cbox,x,y);
        bbox.w = w; bbox.h = h; bbox.d = d;
        this.CHTML = bbox;
        return node.parentNode;
      },
      CHTMLstretchV: MML.mbase.CHTMLstretchV,
      CHTMLstretchH: MML.mbase.CHTMLstretchH,
      CHTMLdimen: function (length,d,D,m) {
        if (m == null) {m = -BIGDIMEN}
        length = String(length);
        var match = length.match(/width|height|depth/);
        var size = (match ? this.CHTML[match[0].charAt(0)] : (d ? this.CHTML[d] : 0));
        var dimen = (this.CHTMLlength2em(length,size)||0);
        if (length.match(/^[-+]/) && D != null) dimen += D;
        if (m != null) dimen = Math.max(m,dimen);
        return dimen;
      }
    });

    /********************************************************/
    
    MML.munderover.Augment({
      toCommonHTML: function (node,options) {
        var values = this.getValues("displaystyle","accent","accentunder","align");
        var base = this.data[this.base];
        if (!values.displaystyle && base != null &&
            (base.movablelimits || base.CoreMO().Get("movablelimits")))
                return MML.msubsup.prototype.toCommonHTML.call(this,node,stretch);
        //
        //  Get the nodes for base and limits
        //
        var under, over, nodes = [], stretch = false;
        if (options && options.stretch) {
          if (this.data[this.base])  base = CHTML.getNode(node,"mjx-op");
          if (this.data[this.under]) under = CHTML.getNode(node,"mjx-under");
          if (this.data[this.over])  over = CHTML.getNode(node,"mjx-over");
          nodes[0] = base; nodes[1] = under||over; nodes[2] = over;
          stretch = true;
        } else {
          var types = ["mjx-op","mjx-under","mjx-over"];
          if (this.over === 1) types[1] = types[2];
          node = this.CHTMLdefaultNode(node,{
            childNodes:types, noBBox:true, forceChild:true, minChildren: 2
          });
          nodes[0] = base = node.removeChild(node.firstChild);
          nodes[1] = under = over = node.removeChild(node.firstChild);
          if (node.firstChild) nodes[2] = over = node.removeChild(node.firstChild);
        }
        //
        //  Get the bounding boxes and the maximum width
        //
        var boxes = [], W = this.CHTMLgetBBoxes(boxes,nodes,values);
        var bbox = boxes[this.base], BBOX = this.CHTML;
        BBOX.w = W; BBOX.h = bbox.h; BBOX.d = bbox.d; // modified below
        //
        // Adjust for bases shorter than the center line (#1657)
        // (the center line really depends on the surrounding font, so
        //  it should be measured along with ems and exs, but currently isn't.
        //  so this value is an approximation that is reasonable for most fonts.)
        //
        if (bbox.h < .35) base.style.marginTop = CHTML.Em(bbox.h - .35);
        //
        //  Use a minimum height for accents (#1706)
        //  (same issues with the center line as above)
        //
        if (values.accent && bbox.h < CHTML.TEX.x_height) {
          BBOX.h += CHTML.TEX.x_height - bbox.h;
          base.style.marginTop = CHTML.Em(CHTML.TEX.x_height - Math.max(bbox.h,.35));
          bbox.h = CHTML.TEX.x_height;
        }
        //
        //  Add over- and under-scripts
        //  
        var stack = base, delta = 0;
        if (bbox.ic) {delta = 1.3*bbox.ic + .05} // make faked IC be closer to expeted results
        if (this.data[this.over]) stack = this.CHTMLaddOverscript(over,boxes,values,delta,base,stretch);
        if (this.data[this.under]) this.CHTMLaddUnderscript(under,boxes,values,delta,node,stack,stretch);
          else if (!stretch) node.appendChild(stack);
        //
        //  Handle horizontal positions
        //
        this.CHTMLplaceBoxes(base,under,over,values,boxes);
        return node;
      },
      //
      //  Get the bounding boxes for the children, stretch
      //  any stretchable elements, and compute the maximum width
      //  
      CHTMLgetBBoxes: function (bbox,nodes,values) {
        var i, m = this.data.length, scale,
            w = -BIGDIMEN,  // maximum width of non-stretchy items
            W = w;          // maximum width of all items
        //
        //  Get the maximum width
        //
        for (i = 0; i < m; i++) {
          bbox[i] = this.CHTMLbboxFor(i); bbox[i].x = bbox[i].y = 0;
          if (this.data[i]) bbox[i].stretch = this.data[i].CHTMLcanStretch("Horizontal");
          scale = (i === this.base ? 1 : bbox[i].rscale);
          if (i !== this.base) {delete bbox[i].L; delete bbox[i].R} // these are overridden by CSS
          W = Math.max(W,scale*(bbox[i].w + (bbox[i].L||0) + (bbox[i].R||0)));
          if (!bbox[i].stretch && W > w) w = W;
        }
        if (w === -BIGDIMEN) w = W;
        //
        //  Stretch those parts that need it
        //
        for (i = 0; i < m; i++) {
          if (bbox[i].stretch) {
            scale = (i === this.base ? 1 : bbox[i].rscale);
            bbox[i] = this.data[i].CHTMLstretchH(nodes[i].firstChild,w/scale);
            bbox[i].x = bbox[i].y = 0;
            W = Math.max(W,scale*(bbox[i].w + (bbox[i].L||0) + (bbox[i].R||0)));
          }
        }
        if (!bbox[this.base]) bbox[this.base] = CHTML.BBOX.empty();
        return W;
      },
      //
      //  Add an overscript
      //
      CHTMLaddOverscript: function (over,boxes,values,delta,base,stretch) {
        var BBOX = this.CHTML;
        var z1, z2, z3 = CHTML.TEX.big_op_spacing5, k;
        var obox = boxes[this.over], bbox = boxes[this.base], scale = obox.rscale;
        //
        //  Put the base and script into a stack
        //
        if (!stretch) {
          var stack = CHTML.Element("mjx-stack");
          stack.appendChild(over); stack.appendChild(base);
        }
        if (obox.D) obox.d = obox.D;
        if (obox.d < 0) {
          //
          // For negative depths, set the height and align to top
          // in order to avoid extra baseline space
          //
          over.firstChild.style.verticalAlign = "top";
          over.style.height = CHTML.Em(obox.h+obox.d);
        }
        //
        //  Determine the spacing
        //
        obox.x = 0;
        if (values.accent) {
          if (obox.w < .001) obox.x += (obox.r - obox.l)/2; // center combining accents
          k = CHTML.TEX.rule_thickness; z3 = 0;
          if (bbox.skew) {
            obox.x += scale*bbox.skew; BBOX.skew = scale*bbox.skew;
            if (obox.x+scale*obox.w > BBOX.w) BBOX.skew += (BBOX.w - (obox.x+scale*obox.w))/2;
          }
        } else {
          z1 = CHTML.TEX.big_op_spacing1;
          z2 = CHTML.TEX.big_op_spacing3;
          k = Math.max(z1,z2-Math.max(0,scale*obox.d));
        }
        obox.x += delta/2; obox.y = BBOX.h + k + z3 + scale*obox.d;
        //
        //  Position the overscript
        //
        if (k) over.style.paddingBottom = CHTML.Em(k/scale);
        if (z3) over.style.paddingTop = CHTML.Em(z3/scale);
        return stack;
      },
      //
      //  Add an underscript
      //
      CHTMLaddUnderscript: function (under,boxes,values,delta,node,stack,stretch) {
        var BBOX = this.CHTML;
        var z1, z2, z3 = CHTML.TEX.big_op_spacing5, k;
        var ubox = boxes[this.under], scale = ubox.rscale;
        //
        //  Create a table for the underscript
        //
        if (!stretch) {
          CHTML.addElement(node,"mjx-itable",{},[
            ["mjx-row",{},[["mjx-cell"]]],
            ["mjx-row"]
          ]);
          node.firstChild.firstChild.firstChild.appendChild(stack);
          node.firstChild.lastChild.appendChild(under);
        }
        if (ubox.D) ubox.d = ubox.D;
        if (ubox.d < 0) {
          //
          // For negative depths, set the height and align to top
          // in order to avoid extra baseline space
          //
          under.firstChild.style.verticalAlign = "top";
          node.firstChild.style.marginBottom = CHTML.Em(ubox.d);
        }
        //
        //  determine the spacing
        //
        if (values.accentunder) {
          k = 2*CHTML.TEX.rule_thickness; z3 = 0;
        } else {
          z1 = CHTML.TEX.big_op_spacing2;
          z2 = CHTML.TEX.big_op_spacing4;
          k = Math.max(z1,z2-scale*ubox.h);
        }
        ubox.x = -delta/2; ubox.y = -(BBOX.d + k + z3 + scale*ubox.h);
        //
        //  Position the underscript
        //
        if (k) under.style.paddingTop = CHTML.Em(k/scale);
        if (z3) under.style.paddingBottom = CHTML.Em(z3/scale);
      },
      //
      //  Center boxes horizontally, taking offsets into account
      //
      CHTMLplaceBoxes: function (base,under,over,values,boxes) {
        var W = this.CHTML.w, i, m = boxes.length, scale;
        var BBOX = CHTML.BBOX.zero();
        BBOX.scale = this.CHTML.scale; BBOX.rscale = this.CHTML.rscale;
        boxes[this.base].x = boxes[this.base].y = 0; var dx = BIGDIMEN;
        for (i = 0; i < m; i++) {
          scale = (i === this.base ? 1 : boxes[i].rscale);
          var w = scale*(boxes[i].w + (boxes[i].L||0) + (boxes[i].R||0));
          boxes[i].x += {left:0, center:(W-w)/2, right:W-w}[values.align];
          if (boxes[i].x < dx) dx = boxes[i].x;
        }
        for (i = 0; i < m; i++) {
          if (this.data[i]) {
            scale = (i === this.base ? 1 : boxes[i].rscale);
            if (boxes[i].x - dx) {
              var node = (i === this.base ? base : i === this.over ? over : under);
              node.style.paddingLeft = CHTML.Em((boxes[i].x-dx)/scale);
            }
            BBOX.combine(boxes[i],boxes[i].x-dx,boxes[i].y);
          }
        }
        this.CHTML = BBOX;
      },
      CHTMLstretchV: MML.mbase.CHTMLstretchV,
      CHTMLstretchH: MML.mbase.CHTMLstretchH,
      CHTMLchildNode: function (node,i) {
        var types = ["mjx-op","mjx-under","mjx-over"];
        if (this.over === 1) types[1] = types[2];
        return CHTML.getNode(node,types[i]);
      }
    });

    /********************************************************/
    
    MML.msubsup.Augment({
      toCommonHTML: function (node,options) {
        var values = this.getValues(
           "displaystyle","subscriptshift","superscriptshift","texprimestyle"
        );
        //
        //  Get the nodes for base and limits
        //
        var base, sub, sup;
        if (options && options.stretch) {
          if (this.data[this.base]) base = CHTML.getNode(node,"mjx-base");
          if (this.data[this.sub])  sub = CHTML.getNode(node,"mjx-sub");
          if (this.data[this.sup])  sup = CHTML.getNode(node,"mjx-sup");
          stack = CHTML.getNode(node,"mjx-stack");
        } else {
          var types = ["mjx-base","mjx-sub","mjx-sup"];
          if (this.sup === 1) types[1] = types[2];
          node = this.CHTMLdefaultNode(node,{
            childNodes:types, noBBox:true, forceChild:true, minChildren: 3
          });
          base = node.childNodes[this.base];
          sub = node.childNodes[this.sub]; sup = node.childNodes[this.sup];
          if (!this.CHTMLnotEmpty(this.data[this.sub])) {node.removeChild(sub); sub = null}
          if (!this.CHTMLnotEmpty(this.data[this.sup])) {node.removeChild(sup); sup = null}
          if (node.childNodes.length === 3) {
            var stack = CHTML.addElement(node,"mjx-stack");
            stack.appendChild(sup); stack.appendChild(sub);
          }
        }
        //
        //  Get the bounding boxes and maximum width of scripts
        //
        var boxes = [], BBOX = CHTML.BBOX.empty(this.CHTML);
        for (var i = 0, m = this.data.length; i < m; i++) boxes[i] = this.CHTMLbboxFor(i);
        var bbox = boxes[this.base] || CHTML.BBOX.empty(),
            sbox = boxes[this.sub], Sbox = boxes[this.sup];
        var sscale = (sub ? sbox.rscale : 1), Sscale = (sup ? Sbox.rscale : 1);
        BBOX.combine(bbox,0,0);
        //
        //  Get initial values for parameters
        //
        var ex = CHTML.TEX.x_height, s = CHTML.TEX.scriptspace;
        var q = CHTML.TEX.sup_drop * Sscale, r = CHTML.TEX.sub_drop * sscale;
        var u = bbox.h - q, v = bbox.d + r, delta = 0, p;
        if (bbox.ic) {
          BBOX.w -= bbox.ic;         // remove IC (added by mo and mi)
          base.style.marginRight = CHTML.Em(-bbox.ic);
          delta = 1.3*bbox.ic + .05; // make faked IC be closer to expeted results
        }
        var bmml = this.data[this.base];
        if (bmml) {
          if ((bmml.type === "mrow" || bmml.type === "mstyle") && bmml.data.length === 1) bmml = bmml.data[0];
          if (bmml.type === "mi" || bmml.type === "mo") {
            if (CHTML.isChar(bmml.data.join("")) && bbox.rscale === 1 && !bbox.sH &&
                !bmml.Get("largeop")) {u = v = 0}
          }
        }
        values.subscriptshift   = (values.subscriptshift === ""   ? 0 : this.CHTMLlength2em(values.subscriptshift));
        values.superscriptshift = (values.superscriptshift === "" ? 0 : this.CHTMLlength2em(values.superscriptshift));
        //
        //  Add the super- and subscripts
        //
        var x = BBOX.w; if (sub) sbox.w += s; if (sup) Sbox.w += s;
        if (!sup) {
          if (sub) {
            v = Math.max(v,CHTML.TEX.sub1,sscale*sbox.h-(4/5)*ex,values.subscriptshift);
            sub.style.verticalAlign = CHTML.Em(-v/sscale);
            sub.style.paddingRight = CHTML.Em(s/sscale);
            BBOX.combine(sbox,x,-v);
          }
        } else {
          if (!sub) {
            p = CHTML.TEX[(values.displaystyle ? "sup1" : (values.texprimestyle ? "sup3" : "sup2"))];
            u = Math.max(u,p,Sscale*Sbox.d+(1/4)*ex,values.superscriptshift);
            sup.style.verticalAlign = CHTML.Em(u/Sscale);
            sup.style.paddingLeft = CHTML.Em(delta/Sscale);
            sup.style.paddingRight = CHTML.Em(s/Sscale);
            BBOX.combine(Sbox,x+delta,u);
          } else {
            v = Math.max(v,CHTML.TEX.sub2);
            var t = CHTML.TEX.rule_thickness;
            if ((u - Sscale*Sbox.d) - (sscale*sbox.h - v) < 3*t) {
              v = 3*t - u + Sscale*Sbox.d + sscale*sbox.h;
              q = (4/5)*ex - (u - Sscale*Sbox.d);
              if (q > 0) {u += q; v -= q}
            }
            u = Math.max(u,values.superscriptshift);
            v = Math.max(v,values.subscriptshift);
            sub.style.paddingRight = CHTML.Em(s/sscale);
            sup.style.paddingBottom = CHTML.Em(u/Sscale+v/sscale-Sbox.d-sbox.h/sscale*Sscale);
            sup.style.paddingLeft = CHTML.Em(delta/Sscale);
            sup.style.paddingRight = CHTML.Em(s/Sscale);
            stack.style.verticalAlign = CHTML.Em(-v);
            BBOX.combine(Sbox,x+delta,u);
            BBOX.combine(sbox,x,-v);
          }
        }
        BBOX.clean();
        return node;
      },
      CHTMLstretchV: MML.mbase.CHTMLstretchV,
      CHTMLstretchH: MML.mbase.CHTMLstretchH,
      CHTMLchildNode: function (node,i) {
        var types = ["mjx-base","mjx-sub","mjx-sup"];
        if (this.over === 1) types[1] = types[2];
        return CHTML.getNode(node,types[i]);
      }
    });

    /********************************************************/
    
    MML.mfrac.Augment({
      toCommonHTML: function (node) {
        node = this.CHTMLdefaultNode(node,{
          childNodes:["mjx-numerator","mjx-denominator"],
          childOptions: {autowidth: true},
          forceChild:true, noBBox:true, minChildren:2
        });
        var values = this.getValues("linethickness","displaystyle",
                                    "numalign","denomalign","bevelled");
        var isDisplay = values.displaystyle;
        //
        //  Create the table for the fraction and set the alignment
        //
        var num = node.firstChild, denom = node.lastChild;
        var frac = CHTML.addElement(node,"mjx-box");
        frac.appendChild(num); frac.appendChild(denom); node.appendChild(frac);
        if (values.numalign !== "center") num.style.textAlign = values.numalign;
        if (values.denomalign !== "center") denom.style.textAlign = values.denomalign;
        //
        //  Get the bounding boxes for the parts, and determine the placement
        //  of the numerator and denominator
        //
        var nbox = this.CHTMLbboxFor(0), dbox = this.CHTMLbboxFor(1),
            BBOX = CHTML.BBOX.empty(this.CHTML), nscale = nbox.rscale, dscale = dbox.rscale;
        values.linethickness = Math.max(0,CHTML.thickness2em(values.linethickness||"0",BBOX.scale));
        var mt = CHTML.TEX.min_rule_thickness/CHTML.em, a = CHTML.TEX.axis_height;
        var t = values.linethickness, p,q, u,v;
        if (values.bevelled) {
          frac.className += " MJXc-bevelled";
          var delta = (isDisplay ? .4 : .15);
          var H = Math.max(nscale*(nbox.h+nbox.d),dscale*(dbox.h+dbox.d)) + 2*delta;
          var bevel = CHTML.Element("mjx-bevel"); frac.insertBefore(bevel,denom);
          var bbox = CHTML.createDelimiter(bevel,0x2F,H);
          u = nscale*(nbox.d-nbox.h)/2+a+delta;
          v = dscale*(dbox.d-dbox.h)/2+a-delta;
          if (u) num.style.verticalAlign = CHTML.Em(u/nscale);
          if (v) denom.style.verticalAlign = CHTML.Em(v/dscale);
          bevel.style.marginLeft = bevel.style.marginRight = CHTML.Em(-delta/2);
          BBOX.combine(nbox,0,u);
          BBOX.combine(bbox,nscale*nbox.w-delta/2,0);
          BBOX.combine(dbox,nscale*nbox.w+bbox.w-delta,v);
          BBOX.clean();
        } else {
          frac.className += " MJXc-stacked";
          if (isDisplay) {u = CHTML.TEX.num1; v = CHTML.TEX.denom1}
            else {u = (t === 0 ? CHTML.TEX.num3 : CHTML.TEX.num2); v = CHTML.TEX.denom2}
          if (t === 0) { // \atop
            p = Math.max((isDisplay ? 7 : 3) * CHTML.TEX.rule_thickness, 2*mt); // force to at least 2 px
            q = (u - nbox.d*nscale) - (dbox.h*dscale - v);
            if (q < p) {u += (p - q)/2; v += (p - q)/2}
          } else { // \over
            p = Math.max((isDisplay ? 2 : 0) * mt + t, t/2 + 1.5*mt);
            t = Math.max(t,mt);
            q = (u - nbox.d*nscale) - (a + t/2); if (q < p) u += (p - q);
            q = (a - t/2) - (dbox.h*dscale - v); if (q < p) v += (p - q);
            nbox.L = nbox.R = dbox.L = dbox.R = .1;  // account for padding in BBOX width
            var rule = CHTML.addElement(frac,"mjx-line",{style: {
              "border-bottom":CHTML.Px(t*BBOX.scale,1)+" solid", top: CHTML.Em(-t/2-a)
            }});
          }
          //
          //  Determine the new bounding box and place the parts
          //
          BBOX.combine(nbox,0,u);
          BBOX.combine(dbox,0,-v);
          BBOX.clean();
          //
          //  Force elements to the correct width
          //
          frac.style.width = CHTML.Em(BBOX.w);
          num.style.width = CHTML.Em(BBOX.w/nscale);
          denom.style.width = CHTML.Em(BBOX.w/dscale);
          if (rule) rule.style.width = frac.style.width;
          //
          //  Place the numerator and denominator in relation to the baseline
          //
          num.style.top = CHTML.Em(-BBOX.h/nscale);
          denom.style.bottom = CHTML.Em(-BBOX.d/dscale);
          //
          //  Force the size of the surrounding box, since everything is absolutely positioned
          //
          CHTML.addElement(node,"mjx-vsize",{style: {
            height: CHTML.Em(BBOX.h+BBOX.d), verticalAlign: CHTML.Em(-BBOX.d)
          }});
        }
        //
        //  Add nulldelimiterspace around the fraction
        //  (TeXBook pg 150 and Appendix G rule 15e)
        //
        if (!this.texWithDelims) {
          var space = CHTML.TEX.nulldelimiterspace;
          frac.style.padding = "0 "+CHTML.Em(space);
          BBOX.l += space; BBOX.r += space; BBOX.w += 2*space;
        }
        //
        //  Return the completed fraction
        //
        return node;
      },
      CHTMLcanStretch: function (direction) {return false}
    });

    /********************************************************/
    
    MML.msqrt.Augment({
      toCommonHTML: function (node) {
        node = this.CHTMLdefaultNode(node,{
          childNodes:["mjx-box","mjx-root"], forceChild:true, noBBox:true
        });
        var base = node.firstChild || CHTML.Element("mjx-box");
        var sqrt = CHTML.addElement(node,"mjx-box"); sqrt.appendChild(base);
        var bbox = this.CHTMLbboxFor(0), BBOX = CHTML.BBOX.empty(this.CHTML);
        var t = CHTML.TEX.rule_thickness, T = CHTML.TEX.surd_height, p = t, q, H;
        if (this.Get("displaystyle")) p = CHTML.TEX.x_height;
        q = t + p/4;
        H = bbox.h + bbox.d + q + t;
        var surd = CHTML.Element("mjx-surd"); sqrt.insertBefore(surd,base);
        var sbox = CHTML.createDelimiter(surd,0x221A,[H-.04,H]);
        if (sbox.h + sbox.d > H) q = ((sbox.h+sbox.d) - (H-t))/2;
        H = bbox.h + q + t;
        var x = this.CHTMLaddRoot(node,sbox,sbox.h+sbox.d-H);
        base.style.paddingTop = CHTML.Em(q); 
        base.style.borderTop = CHTML.Px(T*bbox.scale,1)+" solid";
        sqrt.style.paddingTop = CHTML.Em(2*t-T);  // use wider line, but don't affect height
        bbox.h += q + 2*t;
        BBOX.combine(sbox,x,H-sbox.h);
        BBOX.combine(bbox,x+sbox.w,0);
        BBOX.clean();
        return node;
      },
      CHTMLaddRoot: function () {return 0},
      CHTMLhandleBBox: function (node) {
        var bbox = this.CHTMLbboxFor(0);
        delete bbox.pwidth;
        this.SUPER(arguments).CHTMLhandleBBox.apply(this,arguments);
      }
    });

    /********************************************************/
    
    MML.mroot.Augment({
      toCommonHTML: MML.msqrt.prototype.toCommonHTML,
      CHTMLhandleBBox: MML.msqrt.prototype.CHTMLhandleBBox,
      CHTMLaddRoot: function (sqrt,sbox,d) {
        if (!this.data[1]) return;
        var BBOX = this.CHTML, bbox = this.data[1].CHTML, root = sqrt.firstChild;
        var scale = bbox.rscale;
        var h = this.CHTMLrootHeight(bbox,sbox,scale)-d;
        var w = Math.min(bbox.w,bbox.r); // remove extra right-hand padding, if any
        var dx = Math.max(w,sbox.offset/scale); 
        if (h) root.style.verticalAlign = CHTML.Em(h/scale);
        if (dx > w) root.firstChild.style.paddingLeft = CHTML.Em(dx-w);
        dx -= sbox.offset/scale;
        root.style.width = CHTML.Em(dx);
        BBOX.combine(bbox,0,h);
        return dx*scale;
      },
      CHTMLrootHeight: function (bbox,sbox,scale) {
        return .45*(sbox.h+sbox.d-.9)+sbox.offset + Math.max(0,bbox.d-.075);
      }
    });
    
    /********************************************************/
    
    MML.mfenced.Augment({
      toCommonHTML: function (node) {
        node = this.CHTMLcreateNode(node);
        this.CHTMLhandleStyle(node);
        this.CHTMLhandleScale(node);
        //
        //  Make row of open, data, sep, ... data, close
        //
        this.CHTMLaddChild(node,"open",{});
        for (var i = 0, m = this.data.length; i < m; i++) {
          this.CHTMLaddChild(node,"sep"+i,{});
          this.CHTMLaddChild(node,i,{});
        }
        this.CHTMLaddChild(node,"close",{});
        //
        //  Check for stretching the elements
        //
        var H = this.CHTML.h, D = this.CHTML.d;
        this.CHTMLstretchChildV("open",H,D);
        for (i = 0, m = this.data.length; i < m; i++) {
          this.CHTMLstretchChildV("sep"+i,H,D);
          this.CHTMLstretchChildV(i,H,D);
        }
        this.CHTMLstretchChildV("close",H,D);
        this.CHTMLhandleSpace(node);
        this.CHTMLhandleBBox(node);
        this.CHTMLhandleColor(node);
        return node;
      }
    });

    /********************************************************/
    
    MML.mrow.Augment({
      toCommonHTML: function (node,options) {
        options = options || {};
        node = this.CHTMLdefaultNode(node);
        var bbox = this.CHTML, H = bbox.h, D = bbox.d, hasNegative;
        for (var i = 0, m = this.data.length; i < m; i++) {
          this.CHTMLstretchChildV(i,H,D);
          if (this.data[i] && this.data[i].CHTML && this.data[i].CHTML.w < 0) hasNegative = true;
        }
        if (this.CHTMLlineBreaks()) {
          this.CHTMLmultiline(node);
          if (options.autowidth) node.style.width = "";
        } else {
          if (hasNegative && bbox.w) node.style.width = CHTML.Em(Math.max(0,bbox.w));
          if (bbox.w < 0) node.style.marginRight = CHTML.Em(bbox.w);
        }
        return node;
      },
      CHTMLlineBreaks: function () {
        if (!this.parent.linebreakContainer) return false;
        return (LINEBREAKS.automatic && this.CHTML.w > CHTML.linebreakWidth) || this.hasNewline();
      },
      CHTMLstretchV: function (h,d) {
        this.CHTMLstretchChildV(this.CoreIndex(),h,d);
        return this.CHTML;
      },
      CHTMLstretchH: function (node,w) {
        this.CHTMLstretchChildH(this.CoreIndex(),w,node);
        return this.CHTML;
      }
    });

    /********************************************************/
    
    MML.TeXAtom.Augment({
      toCommonHTML: function (node,options) {
        if (!options || !options.stretch) node = this.CHTMLdefaultNode(node);
        if (this.texClass === MML.TEXCLASS.VCENTER) {
          var a = CHTML.TEX.axis_height, BBOX = this.CHTML;
          var v = a-(BBOX.h+BBOX.d)/2+BBOX.d;
          if (Math.abs(v) > .001) {
            node.style.verticalAlign = CHTML.Em(v);
            BBOX.h += v; BBOX.t += v; BBOX.d -= v; BBOX.b -= v;
          }
        }
        return node;
      },
      CHTMLstretchV: function (h,d) {
        this.CHTMLupdateFrom(this.Core().CHTMLstretchV(h,d));
        this.toCommonHTML(this.CHTMLnodeElement(),{stretch:true});
        return this.CHTML;
      },
      CHTMLstretchH: function (node,w) {
        this.CHTMLupdateFrom(this.CHTMLstretchCoreH(node,w));
        this.toCommonHTML(node,{stretch:true});
        return this.CHTML;
      }
    });

    /********************************************************/
    
    MML.semantics.Augment({
      toCommonHTML: function (node) {
        node = this.CHTMLcreateNode(node);
	if (this.data[0]) {
	  this.data[0].toCommonHTML(node);
	  this.CHTMLupdateFrom(this.data[0].CHTML);
          this.CHTMLhandleBBox(node);
	}
        return node;
      }
    });
    MML.annotation.Augment({toCommonHTML: function(node) {return this.CHTMLcreateNode(node)}});
    MML["annotation-xml"].Augment({toCommonHTML: MML.mbase.CHTMLautoload});

    /********************************************************/

    MML.ms.Augment({toCommonHTML: MML.mbase.CHTMLautoload});
    MML.mglyph.Augment({toCommonHTML: MML.mbase.CHTMLautoload});
    MML.menclose.Augment({toCommonHTML: MML.mbase.CHTMLautoload});
    MML.maction.Augment({toCommonHTML: MML.mbase.CHTMLautoload});
    MML.mmultiscripts.Augment({toCommonHTML: MML.mbase.CHTMLautoload});
    MML.mtable.Augment({toCommonHTML: MML.mbase.CHTMLautoload});
    
    /********************************************************/
    
    //
    //  Loading isn't complete until the element jax is modified,
    //  but can't call loadComplete within the callback for "mml Jax Ready"
    //  (it would call CommonHTML's Require routine, asking for the mml jax again)
    //  so wait until after the mml jax has finished processing.
    //  
    //  We also need to wait for the onload handler to run, since the loadComplete
    //  will call Config and Startup, which need to modify the body.
    //
    MathJax.Hub.Register.StartupHook("onLoad",function () {
      setTimeout(MathJax.Callback(["loadComplete",CHTML,"jax.js"]),0);
    });
  });

  MathJax.Hub.Register.StartupHook("End Cookie", function () {  
    if (HUB.config.menuSettings.zoom !== "None")
      {AJAX.Require("[MathJax]/extensions/MathZoom.js")}
  });
    
})(MathJax.Ajax,MathJax.Hub,MathJax.HTML,MathJax.OutputJax.CommonHTML);
