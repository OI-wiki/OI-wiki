/* -*- Mode: Javascript; indent-tabs-mode:nil; js-indent-level: 2 -*- */
/* vim: set ts=2 et sw=2 tw=80: */

/*************************************************************
 *
 *  MathJax/extensions/MatchWebFonts.js
 *  
 *  Adds code to the output jax so that if web fonts are used on the page,
 *  MathJax will be able to detect their arrival and update the math to
 *  accommodate the change in font.  For the NativeMML output, this works
 *  both for web fonts in main text, and for web fonts in the math as well.
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

(function (HUB,AJAX) {
  var VERSION = "2.7.5";
  
  var CONFIG = MathJax.Hub.CombineConfig("MatchWebFonts",{
    matchFor: {
      "HTML-CSS": true,
      NativeMML: true,
      SVG: true
    },
    fontCheckDelay: 500,          // initial delay for the first check for web fonts
    fontCheckTimeout: 15 * 1000,  // how long to keep looking for fonts (15 seconds)
  });
  
  MathJax.Extension.MatchWebFonts = {
    version: VERSION,
    config: CONFIG
  };
  
  HUB.Register.StartupHook("HTML-CSS Jax Ready",function () {
    var HTMLCSS = MathJax.OutputJax["HTML-CSS"];
    var POSTTRANSLATE = HTMLCSS.postTranslate;

    HTMLCSS.Augment({
      postTranslate: function (state,partial) {
        if (!partial && CONFIG.matchFor["HTML-CSS"] && this.config.matchFontHeight) {
          //
          //  Check for changes in the web fonts that might affect the font
          //  size for math elements.  This is a periodic check that goes on
          //  until a timeout is reached.
          //
          AJAX.timer.start(AJAX,["checkFonts",this,state.jax[this.id]],
                           CONFIG.fontCheckDelay,CONFIG.fontCheckTimeout);
        }
        return POSTTRANSLATE.apply(this,arguments); // do the original function
      },
      
      checkFonts: function (check,scripts) {
        if (check.time(function () {})) return;
        var size = [], i, m, retry = false;
        //
        //  Add the elements used for testing ex and em sizes
        //
        for (i = 0, m = scripts.length; i < m; i++) {
          script = scripts[i];
          if (script.parentNode && script.MathJax.elementJax) {
            script.parentNode.insertBefore(this.EmExSpan.cloneNode(true),script);
          }
        }
        //
        //  Check to see if anything has changed
        //
        for (i = 0, m = scripts.length; i < m; i++) {
          script = scripts[i]; if (!script.parentNode) continue; retry = true;
          var jax = script.MathJax.elementJax; if (!jax) continue;
          //
          //  Check if ex or mex has changed
          //
          var test = script.previousSibling;
          var ex = test.firstChild.offsetHeight/60;
          var em = test.lastChild.lastChild.offsetHeight/60;
          if (ex === 0 || ex === "NaN") {ex = this.defaultEx; em = this.defaultEm}
          if (ex !== jax.HTMLCSS.ex || em !== jax.HTMLCSS.em) {
            var scale = ex/this.TeX.x_height/em;
            scale = Math.floor(Math.max(this.config.minScaleAdjust/100,scale)*this.config.scale);
            if (scale/100 !== jax.scale) {size.push(script); scripts[i] = {}}
          }
        }
        //
        //  Remove markers
        //
        scripts = scripts.concat(size);  // some scripts have been moved to the size array
        for (i = 0, m = scripts.length; i < m; i++) {
          script = scripts[i];
          if (script && script.parentNode && script.MathJax.elementJax) {
            script.parentNode.removeChild(script.previousSibling);
          }
        }
        //
        //  Rerender the changed items
        //
        if (size.length) {HUB.Queue(["Rerender",HUB,[size],{}])}
        //
        //  Try again later
        //
        if (retry) {setTimeout(check,check.delay)}
      }
    });
  });
  
  HUB.Register.StartupHook("SVG Jax Ready",function () {
    var SVG = MathJax.OutputJax.SVG;
    var POSTTRANSLATE = SVG.postTranslate;

    SVG.Augment({
      postTranslate: function (state,partial) {
        if (!partial && CONFIG.matchFor.SVG) {
          //
          //  Check for changes in the web fonts that might affect the font
          //  size for math elements.  This is a periodic check that goes on
          //  until a timeout is reached.
          //
          AJAX.timer.start(AJAX,["checkFonts",this,state.jax[this.id]],
                           CONFIG.fontCheckDelay,CONFIG.fontCheckTimeout);
        }
        return POSTTRANSLATE.apply(this,arguments); // do the original function
      },
      
      checkFonts: function (check,scripts) {
        if (check.time(function () {})) return;
        var size = [], i, m, retry = false;
        //
        //  Add the elements used for testing ex and em sizes
        //
        for (i = 0, m = scripts.length; i < m; i++) {
          script = scripts[i];
          if (script.parentNode && script.MathJax.elementJax) {
            script.parentNode.insertBefore(this.ExSpan.cloneNode(true),script);
          }
        }
        //
        //  Check to see if anything has changed
        //
        for (i = 0, m = scripts.length; i < m; i++) {
          script = scripts[i]; if (!script.parentNode) continue; retry = true;
          var jax = script.MathJax.elementJax; if (!jax) continue;
          //
          //  Check if ex or mex has changed
          //
          var test = script.previousSibling;
          var ex = test.firstChild.offsetHeight/60;
          if (ex === 0 || ex === "NaN") {ex = this.defaultEx}
          if (ex !== jax.SVG.ex) {size.push(script); scripts[i] = {}}
        }
        //
        //  Remove markers
        //
        scripts = scripts.concat(size);  // some scripts have been moved to the size array
        for (i = 0, m = scripts.length; i < m; i++) {
          script = scripts[i];
          if (script.parentNode && script.MathJax.elementJax) {
            script.parentNode.removeChild(script.previousSibling);
          }
        }
        //
        //  Rerender the changed items
        //
        if (size.length) {HUB.Queue(["Rerender",HUB,[size],{}])}
        //
        //  Try again later (if not all the scripts are null)
        //

        if (retry) setTimeout(check,check.delay);
      }
    });
  });
 
  HUB.Register.StartupHook("NativeMML Jax Ready",function () {
    var nMML = MathJax.OutputJax.NativeMML;
    var POSTTRANSLATE = nMML.postTranslate;
    
    nMML.Augment({
      postTranslate: function (state) {
        if (!HUB.Browser.isMSIE && CONFIG.matchFor.NativeMML) {
          //
          //  Check for changes in the web fonts that might affect the sizes
          //  of math elements.  This is a periodic check that goes on until
          //  a timeout is reached.
          //
          AJAX.timer.start(AJAX,["checkFonts",this,state.jax[this.id]],
                           CONFIG.fontCheckDelay,CONFIG.fontCheckTimeout);
        }
        POSTTRANSLATE.apply(this,arguments); // do the original routine
      },
      
      //
      //  Check to see if web fonts have been loaded that change the ex size
      //  of the surrounding font, the ex size within the math, or the widths
      //  of math elements.  We do this by rechecking the ex and mex sizes
      //  (to see if the font scaling needs adjusting) and by checking the
      //  size of the inner mrow of math elements and mtd elements.  The
      //  sizes of these have been stored in the NativeMML object of the
      //  element jax so that we can check for them here.
      //
      checkFonts: function (check,scripts) {
        if (check.time(function () {})) return;
        var adjust = [], mtd = [], size = [], i, m, script;
        //
        //  Add the elements used for testing ex and em sizes
        //
        for (i = 0, m = scripts.length; i < m; i++) {
          script = scripts[i];
          if (script.parentNode && script.MathJax.elementJax) {
            script.parentNode.insertBefore(this.EmExSpan.cloneNode(true),script);
          }
        }
        //
        //  Check to see if anything has changed
        //
        for (i = 0, m = scripts.length; i < m; i++) {
          script = scripts[i]; if (!script.parentNode) continue;
          var jax = script.MathJax.elementJax; if (!jax) continue;
          var span = document.getElementById(jax.inputID+"-Frame");
          var math = span.getElementsByTagName("math")[0]; if (!math) continue;
          jax = jax.NativeMML;
          //
          //  Check if ex or mex has changed
          //
          var test = script.previousSibling;
          var ex = test.firstChild.offsetWidth/60;
          var mex = test.lastChild.offsetWidth/60;
          if (ex === 0 || ex === "NaN") {ex = this.defaultEx; mex = this.defaultMEx}
          var newEx = (ex !== jax.ex);
          if (newEx || mex != jax.mex) {
            var scale = (this.config.matchFontHeight && mex > 1 ? ex/mex : 1);
            scale = Math.floor(Math.max(this.config.minScaleAdjust/100,scale) * this.config.scale);
            if (scale/100 !== jax.scale) {size.push([span.style,scale])}
            jax.scale = scale/100; jax.fontScale = scale+"%"; jax.ex = ex; jax.mex = mex;
          }
          
          //
          //  Check width of math elements
          //
          if ("scrollWidth" in jax && (newEx || jax.scrollWidth !== math.firstChild.scrollWidth)) {
            jax.scrollWidth = math.firstChild.scrollWidth;
            adjust.push([math.parentNode.style,jax.scrollWidth/jax.ex/jax.scale]);
          }
          //
          //  Check widths of mtd elements
          //
          if (math.MathJaxMtds) {
            for (var j = 0, n = math.MathJaxMtds.length; j < n; j++) {
              if (!math.MathJaxMtds[j].parentNode) continue;
              if (newEx || math.MathJaxMtds[j].firstChild.scrollWidth !== jax.mtds[j]) {
                jax.mtds[j] = math.MathJaxMtds[j].firstChild.scrollWidth;
                mtd.push([math.MathJaxMtds[j],jax.mtds[j]/jax.ex]);
              }
            }
          }
        }
        //
        //  Remove markers
        //
        for (i = 0, m = scripts.length; i < m; i++) {
          script = scripts[i];
          if (script.parentNode && script.MathJax.elementJax) {
            script.parentNode.removeChild(script.previousSibling);
          }
        }
        //
        //  Adjust scaling factor
        //
        for (i = 0, m = size.length; i < m; i++) {
          size[i][0].fontSize = size[i][1] + "%";
        }
        //
        //  Adjust width of spans containing math elements that have changed
        //
        for (i = 0, m = adjust.length; i < m; i++) {
          adjust[i][0].width = adjust[i][1].toFixed(3)+"ex";
        }
        //
        //  Adjust widths of mtd elements that have changed
        //
        for (i = 0, m = mtd.length; i < m; i++) {
          var style = mtd[i][0].getAttribute("style");
          style = style.replace(/(($|;)\s*min-width:).*?ex/,"$1 "+mtd[i][1].toFixed(3)+"ex");
          mtd[i][0].setAttribute("style",style);
        }
        //
        //  Try again later
        //
        setTimeout(check,check.delay);
      }
    });
  });
  
  HUB.Startup.signal.Post("MatchWebFonts Extension Ready");
  AJAX.loadComplete("[MathJax]/extensions/MatchWebFonts.js");

})(MathJax.Hub,MathJax.Ajax);
