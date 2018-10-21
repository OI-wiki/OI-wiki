/*************************************************************
 *
 *  MathJax/localization/cs/MathML.js
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
MathJax.Localization.addTranslation("cs","MathML",{
        version: "2.7.5",
        isLoaded: true,
        strings: {
          BadMglyph: "Chybn\u00FD mglyph: %1",
          BadMglyphFont: "\u0160patn\u00E9 p\u00EDsmo: %1",
          MathPlayer: "MathJax nedok\u00E1zal spustit MathPlayer.\n\nPokud nen\u00ED MathPlayer nainstalov\u00E1n, budete ho muset nejprve nainstalovat.\nJinak mo\u017En\u00E1 spu\u0161t\u011Bn\u00ED ovl\u00E1dac\u00EDch prvk\u016F ActiveX br\u00E1n\u00ED va\u0161e bezpe\u010Dnostn\u00ED\nnastaven\u00ED. Klikn\u011Bte v nab\u00EDdce N\u00E1stroje na polo\u017Eku Mo\u017Enosti Internetu,\nvyberte z\u00E1lo\u017Eku Zabezpe\u010Den\u00ED a klikn\u011Bte na tla\u010D\u00EDtko Vlastn\u00ED \u00FArove\u0148.\nZkontrolujte, \u017Ee jsou povolen\u00E9 mo\u017Enosti \u201ESpou\u0161t\u011Bt ovl\u00E1dac\u00ED prvky ActiveX\u201C\na \u201EChov\u00E1n\u00ED skript\u016F a bin\u00E1rn\u00EDch soubor\u016F\u201C.\n\nMoment\u00E1ln\u011B uvid\u00EDte m\u00EDsto vys\u00E1zen\u00E9 matematiky chybov\u00E1 hl\u00E1\u0161en\u00ED.",
          CantCreateXMLParser: "MathJax nem\u016F\u017Ee vytvo\u0159it syntaktick\u00FD analyz\u00E1tor XML pro MathML.\nZkontrolujte,\u017Ee m\u00E1te povolen\u00E9 nastaven\u00ED \u201ESkriptovat ovl\u00E1dac\u00ED\nprvky ActiveX ozna\u010Den\u00E9 jako bezpe\u010Dn\u00E9\u201C (v nab\u00EDdce N\u00E1stroje\nklikn\u011Bte na polo\u017Eku Mo\u017Enosti Internetu, vyberte z\u00E1lo\u017Eku\nZabezpe\u010Den\u00ED a klikn\u011Bte na tla\u010D\u00EDtko Vlastn\u00ED \u00FArove\u0148).\n\nMathJax nebude moci zpracov\u00E1vat rovnice v MathML",
          UnknownNodeType: "Nezn\u00E1m\u00FD typ uzlu: %1",
          UnexpectedTextNode: "Neo\u010Dek\u00E1van\u00FD textov\u00FD uzel: %1",
          ErrorParsingMathML: "Chyba p\u0159i anal\u00FDze MathML",
          ParsingError: "Chyba p\u0159i anal\u00FDze MathML: %1",
          MathMLSingleElement: "MathML mus\u00ED b\u00FDt tvo\u0159eno jedin\u00FDm elementem",
          MathMLRootElement: "MathML mus\u00ED b\u00FDt tvo\u0159eno elementem \u003Cmath\u003E, nikoli %1"
        }
});

MathJax.Ajax.loadComplete("[MathJax]/localization/cs/MathML.js");
