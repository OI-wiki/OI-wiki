/*************************************************************
 *
 *  MathJax/localization/da/da.js
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
MathJax.Localization.addTranslation("da",null,{
  menuTitle: "dansk",
  version: "2.7.5",
  isLoaded: true,
  domains: {
    "_": {
        version: "2.7.5",
        isLoaded: true,
        strings: {
          CookieConfig: "MathJax har fundet en cookie med brugerkonfiguration, der indeholder kode til at k\u00F8re. Vil du k\u00F8re det?\n\n(Du b\u00F8r trykke p\u00E5 Annuller, medmindre du oprettede cookien selv.)",
          MathProcessingError: "Fejl under bearbejdning af matematik",
          MathError: "Matematikfejl",
          LoadFile: "Indl\u00E6ser %1",
          Loading: "Indl\u00E6ser",
          LoadFailed: "Kunne ikke indl\u00E6se filen: %1",
          ProcessMath: "Bearbejder matematik: %1%%",
          Processing: "Bearbejder",
          TypesetMath: "Ops\u00E6tter matematik: %1%%",
          Typesetting: "Ops\u00E6tter",
          MathJaxNotSupported: "Din browser underst\u00F8tter ikke MathJax",
          ErrorTips: "Tips til fejls\u00F8gning: brug %%1, inspicer %%2 i browserkonsollen"
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

MathJax.Ajax.loadComplete("[MathJax]/localization/da/da.js");
