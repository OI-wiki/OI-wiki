/*************************************************************
 *
 *  MathJax/jax/output/HTML-CSS/fonts/Neo-Euler/fontdata-extra.js
 *  
 *  Adds extra stretchy characters to the Neo-Euler fonts

 *  Copyright (c) 2013-2018 The MathJax Consortium
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
 */

(function (HTMLCSS) {
  var VERSION = "2.7.5";

  var DELIMITERS = HTMLCSS.FONTDATA.DELIMITERS;

  var H = "H", V = "V";

  var ALPHABETS = "NeoEulerMathJax_Alphabets",
      ARROWS = "NeoEulerMathJax_Arrows",
      FRAKTUR = "NeoEulerMathJax_Fraktur",
      MAIN = "NeoEulerMathJax_Main",
      MARKS = "NeoEulerMathJax_Marks",
      NONUNICODE = "NeoEulerMathJax_NonUnicode",
      NORMAL = "NeoEulerMathJax_Normal",
      OPERATORS = "NeoEulerMathJax_Operators",
      SCRIPT = "NeoEulerMathJax_Script",
      SHAPES = "NeoEulerMathJax_Shapes",
      SIZE1 = "NeoEulerMathJax_Size1",
      SIZE2 = "NeoEulerMathJax_Size2",
      SIZE3 = "NeoEulerMathJax_Size3",
      SIZE4 = "NeoEulerMathJax_Size4",
      SIZE5 = "NeoEulerMathJax_Size5",
      SYMBOLS = "NeoEulerMathJax_Symbols",
      VARIANTS = "NeoEulerMathJax_Variants",
      DOUBLESTRUCK = "NeoEulerMathJax_Normal",
      SANSSERIF = "NeoEulerMathJax_Normal",
      MONOSPACE = "NeoEulerMathJax_Normal";

  var delim = {
      0x2044:
      {
        dir: V,
        HW: [[0.912,MAIN], [1.199,SIZE1], [1.799,SIZE2], [2.399,SIZE3], [2.999,SIZE4]]
      },
      0x20E1:
      {
        dir: H,
        HW: [[0.449,MARKS]],
        stretch: {left:[0x20D6,MARKS], rep:[0xE004,SIZE5], right:[0x20D7,MAIN]}
      },
      0x20EE:
      {
        dir: H,
        HW: [[0.418,MARKS]],
        stretch: {left:[0x20EE,MARKS], rep:[0xE005,SIZE5]}
      },
      0x20EF:
      {
        dir: H,
        HW: [[0.418,MARKS]],
        stretch: {rep:[0xE005,SIZE5], right:[0x20EF,MARKS]}
      },
      0x220F:
      {
        dir: V,
        HW: [[1.000,OPERATORS], [1.400,SIZE1]]
      },
      0x2210:
      {
        dir: V,
        HW: [[1.000,OPERATORS], [1.400,SIZE1]]
      },
      0x2211:
      {
        dir: V,
        HW: [[1.000,OPERATORS], [1.400,SIZE1]]
      },
      0x2227:
      {
        dir: V,
        HW: [[0.718,MAIN], [0.998,SIZE1], [1.395,SIZE2]]
      },
      0x2228:
      {
        dir: V,
        HW: [[0.700,MAIN], [0.998,SIZE1], [1.395,SIZE2]]
      },
      0x2229:
      {
        dir: V,
        HW: [[0.600,MAIN], [0.965,SIZE1], [1.358,SIZE2]]
      },
      0x222A:
      {
        dir: V,
        HW: [[0.600,MAIN], [0.965,SIZE1], [1.358,SIZE2]]
      },
      0x222B:
      {
        dir: V,
        HW: [[1.111,MAIN], [2.222,SIZE1]]
      },
      0x222C:
      {
        dir: V,
        HW: [[1.111,OPERATORS], [2.222,SIZE1]]
      },
      0x222D:
      {
        dir: V,
        HW: [[1.111,OPERATORS], [2.222,SIZE1]]
      },
      0x222E:
      {
        dir: V,
        HW: [[1.111,OPERATORS], [2.222,SIZE1]]
      },
      0x228E:
      {
        dir: V,
        HW: [[0.600,MAIN], [0.965,SIZE1], [1.358,SIZE2]]
      },
      0x22C0:
      {
        dir: V,
        HW: [[0.718,OPERATORS], [0.998,SIZE1], [1.395,SIZE2]]
      },
      0x22C1:
      {
        dir: V,
        HW: [[0.700,OPERATORS], [0.998,SIZE1], [1.395,SIZE2]]
      },
      0x22C2:
      {
        dir: V,
        HW: [[0.600,OPERATORS], [0.965,SIZE1], [1.358,SIZE2]]
      },
      0x22C3:
      {
        dir: V,
        HW: [[0.600,OPERATORS], [0.965,SIZE1], [1.358,SIZE2]]
      },
      0x23DC:
      {
        dir: H,
        HW: [[0.925,MAIN], [1.199,SIZE1], [1.799,SIZE2], [2.399,SIZE3], [2.999,SIZE4]],
        stretch: {left:[0xE009,SIZE5], rep:[0xE00A,SIZE5], right:[0xE00B,SIZE5]}
      },
      0x23DD:
      {
        dir: H,
        HW: [[0.925,MAIN], [1.199,SIZE1], [1.799,SIZE2], [2.399,SIZE3], [2.999,SIZE4]],
        stretch: {left:[0xE00C,SIZE5], rep:[0xE00D,SIZE5], right:[0xE00E,SIZE5]}
      },
      0x2A0C:
      {
        dir: V,
        HW: [[1.111,OPERATORS], [2.222,SIZE1]]
      }
  };
  
  for (var id in delim) {if (delim.hasOwnProperty(id)) {DELIMITERS[id] = delim[id]}};

  MathJax.Ajax.loadComplete(HTMLCSS.fontDir + "/fontdata-extra.js");

})(MathJax.OutputJax["HTML-CSS"]);
