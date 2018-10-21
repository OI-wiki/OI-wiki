/*************************************************************
 *
 *  MathJax/localization/lt/lt.js
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
MathJax.Localization.addTranslation("lt",null,{
  menuTitle: "lietuvi\u0173",
  version: "2.7.5",
  isLoaded: true,
  domains: {
    "_": {
        version: "2.7.5",
        isLoaded: true,
        strings: {
          MathProcessingError: "Matematikos apdorojimo klaida",
          MathError: "Matematikos klaida",
          LoadFile: "\u012Ekeliama %1",
          Loading: "\u012Ekeliama",
          LoadFailed: "Nepavyko \u012Fkelti bylos: %1",
          ProcessMath: "Apdorojama matematika: %1%%",
          Processing: "Apdorojama",
          TypesetMath: "Renkami matematikos \u017Eenklai: %1%%",
          Typesetting: "\u017Denkl\u0173 rinkimas",
          MathJaxNotSupported: "J\u016Bs\u0173 nar\u0161ykl\u0117 \u201EMathJax\u201C nenumato"
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
      if (n % 10 === 1 && n % 100 !== 11) {
        return 1;
      } else if (n % 10 >=2 && n % 10 <= 9 && (n % 100 < 10 || n % 100 >= 20)) {
        return 2;
      } else {
        return 3;
      }
    },
  number: function (n) {
      return n; // needs check
    }
});

MathJax.Ajax.loadComplete("[MathJax]/localization/lt/lt.js");
