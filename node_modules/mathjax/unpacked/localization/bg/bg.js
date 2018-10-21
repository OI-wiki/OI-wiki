/*************************************************************
 *
 *  MathJax/localization/bg/bg.js
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
MathJax.Localization.addTranslation("bg",null,{
  menuTitle: " \u0431\u044A\u043B\u0433\u0430\u0440\u0441\u043A\u0438",
  version: "2.7.5",
  isLoaded: true,
  domains: {
    "_": {
        version: "2.7.5",
        isLoaded: true,
        strings: {
          MathProcessingError: "\u0413\u0440\u0435\u0448\u043A\u0430 \u043F\u0440\u0438 \u043E\u0431\u0440\u0430\u0431\u043E\u0442\u043A\u0430\u0442\u0430",
          MathError: "\u041C\u0430\u0442\u0435\u043C\u0430\u0442\u0438\u0447\u0435\u0441\u043A\u0430 \u0433\u0440\u0435\u0448\u043A\u0430",
          LoadFile: "\u0417\u0430\u0440\u0435\u0436\u0434\u0430\u043D\u0435 \u043D\u0430 %1",
          Loading: "\u0417\u0430\u0440\u0435\u0436\u0434\u0430\u043D\u0435",
          LoadFailed: "\u041D\u0435 \u043C\u043E\u0436\u0435 \u0434\u0430 \u0441\u0435 \u0437\u0430\u0440\u0435\u0434\u0438: %1",
          ProcessMath: "\u041E\u0431\u0440\u0430\u0431\u043E\u0442\u043A\u0430 \u043D\u0430 \u043A\u043E\u0434\u0430: %1%%",
          Processing: "\u041E\u0431\u0440\u0430\u0431\u043E\u0442\u043A\u0430",
          TypesetMath: "\u041E\u0444\u043E\u0440\u043C\u044F\u043D\u0435: %1%%",
          Typesetting: "\u041E\u0444\u043E\u0440\u043C\u044F\u043D\u0435",
          MathJaxNotSupported: "\u0411\u0440\u0430\u0443\u0437\u044A\u0440\u044A\u0442 \u0412\u0438 \u043D\u0435 \u043F\u043E\u0434\u0434\u044A\u0440\u0436\u0430 MathJax"
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
  number: undefined
});

MathJax.Ajax.loadComplete("[MathJax]/localization/bg/bg.js");
