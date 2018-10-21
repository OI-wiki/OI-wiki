/* -*- Mode: Javascript; indent-tabs-mode:nil; js-indent-level: 2 -*- */
/* vim: set ts=2 et sw=2 tw=80: */

/*************************************************************
 *
 *  MathJax/extensions/TeX/boldsymbol.js
 *  
 *  Implements the \boldsymbol{...} command to make bold
 *  versions of all math characters (not just variables).
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

MathJax.Extension["TeX/boldsymbol"] = {
  version: "2.7.5"
};

MathJax.Hub.Register.StartupHook("TeX Jax Ready",function () {
  
  var MML = MathJax.ElementJax.mml;
  var TEX = MathJax.InputJax.TeX;
  var TEXDEF = TEX.Definitions;
  
  var BOLDVARIANT = {};
  BOLDVARIANT[MML.VARIANT.NORMAL]    = MML.VARIANT.BOLD;
  BOLDVARIANT[MML.VARIANT.ITALIC]    = MML.VARIANT.BOLDITALIC;
  BOLDVARIANT[MML.VARIANT.FRAKTUR]   = MML.VARIANT.BOLDFRAKTUR;
  BOLDVARIANT[MML.VARIANT.SCRIPT]    = MML.VARIANT.BOLDSCRIPT;
  BOLDVARIANT[MML.VARIANT.SANSSERIF] = MML.VARIANT.BOLDSANSSERIF;
  BOLDVARIANT["-tex-caligraphic"]    = "-tex-caligraphic-bold";
  BOLDVARIANT["-tex-oldstyle"]       = "-tex-oldstyle-bold";
  
  TEXDEF.Add({macros: {boldsymbol: 'Boldsymbol'}},null,true);
  
  TEX.Parse.Augment({
    mmlToken: function (token) {
      if (this.stack.env.boldsymbol) {
        var variant = token.Get("mathvariant");
        if (variant == null) {token.mathvariant = MML.VARIANT.BOLD}
        else {token.mathvariant = (BOLDVARIANT[variant]||variant)}
      }
      return token;
    },
    
    Boldsymbol: function (name) {
      var boldsymbol = this.stack.env.boldsymbol,
          font = this.stack.env.font;
      this.stack.env.boldsymbol = true;
      this.stack.env.font = null;
      var mml = this.ParseArg(name);
      this.stack.env.font = font;
      this.stack.env.boldsymbol = boldsymbol;
      this.Push(mml);
    }
  });
  
  MathJax.Hub.Startup.signal.Post("TeX boldsymbol Ready");

});

MathJax.Ajax.loadComplete("[MathJax]/extensions/TeX/boldsymbol.js");
