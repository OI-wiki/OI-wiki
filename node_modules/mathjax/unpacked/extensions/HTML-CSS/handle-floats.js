/* -*- Mode: Javascript; indent-tabs-mode:nil; js-indent-level: 2 -*- */
/* vim: set ts=2 et sw=2 tw=80: */

/*************************************************************
 *
 *  MathJax/extensions/HTML-CSS/handle-floats.js
 *
 *  This extension allows HTML-CSS output to deal with floating elements
 *  better.  In particular, when there are tags or equation numbers, these
 *  would overlap floating elements, but with this extension, the width of
 *  the line should properly correspond to the amount of space remaining.
 *  
 *  To load it, include
 *  
 *      "HTML-CSS": {
 *        extensions: ["handle-floats.js"]
 *      }
 *  
 *  in your configuration.
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


MathJax.Extension["HTML-CSS/handle-floats"] = {
  version: "2.7.5"
};

//
//  This file is now obsolete, since the HTML-CSS output already handles
//  floating elements properly.
//

MathJax.Hub.Startup.signal.Post("HTML-CSS handle-floats Ready");
MathJax.Ajax.loadComplete("[MathJax]/extensions/HTML-CSS/handle-floats.js");
