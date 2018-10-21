/*************************************************************
 *
 *  MathJax/localization/de/FontWarnings.js
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
MathJax.Localization.addTranslation("de","FontWarnings",{
        version: "2.7.5",
        isLoaded: true,
        strings: {
          webFont: "MathJax nutz web-basierte Fonts zur Darstellung der Mathematik auf dieser Seite. Da diese heruntergeladen werden m\u00FCssen, l\u00E4dt die Seite schneller, wenn Mathe-Fonts auf dem System installiert sind.",
          imageFonts: "MathJax verwendet die Bildschriften anstatt der lokalen oder webbasierten Schriften. Das Rendern dauert l\u00E4nger als gew\u00F6hnlich und die Inhalte werden m\u00F6glicherweise nicht mit der vollen Aufl\u00F6sung deines Druckers ausgedruckt.",
          noFonts: "MathJax konnte keine Schriftart zur Anzeige der Inhalte finden und Bildschriften sind nicht verf\u00FCgbar. Es wird auf allgemeine Unicode-Zeichen zur\u00FCckgegriffen in der Hoffnung, dass dein Browser in der Lage ist, sie darzustellen. Einige Zeichen werden m\u00F6glicherweise nicht richtig oder gar nicht angezeigt.",
          webFonts: "Die meisten modernen Browser erlauben den Download von Schriften \u00FCber das Web. Eine Aktualisierung auf eine aktuellere Version deines Browsers (oder dessen Wechsel) kann die Qualit\u00E4t der Inhalte auf dieser Seite verbessern.",
          fonts: "MathJax kann entweder die [STIX-](%1) oder [MathJax-TeX-Schriften](%2) verwenden. Lade eine dieser Schriften herunter und installiere sie, um dein MathJax-Erlebnis zu steigern.",
          STIXPage: "Diese Seite wurde konzipiert, um die [STIX-Schriften](%1) zu verwenden. Lade sie herunter und installiere sie, um dein MathJax-Erlebnis zu steigern.",
          TeXPage: "Diese Seite wurde konzipiert, um die [MathJax-TeX-Schriften](%1) zu verwenden. Lade sie herunter und installiere sie, um dein MathJax-Erlebnis zu steigern."
        }
});

MathJax.Ajax.loadComplete("[MathJax]/localization/de/FontWarnings.js");
