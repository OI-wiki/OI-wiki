/* -*- Mode: Javascript; indent-tabs-mode:nil; js-indent-level: 2 -*- */
/* vim: set ts=2 et sw=2 tw=80: */

/*************************************************************
 *
 *  MathJax/jax/output/CommonHTML/autoload/annotation-xm;l.js
 *  
 *  Implements the CommonHTML output for <annotation-xml> elements.
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

  MML["annotation-xml"].Augment({
    toCommonHTML: function (node) {
      var encoding = this.Get("encoding");
      node = this.CHTMLdefaultNode(node,{childOptions:{encoding:encoding}});
      if (this.CHTML.rscale !== 1) this.CHTML.rescale(1/this.CHTML.rscale);
      return node;
    }
  });
  
  MML.xml.Augment({
    toCommonHTML: function (node,options) {
      var bbox = this.CHTML = CHTML.BBOX.zero();
      for (var i = 0, m = this.data.length; i < m; i++) 
        {node.appendChild(this.data[i].cloneNode(true))}
      //
      //  Warning: causes reflow
      //
      var w = node.offsetWidth, h = node.offsetHeight;
      var strut = CHTML.addElement(node,"mjx-hd-test",{style:{height:h+"px"}});
      bbox.d = bbox.b = (node.offsetHeight - h)/CHTML.em;
      bbox.w = bbox.r = w/CHTML.em; bbox.h = bbox.t = h/CHTML.em - bbox.d;
      node.removeChild(strut);
    }
  });
  
  MathJax.Hub.Startup.signal.Post("CommonHTML annotation-xml Ready");
  MathJax.Ajax.loadComplete(CHTML.autoloadDir+"/annotation-xml.js");
});

