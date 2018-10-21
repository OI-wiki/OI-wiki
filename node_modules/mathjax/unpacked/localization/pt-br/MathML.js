/*************************************************************
 *
 *  MathJax/localization/pt-br/MathML.js
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
MathJax.Localization.addTranslation("pt-br","MathML",{
        version: "2.7.5",
        isLoaded: true,
        strings: {
          BadMglyph: "Mglyph ruim: %1",
          BadMglyphFont: "Fonte ruim: %1",
          MathPlayer: "O MathJax n\u00E3o foi capaz de configurar o MathPlayer.\n\nSe o MathPlayer n\u00E3o estiver instalado, precisar\u00E1 instal\u00E1-lo primeiro.\nCaso contr\u00E1rio, suas configura\u00E7\u00F5es de seguran\u00E7a podem estar prevenindo a execu\u00E7\u00E3o\nde controles ActiveX.  Use as Op\u00E7\u00F5es de Internet sob\no menu Ferramentas e selecione a aba de Seguran\u00E7a ent\u00E3o pressione o bot\u00E3o N\u00EDvel Personalizado. Confira se as configura\u00E7\u00F5es para 'Execu\u00E7\u00E3o de Controles ActiveX', e 'Comportamento de scripts e c\u00F3digos bin\u00E1rios'\nest\u00E3o ativadas.\n\nAtualmente voc\u00EA ver\u00E1 mensagens de erro em vez da \ndiagrama\u00E7\u00E3o das f\u00F3rmulas matem\u00E1ticas.",
          CantCreateXMLParser: "O MathJax n\u00E3o pode criar um interpretador de XML para o MathML.  Confira se\na configura\u00E7\u00E3o de seguran\u00E7a 'Controles de Script ActiveX marcados como seguros para scripting'\nest\u00E1 habilitado (use as Op\u00E7\u00F5es de Internet no menu \nFerramentas, e selecione o painel de Seguran\u00E7a, depois pressione o bot\u00E3o N\u00EDvel Personalizado\npara conferir isso).\n\nAs equa\u00E7\u00F5es em MathML n\u00E3o poder\u00E3o ser processadas pelo MathJax.",
          UnknownNodeType: "Tipo de n\u00F3 desconhecido: %1",
          UnexpectedTextNode: "N\u00F3 de texto inesperado: %1",
          ErrorParsingMathML: "Erro ao interpretar MathML",
          ParsingError: "Erro ao interpretar MathML: %1",
          MathMLSingleElement: "MathML deve ser formado por um \u00FAnico elemento",
          MathMLRootElement: "MathML deve ser formado por um elemento \u003Cmath\u003E, n\u00E3o %1"
        }
});

MathJax.Ajax.loadComplete("[MathJax]/localization/pt-br/MathML.js");
