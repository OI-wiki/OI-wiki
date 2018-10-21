/*************************************************************
 *
 *  MathJax/localization/sco/MathML.js
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
MathJax.Localization.addTranslation("sco","MathML",{
        version: "2.7.5",
        isLoaded: true,
        strings: {
          BadMglyph: "Bad mglyph: %1",
          BadMglyphFont: "Bad font: %1",
          MathPlayer: "MathJax wisna able tae set up MathPlayer.\n\nGif MathPlayer isna installed, than ye need tae install it first.\nItherwise, yer securitie settins micht be preventin ActiveX\ncontrols fae rinnin. Uise the Internet Opties eetem unner\nthe Tuilkist menu n select the Securitie tab, than press the\nCustom Level button. Check that the settins fer\n'Rin ActiveX Controls', n 'Binarie n screept behaviors'\nar enabled.\n\nOan the nou ye'll see mistak messages insteid o typeset mathematics",
          CantCreateXMLParser: "MathJax canna creaut aen XML parser fer MathML. Check that\nthe 'Screept ActiveX controls maurkit safe fer screeptin' securitie\nsettin is enabled (uise the Internet Opties eetem in the Tuils menu, n select the Securitie panel, than press the Custom Level button tae check this).\n\nMathML equations will no be able tae be processed bi MathJax",
          UnknownNodeType: "Onkent node type: %1",
          UnexpectedTextNode: "Onexpected tex node: %1",
          ErrorParsingMathML: "Mistak parsin MathML",
          ParsingError: "Mistak parsin MathML: %1",
          MathMLSingleElement: "MathML maun be formed bi ae single element",
          MathMLRootElement: "MathML maun be formed bi ae \u003Cmath\u003E element, no %1"
        }
});

MathJax.Ajax.loadComplete("[MathJax]/localization/sco/MathML.js");
