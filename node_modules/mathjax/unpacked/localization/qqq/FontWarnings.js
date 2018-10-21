/*************************************************************
 *
 *  MathJax/localization/qqq/FontWarnings.js
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
MathJax.Localization.addTranslation("qqq","FontWarnings",{
        version: "2.7.5",
        isLoaded: true,
        strings: {
          webFont: "This warning is displayed by the FontWarnings extension when web-based fonts are used.",
          imageFonts: "This warning is displayed by the FontWarnings extension when image fonts are used.",
          noFonts: "This warning is displayed by the FontWarnings extension when no fonts can be used.",
          webFonts: "This warning is displayed by the FontWarnings extension when the browser do not support web fonts",
          fonts: "{{doc-markdown}}\nThis warning is displayed by the FontWarnings extension when the HTML-CSS availableFonts list contains both STIX and TeX.\n\nParameters:\n* %1 - URL\n* %2 - URL\nSee also:\n* {{msg-mathjax|Fontwarnings-TeXPage}}",
          STIXPage: "{{doc-markdown}}\nThis warning is displayed by the FontWarnings extension when the HTML-CSS availableFonts list contains only STIX.\n\nParameters:\n* %1 - URL",
          TeXPage: "{{doc-markdown}}\nThis warning is displayed by the FontWarnings extension when the HTML-CSS availableFonts list contains only TeX.\n\nParameters:\n* %1 - URL\nSee also:\n* {{msg-mathjax|Fontwarnings-fonts}}"
        }
});

MathJax.Ajax.loadComplete("[MathJax]/localization/qqq/FontWarnings.js");
