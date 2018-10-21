/* -*- Mode: Javascript; indent-tabs-mode:nil; js-indent-level: 2 -*- */
/* vim: set ts=2 et sw=2 tw=80: */

/*************************************************************
 *
 *  MathJax/extensions/AssistiveMML.js
 *  
 *  Implements an extension that inserts hidden MathML into the
 *  page for screen readers or other asistive technology.
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

(function (AJAX,CALLBACK,HUB,HTML) {
  var SETTINGS = HUB.config.menuSettings;
  
  var AssistiveMML = MathJax.Extension["AssistiveMML"] = {
    version: "2.7.5",
    
    config: HUB.CombineConfig("AssistiveMML",{
      disabled: false,
      styles: {
        ".MJX_Assistive_MathML": {
          position:"absolute!important",
          top: 0, left: 0,
          clip: (HUB.Browser.isMSIE && (document.documentMode||0) < 8 ?
                 "rect(1px 1px 1px 1px)" : "rect(1px, 1px, 1px, 1px)"),
          padding: "1px 0 0 0!important",
          border: "0!important",
          height: "1px!important",
          width: "1px!important",
          overflow: "hidden!important",
          display:"block!important",
          //
          //  Don't allow the assistive MathML become part of the selection
          //
          "-webkit-touch-callout": "none",
          "-webkit-user-select": "none",
          "-khtml-user-select": "none",
          "-moz-user-select": "none",
          "-ms-user-select": "none",
          "user-select": "none"
        },
        ".MJX_Assistive_MathML.MJX_Assistive_MathML_Block": {
          width: "100%!important"
        }
      }
    }),
    
    Config: function () {
      if (!this.config.disabled && SETTINGS.assistiveMML == null)
        HUB.Config({menuSettings:{assistiveMML:true}});
      AJAX.Styles(this.config.styles);
      HUB.Register.MessageHook("End Math",function (msg) {
        if (SETTINGS.assistiveMML) return AssistiveMML.AddAssistiveMathML(msg[1])
      });
    },
    
    //
    //  This sets up a state object that lists the jax and index into the jax,
    //    and a dummy callback that is used to synchronizing with MathJax.
    //    It will be called when the jax are all processed, and that will
    //    let the MathJax queue continue (it will block until then).
    //
    AddAssistiveMathML: function (node) {
      var state = {
        jax: HUB.getAllJax(node), i: 0,
        callback: MathJax.Callback({})
      };
      this.HandleMML(state);
      return state.callback;
    },

    //
    //  This removes the data-mathml attribute and the assistive MathML from
    //  all the jax.
    //
    RemoveAssistiveMathML: function (node) {
      var jax = HUB.getAllJax(node), frame;
      for (var i = 0, m = jax.length; i < m; i++) {
        frame = document.getElementById(jax[i].inputID+"-Frame");
        if (frame && frame.getAttribute("data-mathml")) {
          frame.removeAttribute("data-mathml");
          if (frame.lastChild && frame.lastChild.className.match(/MJX_Assistive_MathML/))
            frame.removeChild(frame.lastChild);
        }
      }
    },

    //
    //  For each jax in the state, look up the frame.
    //  If the jax doesn't use NativeMML and hasn't already been handled:
    //    Get the MathML for the jax, taking resets into account.
    //    Add a data-mathml attribute to the frame, and
    //    Create a span that is not visible on screen and put the MathML in it,
    //      and add it to the frame.
    //  When all the jax are processed, call the callback.
    //
    HandleMML: function (state) {
      var m = state.jax.length, jax, mml, frame, span;
      while (state.i < m) {
        jax = state.jax[state.i];
        frame = document.getElementById(jax.inputID+"-Frame");
        if (jax.outputJax !== "NativeMML" && jax.outputJax !== "PlainSource" &&
            frame && !frame.getAttribute("data-mathml")) {
          try {
            mml = jax.root.toMathML("").replace(/\n */g,"").replace(/<!--.*?-->/g,"");
          } catch (err) {
            if (!err.restart) throw err; // an actual error
            return MathJax.Callback.After(["HandleMML",this,state],err.restart);
          }
          frame.setAttribute("data-mathml",mml);
          span = HTML.addElement(frame,"span",{
            isMathJax: true, unselectable: "on",
            className: "MJX_Assistive_MathML"
              + (jax.root.Get("display") === "block" ? " MJX_Assistive_MathML_Block" : "")
          });
          try {span.innerHTML = mml} catch (err) {}
          frame.style.position = "relative";
          frame.setAttribute("role","presentation");
          frame.firstChild.setAttribute("aria-hidden","true");
          span.setAttribute("role","presentation");
        }
        state.i++;
      }
      state.callback();
    }
    
  };

  HUB.Startup.signal.Post("AssistiveMML Ready");

})(MathJax.Ajax,MathJax.Callback,MathJax.Hub,MathJax.HTML);

//
//  Make sure the toMathML extension is loaded before we signal
//  the load complete for this extension.  Then wait for the end
//  of the user configuration before configuring this extension. 
//
MathJax.Callback.Queue(
  ["Require",MathJax.Ajax,"[MathJax]/extensions/toMathML.js"],
  ["loadComplete",MathJax.Ajax,"[MathJax]/extensions/AssistiveMML.js"],
  function () {
    MathJax.Hub.Register.StartupHook("End Config",["Config",MathJax.Extension.AssistiveMML]);
  }
);

