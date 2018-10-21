/*************************************************************
 *
 *  MathJax/localization/scn/scn.js
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
MathJax.Localization.addTranslation("scn",null,{
  menuTitle: "sicilianu",
  version: "2.7.5",
  isLoaded: true,
  domains: {
    "_": {
        version: "2.7.5",
        isLoaded: true,
        strings: {
          MathProcessingError: "Erruri nt\u00E2 labburazzioni d\u00EE f\u00F2rmuli matim\u00E0tichi",
          MathError: "Erruri nt\u00E2 matim\u00E0tica",
          LoadFile: "Carricamentu di %1",
          Loading: "Carricamentu",
          LoadFailed: "Nun arrinisc\u00ECu lu carricamentu di: %1",
          ProcessMath: "Labburazzioni d\u00EE f\u00F2rmuli matim\u00E0tichi: %1%%",
          Processing: "Labburazzioni",
          TypesetMath: "Mpagginazzioni d\u00EE f\u00F2rmuli matim\u00E0tichi: %1%%",
          Typesetting: "Mpagginazzioni",
          MathJaxNotSupported: "Lu t\u00F2 browser nun supporta MathJax"
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
      return String(n).replace(".", ","); // replace dot by comma
    }
});

MathJax.Ajax.loadComplete("[MathJax]/localization/scn/scn.js");
