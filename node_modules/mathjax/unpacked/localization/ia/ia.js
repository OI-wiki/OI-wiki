/*************************************************************
 *
 *  MathJax/localization/ia/ia.js
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
MathJax.Localization.addTranslation("ia",null,{
  menuTitle: "interlingua",
  version: "2.7.5",
  isLoaded: true,
  domains: {
    "_": {
        version: "2.7.5",
        isLoaded: true,
        strings: {
          CookieConfig: "MathJax ha trovate un cookie con un configuration de usator que include codice executabile. Executar iste codice?\n\n(Preme Cancellar si vos mesme non ha installate iste cookie.)",
          MathProcessingError: "Error de tractamento de formula mathematic",
          MathError: "Error in formula",
          LoadFile: "Carga %1",
          Loading: "Cargamento",
          LoadFailed: "Cargamento del file fallite: %1",
          ProcessMath: "Tracta formulas: %1%%",
          Processing: "Tractamento",
          TypesetMath: "Compone formulas: %1%%",
          Typesetting: "Composition",
          MathJaxNotSupported: "Vostre navigator non supporta MathJax"
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

MathJax.Ajax.loadComplete("[MathJax]/localization/ia/ia.js");
