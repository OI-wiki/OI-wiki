/*************************************************************
 *
 *  MathJax/localization/sl/sl.js
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
MathJax.Localization.addTranslation("sl",null,{
  menuTitle: "sloven\u0161\u010Dina",
  version: "2.7.5",
  isLoaded: true,
  domains: {
    "_": {
        version: "2.7.5",
        isLoaded: true,
        strings: {
          CookieConfig: "MathJax je na\u0161el pi\u0161kotek za uporabni\u0161ko konfiguracijo, ki vklju\u010Duje kodo za zagon. Ali jo \u017Eelite zagnati?\n\n(Pritisnite Prekli\u010Di, razen \u010De ste pi\u0161kotek sami nastavili.)",
          MathProcessingError: "Napaka pri obdelavi matematike",
          MathError: "Napaka v matemati\u010Dni formuli",
          LoadFile: "Nalagam %1",
          Loading: "Nalagam",
          LoadFailed: "Datoteka se ni nalo\u017Eila: %1",
          ProcessMath: "Obdelava matematike: %1%%",
          Processing: "Obdelujem",
          TypesetMath: "Stavljenje matematike: %1%%",
          Typesetting: "Stavljenje",
          MathJaxNotSupported: "Va\u0161 brskalnik ne podpira MathJax"
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
      if (n % 100 === 1) return 1; // one
      if (n % 100 === 2) return 2; // two
      if (3 <= n % 100 && n % 100 <= 4) return 3;
      return 4; // other
    },
  number: function (n) {
      return n;
    }
});

MathJax.Ajax.loadComplete("[MathJax]/localization/sl/sl.js");
