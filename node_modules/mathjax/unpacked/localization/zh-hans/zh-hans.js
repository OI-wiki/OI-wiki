/*************************************************************
 *
 *  MathJax/localization/zh-hans/zh-hans.js
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
MathJax.Localization.addTranslation("zh-hans",null,{
  menuTitle: "\u4E2D\u6587\uFF08\u7B80\u4F53\uFF09",
  version: "2.7.5",
  isLoaded: true,
  domains: {
    "_": {
        version: "2.7.5",
        isLoaded: true,
        strings: {
          CookieConfig: "MathJax\u5DF2\u627E\u5230\u7528\u6237\u914D\u7F6E\uFF0C\u5176\u4E2D\u5305\u542B\u8981\u8FD0\u884C\u4EE3\u7801\u6240\u4F9D\u8D56\u7684cookie\u3002\u60A8\u60F3\u8FD0\u884C\u5B83\u4E48\uFF1F\n\n\uFF08\u60A8\u5E94\u8BE5\u81EA\u884C\u6309\u53D6\u6D88\u9664\u975E\u60A8\u8BBE\u7F6E\u4E86\u81EA\u5DF1\u7684cookie\u3002\uFF09",
          MathProcessingError: "\u6570\u5B66\u5904\u7406\u9519\u8BEF",
          MathError: "\u6570\u5B66\u9519\u8BEF",
          LoadFile: "%1\u52A0\u8F7D\u4E2D",
          Loading: "\u52A0\u8F7D\u4E2D",
          LoadFailed: "\u65E0\u6CD5\u52A0\u8F7D\u6587\u4EF6\uFF1A%1",
          ProcessMath: "\u6570\u5B66\u5904\u7406\uFF1A%1%%",
          Processing: "\u5904\u7406\u4E2D",
          TypesetMath: "\u6392\u7248\u6570\u5B66\uFF1A%1%%",
          Typesetting: "\u6392\u7248",
          MathJaxNotSupported: "\u60A8\u7684\u6D4F\u89C8\u5668\u6682\u4E0D\u652F\u6301MathJax",
          ErrorTips: "\u8C03\u8BD5\u63D0\u793A\uFF1A\u4F7F\u7528%%1\uFF0C\u5728\u6D4F\u89C8\u5668\u63A7\u5236\u53F0\u4E2D\u68C0\u67E5%%2"
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

MathJax.Ajax.loadComplete("[MathJax]/localization/zh-hans/zh-hans.js");
