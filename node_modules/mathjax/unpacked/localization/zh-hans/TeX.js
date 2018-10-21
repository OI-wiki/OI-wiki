/*************************************************************
 *
 *  MathJax/localization/zh-hans/TeX.js
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
MathJax.Localization.addTranslation("zh-hans","TeX",{
        version: "2.7.5",
        isLoaded: true,
        strings: {
          ExtraOpenMissingClose: "\u6709\u591A\u4F59\u7684\u5DE6\u62EC\u53F7\u6216\u7F3A\u5C11\u53F3\u62EC\u53F7",
          ExtraCloseMissingOpen: "\u6709\u591A\u4F59\u7684\u53F3\u62EC\u53F7\u6216\u7F3A\u5C11\u5DE6\u62EC\u53F7",
          MissingLeftExtraRight: "\u4E22\u5931\\left\u6216\u989D\u5916\u51FA\u73B0\\right",
          MissingScript: "\u6709\u4E0A\u6807\u6216\u4E0B\u6807\u7F3A\u5C11\u53C2\u6570",
          ExtraLeftMissingRight: "\u989D\u5916\u7684\\left\u6216\u8005\u4E22\u5931\\right",
          Misplaced: "%1\u88AB\u653E\u7F6E\u4E8E\u9519\u8BEF\u7684\u5730\u65B9",
          MissingOpenForSub: "\u7F3A\u5C11\u4E0B\u6807\u7684\u5DE6\u62EC\u53F7",
          MissingOpenForSup: "\u7F3A\u5C11\u4E0A\u6807\u7684\u5DE6\u62EC\u53F7",
          AmbiguousUseOf: "%1\u7684\u4F7F\u7528\u4E0D\u660E\u786E",
          EnvBadEnd: "\\begin{%1}\u7531\\end{%2}\u7ED3\u675F\u4E4B",
          EnvMissingEnd: "\\end{%1}\u4E22\u5931",
          MissingBoxFor: "\u7F3A\u5C11\u7528\u4E8E%1\u7684\u6846",
          MissingCloseBrace: "\u7F3A\u5C11\u53F3\u62EC\u53F7",
          UndefinedControlSequence: "\u672A\u5B9A\u4E49\u7684\u63A7\u5236\u6570\u5217%1",
          DoubleExponent: "\u4E24\u4E2A\u6307\u6570\uFF1A\u4F7F\u7528\u5927\u62EC\u53F7\u6765\u6F84\u6E05",
          DoubleSubscripts: "\u53CC\u4E0B\u6807\uFF1A\u4F7F\u7528\u62EC\u53F7\u6765\u660E\u786E",
          CantUseHash1: "\u60A8\u4E0D\u80FD\u5728\u6570\u5B66\u6A21\u5F0F\u4E2D\u4F7F\u7528\u201C\u5B8F\u53C2\u6570\u5B57\u7B26#\u201D",
          MisplacedMiddle: "%1\u5FC5\u987B\u5728\\left\u548C\\right\u4E4B\u5185",
          MisplacedLimits: "%1\u53EA\u5141\u8BB8\u5728\u8FD0\u7B97\u7B26\u4E0A",
          MisplacedMoveRoot: "%1\u53EA\u80FD\u5728\u6839\u4E2D\u51FA\u73B0",
          MultipleCommand: "\u591A\u79CD%1",
          IntegerArg: "\u53C2\u6570%1\u5FC5\u987B\u662F\u6574\u6570",
          NotMathMLToken: "%1\u4E0D\u662F\u6743\u6807\u5143\u7D20",
          InvalidMathMLAttr: "\u65E0\u6548MathML\u5C5E\u6027\uFF1A%1",
          UnknownAttrForElement: "%1\u4E0D\u662F%2\u7684\u5DF2\u8BC6\u522B\u5C5E\u6027",
          MaxMacroSub1: "\u8D85\u51FAMathJax\u6700\u5927\u5B8F\u66FF\u4EE3\u6B21\u6570\uFF1B\u5B58\u5728\u9012\u5F52\u7684\u5B8F\u8C03\u7528\uFF1F",
          MissingArgFor: "\u4E0E%1\u76F8\u5173\u7684\u53C2\u6570\u7F3A\u5931",
          InvalidEnv: "\u65E0\u6548\u7684\u73AF\u5883\u540D\u79F0\u201C%1\u201D",
          UnknownEnv: "\u672A\u77E5\u7684\u73AF\u5883\u53D8\u91CF'%1'",
          MissingCloseBracket: "\u65E0\u6CD5\u627E\u5230%1\u7684\u53C2\u6570\u7684\u53F3\u201C]\u201D",
          MissingOrUnrecognizedDelim: "\u627E\u4E0D\u5230\u6216\u65E0\u6CD5\u8BC6\u522B%1\u7684\u5206\u9694\u7B26",
          MissingDimOrUnits: "\u7F3A\u5C11%1\u7684\u7EF4\u5EA6\u6216\u5176\u5355\u4F4D",
          TokenNotFoundForCommand: "\u65E0\u6CD5\u627E\u5230\u7528\u4E8E%2\u7684%1",
          MathNotTerminated: "\u6570\u5B66\u5F0F\u5728\u6587\u672C\u6846\u4E2D\u672A\u7ED3\u675F",
          IllegalMacroParam: "\u975E\u6CD5\u5B8F\u53C2\u6570\u5F15\u7528",
          MaxBufferSize: "MathJax\u5185\u90E8\u7F13\u51B2\u533A\u5927\u5C0F\u8D85\u9650\uFF1B\u5B58\u5728\u9012\u5F52\u7684\u5B8F\u8C03\u7528\uFF1F",
          CommandNotAllowedInEnv: "%1\u5728%2\u73AF\u5883\u4E2D\u4E0D\u5141\u8BB8",
          IllegalAlign: "\u6307\u5B9A\u7684\u5BF9\u9F50\u65B9\u5F0F%1\u4E0D\u7B26\u7F16\u8F91\u624B\u518C",
          BadMathStyleFor: "%1\u7684\u6570\u5F0F\u6837\u5F0F\u65E0\u6548",
          PositiveIntegerArg: "\u53C2\u6570%1\u5FC5\u987B\u662F\u6B63\u6574\u6570",
          ErroneousNestingEq: "\u9519\u8BEF\u7684\u65B9\u7A0B\u5D4C\u5957\u7ED3\u6784",
          MultipleBBoxProperty: "%1\u5728%2\u4E2D\u6307\u5B9A\u4E86\u4E24\u6B21",
          ExtraEndMissingBegin: "\u6709\u591A\u4F59\u7684%1\u6216\u7F3A\u5C11\\begingroup",
          UndefinedColorModel: "\u8272\u5F69\u6A21\u5757\u201C%1\u201D\u672A\u5B9A\u4E49",
          ModelArg1: "%1\u6A21\u5757\u7684\u8272\u5F69\u503C\u9700\u8981\u4E09\u4E2A\u6570\u5B57",
          InvalidDecimalNumber: "\u65E0\u6548\u5341\u8FDB\u5236\u6570",
          ModelArg2: "%1\u6A21\u5757\u7684\u8272\u5F69\u503C\u5FC5\u987B\u5728%2\u548C%3\u4E4B\u95F4",
          InvalidNumber: "\u4E0D\u5141\u8BB8\u7684\u6570\u5B57",
          NewextarrowArg1: "%1\u7684\u7B2C\u4E00\u4E2A\u53C2\u6570\u5FC5\u987B\u662F\u4E00\u4E2A\u63A7\u5236\u6570\u5217\u540D\u79F0",
          NewextarrowArg2: "%1\u7684\u7B2C\u4E8C\u4E2A\u53C2\u6570\u5FC5\u987B\u662F\u7531\u9017\u53F7\u5206\u5F00\u7684\u4E24\u4E2A\u6574\u6570",
          NewextarrowArg3: "%1\u7684\u7B2C\u4E09\u4E2A\u53C2\u6570\u5FC5\u987B\u662FUnicode\u5B57\u7B26\u503C",
          NoClosingChar: "\u672A\u80FD\u627E\u5230\u5173\u95ED\u7684%1",
          IllegalControlSequenceName: "\u975E\u6CD5\u63A7\u5236\u5E8F\u5217\u540D\u79F0%1",
          IllegalParamNumber: "%1\u6307\u5B9A\u7684\u53C2\u6570\u6570\u91CF\u975E\u6CD5",
          MissingCS: "%1\u5FC5\u987B\u8DDF\u7740\u4E00\u4E2A\u63A7\u5236\u5E8F\u5217",
          CantUseHash2: "%1\u7684\u6A21\u677F\u4E2D\u975E\u6CD5\u4F7F\u7528#",
          SequentialParam: "%1\u7684\u53C2\u6570\u5FC5\u987B\u987A\u5E8F\u6807\u53F7",
          MissingReplacementString: "%1\u7684\u5B9A\u4E49\u7F3A\u5C11\u66FF\u6362\u5B57\u7B26\u4E32",
          MismatchUseDef: "%1\u7684\u4F7F\u7528\u4E0D\u7B26\u5408\u5176\u5B9A\u4E49",
          NoClosingDelim: "\u65E0\u6CD5\u627E\u5230\u7528\u4E8E\u7ED3\u675F\u7684\u5206\u9694\u7B26%1",
          MaxMacroSub2: "\u5DF2\u8D85\u51FAMathJax\u7684\u6700\u9AD8\u66FF\u4EE3\u6B21\u6570\uFF1B\u96BE\u9053\u5B58\u5728\u5FAA\u73AFLaTeX\u73AF\u5883\uFF1F",
          MultipleLabel: "\u5DF2\u5B9A\u4E49\u6807\u7B7E\u201C%1\u201D\u4E58",
          DoubleExponentPrime: "\u89D2\u5206\u7B26\u53F7\u5BFC\u81F4\u53CC\u91CD\u6307\u6570\uFF1A\u4F7F\u7528\u5927\u62EC\u53F7\u6F84\u6E05",
          ExtraAlignTab: "\\cases \u6587\u672C\u4E2D\u6709\u989D\u5916\u7684\u53C2\u6570\u5236\u8868\u7B26",
          BracketMustBeDimension: "%1\u7684\u62EC\u53F7\u53C2\u6570\u5FC5\u987B\u662F\u4E00\u4E2A\u5C3A\u5BF8",
          ExtraCloseLooking: "\u5BFB\u627E %1 \u65F6\u53D1\u73B0\u4E00\u4E2A\u989D\u5916\u7684\u53F3\u5927\u62EC\u53F7",
          CommandAtTheBeginingOfLine: "%1\u5FC5\u987B\u4F4D\u4E8E\u884C\u7684\u5F00\u5934",
          MultlineRowsOneCol: "%1 \u73AF\u5883\u5185\u7684\u884C\u5FC5\u987B\u53EA\u6709\u4E00\u4E2A\u5217",
          InvalidBBoxProperty: "\u201C%1\u201D\u597D\u50CF\u4E0D\u662F\u4E00\u4E2A\u989C\u8272\u3001\u586B\u5145\u5C3A\u5BF8\u6216\u6837\u5F0F",
          GlobalNotFollowedBy: "%1\u4E0D\u88AB\\let\u3001\\def\u6216\\newcommand\u5141\u8BB8",
          RunawayArgument: "%1\u7684\u53C2\u6570\u5931\u63A7\u4E86\u4E48\uFF1F"
        }
});

MathJax.Ajax.loadComplete("[MathJax]/localization/zh-hans/TeX.js");
