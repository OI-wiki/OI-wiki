/*************************************************************
 *
 *  MathJax/localization/he/he.js
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
MathJax.Localization.addTranslation("he",null,{
  menuTitle: "\u05E2\u05D1\u05E8\u05D9\u05EA",
  fontDirection: "rtl",
  version: "2.7.5",
  isLoaded: true,
  domains: {
    "_": {
        version: "2.7.5",
        isLoaded: true,
        strings: {
          CookieConfig: "MathJax \u05DE\u05E6\u05D0 \u05E2\u05D5\u05D2\u05D9\u05D9\u05EA \u05D4\u05D2\u05D3\u05E8\u05D5\u05EA \u05DE\u05E9\u05EA\u05DE\u05E9 \u05E9\u05DB\u05D5\u05DC\u05DC\u05EA \u05E7\u05D5\u05D3 \u05DC\u05D4\u05E8\u05E6\u05D4. \u05D4\u05D0\u05DD \u05DC\u05D4\u05E8\u05D9\u05E5 \u05D0\u05D5\u05EA\u05D5?\n\n(\u05D9\u05E9 \u05DC\u05DC\u05D7\u05D5\u05E5 \"\u05D1\u05D9\u05D8\u05D5\u05DC\" \u05D0\u05DC\u05D0 \u05D0\u05DD \u05D4\u05D2\u05D3\u05E8\u05EA \u05D0\u05EA \u05D4\u05E2\u05D5\u05D2\u05D9\u05D9\u05D4 \u05D1\u05E2\u05E6\u05DE\u05DA.)",
          MathProcessingError: "\u05E9\u05D2\u05D9\u05D0\u05D4 \u05D1\u05E2\u05D9\u05D1\u05D5\u05D3 \u05E0\u05D5\u05E1\u05D7\u05D4",
          MathError: "\u05E9\u05D2\u05D9\u05D0\u05D4 \u05D1\u05E0\u05D5\u05E1\u05D7\u05D4",
          LoadFile: "\u05D8\u05E2\u05D9\u05E0\u05EA %1",
          Loading: "\u05D8\u05E2\u05D9\u05E0\u05D4",
          LoadFailed: "\u05D4\u05E7\u05D5\u05D1\u05E5 \u05DC\u05D0 \u05E0\u05D8\u05E2\u05DF: %1",
          ProcessMath: "\u05E2\u05D9\u05D1\u05D5\u05D3 \u05E0\u05D5\u05E1\u05D7\u05D0\u05D5\u05EA: %1%%",
          Processing: "\u05E2\u05D9\u05D1\u05D5\u05D3",
          TypesetMath: "\u05E1\u05D3\u05B7\u05E8 \u05E0\u05D5\u05E1\u05D7\u05D0\u05D5\u05EA: %1%%",
          Typesetting: "\u05E1\u05D3\u05B7\u05E8",
          MathJaxNotSupported: "\u05D4\u05D3\u05E4\u05D3\u05E4\u05DF \u05E9\u05DC\u05DA \u05D0\u05D9\u05E0\u05D5 \u05EA\u05D5\u05DE\u05DA \u05D1\u05BEMathJax",
          ErrorTips: "\u05E2\u05E6\u05D5\u05EA \u05DC\u05EA\u05D9\u05E7\u05D5\u05DF \u05E9\u05D2\u05D9\u05D0\u05D5\u05EA: \u05D4\u05E9\u05EA\u05DE\u05E9\u05D5 \u05D1\u05BE%%1, \u05D1\u05D3\u05E7\u05D5 \u05D0\u05EA %%2 \u05D1\u05DE\u05E1\u05D5\u05E3 \u05D4\u05D3\u05E4\u05D3\u05E4\u05DF"
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
      if (n === 2) {return 2} // two
      if (n !== 0 && n % 10 !== 0) {return 3} // many
      return 4; // other
    },
  number: function (n) {
      return n;
    }
});

MathJax.Ajax.loadComplete("[MathJax]/localization/he/he.js");
