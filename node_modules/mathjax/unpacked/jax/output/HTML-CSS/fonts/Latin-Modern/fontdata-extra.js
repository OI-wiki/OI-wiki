/*************************************************************
 *
 *  MathJax/jax/output/HTML-CSS/fonts/Latin-Modern/fontdata-extra.js
 *  
 *  Adds extra stretchy characters to the Latin-Modern fonts

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

  var ALPHABETS = "LatinModernMathJax_Alphabets",
      ARROWS = "LatinModernMathJax_Arrows",
      DOUBLESTRUCK = "LatinModernMathJax_DoubleStruck",
      FRAKTUR = "LatinModernMathJax_Fraktur",
      LATIN = "LatinModernMathJax_Latin",
      MAIN = "LatinModernMathJax_Main",
      MARKS = "LatinModernMathJax_Marks",
      MISC = "LatinModernMathJax_Misc",
      MONOSPACE = "LatinModernMathJax_Monospace",
      NONUNICODE = "LatinModernMathJax_NonUnicode",
      NORMAL = "LatinModernMathJax_Normal",
      OPERATORS = "LatinModernMathJax_Operators",
      SANSSERIF = "LatinModernMathJax_SansSerif",
      SCRIPT = "LatinModernMathJax_Script",
      SHAPES = "LatinModernMathJax_Shapes",
      SIZE1 = "LatinModernMathJax_Size1",
      SIZE2 = "LatinModernMathJax_Size2",
      SIZE3 = "LatinModernMathJax_Size3",
      SIZE4 = "LatinModernMathJax_Size4",
      SIZE5 = "LatinModernMathJax_Size5",
      SIZE6 = "LatinModernMathJax_Size6",
      SIZE7 = "LatinModernMathJax_Size7",
      SYMBOLS = "LatinModernMathJax_Symbols",
      VARIANTS = "LatinModernMathJax_Variants";

  var delim = {
      0x306:
      {
        dir: H,
        HW: [[0.374,MAIN], [0.658,SIZE1], [0.784,SIZE2], [0.937,SIZE3], [1.120,SIZE4], [1.341,SIZE5], [1.604,SIZE6], [1.920,SIZE7]]
      },
      0x311:
      {
        dir: H,
        HW: [[0.374,MARKS], [0.658,SIZE1], [0.784,SIZE2], [0.937,SIZE3], [1.120,SIZE4], [1.341,SIZE5], [1.604,SIZE6], [1.920,SIZE7]]
      },
      0x32C:
      {
        dir: H,
        HW: [[0.364,MARKS], [0.644,SIZE1], [0.768,SIZE2], [0.919,SIZE3], [1.100,SIZE4], [1.320,SIZE5], [1.581,SIZE6], [1.896,SIZE7]]
      },
      0x32D:
      {
        dir: H,
        HW: [[0.364,MARKS], [0.644,SIZE1], [0.768,SIZE2], [0.919,SIZE3], [1.100,SIZE4], [1.320,SIZE5], [1.581,SIZE6], [1.896,SIZE7]]
      },
      0x32E:
      {
        dir: H,
        HW: [[0.374,MARKS], [0.658,SIZE1], [0.784,SIZE2], [0.937,SIZE3], [1.120,SIZE4], [1.341,SIZE5], [1.604,SIZE6], [1.920,SIZE7]]
      },
      0x32F:
      {
        dir: H,
        HW: [[0.374,MARKS], [0.658,SIZE1], [0.784,SIZE2], [0.937,SIZE3], [1.120,SIZE4], [1.341,SIZE5], [1.604,SIZE6], [1.920,SIZE7]]
      },
      0x330:
      {
        dir: H,
        HW: [[0.370,MARKS], [0.652,SIZE1], [0.778,SIZE2], [0.931,SIZE3], [1.115,SIZE4], [1.335,SIZE5], [1.599,SIZE6], [1.915,SIZE7]]
      },
      0x333:
      {
        dir: H,
        HW: [[0.392,MARKS], [0.568,SIZE1]],
        stretch: {left:[0xE0F8,SIZE7], rep:[0xE0F9,SIZE7], right:[0xE0FA,SIZE7]}
      },
      0x33F:
      {
        dir: H,
        HW: [[0.392,MARKS], [0.568,SIZE1]],
        stretch: {left:[0xE0FE,SIZE7], rep:[0xE0FF,SIZE7], right:[0xE100,SIZE7]}
      },
      0x20D0:
      {
        dir: H,
        HW: [[0.422,MARKS], [0.555,SIZE1]],
        stretch: {left:[0xE008,SIZE7], rep:[0xE009,SIZE7], right:[0xE00A,SIZE7]}
      },
      0x20D1:
      {
        dir: H,
        HW: [[0.422,MARKS], [0.555,SIZE1]],
        stretch: {left:[0xE00B,SIZE7], rep:[0xE00C,SIZE7], right:[0xE00D,SIZE7]}
      },
      0x20D6:
      {
        dir: H,
        HW: [[0.416,MARKS], [0.547,SIZE1]],
        stretch: {left:[0xE00E,SIZE7], rep:[0xE00F,SIZE7], right:[0xE010,SIZE7]}
      },
      0x20D7:
      {
        dir: H,
        HW: [[0.416,MAIN], [0.547,SIZE1]],
        stretch: {left:[0xE011,SIZE7], rep:[0xE012,SIZE7], right:[0xE013,SIZE7]}
      },
      0x20E1:
      {
        dir: H,
        HW: [[0.470,MARKS], [0.603,SIZE1]],
        stretch: {left:[0xE014,SIZE7], rep:[0xE015,SIZE7], right:[0xE016,SIZE7]}
      },
      0x20E9:
      {
        dir: H,
        HW: [[0.360,MARKS], [0.735,SIZE1], [1.110,SIZE2], [1.485,SIZE3], [1.860,SIZE4], [2.235,SIZE5], [2.610,SIZE6], [2.985,SIZE7]],
        stretch: {left:[0xE11B,SIZE7], rep:[0xE11C,SIZE7], right:[0xE11D,SIZE7]}
      },
      0x20EC:
      {
        dir: H,
        HW: [[0.422,MARKS], [0.555,SIZE1]],
        stretch: {left:[0xE017,SIZE7], rep:[0xE018,SIZE7], right:[0xE019,SIZE7]}
      },
      0x20ED:
      {
        dir: H,
        HW: [[0.422,MARKS], [0.555,SIZE1]],
        stretch: {left:[0xE01A,SIZE7], rep:[0xE01B,SIZE7], right:[0xE01C,SIZE7]}
      },
      0x20EE:
      {
        dir: H,
        HW: [[0.416,MARKS], [0.547,SIZE1]],
        stretch: {left:[0xE01D,SIZE7], rep:[0xE01E,SIZE7], right:[0xE01F,SIZE7]}
      },
      0x20EF:
      {
        dir: H,
        HW: [[0.416,MARKS], [0.547,SIZE1]],
        stretch: {left:[0xE020,SIZE7], rep:[0xE021,SIZE7], right:[0xE022,SIZE7]}
      },
      0x2196:
      {
        dir: V,
        HW: [[0.917,MAIN], [1.383,SIZE1]]
      },
      0x2197:
      {
        dir: V,
        HW: [[0.917,MAIN], [1.383,SIZE1]]
      },
      0x2198:
      {
        dir: V,
        HW: [[0.917,MAIN], [1.383,SIZE1]]
      },
      0x2199:
      {
        dir: V,
        HW: [[0.917,MAIN], [1.383,SIZE1]]
      },
      0x219A:
      {
        dir: H,
        HW: [[0.885,MAIN], [1.351,SIZE1]],
        stretch: {left:[0xE02F,SIZE7], rep:[0xE030,SIZE7], mid:[0xE031,SIZE7], right:[0xE032,SIZE7]}
      },
      0x219B:
      {
        dir: H,
        HW: [[0.885,MAIN], [1.351,SIZE1]],
        stretch: {left:[0xE033,SIZE7], rep:[0xE034,SIZE7], mid:[0xE035,SIZE7], right:[0xE036,SIZE7]}
      },
      0x219E:
      {
        dir: H,
        HW: [[0.905,MAIN], [1.351,SIZE1]],
        stretch: {left:[0xE041,SIZE7], rep:[0xE042,SIZE7], right:[0xE043,SIZE7]}
      },
      0x219F:
      {
        dir: V,
        HW: [[0.902,ARROWS], [1.348,SIZE1]],
        stretch: {bot:[0xE047,SIZE7], ext:[0xE048,SIZE7], top:[0xE049,SIZE7]}
      },
      0x21A0:
      {
        dir: H,
        HW: [[0.905,MAIN], [1.351,SIZE1]],
        stretch: {left:[0xE044,SIZE7], rep:[0xE045,SIZE7], right:[0xE046,SIZE7]}
      },
      0x21A1:
      {
        dir: V,
        HW: [[0.902,ARROWS], [1.348,SIZE1]],
        stretch: {bot:[0xE04A,SIZE7], ext:[0xE04B,SIZE7], top:[0xE04C,SIZE7]}
      },
      0x21A2:
      {
        dir: H,
        HW: [[1.080,MAIN], [1.546,SIZE1]],
        stretch: {left:[0xE04D,SIZE7], rep:[0xE04E,SIZE7], right:[0xE04F,SIZE7]}
      },
      0x21A3:
      {
        dir: H,
        HW: [[1.080,MAIN], [1.546,SIZE1]],
        stretch: {left:[0xE050,SIZE7], rep:[0xE051,SIZE7], right:[0xE052,SIZE7]}
      },
      0x21A5:
      {
        dir: V,
        HW: [[0.862,ARROWS], [1.328,SIZE1]],
        stretch: {bot:[0xE059,SIZE7], ext:[0xE05A,SIZE7], top:[0xE05B,SIZE7]}
      },
      0x21A7:
      {
        dir: V,
        HW: [[0.862,ARROWS], [1.328,SIZE1]],
        stretch: {bot:[0xE05C,SIZE7], ext:[0xE05D,SIZE7], top:[0xE05E,SIZE7]}
      },
      0x21A9:
      {
        dir: H,
        HW: [[0.885,MAIN], [1.351,SIZE1]],
        stretch: {left:[0xE062,SIZE7], rep:[0xE063,SIZE7], right:[0xE064,SIZE7]}
      },
      0x21AA:
      {
        dir: H,
        HW: [[0.885,MAIN], [1.351,SIZE1]],
        stretch: {left:[0xE05F,SIZE7], rep:[0xE060,SIZE7], right:[0xE061,SIZE7]}
      },
      0x21AB:
      {
        dir: H,
        HW: [[0.885,MAIN], [1.351,SIZE1]],
        stretch: {left:[0xE068,SIZE7], rep:[0xE069,SIZE7], right:[0xE06A,SIZE7]}
      },
      0x21AC:
      {
        dir: H,
        HW: [[0.885,MAIN], [1.351,SIZE1]],
        stretch: {left:[0xE065,SIZE7], rep:[0xE066,SIZE7], right:[0xE067,SIZE7]}
      },
      0x21AD:
      {
        dir: H,
        HW: [[0.884,MAIN], [1.330,SIZE1]]
      },
      0x21AE:
      {
        dir: H,
        HW: [[0.884,MAIN], [1.330,SIZE1]],
        stretch: {left:[0xE03D,SIZE7], rep:[0xE03E,SIZE7], mid:[0xE03F,SIZE7], right:[0xE040,SIZE7]}
      },
      0x21B0:
      {
        dir: V,
        HW: [[0.858,MAIN], [1.168,SIZE1]]
      },
      0x21B1:
      {
        dir: V,
        HW: [[0.858,MAIN], [1.168,SIZE1]]
      },
      0x21B2:
      {
        dir: V,
        HW: [[0.858,ARROWS], [1.168,SIZE1]]
      },
      0x21B3:
      {
        dir: V,
        HW: [[0.858,ARROWS], [1.168,SIZE1]]
      },
      0x21B6:
      {
        dir: H,
        HW: [[0.868,MAIN], [1.218,SIZE1]]
      },
      0x21B7:
      {
        dir: H,
        HW: [[0.868,MAIN], [1.218,SIZE1]]
      },
      0x21BC:
      {
        dir: H,
        HW: [[0.900,MAIN], [1.366,SIZE1]],
        stretch: {left:[0xE06B,SIZE7], rep:[0xE06C,SIZE7], right:[0xE06D,SIZE7]}
      },
      0x21BD:
      {
        dir: H,
        HW: [[0.900,MAIN], [1.366,SIZE1]],
        stretch: {left:[0xE071,SIZE7], rep:[0xE072,SIZE7], right:[0xE073,SIZE7]}
      },
      0x21BE:
      {
        dir: V,
        HW: [[0.900,MAIN], [1.366,SIZE1]],
        stretch: {bot:[0xE077,SIZE7], ext:[0xE078,SIZE7], top:[0xE079,SIZE7]}
      },
      0x21BF:
      {
        dir: V,
        HW: [[0.900,MAIN], [1.366,SIZE1]],
        stretch: {bot:[0xE07D,SIZE7], ext:[0xE07E,SIZE7], top:[0xE07F,SIZE7]}
      },
      0x21C0:
      {
        dir: H,
        HW: [[0.900,MAIN], [1.366,SIZE1]],
        stretch: {left:[0xE06E,SIZE7], rep:[0xE06F,SIZE7], right:[0xE070,SIZE7]}
      },
      0x21C1:
      {
        dir: H,
        HW: [[0.900,MAIN], [1.366,SIZE1]],
        stretch: {left:[0xE074,SIZE7], rep:[0xE075,SIZE7], right:[0xE076,SIZE7]}
      },
      0x21C2:
      {
        dir: V,
        HW: [[0.900,MAIN], [1.366,SIZE1]],
        stretch: {bot:[0xE07A,SIZE7], ext:[0xE07B,SIZE7], top:[0xE07C,SIZE7]}
      },
      0x21C3:
      {
        dir: V,
        HW: [[0.900,MAIN], [1.366,SIZE1]],
        stretch: {bot:[0xE080,SIZE7], ext:[0xE081,SIZE7], top:[0xE082,SIZE7]}
      },
      0x21C4:
      {
        dir: H,
        HW: [[0.906,MAIN], [1.372,SIZE1]],
        stretch: {left:[0xE083,SIZE7], rep:[0xE084,SIZE7], right:[0xE085,SIZE7]}
      },
      0x21C5:
      {
        dir: V,
        HW: [[0.906,ARROWS], [1.372,SIZE1]],
        stretch: {bot:[0xE089,SIZE7], ext:[0xE08A,SIZE7], top:[0xE08B,SIZE7]}
      },
      0x21C6:
      {
        dir: H,
        HW: [[0.906,MAIN], [1.372,SIZE1]],
        stretch: {left:[0xE086,SIZE7], rep:[0xE087,SIZE7], right:[0xE088,SIZE7]}
      },
      0x21C7:
      {
        dir: H,
        HW: [[0.885,MAIN], [1.351,SIZE1]],
        stretch: {left:[0xE08F,SIZE7], rep:[0xE090,SIZE7], right:[0xE091,SIZE7]}
      },
      0x21C8:
      {
        dir: V,
        HW: [[0.882,MAIN], [1.348,SIZE1]],
        stretch: {bot:[0xE095,SIZE7], ext:[0xE096,SIZE7], top:[0xE097,SIZE7]}
      },
      0x21C9:
      {
        dir: H,
        HW: [[0.885,MAIN], [1.351,SIZE1]],
        stretch: {left:[0xE092,SIZE7], rep:[0xE093,SIZE7], right:[0xE094,SIZE7]}
      },
      0x21CA:
      {
        dir: V,
        HW: [[0.882,MAIN], [1.348,SIZE1]],
        stretch: {bot:[0xE098,SIZE7], ext:[0xE099,SIZE7], top:[0xE09A,SIZE7]}
      },
      0x21CB:
      {
        dir: H,
        HW: [[0.906,MAIN], [1.372,SIZE1]],
        stretch: {left:[0xE0A1,SIZE7], rep:[0xE0A2,SIZE7], right:[0xE0A3,SIZE7]}
      },
      0x21CC:
      {
        dir: H,
        HW: [[0.906,MAIN], [1.372,SIZE1]],
        stretch: {left:[0xE0A4,SIZE7], rep:[0xE0A5,SIZE7], right:[0xE0A6,SIZE7]}
      },
      0x21CD:
      {
        dir: H,
        HW: [[0.879,MAIN], [1.345,SIZE1]],
        stretch: {left:[0xE0B9,SIZE7], rep:[0xE0BA,SIZE7], mid:[0xE0BB,SIZE7], right:[0xE0BC,SIZE7]}
      },
      0x21CE:
      {
        dir: H,
        HW: [[0.956,MAIN], [1.422,SIZE1]],
        stretch: {left:[0xE0C1,SIZE7], rep:[0xE0C2,SIZE7], mid:[0xE0C3,SIZE7], right:[0xE0C4,SIZE7]}
      },
      0x21CF:
      {
        dir: H,
        HW: [[0.879,MAIN], [1.345,SIZE1]],
        stretch: {left:[0xE0BD,SIZE7], rep:[0xE0BE,SIZE7], mid:[0xE0BF,SIZE7], right:[0xE0C0,SIZE7]}
      },
      0x21D6:
      {
        dir: V,
        HW: [[0.954,ARROWS], [1.420,SIZE1]]
      },
      0x21D7:
      {
        dir: V,
        HW: [[0.954,ARROWS], [1.420,SIZE1]]
      },
      0x21D8:
      {
        dir: V,
        HW: [[0.954,ARROWS], [1.420,SIZE1]]
      },
      0x21D9:
      {
        dir: V,
        HW: [[0.954,ARROWS], [1.420,SIZE1]]
      },
      0x21DA:
      {
        dir: H,
        HW: [[0.903,MAIN], [1.349,SIZE1]],
        stretch: {left:[0xE0CB,SIZE7], rep:[0xE0CC,SIZE7], right:[0xE0CD,SIZE7]}
      },
      0x21DB:
      {
        dir: H,
        HW: [[0.903,MAIN], [1.349,SIZE1]],
        stretch: {left:[0xE0CE,SIZE7], rep:[0xE0CF,SIZE7], right:[0xE0D0,SIZE7]}
      },
      0x21DC:
      {
        dir: H,
        HW: [[0.885,ARROWS], [1.351,SIZE1]]
      },
      0x21DD:
      {
        dir: H,
        HW: [[0.885,MAIN], [1.351,SIZE1]]
      },
      0x21E6:
      {
        dir: H,
        HW: [[0.938,ARROWS], [1.384,SIZE1]],
        stretch: {left:[0xE0D1,SIZE7], rep:[0xE0D2,SIZE7], right:[0xE0D3,SIZE7]}
      },
      0x21E7:
      {
        dir: V,
        HW: [[0.938,ARROWS], [1.384,SIZE1]],
        stretch: {bot:[0xE0D7,SIZE7], ext:[0xE0D8,SIZE7], top:[0xE0D9,SIZE7]}
      },
      0x21E8:
      {
        dir: H,
        HW: [[0.938,ARROWS], [1.384,SIZE1]],
        stretch: {left:[0xE0D4,SIZE7], rep:[0xE0D5,SIZE7], right:[0xE0D6,SIZE7]}
      },
      0x21E9:
      {
        dir: V,
        HW: [[0.938,ARROWS], [1.384,SIZE1]],
        stretch: {bot:[0xE0DA,SIZE7], ext:[0xE0DB,SIZE7], top:[0xE0DC,SIZE7]}
      },
      0x21F3:
      {
        dir: V,
        HW: [[0.950,ARROWS], [1.396,SIZE1]],
        stretch: {bot:[0xE0DD,SIZE7], ext:[0xE0DE,SIZE7], top:[0xE0DF,SIZE7]}
      },
      0x21F5:
      {
        dir: V,
        HW: [[0.906,ARROWS], [1.372,SIZE1]],
        stretch: {bot:[0xE08C,SIZE7], ext:[0xE08D,SIZE7], top:[0xE08E,SIZE7]}
      },
      0x21F6:
      {
        dir: H,
        HW: [[0.885,ARROWS], [1.351,SIZE1]],
        stretch: {left:[0xE09B,SIZE7], rep:[0xE09C,SIZE7], right:[0xE09D,SIZE7]}
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
      0x222F:
      {
        dir: V,
        HW: [[1.111,OPERATORS], [2.222,SIZE1]]
      },
      0x2230:
      {
        dir: V,
        HW: [[1.111,OPERATORS], [2.222,SIZE1]]
      },
      0x2231:
      {
        dir: V,
        HW: [[1.111,OPERATORS], [2.222,SIZE1]]
      },
      0x2232:
      {
        dir: V,
        HW: [[1.111,OPERATORS], [2.222,SIZE1]]
      },
      0x2233:
      {
        dir: V,
        HW: [[1.111,OPERATORS], [2.222,SIZE1]]
      },
      0x2261:
      {
        dir: H,
        HW: [[0.666,MAIN]],
        stretch: {left:[0xE12D,SIZE7], rep:[0xE12E,SIZE7], right:[0xE12F,SIZE7]}
      },
      0x2263:
      {
        dir: H,
        HW: [[0.666,OPERATORS]],
        stretch: {left:[0xE130,SIZE7], rep:[0xE131,SIZE7], right:[0xE132,SIZE7]}
      },
      0x22A2:
      {
        dir: V,
        HW: [[0.684,MAIN], [0.868,SIZE1]]
      },
      0x22A3:
      {
        dir: V,
        HW: [[0.684,MAIN], [0.868,SIZE1]]
      },
      0x22A4:
      {
        dir: V,
        HW: [[0.684,MAIN], [0.868,SIZE1]]
      },
      0x22A5:
      {
        dir: V,
        HW: [[0.684,MAIN], [0.868,SIZE1]]
      },
      0x22C0:
      {
        dir: V,
        HW: [[1.045,OPERATORS], [1.393,SIZE1]]
      },
      0x22C1:
      {
        dir: V,
        HW: [[1.045,OPERATORS], [1.393,SIZE1]]
      },
      0x22C2:
      {
        dir: V,
        HW: [[1.022,OPERATORS], [1.356,SIZE1]]
      },
      0x22C3:
      {
        dir: V,
        HW: [[1.022,OPERATORS], [1.356,SIZE1]]
      },
      0x23B4:
      {
        dir: H,
        HW: [[0.360,MAIN], [0.735,SIZE1], [1.110,SIZE2], [1.485,SIZE3], [1.860,SIZE4], [2.235,SIZE5], [2.610,SIZE6], [2.985,SIZE7]],
        stretch: {left:[0xE11B,SIZE7], rep:[0xE11C,SIZE7], right:[0xE11D,SIZE7]}
      },
      0x23B5:
      {
        dir: H,
        HW: [[0.360,MAIN], [0.735,SIZE1], [1.110,SIZE2], [1.485,SIZE3], [1.860,SIZE4], [2.235,SIZE5], [2.610,SIZE6], [2.985,SIZE7]],
        stretch: {left:[0xE11E,SIZE7], rep:[0xE11F,SIZE7], right:[0xE120,SIZE7]}
      },
      0x23DC:
      {
        dir: H,
        HW: [[0.504,MAIN], [1.006,SIZE1], [1.508,SIZE2], [2.012,SIZE3], [2.516,SIZE4], [3.020,SIZE5], [3.524,SIZE6], [4.032,SIZE7]],
        stretch: {left:[0xE115,SIZE7], rep:[0xE116,SIZE7], right:[0xE117,SIZE7]}
      },
      0x23DD:
      {
        dir: H,
        HW: [[0.504,MAIN], [1.006,SIZE1], [1.508,SIZE2], [2.012,SIZE3], [2.516,SIZE4], [3.020,SIZE5], [3.524,SIZE6], [4.032,SIZE7]],
        stretch: {left:[0xE118,SIZE7], rep:[0xE119,SIZE7], right:[0xE11A,SIZE7]}
      },
      0x23E0:
      {
        dir: H,
        HW: [[0.546,MAIN], [1.048,SIZE1], [1.550,SIZE2], [2.056,SIZE3], [2.564,SIZE4], [3.068,SIZE5], [3.574,SIZE6], [4.082,SIZE7]],
        stretch: {left:[0xE121,SIZE7], rep:[0xE122,SIZE7], right:[0xE123,SIZE7]}
      },
      0x23E1:
      {
        dir: H,
        HW: [[0.546,MAIN], [1.048,SIZE1], [1.550,SIZE2], [2.056,SIZE3], [2.564,SIZE4], [3.068,SIZE5], [3.574,SIZE6], [4.082,SIZE7]],
        stretch: {left:[0xE124,SIZE7], rep:[0xE125,SIZE7], right:[0xE126,SIZE7]}
      },
      0x27A1:
      {
        dir: H,
        HW: [[0.865,MISC], [1.311,SIZE1]],
        stretch: {left:[0xE0E6,SIZE7], rep:[0xE0E7,SIZE7], right:[0xE0E8,SIZE7]}
      },
      0x27E6:
      {
        dir: V,
        HW: [[1.000,SYMBOLS], [1.100,SIZE1], [1.200,SIZE2], [1.450,SIZE3], [1.800,SIZE4], [2.100,SIZE5], [2.400,SIZE6], [3.000,SIZE7]],
        stretch: {bot:[0xE107,SIZE7], ext:[0xE108,SIZE7], top:[0xE109,SIZE7]}
      },
      0x27E7:
      {
        dir: V,
        HW: [[1.000,SYMBOLS], [1.100,SIZE1], [1.200,SIZE2], [1.450,SIZE3], [1.800,SIZE4], [2.100,SIZE5], [2.400,SIZE6], [3.000,SIZE7]],
        stretch: {bot:[0xE10A,SIZE7], ext:[0xE10B,SIZE7], top:[0xE10C,SIZE7]}
      },
      0x27EA:
      {
        dir: V,
        HW: [[1.000,SYMBOLS], [1.100,SIZE1], [1.200,SIZE2], [1.450,SIZE3], [1.800,SIZE4], [2.100,SIZE5], [2.400,SIZE6], [3.000,SIZE7]]
      },
      0x27EB:
      {
        dir: V,
        HW: [[1.000,SYMBOLS], [1.100,SIZE1], [1.200,SIZE2], [1.450,SIZE3], [1.800,SIZE4], [2.100,SIZE5], [2.400,SIZE6], [3.000,SIZE7]]
      },
      0x2A00:
      {
        dir: V,
        HW: [[0.986,OPERATORS], [1.304,SIZE1]]
      },
      0x2A01:
      {
        dir: V,
        HW: [[0.986,OPERATORS], [1.304,SIZE1]]
      },
      0x2A02:
      {
        dir: V,
        HW: [[0.986,OPERATORS], [1.304,SIZE1]]
      },
      0x2A03:
      {
        dir: V,
        HW: [[1.022,OPERATORS], [1.356,SIZE1]]
      },
      0x2A04:
      {
        dir: V,
        HW: [[1.022,OPERATORS], [1.356,SIZE1]]
      },
      0x2A05:
      {
        dir: V,
        HW: [[1.028,OPERATORS], [1.372,SIZE1]]
      },
      0x2A06:
      {
        dir: V,
        HW: [[1.028,OPERATORS], [1.372,SIZE1]]
      },
      0x2A09:
      {
        dir: V,
        HW: [[0.981,OPERATORS], [1.260,SIZE1]]
      },
      0x2A0C:
      {
        dir: V,
        HW: [[1.111,OPERATORS], [2.222,SIZE1]]
      },
      0x2A11:
      {
        dir: V,
        HW: [[1.111,OPERATORS], [2.222,SIZE1]]
      },
      0x2B04:
      {
        dir: H,
        HW: [[0.950,SHAPES], [1.396,SIZE1]],
        stretch: {left:[0xE0E0,SIZE7], rep:[0xE0E1,SIZE7], right:[0xE0E2,SIZE7]}
      },
      0x2B05:
      {
        dir: H,
        HW: [[0.865,SHAPES], [1.311,SIZE1]],
        stretch: {left:[0xE0E3,SIZE7], rep:[0xE0E4,SIZE7], right:[0xE0E5,SIZE7]}
      },
      0x2B06:
      {
        dir: V,
        HW: [[0.865,SHAPES], [1.311,SIZE1]],
        stretch: {bot:[0xE0E9,SIZE7], ext:[0xE0EA,SIZE7], top:[0xE0EB,SIZE7]}
      },
      0x2B07:
      {
        dir: V,
        HW: [[0.865,SHAPES], [1.311,SIZE1]],
        stretch: {bot:[0xE0EC,SIZE7], ext:[0xE0ED,SIZE7], top:[0xE0EE,SIZE7]}
      },
      0x2B0C:
      {
        dir: H,
        HW: [[0.844,SHAPES], [1.290,SIZE1]],
        stretch: {left:[0xE0EF,SIZE7], rep:[0xE0F0,SIZE7], right:[0xE0F1,SIZE7]}
      },
      0x2B0D:
      {
        dir: V,
        HW: [[0.844,SHAPES], [1.290,SIZE1]],
        stretch: {bot:[0xE0F2,SIZE7], ext:[0xE0F3,SIZE7], top:[0xE0F4,SIZE7]}
      },
      0x2B31:
      {
        dir: H,
        HW: [[0.885,SHAPES], [1.351,SIZE1]],
        stretch: {left:[0xE09E,SIZE7], rep:[0xE09F,SIZE7], right:[0xE0A0,SIZE7]}
      }
  };
  
  for (var id in delim) {if (delim.hasOwnProperty(id)) {DELIMITERS[id] = delim[id]}};

  MathJax.Ajax.loadComplete(HTMLCSS.fontDir + "/fontdata-extra.js");

})(MathJax.OutputJax["HTML-CSS"]);
