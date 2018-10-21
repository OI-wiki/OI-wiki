/*************************************************************
 *
 *  MathJax/localization/sco/sco.js
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
MathJax.Localization.addTranslation("sco",null,{
  menuTitle: "scots",
  version: "2.7.5",
  isLoaded: true,
  domains: {
    "_": {
        version: "2.7.5",
        isLoaded: true,
        strings: {
          MathProcessingError: "Maths processin mistak",
          MathError: "Maths mistak",
          LoadFile: "Laidin %1",
          Loading: "Laidin",
          LoadFailed: "File failed tae laid: %1",
          ProcessMath: "Processin maths: %1%%",
          Processing: "Processin",
          TypesetMath: "Typesettin maths: %1%%",
          Typesetting: "Typesettin",
          MathJaxNotSupported: "Yer brouser disna support MathJax"
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
  number: function (n) {
      return n;
    }
});

MathJax.Ajax.loadComplete("[MathJax]/localization/sco/sco.js");
