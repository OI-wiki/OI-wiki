/*************************************************************
 *
 *  MathJax/localization/zh-hant/zh-hant.js
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
MathJax.Localization.addTranslation("zh-hant",null,{
  menuTitle: "\u6C49\u8BED",
  version: "2.7.5",
  isLoaded: true,
  domains: {
    "_": {
        version: "2.7.5",
        isLoaded: true,
        strings: {
          MathProcessingError: "\u6578\u5B78\u8655\u7406\u932F\u8AA4",
          MathError: "\u6578\u5B78\u932F\u8AA4",
          LoadFile: "\u6B63\u5728\u8F09\u5165%1",
          Loading: "\u8F09\u5165\u4E2D\u2026",
          LoadFailed: "\u7121\u6CD5\u8F09\u5165\u6A94\u6848\uFF1A%1",
          ProcessMath: "\u8655\u7406\u6578\u5B78\uFF1A%1%%",
          Processing: "\u8655\u7406\u4E2D",
          TypesetMath: "\u6392\u7248\u6578\u5B78\uFF1A%1%%",
          Typesetting: "\u6392\u7248",
          MathJaxNotSupported: "\u60A8\u7684\u700F\u89BD\u5668\u4E0D\u652F\u63F4MathJax",
          ErrorTips: "\u9664\u932F\u63D0\u793A\uFF1A\u4F7F\u7528%%1\uFF0C\u5728\u700F\u89BD\u5668\u63A7\u5236\u53F0\u6AA2\u67E5%%2"
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
      return 1; // other
    },
  number: function (n) {
      return n;
    }
});

MathJax.Ajax.loadComplete("[MathJax]/localization/zh-hant/zh-hant.js");
