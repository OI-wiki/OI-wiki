/*************************************************************
 *
 *  MathJax/localization/nl/nl.js
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
MathJax.Localization.addTranslation("nl",null,{
  menuTitle: "Nederlands",
  version: "2.7.5",
  isLoaded: true,
  domains: {
    "_": {
        version: "2.7.5",
        isLoaded: true,
        strings: {
          CookieConfig: "MathJax heeft een gebruikersconfiguratie cookie aangetroffen dat code bevat die uitgevoerd moet worden. Wilt u deze uitvoeren?\n\\n\n(U zou op annuleren moeten drukken tenzij u het cookie zelf ingesteld heeft.)",
          MathProcessingError: "Mathverwerkingsfout",
          MathError: "Mathfout",
          LoadFile: "Bezig met laden van %1",
          Loading: "Bezig met laden",
          LoadFailed: "Het bestand kon niet geladen worden: %1",
          ProcessMath: "Berekening aan het verwerken: %1%%",
          Processing: "Bezig met verwerken",
          TypesetMath: "Berekening aan het opmaken: %1%%",
          Typesetting: "Opmaken",
          MathJaxNotSupported: "Uw browser ondersteunt MathJax niet",
          ErrorTips: "Debugtips: gebruik %%1, inspecteer %%2 in de console van de browser"
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

MathJax.Ajax.loadComplete("[MathJax]/localization/nl/nl.js");
