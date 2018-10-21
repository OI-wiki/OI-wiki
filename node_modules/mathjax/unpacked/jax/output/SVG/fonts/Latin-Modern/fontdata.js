/*************************************************************
 *
 *  MathJax/jax/output/SVG/fonts/Latin-Modern/fontdata.js
 *  
 *  Initializes the SVG OutputJax to use the Latin-Modern fonts

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

  var H = "H", V = "V", EXTRAH = {load:"extra", dir:H}, EXTRAV = {load:"extra", dir:V};

  SVG.Augment({
    FONTDATA: {
      version: VERSION,


      baselineskip: 1200,
      lineH: 800, lineD: 200,

      FONTS: {
        "LatinModernMathJax_Alphabets": "Alphabets/Regular/Main.js",
        "LatinModernMathJax_Arrows": "Arrows/Regular/Main.js",
        "LatinModernMathJax_DoubleStruck": "DoubleStruck/Regular/Main.js",
        "LatinModernMathJax_Fraktur": "Fraktur/Regular/Main.js",
        "LatinModernMathJax_Latin": "Latin/Regular/Main.js",
        "LatinModernMathJax_Main": "Main/Regular/Main.js",
        "LatinModernMathJax_Marks": "Marks/Regular/Main.js",
        "LatinModernMathJax_Misc": "Misc/Regular/Main.js",
        "LatinModernMathJax_Monospace": "Monospace/Regular/Main.js",
        "LatinModernMathJax_NonUnicode": "NonUnicode/Regular/Main.js",
        "LatinModernMathJax_Normal": "Normal/Regular/Main.js",
        "LatinModernMathJax_Operators": "Operators/Regular/Main.js",
        "LatinModernMathJax_SansSerif": "SansSerif/Regular/Main.js",
        "LatinModernMathJax_Script": "Script/Regular/Main.js",
        "LatinModernMathJax_Shapes": "Shapes/Regular/Main.js",
        "LatinModernMathJax_Size1": "Size1/Regular/Main.js",
        "LatinModernMathJax_Size2": "Size2/Regular/Main.js",
        "LatinModernMathJax_Size3": "Size3/Regular/Main.js",
        "LatinModernMathJax_Size4": "Size4/Regular/Main.js",
        "LatinModernMathJax_Size5": "Size5/Regular/Main.js",
        "LatinModernMathJax_Size6": "Size6/Regular/Main.js",
        "LatinModernMathJax_Size7": "Size7/Regular/Main.js",
        "LatinModernMathJax_Symbols": "Symbols/Regular/Main.js",
        "LatinModernMathJax_Variants": "Variants/Regular/Main.js"
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
          "-Latin-Modern-variant": {fonts: [VARIANTS,MAIN,NORMAL,MONOSPACE,LATIN,ALPHABETS,MARKS,ARROWS,OPERATORS,SYMBOLS,SHAPES,MISC,NONUNICODE,SIZE1]},
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
          HW: [[996,MAIN], [1094,SIZE1], [1194,SIZE2], [1444,SIZE3], [1792,SIZE4], [2092,SIZE5], [2392,SIZE6], [2990,SIZE7]],
          stretch: {bot:[0x239D,SYMBOLS], ext:[0x239C,SYMBOLS], top:[0x239B,SYMBOLS]}
        },
        0x29:
        {
          dir: V,
          HW: [[996,MAIN], [1094,SIZE1], [1194,SIZE2], [1444,SIZE3], [1792,SIZE4], [2092,SIZE5], [2392,SIZE6], [2990,SIZE7]],
          stretch: {bot:[0x23A0,SYMBOLS], ext:[0x239F,SYMBOLS], top:[0x239E,SYMBOLS]}
        },
        0x2D: {alias: 0x2212, dir: H},
        0x2F:
        {
          dir: V,
          HW: [[1000,MAIN], [1310,SIZE1], [1716,SIZE2], [1771,SIZE2,1.032], [2248,SIZE3], [2944,SIZE4], [3858,SIZE5], [5054,SIZE6], [6620,SIZE7]]
        },
        0x3D:
        {
          dir: H,
          HW: [[666,MAIN]],
          stretch: {left:[0xE000,SIZE7], rep:[0xE001,SIZE7], right:[0xE002,SIZE7]}
        },
        0x5B:
        {
          dir: V,
          HW: [[1000,MAIN], [1100,SIZE1], [1200,SIZE2], [1450,SIZE3], [1800,SIZE4], [2100,SIZE5], [2400,SIZE6], [3000,SIZE7]],
          stretch: {bot:[0x23A3,SYMBOLS], ext:[0x23A2,SYMBOLS], top:[0x23A1,SYMBOLS]}
        },
        0x5C:
        {
          dir: V,
          HW: [[1000,MAIN], [1310,SIZE1], [1716,SIZE2], [1771,SIZE2,1.032], [2248,SIZE3], [2944,SIZE4], [3858,SIZE5], [5054,SIZE6], [6620,SIZE7]]
        },
        0x5D:
        {
          dir: V,
          HW: [[1000,MAIN], [1100,SIZE1], [1200,SIZE2], [1450,SIZE3], [1800,SIZE4], [2100,SIZE5], [2400,SIZE6], [3000,SIZE7]],
          stretch: {bot:[0x23A6,SYMBOLS], ext:[0x23A5,SYMBOLS], top:[0x23A4,SYMBOLS]}
        },
        0x5E: {alias: 0x302, dir: H},
        0x5F: {alias: 0x332, dir: H},
        0x7B:
        {
          dir: V,
          HW: [[1000,MAIN], [1100,SIZE1], [1200,SIZE2], [1450,SIZE3], [1800,SIZE4], [2100,SIZE5], [2400,SIZE6], [3000,SIZE7]],
          stretch: {bot:[0x23A9,SYMBOLS], ext:[0xE003,SIZE7], mid:[0x23A8,SYMBOLS], top:[0x23A7,SYMBOLS]}
        },
        0x7C:
        {
          dir: V,
          HW: [[1000,MAIN], [1202,SIZE1], [1444,SIZE2], [1734,SIZE3], [2084,SIZE4], [2502,SIZE5], [3004,SIZE6], [3606,SIZE7]],
          stretch: {bot:[0xE004,SIZE7], ext:[0xE005,SIZE7], top:[0xE006,SIZE7]}
        },
        0x7D:
        {
          dir: V,
          HW: [[1000,MAIN], [1100,SIZE1], [1200,SIZE2], [1450,SIZE3], [1800,SIZE4], [2100,SIZE5], [2400,SIZE6], [3000,SIZE7]],
          stretch: {bot:[0x23AD,SYMBOLS], ext:[0xE007,SIZE7], mid:[0x23AC,SYMBOLS], top:[0x23AB,SYMBOLS]}
        },
        0x7E: {alias: 0x303, dir: H},
        0xAF: {alias: 0x332, dir: H},
        0x2C6: {alias: 0x302, dir: H},
        0x2C9: {alias: 0x2212, dir: H},
        0x2DC: {alias: 0x303, dir: H},
        0x302:
        {
          dir: H,
          HW: [[364,MAIN], [644,SIZE1], [768,SIZE2], [919,SIZE3], [1100,SIZE4], [1320,SIZE5], [1581,SIZE6], [1896,SIZE7]]
        },
        0x303:
        {
          dir: H,
          HW: [[370,MAIN], [652,SIZE1], [778,SIZE2], [931,SIZE3], [1115,SIZE4], [1335,SIZE5], [1599,SIZE6], [1915,SIZE7]]
        },
        0x2212:
        {
          HW: [],
          stretch: {rep:[0x2212,MAIN,0,0,0,-.31,-.31]}
        },
        0x306: EXTRAH,
        0x30C:
        {
          dir: H,
          HW: [[364,MAIN], [644,SIZE1], [768,SIZE2], [919,SIZE3], [1100,SIZE4], [1320,SIZE5], [1581,SIZE6], [1896,SIZE7]]
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
          HW: [[392,MARKS], [568,SIZE1]],
          stretch: {left:[0xE0F5,SIZE7], rep:[0xE0F6,SIZE7], right:[0xE0F7,SIZE7]}
        },
        0x333: EXTRAH,
        0x33F: EXTRAH,
        0x2015: {alias: 0x2212, dir: H},
        0x2016:
        {
          dir: V,
          HW: [[1000,MAIN], [1202,SIZE1], [1444,SIZE2], [1734,SIZE3], [2084,SIZE4], [2502,SIZE5], [3004,SIZE6], [3606,SIZE7]],
          stretch: {bot:[0xE12A,SIZE7], ext:[0xE12B,SIZE7], top:[0xE12C,SIZE7]}
        },
        0x2017: {alias: 0x2212, dir: H},
        0x203E: {alias: 0x2212, dir: H},
        0x2044:
        {
          dir: V,
          HW: [[1000,MAIN], [1310,SIZE1], [1716,SIZE2], [2248,SIZE3], [2944,SIZE4], [3858,SIZE5], [5054,SIZE6], [6620,SIZE7]]
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
        0x2190:
        {
          dir: H,
          HW: [[885,MAIN], [1351,SIZE1]],
          stretch: {left:[0xE023,SIZE7], rep:[0xE024,SIZE7], right:[0xE025,SIZE7]}
        },
        0x2191:
        {
          dir: V,
          HW: [[882,MAIN], [1348,SIZE1]],
          stretch: {bot:[0xE029,SIZE7], ext:[0xE02A,SIZE7], top:[0xE02B,SIZE7]}
        },
        0x2192:
        {
          dir: H,
          HW: [[885,MAIN], [1351,SIZE1]],
          stretch: {left:[0xE026,SIZE7], rep:[0xE027,SIZE7], right:[0xE028,SIZE7]}
        },
        0x2193:
        {
          dir: V,
          HW: [[882,MAIN], [1348,SIZE1]],
          stretch: {bot:[0xE02C,SIZE7], ext:[0xE02D,SIZE7], top:[0xE02E,SIZE7]}
        },
        0x2194:
        {
          dir: H,
          HW: [[884,MAIN], [1330,SIZE1]],
          stretch: {left:[0xE037,SIZE7], rep:[0xE038,SIZE7], right:[0xE039,SIZE7]}
        },
        0x2195:
        {
          dir: V,
          HW: [[1014,MAIN], [1014,SIZE1]],
          stretch: {bot:[0xE03A,SIZE7], ext:[0xE03B,SIZE7], top:[0xE03C,SIZE7]}
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
          HW: [[865,ARROWS], [1331,SIZE1]],
          stretch: {left:[0xE053,SIZE7], rep:[0xE054,SIZE7], right:[0xE055,SIZE7]}
        },
        0x21A5: EXTRAV,
        0x21A6:
        {
          dir: H,
          HW: [[865,MAIN], [1331,SIZE1]],
          stretch: {left:[0xE056,SIZE7], rep:[0xE057,SIZE7], right:[0xE058,SIZE7]}
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
          HW: [[879,MAIN], [1345,SIZE1]],
          stretch: {left:[0xE0A7,SIZE7], rep:[0xE0A8,SIZE7], right:[0xE0A9,SIZE7]}
        },
        0x21D1:
        {
          dir: V,
          HW: [[879,MAIN], [1345,SIZE1]],
          stretch: {bot:[0xE0AD,SIZE7], ext:[0xE0AE,SIZE7], top:[0xE0AF,SIZE7]}
        },
        0x21D2:
        {
          dir: H,
          HW: [[879,MAIN], [1345,SIZE1]],
          stretch: {left:[0xE0AA,SIZE7], rep:[0xE0AB,SIZE7], right:[0xE0AC,SIZE7]}
        },
        0x21D3:
        {
          dir: V,
          HW: [[879,MAIN], [1345,SIZE1]],
          stretch: {bot:[0xE0B0,SIZE7], ext:[0xE0B1,SIZE7], top:[0xE0B2,SIZE7]}
        },
        0x21D4:
        {
          dir: H,
          HW: [[956,MAIN], [1422,SIZE1]],
          stretch: {left:[0xE0B3,SIZE7], rep:[0xE0B4,SIZE7], right:[0xE0B5,SIZE7]}
        },
        0x21D5:
        {
          dir: V,
          HW: [[956,MAIN], [1422,SIZE1]],
          stretch: {bot:[0xE0B6,SIZE7], ext:[0xE0B7,SIZE7], top:[0xE0B8,SIZE7]}
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
          dir: H,
          HW: [[666,MAIN]],
          stretch: {left:[0xE127,SIZE7], rep:[0xE128,SIZE7], right:[0xE129,SIZE7]}
        },
        0x2215: {alias: 0x2044, dir: V},
        0x221A:
        {
          dir: V,
          HW: [[1000,MAIN], [1200,SIZE1], [1800,SIZE2], [2400,SIZE3], [3000,SIZE4]],
          stretch: {bot:[0x23B7,SYMBOLS], ext:[0xE133,SIZE7], top:[0xE134,SIZE7]}
        },
        0x2223:
        {
          dir: V,
          HW: [[1000,MAIN], [1202,SIZE1], [1444,SIZE2], [1734,SIZE3], [2084,SIZE4], [2502,SIZE5], [3004,SIZE6], [3606,SIZE7]],
          stretch: {bot:[0xE004,SIZE7], ext:[0xE005,SIZE7], top:[0xE006,SIZE7]}
        },
        0x2225:
        {
          dir: V,
          HW: [[1000,MAIN], [1202,SIZE1], [1444,SIZE2], [1734,SIZE3], [2084,SIZE4], [2502,SIZE5], [3004,SIZE6], [3606,SIZE7]],
          stretch: {bot:[0xE12A,SIZE7], ext:[0xE12B,SIZE7], top:[0xE12C,SIZE7]}
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
          HW: [[1000,MAIN], [1100,SIZE1], [1200,SIZE2], [1450,SIZE3], [1800,SIZE4], [2100,SIZE5], [2400,SIZE6], [3000,SIZE7]],
          stretch: {ext:[0x23A2,SYMBOLS], top:[0x23A1,SYMBOLS]}
        },
        0x2309:
        {
          dir: V,
          HW: [[1000,MAIN], [1100,SIZE1], [1200,SIZE2], [1450,SIZE3], [1800,SIZE4], [2100,SIZE5], [2400,SIZE6], [3000,SIZE7]],
          stretch: {ext:[0x23A5,SYMBOLS], top:[0x23A4,SYMBOLS]}
        },
        0x230A:
        {
          dir: V,
          HW: [[1000,MAIN], [1100,SIZE1], [1200,SIZE2], [1450,SIZE3], [1800,SIZE4], [2100,SIZE5], [2400,SIZE6], [3000,SIZE7]],
          stretch: {bot:[0x23A3,SYMBOLS], ext:[0x23A2,SYMBOLS]}
        },
        0x230B:
        {
          dir: V,
          HW: [[1000,MAIN], [1100,SIZE1], [1200,SIZE2], [1450,SIZE3], [1800,SIZE4], [2100,SIZE5], [2400,SIZE6], [3000,SIZE7]],
          stretch: {bot:[0x23A6,SYMBOLS], ext:[0x23A5,SYMBOLS]}
        },
        0x2312: {alias: 0x23DC, dir:H},
        0x2322: {alias: 0x23DC, dir:H},
        0x2323: {alias: 0x23DD, dir:H},
        0x2329:
        {
          dir: V,
          HW: [[1000,SYMBOLS], [1100,SIZE1], [1200,SIZE2], [1450,SIZE3], [1800,SIZE4], [2100,SIZE5], [2400,SIZE6], [3000,SIZE7]]
        },
        0x232A:
        {
          dir: V,
          HW: [[1000,SYMBOLS], [1100,SIZE1], [1200,SIZE2], [1450,SIZE3], [1800,SIZE4], [2100,SIZE5], [2400,SIZE6], [3000,SIZE7]]
        },
        0x23AA:
        {
          dir: V,
          HW: [[748,SYMBOLS]],
          stretch: {ext:[0x23AA,SYMBOLS]}
        },
        0x23AF: {alias: 0x2212, dir: H},
        0x23B0:
        {
          dir: V,
          HW: [[750,SYMBOLS,null,0x23A7]],
          stretch: {top:[0x23A7,SYMBOLS], ext:[0x23AA,SYMBOLS], bot:[0x23AD,SYMBOLS]}
        },
        0x23B1:
        {
          dir: V,
          HW: [[750,SYMBOLS,null,0x23AB]],
          stretch: {top:[0x23AB,SYMBOLS], ext:[0x23AA,SYMBOLS], bot:[0x23A9,SYMBOLS]}
        },
        0x23B4: EXTRAH,
        0x23B5: EXTRAH,
        0x23D0:
        {
          dir: V,
          HW: [[1000,MAIN,null,0x7C], [1309,MAIN,1.309,0x7C], [1771,MAIN,1.771,0x7C], [2233,MAIN,2.233,0x7C], [2695,MAIN,2.695,0x7C]],
          stretch: {ext:[0x7C,MAIN]}
        },
        0x23DC: EXTRAH,
        0x23DD: EXTRAH,
        0x23DE:
        {
          dir: H,
          HW: [[492,MAIN], [993,SIZE1], [1494,SIZE2], [1996,SIZE3], [2498,SIZE4], [3000,SIZE5], [3502,SIZE6], [4006,SIZE7]],
          stretch: {left:[0xE10D,SIZE7], rep:[0xE10E,SIZE7], mid:[0xE10F,SIZE7], right:[0xE110,SIZE7]}
        },
        0x23DF:
        {
          dir: H,
          HW: [[492,MAIN], [993,SIZE1], [1494,SIZE2], [1996,SIZE3], [2498,SIZE4], [3000,SIZE5], [3502,SIZE6], [4006,SIZE7]],
          stretch: {left:[0xE111,SIZE7], rep:[0xE112,SIZE7], mid:[0xE113,SIZE7], right:[0xE114,SIZE7]}
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
          HW: [[1000,MAIN], [1100,SIZE1], [1200,SIZE2], [1450,SIZE3], [1800,SIZE4], [2100,SIZE5], [2400,SIZE6], [3000,SIZE7]]
        },
        0x27E9:
        {
          dir: V,
          HW: [[1000,MAIN], [1100,SIZE1], [1200,SIZE2], [1450,SIZE3], [1800,SIZE4], [2100,SIZE5], [2400,SIZE6], [3000,SIZE7]]
        },
        0x27EA: EXTRAV,
        0x27EB: EXTRAV,
        0x27EE:
        {
          dir: V,
          HW: [[1024,MAIN], [1126,SIZE1], [1228,SIZE2], [1482,SIZE3], [1836,SIZE4], [2140,SIZE5], [2444,SIZE6], [3052,SIZE7]],
          stretch: {bot:[0xE101,SIZE7], ext:[0xE102,SIZE7], top:[0xE103,SIZE7]}
        },
        0x27EF:
        {
          dir: V,
          HW: [[1024,MAIN], [1126,SIZE1], [1228,SIZE2], [1482,SIZE3], [1836,SIZE4], [2140,SIZE5], [2444,SIZE6], [3052,SIZE7]],
          stretch: {bot:[0xE104,SIZE7], ext:[0xE105,SIZE7], top:[0xE106,SIZE7]}
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
          HW: [[879,ARROWS], [1325,SIZE1]],
          stretch: {left:[0xE0C5,SIZE7], rep:[0xE0C6,SIZE7], right:[0xE0C7,SIZE7]}
        },
        0x2907:
        {
          dir: H,
          HW: [[879,ARROWS], [1325,SIZE1]],
          stretch: {left:[0xE0C8,SIZE7], rep:[0xE0C9,SIZE7], right:[0xE0CA,SIZE7]}
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
  MathJax.Hub.Register.LoadHook(SVG.fontDir+"/Size7/Regular/Main.js",function () {
    var u;
    u = SVG.FONTDATA.DELIMITERS[0x23DE].stretch.rep[0];
    SVG.FONTDATA.FONTS[SIZE7][u][0] += 200;  // adjust height for brace extender
    SVG.FONTDATA.FONTS[SIZE7][u][1] += 200;  // adjust depth for brace extender
    u = SVG.FONTDATA.DELIMITERS[0x23DF].stretch.rep[0];
    SVG.FONTDATA.FONTS[SIZE7][u][0] += 200;  // adjust height for brace extender
    SVG.FONTDATA.FONTS[SIZE7][u][1] += 200;  // adjust depth for brace extender
  });
  MathJax.Hub.Register.LoadHook(SVG.fontDir+"/Size1/Regular/Main.js",function () {
    SVG.FONTDATA.FONTS[SIZE1][0x222B][2] -= 425;
    SVG.FONTDATA.FONTS[SIZE1][0x222C][2] -= 425;
    SVG.FONTDATA.FONTS[SIZE1][0x222D][2] -= 425;
    SVG.FONTDATA.FONTS[SIZE1][0x222E][2] -= 425;
    SVG.FONTDATA.FONTS[SIZE1][0x222F][2] -= 425;
    SVG.FONTDATA.FONTS[SIZE1][0x2230][2] -= 425;
    SVG.FONTDATA.FONTS[SIZE1][0x2231][2] -= 425;
    SVG.FONTDATA.FONTS[SIZE1][0x2232][2] -= 425;
    SVG.FONTDATA.FONTS[SIZE1][0x2233][2] -= 425;
    SVG.FONTDATA.FONTS[SIZE1][0x2A0C][2] -= 425;
    SVG.FONTDATA.FONTS[SIZE1][0x2A11][2] -= 425;
  });
  AJAX.loadComplete(SVG.fontDir + "/fontdata.js");

})(MathJax.OutputJax.SVG,MathJax.ElementJax.mml,MathJax.Ajax,MathJax.Hub);
