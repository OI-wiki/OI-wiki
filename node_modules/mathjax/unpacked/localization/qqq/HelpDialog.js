/*************************************************************
 *
 *  MathJax/localization/qqq/HelpDialog.js
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
MathJax.Localization.addTranslation("qqq","HelpDialog",{
        version: "2.7.5",
        isLoaded: true,
        strings: {
          Help: "This is the title displayed at the top of the MathJax Help dialog.",
          MathJax: "First paragraph of the MathJax Help dialog.\n\nStars around 'MathJax' is the Markdown syntax to put it in emphasis.",
          Browsers: "Second paragraph of the MathJax Help dialog.\n\nStars around 'Browsers' is the Markdown syntax to put it in emphasis.",
          Menu: "Third paragraph of the MathJax Help dialog.\n\nStars around 'Math Menu' the Markdown syntax to put it in emphasis.\n\n\"CTRL\" refers to \"Ctrl key\" (\"Control key\").",
          ShowMath: "First item of the the 'Math Menu' paragraph.\n\nStars around 'Show math as' is the Markdown syntax to put it in emphasis.\n\n'Show Math as' should be consistent with {{msg-mathjax|Mathmenu-Show}}.",
          Settings: "Second item of the the 'Math Menu' paragraph.\n\nStars around 'Settings' is the Markdown syntax to put it in emphasis.\n\n'Settings' should be consistent with {{msg-mathjax|Mathmenu-Settings}}.",
          Language: "Third item of the the 'Math Menu' paragraph.\n\nStars around 'Language' is the Markdown syntax to put it in emphasis.\n\n'Language' should be consistent with {{msg-mathjax|Mathmenu-Locale}}.",
          Zoom: "Fourth paragraph of the MathJax Help dialog.\n\nStars around 'Math Zoom' is the Markdown syntax to put it in emphasis.\n\n'Math Zoom' should be consistent with {{msg-mathjax|Mathmenu-ZoomTrigger}} and {{msg-mathjax|Mathmenu-ZoomFactor}}.",
          Accessibilty: "Fifth paragraph of the MathJax Help dialog.\n\nStars around 'Accessibility' is the Markdown syntax to put it in emphasis.",
          Fonts: "{{doc-markdown}}\nSixth paragraph of the MathJax Help dialog.\n\nStars around 'Fonts' is the Markdown syntax to put it in emphasis.\n\n\u003Ccode\u003E[STIX fonts](%1)\u003C/code\u003E is the Markdown syntax for links.\n\nParameters:\n* %1 - a URL the STIX fonts",
          CloseDialog: "Text alternative for the closing button of the 'MathJax Help' pop-up."
        }
});

MathJax.Ajax.loadComplete("[MathJax]/localization/qqq/HelpDialog.js");
