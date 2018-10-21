/*************************************************************
 *
 *  MathJax/localization/qqq/HTML-CSS.js
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
MathJax.Localization.addTranslation("qqq","HTML-CSS",{
        version: "2.7.5",
        isLoaded: true,
        strings: {
          LoadWebFont: "This is displayed in MathJax message box when the HTML-CSS output is loading a Web font.\n\nParameters:\n* %1 - the font name",
          CantLoadWebFont: "This is displayed in MathJax message box when the HTML-CSS output fails to load a Web font. The first argument is the font name",
          FirefoxCantLoadWebFont: "This is displayed in MathJax message box when the HTML-CSS output fails to load a Web font in Firefox",
          CantFindFontUsing: "This is displayed in MathJax message box when the HTML-CSS output fails to load a Web font from a given list.\n\nParameters:\n* %1 - a list of fonts tried, comma-separated",
          WebFontsNotAvailable: "This is displayed in MathJax message box when the HTML-CSS fails to load Web fonts"
        }
});

MathJax.Ajax.loadComplete("[MathJax]/localization/qqq/HTML-CSS.js");
