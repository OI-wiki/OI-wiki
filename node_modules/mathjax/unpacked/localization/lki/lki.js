/*************************************************************
 *
 *  MathJax/localization/lki/lki.js
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
MathJax.Localization.addTranslation("lki",null,{
  menuTitle: "\u0644\u06D5\u06A9\u06CC",
  fontDirection: "rtl",
  version: "2.7.5",
  isLoaded: true,
  domains: {
    "_": {
        version: "2.7.5",
        isLoaded: true,
        strings: {
          MathProcessingError: "\u062E\u0637\u0627\u06CC \u067E\u0631\u062F\u0627\u0632\u0634 \u0631\u06CC\u0627\u0636\u06CC",
          MathError: "\u062E\u0637\u0627 \u0631\u06CC\u0627\u0636\u06CC",
          LoadFile: "\u0628\u0627\u0631\u06AF\u06CC\u0631\u06CC %1",
          Loading: "\u0628\u0627\u0631\u06AF\u06CC\u0631\u06CC",
          LoadFailed: "\u062E\u0637\u0627 \u062F\u0631 \u0628\u0627\u0631\u06AF\u06CC\u0631\u06CC \u067E\u0631\u0648\u0646\u062F\u0647: %1",
          ProcessMath: "\u067E\u0631\u062F\u0627\u0632\u0634 \u0631\u06CC\u0627\u0636\u06CC: %1\u066A",
          Processing: "\u067E\u0631\u062F\u0627\u0632\u0634",
          TypesetMath: "\u062D\u0631\u0648\u0641\u200C\u0686\u06CC\u0646\u06CC \u0631\u06CC\u0627\u0636\u06CC: %1\u066A",
          Typesetting: "\u062D\u0631\u0648\u0641\u200C\u0686\u06CC\u0646\u06CC",
          MathJaxNotSupported: "\u0645\u0631\u0648\u0631\u06AF\u0631 \u0634\u0645\u0627 \u0627\u0632 MathJax \u067E\u0634\u062A\u06CC\u0628\u0627\u0646\u06CC \u0646\u0645\u06CC\u200C\u06A9\u0646\u062F"
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

MathJax.Ajax.loadComplete("[MathJax]/localization/lki/lki.js");
