/*************************************************************
 *
 *  MathJax/localization/sv/MathML.js
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
MathJax.Localization.addTranslation("sv","MathML",{
        version: "2.7.5",
        isLoaded: true,
        strings: {
          BadMglyph: "D\u00E5lig mglyph: %1",
          BadMglyphFont: "D\u00E5ligt typsnitt: %1",
          MathPlayer: "MathJax kunde inte st\u00E4lla in MathPlayer.\n\nOm MathPlayer inte \u00E4r installerat, m\u00E5ste du installera \nden f\u00F6rst. Annars kan det h\u00E4nda att dina \ns\u00E4kerhetsinst\u00E4llningar f\u00F6rhindrar ActiveX-kontroller \nfr\u00E5n att k\u00F6ras. Anv\u00E4nd internetinst\u00E4llningar i \nverktygsmenyn, v\u00E4lj s\u00E4kerhetspanelen, klicka sedan \nanv\u00E4ndardefinierad niv\u00E5-knappen. Kontrollera att \ninst\u00E4llningarna f\u00F6r 'K\u00F6r ActiveX-kontroller' samt \n'Bin\u00E4r och skript-beteenden' \u00E4r aktiverade.\n\nF\u00F6r n\u00E4rvarande kommer du att se flemeddelande snarare \n\u00E4n typsatt matematik",
          CantCreateXMLParser: "MathJax kunde inte skapa en XML-tolk f\u00F6r MathML. Kontrollera att \ns\u00E4kerhetsinst\u00E4llningen 'Script ActiveX X-kontroller som markerats \nsom s\u00E4kra f\u00F6r skript' \u00E4r aktiverad (anv\u00E4nd internetinst\u00E4llningar \ni verktygsmenyn, v\u00E4lj s\u00E4kerhetspanelen, klicka sedan \nanv\u00E4ndardefinierad niv\u00E5-knappen f\u00F6r att kontrollera detta).\n\nMathML-ekvationer kommer inte kunna hanteras av MathJax",
          UnknownNodeType: "Ok\u00E4nd nodtyp: %1",
          UnexpectedTextNode: "Ov\u00E4ntad textnod: %1",
          ErrorParsingMathML: "Fel vid tolkning av MathML",
          ParsingError: "Fel vid tolkning av MathML: %1",
          MathMLSingleElement: "MathML m\u00E5ste bildas av ett enskilt element",
          MathMLRootElement: "MathML m\u00E5ste bildas av ett \u003Cmath\u003E-element, inte %1"
        }
});

MathJax.Ajax.loadComplete("[MathJax]/localization/sv/MathML.js");
