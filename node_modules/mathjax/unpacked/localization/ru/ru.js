/*************************************************************
 *
 *  MathJax/localization/ru/ru.js
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
MathJax.Localization.addTranslation("ru",null,{
  menuTitle: "\u0440\u0443\u0441\u0441\u043A\u0438\u0439",
  version: "2.7.5",
  isLoaded: true,
  domains: {
    "_": {
        version: "2.7.5",
        isLoaded: true,
        strings: {
          CookieConfig: "MathJax \u043D\u0430\u0448\u043B\u0430 \u043A\u0443\u043A\u0438 \u043F\u043E\u043B\u044C\u0437\u043E\u0432\u0430\u0442\u0435\u043B\u044C\u0441\u043A\u043E\u0439 \u043D\u0430\u0441\u0442\u0440\u043E\u0439\u043A\u0438, \u043A\u043E\u0442\u043E\u0440\u0430\u044F \u0441\u043E\u0434\u0435\u0440\u0436\u0438\u0442 \u043A\u043E\u0434 \u0434\u043B\u044F \u0437\u0430\u043F\u0443\u0441\u043A\u0430. \u0412\u044B \u0445\u043E\u0442\u0438\u0442\u0435 \u0437\u0430\u043F\u0443\u0441\u0442\u0438\u0442\u044C \u0435\u0433\u043E?\n\n(\u0412\u044B \u0434\u043E\u043B\u0436\u043D\u044B \u043D\u0430\u0436\u0430\u0442\u044C \u041E\u0442\u043C\u0435\u043D\u0430, \u0435\u0441\u043B\u0438 \u0432\u044B \u0441\u0430\u043C\u043E\u0441\u0442\u043E\u044F\u0442\u0435\u043B\u044C\u043D\u043E \u043D\u0430\u0441\u0442\u0440\u043E\u0438\u043B\u0438 \u0444\u0430\u0439\u043B \u043A\u0443\u043A\u0438).",
          MathProcessingError: "\u041E\u0448\u0438\u0431\u043A\u0430 \u043C\u0430\u0442\u0435\u043C\u0430\u0442\u0438\u0447\u0435\u0441\u043A\u043E\u0439 \u043E\u0431\u0440\u0430\u0431\u043E\u0442\u043A\u0438",
          MathError: "\u041C\u0430\u0442\u0435\u043C\u0430\u0442\u0438\u0447\u0435\u0441\u043A\u0430\u044F \u043E\u0448\u0438\u0431\u043A\u0430",
          LoadFile: "\u0417\u0430\u0433\u0440\u0443\u0437\u043A\u0430 %1",
          Loading: "\u0417\u0430\u0433\u0440\u0443\u0437\u043A\u0430",
          LoadFailed: "\u041D\u0435 \u0443\u0434\u0430\u043B\u043E\u0441\u044C \u0437\u0430\u0433\u0440\u0443\u0437\u0438\u0442\u044C: %1",
          ProcessMath: "\u041E\u0431\u0440\u0430\u0431\u043E\u0442\u043A\u0430 \u043C\u0430\u0442\u0435\u043C\u0430\u0442\u0438\u043A\u0438: %1%%",
          Processing: "\u041E\u0431\u0440\u0430\u0431\u043E\u0442\u043A\u0430",
          TypesetMath: "\u0412\u0451\u0440\u0441\u0442\u043A\u0430 \u043C\u0430\u0442\u0435\u043C\u0430\u0442\u0438\u043A\u0438: %1%%",
          Typesetting: "\u0412\u0451\u0440\u0441\u0442\u043A\u0430",
          MathJaxNotSupported: "\u0412\u0430\u0448 \u0431\u0440\u0430\u0443\u0437\u0435\u0440 \u043D\u0435 \u043F\u043E\u0434\u0434\u0435\u0440\u0436\u0438\u0432\u0430\u0435\u0442 MathJax",
          ErrorTips: "\u0421\u043E\u0432\u0435\u0442\u044B \u043F\u043E \u043E\u0442\u043B\u0430\u0434\u043A\u0435: \u0438\u0441\u043F\u043E\u043B\u044C\u0437\u0443\u0439\u0442\u0435 %%1, \u0438\u0437\u0443\u0447\u0438\u0442\u0435 %%2 \u0432 \u043A\u043E\u043D\u0441\u043E\u043B\u0438 \u0431\u0440\u0430\u0443\u0437\u0435\u0440\u0430"
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

MathJax.Ajax.loadComplete("[MathJax]/localization/ru/ru.js");
