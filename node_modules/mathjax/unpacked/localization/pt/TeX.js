/*************************************************************
 *
 *  MathJax/localization/pt/TeX.js
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
MathJax.Localization.addTranslation("pt","TeX",{
        version: "2.7.5",
        isLoaded: true,
        strings: {
          ExtraOpenMissingClose: "Chaveta de abertura a mais ou chaveta de fecho a menos",
          ExtraCloseMissingOpen: "Chaveta de fecho a mais ou chaveta de abertura a menos",
          MissingLeftExtraRight: "Falta um \\left ou h\u00E1 um \\right a mais",
          MissingScript: "Falta o valor de um sobrescrito ou de um subscrito",
          ExtraLeftMissingRight: "Falta um \\right ou h\u00E1 um \\left a mais",
          Misplaced: "%1 fora do lugar",
          MissingOpenForSub: "Falta a chaveta de abertura para o subscrito",
          MissingOpenForSup: "Falta a chaveta de abertura para o sobrescrito",
          AmbiguousUseOf: "Uso amb\u00EDguo de %1",
          EnvBadEnd: "\\begin{%1} foi terminado com \\end{%2}",
          EnvMissingEnd: "\\end{%1} em falta",
          MissingBoxFor: "Falta uma caixa para %1",
          MissingCloseBrace: "Falta chaveta de fecho",
          UndefinedControlSequence: "Sequ\u00EAncia de controlo indefinida %1",
          DoubleExponent: "Expoente duplo: use chavetas para clarificar",
          DoubleSubscripts: "Subscrito duplo: use chavetas para clarificar",
          DoubleExponentPrime: "\u00C9 amb\u00EDguo a que diz respeito a plica (\u2032): use chavetas para clarificar",
          CantUseHash1: "N\u00E3o pode usar o car\u00E1cter # que indica um par\u00E2metro de macro no modo matem\u00E1tico",
          MisplacedMiddle: "%1 deve estar entre \\left e \\right",
          MisplacedLimits: "%1 s\u00F3 \u00E9 permitido em operadores",
          MisplacedMoveRoot: "%1 s\u00F3 pode ser usado dentro de uma raiz",
          MultipleCommand: "Repeti\u00E7\u00E3o de %1",
          IntegerArg: "O argumento de %1 deve ser um inteiro",
          NotMathMLToken: "%1 n\u00E3o \u00E9 um elemento de chave",
          InvalidMathMLAttr: "Atributo MathML inv\u00E1lido: %1",
          UnknownAttrForElement: "%1 n\u00E3o \u00E9 um atributo reconhecido para %2",
          MaxMacroSub1: "Foi excedido o m\u00E1ximo de substitui\u00E7\u00F5es de macros do MathJax; h\u00E1 alguma chamada a uma macro recursiva?",
          MaxMacroSub2: "Foi excedido o m\u00E1ximo de substitui\u00E7\u00F5es do MathJax; h\u00E1 algum ambiente LaTeX recursivo?",
          MissingArgFor: "Falta um argumento para %1",
          ExtraAlignTab: "H\u00E1 um tab de alinhamento a mais no texto de \\cases",
          BracketMustBeDimension: "O argumento nos par\u00EAnteses retos de %1 deve ser uma dimens\u00E3o",
          InvalidEnv: "Nome de ambiente inv\u00E1lido: '%1'",
          UnknownEnv: "Ambiente desconhecido: '%1'",
          ExtraCloseLooking: "Encontrada uma chaveta de fecho ao procurar por %1",
          MissingCloseBracket: "N\u00E3o foi encontrado um ']' de fecho para o argumento de %1",
          MissingOrUnrecognizedDelim: "O delimitador para %1 est\u00E1 em falta ou n\u00E3o foi reconhecido",
          MissingDimOrUnits: "Falta a dimens\u00E3o ou a unidade de %1",
          TokenNotFoundForCommand: "N\u00E3o foi encontrado %1 para %2",
          MathNotTerminated: "A f\u00F3rmula n\u00E3o foi terminada na caixa de texto",
          IllegalMacroParam: "Refer\u00EAncia inv\u00E1lida a um par\u00E2metro de macro",
          MaxBufferSize: "O tamanho do buffer interno do MathJax foi excedido; h\u00E1 alguma chamada a uma macro recursiva?",
          CommandNotAllowedInEnv: "%1 n\u00E3o \u00E9 permitido no ambiente %2",
          MultipleLabel: "O r\u00F3tulo '%1' foi definido mais que uma vez",
          CommandAtTheBeginingOfLine: "%1 deve vir no in\u00EDcio da linha",
          IllegalAlign: "Foi especificado um alinhamento ilegal em %1",
          BadMathStyleFor: "Estilo de f\u00F3rmula inv\u00E1lido para %1",
          PositiveIntegerArg: "O argumento para %1 deve ser um inteiro positivo",
          ErroneousNestingEq: "Aninhamento incorreto de estruturas de equa\u00E7\u00F5es",
          MultlineRowsOneCol: "As linhas do ambiente %1 devem ter apenas uma coluna",
          MultipleBBoxProperty: "%1 foi especificado duas vezes em %2",
          InvalidBBoxProperty: "'%1' n\u00E3o parece ser uma cor, uma dimens\u00E3o de espa\u00E7amento, nem um estilo",
          ExtraEndMissingBegin: "H\u00E1 um %1 a mais ou um \\begingroup a menos",
          GlobalNotFollowedBy: "%1 n\u00E3o foi seguido por um \\let, \\def, ou \\newcommand",
          UndefinedColorModel: "O modelo de cores '%1' n\u00E3o foi definido",
          ModelArg1: "O modelo %1 requer 3 n\u00FAmeros para valores de cor",
          InvalidDecimalNumber: "N\u00FAmero decimal inv\u00E1lido",
          ModelArg2: "Os valores de cor para o modelo %1 devem estar entre %2 e %3",
          InvalidNumber: "N\u00FAmero inv\u00E1lido",
          NewextarrowArg1: "O primeiro argumento de %1 deve ser o nome de uma sequ\u00EAncia de controlo",
          NewextarrowArg2: "O segundo argumento de %1 deve ser composto por dois inteiros separados por uma v\u00EDrgula",
          NewextarrowArg3: "O terceiro argumento de %1 deve ser o c\u00F3digo Unicode de um caractere",
          NoClosingChar: "N\u00E3o foi poss\u00EDvel encontrar um %1 de fecho",
          IllegalControlSequenceName: "O nome da sequ\u00EAncia de controlo para %1 \u00E9 inv\u00E1lido",
          IllegalParamNumber: "N\u00FAmero inv\u00E1lido de par\u00E2metros especificado em %1",
          MissingCS: "%1 deve ser seguido por uma sequ\u00EAncia de controlo",
          CantUseHash2: "Uso ilegal de # em modelo para %1",
          SequentialParam: "Os par\u00E2metros para %1 devem ser numerados sequencialmente",
          MissingReplacementString: "Falta a string de substitui\u00E7\u00E3o para a defini\u00E7\u00E3o de %1",
          MismatchUseDef: "O uso de %1 n\u00E3o condiz com sua defini\u00E7\u00E3o",
          RunawayArgument: "Argumento em excesso para %1?",
          NoClosingDelim: "N\u00E3o foi encontrado um delimitador de fecho para %1"
        }
});

MathJax.Ajax.loadComplete("[MathJax]/localization/pt/TeX.js");
