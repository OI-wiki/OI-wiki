/*************************************************************
 *
 *  MathJax/localization/eo/eo.js
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
MathJax.Localization.addTranslation("eo",null,{
  menuTitle: "Esperanto",
  version: "2.7.5",
  isLoaded: true,
  domains: {
    "_": {
        version: "2.7.5",
        isLoaded: true,
        strings: {
          Loading: "\u015Cargado",
          LoadFailed: "\u015Cargado de dosiero malsukcesis: %1",
          ProcessMath: "Prilaborado de formulo: %1 %%",
          Processing: "Prilaborado",
          TypesetMath: "Kompostado de formulo: %1 %%",
          Typesetting: "Kompostado",
          MathJaxNotSupported: "Via krozilo ne subtenas Mathjax."
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
      if (n === 1) return 1; // one
      return 2; // other
    },
  number: function (n) {
      return n;
    }
});

MathJax.Ajax.loadComplete("[MathJax]/localization/eo/eo.js");
