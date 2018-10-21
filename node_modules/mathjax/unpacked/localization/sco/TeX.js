/*************************************************************
 *
 *  MathJax/localization/sco/TeX.js
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
MathJax.Localization.addTranslation("sco","TeX",{
        version: "2.7.5",
        isLoaded: true,
        strings: {
          ExtraOpenMissingClose: "Eixtra apen brace or missin claise bracket",
          ExtraCloseMissingOpen: "Eixtra claise brace or missin apen bracket",
          MissingLeftExtraRight: "Missin \\left or eixtra \\right",
          MissingScript: "Missin superscreept or subscreept argument",
          ExtraLeftMissingRight: "Eixtra \\left or missin \\right",
          Misplaced: "Misplaced %1",
          MissingOpenForSub: "Missin apen bracket fer subscreept",
          MissingOpenForSup: "Missin apen bracket fer superscreept",
          AmbiguousUseOf: "Ambeeguous uise o %1",
          EnvBadEnd: "\\begin{%1} ended wi \\end{%2}",
          EnvMissingEnd: "Missin \\end{%1}",
          MissingBoxFor: "Missin kist fer %1",
          MissingCloseBrace: "Missin claise bracket",
          UndefinedControlSequence: "Ondefined control sequence %1",
          DoubleExponent: "Dooble exponent: uise brackets tae clarifie",
          DoubleSubscripts: "Dooble subscreepts: uise brackets tae clarifie",
          DoubleExponentPrime: "Prime causes dooble exponent: Uise brackets tae clarifie",
          CantUseHash1: "Ye canna uise 'macro parameter chairacter #' in maths mode",
          MisplacedMiddle: "%1 mau be wiin \\left n \\right",
          MisplacedLimits: "%1 is yinlie permited oan operaters",
          MisplacedMoveRoot: "%1 can yinlie appear wiin ae ruit",
          MultipleCommand: "Multiple %1",
          IntegerArg: "The aurgument til %1 mau be aen integer",
          NotMathMLToken: "%1 isna ae token element",
          InvalidMathMLAttr: "Onvalid MathML attreebute: %1",
          UnknownAttrForElement: "%1 isna ae recognized attribute fer %2",
          MaxMacroSub1: "MathJax mucklest macro substitution coont exceeded; is thaur ae recursive macro caw?",
          MaxMacroSub2: "MathJax mucklest substitution coont exceeded; is thaur ae recursive LaTeX environment?",
          MissingArgFor: "Missin aurgument fer %1",
          ExtraAlignTab: "Eixtra alignment tab in \\cases tex",
          BracketMustBeDimension: "Bracket aurgument til %1 maun be ae dimension",
          InvalidEnv: "Onvalid environment name '%1'",
          UnknownEnv: "Onkent environment '%1'",
          ExtraCloseLooking: "Eixtra claise bracket while luikin fer %1",
          MissingCloseBracket: "Coudna fynd claisin ']' fer aurgument til %1",
          MissingOrUnrecognizedDelim: "Missin or onrecognized delimiter fer %1",
          MissingDimOrUnits: "Missin dimension or its units fer %1",
          TokenNotFoundForCommand: "Coudna fynd %1 fer %2",
          MathNotTerminated: "Maths no terminated in tex kist",
          IllegalMacroParam: "Onlegal macro parameter reference",
          MaxBufferSize: "MathJax internal buffer size exceeded; is thaur ae recursive macro caw?",
          CommandNotAllowedInEnv: "%1 no permited in %2 environment",
          MultipleLabel: "Label '%1' multiplie defined",
          CommandAtTheBeginingOfLine: "%1 maun come at the beginnin o the line",
          IllegalAlign: "Onlegal alignment speceefied in %1",
          BadMathStyleFor: "Puir maths style fer %1",
          PositiveIntegerArg: "Argument til %1 maun be ae positeeve integer",
          ErroneousNestingEq: "Mistaken nestin o equation structures",
          MultlineRowsOneCol: "The lines wiin the %1 environment maun hae exactlie yin column",
          MultipleBBoxProperty: "%1 speceefied twice in %2",
          InvalidBBoxProperty: "'%1' disna luik like ae colour, ae paddin dimension, or ae style",
          ExtraEndMissingBegin: "Eixtra %1 or missin \\begingroup",
          GlobalNotFollowedBy: "%1 isna follaed bi \\let, \\def, or \\newcommand",
          UndefinedColorModel: "Colour model '%1' no defined",
          ModelArg1: "Colour values fer the %1 model need 3 nummers",
          InvalidDecimalNumber: "Onvalid decimal nummer",
          ModelArg2: "Colour values fer the %1 model maun be atween %2 n %3",
          InvalidNumber: "Onvalid nummer",
          NewextarrowArg1: "Foremait argument til %1 maun be ae control sequence name",
          NewextarrowArg2: "Seicont argument til %1 maun be twa integers separated bi ae comma",
          NewextarrowArg3: "Third argument til %1 maun be ae Unicode chairacter nummer",
          NoClosingChar: "Canna fynd claisin %1",
          IllegalControlSequenceName: "Onlegal control sequence name fer %1",
          IllegalParamNumber: "Onlegal nummer o parameters speceefied in %1",
          MissingCS: "%1 maun be follaeed bi ae control sequence",
          CantUseHash2: "Onlegal uiss o # in template fer %1",
          SequentialParam: "Parameters fer %1 maun be nummer't sequentiallie",
          MissingReplacementString: "Missin replacement string fer defineetion o %1",
          MismatchUseDef: "Uiss o %1 disna match its defineetion",
          RunawayArgument: "Rinawa argument fer %1?",
          NoClosingDelim: "Canna fynd claisin delimiter fer %1"
        }
});

MathJax.Ajax.loadComplete("[MathJax]/localization/sco/TeX.js");
