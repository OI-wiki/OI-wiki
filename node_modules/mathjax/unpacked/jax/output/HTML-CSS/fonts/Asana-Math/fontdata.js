/*************************************************************
 *
 *  MathJax/jax/output/HTML-CSS/fonts/Asana-Math/fontdata.js
 *  
 *  Initializes the HTML-CSS OutputJax to use the Asana-Math fonts

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

(function (HTMLCSS,MML,AJAX) {

  var VERSION = "2.7.5";

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

  var H = "H", V = "V", EXTRAH = {load:"extra", dir:H}, EXTRAV = {load:"extra", dir:V};

  HTMLCSS.Augment({
    FONTDATA: {
      version: VERSION,


      TeX_factor: 1.058,
      baselineskip: 1.200,
      lineH: 0.800, lineD: 0.200,

      hasStyleChar: true,  // char 0xEFFD encodes font style

      FONTS: {
        "AsanaMathJax_Alphabets": "Alphabets/Regular/Main.js",
        "AsanaMathJax_Arrows": "Arrows/Regular/Main.js",
        "AsanaMathJax_DoubleStruck": "DoubleStruck/Regular/Main.js",
        "AsanaMathJax_Fraktur": "Fraktur/Regular/Main.js",
        "AsanaMathJax_Latin": "Latin/Regular/Main.js",
        "AsanaMathJax_Main": "Main/Regular/Main.js",
        "AsanaMathJax_Marks": "Marks/Regular/Main.js",
        "AsanaMathJax_Misc": "Misc/Regular/Main.js",
        "AsanaMathJax_Monospace": "Monospace/Regular/Main.js",
        "AsanaMathJax_NonUnicode": "NonUnicode/Regular/Main.js",
        "AsanaMathJax_Normal": "Normal/Regular/Main.js",
        "AsanaMathJax_Operators": "Operators/Regular/Main.js",
        "AsanaMathJax_SansSerif": "SansSerif/Regular/Main.js",
        "AsanaMathJax_Script": "Script/Regular/Main.js",
        "AsanaMathJax_Shapes": "Shapes/Regular/Main.js",
        "AsanaMathJax_Size1": "Size1/Regular/Main.js",
        "AsanaMathJax_Size2": "Size2/Regular/Main.js",
        "AsanaMathJax_Size3": "Size3/Regular/Main.js",
        "AsanaMathJax_Size4": "Size4/Regular/Main.js",
        "AsanaMathJax_Size5": "Size5/Regular/Main.js",
        "AsanaMathJax_Size6": "Size6/Regular/Main.js",
        "AsanaMathJax_Symbols": "Symbols/Regular/Main.js",
        "AsanaMathJax_Variants": "Variants/Regular/Main.js"
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
          "-Asana-Math-variant": {fonts: [MAIN,NORMAL,MONOSPACE,LATIN,ALPHABETS,MARKS,ARROWS,OPERATORS,SYMBOLS,SHAPES,MISC,VARIANTS,NONUNICODE,SIZE1]},
          "-tex-caligraphic": {offsetA: 0xE20A, noLowerCase: 1, fonts: [VARIANTS,MAIN,NORMAL,MONOSPACE,LATIN,ALPHABETS,MARKS,ARROWS,OPERATORS,SYMBOLS,SHAPES,MISC,NONUNICODE,SIZE1], italic: true},
          "-tex-oldstyle": {offsetN: 0xE200, fonts: [VARIANTS,MAIN,NORMAL,MONOSPACE,LATIN,ALPHABETS,MARKS,ARROWS,OPERATORS,SYMBOLS,SHAPES,MISC,NONUNICODE,SIZE1]},
          "-tex-caligraphic-bold": {offsetA: 0xE224, noLowerCase: 1, fonts: [VARIANTS,MAIN,NORMAL,MONOSPACE,LATIN,ALPHABETS,MARKS,ARROWS,OPERATORS,SYMBOLS,SHAPES,MISC,NONUNICODE,SIZE1], italic: true, bold: true},
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
        0x25C3: 0x25C1,
        0xFE38: 0x23DF,
        0x3008: 0x27E8,
        0x3009: 0x27E9,
        0x25AA: 0x25A0,
        0x00AF: 0x0304,
        0x20F0: 0x002A,
        0x2758: 0x2223,
        0x03D2: 0x03A5,
        0x25B4: 0x25B2,
        0x25B5: 0x25B3,
        0xFE37: 0x23DE,
        0x25B8: 0x25B6,
        0x02B9: 0x2032,
        0x25BE: 0x25BC,
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
          HW: [[0.941,MAIN], [1.471,SIZE1], [2.041,SIZE2], [2.552,SIZE3], [2.615,SIZE3,1.025]],
          stretch: {bot:[0x239D,SYMBOLS], ext:[0x239C,SYMBOLS], top:[0x239B,SYMBOLS]}
        },
        0x29:
        {
          dir: V,
          HW: [[0.941,MAIN], [1.471,SIZE1], [2.041,SIZE2], [2.552,SIZE3], [2.615,SIZE3,1.025]],
          stretch: {bot:[0x23A0,SYMBOLS], ext:[0x239F,SYMBOLS], top:[0x239E,SYMBOLS]}
        },
        0x2D: {alias: 0x2212, dir: H},
        0x2F: {alias: 0x2044, dir: H},
        0x3D:
        {
          dir: H,
          HW: [[0.539,MAIN]],
          stretch: {rep:[0x3D,MAIN]}
        },
        0x5B:
        {
          dir: V,
          HW: [[0.910,MAIN], [1.476,SIZE1], [2.045,SIZE2], [2.556,SIZE3], [2.615,SIZE3,1.023]],
          stretch: {bot:[0x23A3,SYMBOLS], ext:[0x23A2,SYMBOLS], top:[0x23A1,SYMBOLS]}
        },
        0x5C:
        {
          dir: V,
          HW: [[0.883,MAIN], [1.270,MAIN,1.439], [1.719,MAIN,1.946], [2.167,MAIN,2.454], [2.615,MAIN,2.961]]
        },
        0x5D:
        {
          dir: V,
          HW: [[0.910,MAIN], [1.476,SIZE1], [2.045,SIZE2], [2.556,SIZE3], [2.615,SIZE3,1.023]],
          stretch: {bot:[0x23A6,SYMBOLS], ext:[0x23A5,SYMBOLS], top:[0x23A4,SYMBOLS]}
        },
        0x5E: {alias: 0x302, dir: H},
        0x5F: {alias: 0x332, dir: H},
        0x7B:
        {
          dir: V,
          HW: [[0.901,MAIN], [1.471,SIZE1], [2.041,SIZE2], [2.552,SIZE3], [2.615,SIZE3,1.025]],
          stretch: {bot:[0x23A9,SYMBOLS], ext:[0x23AA,SYMBOLS], mid:[0x23A8,SYMBOLS], top:[0x23A7,SYMBOLS]}
        },
        0x7C:
        {
          dir: V,
          HW: [[0.885,MAIN], [1.275,SIZE1], [1.555,SIZE2], [1.897,SIZE3], [2.315,SIZE4], [2.712,SIZE5], [3.177,SIZE6]],
          stretch: {ext:[0xE000,SIZE6], top:[0xE000,SIZE6]}
        },
        0x7D:
        {
          dir: V,
          HW: [[0.901,MAIN], [1.471,SIZE1], [2.041,SIZE2], [2.552,SIZE3], [2.615,SIZE3,1.025]],
          stretch: {bot:[0x23AD,SYMBOLS], ext:[0x23AA,SYMBOLS], mid:[0x23AC,SYMBOLS], top:[0x23AB,SYMBOLS]}
        },
        0x7E: {alias: 0x303, dir: H},
        0xAF: {alias: 0x2212, dir: H},
        0x2C6: {alias: 0x302, dir: H},
        0x2C9: {alias: 0x2212, dir: H},
        0x2DC: {alias: 0x303, dir: H},
        0x302:
        {
          dir: H,
          HW: [[0.312,MAIN], [0.453,SIZE1], [0.633,SIZE2], [1.055,SIZE3], [2.017,SIZE4], [3.026,SIZE5]]
        },
        0x303:
        {
          dir: H,
          HW: [[0.330,MAIN], [0.701,SIZE1], [1.053,SIZE2], [1.403,SIZE3], [1.865,SIZE4], [2.797,SIZE5]]
        },
        0x305:
        {
          dir: H,
          HW: [[0.433,MARKS], [0.511,SIZE1], [0.675,SIZE2], [1.127,SIZE3]],
          stretch: {rep:[0xE001,SIZE6], right:[0xE001,SIZE6]}
        },
        0x306: EXTRAH,
        0x30C:
        {
          dir: H,
          HW: [[0.312,MAIN], [0.737,SIZE1], [1.105,SIZE2], [1.474,SIZE3], [1.960,SIZE4], [2.940,SIZE5]]
        },
        0x332:
        {
          dir: H,
          HW: [[0.433,MARKS], [0.511,SIZE1], [0.675,SIZE2], [1.127,SIZE3]],
          stretch: {rep:[0xE002,SIZE6], right:[0xE002,SIZE6]}
        },
        0x333: EXTRAH,
        0x33F: EXTRAH,
        0x2015: {alias: 0x2212, dir: H},
        0x2016:
        {
          dir: V,
          HW: [[0.885,MAIN], [1.275,SIZE1], [1.555,SIZE2], [1.897,SIZE3], [2.315,SIZE4]],
          stretch: {ext:[0xE005,SIZE6], top:[0xE005,SIZE6]}
        },
        0x2017: {alias: 0x2212, dir: H},
        0x203E: {alias: 0x2212, dir: H},
        0x2044:
        {
          dir: V,
          HW: [[0.837,MAIN], [1.205,SIZE1], [1.471,SIZE2], [1.795,SIZE3], [2.189,SIZE4], [2.615,SIZE4,1.195]]
        },
        0x2045: EXTRAV,
        0x2046: EXTRAV,
        0x20D0: EXTRAH,
        0x20D1: EXTRAH,
        0x20D6: EXTRAH,
        0x20D7: EXTRAH,
        0x20E1: EXTRAH,
        0x20E9: EXTRAH,
        0x20EE: EXTRAH,
        0x20EF: EXTRAH,
        0x2190:
        {
          dir: H,
          HW: [[0.884,MAIN]],
          stretch: {left:[0xE013,SIZE6], rep:[0x23AF,SYMBOLS], right:[0xE014,SIZE6]}
        },
        0x2191:
        {
          dir: V,
          HW: [[0.885,MAIN]],
          stretch: {ext:[0xE015,SIZE6], top:[0x2191,MAIN]}
        },
        0x2192:
        {
          dir: H,
          HW: [[0.884,MAIN]],
          stretch: {left:[0xE016,SIZE6], rep:[0x23AF,SYMBOLS], right:[0xE017,SIZE6]}
        },
        0x2193:
        {
          dir: V,
          HW: [[0.885,MAIN]],
          stretch: {bot:[0x2193,MAIN], ext:[0xE015,SIZE6]}
        },
        0x2194:
        {
          dir: H,
          HW: [[0.884,MAIN]],
          stretch: {left:[0xE013,SIZE6], rep:[0x23AF,SYMBOLS], right:[0xE017,SIZE6]}
        },
        0x2195:
        {
          dir: V,
          HW: [[0.884,MAIN]],
          stretch: {top:[0x2191,MAIN], ext:[0xE015,SIZE6], bot:[0x2193,MAIN]}
        },
        0x21A4:
        {
          dir: H,
          HW: [[0.942,ARROWS]],
          stretch: {left:[0xE013,SIZE6], rep:[0x23AF,SYMBOLS], right:[0xE018,SIZE6]}
        },
        0x21A6:
        {
          dir: H,
          HW: [[0.942,MAIN]],
          stretch: {left:[0xE019,SIZE6], rep:[0x23AF,SYMBOLS], right:[0xE017,SIZE6]}
        },
        0x21A9: EXTRAH,
        0x21AA: EXTRAH,
        0x21D0:
        {
          dir: H,
          HW: [[0.884,MAIN]],
          stretch: {left:[0xE01C,SIZE6], rep:[0xE01D,SIZE6], right:[0xE01E,SIZE6]}
        },
        0x21D1:
        {
          dir: V,
          HW: [[0.885,MAIN]],
          stretch: {ext:[0xE01F,SIZE6], top:[0x21D1,MAIN]}
        },
        0x21D2:
        {
          dir: H,
          HW: [[0.884,MAIN]],
          stretch: {left:[0xE020,SIZE6], rep:[0xE01D,SIZE6], right:[0xE021,SIZE6]}
        },
        0x21D3:
        {
          dir: V,
          HW: [[0.885,MAIN]],
          stretch: {bot:[0x21D3,MAIN], ext:[0xE01F,SIZE6]}
        },
        0x21D4:
        {
          dir: H,
          HW: [[0.895,MAIN]],
          stretch: {left:[0xE01C,SIZE6], rep:[0xE01D,SIZE6], right:[0xE021,SIZE6]}
        },
        0x21D5:
        {
          dir: V,
          HW: [[0.884,MAIN,null,0x2195]],
          stretch: {top:[0x21D1,MAIN], ext:[0xE01F,SIZE6], bot:[0x21D3,MAIN]}
        },
        0x220F:
        {
          dir: V,
          HW: [[0.937,OPERATORS], [1.349,SIZE1], [1.942,SIZE2], [2.797,SIZE3]]
        },
        0x2210: EXTRAV,
        0x2211: EXTRAV,
        0x2212: {
          dir: H, HW: [],
          stretch: {rep:[0x2212,MAIN,0,0,0,-.23,-.23]}
        },
        0x2215: {alias: 0x2044, dir: V},
        0x221A:
        {
          dir: V,
          HW: [[1.138,MAIN], [1.280,SIZE1], [1.912,SIZE2], [2.543,SIZE3], [3.175,SIZE4]],
          stretch: {bot:[0x23B7,SYMBOLS], ext:[0x20D3,MARKS], top:[0xE022,SIZE6]}
        },
        0x2223:
        {
          dir: V,
          HW: [[0.885,MAIN]],
          stretch: {ext:[0x2223,MAIN], top:[0x2223,MAIN]}
        },
        0x2225:
        {
          dir: V,
          HW: [[0.885,MAIN]],
          stretch: {ext:[0x2225,MAIN], top:[0x2225,MAIN]}
        },
        0x2229: EXTRAV,
        0x222B: EXTRAV,
        0x222C: EXTRAV,
        0x222D: EXTRAV,
        0x222E: EXTRAV,
        0x222F: EXTRAV,
        0x2230: EXTRAV,
        0x2231: EXTRAV,
        0x2232: EXTRAV,
        0x2233: EXTRAV,
        0x22C0: EXTRAV,
        0x22C1: EXTRAV,
        0x22C2: EXTRAV,
        0x22C3: EXTRAV,
        0x2308:
        {
          dir: V,
          HW: [[0.885,MAIN], [1.470,SIZE1], [2.041,SIZE2], [2.552,SIZE3], [2.615,SIZE3,1.025]],
          stretch: {ext:[0x23A2,SYMBOLS], top:[0x23A1,SYMBOLS]}
        },
        0x2309:
        {
          dir: V,
          HW: [[0.885,MAIN], [1.470,SIZE1], [2.041,SIZE2], [2.552,SIZE3], [2.615,SIZE3,1.025]],
          stretch: {ext:[0x23A5,SYMBOLS], top:[0x23A4,SYMBOLS]}
        },
        0x230A:
        {
          dir: V,
          HW: [[0.885,MAIN], [1.470,SIZE1], [2.041,SIZE2], [2.552,SIZE3], [2.615,SIZE3,1.025]],
          stretch: {bot:[0x23A3,SYMBOLS], ext:[0x23A2,SYMBOLS]}
        },
        0x230B:
        {
          dir: V,
          HW: [[0.885,MAIN], [1.470,SIZE1], [2.041,SIZE2], [2.552,SIZE3], [2.615,SIZE3,1.025]],
          stretch: {bot:[0x23A6,SYMBOLS], ext:[0x23A5,SYMBOLS]}
        },
        0x2312: {alias: 0x23DC, dir:H},
        0x2322: {alias: 0x23DC, dir:H},
        0x2323: {alias: 0x23DD, dir:H},
        0x2329: {alias: 0x27E8, dir: V},
        0x232A: {alias: 0x27E9, dir: V},
        0x23AA:
        {
          dir: V,
          HW: [[0.688,SYMBOLS]],
          stretch: {ext:[0x23AA,SYMBOLS]}
        },
        0x23AF:
        {
          dir: H,
          HW: [[0.638,SYMBOLS]],
          stretch: {rep:[0x23AF,SYMBOLS]}
        },
        0x23B0: {alias: 0x27C6, dir: V},
        0x23B1: {alias: 0x27C5, dir: V},
        0x23B4: EXTRAH,
        0x23B5: EXTRAH,
        0x23D0:
        {
          dir: V,
          HW: [[0.885,MAIN,null,0x7C], [1.270,MAIN,1.435,0x7C], [1.719,MAIN,1.942,0x7C], [2.167,MAIN,2.448,0x7C], [2.615,MAIN,2.955,0x7C]],
          stretch: {ext:[0x7C,MAIN]}
        },
        0x23DC: EXTRAH,
        0x23DD: EXTRAH,
        0x23DE:
        {
          dir: H,
          HW: [[0.902,MAIN], [1.471,SIZE1], [2.041,SIZE2], [2.552,SIZE3]],
          stretch: {left:[0xE026,SIZE6], rep:[0xE027,SIZE6], mid:[0xE02C,SIZE6], right:[0xE028,SIZE6]}
        },
        0x23DF:
        {
          dir: H,
          HW: [[0.902,MAIN], [1.471,SIZE1], [2.041,SIZE2], [2.552,SIZE3]],
          stretch: {left:[0xE029,SIZE6], rep:[0xE02A,SIZE6], mid:[0xE02D,SIZE6], right:[0xE02B,SIZE6]}
        },
        0x23E0: EXTRAH,
        0x23E1: EXTRAH,
        0x2500: {alias: 0x2212, dir: H},
        0x2758: {alias: 0x2223, dir: V},
        0x27C5:
        {
          dir: V,
          HW: [[0.910,SYMBOLS], [1.021,SIZE1], [1.531,SIZE2], [2.041,SIZE3], [2.552,SIZE4], [3.063,SIZE5]]
        },
        0x27C6:
        {
          dir: V,
          HW: [[0.910,SYMBOLS], [1.021,SIZE1], [1.531,SIZE2], [2.041,SIZE3], [2.552,SIZE4], [3.063,SIZE5]]
        },
        0x27E6: EXTRAV,
        0x27E7: EXTRAV,
        0x27E8:
        {
          dir: V,
          HW: [[0.885,MAIN], [1.021,SIZE1], [1.270,SIZE1,1.244], [2.042,SIZE2], [2.552,SIZE3], [2.615,SIZE3,1.025]]
        },
        0x27E9:
        {
          dir: V,
          HW: [[0.885,MAIN], [1.021,SIZE1], [1.270,SIZE1,1.244], [2.042,SIZE2], [2.552,SIZE3], [2.615,SIZE3,1.025]]
        },
        0x27EA: EXTRAV,
        0x27EB: EXTRAV,
        0x27EE: {alias: 0x28, dir: V},
        0x27EF: {alias: 0x29, dir: V},
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
          HW: [[0.884,ARROWS]],
          stretch: {left:[0xE01C,SIZE6], rep:[0xE01D,SIZE6], right:[0xE02E,SIZE6]}
        },
        0x2907:
        {
          dir: H,
          HW: [[0.884,ARROWS]],
          stretch: {left:[0xE02F,SIZE6], rep:[0xE01D,SIZE6], right:[0xE021,SIZE6]}
        },
        0x29FC: EXTRAV,
        0x29FD: EXTRAV,
        0x2A00: EXTRAV,
        0x2A01: EXTRAV,
        0x2A02: EXTRAV,
        0x2A03: EXTRAV,
        0x2A04: EXTRAV,
        0x2A05: EXTRAV,
        0x2A06: EXTRAV,
        0x2A07: EXTRAV,
        0x2A08: EXTRAV,
        0x2A09: EXTRAV,
        0x2A0C: EXTRAV,
        0x2A0D: EXTRAV,
        0x2A0E: EXTRAV,
        0x2A0F: EXTRAV,
        0x2A10: EXTRAV,
        0x2A11: EXTRAV,
        0x2A12: EXTRAV,
        0x2A13: EXTRAV,
        0x2A14: EXTRAV,
        0x2A15: EXTRAV,
        0x2A16: EXTRAV,
        0x2A17: EXTRAV,
        0x2A18: EXTRAV,
        0x2A19: EXTRAV,
        0x2A1A: EXTRAV,
        0x2A1B: EXTRAV,
        0x2A1C: EXTRAV,
        0x3008: {alias: 0x27E8, dir: V},
        0x3009: {alias: 0x27E9, dir: V},
        0xFE37: {alias: 0x23DE, dir: H},
        0xFE38: {alias: 0x23DF, dir: H}
      }

    }
  });
  MathJax.Hub.Register.LoadHook(HTMLCSS.fontDir+"/Main/Regular/Main.js",function () {
    HTMLCSS.FONTDATA.FONTS[MAIN][0x2212][0] = HTMLCSS.FONTDATA.FONTS[MAIN][0x002B][0]; // - needs height and depth of +
    HTMLCSS.FONTDATA.FONTS[MAIN][0x2212][1] = HTMLCSS.FONTDATA.FONTS[MAIN][0x002B][1]; // - needs height and depth of +
  });
  MathJax.Hub.Register.LoadHook(HTMLCSS.fontDir+"/Size6/Regular/Main.js",function () {
    var u;
    u = HTMLCSS.FONTDATA.DELIMITERS[0x23DE].stretch.rep[0];
    HTMLCSS.FONTDATA.FONTS[SIZE6][u][0] += 100;  // adjust height for brace extender
    HTMLCSS.FONTDATA.FONTS[SIZE6][u][1] += 100;  // adjust depth for brace extender
    u = HTMLCSS.FONTDATA.DELIMITERS[0x23DF].stretch.rep[0];
    HTMLCSS.FONTDATA.FONTS[SIZE6][u][0] += 100;  // adjust height for brace extender
    HTMLCSS.FONTDATA.FONTS[SIZE6][u][1] += 100;  // adjust depth for brace extender
  });
  MathJax.Hub.Register.LoadHook(HTMLCSS.fontDir+"/Size1/Regular/Main.js",function () {
    var i;
    HTMLCSS.FONTDATA.FONTS[SIZE1][0x222B][2] -= 300;
    HTMLCSS.FONTDATA.FONTS[SIZE1][0x222B][5] = {rfix:-300};
    for (i = 0x222C; i <= 0x2233; i++) {
      HTMLCSS.FONTDATA.FONTS[SIZE1][i][2] -= 420;
      HTMLCSS.FONTDATA.FONTS[SIZE1][i][5] = {rfix:-420};
    }
    for (i = 0x2A0C; i <= 0x2A1C; i++) {
      HTMLCSS.FONTDATA.FONTS[SIZE1][i][2] -= 420;
      HTMLCSS.FONTDATA.FONTS[SIZE1][i][5] = {rfix:-420};
    } 
  });
  AJAX.loadComplete(HTMLCSS.fontDir + "/fontdata.js");

})(MathJax.OutputJax["HTML-CSS"],MathJax.ElementJax.mml,MathJax.Ajax);
