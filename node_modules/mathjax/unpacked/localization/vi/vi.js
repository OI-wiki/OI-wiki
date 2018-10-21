/*************************************************************
 *
 *  MathJax/localization/vi/vi.js
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
MathJax.Localization.addTranslation("vi",null,{
  menuTitle: "Ti\u1EBFng Vi\u1EC7t",
  version: "2.7.5",
  isLoaded: true,
  domains: {
    "_": {
        version: "2.7.5",
        isLoaded: true,
        strings: {
          CookieConfig: "MathJax \u0111\u00E3 t\u00ECm th\u1EA5y m\u1ED9t cookie thi\u1EBFt l\u1EADp c\u1EE7a ng\u01B0\u1EDDi d\u00F9ng c\u00F3 m\u00E3 ngu\u1ED3n \u0111\u1EC3 ch\u1EA1y. B\u1EA1n c\u00F3 mu\u1ED1n ch\u1EA1y n\u00F3?\n\n(Khuy\u00EAn b\u1EA1n b\u1EA5m H\u1EE7y b\u1ECF tr\u1EEB khi b\u1EA1n l\u00E0 ng\u01B0\u1EDDi thi\u1EBFt l\u1EADp cookie.)",
          MathProcessingError: "L\u1ED7i x\u1EED l\u00FD to\u00E1n",
          MathError: "L\u1ED7i to\u00E1n",
          LoadFile: "\u0110ang t\u1EA3i %1",
          Loading: "\u0110ang t\u1EA3i",
          LoadFailed: "Th\u1EA5t b\u1EA1i khi t\u1EA3i t\u1EADp tin: %1",
          ProcessMath: "\u0110ang x\u1EED l\u00FD to\u00E1n: %1%%",
          Processing: "\u0110ang x\u1EED l\u00FD",
          TypesetMath: "\u0110ang x\u1EBFp ch\u1EEF to\u00E1n: %1%%",
          Typesetting: "\u0110ang x\u1EBFp ch\u1EEF",
          MathJaxNotSupported: "Tr\u00ECnh duy\u1EC7t c\u1EE7a b\u1EA1n kh\u00F4ng h\u1ED7 tr\u1EE3 MathJax",
          ErrorTips: "M\u1EB9o v\u1EB7t g\u1EE1 l\u1ED7i: s\u1EED d\u1EE5ng %%1, ki\u1EC3m tra %%2 trong b\u1EA3ng \u0111i\u1EC1u khi\u1EC3n c\u1EE7a tr\u00ECnh duy\u1EC7t"
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
      return String(n).replace(".", ","); // replace dot by comma
    }
});

MathJax.Ajax.loadComplete("[MathJax]/localization/vi/vi.js");
