/*************************************************************
 *
 *  MathJax/localization/en/TeX.js
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
MathJax.Localization.addTranslation("en","TeX",{
        version: "2.7.5",
        isLoaded: true,
        strings: {
          ExtraOpenMissingClose: "Extra open brace or missing close brace",
          ExtraCloseMissingOpen: "Extra close brace or missing open brace",
          MissingLeftExtraRight: "Missing \\left or extra \\right",
          MissingScript: "Missing superscript or subscript argument",
          ExtraLeftMissingRight: "Extra \\left or missing \\right",
          Misplaced: "Misplaced %1",
          MissingOpenForSub: "Missing open brace for subscript",
          MissingOpenForSup: "Missing open brace for superscript",
          AmbiguousUseOf: "Ambiguous use of %1",
          EnvBadEnd: "\\begin{%1} ended with \\end{%2}",
          EnvMissingEnd: "Missing \\end{%1}",
          MissingBoxFor: "Missing box for %1",
          MissingCloseBrace: "Missing close brace",
          UndefinedControlSequence: "Undefined control sequence %1",
          DoubleExponent: "Double exponent: use braces to clarify",
          DoubleSubscripts: "Double subscripts: use braces to clarify",
          DoubleExponentPrime: "Prime causes double exponent: Use braces to clarify",
          CantUseHash1: "You cannot use 'macro parameter character #' in math mode",
          MisplacedMiddle: "%1 must be within \\left and \\right",
          MisplacedLimits: "%1 is allowed only on operators",
          MisplacedMoveRoot: "%1 can appear only within a root",
          MultipleCommand: "Multiple %1",
          IntegerArg: "The argument to %1 must be an integer",
          NotMathMLToken: "%1 is not a token element",
          InvalidMathMLAttr: "Invalid MathML attribute: %1",
          UnknownAttrForElement: "%1 is not a recognized attribute for %2",
          MaxMacroSub1: "MathJax maximum macro substitution count exceeded; is there a recursive macro call?",
          MaxMacroSub2: "MathJax maximum substitution count exceeded; is there a recursive LaTeX environment?",
          MissingArgFor: "Missing argument for %1",
          ExtraAlignTab: "Extra alignment tab in \\cases text",
          BracketMustBeDimension: "Bracket argument to %1 must be a dimension",
          InvalidEnv: "Invalid environment name '%1'",
          UnknownEnv: "Unknown environment '%1'",
          ExtraCloseLooking: "Extra close brace while looking for %1",
          MissingCloseBracket: "Could not find closing ']' for argument to %1",
          MissingOrUnrecognizedDelim: "Missing or unrecognized delimiter for %1",
          MissingDimOrUnits: "Missing dimension or its units for %1",
          TokenNotFoundForCommand: "Could not find %1 for %2",
          MathNotTerminated: "Math not terminated in text box",
          IllegalMacroParam: "Illegal macro parameter reference",
          MaxBufferSize: "MathJax internal buffer size exceeded; is there a recursive macro call?",
          CommandNotAllowedInEnv: "%1 not allowed in %2 environment",
          MultipleLabel: "Label '%1' multiply defined",
          CommandAtTheBeginingOfLine: "%1 must come at the beginning of the line",
          IllegalAlign: "Illegal alignment specified in %1",
          BadMathStyleFor: "Bad math style for %1",
          PositiveIntegerArg: "Argument to %1 must be a positive integer",
          ErroneousNestingEq: "Erroneous nesting of equation structures",
          MultlineRowsOneCol: "The rows within the %1 environment must have exactly one column",
          MultipleBBoxProperty: "%1 specified twice in %2",
          InvalidBBoxProperty: "'%1' does not look like a color, a padding dimension, or a style",
          ExtraEndMissingBegin: "Extra %1 or missing \\begingroup",
          GlobalNotFollowedBy: "%1 not followed by \\let, \\def, or \\newcommand",
          UndefinedColorModel: "Color model '%1' not defined",
          ModelArg1: "Color values for the %1 model require 3 numbers",
          InvalidDecimalNumber: "Invalid decimal number",
          ModelArg2: "Color values for the %1 model must be between %2 and %3",
          InvalidNumber: "Invalid number",
          NewextarrowArg1: "First argument to %1 must be a control sequence name",
          NewextarrowArg2: "Second argument to %1 must be two integers separated by a comma",
          NewextarrowArg3: "Third argument to %1 must be a Unicode character number",
          NoClosingChar: "Cannot find closing %1",
          IllegalControlSequenceName: "Illegal control sequence name for %1",
          IllegalParamNumber: "Illegal number of parameters specified in %1",
          MissingCS: "%1 must be followed by a control sequence",
          CantUseHash2: "Illegal use of # in template for %1",
          SequentialParam: "Parameters for %1 must be numbered sequentially",
          MissingReplacementString: "Missing replacement string for definition of %1",
          MismatchUseDef: "Use of %1 does not match its definition",
          RunawayArgument: "Runaway argument for %1?",
          NoClosingDelim: "Cannot find closing delimiter for %1"
        }
});

MathJax.Ajax.loadComplete("[MathJax]/localization/en/TeX.js");
