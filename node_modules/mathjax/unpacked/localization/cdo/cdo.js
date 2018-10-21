/*************************************************************
 *
 *  MathJax/localization/cdo/cdo.js
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
MathJax.Localization.addTranslation("cdo",null,{
  menuTitle: "M\u00ECng-d\u0115\u0324ng-ng\u1E73\u0304",
  version: "2.7.5",
  isLoaded: true,
  domains: {
    "_": {
        version: "2.7.5",
        isLoaded: true,
        strings: {
          CookieConfig: "MathJax\u5DF2\u7D93\u8A0E\u8457\u5305\u62EC\u6703\u904B\u884C\u5176\u4EE3\u78BC\u5176\u7528\u6236\u914D\u7F6Ecookie\u3002\u6C5D\u6709\u60F3\u904B\u884C\u7121\uFF1F\n\n\uFF08\u9664\u958B\u9019\u78BA\u5BE6\u662F\u6C5D\u81EA\u5BB6\u7279\u610F\u8A2D\u5176cookie\uFF0C\u82E5\u7121\u6C5D\u8457\u9EDE\u53D6\u6D88\u3002\uFF09",
          MathProcessingError: "\u6578\u5B78\u8655\u7406\u932F\u8AA4",
          MathError: "\u6578\u5B78\u932F\u8AA4",
          LoadFile: "\u8F09\u5165%1",
          Loading: "\u8F09\u5165",
          LoadFailed: "\u6587\u4EF6\u8F09\u5165\u5931\u6557\uFF1A%1",
          ProcessMath: "\u8655\u7406\u6578\u5B78\uFF1A%1%%",
          Processing: "\u6546\uD844\uDD4F\u8655\u7406",
          TypesetMath: "\u6392\u7248\u6578\u5B78\uFF1A%1%%",
          Typesetting: "\u6546\uD844\uDD4F\u6392\u7248",
          MathJaxNotSupported: "\u6C5D\u5176\u700F\u89BD\u5668\uD84C\uDF50\u652F\u6301MathJax"
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

MathJax.Ajax.loadComplete("[MathJax]/localization/cdo/cdo.js");
