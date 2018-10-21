/*************************************************************
 *
 *  MathJax/localization/en/en.js
 *
 *  Copyright (c) 2009-2018 The MathJax Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 */
MathJax.Localization.addTranslation("en",null,{
  menuTitle: "English",
  version: "2.7.5",
  isLoaded: true,
  domains: {
    "_": {
        version: "2.7.5",
        isLoaded: true,
        strings: {
          CookieConfig: "MathJax has found a user-configuration cookie that includes code to be run. Do you want to run it?\n\n(You should press Cancel unless you set up the cookie yourself.)",
          MathProcessingError: "Math processing error",
          MathError: "Math error",
          LoadFile: "Loading %1",
          Loading: "Loading",
          LoadFailed: "File failed to load: %1",
          ProcessMath: "Processing math: %1%%",
          Processing: "Processing",
          TypesetMath: "Typesetting math: %1%%",
          Typesetting: "Typesetting",
          MathJaxNotSupported: "Your browser does not support MathJax",
          ErrorTips: "Debugging tips: use %%1, inspect %%2 in the browser console"
        }
    },
    "FontWarnings": {},
    "HTML-CSS": {},
    "HelpDialog": {},
    "MathML": {},
    "MathMenu": {},
    "TeX": {}
  },
  plural: function (n) {
      if (n === 1) {return 1} // one
      return 2; // other
    },
  number: function (n) {
      return n;
    }
});

MathJax.Ajax.loadComplete("[MathJax]/localization/en/en.js");
