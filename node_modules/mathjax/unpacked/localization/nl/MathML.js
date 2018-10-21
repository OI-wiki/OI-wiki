/*************************************************************
 *
 *  MathJax/localization/nl/MathML.js
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
MathJax.Localization.addTranslation("nl","MathML",{
        version: "2.7.5",
        isLoaded: true,
        strings: {
          BadMglyph: "Onjuiste mglyph: %1",
          BadMglyphFont: "Verkeerd lettertype: %1",
          MathPlayer: "MathJax was niet in staat MathPlayer in te stellen.\n\nAls MathPlay niet ge\u00EFnstalleerd is, doe dat dan eerst.\nAnders kan het zijn dat beveiligingsinstellingen de uitvoering van ActiveX-besturingselementen verhinderen. Gebruik de keuze Internet Opties in het menu Extra en selecteer het tabblad Beveiligingsinstellingen en druk op de knop Aangepaste niveau.\nControleer dat de instellingen voor \"Uitvoeren van ActiveX-besturingselementen\" en \"Gedrag van binaire elementen en scripts\" ingeschakeld zijn.\n\nMomenteel zie u foutmeldingen in plaats van opgemaakte wiskunde.",
          CantCreateXMLParser: "MathJax kan geen XML-verwerker cre\u00EBren voor MathML. Controleer of de beveiligingsinstelling \"ActiveX-besturingselementen die zijn gemarkeerd als veilig voor uitvoeren in scripts\" is ingeschakeld. Gebruik de keuze Internet Opties in het menu Extra en selecteer het paneel Beveiliging, druk dan op de knop Aangepast niveau om dit te controleren.\n\nMathML-vergelijkingen kunnen niet verwerkt worden door MathJax.",
          UnknownNodeType: "Onbekend knooptype: %1",
          UnexpectedTextNode: "Onverwachte tekstknoop: %1",
          ErrorParsingMathML: "Fout tijdens verwerken MathML",
          ParsingError: "Fout tijdens verwerken MathML: %1",
          MathMLSingleElement: "MathML moet bestaan uit \u00E9\u00E9n element",
          MathMLRootElement: "MathML moet bestaan uit een \u003Cmath\u003E element, niet %1"
        }
});

MathJax.Ajax.loadComplete("[MathJax]/localization/nl/MathML.js");
