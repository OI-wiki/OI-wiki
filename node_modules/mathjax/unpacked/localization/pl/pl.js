/*************************************************************
 *
 *  MathJax/localization/pl/pl.js
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
MathJax.Localization.addTranslation("pl",null,{
  menuTitle: "polski",
  version: "2.7.5",
  isLoaded: true,
  domains: {
    "_": {
        version: "2.7.5",
        isLoaded: true,
        strings: {
          CookieConfig: "MathJax znalaz\u0142 konfiguracj\u0119 zapisan\u0105 w ciasteczku, kt\u00F3ra zawiera kod do uruchomienia. Czy chcesz go uruchomi\u0107?\n\n(Powiniene\u015B nacisn\u0105\u0107 Anuluj, je\u015Bli to nie Ty stworzy\u0142e\u015B t\u0119 konfiguracj\u0119.)",
          MathProcessingError: "B\u0142\u0105d podczas przetwarzania wzor\u00F3w matematycznych",
          MathError: "B\u0142\u0105d we wzorze matematycznym",
          LoadFile: "\u0141aduj\u0119 %1",
          Loading: "\u0141aduj\u0119",
          LoadFailed: "Nie uda\u0142o si\u0119 za\u0142adowa\u0107 pliku: %1",
          ProcessMath: "Przetwarzam wzory matematyczne: %1%%",
          Processing: "Przetwarzam",
          TypesetMath: "Przetwarzam wzory matematyczne: %1%%",
          Typesetting: "Przetwarzam",
          MathJaxNotSupported: "Twoja przegl\u0105darka nie obs\u0142uguje MathJax",
          ErrorTips: "Porady debugowania: u\u017Cyj %%1, sprawd\u017A %%2 w konsoli przegl\u0105darki."
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
      if (n == 1) {
        return 1;
      } else if (n % 10 >=2 && n % 10 <= 4 && (n % 100 < 10 || n % 100 >= 20)) {
        return 2;
      } else {
        return 3;
      }
    },
  number: function (n) {
      return String(n).replace(".", ","); // replace dot by comma
    }
});

MathJax.Ajax.loadComplete("[MathJax]/localization/pl/pl.js");
