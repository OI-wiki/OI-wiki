/*************************************************************
 *
 *  MathJax/jax/output/HTML-CSS/fonts/Asana-Math/fontdata-extra.js
 *  
 *  Adds extra stretchy characters to the Asana-Math fonts

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

  var ALPHABETS = "AsanaMathJax_Alphabets",
      ARROWS = "AsanaMathJax_Arrows",
      DOUBLESTRUCK = "AsanaMathJax_DoubleStruck",
      FRAKTUR = "AsanaMathJax_Fraktur",
      LATIN = "AsanaMathJax_Latin",
      MAIN = "AsanaMathJax_Main",
      MARKS = "AsanaMathJax_Marks",
      MISC = "AsanaMathJax_Misc",
      MONOSPACE = "AsanaMathJax_Monospace",
      NONUNICODE = "AsanaMathJax_NonUnicode",
      NORMAL = "AsanaMathJax_Normal",
      OPERATORS = "AsanaMathJax_Operators",
      SANSSERIF = "AsanaMathJax_SansSerif",
      SCRIPT = "AsanaMathJax_Script",
      SHAPES = "AsanaMathJax_Shapes",
      SIZE1 = "AsanaMathJax_Size1",
      SIZE2 = "AsanaMathJax_Size2",
      SIZE3 = "AsanaMathJax_Size3",
      SIZE4 = "AsanaMathJax_Size4",
      SIZE5 = "AsanaMathJax_Size5",
      SIZE6 = "AsanaMathJax_Size6",
      SYMBOLS = "AsanaMathJax_Symbols",
      VARIANTS = "AsanaMathJax_Variants";

  var delim = {
      0x306:
      {
        dir: H,
        HW: [[0.282,MAIN], [0.384,SIZE1], [0.542,SIZE2], [0.922,SIZE3], [1.762,SIZE4]]
      },
      0x333:
      {
        dir: H,
        HW: [[0.433,MARKS], [0.511,SIZE1], [0.675,SIZE2], [1.127,SIZE3]],
        stretch: {rep:[0xE003,SIZE6], right:[0xE003,SIZE6]}
      },
      0x33F:
      {
        dir: H,
        HW: [[0.433,MARKS], [0.511,SIZE1], [0.675,SIZE2], [1.127,SIZE3]],
        stretch: {rep:[0xE004,SIZE6], right:[0xE004,SIZE6]}
      },
      0x2045:
      {
        dir: V,
        HW: [[0.910,MARKS], [1.344,SIZE1], [1.862,SIZE2], [2.328,SIZE3]],
        stretch: {bot:[0xE006,SIZE6], ext:[0xE007,SIZE6], mid:[0xE008,SIZE6], top:[0xE009,SIZE6]}
      },
      0x2046:
      {
        dir: V,
        HW: [[0.910,MARKS], [1.344,SIZE1], [1.862,SIZE2], [2.328,SIZE3]],
        stretch: {bot:[0xE00A,SIZE6], ext:[0xE00B,SIZE6], mid:[0xE00C,SIZE6], top:[0xE00D,SIZE6]}
      },
      0x20D0:
      {
        dir: H,
        HW: [[0.558,MARKS]],
        stretch: {left:[0x20D0,MARKS], rep:[0xE00E,SIZE6]}
      },
      0x20D1:
      {
        dir: H,
        HW: [[0.558,MARKS]],
        stretch: {rep:[0xE00E,SIZE6], right:[0x20D1,MARKS]}
      },
      0x20D6:
      {
        dir: H,
        HW: [[0.558,MARKS], [0.807,SIZE1], [1.127,SIZE2], [1.878,SIZE3], [3.579,SIZE4]],
        stretch: {left:[0x20D6,MARKS], rep:[0xE00E,SIZE6]}
      },
      0x20D7:
      {
        dir: H,
        HW: [[0.558,MAIN], [0.807,SIZE1], [1.127,SIZE2], [1.878,SIZE3], [3.579,SIZE4]],
        stretch: {rep:[0xE00E,SIZE6], right:[0x20D7,MAIN]}
      },
      0x20E1:
      {
        dir: H,
        HW: [[0.557,MARKS]],
        stretch: {left:[0x20D6,MARKS], rep:[0xE00E,SIZE6], right:[0x20D7,MAIN]}
      },
      0x20E9:
      {
        dir: H,
        HW: [[0.630,MARKS]],
        stretch: {left:[0xE00F,SIZE6], rep:[0xE010,SIZE6], right:[0xE011,SIZE6]}
      },
      0x20EE:
      {
        dir: H,
        HW: [[0.557,MARKS]],
        stretch: {left:[0x20EE,MARKS], rep:[0xE012,SIZE6]}
      },
      0x20EF:
      {
        dir: H,
        HW: [[0.557,MARKS]],
        stretch: {rep:[0xE012,SIZE6], right:[0x20EF,MARKS]}
      },
      0x21A9:
      {
        dir: H,
        HW: [[0.884,MAIN]],
        stretch: {left:[0xE013,SIZE6], rep:[0x23AF,SYMBOLS], right:[0xE01A,SIZE6]}
      },
      0x21AA:
      {
        dir: H,
        HW: [[0.884,MAIN]],
        stretch: {left:[0xE01B,SIZE6], rep:[0x23AF,SYMBOLS], right:[0xE017,SIZE6]}
      },
      0x2210:
      {
        dir: V,
        HW: [[0.937,OPERATORS], [1.349,SIZE1], [1.942,SIZE2], [2.797,SIZE3]]
      },
      0x2211:
      {
        dir: V,
        HW: [[0.930,OPERATORS], [1.339,SIZE1], [1.928,SIZE2], [2.776,SIZE3]]
      },
      0x2229:
      {
        dir: V,
        HW: [[0.603,MAIN], [1.559,SIZE1], [2.245,SIZE2], [2.588,SIZE3]]
      },
      0x222B:
      {
        dir: V,
        HW: [[1.327,MAIN], [1.964,SIZE1], [2.711,SIZE2], [3.470,SIZE3]],
        stretch: {bot:[0x2321,SYMBOLS], ext:[0x23AE,SYMBOLS], top:[0x2320,SYMBOLS]}
      },
      0x222C:
      {
        dir: V,
        HW: [[1.327,OPERATORS], [1.964,SIZE1], [2.711,SIZE2], [3.470,SIZE3]]
      },
      0x222D:
      {
        dir: V,
        HW: [[1.327,OPERATORS], [1.964,SIZE1], [2.711,SIZE2], [3.470,SIZE3]]
      },
      0x222E:
      {
        dir: V,
        HW: [[1.327,OPERATORS], [1.964,SIZE1], [2.711,SIZE2], [3.470,SIZE3]]
      },
      0x222F:
      {
        dir: V,
        HW: [[1.327,OPERATORS], [1.964,SIZE1], [2.711,SIZE2], [3.470,SIZE3]]
      },
      0x2230:
      {
        dir: V,
        HW: [[1.327,OPERATORS], [1.964,SIZE1], [2.711,SIZE2], [3.470,SIZE3]]
      },
      0x2231:
      {
        dir: V,
        HW: [[1.327,OPERATORS], [1.964,SIZE1], [2.711,SIZE2], [3.470,SIZE3]]
      },
      0x2232:
      {
        dir: V,
        HW: [[1.327,OPERATORS], [1.964,SIZE1], [2.711,SIZE2], [3.470,SIZE3]]
      },
      0x2233:
      {
        dir: V,
        HW: [[1.327,OPERATORS], [1.964,SIZE1], [2.711,SIZE2], [3.470,SIZE3]]
      },
      0x22C0:
      {
        dir: V,
        HW: [[0.939,OPERATORS], [1.559,SIZE1], [2.588,SIZE2]]
      },
      0x22C1:
      {
        dir: V,
        HW: [[0.939,OPERATORS], [1.559,SIZE1], [2.588,SIZE2]]
      },
      0x22C2:
      {
        dir: V,
        HW: [[0.939,OPERATORS], [1.559,SIZE1], [2.588,SIZE2]]
      },
      0x22C3:
      {
        dir: V,
        HW: [[0.939,OPERATORS], [1.559,SIZE1], [2.245,SIZE2], [2.588,SIZE3]]
      },
      0x23B4:
      {
        dir: H,
        HW: [[0.602,MAIN], [0.978,SIZE1], [1.353,SIZE2], [1.690,SIZE3]],
        stretch: {left:[0xE00F,SIZE6], rep:[0xE010,SIZE6], right:[0xE011,SIZE6]}
      },
      0x23B5:
      {
        dir: H,
        HW: [[0.602,MAIN], [0.978,SIZE1], [1.353,SIZE2], [1.690,SIZE3]],
        stretch: {left:[0xE023,SIZE6], rep:[0xE024,SIZE6], right:[0xE025,SIZE6]}
      },
      0x23DC:
      {
        dir: H,
        HW: [[0.942,MAIN], [0.973,SIZE1], [1.349,SIZE2], [1.686,SIZE3]],
        stretch: {left:[0xE026,SIZE6], rep:[0xE027,SIZE6], right:[0xE028,SIZE6]}
      },
      0x23DD:
      {
        dir: H,
        HW: [[0.942,MAIN], [0.973,SIZE1], [1.349,SIZE2], [1.686,SIZE3]],
        stretch: {left:[0xE029,SIZE6], rep:[0xE02A,SIZE6], right:[0xE02B,SIZE6]}
      },
      0x23E0:
      {
        dir: H,
        HW: [[0.900,MAIN], [1.360,SIZE1], [2.056,SIZE2], [3.108,SIZE3]]
      },
      0x23E1:
      {
        dir: H,
        HW: [[0.900,MAIN], [1.360,SIZE1], [2.056,SIZE2], [3.108,SIZE3]]
      },
      0x27E6:
      {
        dir: V,
        HW: [[0.910,SYMBOLS], [1.025,SIZE1], [1.535,SIZE2], [2.045,SIZE3], [2.556,SIZE4]]
      },
      0x27E7:
      {
        dir: V,
        HW: [[0.910,SYMBOLS], [1.025,SIZE1], [1.535,SIZE2], [2.045,SIZE3], [2.556,SIZE4]]
      },
      0x27EA:
      {
        dir: V,
        HW: [[0.885,SYMBOLS], [1.021,SIZE1], [2.042,SIZE2], [2.552,SIZE3]]
      },
      0x27EB:
      {
        dir: V,
        HW: [[0.885,SYMBOLS], [1.021,SIZE1], [2.042,SIZE2], [2.552,SIZE3]]
      },
      0x29FC:
      {
        dir: V,
        HW: [[0.953,SYMBOLS], [1.372,SIZE1], [1.893,SIZE2], [2.366,SIZE3]]
      },
      0x29FD:
      {
        dir: V,
        HW: [[0.953,SYMBOLS], [1.372,SIZE1], [1.893,SIZE2], [2.366,SIZE3]]
      },
      0x2A00:
      {
        dir: V,
        HW: [[1.146,OPERATORS], [1.650,SIZE1], [2.376,SIZE2]]
      },
      0x2A01:
      {
        dir: V,
        HW: [[1.149,OPERATORS], [1.650,SIZE1], [2.376,SIZE2]]
      },
      0x2A02:
      {
        dir: V,
        HW: [[1.149,OPERATORS], [1.650,SIZE1], [2.376,SIZE2]]
      },
      0x2A03:
      {
        dir: V,
        HW: [[0.939,OPERATORS], [1.559,SIZE1], [2.588,SIZE2]]
      },
      0x2A04:
      {
        dir: V,
        HW: [[0.939,OPERATORS], [1.559,SIZE1], [2.588,SIZE2]]
      },
      0x2A05:
      {
        dir: V,
        HW: [[0.926,OPERATORS], [1.537,SIZE1], [2.552,SIZE2]]
      },
      0x2A06:
      {
        dir: V,
        HW: [[0.926,OPERATORS], [1.537,SIZE1], [2.552,SIZE2]]
      },
      0x2A07:
      {
        dir: V,
        HW: [[0.939,OPERATORS], [1.559,SIZE1], [2.588,SIZE2]]
      },
      0x2A08:
      {
        dir: V,
        HW: [[0.939,OPERATORS], [1.559,SIZE1], [2.588,SIZE2]]
      },
      0x2A09:
      {
        dir: V,
        HW: [[0.926,OPERATORS], [1.333,SIZE1], [1.920,SIZE2]]
      },
      0x2A0C:
      {
        dir: V,
        HW: [[1.327,OPERATORS], [1.964,SIZE1], [2.711,SIZE2], [3.470,SIZE3]]
      },
      0x2A0D:
      {
        dir: V,
        HW: [[1.327,OPERATORS], [1.964,SIZE1], [2.711,SIZE2], [3.470,SIZE3]]
      },
      0x2A0E:
      {
        dir: V,
        HW: [[1.327,OPERATORS], [1.964,SIZE1], [2.711,SIZE2], [3.470,SIZE3]]
      },
      0x2A0F:
      {
        dir: V,
        HW: [[1.327,OPERATORS], [1.964,SIZE1], [2.711,SIZE2], [3.470,SIZE3]]
      },
      0x2A10:
      {
        dir: V,
        HW: [[1.327,OPERATORS], [1.964,SIZE1], [2.711,SIZE2], [3.470,SIZE3]]
      },
      0x2A11:
      {
        dir: V,
        HW: [[1.327,OPERATORS], [1.964,SIZE1], [2.711,SIZE2], [3.470,SIZE3]]
      },
      0x2A12:
      {
        dir: V,
        HW: [[1.327,OPERATORS], [1.964,SIZE1], [2.711,SIZE2], [3.470,SIZE3]]
      },
      0x2A13:
      {
        dir: V,
        HW: [[1.327,OPERATORS], [1.964,SIZE1], [2.711,SIZE2], [3.470,SIZE3]]
      },
      0x2A14:
      {
        dir: V,
        HW: [[1.327,OPERATORS], [1.964,SIZE1], [2.711,SIZE2], [3.470,SIZE3]]
      },
      0x2A15:
      {
        dir: V,
        HW: [[1.327,OPERATORS], [1.964,SIZE1], [2.711,SIZE2], [3.470,SIZE3]]
      },
      0x2A16:
      {
        dir: V,
        HW: [[1.327,OPERATORS], [1.964,SIZE1], [2.711,SIZE2], [3.470,SIZE3]]
      },
      0x2A17:
      {
        dir: V,
        HW: [[1.327,OPERATORS], [1.964,SIZE1], [2.711,SIZE2], [3.470,SIZE3]]
      },
      0x2A18:
      {
        dir: V,
        HW: [[1.327,OPERATORS], [1.964,SIZE1], [2.711,SIZE2], [3.470,SIZE3]]
      },
      0x2A19:
      {
        dir: V,
        HW: [[1.327,OPERATORS], [1.964,SIZE1], [2.711,SIZE2], [3.470,SIZE3]]
      },
      0x2A1A:
      {
        dir: V,
        HW: [[1.327,OPERATORS], [1.964,SIZE1], [2.711,SIZE2], [3.470,SIZE3]]
      },
      0x2A1B:
      {
        dir: V,
        HW: [[1.436,OPERATORS], [2.125,SIZE1], [2.933,SIZE2], [3.754,SIZE3]]
      },
      0x2A1C:
      {
        dir: V,
        HW: [[1.436,OPERATORS], [2.125,SIZE1], [2.933,SIZE2], [3.754,SIZE3]]
      }
  };
  
  for (var id in delim) {if (delim.hasOwnProperty(id)) {DELIMITERS[id] = delim[id]}};

  MathJax.Ajax.loadComplete(HTMLCSS.fontDir + "/fontdata-extra.js");

})(MathJax.OutputJax["HTML-CSS"]);
