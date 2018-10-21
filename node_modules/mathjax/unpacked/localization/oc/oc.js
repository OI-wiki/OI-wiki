/*************************************************************
 *
 *  MathJax/localization/oc/oc.js
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
MathJax.Localization.addTranslation("oc",null,{
  menuTitle: "occitan",
  version: "2.7.5",
  isLoaded: true,
  domains: {
    "_": {
        version: "2.7.5",
        isLoaded: true,
        strings: {
          MathProcessingError: "Error de tractament de la formula matematica",
          MathError: "Error dins la formula matematica",
          LoadFile: "Telecargament de %1",
          Loading: "Cargament",
          LoadFailed: "Frac\u00E0s del telecargament de %1",
          ProcessMath: "Tractament de las formulas : %1%%",
          Processing: "Tractament",
          TypesetMath: "Composicion de las formulas : %1%%",
          Typesetting: "Composicion",
          MathJaxNotSupported: "V\u00F2stre navigador sup\u00F2rta pas MathJax"
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

MathJax.Ajax.loadComplete("[MathJax]/localization/oc/oc.js");
