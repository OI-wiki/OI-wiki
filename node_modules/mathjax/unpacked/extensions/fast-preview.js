/* -*- Mode: Javascript; indent-tabs-mode:nil; js-indent-level: 2 -*- */
/* vim: set ts=2 et sw=2 tw=80: */

/*************************************************************
 *
 *  MathJax/extensions/fast-preview.js
 *  
 *  Implements a fast preview using the PreviewHTML output jax
 *  and then a slower update to the more accurate HTML-CSS output
 *  (or whatever the user has selected).
 *  
 *  ---------------------------------------------------------------------
 *  
 *  Copyright (c) 2014-2018 The MathJax Consortium
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

(function (HUB,HTML,BROWSER) {
  
  var SETTINGS = HUB.config.menuSettings;
  var JAX = MathJax.OutputJax;
  var msieColorBug = BROWSER.isMSIE && (document.documentMode||0) < 8;

  var FastPreview = MathJax.Extension["fast-preview"] = {
    version: "2.7.5",
    enabled: true,

    //
    //  Configuration for the chunking of the main output
    //  after the previews have been created, and other configuration.
    //
    config: HUB.CombineConfig("fast-preview",{
      Chunks: {EqnChunk: 10000, EqnChunkFactor: 1, EqnChunkDelay: 0},
      color: "inherit!important",
      updateTime: 30, updateDelay: 6,
      messageStyle: "none",
      disabled: BROWSER.isMSIE && !BROWSER.versionAtLeast("8.0")
    }),

    //
    //  Ajust the chunking of the output jax
    //
    Config: function () {
      if (HUB.config["CHTML-preview"])
        MathJax.Hub.Config({"fast-preview": HUB.config["CHTML-preview"]});
      var update, delay, style, done, saved;
      var config = this.config;

      if (!config.disabled && SETTINGS.FastPreview == null)
        HUB.Config({menuSettings:{FastPreview:true}});
      if (SETTINGS.FastPreview) {
        MathJax.Ajax.Styles({".MathJax_Preview .MJXf-math":{color:config.color}});
        HUB.Config({"HTML-CSS": config.Chunks, CommonHTML: config.Chunks, SVG: config.Chunks});
      }
      HUB.Register.MessageHook("Begin Math Output",function () {
        if (!done && FastPreview.Active()) {
          update = HUB.processUpdateTime; delay = HUB.processUpdateDelay;
          style = HUB.config.messageStyle;
          HUB.processUpdateTime = config.updateTime;
          HUB.processUpdateDelay = config.updateDelay;
          HUB.Config({messageStyle: config.messageStyle});
          MathJax.Message.Clear(0,0);
          saved = true;
        }
      });
      HUB.Register.MessageHook("End Math Output",function () {
        if (!done && saved) {
          HUB.processUpdateTime = update;
          HUB.processUpdateDelay = delay;
          HUB.Config({messageStyle: style});
          done = true;
        }
      });
    },
    
    //
    //  Allow page to override user settings (for things like editor previews)
    //
    Disable: function () {this.enabled = false},
    Enable: function () {this.enabled = true},
    
    Active: function () {
      return SETTINGS.FastPreview && this.enabled &&
             !(JAX[SETTINGS.renderer]||{}).noFastPreview;
    },

    //
    //  Insert a preview span, if there isn't one already,
    //  and call the PreviewHTML output jax to create the preview
    //
    Preview: function (data) {
      if (!this.Active() || !data.script.parentNode) return;
      var preview = data.script.MathJax.preview || data.script.previousSibling;
      if (!preview || preview.className !== MathJax.Hub.config.preRemoveClass) {
        preview = HTML.Element("span",{className:MathJax.Hub.config.preRemoveClass});
        data.script.parentNode.insertBefore(preview,data.script);
        data.script.MathJax.preview = preview;
      }
      preview.innerHTML = "";
      preview.style.color = (msieColorBug ? "black" : "inherit");
      return this.postFilter(preview,data);
    },
    postFilter: function (preview,data) {
      //
      //  Load the PreviewHTML jax if it is not already loaded
      //
      if (!data.math.root.toPreviewHTML) {
        var queue = MathJax.Callback.Queue();
        queue.Push(
          ["Require",MathJax.Ajax,"[MathJax]/jax/output/PreviewHTML/config.js"],
          ["Require",MathJax.Ajax,"[MathJax]/jax/output/PreviewHTML/jax.js"]
        );
        HUB.RestartAfter(queue.Push({}));
      }
      data.math.root.toPreviewHTML(preview);
    },

    //
    //  Hook into the input jax postFilter to create the previews as
    //  the input jax are processed.
    //
    Register: function (name) {
      HUB.Register.StartupHook(name+" Jax Require",function () {
        var jax = MathJax.InputJax[name];
        jax.postfilterHooks.Add(["Preview",MathJax.Extension["fast-preview"]],50);
      });
    }
  }

  //
  //  Hook into each input jax
  //
  FastPreview.Register("TeX");
  FastPreview.Register("MathML");
  FastPreview.Register("AsciiMath");
  
  HUB.Register.StartupHook("End Config",["Config",FastPreview]);
  
  HUB.Startup.signal.Post("fast-preview Ready");

})(MathJax.Hub,MathJax.HTML,MathJax.Hub.Browser);

MathJax.Ajax.loadComplete("[MathJax]/extensions/fast-preview.js");

