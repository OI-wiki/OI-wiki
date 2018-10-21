/*************************************************************
 *
 *  MathJax/localization/pl/MathML.js
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
MathJax.Localization.addTranslation("pl","MathML",{
        version: "2.7.5",
        isLoaded: true,
        strings: {
          BadMglyph: "B\u0142\u0105d w elemencie mglyph: %1",
          BadMglyphFont: "B\u0142\u0119dna czcionka: %1",
          MathPlayer: "MathJax nie m\u00F3g\u0142 uruchomi\u0107 MathPlayer.\n\nJe\u015Bli MathPlayer nie jest zainstalowany, musisz go najpierw zainstalowa\u0107.\nW przeciwnym razie, twoje ustawienia bezpiecze\u0144stwa mog\u0105 blokowa\u0107 dzia\u0142anie\nformant\u00F3w ActiveX. W Opcjach internetowych, w menu Narz\u0119dzia wybierz zak\u0142adk\u0119\nZabezpieczenia i naci\u015Bnij przycisk Poziom niestandardowy. Upewnij si\u0119, \u017Ce ustawienia\ndotycz\u0105ce ActiveX oraz skrypt\u00F3w s\u0105 w\u0142\u0105czone.\n\nDo tego czasu b\u0119d\u0105 wy\u015Bwietlane b\u0142\u0119dy zamiast wzor\u00F3w matematycznych.",
          CantCreateXMLParser: "MathJax nie mo\u017Ce utworzy\u0107 parsera XML dla MathML. Upewnij si\u0119, \u017Ce\nopcja 'Wykonywanie skrypt\u00F3w formant\u00F3w ActiveX' jest w\u0142\u0105czona\n(sprawd\u017A to w Opcjach internetowych w menu Narz\u0119dzia,\nw zak\u0142adce Zabezpieczenia kliknij na przycisk Poziom niestandardowy).\n\nDo tego czasu b\u0119d\u0105 wy\u015Bwietlane b\u0142\u0119dy zamiast wzor\u00F3w matematycznych.",
          UnknownNodeType: "Nieznany typ elementu: %1",
          UnexpectedTextNode: "Nieoczekiwany element tekstowy: %1",
          ErrorParsingMathML: "B\u0142\u0105d podczas przetwarzania MathML",
          ParsingError: "B\u0142\u0105d podczas przetwarzania MathML: %1",
          MathMLSingleElement: "MathML musi by\u0107 zamkni\u0119ty w pojedynczym elemencie",
          MathMLRootElement: "MathML musi by\u0107 zamkni\u0119ty w elemencie \u003Cmath\u003E, a nie %1"
        }
});

MathJax.Ajax.loadComplete("[MathJax]/localization/pl/MathML.js");
