/* -*- Mode: Javascript; indent-tabs-mode:nil; js-indent-level: 2 -*- */
/* vim: set ts=2 et sw=2 tw=80: */

/*************************************************************
 *
 *  MathJax/jax/input/AsciiMath/config.js
 *
 *  Initializes the AsciiMath InputJax (the main definition is in
 *  MathJax/jax/input/AsciiMath/jax.js, which is loaded when needed).
 *  
 *  Originally adapted for MathJax by David Lippman.
 *  Additional work done by Davide P. Cervone.
 *  
 *  ---------------------------------------------------------------------
 *  
 *  Copyright (c) 2012-2018 The MathJax Consortium
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

MathJax.InputJax.AsciiMath = MathJax.InputJax({
  id: "AsciiMath",
  version: "2.7.5",
  directory: MathJax.InputJax.directory + "/AsciiMath",
  extensionDir: MathJax.InputJax.extensionDir + "/AsciiMath",
  
  config: {
    fixphi: true,                     // switch phi and varphi unicode values
    useMathMLspacing: true,           // use MathML spacing rather than TeX spacing?
    displaystyle: true,               // put limits above and below operators
    decimalsign: "."                  // can change to "," but watch out for "(1,2)"
  }
});
MathJax.InputJax.AsciiMath.Register("math/asciimath");

MathJax.InputJax.AsciiMath.loadComplete("config.js");
