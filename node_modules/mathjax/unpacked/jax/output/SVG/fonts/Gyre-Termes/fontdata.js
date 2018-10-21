/*************************************************************
 *
 *  MathJax/jax/output/SVG/fonts/Gyre-Termes/fontdata.js
 *  
 *  Initializes the SVG OutputJax to use the Gyre-Termes fonts

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

(function (SVG,MML,AJAX,HUB) {

  var VERSION = "2.7.5";

  var ALPHABETS = "GyreTermesMathJax_Alphabets",
      ARROWS = "GyreTermesMathJax_Arrows",
      DOUBLESTRUCK = "GyreTermesMathJax_DoubleStruck",
      FRAKTUR = "GyreTermesMathJax_Fraktur",
      LATIN = "GyreTermesMathJax_Latin",
      MAIN = "GyreTermesMathJax_Main",
      MARKS = "GyreTermesMathJax_Marks",
      MISC = "GyreTermesMathJax_Misc",
      MONOSPACE = "GyreTermesMathJax_Monospace",
      NONUNICODE = "GyreTermesMathJax_NonUnicode",
      NORMAL = "GyreTermesMathJax_Normal",
      OPERATORS = "GyreTermesMathJax_Operators",
      SANSSERIF = "GyreTermesMathJax_SansSerif",
      SCRIPT = "GyreTermesMathJax_Script",
      SHAPES = "GyreTermesMathJax_Shapes",
      SIZE1 = "GyreTermesMathJax_Size1",
      SIZE2 = "GyreTermesMathJax_Size2",
      SIZE3 = "GyreTermesMathJax_Size3",
      SIZE4 = "GyreTermesMathJax_Size4",
      SIZE5 = "GyreTermesMathJax_Size5",
      SIZE6 = "GyreTermesMathJax_Size6",
      SYMBOLS = "GyreTermesMathJax_Symbols",
      VARIANTS = "GyreTermesMathJax_Variants";

  var H = "H", V = "V", EXTRAH = {load:"extra", dir:H}, EXTRAV = {load:"extra", dir:V};

  SVG.Augment({
    FONTDATA: {
      version: VERSION,


      baselineskip: 1200,
      lineH: 800, lineD: 200,

      FONTS: {
        "GyreTermesMathJax_Alphabets": "Alphabets/Regular/Main.js",
        "GyreTermesMathJax_Arrows": "Arrows/Regular/Main.js",
        "GyreTermesMathJax_DoubleStruck": "DoubleStruck/Regular/Main.js",
        "GyreTermesMathJax_Fraktur": "Fraktur/Regular/Main.js",
        "GyreTermesMathJax_Latin": "Latin/Regular/Main.js",
        "GyreTermesMathJax_Main": "Main/Regular/Main.js",
        "GyreTermesMathJax_Marks": "Marks/Regular/Main.js",
        "GyreTermesMathJax_Misc": "Misc/Regular/Main.js",
        "GyreTermesMathJax_Monospace": "Monospace/Regular/Main.js",
        "GyreTermesMathJax_NonUnicode": "NonUnicode/Regular/Main.js",
        "GyreTermesMathJax_Normal": "Normal/Regular/Main.js",
        "GyreTermesMathJax_Operators": "Operators/Regular/Main.js",
        "GyreTermesMathJax_SansSerif": "SansSerif/Regular/Main.js",
        "GyreTermesMathJax_Script": "Script/Regular/Main.js",
        "GyreTermesMathJax_Shapes": "Shapes/Regular/Main.js",
        "GyreTermesMathJax_Size1": "Size1/Regular/Main.js",
        "GyreTermesMathJax_Size2": "Size2/Regular/Main.js",
        "GyreTermesMathJax_Size3": "Size3/Regular/Main.js",
        "GyreTermesMathJax_Size4": "Size4/Regular/Main.js",
        "GyreTermesMathJax_Size5": "Size5/Regular/Main.js",
        "GyreTermesMathJax_Size6": "Size6/Regular/Main.js",
        "GyreTermesMathJax_Symbols": "Symbols/Regular/Main.js",
        "GyreTermesMathJax_Variants": "Variants/Regular/Main.js"
      },

      VARIANT: {
          "normal": {fonts: [MAIN,NORMAL,MONOSPACE,LATIN,ALPHABETS,MARKS,ARROWS,OPERATORS,SYMBOLS,SHAPES,MISC,VARIANTS,NONUNICODE,SIZE1]},
          "bold": {fonts: [MAIN,NORMAL,MONOSPACE,LATIN,ALPHABETS,MARKS,ARROWS,OPERATORS,SYMBOLS,SHAPES,MISC,VARIANTS,NONUNICODE,SIZE1], bold:true
, offsetA: 0x1D400, offsetG: 0x1D6A8, offsetN: 0x1D7CE},
          "italic": {fonts: [MAIN,NORMAL,MONOSPACE,LATIN,ALPHABETS,MARKS,ARROWS,OPERATORS,SYMBOLS,SHAPES,MISC,VARIANTS,NONUNICODE,SIZE1], italic:true, offsetA: 0x1D434, offsetG: 0x1D6E2, remap: {0x1D455: 0x210E}},
          "bold-italic": {fonts: [MAIN,NORMAL,MONOSPACE,LATIN,ALPHABETS,MARKS,ARROWS,OPERATORS,SYMBOLS,SHAPES,MISC,VARIANTS,NONUNICODE,SIZE1], bold: true, italic:true, offsetA: 0x1D468, offsetG: 0x1D71C},
          "double-struck": {
            fonts: [DOUBLESTRUCK],
            offsetA: 0x1D538,
            offsetN: 0x1D7D8,
            remap: {0x1D53A: 0x2102, 0x1D53F: 0x210D, 0x1D545: 0x2115, 0x1D547: 0x2119, 0x1D548: 0x211A, 0x1D549: 0x211D, 0x1D551: 0x2124}
          },
          "fraktur": {
            fonts: [FRAKTUR],
            offsetA: 0x1D504,
            remap: {0x1D506: 0x212D, 0x1D50B: 0x210C, 0x1D50C: 0x2111, 0x1D515: 0x211C, 0x1D51D: 0x2128}
          },
          "bold-fraktur": {
            fonts: [FRAKTUR], bold:true,
            offsetA: 0x1D56C
          },
          "script": {
            fonts: [SCRIPT], italic:true,
            offsetA: 0x1D49C,
            remap: {0x1D49D: 0x212C, 0x1D4A0: 0x2130, 0x1D4A1: 0x2131, 0x1D4A3: 0x210B, 0x1D4A4: 0x2110, 0x1D4A7: 0x2112, 0x1D4A8: 0x2133, 0x1D4AD: 0x211B, 0x1D4BA: 0x212F, 0x1D4BC: 0x210A, 0x1D4C4: 0x2134}
          },
          "bold-script": {
            fonts: [SCRIPT], bold:true, italic:true,
            offsetA: 0x1D4D0
          },
          "sans-serif": {
            fonts: [SANSSERIF],
            offsetA: 0x1D5A0,
            offsetN: 0x1D7E2
          },
          "bold-sans-serif": {
            fonts: [SANSSERIF], bold:true,
            offsetA: 0x1D5D4,
            offsetN: 0x1D7EC,
            offsetG: 0x1D756
          },
          "sans-serif-italic": {
             fonts: [SANSSERIF], italic: true,
             offsetA: 0x1D608
          },
          "sans-serif-bold-italic": {
             fonts: [SANSSERIF], bold:true, italic: true,
             offsetA: 0x1D63C,
             offsetG: 0x1D790
          },
          "monospace": {
             fonts: [MONOSPACE],
             offsetA: 0x1D670,
             offsetN: 0x1D7F6
          },
          "-Gyre-Termes-variant": {fonts: [VARIANTS,MAIN,NORMAL,MONOSPACE,LATIN,ALPHABETS,MARKS,ARROWS,OPERATORS,SYMBOLS,SHAPES,MISC,NONUNICODE,SIZE1]},
          "-tex-caligraphic": {fonts: [MAIN,NORMAL,MONOSPACE,LATIN,ALPHABETS,MARKS,ARROWS,OPERATORS,SYMBOLS,SHAPES,MISC,VARIANTS,NONUNICODE,SIZE1], italic: true},
          "-tex-oldstyle": {fonts: [MAIN,NORMAL,MONOSPACE,LATIN,ALPHABETS,MARKS,ARROWS,OPERATORS,SYMBOLS,SHAPES,MISC,VARIANTS,NONUNICODE,SIZE1]},
          "-tex-caligraphic-bold": {fonts: [MAIN,NORMAL,MONOSPACE,LATIN,ALPHABETS,MARKS,ARROWS,OPERATORS,SYMBOLS,SHAPES,MISC,VARIANTS,NONUNICODE,SIZE1], italic: true, bold: true},
          "-tex-oldstyle-bold": {fonts: [MAIN,NORMAL,MONOSPACE,LATIN,ALPHABETS,MARKS,ARROWS,OPERATORS,SYMBOLS,SHAPES,MISC,VARIANTS,NONUNICODE,SIZE1], bold: true},
          "-tex-mathit": {fonts: [MAIN,NORMAL,MONOSPACE,LATIN,ALPHABETS,MARKS,ARROWS,OPERATORS,SYMBOLS,SHAPES,MISC,VARIANTS,NONUNICODE,SIZE1], italic:true, noIC:true},
          "-largeOp": {fonts:[SIZE1,MAIN]},
          "-smallOp": {}
      },

      RANGES: [
        {name: "alpha", low: 0x61, high: 0x7A, offset: "A", add: 26},
        {name: "Alpha", low: 0x41, high: 0x5A, offset: "A"},
        {name: "number", low: 0x30, high: 0x39, offset: "N"},
        {name: "greek", low: 0x03B1, high: 0x03C9, offset: "G", add: 26},
        {name: "Greek", low: 0x0391, high: 0x03F6, offset: "G",
           remap: {0x03F5: 52, 0x03D1: 53, 0x03F0: 54, 0x03D5: 55, 0x03F1: 56, 0x03D6: 57, 0x03F4: 17}}
      ],

      RULECHAR: 0x2212,

      REMAP: {
        0xA: 0x20,
        0x25C2: 0x25C0,
        0x3008: 0x27E8,
        0x3009: 0x27E9,
        0x2758: 0x2223,
        0x25B8: 0x25B6,
        0x03D2: 0x03A5,
        0x25B4: 0x25B2,
        0x25B5: 0x25B3,
        0xFE37: 0x23DE,
        0xFE38: 0x23DF,
        0x02B9: 0x2032,
        0x25FB: 0x25A1,
        0x25FC: 0x25A0,
        0x25BE: 0x25BC,
        0x203E: 0x0305,
        0x25BF: 0x25BD
      },

      REMAPACCENT: {
        "\u007E": "\u0303",
        "\u2192": "\u20D7",
        "\u0060": "\u0300",
        "\u005E": "\u0302",
        "\u00B4": "\u0301",
        "\u2032": "\u0301",
        "\u2035": "\u0300"
      },

      REMAPACCENTUNDER: {
      },

      DELIMITERS: {
        0x28:
        {
          dir: V,
          HW: [[816,MAIN], [976,SIZE1], [1168,SIZE2], [1398,SIZE3], [1674,SIZE4], [2005,SIZE5], [2404,SIZE6], [2780,SIZE6,1.157]],
          stretch: {bot:[0x239D,SYMBOLS], ext:[0x239C,SYMBOLS], top:[0x239B,SYMBOLS]}
        },
        0x29:
        {
          dir: V,
          HW: [[816,MAIN], [976,SIZE1], [1168,SIZE2], [1398,SIZE3], [1674,SIZE4], [2005,SIZE5], [2404,SIZE6], [2780,SIZE6,1.157]],
          stretch: {bot:[0x23A0,SYMBOLS], ext:[0x239F,SYMBOLS], top:[0x239E,SYMBOLS]}
        },
        0x2D: {alias: 0x2212, dir: H},
        0x2F:
        {
          dir: V,
          HW: [[800,MAIN], [1048,SIZE1], [1372,SIZE2], [1798,SIZE3], [1827,SIZE3,1.016], [2356,SIZE4], [3086,SIZE5], [4043,SIZE6]]
        },
        0x3D:
        {
          dir: H,
          HW: [[500,MAIN]],
          stretch: {left:[0xE000,SIZE6], rep:[0xE001,SIZE6], right:[0xE002,SIZE6]}
        },
        0x5B:
        {
          dir: V,
          HW: [[836,MAIN], [998,SIZE1], [1190,SIZE2], [1422,SIZE3], [1698,SIZE4], [2032,SIZE5], [2432,SIZE6], [2780,SIZE6,1.143]],
          stretch: {bot:[0x23A3,SYMBOLS], ext:[0x23A2,SYMBOLS], top:[0x23A1,SYMBOLS]}
        },
        0x5C:
        {
          dir: V,
          HW: [[800,MAIN], [1048,SIZE1], [1372,SIZE2], [1798,SIZE3], [1827,SIZE3,1.016], [2356,SIZE4], [3086,SIZE5], [4043,SIZE6]]
        },
        0x5D:
        {
          dir: V,
          HW: [[836,MAIN], [998,SIZE1], [1190,SIZE2], [1422,SIZE3], [1698,SIZE4], [2032,SIZE5], [2432,SIZE6], [2780,SIZE6,1.143]],
          stretch: {bot:[0x23A6,SYMBOLS], ext:[0x23A5,SYMBOLS], top:[0x23A4,SYMBOLS]}
        },
        0x5E: {alias: 0x302, dir: H},
        0x5F: {alias: 0x332, dir: H},
        0x7B:
        {
          dir: V,
          HW: [[820,MAIN], [980,SIZE1], [1172,SIZE2], [1402,SIZE3], [1678,SIZE4], [2009,SIZE5], [2408,SIZE6], [2780,SIZE6,1.155]],
          stretch: {bot:[0x23A9,SYMBOLS], ext:[0xE003,SIZE6], mid:[0x23A8,SYMBOLS], top:[0x23A7,SYMBOLS]}
        },
        0x7C:
        {
          dir: V,
          HW: [[800,MAIN], [960,SIZE1], [1152,SIZE2], [1382,SIZE3], [1658,SIZE4], [1990,SIZE5], [2388,SIZE6]],
          stretch: {bot:[0xE004,SIZE6], ext:[0xE005,SIZE6], top:[0xE006,SIZE6]}
        },
        0x7D:
        {
          dir: V,
          HW: [[820,MAIN], [980,SIZE1], [1172,SIZE2], [1402,SIZE3], [1678,SIZE4], [2009,SIZE5], [2408,SIZE6], [2780,SIZE6,1.155]],
          stretch: {bot:[0x23AD,SYMBOLS], ext:[0xE007,SIZE6], mid:[0x23AC,SYMBOLS], top:[0x23AB,SYMBOLS]}
        },
        0x7E: {alias: 0x303, dir: H},
        0xAF: {alias: 0x332, dir: H},
        0x2C6: {alias: 0x302, dir: H},
        0x2C9: {alias: 0x2212, dir: H},
        0x2DC: {alias: 0x303, dir: H},
        0x302:
        {
          dir: H,
          HW: [[342,MAIN], [608,SIZE1], [727,SIZE2], [870,SIZE3], [1041,SIZE4], [1249,SIZE5], [1496,SIZE6]]
        },
        0x303:
        {
          dir: H,
          HW: [[334,MAIN], [601,SIZE1], [720,SIZE2], [863,SIZE3], [1037,SIZE4], [1241,SIZE5], [1491,SIZE6]]
        },
        0x305:
        {
          dir: H,
          HW: [[333,MARKS], [500,SIZE1]],
          stretch: {left:[0xE0FB,SIZE6], rep:[0xE0FC,SIZE6], right:[0xE0FD,SIZE6]}
        },
        0x306: EXTRAH,
        0x30C:
        {
          dir: H,
          HW: [[342,MAIN], [608,SIZE1], [727,SIZE2], [870,SIZE3], [1041,SIZE4], [1249,SIZE5], [1496,SIZE6]]
        },
        0x311: EXTRAH,
        0x32C: EXTRAH,
        0x32D: EXTRAH,
        0x32E: EXTRAH,
        0x32F: EXTRAH,
        0x330: EXTRAH,
        0x332:
        {
          dir: H,
          HW: [[333,MARKS], [500,SIZE1]],
          stretch: {left:[0xE0F5,SIZE6], rep:[0xE0F6,SIZE6], right:[0xE0F7,SIZE6]}
        },
        0x333: EXTRAH,
        0x33F: EXTRAH,
        0x2015: {alias: 0x2212, dir: H},
        0x2016:
        {
          dir: V,
          HW: [[800,MAIN], [960,SIZE1], [1152,SIZE2], [1382,SIZE3], [1658,SIZE4], [1990,SIZE5], [2388,SIZE6]],
          stretch: {bot:[0xE12A,SIZE6], ext:[0xE12B,SIZE6], top:[0xE12C,SIZE6]}
        },
        0x2017: {alias: 0x2212, dir: H},
        0x203E: {alias: 0x2212, dir: H},
        0x2044:
        {
          dir: V,
          HW: [[800,MAIN], [1048,SIZE1], [1372,SIZE2], [1798,SIZE3], [2356,SIZE4], [3086,SIZE5], [4043,SIZE6]]
        },
        0x20D0: EXTRAH,
        0x20D1: EXTRAH,
        0x20D6: EXTRAH,
        0x20D7: EXTRAH,
        0x20E1: EXTRAH,
        0x20E9: EXTRAH,
        0x20EC: EXTRAH,
        0x20ED: EXTRAH,
        0x20EE: EXTRAH,
        0x20EF: EXTRAH,
        0x2140:
        {
          dir: V,
          HW: [[956,DOUBLESTRUCK], [1360,SIZE1]]
        },
        0x2190:
        {
          dir: H,
          HW: [[690,MAIN], [1010,SIZE1]],
          stretch: {left:[0xE023,SIZE6], rep:[0xE024,SIZE6], right:[0xE025,SIZE6]}
        },
        0x2191:
        {
          dir: V,
          HW: [[690,MAIN], [1010,SIZE1]],
          stretch: {bot:[0xE029,SIZE6], ext:[0xE02A,SIZE6], top:[0xE02B,SIZE6]}
        },
        0x2192:
        {
          dir: H,
          HW: [[690,MAIN], [1010,SIZE1]],
          stretch: {left:[0xE026,SIZE6], rep:[0xE027,SIZE6], right:[0xE028,SIZE6]}
        },
        0x2193:
        {
          dir: V,
          HW: [[690,MAIN], [1010,SIZE1]],
          stretch: {bot:[0xE02C,SIZE6], ext:[0xE02D,SIZE6], top:[0xE02E,SIZE6]}
        },
        0x2194:
        {
          dir: H,
          HW: [[880,MAIN], [1200,SIZE1]],
          stretch: {left:[0xE037,SIZE6], rep:[0xE038,SIZE6], right:[0xE039,SIZE6]}
        },
        0x2195:
        {
          dir: V,
          HW: [[880,MAIN], [1200,SIZE1]],
          stretch: {bot:[0xE03A,SIZE6], ext:[0xE03B,SIZE6], top:[0xE03C,SIZE6]}
        },
        0x2196: EXTRAV,
        0x2197: EXTRAV,
        0x2198: EXTRAV,
        0x2199: EXTRAV,
        0x219A: EXTRAH,
        0x219B: EXTRAH,
        0x219E: EXTRAH,
        0x219F: EXTRAV,
        0x21A0: EXTRAH,
        0x21A1: EXTRAV,
        0x21A2: EXTRAH,
        0x21A3: EXTRAH,
        0x21A4:
        {
          dir: H,
          HW: [[690,ARROWS], [1010,SIZE1]],
          stretch: {left:[0xE053,SIZE6], rep:[0xE054,SIZE6], right:[0xE055,SIZE6]}
        },
        0x21A5: EXTRAV,
        0x21A6:
        {
          dir: H,
          HW: [[690,MAIN], [1010,SIZE1]],
          stretch: {left:[0xE056,SIZE6], rep:[0xE057,SIZE6], right:[0xE058,SIZE6]}
        },
        0x21A7: EXTRAV,
        0x21A9: EXTRAH,
        0x21AA: EXTRAH,
        0x21AB: EXTRAH,
        0x21AC: EXTRAH,
        0x21AD: EXTRAH,
        0x21AE: EXTRAH,
        0x21B0: EXTRAV,
        0x21B1: EXTRAV,
        0x21B2: EXTRAV,
        0x21B3: EXTRAV,
        0x21B6: EXTRAH,
        0x21B7: EXTRAH,
        0x21BC: EXTRAH,
        0x21BD: EXTRAH,
        0x21BE: EXTRAV,
        0x21BF: EXTRAV,
        0x21C0: EXTRAH,
        0x21C1: EXTRAH,
        0x21C2: EXTRAV,
        0x21C3: EXTRAV,
        0x21C4: EXTRAH,
        0x21C5: EXTRAV,
        0x21C6: EXTRAH,
        0x21C7: EXTRAH,
        0x21C8: EXTRAV,
        0x21C9: EXTRAH,
        0x21CA: EXTRAV,
        0x21CB: EXTRAH,
        0x21CC: EXTRAH,
        0x21CD: EXTRAH,
        0x21CE: EXTRAH,
        0x21CF: EXTRAH,
        0x21D0:
        {
          dir: H,
          HW: [[690,MAIN], [1010,SIZE1]],
          stretch: {left:[0xE0A7,SIZE6], rep:[0xE0A8,SIZE6], right:[0xE0A9,SIZE6]}
        },
        0x21D1:
        {
          dir: V,
          HW: [[690,MAIN], [1010,SIZE1]],
          stretch: {bot:[0xE0AD,SIZE6], ext:[0xE0AE,SIZE6], top:[0xE0AF,SIZE6]}
        },
        0x21D2:
        {
          dir: H,
          HW: [[690,MAIN], [1010,SIZE1]],
          stretch: {left:[0xE0AA,SIZE6], rep:[0xE0AB,SIZE6], right:[0xE0AC,SIZE6]}
        },
        0x21D3:
        {
          dir: V,
          HW: [[690,MAIN], [1010,SIZE1]],
          stretch: {bot:[0xE0B0,SIZE6], ext:[0xE0B1,SIZE6], top:[0xE0B2,SIZE6]}
        },
        0x21D4:
        {
          dir: H,
          HW: [[880,MAIN], [1200,SIZE1]],
          stretch: {left:[0xE0B3,SIZE6], rep:[0xE0B4,SIZE6], right:[0xE0B5,SIZE6]}
        },
        0x21D5:
        {
          dir: V,
          HW: [[880,MAIN], [1200,SIZE1]],
          stretch: {bot:[0xE0B6,SIZE6], ext:[0xE0B7,SIZE6], top:[0xE0B8,SIZE6]}
        },
        0x21D6: EXTRAV,
        0x21D7: EXTRAV,
        0x21D8: EXTRAV,
        0x21D9: EXTRAV,
        0x21DA: EXTRAH,
        0x21DB: EXTRAH,
        0x21DC: EXTRAH,
        0x21DD: EXTRAH,
        0x21E6: EXTRAH,
        0x21E7: EXTRAV,
        0x21E8: EXTRAH,
        0x21E9: EXTRAV,
        0x21F3: EXTRAV,
        0x21F5: EXTRAV,
        0x21F6: EXTRAH,
        0x220F: EXTRAV,
        0x2210: EXTRAV,
        0x2211: EXTRAV,
        0x2212:
        {
          HW: [],
          stretch: {rep:[0x2212,MAIN,0,0,0,-.224,-.224]}
        },
        0x2215: {alias: 0x2044, dir: V},
        0x221A:
        {
          dir: V,
          HW: [[706,MAIN], [1090,SIZE1], [1474,SIZE2], [1858,SIZE3], [2242,SIZE4], [2626,SIZE5], [3010,SIZE6]],
          stretch: {bot:[0x23B7,SYMBOLS], ext:[0xE133,SIZE6], top:[0xE134,SIZE6]}
        },
        0x2223:
        {
          dir: V,
          HW: [[800,MAIN], [960,SIZE1], [1152,SIZE2], [1382,SIZE3], [1658,SIZE4], [1990,SIZE5], [2388,SIZE6]],
          stretch: {bot:[0xE004,SIZE6], ext:[0xE005,SIZE6], top:[0xE006,SIZE6]}
        },
        0x2225:
        {
          dir: V,
          HW: [[800,MAIN], [960,SIZE1], [1152,SIZE2], [1382,SIZE3], [1658,SIZE4], [1990,SIZE5], [2388,SIZE6]],
          stretch: {bot:[0xE12A,SIZE6], ext:[0xE12B,SIZE6], top:[0xE12C,SIZE6]}
        },
        0x222B: EXTRAV,
        0x222C: EXTRAV,
        0x222D: EXTRAV,
        0x222E: EXTRAV,
        0x222F: EXTRAV,
        0x2230: EXTRAV,
        0x2231: EXTRAV,
        0x2232: EXTRAV,
        0x2233: EXTRAV,
        0x2261: EXTRAH,
        0x2263: EXTRAH,
        0x22A2: EXTRAV,
        0x22A3: EXTRAV,
        0x22A4: EXTRAV,
        0x22A5: EXTRAV,
        0x22C0: EXTRAV,
        0x22C1: EXTRAV,
        0x22C2: EXTRAV,
        0x22C3: EXTRAV,
        0x2308:
        {
          dir: V,
          HW: [[818,MAIN], [979,SIZE1], [1171,SIZE2], [1402,SIZE3], [1678,SIZE4], [2011,SIZE5], [2410,SIZE6], [2780,SIZE6,1.154]],
          stretch: {ext:[0x23A2,SYMBOLS], top:[0x23A1,SYMBOLS]}
        },
        0x2309:
        {
          dir: V,
          HW: [[818,MAIN], [979,SIZE1], [1171,SIZE2], [1402,SIZE3], [1678,SIZE4], [2011,SIZE5], [2410,SIZE6], [2780,SIZE6,1.154]],
          stretch: {ext:[0x23A5,SYMBOLS], top:[0x23A4,SYMBOLS]}
        },
        0x230A:
        {
          dir: V,
          HW: [[818,MAIN], [979,SIZE1], [1171,SIZE2], [1402,SIZE3], [1678,SIZE4], [2011,SIZE5], [2410,SIZE6], [2780,SIZE6,1.154]],
          stretch: {bot:[0x23A3,SYMBOLS], ext:[0x23A2,SYMBOLS]}
        },
        0x230B:
        {
          dir: V,
          HW: [[818,MAIN], [979,SIZE1], [1171,SIZE2], [1402,SIZE3], [1678,SIZE4], [2011,SIZE5], [2410,SIZE6], [2780,SIZE6,1.154]],
          stretch: {bot:[0x23A6,SYMBOLS], ext:[0x23A5,SYMBOLS]}
        },
        0x2312: {alias: 0x23DC, dir:H},
        0x2322: {alias: 0x23DC, dir:H},
        0x2323: {alias: 0x23DD, dir:H},
        0x2329:
        {
          dir: V,
          HW: [[812,SYMBOLS], [1060,SIZE1], [1382,SIZE2], [1806,SIZE3], [2364,SIZE4], [3092,SIZE5], [4048,SIZE6]]
        },
        0x232A:
        {
          dir: V,
          HW: [[812,SYMBOLS], [1060,SIZE1], [1382,SIZE2], [1806,SIZE3], [2364,SIZE4], [3092,SIZE5], [4048,SIZE6]]
        },
        0x23AA:
        {
          dir: V,
          HW: [[596,SYMBOLS]],
          stretch: {ext:[0x23AA,SYMBOLS]}
        },
        0x23AF: {alias: 0x2212, dir: H},
        0x23B0:
        {
          dir: V,
          HW: [[607,SYMBOLS,null,0x23A7]],
          stretch: {top:[0x23A7,SYMBOLS], ext:[0x23AA,SYMBOLS], bot:[0x23AD,SYMBOLS]}
        },
        0x23B1:
        {
          dir: V,
          HW: [[607,SYMBOLS,null,0x23AB]],
          stretch: {top:[0x23AB,SYMBOLS], ext:[0x23AA,SYMBOLS], bot:[0x23A9,SYMBOLS]}
        },
        0x23B4: EXTRAH,
        0x23B5: EXTRAH,
        0x23D0:
        {
          dir: V,
          HW: [[800,MAIN,null,0x7C], [1350,MAIN,1.688,0x7C], [1827,MAIN,2.283,0x7C], [2303,MAIN,2.879,0x7C], [2780,MAIN,3.474,0x7C]],
          stretch: {ext:[0x7C,MAIN]}
        },
        0x23DC: EXTRAH,
        0x23DD: EXTRAH,
        0x23DE:
        {
          dir: H,
          HW: [[520,MAIN], [1018,SIZE1], [1519,SIZE2], [2019,SIZE3], [2519,SIZE4], [3019,SIZE5], [3519,SIZE6]],
          stretch: {left:[0xE10D,SIZE6], rep:[0xE10E,SIZE6], mid:[0xE10F,SIZE6], right:[0xE110,SIZE6]}
        },
        0x23DF:
        {
          dir: H,
          HW: [[520,MAIN], [1018,SIZE1], [1519,SIZE2], [2019,SIZE3], [2519,SIZE4], [3019,SIZE5], [3519,SIZE6]],
          stretch: {left:[0xE111,SIZE6], rep:[0xE112,SIZE6], mid:[0xE113,SIZE6], right:[0xE114,SIZE6]}
        },
        0x23E0: EXTRAH,
        0x23E1: EXTRAH,
        0x2500: {alias: 0x2212, dir: H},
        0x27A1: EXTRAH,
        0x27E6: EXTRAV,
        0x27E7: EXTRAV,
        0x27E8:
        {
          dir: V,
          HW: [[812,MAIN], [1060,SIZE1], [1382,SIZE2], [1806,SIZE3], [1827,SIZE3,1.012], [2364,SIZE4], [3092,SIZE5], [4048,SIZE6]]
        },
        0x27E9:
        {
          dir: V,
          HW: [[812,MAIN], [1060,SIZE1], [1382,SIZE2], [1806,SIZE3], [1827,SIZE3,1.012], [2364,SIZE4], [3092,SIZE5], [4048,SIZE6]]
        },
        0x27EA: EXTRAV,
        0x27EB: EXTRAV,
        0x27EE:
        {
          dir: V,
          HW: [[814,MAIN], [974,SIZE1], [1166,SIZE2], [1396,SIZE3], [1672,SIZE4], [2004,SIZE5], [2402,SIZE6]],
          stretch: {bot:[0xE101,SIZE6], ext:[0xE102,SIZE6], top:[0xE103,SIZE6]}
        },
        0x27EF:
        {
          dir: V,
          HW: [[814,MAIN], [974,SIZE1], [1166,SIZE2], [1396,SIZE3], [1672,SIZE4], [2004,SIZE5], [2402,SIZE6]],
          stretch: {bot:[0xE104,SIZE6], ext:[0xE105,SIZE6], top:[0xE106,SIZE6]}
        },
        0x27F5: {alias: 0x2190, dir: H},
        0x27F6: {alias: 0x2192, dir: H},
        0x27F7: {alias: 0x2194, dir: H},
        0x27F8: {alias: 0x21D0, dir: H},
        0x27F9: {alias: 0x21D2, dir: H},
        0x27FA: {alias: 0x21D4, dir: H},
        0x27FB: {alias: 0x21A4, dir: H},
        0x27FC: {alias: 0x21A6, dir: H},
        0x27FD: {alias: 0x2906, dir: H},
        0x27FE: {alias: 0x2907, dir: H},
        0x2906:
        {
          dir: H,
          HW: [[870,ARROWS], [1190,SIZE1]],
          stretch: {left:[0xE0C5,SIZE6], rep:[0xE0C6,SIZE6], right:[0xE0C7,SIZE6]}
        },
        0x2907:
        {
          dir: H,
          HW: [[870,ARROWS], [1190,SIZE1]],
          stretch: {left:[0xE0C8,SIZE6], rep:[0xE0C9,SIZE6], right:[0xE0CA,SIZE6]}
        },
        0x2A00: EXTRAV,
        0x2A01: EXTRAV,
        0x2A02: EXTRAV,
        0x2A03: EXTRAV,
        0x2A04: EXTRAV,
        0x2A05: EXTRAV,
        0x2A06: EXTRAV,
        0x2A09: EXTRAV,
        0x2A0C: EXTRAV,
        0x2A11: EXTRAV,
        0x2B04: EXTRAH,
        0x2B05: EXTRAH,
        0x2B06: EXTRAV,
        0x2B07: EXTRAV,
        0x2B0C: EXTRAH,
        0x2B0D: EXTRAV,
        0x2B31: EXTRAH,
        0x3008: {alias: 0x27E8, dir: V},
        0x3009: {alias: 0x27E9, dir: V},
        0xFE37: {alias: 0x23DE, dir: H},
        0xFE38: {alias: 0x23DF, dir: H}
      }

    }
  });
  MathJax.Hub.Register.LoadHook(SVG.fontDir+"/Main/Regular/Main.js",function () {
    SVG.FONTDATA.FONTS[MAIN][0x2212][0] = SVG.FONTDATA.FONTS[MAIN][0x002B][0]; // - needs height and depth of +
    SVG.FONTDATA.FONTS[MAIN][0x2212][1] = SVG.FONTDATA.FONTS[MAIN][0x002B][1]; // - needs height and depth of +
  });
  MathJax.Hub.Register.LoadHook(SVG.fontDir+"/Size1/Regular/Main.js",function () {
    var i;
    for (i = 0x222B; i <= 0x222D; i++)
      SVG.FONTDATA.FONTS[SIZE1][i][2] -= 200;
    for (i = 0x222E; i <= 0x2231; i++)
      SVG.FONTDATA.FONTS[SIZE1][i][2] -= 150;
  });
  AJAX.loadComplete(SVG.fontDir + "/fontdata.js");

})(MathJax.OutputJax.SVG,MathJax.ElementJax.mml,MathJax.Ajax,MathJax.Hub);
