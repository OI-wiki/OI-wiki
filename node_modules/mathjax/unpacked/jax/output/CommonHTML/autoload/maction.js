/* -*- Mode: Javascript; indent-tabs-mode:nil; js-indent-level: 2 -*- */
/* vim: set ts=2 et sw=2 tw=80: */

/*************************************************************
 *
 *  MathJax/jax/output/CommonHTML/autoload/maction.js
 *  
 *  Implements the CommonHTML output for <maction> elements.
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
  
  var currentTip, hover, clear;

  //
  //  Add configuration for tooltips
  //
  var CONFIG = CHTML.config.tooltip = MathJax.Hub.Insert({
    delayPost: 600, delayClear: 600,
    offsetX: 10, offsetY: 5
  },CHTML.config.tooltip||{});
  
  
  MML.maction.Augment({
    CHTMLtooltip: CHTML.addElement(document.body,"div",{id:"MathJax_CHTML_Tooltip"}),
    
    toCommonHTML: function (node) {
      var selected = this.Get("selection");
      node = this.CHTMLcreateNode(node);
      this.CHTML = CHTML.BBOX.empty();
      this.CHTMLhandleStyle(node);
      this.CHTMLhandleScale(node);
      this.CHTMLaddChild(node,selected-1,{});
      this.CHTML.clean();
      this.CHTMLhandleSpace(node);
      this.CHTMLhandleBBox(node);
      this.CHTMLhandleColor(node);
      
      var type = this.Get("actiontype");
      if (this.CHTMLaction[type] && this.CHTMLaction.hasOwnProperty(type))
        this.CHTMLaction[type].call(this,node,selected);

      return node;
    },
    CHTMLcoreNode: function (node) {return this.CHTMLchildNode(node,0)},
    
    //
    //  Implementations for the various actions
    //
    CHTMLaction: {
      toggle: function (node,selection) {
        this.selection = selection;
        node.onclick = MathJax.Callback(["CHTMLclick",this,CHTML.jax]);
        node.style.cursor = "pointer";
      },
      
      statusline: function (node,selection) {
        node.onmouseover = MathJax.Callback(["CHTMLsetStatus",this]);
        node.onmouseout  = MathJax.Callback(["CHTMLclearStatus",this]);
        node.onmouseover.autoReset = node.onmouseout.autoReset = true;
      },
      
      tooltip: function(node,selection) {
        if (this.data[1] && this.data[1].isToken) {
          node.title = node.alt = this.data[1].data.join("");
        } else {
          node.onmouseover = MathJax.Callback(["CHTMLtooltipOver",this,CHTML.jax]);
          node.onmouseout  = MathJax.Callback(["CHTMLtooltipOut",this,CHTML.jax]);
          node.onmouseover.autoReset = node.onmouseout.autoReset = true;
        }
      }
    },
    
    //
    //  Handle a click on the maction element
    //    (remove the original rendering and rerender)
    //
    CHTMLclick: function (jax,event) {
      this.selection++;
      if (this.selection > this.data.length) this.selection = 1;
      var hover = !!jax.hover;
      jax.Update();
      if (hover) {
        var span = document.getElementById(jax.inputID+"-Span");
        MathJax.Extension.MathEvents.Hover.Hover(jax,span);
      }
      return MathJax.Extension.MathEvents.Event.False(event);
    },
    
    //
    //  Set/Clear the window status message
    //
    CHTMLsetStatus: function (event) {
      // FIXME:  Do something better with non-token elements
      this.messageID = MathJax.Message.Set
        ((this.data[1] && this.data[1].isToken) ?
             this.data[1].data.join("") : this.data[1].toString());
    },
    CHTMLclearStatus: function (event) {
      if (this.messageID) MathJax.Message.Clear(this.messageID,0);
      delete this.messageID;
    },
    
    //
    //  Handle tooltips
    //
    CHTMLtooltipOver: function (jax,event) {
      if (!event) event = window.event;
      if (clear) {clearTimeout(clear); clear = null}
      if (hover) clearTimeout(hover);
      var x = event.pageX; var y = event.pageY;
      if (x == null) {
        x = event.clientX + document.body.scrollLeft + document.documentElement.scrollLeft;
        y = event.clientY + document.body.scrollTop + document.documentElement.scrollTop;
      }
      var callback = MathJax.Callback(["CHTMLtooltipPost",this,jax,x+CONFIG.offsetX,y+CONFIG.offsetY])
      hover = setTimeout(callback,CONFIG.delayPost);
    },
    CHTMLtooltipOut: function (jax,event) {
      if (hover) {clearTimeout(hover); hover = null}
      if (clear) clearTimeout(clear);
      var callback = MathJax.Callback(["CHTMLtooltipClear",this,80]);
      clear = setTimeout(callback,CONFIG.delayClear);
    },
    CHTMLtooltipPost: function (jax,x,y) {
      hover = null; if (clear) {clearTimeout(clear); clear = null}
      var tip = this.CHTMLtooltip;
      tip.style.display = "block"; tip.style.opacity = "";
//      tip.style.filter = CHTML.config.styles["#MathJax_CHTML_Tooltip"].filter;
      if (this === currentTip) return;
      tip.style.left = x+"px"; tip.style.top = y+"px";
      tip.innerHTML = '<span class="mjx-chtml"><span class="mjx-math"></span></span>';
      CHTML.getMetrics(jax);
      try {this.data[1].toCommonHTML(tip.firstChild.firstChild)}  catch(err) {
        if (!err.restart) throw err;
        tip.style.display = "none";
        MathJax.Callback.After(["CHTMLtooltipPost",this,jax,x,y],err.restart);
        return;
      }
      currentTip = this;
    },
    CHTMLtooltipClear: function (n) {
      var tip = this.CHTMLtooltip;
      if (n <= 0) {
        tip.style.display = "none";
        tip.style.opacity = tip.style.filter = "";
        clear = null;
      } else {
        tip.style.opacity = n/100;
        tip.style.filter = "alpha(opacity="+n+")";
        clear = setTimeout(MathJax.Callback(["CHTMLtooltipClear",this,n-20]),50);
      }
    }
  });

  MathJax.Hub.Startup.signal.Post("CommonHTML maction Ready");
  MathJax.Ajax.loadComplete(CHTML.autoloadDir+"/maction.js");
});

