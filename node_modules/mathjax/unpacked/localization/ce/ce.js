/*************************************************************
 *
 *  MathJax/localization/ce/ce.js
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
MathJax.Localization.addTranslation("ce",null,{
  menuTitle: "\u041D\u043E\u0445\u0447\u0438\u0439\u043D \u043C\u043E\u0442\u0442",
  version: "2.7.5",
  isLoaded: true,
  domains: {
    "_": {
        version: "2.7.5",
        isLoaded: true,
        strings: {
          MathProcessingError: "\u041C\u0430\u0442\u0435\u043C\u0430\u0442\u0438\u043A\u0438\u043D \u043A\u0435\u0447\u0434\u0430\u0440\u0430\u043D \u0433\u04C0\u0430\u043B\u0430\u0442",
          MathError: "\u041C\u0430\u0442\u0435\u043C\u0430\u0442\u0438\u043A\u0438\u043D \u0433\u04C0\u0430\u043B\u0430\u0442",
          LoadFile: "\u0427\u0443\u0439\u043E\u043B\u0443\u0448 %1",
          Loading: "\u0427\u0443\u0439\u043E\u043B\u0443\u0448",
          LoadFailed: "\u0427\u0443\u044F\u043A\u043A\u0445\u0430 \u0446\u0430\u0435\u043B\u0438\u0440\u0430: %1",
          ProcessMath: "\u041C\u0430\u0442\u0435\u043C\u0430\u0442\u0438\u043A\u0430 \u043A\u0435\u0447\u044F\u0440: %1%%",
          Processing: "\u041A\u0435\u0447\u0434\u0430\u0440"
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
      if (n % 10 === 1 && n % 100 !== 11) return 1; // one
      if (2 <= n % 10 && n % 10 <= 4 && 12 <= n % 100 && n % 100 <= 14) return 2; // few
      if (n % 10 === 0 || (5 <= n % 10 && n % 10 <= 9) ||
          (11 <= n % 100 && n % 100 <= 14)) return 2; // many
      return 3; // other
    },
  number: function (n) {
      return n;
    }
});

MathJax.Ajax.loadComplete("[MathJax]/localization/ce/ce.js");
