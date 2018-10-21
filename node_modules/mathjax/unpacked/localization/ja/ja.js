/*************************************************************
 *
 *  MathJax/localization/ja/ja.js
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
MathJax.Localization.addTranslation("ja",null,{
  menuTitle: "\u65E5\u672C\u8A9E",
  version: "2.7.5",
  isLoaded: true,
  domains: {
    "_": {
        version: "2.7.5",
        isLoaded: true,
        strings: {
          CookieConfig: "MathJax \u306F\u3001\u30E6\u30FC\u30B6\u30FC\u8A2D\u5B9A\u306E Cookie \u3067\u5B9F\u884C\u3059\u3079\u304D\u30B3\u30FC\u30C9\u3092\u691C\u51FA\u3057\u307E\u3057\u305F\u3002\u5B9F\u884C\u3057\u307E\u3059\u304B?\n\n(Cookie \u3092\u81EA\u5206\u3067\u8A2D\u5B9A\u3057\u3066\u3044\u306A\u3044\u5834\u5408\u306F\u30AD\u30E3\u30F3\u30BB\u30EB\u3057\u3066\u304F\u3060\u3055\u3044\u3002)",
          MathProcessingError: "\u6570\u5F0F\u51E6\u7406\u30A8\u30E9\u30FC",
          MathError: "\u6570\u5F0F\u30A8\u30E9\u30FC",
          LoadFile: "%1 \u3092\u8AAD\u307F\u8FBC\u307F\u4E2D",
          Loading: "\u8AAD\u307F\u8FBC\u307F\u4E2D",
          LoadFailed: "\u30D5\u30A1\u30A4\u30EB\u3092\u8AAD\u307F\u8FBC\u3081\u307E\u305B\u3093\u3067\u3057\u305F: %1",
          ProcessMath: "\u6570\u5F0F\u3092\u51E6\u7406\u4E2D: %1%%",
          Processing: "\u51E6\u7406\u4E2D",
          TypesetMath: "\u6570\u5F0F\u3092\u7D44\u7248\u4E2D: %1%%",
          Typesetting: "\u7D44\u7248\u4E2D",
          MathJaxNotSupported: "\u3054\u4F7F\u7528\u4E2D\u306E\u30D6\u30E9\u30A6\u30B6\u30FC\u306F MathJax \u306B\u5BFE\u5FDC\u3057\u3066\u3044\u307E\u305B\u3093"
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

MathJax.Ajax.loadComplete("[MathJax]/localization/ja/ja.js");
