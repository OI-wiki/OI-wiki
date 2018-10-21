/*************************************************************
 *
 *  MathJax/jax/output/SVG/fonts/STIX-Web/fontdata-extra.js
 *  
 *  Adds extra stretchy characters to the STIX-Web fonts

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

(function (SVG) {
  var VERSION = "2.7.5";

  var DELIMITERS = SVG.FONTDATA.DELIMITERS;

  var H = "H", V = "V";
  var ARROWREP = [0x2212,MAIN,0,0,0,-.26,-.26];

  var ALPHABETSBOLDITALIC = "STIXMathJax_Alphabets-bold-italic",
      ALPHABETSBOLD = "STIXMathJax_Alphabets-bold",
      ALPHABETSITALIC = "STIXMathJax_Alphabets-italic",
      ALPHABETS = "STIXMathJax_Alphabets",
      ARROWSBOLD = "STIXMathJax_Arrows-bold",
      ARROWS = "STIXMathJax_Arrows",
      DOUBLESTRUCKBOLDITALIC = "STIXMathJax_DoubleStruck-bold-italic",
      DOUBLESTRUCKBOLD = "STIXMathJax_DoubleStruck-bold",
      DOUBLESTRUCKITALIC = "STIXMathJax_DoubleStruck-italic",
      DOUBLESTRUCK = "STIXMathJax_DoubleStruck",
      FRAKTURBOLD = "STIXMathJax_Fraktur-bold",
      FRAKTUR = "STIXMathJax_Fraktur",
      LATINBOLDITALIC = "STIXMathJax_Latin-bold-italic",
      LATINBOLD = "STIXMathJax_Latin-bold",
      LATINITALIC = "STIXMathJax_Latin-italic",
      LATIN = "STIXMathJax_Latin",
      MAINBOLDITALIC = "STIXMathJax_Main-bold-italic",
      MAINBOLD = "STIXMathJax_Main-bold",
      MAINITALIC = "STIXMathJax_Main-italic",
      MAIN = "STIXMathJax_Main",
      MARKSBOLDITALIC = "STIXMathJax_Marks-bold-italic",
      MARKSBOLD = "STIXMathJax_Marks-bold",
      MARKSITALIC = "STIXMathJax_Marks-italic",
      MARKS = "STIXMathJax_Marks",
      MISCBOLDITALIC = "STIXMathJax_Misc-bold-italic",
      MISCBOLD = "STIXMathJax_Misc-bold",
      MISCITALIC = "STIXMathJax_Misc-italic",
      MISC = "STIXMathJax_Misc",
      MONOSPACE = "STIXMathJax_Monospace",
      NORMALBOLDITALIC = "STIXMathJax_Normal-bold-italic",
      NORMALBOLD = "STIXMathJax_Normal-bold",
      NORMALITALIC = "STIXMathJax_Normal-italic",
      OPERATORSBOLD = "STIXMathJax_Operators-bold",
      OPERATORS = "STIXMathJax_Operators",
      SANSSERIFBOLDITALIC = "STIXMathJax_SansSerif-bold-italic",
      SANSSERIFBOLD = "STIXMathJax_SansSerif-bold",
      SANSSERIFITALIC = "STIXMathJax_SansSerif-italic",
      SANSSERIF = "STIXMathJax_SansSerif",
      SCRIPTBOLDITALIC = "STIXMathJax_Script-bold-italic",
      SCRIPTITALIC = "STIXMathJax_Script-italic",
      SCRIPT = "STIXMathJax_Script",
      SHAPESBOLDITALIC = "STIXMathJax_Shapes-bold-italic",
      SHAPESBOLD = "STIXMathJax_Shapes-bold",
      SHAPES = "STIXMathJax_Shapes",
      SIZE1 = "STIXMathJax_Size1",
      SIZE2 = "STIXMathJax_Size2",
      SIZE3 = "STIXMathJax_Size3",
      SIZE4 = "STIXMathJax_Size4",
      SIZE5 = "STIXMathJax_Size5",
      SYMBOLSBOLD = "STIXMathJax_Symbols-bold",
      SYMBOLS = "STIXMathJax_Symbols",
      VARIANTSBOLDITALIC = "STIXMathJax_Variants-bold-italic",
      VARIANTSBOLD = "STIXMathJax_Variants-bold",
      VARIANTSITALIC = "STIXMathJax_Variants-italic",
      VARIANTS = "STIXMathJax_Variants";

  var delim = {
      0x3D:
      {
        dir: H,
        HW: [[589,MAIN]],
        stretch: {rep:[0x3D,MAIN]}
      },
      0x2C7:
      {
        dir: H,
        HW: [[311,MAIN], [560,SIZE1], [979,SIZE2], [1460,SIZE3], [1886,SIZE4], [2328,SIZE5]]
      },
      0x2CD:
      {
        dir: H,
        HW: [[312,MARKS]],
        stretch: {rep:[0x2CD,MARKS]}
      },
      0x2F7:
      {
        dir: H,
        HW: [[330,MARKS], [560,SIZE1], [979,SIZE2], [1460,SIZE3], [1886,SIZE4], [2328,SIZE5]]
      },
      0x20D0:
      {
        dir: H,
        HW: [[436,MARKS], [871,SIZE1], [1308,SIZE2], [1744,SIZE3], [2180,SIZE4], [3000,SIZE5]],
        stretch: {left:[0xE015,SIZE5], rep:[0xE016,SIZE5]}
      },
      0x20D1:
      {
        dir: H,
        HW: [[436,MARKS], [871,SIZE1], [1308,SIZE2], [1744,SIZE3], [2180,SIZE4], [3000,SIZE5]],
        stretch: {rep:[0xE016,SIZE5], right:[0xE017,SIZE5]}
      },
      0x20D6:
      {
        dir: H,
        HW: [[436,MARKS], [872,SIZE1], [1308,SIZE2], [1744,SIZE3], [2180,SIZE4], [3000,SIZE5]],
        stretch: {left:[0xE018,SIZE5], rep:[0xE016,SIZE5]}
      },
      0x20E1:
      {
        dir: H,
        HW: [[478,MARKS]],
        stretch: {left:[0xE018,SIZE5], rep:[0xE016,SIZE5], right:[0xE019,SIZE5]}
      },
      0x20EC:
      {
        dir: H,
        HW: [[436,MARKS], [871,SIZE1], [1308,SIZE2], [1744,SIZE3], [2180,SIZE4], [3000,SIZE5]],
        stretch: {rep:[0xE01A,SIZE5], right:[0xE01B,SIZE5]}
      },
      0x20ED:
      {
        dir: H,
        HW: [[436,MARKS], [871,SIZE1], [1308,SIZE2], [1744,SIZE3], [2180,SIZE4], [3000,SIZE5]],
        stretch: {left:[0xE01C,SIZE5], rep:[0xE01A,SIZE5]}
      },
      0x20EE:
      {
        dir: H,
        HW: [[436,MARKS], [872,SIZE1], [1308,SIZE2], [1744,SIZE3], [2180,SIZE4], [3000,SIZE5]],
        stretch: {left:[0xE01D,SIZE5], rep:[0xE01A,SIZE5]}
      },
      0x20EF:
      {
        dir: H,
        HW: [[436,MARKS], [872,SIZE1], [1308,SIZE2], [1744,SIZE3], [2180,SIZE4], [3000,SIZE5]],
        stretch: {rep:[0xE01A,SIZE5], right:[0xE01E,SIZE5]}
      },
      0x2140:
      {
        dir: V,
        HW: [[1022,DOUBLESTRUCK], [1450,SIZE1]]
      },
      0x219E:
      {
        dir: H,
        HW: [[786,MAIN]],
        stretch: {left:[0x219E,MAIN], rep:ARROWREP}
      },
      0x219F:
      {
        dir: V,
        HW: [[816,ARROWS]],
        stretch: {ext:[0x23D0,MAIN], top:[0x219F,ARROWS]}
      },
      0x21A0:
      {
        dir: H,
        HW: [[786,MAIN]],
        stretch: {right:[0x21A0,MAIN], rep:ARROWREP}
      },
      0x21A1:
      {
        dir: V,
        HW: [[816,ARROWS]],
        stretch: {ext:[0x23D0,MAIN], bot:[0x21A1,ARROWS]}
      },
      0x21A4:
      {
        dir: H,
        HW: [[787,ARROWS]],
        stretch: {left:[0x2190,MAIN], rep:[0x23AF,SYMBOLS], right:[0x27DE,SYMBOLS]}
      },
      0x21A5:
      {
        dir: V,
        HW: [[816,ARROWS]],
        stretch: {bot:[0x5F,MAIN,0.050,-0.010,0.800], ext:[0x23D0,MAIN], top:[0x2191,MAIN]}
      },
      0x21A6:
      {
        dir: H,
        HW: [[787,MAIN]],
        stretch: {left:[0x27DD,SYMBOLS], rep:[0x23AF,SYMBOLS], right:[0x2192,MAIN]}
      },
      0x21A7:
      {
        dir: V,
        HW: [[816,ARROWS]],
        stretch: {top:[0x22A4,MAINBOLD,0.040,0.000,0.600], ext:[0x23D0,MAIN], bot:[0x2193,MAIN]}
      },
      0x21A8:
      {
        dir: V,
        HW: [[816,ARROWS]],
        stretch: {top:[0x2191,MAIN], ext:[0x23D0,MAIN], bot:[0x2913,ARROWS]}
      },
      0x21A9:
      {
        dir: H,
        HW: [[786,MAIN]],
        stretch: {left:[0x2190,MAIN], rep:ARROWREP, right:[0xE0B5,ARROWS]}
      },
      0x21AA:
      {
        dir: H,
        HW: [[786,MAIN]],
        stretch: {left:[0xE0B4,ARROWS], rep:ARROWREP, right:[0x2192,MAIN]}
      },
      0x21B0:
      {
        dir: V,
        HW: [[818,MAIN]],
        stretch: {top:[0x21B0,MAIN], ext:[0x23D0,MAIN,0.152]}
      },
      0x21B1:
      {
        dir: V,
        HW: [[818,MAIN]],
        stretch: {top:[0x21B1,MAIN], ext:[0x23D0,MAIN,-0.195]}
      },
      0x21B2:
      {
        dir: V,
        HW: [[816,ARROWS]],
        stretch: {bot:[0x21B2,ARROWS], ext:[0x23D0,MAIN,0.152]}
      },
      0x21B3:
      {
        dir: V,
        HW: [[816,ARROWS]],
        stretch: {bot:[0x21B3,ARROWS], ext:[0x23D0,MAIN,-0.195]}
      },
      0x21B4:
      {
        dir: H,
        HW: [[786,ARROWS]],
        stretch: {rep:[0x2212,MAIN,0.000,0.400], right:[0x21B4,ARROWS]}
      },
      0x21B5:
      {
        dir: V,
        HW: [[818,ARROWS]],
        stretch: {bot:[0x21B5,ARROWS], ext:[0x23D0,MAIN,0.570]}
      },
      0x21BC:
      {
        dir: H,
        HW: [[847,MAIN]],
        stretch: {left:[0x21BC,MAIN], rep:[0x23AF,SYMBOLS]}
      },
      0x21BD:
      {
        dir: H,
        HW: [[847,MAIN]],
        stretch: {left:[0x21BD,MAIN], rep:[0x23AF,SYMBOLS]}
      },
      0x21BE:
      {
        dir: V,
        HW: [[818,MAIN]],
        stretch: {ext:[0x23D0,MAIN], top:[0x21BE,MAIN]}
      },
      0x21BF:
      {
        dir: V,
        HW: [[818,MAIN]],
        stretch: {ext:[0x23D0,MAIN], top:[0x21BF,MAIN]}
      },
      0x21C0:
      {
        dir: H,
        HW: [[847,MAIN]],
        stretch: {rep:[0x23AF,SYMBOLS], right:[0x21C0,MAIN]}
      },
      0x21C1:
      {
        dir: H,
        HW: [[847,MAIN]],
        stretch: {right:[0x21C1,MAIN], rep:ARROWREP}
      },
      0x21C2:
      {
        dir: V,
        HW: [[818,MAIN]],
        stretch: {bot:[0x21C2,MAIN], ext:[0x23D0,MAIN]}
      },
      0x21C3:
      {
        dir: V,
        HW: [[818,MAIN]],
        stretch: {bot:[0x21C3,MAIN], ext:[0x23D0,MAIN]}
      },
      0x21CB:
      {
        dir: H,
        HW: [[786,MAIN]],
        stretch: {left:[0x296A,ARROWS], rep:[0x3D,MAIN], right:[0x296D,ARROWS]}
      },
      0x21CC:
      {
        dir: H,
        HW: [[786,MAIN]],
        stretch: {left:[0x296B,ARROWS], rep:[0x3D,MAIN], right:[0x296C,ARROWS]}
      },
      0x21DA:
      {
        dir: H,
        HW: [[806,MAIN]],
        stretch: {left:[0x21DA,MAIN], rep:[0xE021,SIZE5]}
      },
      0x21DB:
      {
        dir: H,
        HW: [[806,MAIN]],
        stretch: {rep:[0xE021,SIZE5], right:[0x21DB,MAIN]}
      },
      0x21E0:
      {
        dir: H,
        HW: [[806,MAIN]],
        stretch: {left:[0x21E0,MAIN], rep:[0xE121,ARROWS]}
      },
      0x21E1:
      {
        dir: V,
        HW: [[818,ARROWS]],
        stretch: {ext:[0xE12D,ARROWS], top:[0x21E1,ARROWS]}
      },
      0x21E2:
      {
        dir: H,
        HW: [[806,MAIN]],
        stretch: {right:[0x21E2,MAIN], rep:[0xE12E,ARROWS]}
      },
      0x21E3:
      {
        dir: V,
        HW: [[818,ARROWS]],
        stretch: {ext:[0xE12C,ARROWS], bot:[0x21E3,ARROWS]}
      },
      0x21E4:
      {
        dir: H,
        HW: [[806,ARROWS]],
        stretch: {left:[0x21E4,ARROWS], rep:ARROWREP}
      },
      0x21E5:
      {
        dir: H,
        HW: [[806,ARROWS]],
        stretch: {right:[0x21E5,ARROWS], rep:ARROWREP}
      },
      0x21FD:
      {
        dir: H,
        HW: [[806,ARROWS]],
        stretch: {left:[0x21FD,ARROWS], rep:ARROWREP}
      },
      0x21FE:
      {
        dir: H,
        HW: [[806,ARROWS]],
        stretch: {right:[0x21FE,ARROWS], rep:ARROWREP}
      },
      0x21FF:
      {
        dir: H,
        HW: [[886,ARROWS]],
        stretch: {left:[0x21FD,ARROWS], rep:ARROWREP, right:[0x21FE,ARROWS]}
      },
      0x220F:
      {
        dir: V,
        HW: [[1022,OPERATORS], [1451,SIZE1]]
      },
      0x2210:
      {
        dir: V,
        HW: [[1022,OPERATORS], [1451,SIZE1]]
      },
      0x2211:
      {
        dir: V,
        HW: [[1022,OPERATORS], [1450,SIZE1]]
      },
      0x221B:
      {
        dir: V,
        HW: [[1232,OPERATORS], [1847,SIZE1], [2460,SIZE2], [3075,SIZE3]],
        stretch: {bot:[0xE025,SIZE5], ext:[0xE023,SIZE5], top:[0xE024,SIZE5]}
      },
      0x221C:
      {
        dir: V,
        HW: [[1232,OPERATORS], [1847,SIZE1], [2460,SIZE2], [3075,SIZE3]],
        stretch: {bot:[0xE026,SIZE5], ext:[0xE023,SIZE5], top:[0xE024,SIZE5]}
      },
      0x222B:
      {
        dir: V,
        HW: [[607,MAIN], [979,SIZE1]],
        stretch: {top:[0xE03C,SIZE5], ext:[0xE03D,SIZE5], bot:[0xE03E,SIZE5]}
      },
      0x222C:
      {
        dir: V,
        HW: [[1144,OPERATORS], [2269,SIZE1]]
      },
      0x222D:
      {
        dir: V,
        HW: [[1144,OPERATORS], [2269,SIZE1]]
      },
      0x222E:
      {
        dir: V,
        HW: [[1144,OPERATORS], [2269,SIZE1]]
      },
      0x222F:
      {
        dir: V,
        HW: [[1144,OPERATORS], [2269,SIZE1]]
      },
      0x2230:
      {
        dir: V,
        HW: [[1144,OPERATORS], [2269,SIZE1]]
      },
      0x2231:
      {
        dir: V,
        HW: [[1144,OPERATORS], [2269,SIZE1]]
      },
      0x2232:
      {
        dir: V,
        HW: [[1144,OPERATORS], [2269,SIZE1]]
      },
      0x2233:
      {
        dir: V,
        HW: [[1144,OPERATORS], [2269,SIZE1]]
      },
      0x22C0:
      {
        dir: V,
        HW: [[1022,OPERATORS], [1451,SIZE1]]
      },
      0x22C1:
      {
        dir: V,
        HW: [[1022,OPERATORS], [1451,SIZE1]]
      },
      0x22C2:
      {
        dir: V,
        HW: [[1032,OPERATORS], [1461,SIZE1]]
      },
      0x22C3:
      {
        dir: V,
        HW: [[1032,OPERATORS], [1461,SIZE1]]
      },
      0x23AA:
      {
        dir: V,
        HW: [[1010,SIZE5,null,0xE00D]],
        stretch: {top:[0xE00D,SIZE5], ext:[0xE00D,SIZE5], bot:[0xE00D,SIZE5]}
      },
      0x23B4:
      {
        dir: H,
        HW: [[816,MAIN], [925,SIZE1], [1458,SIZE2], [1991,SIZE3], [2524,SIZE4], [3057,SIZE5]],
        stretch: {left:[0xE027,SIZE5], rep:[0xE028,SIZE5], right:[0xE029,SIZE5]}
      },
      0x23B5:
      {
        dir: H,
        HW: [[816,MAIN], [925,SIZE1], [1458,SIZE2], [1991,SIZE3], [2524,SIZE4], [3057,SIZE5]],
        stretch: {left:[0xE02A,SIZE5], rep:[0xE02B,SIZE5], right:[0xE02C,SIZE5]}
      },
      0x23D0:
      {
        dir: V,
        HW: [[304,MAIN], [690,SIZE1], [879,SIZE2], [1350,SIZE2,1.536], [1827,SIZE2,2.078], [2303,SIZE2,2.620], [2780,SIZE2,3.162]],
        stretch: {ext:[0x2223,MAIN]}
      },
      0x23DC:
      {
        dir: H,
        HW: [[1000,MAIN], [926,SIZE1], [1460,SIZE2], [1886,SIZE3], [2328,SIZE4], [3237,SIZE5]],
        stretch: {left:[0xE02D,SIZE5], rep:[0xE028,SIZE5], right:[0xE02E,SIZE5]}
      },
      0x23DD:
      {
        dir: H,
        HW: [[1000,MAIN], [926,SIZE1], [1460,SIZE2], [1886,SIZE3], [2328,SIZE4], [3237,SIZE5]],
        stretch: {left:[0xE02F,SIZE5], rep:[0xE02B,SIZE5], right:[0xE030,SIZE5]}
      },
      0x23E0:
      {
        dir: H,
        HW: [[1000,MAIN], [1460,SIZE1], [1886,SIZE2], [2312,SIZE3], [2738,SIZE4], [3164,SIZE5]]
      },
      0x23E1:
      {
        dir: H,
        HW: [[1000,MAIN], [1460,SIZE1], [1886,SIZE2], [2312,SIZE3], [2738,SIZE4], [3164,SIZE5]]
      },
      0x2772:
      {
        dir: V,
        HW: [[932,MISC], [1230,SIZE1], [1845,SIZE2], [2459,SIZE3], [3075,SIZE4]]
      },
      0x2773:
      {
        dir: V,
        HW: [[932,MISC], [1230,SIZE1], [1845,SIZE2], [2459,SIZE3], [3075,SIZE4]]
      },
      0x27E6:
      {
        dir: V,
        HW: [[930,SYMBOLS], [1230,SIZE1], [1845,SIZE2], [2460,SIZE3], [3075,SIZE4]],
        stretch: {top:[0x2553,SHAPES], ext:[0x2551,SHAPES], bot:[0x2559,SHAPES]}
      },
      0x27E7:
      {
        dir: V,
        HW: [[930,SYMBOLS], [1230,SIZE1], [1845,SIZE2], [2460,SIZE3], [3075,SIZE4]],
        stretch: {top:[0x2556,SHAPES], ext:[0x2551,SHAPES], bot:[0x255C,SHAPES]}
      },
      0x27EA:
      {
        dir: V,
        HW: [[932,SYMBOLS], [1230,SIZE1], [1845,SIZE2], [2461,SIZE3], [3075,SIZE4]]
      },
      0x27EB:
      {
        dir: V,
        HW: [[932,SYMBOLS], [1230,SIZE1], [1845,SIZE2], [2461,SIZE3], [3075,SIZE4]]
      },
      0x27F0:
      {
        dir: V,
        HW: [[818,ARROWS]],
        stretch: {ext:[0xE037,SIZE5], top:[0x27F0,ARROWS]}
      },
      0x27F1:
      {
        dir: V,
        HW: [[818,ARROWS]],
        stretch: {bot:[0x27F1,ARROWS], ext:[0xE037,SIZE5]}
      },
      0x2906:
      {
        dir: H,
        HW: [[816,ARROWS]],
        stretch: {left:[0x21D0,MAIN], rep:[0x3D,MAIN], right:[0x2AE4,OPERATORS,0.000,-0.090]}
      },
      0x2907:
      {
        dir: H,
        HW: [[816,ARROWS]],
        stretch: {left:[0x22A8,MAIN,0.000,-0.090], rep:[0x3D,MAIN], right:[0x21D2,MAIN]}
      },
      0x290A:
      {
        dir: V,
        HW: [[818,ARROWS]],
        stretch: {ext:[0xE038,SIZE5], top:[0x290A,ARROWS]}
      },
      0x290B:
      {
        dir: V,
        HW: [[818,ARROWS]],
        stretch: {bot:[0x290B,ARROWS], ext:[0xE038,SIZE5]}
      },
      0x2912:
      {
        dir: V,
        HW: [[818,ARROWS]],
        stretch: {top:[0x2912,ARROWS], ext:[0x23D0,MAIN]}
      },
      0x2913:
      {
        dir: V,
        HW: [[818,ARROWS]],
        stretch: {bot:[0x2913,ARROWS], ext:[0x23D0,MAIN]}
      },
      0x294E:
      {
        dir: H,
        HW: [[850,ARROWS]],
        stretch: {left:[0x21BC,MAIN], rep:ARROWREP, right:[0x21C0,MAIN]}
      },
      0x294F:
      {
        dir: V,
        HW: [[818,ARROWS]],
        stretch: {top:[0x21BE,MAIN], ext:[0x23D0,MAIN], bot:[0x21C2,MAIN]}
      },
      0x2950:
      {
        dir: H,
        HW: [[850,ARROWS]],
        stretch: {left:[0x21BD,MAIN], rep:ARROWREP, right:[0x21C1,MAIN]}
      },
      0x2951:
      {
        dir: V,
        HW: [[818,ARROWS]],
        stretch: {top:[0x21BF,MAIN], ext:[0x23D0,MAIN], bot:[0x21C3,MAIN]}
      },
      0x2952:
      {
        dir: H,
        HW: [[816,ARROWS]],
        stretch: {left:[0x2952,ARROWS], rep:ARROWREP}
      },
      0x2953:
      {
        dir: H,
        HW: [[816,ARROWS]],
        stretch: {right:[0x2953,ARROWS], rep:ARROWREP}
      },
      0x2954:
      {
        dir: V,
        HW: [[818,ARROWS]],
        stretch: {top:[0x2954,ARROWS], ext:[0x23D0,MAIN]}
      },
      0x2955:
      {
        dir: V,
        HW: [[818,ARROWS]],
        stretch: {bot:[0x2955,ARROWS], ext:[0x23D0,MAIN]}
      },
      0x2956:
      {
        dir: H,
        HW: [[816,ARROWS]],
        stretch: {left:[0x2956,ARROWS], rep:ARROWREP}
      },
      0x2957:
      {
        dir: H,
        HW: [[816,ARROWS]],
        stretch: {right:[0x2957,ARROWS], rep:ARROWREP}
      },
      0x2958:
      {
        dir: V,
        HW: [[818,ARROWS]],
        stretch: {top:[0x2958,ARROWS], ext:[0x23D0,MAIN]}
      },
      0x2959:
      {
        dir: V,
        HW: [[818,ARROWS]],
        stretch: {bot:[0x2959,ARROWS], ext:[0x23D0,MAIN]}
      },
      0x295A:
      {
        dir: H,
        HW: [[816,ARROWS]],
        stretch: {left:[0x21BC,MAIN], rep:ARROWREP, right:[0x22A3,MAINBOLD,0.000,0.100,0.600]}
      },
      0x295B:
      {
        dir: H,
        HW: [[816,ARROWS]],
        stretch: {left:[0xE0B6,ARROWS], rep:ARROWREP, right:[0x21C0,MAIN]}
      },
      0x295C:
      {
        dir: V,
        HW: [[818,ARROWS]],
        stretch: {bot:[0x5F,MAIN,0.050,-0.010,0.800], ext:[0x23D0,MAIN], top:[0x21BE,MAIN]}
      },
      0x295D:
      {
        dir: V,
        HW: [[818,ARROWS]],
        stretch: {top:[0x22A4,MAINBOLD,0.040,0.000,0.600], ext:[0x23D0,MAIN], bot:[0x21C2,MAIN]}
      },
      0x295E:
      {
        dir: H,
        HW: [[816,ARROWS]],
        stretch: {left:[0x21BD,MAIN], rep:ARROWREP, right:[0x22A3,MAINBOLD,0.000,0.100,0.600]}
      },
      0x295F:
      {
        dir: H,
        HW: [[816,ARROWS]],
        stretch: {left:[0xE0B6,ARROWS], rep:ARROWREP, right:[0x21C1,MAIN]}
      },
      0x2960:
      {
        dir: V,
        HW: [[818,ARROWS]],
        stretch: {bot:[0x5F,MAIN,0.050,-0.010,0.800], ext:[0x23D0,MAIN], top:[0x21BF,MAIN]}
      },
      0x2961:
      {
        dir: V,
        HW: [[818,ARROWS]],
        stretch: {top:[0x22A4,MAINBOLD,0.040,0.000,0.600], ext:[0x23D0,MAIN], bot:[0x21C3,MAIN]}
      },
      0x2980:
      {
        dir: V,
        HW: [[884,SYMBOLS]],
        stretch: {ext:[0x2980,SYMBOLS]}
      },
      0x2983:
      {
        dir: V,
        HW: [[932,SYMBOLS], [1230,SIZE1], [1845,SIZE2], [2460,SIZE3], [3075,SIZE4]]
      },
      0x2984:
      {
        dir: V,
        HW: [[932,SYMBOLS], [1230,SIZE1], [1845,SIZE2], [2460,SIZE3], [3075,SIZE4]]
      },
      0x2985:
      {
        dir: V,
        HW: [[932,SYMBOLS], [1230,SIZE1], [1848,SIZE2], [2459,SIZE3], [3075,SIZE4]]
      },
      0x2986:
      {
        dir: V,
        HW: [[932,SYMBOLS], [1230,SIZE1], [1848,SIZE2], [2459,SIZE3], [3075,SIZE4]]
      },
      0x2997:
      {
        dir: V,
        HW: [[932,MAIN]],
        stretch: {top:[0xE10D,SHAPES,0.100,0.050], ext:[0x23D0,MAIN,-0.100], bot:[0xE10C,SHAPES,0.100]}
      },
      0x2998:
      {
        dir: V,
        HW: [[932,MAIN]],
        stretch: {top:[0xE10C,SHAPES,-0.100,0.050], ext:[0x23D0,MAIN], bot:[0xE10D,SHAPES,-0.100]}
      },
      0x2A00:
      {
        dir: V,
        HW: [[1022,OPERATORS], [1451,SIZE1]]
      },
      0x2A01:
      {
        dir: V,
        HW: [[1022,OPERATORS], [1451,SIZE1]]
      },
      0x2A02:
      {
        dir: V,
        HW: [[1022,OPERATORS], [1451,SIZE1]]
      },
      0x2A03:
      {
        dir: V,
        HW: [[1032,OPERATORS], [1461,SIZE1]]
      },
      0x2A04:
      {
        dir: V,
        HW: [[1032,OPERATORS], [1461,SIZE1]]
      },
      0x2A05:
      {
        dir: V,
        HW: [[1022,OPERATORS], [1451,SIZE1]]
      },
      0x2A06:
      {
        dir: V,
        HW: [[1022,OPERATORS], [1451,SIZE1]]
      },
      0x2A07:
      {
        dir: V,
        HW: [[1022,OPERATORS], [1451,SIZE1]]
      },
      0x2A08:
      {
        dir: V,
        HW: [[1022,OPERATORS], [1451,SIZE1]]
      },
      0x2A09:
      {
        dir: V,
        HW: [[1022,OPERATORS], [1451,SIZE1]]
      },
      0x2A0A:
      {
        dir: V,
        HW: [[1022,OPERATORS], [1450,SIZE1]]
      },
      0x2A0B:
      {
        dir: V,
        HW: [[1144,OPERATORS], [2269,SIZE1]]
      },
      0x2A0C:
      {
        dir: V,
        HW: [[1144,OPERATORS], [2269,SIZE1]]
      },
      0x2A0D:
      {
        dir: V,
        HW: [[1144,OPERATORS], [2269,SIZE1]]
      },
      0x2A0E:
      {
        dir: V,
        HW: [[1144,OPERATORS], [2269,SIZE1]]
      },
      0x2A0F:
      {
        dir: V,
        HW: [[1144,OPERATORS], [2269,SIZE1]]
      },
      0x2A10:
      {
        dir: V,
        HW: [[1144,OPERATORS], [2269,SIZE1]]
      },
      0x2A11:
      {
        dir: V,
        HW: [[1144,OPERATORS], [2269,SIZE1]]
      },
      0x2A12:
      {
        dir: V,
        HW: [[1144,OPERATORS], [2269,SIZE1]]
      },
      0x2A13:
      {
        dir: V,
        HW: [[1144,OPERATORS], [2269,SIZE1]]
      },
      0x2A14:
      {
        dir: V,
        HW: [[1144,OPERATORS], [2269,SIZE1]]
      },
      0x2A15:
      {
        dir: V,
        HW: [[1144,OPERATORS], [2269,SIZE1]]
      },
      0x2A16:
      {
        dir: V,
        HW: [[1144,OPERATORS], [2269,SIZE1]]
      },
      0x2A17:
      {
        dir: V,
        HW: [[1144,OPERATORS], [2269,SIZE1]]
      },
      0x2A18:
      {
        dir: V,
        HW: [[1144,OPERATORS], [2269,SIZE1]]
      },
      0x2A19:
      {
        dir: V,
        HW: [[1144,OPERATORS], [2269,SIZE1]]
      },
      0x2A1A:
      {
        dir: V,
        HW: [[1144,OPERATORS], [2269,SIZE1]]
      },
      0x2A1B:
      {
        dir: V,
        HW: [[1267,OPERATORS], [2426,SIZE1]]
      },
      0x2A1C:
      {
        dir: V,
        HW: [[1267,OPERATORS], [2426,SIZE1]]
      },
      0x2AFC:
      {
        dir: V,
        HW: [[1022,OPERATORS], [1230,SIZE1], [1875,SIZE2]]
      },
      0x2AFF:
      {
        dir: V,
        HW: [[1022,OPERATORS], [1230,SIZE1], [1875,SIZE2]]
      },
      0x2B45:
      {
        dir: H,
        HW: [[818,SHAPES]],
        stretch: {left:[0x2B45,SHAPES], rep:[0xE039,SIZE5]}
      }
  };
  
  for (var id in delim) {if (delim.hasOwnProperty(id)) {DELIMITERS[id] = delim[id]}};

  MathJax.Ajax.loadComplete(SVG.fontDir + "/fontdata-extra.js");

})(MathJax.OutputJax["SVG"]);
