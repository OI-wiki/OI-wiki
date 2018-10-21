/*************************************************************
 *
 *  MathJax/localization/zh-hant/TeX.js
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
MathJax.Localization.addTranslation("zh-hant","TeX",{
        version: "2.7.5",
        isLoaded: true,
        strings: {
          ExtraOpenMissingClose: "\u591A\u9918\u7684\u5DE6\u62EC\u5F27\u6216\u7F3A\u5C11\u53F3\u62EC\u5F27",
          ExtraCloseMissingOpen: "\u591A\u51FA\u7684\u53F3\u62EC\u865F\u6216\u907A\u5931\u5DE6\u62EC\u865F",
          MissingLeftExtraRight: "\u907A\u5931 \\left \u6216\u591A\u9918 \\right",
          MissingScript: "\u7F3A\u5C11\u4E0A\u6A19\u6216\u4E0B\u6A19\u53C3\u6578",
          ExtraLeftMissingRight: "\u6709\u591A\u51FA\u4F86\u7684 \\left \u6216\u6C92\u88DC\u4E0A \\right",
          Misplaced: "%1\u653E\u932F\u4F4D\u7F6E",
          MissingOpenForSub: "\u7F3A\u5C11\u7528\u65BC\u4E0B\u6A19\u7684\u5DE6\u62EC\u865F",
          MissingOpenForSup: "\u7F3A\u5C11\u7528\u65BC\u4E0A\u6A19\u7684\u5DE6\u62EC\u865F",
          AmbiguousUseOf: "%1\u7684\u4F7F\u7528\u4E0D\u660E\u78BA",
          EnvBadEnd: "\\begin{%1}\u4EE5\\end{%2}\u4F86\u7D50\u675F",
          EnvMissingEnd: "\u7F3A\u5C11\\end{%1}",
          MissingBoxFor: "\u7F3A\u5C11\u7528\u65BC%1\u7684\u6846",
          MissingCloseBrace: "\u7F3A\u5C11\u53F3\u62EC\u865F",
          UndefinedControlSequence: "\u672A\u5B9A\u7FA9\u7684\u63A7\u5236\u6578\u5217%1",
          DoubleExponent: "\u51FA\u73FE\u5169\u500B\u6307\u6578\uFF1A\u4F7F\u7528\u5927\u62EC\u865F{}\u4F86\u5206\u6E05\u695A",
          DoubleSubscripts: "\u51FA\u73FE\u5169\u500B\u5E95\u7DDA\uFF1A\u4F7F\u7528\u5927\u62EC\u865F{}\u4F86\u5206\u6E05\u695A",
          DoubleExponentPrime: "\u89D2\u5206\u7B26\u865F\u5C0E\u81F4\u7522\u751F\u96D9\u91CD\u6307\u6578\uFF1A\u4F7F\u7528\u5927\u62EC\u865F\u4F86\u5340\u5206",
          CantUseHash1: "\u5728\u6578\u5B78\u6A21\u5F0F\u88E1\u60A8\u4E0D\u80FD\u4F7F\u7528\u300C\u5DE8\u96C6\u53C3\u6578\u5B57\u5143 #\u300D",
          MisplacedMiddle: "%1\u5FC5\u9808\u5728 \\left \u548C \\right \u4E4B\u9593",
          MisplacedLimits: "%1\u50C5\u5141\u8A31\u7528\u5728\u904B\u7B97\u5F0F\u4E0A",
          MisplacedMoveRoot: "%1\u50C5\u80FD\u5728\u5E36\u6709root\u5B57\u5143\u4E0B\u5448\u73FE",
          MultipleCommand: "\u591A\u500B %1",
          IntegerArg: "\u53C3\u6578%1\u5FC5\u9808\u662F\u500B\u6574\u6578",
          NotMathMLToken: "%1\u4E0D\u662F\u4E00\u500B\u6A19\u793A\u5143\u7D20",
          InvalidMathMLAttr: "\u7121\u6548MathML\u5C6C\u6027\uFF1A %1",
          UnknownAttrForElement: "%1\u5728%2\u4E0D\u662F\u53EF\u8FA8\u8B58\u5C6C\u6027",
          MaxMacroSub1: "\u8D85\u51FAMathJax\u5DE8\u96C6\u66FF\u4EE3\u6B21\u6578\u4E0A\u9650\uFF1B\u662F\u5426\u5B58\u5728\u905E\u8FF4\u5DE8\u96C6\u547C\u53EB\u5167\u5BB9\uFF1F",
          MaxMacroSub2: "\u5DF2\u8D85\u51FAMathJax\u6700\u5927\u4EE3\u63DB\u6B21\u6578\uFF0C\u5728LaTeX\u74B0\u5883\u88E1\u662F\u5426\u5B58\u6709\u905E\u8FF4\u5167\u5BB9?",
          MissingArgFor: "\u7F3A\u5C11\u7528\u65BC%1\u53C3\u6578",
          ExtraAlignTab: "\u5728\\cases\u6587\u5B57\u5167\u5BB9\u88E1\u6709\u591A\u51FA\u7684\u5C0D\u61C9\u53C3\u6578",
          BracketMustBeDimension: "\u7528\u65BC%1\u7684\u62EC\u865F\u53C3\u6578\u5FC5\u9808\u662F\u4E00\u500B\u7DAD\u5EA6",
          InvalidEnv: "\u7121\u6548\u74B0\u5883\u540D\u7A31\u300C%1\u300D",
          UnknownEnv: "\u4E0D\u660E\u74B0\u5883\u8B8A\u6578\u300C%1\u300D",
          ExtraCloseLooking: "\u5728\u627E\u5C0B%1\u6642\u767C\u73FE\u6709\u591A\u51FA\u4F86\u7684\u53F3\u62EC\u865F",
          MissingCloseBracket: "%1\u7684\u53C3\u6578\u7121\u6CD5\u627E\u5230\u53F3\u62EC\u865F\u300C]\u300D",
          MissingOrUnrecognizedDelim: "\u7F3A\u5C11\u6216\u7121\u6CD5\u8FA8\u8B58\u7528\u65BC%1\u7684\u5206\u9694\u7B26\u865F",
          MissingDimOrUnits: "\u7F3A\u5C11\u7528\u65BC%1\u7684\u7DAD\u5EA6\u6216\u55AE\u4F4D",
          TokenNotFoundForCommand: "\u7121\u6CD5\u627E\u5230\u7528\u65BC%2\u7684%1",
          MathNotTerminated: "\u6578\u5B78\u516C\u5F0F\u5728\u6587\u5B57\u6846\u88E1\u672A\u7D50\u675F",
          IllegalMacroParam: "\u975E\u6CD5\u7684\u5DE8\u96C6\u53C3\u6578\u5F15\u7528",
          MaxBufferSize: "\u8D85\u51FAMathJax\u5167\u90E8\u7DE9\u885D\u5927\u5C0F\uFF1B\u662F\u5426\u5B58\u5728\u905E\u8FF4\u5DE8\u96C6\u547C\u53EB\u5167\u5BB9\uFF1F",
          CommandNotAllowedInEnv: "%1 \u4E0D\u88AB\u5141\u8A31\u5728 %2 \u74B0\u5883\u4E0B",
          MultipleLabel: "\u6A19\u7C64\u300C%1\u300D\u88AB\u591A\u91CD\u5B9A\u7FA9",
          CommandAtTheBeginingOfLine: "%1\u5FC5\u9808\u4F4D\u5728\u884C\u5217\u7684\u958B\u982D",
          IllegalAlign: "\u5728%1\u6709\u4E0D\u6B63\u78BA\u6307\u5B9A\u8FA8\u8B58\u65B9\u5F0F",
          BadMathStyleFor: "%1\u7684\u6578\u5B78\u8868\u793A\u5167\u5BB9\u932F\u8AA4",
          PositiveIntegerArg: "\u53C3\u6578%1\u5FC5\u9808\u662F\u500B\u6B63\u6574\u6578",
          ErroneousNestingEq: "\u932F\u8AA4\u7684\u65B9\u7A0B\u5F0F\u5D4C\u5957\u7D50\u69CB",
          MultlineRowsOneCol: "\u5728%1\u74B0\u5883\u88E1\u7684\u884C\u5217\u5FC5\u9808\u53EA\u6709\u4E00\u6B04",
          MultipleBBoxProperty: "%1\u5728%2\u88AB\u6307\u5B9A\u5169\u6B21",
          InvalidBBoxProperty: "\u300C%1\u300D\u4E0D\u50CF\u662F\u4E00\u500B\u8272\u5F69\u3001\u5167\u908A\u7DAD\u5EA6\u3001\u6216\u6A23\u5F0F",
          ExtraEndMissingBegin: "\u6709\u591A\u9918%1\u6216\u7F3A\u5C11\\begingroup",
          GlobalNotFollowedBy: "%1\u4E0D\u88AB\\let\u3001\\def\u3001\u6216\\newcommand\u6240\u5141\u8A31",
          UndefinedColorModel: "\u8272\u5F69\u6A21\u578B\u300C%1\u300D\u6C92\u6709\u5B9A\u7FA9",
          ModelArg1: "\u7528\u65BC%1\u6A21\u578B\u7684\u8272\u5F69\u6578\u503C\u9700\u89813\u500B\u6578\u5B57",
          InvalidDecimalNumber: "\u7121\u6548\u5341\u9032\u4F4D\u6578\u5B57",
          ModelArg2: "\u7528\u65BC%1\u6A21\u578B\u7684\u8272\u5F69\u6578\u503C\u9700\u8981\u4ECB\u65BC%2\u548C%3\u4E4B\u9593",
          InvalidNumber: "\u7121\u6548\u6578\u5B57",
          NewextarrowArg1: "%1\u7684\u7B2C\u4E00\u500B\u53C3\u6578\u5FC5\u9808\u662F\u63A7\u5236\u5E8F\u5217\u540D\u7A31",
          NewextarrowArg2: "%1\u7684\u7B2C\u4E8C\u500B\u53C3\u6578\u5FC5\u9808\u662F\u7531\u9017\u865F\u5206\u958B\u7684\u5169\u500B\u6574\u6578",
          NewextarrowArg3: "%1\u7684\u7B2C\u4E09\u500B\u53C3\u6578\u5FC5\u9808\u662F\u842C\u570B\u78BC\u5B57\u5143\u6578\u5B57",
          NoClosingChar: "\u6C92\u6709\u627E\u5230\u5C01\u9589\u7528\u5B57\u5143%1",
          IllegalControlSequenceName: "\u4E0D\u9069\u5408\u7528\u5728%1\u7684\u63A7\u5236\u5E8F\u5217\u540D\u7A31",
          IllegalParamNumber: "\u6307\u5B9A\u65BC%1\u7684\u4E0D\u9069\u7576\u6578\u5B57\u53C3\u6578",
          MissingCS: "%1\u5FC5\u9808\u8DDF\u96A8\u4E00\u500B\u63A7\u5236\u5E8F\u5217",
          CantUseHash2: "\u5728\u7528\u65BC%1\u7684\u6A21\u677F\u4E0A\u4E0D\u6B63\u78BA\u4F7F\u7528#\u5B57\u5143",
          SequentialParam: "\u7528\u65BC%1\u7684\u53C3\u6578\u5FC5\u9808\u4F9D\u9806\u5E8F\u7DE8\u865F",
          MissingReplacementString: "%1\u7684\u5B9A\u7FA9\u7F3A\u5C11\u66FF\u4EE3\u5B57\u4E32",
          MismatchUseDef: "%1\u7684\u4F7F\u7528\u4E0D\u7B26\u5408\u5B9A\u7FA9",
          RunawayArgument: "\u6709\u7528\u65BC%1\u7684\u53C3\u6578\u4E0D\u898B\u4E86\uFF1F",
          NoClosingDelim: "\u5728%1\u7121\u6CD5\u627E\u5230\u7D50\u675F\u7B26\u865F"
        }
});

MathJax.Ajax.loadComplete("[MathJax]/localization/zh-hant/TeX.js");
