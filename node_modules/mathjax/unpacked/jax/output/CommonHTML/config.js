/* -*- Mode: Javascript; indent-tabs-mode:nil; js-indent-level: 2 -*- */
/* vim: set ts=2 et sw=2 tw=80: */

/*************************************************************
 *
 *  MathJax/jax/output/HTML2/config.js
 *  
 *  Initializes the HTML2 OutputJax  (the main definition is in
 *  MathJax/jax/input/HTML2/jax.js, which is loaded when needed).
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

MathJax.OutputJax.CommonHTML = MathJax.OutputJax({
  id: "CommonHTML",
  version: "2.7.5",
  directory: MathJax.OutputJax.directory + "/CommonHTML",
  extensionDir: MathJax.OutputJax.extensionDir + "/CommonHTML",
  autoloadDir: MathJax.OutputJax.directory + "/CommonHTML/autoload",
  fontDir: MathJax.OutputJax.directory + "/CommonHTML/fonts",  // fontname added later
  webfontDir: MathJax.OutputJax.fontDir + "/HTML-CSS",         // fontname added later
  
  config: {
    matchFontHeight: true,          // try to match math font height to surrounding font?
    scale: 100, minScaleAdjust: 50, // global math scaling factor, and minimum adjusted scale factor
    mtextFontInherit: false,        // to make <mtext> be in page font rather than MathJax font
    undefinedFamily: "STIXGeneral,'Cambria Math','Arial Unicode MS',serif",

    EqnChunk: (MathJax.Hub.Browser.isMobile ? 20: 100),
                                    // number of equations to process before showing them
    EqnChunkFactor: 1.5,            // chunk size is multiplied by this after each chunk
    EqnChunkDelay: 100,             // milliseconds to delay between chunks (to let browser
                                    //   respond to other events)

    linebreaks: {
      automatic: false,   // when false, only process linebreak="newline",
                          // when true, insert line breaks automatically in long expressions.

      width: "container" // maximum width of a line for automatic line breaks (e.g. "30em").
                         // use "container" to compute size from containing element,
                         // use "nn% container" for a portion of the container,
                         // use "nn%" for a portion of the window size
    }
    
  }
});

if (!MathJax.Hub.config.delayJaxRegistration) {MathJax.OutputJax.CommonHTML.Register("jax/mml")}

MathJax.OutputJax.CommonHTML.loadComplete("config.js");
