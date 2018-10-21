/*************************************************************
 *
 *  MathJax/localization/fr/MathML.js
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
MathJax.Localization.addTranslation("fr","MathML",{
        version: "2.7.5",
        isLoaded: true,
        strings: {
          BadMglyph: "\u00C9lement mglyph incorrect: %1",
          BadMglyphFont: "Police non valide : %1",
          MathPlayer: "MathJax n\u2019a pas pu configurer MathPlayer.\n\nSi MathPlayer n\u2019est pas install\u00E9, vous devez d\u2019abord le faire.\nSinon, il se peut que vos param\u00E8tres de s\u00E9curit\u00E9 emp\u00EAchent l\u2019ex\u00E9cution des contr\u00F4les ActiveX. Utilisez l\u2019entr\u00E9e Options Internet sous le menu Outils et s\u00E9lectionnez l\u2019onglet S\u00E9curit\u00E9, puis cliquez le bouton \u00AB Personnaliser le niveau \u00BB. V\u00E9rifiez que les param\u00E8tres pour 'Ex\u00E9cuter les contr\u00F4les ActiveX', et 'Comportement de fichiers binaires et des scripts' sont activ\u00E9s.\n\nPour le moment, vous verrez des messages d\u2019erreur au lieu de textes math\u00E9matiques.",
          CantCreateXMLParser: "MathJax ne peut pas cr\u00E9er un analyseur XML pour MathML. V\u00E9rifiez que l\u2019option de s\u00E9curit\u00E9 'Contr\u00F4les ActiveX reconnus s\u00FBrs pour l\u2019\u00E9criture de scripts' est activ\u00E9e (utilisez l\u2019entr\u00E9e Options Internet dans le menu Outils, et s\u00E9lectionnez l\u2019onglet S\u00E9curit\u00E9, puis appuyez sur le bouton Personnaliser le niveau, pour le v\u00E9rifier).",
          UnknownNodeType: "Type de n\u0153ud inconnu : %1",
          UnexpectedTextNode: "N\u0153ud de texte inattendu : %1",
          ErrorParsingMathML: "Erreur lors de l\u2019analyse de MathML",
          ParsingError: "Erreur d\u2019analyse de MathML : %1",
          MathMLSingleElement: "MathML doit \u00EAtre form\u00E9 d\u2019un unique \u00E9l\u00E9ment",
          MathMLRootElement: "MathML doit \u00EAtre form\u00E9 d\u2019un \u00E9l\u00E9ment \u003Cmath\u003E, et pas %1"
        }
});

MathJax.Ajax.loadComplete("[MathJax]/localization/fr/MathML.js");
