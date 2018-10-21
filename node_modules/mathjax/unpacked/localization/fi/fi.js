/*************************************************************
 *
 *  MathJax/localization/fi/fi.js
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
MathJax.Localization.addTranslation("fi",null,{
  menuTitle: "suomi",
  version: "2.7.5",
  isLoaded: true,
  domains: {
    "_": {
        version: "2.7.5",
        isLoaded: true,
        strings: {
          CookieConfig: "MathJax on l\u00F6yt\u00E4nyt ev\u00E4steen, joka sis\u00E4lt\u00E4\u00E4 asetuksia ja ohjelmakoodia. Haluatko ajaa sen?\n\n(Peru, ellet ole luonut ev\u00E4stett\u00E4 itse.)",
          MathProcessingError: "Matematiikan k\u00E4sittely ep\u00E4onnistui",
          MathError: "Matematiikkavirhe",
          LoadFile: "Ladataan tiedostoa %1",
          Loading: "Ladataan",
          LoadFailed: "Tiedoston %1 lataaminen ep\u00E4onnistui",
          ProcessMath: "K\u00E4sitell\u00E4\u00E4n matematiikkaa: %1%%",
          Processing: "K\u00E4sitell\u00E4\u00E4n",
          TypesetMath: "Ladotaan matematiikkaa: %1%%",
          Typesetting: "Ladotaan",
          MathJaxNotSupported: "Selaimesi ei tue MathJaxia"
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

MathJax.Ajax.loadComplete("[MathJax]/localization/fi/fi.js");
