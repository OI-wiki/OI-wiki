/*************************************************************
 *
 *  MathJax/jax/output/SVG/fonts/STIX-Web/fontdata.js
 *  
 *  Initializes the SVG OutputJax to use the STIX-Web fonts

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

  var H = "H", V = "V", EXTRAH = {load:"extra", dir:H}, EXTRAV = {load:"extra", dir:V};
  var ARROWREP = [0x2212,MAIN,0,0,0,-.26,-.26];

  SVG.Augment({
    FONTDATA: {
      version: VERSION,


      baselineskip: 1200,
      lineH: 800, lineD: 200,

      FONTS: {
        "STIXMathJax_Alphabets-bold-italic": "Alphabets/BoldItalic/Main.js",
        "STIXMathJax_Alphabets-bold": "Alphabets/Bold/Main.js",
        "STIXMathJax_Alphabets-italic": "Alphabets/Italic/Main.js",
        "STIXMathJax_Alphabets": "Alphabets/Regular/Main.js",
        "STIXMathJax_Arrows-bold": "Arrows/Bold/Main.js",
        "STIXMathJax_Arrows": "Arrows/Regular/Main.js",
        "STIXMathJax_DoubleStruck-bold-italic": "DoubleStruck/BoldItalic/Main.js",
        "STIXMathJax_DoubleStruck-bold": "DoubleStruck/Bold/Main.js",
        "STIXMathJax_DoubleStruck-italic": "DoubleStruck/Italic/Main.js",
        "STIXMathJax_DoubleStruck": "DoubleStruck/Regular/Main.js",
        "STIXMathJax_Fraktur-bold": "Fraktur/Bold/Main.js",
        "STIXMathJax_Fraktur": "Fraktur/Regular/Main.js",
        "STIXMathJax_Latin-bold-italic": "Latin/BoldItalic/Main.js",
        "STIXMathJax_Latin-bold": "Latin/Bold/Main.js",
        "STIXMathJax_Latin-italic": "Latin/Italic/Main.js",
        "STIXMathJax_Latin": "Latin/Regular/Main.js",
        "STIXMathJax_Main-bold-italic": "Main/BoldItalic/Main.js",
        "STIXMathJax_Main-bold": "Main/Bold/Main.js",
        "STIXMathJax_Main-italic": "Main/Italic/Main.js",
        "STIXMathJax_Main": "Main/Regular/Main.js",
        "STIXMathJax_Marks-bold-italic": "Marks/BoldItalic/Main.js",
        "STIXMathJax_Marks-bold": "Marks/Bold/Main.js",
        "STIXMathJax_Marks-italic": "Marks/Italic/Main.js",
        "STIXMathJax_Marks": "Marks/Regular/Main.js",
        "STIXMathJax_Misc-bold-italic": "Misc/BoldItalic/Main.js",
        "STIXMathJax_Misc-bold": "Misc/Bold/Main.js",
        "STIXMathJax_Misc-italic": "Misc/Italic/Main.js",
        "STIXMathJax_Misc": "Misc/Regular/Main.js",
        "STIXMathJax_Monospace": "Monospace/Regular/Main.js",
        "STIXMathJax_Normal-bold-italic": "Normal/BoldItalic/Main.js",
        "STIXMathJax_Normal-bold": "Normal/Bold/Main.js",
        "STIXMathJax_Normal-italic": "Normal/Italic/Main.js",
        "STIXMathJax_Operators-bold": "Operators/Bold/Main.js",
        "STIXMathJax_Operators": "Operators/Regular/Main.js",
        "STIXMathJax_SansSerif-bold-italic": "SansSerif/BoldItalic/Main.js",
        "STIXMathJax_SansSerif-bold": "SansSerif/Bold/Main.js",
        "STIXMathJax_SansSerif-italic": "SansSerif/Italic/Main.js",
        "STIXMathJax_SansSerif": "SansSerif/Regular/Main.js",
        "STIXMathJax_Script-bold-italic": "Script/BoldItalic/Main.js",
        "STIXMathJax_Script-italic": "Script/Italic/Main.js",
        "STIXMathJax_Script": "Script/Regular/Main.js",
        "STIXMathJax_Shapes-bold-italic": "Shapes/BoldItalic/Main.js",
        "STIXMathJax_Shapes-bold": "Shapes/Bold/Main.js",
        "STIXMathJax_Shapes": "Shapes/Regular/Main.js",
        "STIXMathJax_Size1": "Size1/Regular/Main.js",
        "STIXMathJax_Size2": "Size2/Regular/Main.js",
        "STIXMathJax_Size3": "Size3/Regular/Main.js",
        "STIXMathJax_Size4": "Size4/Regular/Main.js",
        "STIXMathJax_Size5": "Size5/Regular/Main.js",
        "STIXMathJax_Symbols-bold": "Symbols/Bold/Main.js",
        "STIXMathJax_Symbols": "Symbols/Regular/Main.js",
        "STIXMathJax_Variants-bold-italic": "Variants/BoldItalic/Main.js",
        "STIXMathJax_Variants-bold": "Variants/Bold/Main.js",
        "STIXMathJax_Variants-italic": "Variants/Italic/Main.js",
        "STIXMathJax_Variants": "Variants/Regular/Main.js"
      },

      VARIANT: {
          "normal": {
            fonts: [MAIN,MONOSPACE,LATIN,ALPHABETS,MARKS,ARROWS,OPERATORS,SYMBOLS,SHAPES,MISC,VARIANTS,SIZE1],
            remap: {0x007C: [0x007C, "-STIX-Web-variant"]}
          },
          "bold": {
            fonts: [MAINBOLD,NORMALBOLD,FRAKTURBOLD,DOUBLESTRUCKBOLD,SANSSERIFBOLD,LATINBOLD,ALPHABETSBOLD,MARKSBOLD,ARROWSBOLD,OPERATORSBOLD,SYMBOLSBOLD,SHAPESBOLD,MISCBOLD,VARIANTSBOLD,SIZE1],
            offsetA: 0x1D400,
            offsetG: 0x1D6A8,
            remap: {0x2202: 0x1D6DB, 0x2207: 0x1D6C1},
            bold: true
          },
          "italic": {
            fonts: [MAINITALIC,NORMALITALIC,SCRIPTITALIC,DOUBLESTRUCKITALIC,SANSSERIFITALIC,LATINITALIC,ALPHABETSITALIC,MARKSITALIC,MISCITALIC,VARIANTSITALIC,SIZE1],
            offsetA: 0x1D434,
            offsetG: 0x1D6E2,
            remap: {0x1D455: 0x210E, 0x2202: 0x1D715, 0x2207: 0x1D6FB},
            italic: true
          },
          "bold-italic": {
            fonts: [MAINBOLDITALIC,NORMALBOLDITALIC,SCRIPTBOLDITALIC,DOUBLESTRUCKBOLDITALIC,SANSSERIFBOLDITALIC,LATINBOLDITALIC,ALPHABETSBOLDITALIC,MARKSBOLDITALIC,SHAPESBOLDITALIC,MISCBOLDITALIC,VARIANTSBOLDITALIC,SIZE1],
            offsetA: 0x1D434,
            offsetG: 0x1D71C,
            remap: {0x1D455: 0x210E, 0x2202: 0x1D74F, 0x2207: 0x1D735},
            bold: true, italic: true
          },
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
            fonts: [FRAKTURBOLD],
            offsetA: 0x1D56C,
            bold:true
          },
          "script": {
            fonts: [SCRIPTITALIC],
            offsetA: 0x1D49C,
            italic: true,
            remap: {0x1D49D: 0x212C, 0x1D4A0: 0x2130, 0x1D4A1: 0x2131, 0x1D4A3: 0x210B, 0x1D4A4: 0x2110, 0x1D4A7: 0x2112, 0x1D4A8: 0x2133, 0x1D4AD: 0x211B, 0x1D4BA: 0x212F, 0x1D4BC: 0x210A, 0x1D4C4: 0x2134}
          },
          "bold-script": {
            fonts: [SCRIPTBOLDITALIC],
            offsetA: 0x1D4D0,
            bold: true, italic: true
          },
          "sans-serif": {
            fonts: [SANSSERIF],
            offsetA: 0x1D5A0,
            offsetN: 0x1D7E2,
            offsetP: 0xE17D,
            remap: {0x2202: 0xE17C}
          },
          "bold-sans-serif": {
            fonts: [SANSSERIFBOLD],
            offsetA: 0x1D5D4,
            offsetN: 0x1D7EC,
            offsetG: 0x1D756,
            remap: {0x2202: 0x1D789, 0x2207: 0x1D76F},
            bold: true
          },
          "sans-serif-italic": {
             fonts: [SANSSERIFITALIC],
             offsetA: 0x1D608,
             offsetN: 0xE1B4,
             offsetP: 0xE1BF,
             remap: {0x2202: 0xE1BE},
             italic: true
          },
          "sans-serif-bold-italic": {
             fonts: [SANSSERIFBOLDITALIC],
             offsetA: 0x1D63C,
             offsetN: 0xE1F6,
             offsetG: 0x1D790,
             remap: {0x2202: 0x1D7C3, 0x2207: 0x1D7A9},
             bold: true, italic: true
          },
          "monospace": {
             fonts: [MONOSPACE],
             offsetA: 0x1D670,
             offsetN: 0x1D7F6
          },
          "-STIX-Web-variant": {remap: {0x2A87: 0xE010, 0x2A88: 0xE00F, 0x25B3: 0x25B5, 0x25BD: 0x25BF, 0x007C: [0x07C, MML.VARIANT.NORMAL]}, fonts: [VARIANTS,SHAPES,OPERATORS,MAIN,MONOSPACE,LATIN,ALPHABETS,MARKS,ARROWS,SYMBOLS,MISC,SIZE1]},
          "-tex-caligraphic": {offsetA: 0xE22D, noLowerCase: 1, fonts: [VARIANTSITALIC,MAINITALIC,NORMALITALIC,SCRIPTITALIC,DOUBLESTRUCKITALIC,SANSSERIFITALIC,LATINITALIC,ALPHABETSITALIC,MARKSITALIC,MISCITALIC,SIZE1], italic: true},
          "-tex-oldstyle": {offsetN: 0xE261, remap: {0xE262: 0xE265, 0xE263: 0xE269, 0xE264: 0xE26D, 0xE265: 0xE271, 0xE266: 0xE275, 0xE267: 0xE279, 0xE268: 0xE27D, 0xE269: 0xE281, 0xE26A: 0xE285}, fonts: [VARIANTS,MAIN,MONOSPACE,LATIN,ALPHABETS,MARKS,ARROWS,OPERATORS,SYMBOLS,SHAPES,MISC,SIZE1]},
          "-tex-caligraphic-bold": {offsetA: 0xE247, noLowerCase: 1, fonts: [VARIANTSBOLDITALIC,MAINBOLDITALIC,NORMALBOLDITALIC,SCRIPTBOLDITALIC,DOUBLESTRUCKBOLDITALIC,SANSSERIFBOLDITALIC,LATINBOLDITALIC,ALPHABETSBOLDITALIC,MARKSBOLDITALIC,SHAPESBOLDITALIC,MISCBOLDITALIC,SIZE1], italic: true, bold: true},
          "-tex-oldstyle-bold": {offsetN: 0xE261, remap: {0xE264: 0xE267, 0xE265: 0xE26B, 0xE266: 0xE26F, 0xE267: 0xE273, 0xE268: 0xE277, 0xE269: 0xE27B, 0xE26A: 0xE27F, 0xE26B: 0xE283, 0xE26C: 0xE287}, fonts: [VARIANTSBOLD,MAINBOLD,NORMALBOLD,FRAKTURBOLD,DOUBLESTRUCKBOLD,SANSSERIFBOLD,LATINBOLD,ALPHABETSBOLD,MARKSBOLD,ARROWSBOLD,OPERATORSBOLD,SYMBOLSBOLD,SHAPESBOLD,MISCBOLD,SIZE1], bold: true},
          "-tex-mathit": {fonts: [MAINITALIC,NORMALITALIC,SCRIPTITALIC,DOUBLESTRUCKITALIC,SANSSERIFITALIC,LATINITALIC,ALPHABETSITALIC,MARKSITALIC,MISCITALIC,VARIANTSITALIC,SIZE1], italic:true, noIC:true},
          "-largeOp": {fonts:[SIZE1,MAIN]},
          "-smallOp": {}
      },

      RANGES: [
        {name: "alpha", low: 0x61, high: 0x7A, offset: "A", add: 26},
        {name: "Alpha", low: 0x41, high: 0x5A, offset: "A"},
        {name: "number", low: 0x30, high: 0x39, offset: "N"},
        {name: "greek-non-unicode", low: 0x03B1, high: 0x03C9, offset: "E", add: 25},
        {name: "greek", low: 0x03B1, high: 0x03C9, offset: "G", add: 26},
        {name: "Greek", low: 0x0391, high: 0x03A9, offset: "G"},
        {name: "vargreek", low: 0x03D1, high: 0x03F6, offset: "G", remapOnly: true,
           remap: {0x03F5: 52, 0x03D1: 53, 0x03F0: 54, 0x03D5: 55, 0x03F1: 56, 0x03D6: 57, 0x03F4: 17}},
        {name: "PUAgreek", low: 0x03B1, high: 0x03C9, offset: "P", add: 25},
        {name: "PUAGreek", low: 0x0391, high: 0x03A9, offset: "P"}, 
        {name: "varPUAgreek", low: 0x03D1, high: 0x03F6, offset: "P", remapOnly: true,
           remap: {0x03F5: 50, 0x03D1: 51, 0x03D5: 52, 0x03F1: 53, 0x03D6: 54, 0x03F4: 17}}
      ],

      RULECHAR: 0x23AF,

      REMAP: {
        0xA: 0x20,
        0x3008: 0x27E8,
        0x3009: 0x27E9,
        0x2758: 0x2223,
        0x02F3: 0x02DA,
        0x02F4: 0x02CA,
        0xFE37: 0x23DE,
        0xFE38: 0x23DF
      },

      REMAPACCENT: {
        "\u007E": "\u0303",
        "\u2192": "\u20D7",
        "\u2190": "\u20D6",
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
          HW: [[853,MAIN], [1230,SIZE1], [1350,SIZE1,1.098], [1845,SIZE2], [2460,SIZE3], [3075,SIZE4]],
          stretch: {bot:[0xE000,SIZE5], ext:[0xE001,SIZE5], top:[0xE002,SIZE5]}
        },
        0x29:
        {
          dir: V,
          HW: [[853,MAIN], [1230,SIZE1], [1350,SIZE1,1.098], [1845,SIZE2], [2460,SIZE3], [3075,SIZE4]],
          stretch: {bot:[0xE003,SIZE5], ext:[0xE004,SIZE5], top:[0xE005,SIZE5]}
        },
        0x2D: {alias: 0x23AF, dir: H},
        0x2F:
        {
          dir: V,
          HW: [[690,MAIN], [1230,SIZE1], [1350,SIZE1,1.098], [1845,SIZE2], [2460,SIZE3], [3075,SIZE4]]
        },
        0x3D: EXTRAH,
        0x5B:
        {
          dir: V,
          HW: [[818,MAIN], [1230,SIZE1], [1350,SIZE1,1.098], [1845,SIZE2], [2460,SIZE3], [3075,SIZE4]],
          stretch: {bot:[0xE006,SIZE5], ext:[0xE007,SIZE5], top:[0xE008,SIZE5]}
        },
        0x5C:
        {
          dir: V,
          HW: [[690,MAIN], [1230,SIZE1], [1350,SIZE1,1.098], [1845,SIZE2], [2460,SIZE3], [3075,SIZE4]]
        },
        0x5D:
        {
          dir: V,
          HW: [[818,MAIN], [1230,SIZE1], [1350,SIZE1,1.098], [1845,SIZE2], [2460,SIZE3], [3075,SIZE4]],
          stretch: {bot:[0xE009,SIZE5], ext:[0xE00A,SIZE5], top:[0xE00B,SIZE5]}
        },
        0x5E: {alias: 0x2C6, dir: H},
        0x5F: {alias: 0x23AF, dir: H},
        0x7B:
        {
          dir: V,
          HW: [[861,MAIN], [1230,SIZE1], [1350,SIZE1,1.098], [1845,SIZE2], [2460,SIZE3], [3075,SIZE4]],
          stretch: {bot:[0xE00C,SIZE5], ext:[0xE00D,SIZE5], mid:[0xE00E,SIZE5], top:[0xE00F,SIZE5]}
        },
        0x7C:
        {
          dir: V,
          HW: [[690,MAIN]],
          stretch: {bot:[0x7C,MAIN], ext:[0x7C,MAIN]}
        },
        0x7D:
        {
          dir: V,
          HW: [[861,MAIN], [1230,SIZE1], [1350,SIZE1,1.098], [1845,SIZE2], [2460,SIZE3], [3075,SIZE4]],
          stretch: {bot:[0xE010,SIZE5], ext:[0xE00D,SIZE5], mid:[0xE011,SIZE5], top:[0xE012,SIZE5]}
        },
        0x7E: {alias: 0x2DC, dir: H},
        0xAF: {alias: 0x23AF, dir: H},
        0x2C6:
        {
          dir: H,
          HW: [[311,MAIN], [560,SIZE1], [979,SIZE2], [1460,SIZE3], [1886,SIZE4], [2328,SIZE5]]
        },
        0x2C7: EXTRAH,
        0x2C9: {alias: 0x23AF, dir: H},
        0x2CD: EXTRAH,
        0x2DC:
        {
          dir: H,
          HW: [[330,MAIN], [560,SIZE1], [979,SIZE2], [1460,SIZE3], [1886,SIZE4], [2328,SIZE5]]
        },
        0x2F7: EXTRAH,
        0x302:
        {
          dir: H,
          HW: [[311,MAIN], [560,SIZE1], [979,SIZE2], [1460,SIZE3], [1886,SIZE4], [2328,SIZE5]]
        },
        0x303:
        {
          dir: H,
          HW: [[330,MAIN], [560,SIZE1], [979,SIZE2], [1460,SIZE3], [1886,SIZE4], [2328,SIZE5]]
        },
        0x305:
        {
          dir: H,
          HW: [[500,MARKS], [1000,SIZE1], [1500,SIZE2], [2000,SIZE3], [2500,SIZE4], [3000,SIZE5]],
          stretch: {left:[0xE013,SIZE5], rep:[0xE013,SIZE5]}
        },
        0x30C:
        {
          dir: H,
          HW: [[311,MAIN], [560,SIZE1], [979,SIZE2], [1460,SIZE3], [1886,SIZE4], [2328,SIZE5]]
        },
        0x330:
        {
          dir: H,
          HW: [[330,MARKS], [560,SIZE1], [979,SIZE2], [1460,SIZE3], [1886,SIZE4], [2328,SIZE5]]
        },
        0x332:
        {
          dir: H,
          HW: [[500,MARKS], [1000,SIZE1], [1500,SIZE2], [2000,SIZE3], [2500,SIZE4], [3000,SIZE5]],
          stretch: {left:[0xE014,SIZE5], rep:[0xE014,SIZE5]}
        },
        0x338:
        {
          dir: V,
          HW: [[818,MAIN], [553,SIZE1], [662,SIZE2], [818,SIZE3], [959,SIZE4], [1414,SIZE5]]
        },
        0x2015: {alias: 0x23AF, dir: H},
        0x2016:
        {
          dir: V,
          HW: [[879,MAIN]],
          stretch: {bot:[0x2016,MAIN], ext:[0x2016,MAIN]}
        },
        0x2017: {alias: 0x23AF, dir: H},
        0x203E:
        {
          dir: H,
          HW: [[500,MAIN], [1000,SIZE1], [1500,SIZE2], [2000,SIZE3], [2500,SIZE4], [3000,SIZE5]],
          stretch: {left:[0x203E,MAIN], rep:[0x203E,MAIN]}
        },
        0x20D0: EXTRAH,
        0x20D1: EXTRAH,
        0x20D6: EXTRAH,
        0x20D7:
        {
          dir: H,
          HW: [[436,MAIN], [872,SIZE1], [1308,SIZE2], [1744,SIZE3], [2180,SIZE4], [3000,SIZE5]],
          stretch: {rep:[0xE016,SIZE5], right:[0xE019,SIZE5]}
        },
        0x20E1: EXTRAH,
        0x20EC: EXTRAH,
        0x20ED: EXTRAH,
        0x20EE: EXTRAH,
        0x20EF: EXTRAH,
        0x2140: EXTRAV,
        0x2190:
        {
          dir: H,
          HW: [[786,MAIN]],
          stretch: {left:[0x2190,MAIN], rep:ARROWREP}
        },
        0x2191:
        {
          dir: V,
          HW: [[818,MAIN]],
          stretch: {ext:[0x23D0,MAIN], top:[0x2191,MAIN]}
        },
        0x2192:
        {
          dir: H,
          HW: [[786,MAIN]],
          stretch: {rep:ARROWREP, right:[0x2192,MAIN]}
        },
        0x2193:
        {
          dir: V,
          HW: [[818,MAIN]],
          stretch: {bot:[0x2193,MAIN], ext:[0x23D0,MAIN]}
        },
        0x2194:
        {
          dir: H,
          HW: [[850,MAIN]],
          stretch: {left:[0x2190,MAIN], rep:ARROWREP, right:[0x2192,MAIN]}
        },
        0x2195:
        {
          dir: V,
          HW: [[954,MAIN]],
          stretch: {bot:[0x2193,MAIN], ext:[0x23D0,MAIN], top:[0x2191,MAIN]}
        },
        0x219E: EXTRAH,
        0x219F: EXTRAV,
        0x21A0: EXTRAH,
        0x21A1: EXTRAV,
        0x21A4: EXTRAH,
        0x21A5: EXTRAV,
        0x21A6: EXTRAH,
        0x21A7: EXTRAV,
        0x21A8: EXTRAV,
        0x21A9: EXTRAH,
        0x21AA: EXTRAH,
        0x21B0: EXTRAV,
        0x21B1: EXTRAV,
        0x21B2: EXTRAV,
        0x21B3: EXTRAV,
        0x21B4: EXTRAH,
        0x21B5: EXTRAV,
        0x21BC: EXTRAH,
        0x21BD: EXTRAH,
        0x21BE: EXTRAV,
        0x21BF: EXTRAV,
        0x21C0: EXTRAH,
        0x21C1: EXTRAH,
        0x21C2: EXTRAV,
        0x21C3: EXTRAV,
        0x21CB: EXTRAH,
        0x21CC: EXTRAH,
        0x21D0:
        {
          dir: H,
          HW: [[806,MAIN]],
          stretch: {left:[0x21D0,MAIN], rep:[0xE01F,SIZE5]}
        },
        0x21D1:
        {
          dir: V,
          HW: [[818,MAIN]],
          stretch: {ext:[0xE020,SIZE5], top:[0x21D1,MAIN]}
        },
        0x21D2:
        {
          dir: H,
          HW: [[806,MAIN]],
          stretch: {rep:[0xE01F,SIZE5], right:[0x21D2,MAIN]}
        },
        0x21D3:
        {
          dir: V,
          HW: [[818,MAIN]],
          stretch: {bot:[0x21D3,MAIN], ext:[0xE020,SIZE5]}
        },
        0x21D4:
        {
          dir: H,
          HW: [[886,MAIN]],
          stretch: {left:[0x21D0,MAIN], rep:[0xE01F,SIZE5], right:[0x21D2,MAIN]}
        },
        0x21D5:
        {
          dir: V,
          HW: [[954,MAIN]],
          stretch: {bot:[0x21D3,MAIN], ext:[0xE020,SIZE5], top:[0x21D1,MAIN]}
        },
        0x21DA: EXTRAH,
        0x21DB: EXTRAH,
        0x21E0: EXTRAH,
        0x21E1: EXTRAV,
        0x21E2: EXTRAH,
        0x21E3: EXTRAV,
        0x21E4: EXTRAH,
        0x21E5: EXTRAH,
        0x21FD: EXTRAH,
        0x21FE: EXTRAH,
        0x21FF: EXTRAH,
        0x220F: EXTRAV,
        0x2210: EXTRAV,
        0x2211: EXTRAV,
        0x2212: {alias: 0x23AF, dir: H},
        0x2215: {alias: 0x2F, dir: V},
        0x221A:
        {
          dir: V,
          HW: [[1232,MAIN], [1847,SIZE1], [2460,SIZE2], [3075,SIZE3]],
          stretch: {bot:[0xE022,SIZE5], ext:[0xE023,SIZE5], top:[0xE024,SIZE5]}
        },
        0x221B: EXTRAV,
        0x221C: EXTRAV,
        0x2223:
        {
          dir: V,
          HW: [[879,MAIN]],
          stretch: {ext:[0x2223,MAIN]}
        },
        0x2225:
        {
          dir: V,
          HW: [[879,MAIN]],
          stretch: {ext:[0x2225,MAIN]}
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
        0x22C0: EXTRAV,
        0x22C1: EXTRAV,
        0x22C2: EXTRAV,
        0x22C3: EXTRAV,
        0x2308:
        {
          dir: V,
          HW: [[926,MAIN], [1230,SIZE1], [1350,SIZE1,1.098], [1845,SIZE2], [2460,SIZE3], [3075,SIZE4]],
          stretch: {ext:[0xE007,SIZE5], top:[0xE008,SIZE5]}
        },
        0x2309:
        {
          dir: V,
          HW: [[926,MAIN], [1230,SIZE1], [1350,SIZE1,1.098], [1845,SIZE2], [2460,SIZE3], [3075,SIZE4]],
          stretch: {ext:[0xE00A,SIZE5], top:[0xE00B,SIZE5]}
        },
        0x230A:
        {
          dir: V,
          HW: [[926,MAIN], [1230,SIZE1], [1350,SIZE1,1.098], [1845,SIZE2], [2460,SIZE3], [3075,SIZE4]],
          stretch: {bot:[0xE006,SIZE5], ext:[0xE007,SIZE5]}
        },
        0x230B:
        {
          dir: V,
          HW: [[926,MAIN], [1230,SIZE1], [1350,SIZE1,1.098], [1845,SIZE2], [2460,SIZE3], [3075,SIZE4]],
          stretch: {bot:[0xE009,SIZE5], ext:[0xE00A,SIZE5]}
        },
        0x2312: {alias: 0x23DC, dir:H},
        0x2322: {alias: 0x23DC, dir:H},
        0x2323: {alias: 0x23DD, dir:H},
        0x2329: {alias: 0x27E8, dir: V},
        0x232A: {alias: 0x27E9, dir: V},
        0x23AA: EXTRAV,
        0x23AF:
        {
          dir: H,
          HW: [[315,SYMBOLS]],
          stretch: {rep:[0x23AF,SYMBOLS]}
        },
        0x23B0:
        {
          dir: V,
          HW: [[1000,SIZE5,null,0xE03A]],
          stretch: {top:[0xE00F,SIZE5], ext:[0xE00D,SIZE5], bot:[0xE010,SIZE5]}
        },
        0x23B1:
        {
          dir: V,
          HW: [[1000,SIZE5,null,0xE03B]],
          stretch: {top:[0xE012,SIZE5], ext:[0xE00D,SIZE5], bot:[0xE00C,SIZE5]}
        },
        0x23B4: EXTRAH,
        0x23B5: EXTRAH,
        0x23D0: EXTRAV,
        0x23DC: EXTRAH,
        0x23DD: EXTRAH,
        0x23DE:
        {
          dir: H,
          HW: [[1000,MAIN], [925,SIZE1], [1460,SIZE2], [1886,SIZE3], [2328,SIZE4], [3238,SIZE5]],
          stretch: {left:[0xE031,SIZE5], rep:[0xE028,SIZE5], mid:[0xE032,SIZE5], right:[0xE033,SIZE5]}
        },
        0x23DF:
        {
          dir: H,
          HW: [[1000,MAIN], [925,SIZE1], [1460,SIZE2], [1886,SIZE3], [2328,SIZE4], [3238,SIZE5]],
          stretch: {left:[0xE034,SIZE5], rep:[0xE02B,SIZE5], mid:[0xE035,SIZE5], right:[0xE036,SIZE5]}
        },
        0x23E0: EXTRAH,
        0x23E1: EXTRAH,
        0x2500: {alias: 0x2212, dir: H},
        0x2758: {alias: 0x2223, dir: V},
        0x2772: EXTRAV,
        0x2773: EXTRAV,
        0x27E6: EXTRAV,
        0x27E7: EXTRAV,
        0x27E8:
        {
          dir: V,
          HW: [[926,MAIN], [1230,SIZE1], [1350,SIZE1,1.098], [1845,SIZE2], [2460,SIZE3], [3075,SIZE4]]
        },
        0x27E9:
        {
          dir: V,
          HW: [[926,MAIN], [1230,SIZE1], [1350,SIZE1,1.098], [1845,SIZE2], [2460,SIZE3], [3075,SIZE4]]
        },
        0x27EA: EXTRAV,
        0x27EB: EXTRAV,
        0x27EE:
        {
          dir: V,
          HW: [[853,MAIN]],
          stretch: {bot:[0xE000,SIZE5], ext:[0xE001,SIZE5], top:[0xE002,SIZE5]}
        },
        0x27EF:
        {
          dir: V,
          HW: [[853,MAIN]],
          stretch: {bot:[0xE003,SIZE5], ext:[0xE004,SIZE5], top:[0xE005,SIZE5]}
        },
        0x27F0: EXTRAV,
        0x27F1: EXTRAV,
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
        0x2906: EXTRAH,
        0x2907: EXTRAH,
        0x290A: EXTRAV,
        0x290B: EXTRAV,
        0x2912: EXTRAV,
        0x2913: EXTRAV,
        0x294E: EXTRAH,
        0x294F: EXTRAV,
        0x2950: EXTRAH,
        0x2951: EXTRAV,
        0x2952: EXTRAH,
        0x2953: EXTRAH,
        0x2954: EXTRAV,
        0x2955: EXTRAV,
        0x2956: EXTRAH,
        0x2957: EXTRAH,
        0x2958: EXTRAV,
        0x2959: EXTRAV,
        0x295A: EXTRAH,
        0x295B: EXTRAH,
        0x295C: EXTRAV,
        0x295D: EXTRAV,
        0x295E: EXTRAH,
        0x295F: EXTRAH,
        0x2960: EXTRAV,
        0x2961: EXTRAV,
        0x2980: EXTRAV,
        0x2983: EXTRAV,
        0x2984: EXTRAV,
        0x2985: EXTRAV,
        0x2986: EXTRAV,
        0x2997: EXTRAV,
        0x2998: EXTRAV,
        0x29F8:
        {
          dir: V,
          HW: [[1020,MAIN], [1845,SIZE1]]
        },
        0x29F9:
        {
          dir: V,
          HW: [[1020,MAIN], [1845,SIZE1]]
        },
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
        0x2A0A: EXTRAV,
        0x2A0B: EXTRAV,
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
        0x2AFC: EXTRAV,
        0x2AFF: EXTRAV,
        0x2B45: EXTRAH,
        0x2B46:
        {
          dir: H,
          HW: [[818,SHAPES]],
          stretch: {rep:[0xE039,SIZE5], right:[0x2B46,SHAPES]}
        },
        0x3008: {alias: 0x27E8, dir: V},
        0x3009: {alias: 0x27E9, dir: V},
        0xFE37: {alias: 0x23DE, dir: H},
        0xFE38: {alias: 0x23DF, dir: H}
      }

    }
  });
  MathJax.Hub.Register.LoadHook(SVG.fontDir+"/Main/Regular/Main.js",function () {
    SVG.FONTDATA.FONTS[MAIN][0x22EE][0] += 400;  // adjust height for \vdots
    SVG.FONTDATA.FONTS[MAIN][0x22F1][0] += 500;  // adjust height for \ddots
    SVG.FONTDATA.FONTS[MAIN][0x2212][0] = SVG.FONTDATA.FONTS[MAIN][0x002B][0]; // - needs height and depth of +
    SVG.FONTDATA.FONTS[MAIN][0x2212][1] = SVG.FONTDATA.FONTS[MAIN][0x002B][1]; // - needs height and depth of +
    SVG.FONTDATA.FONTS[MAIN][0x003D][1] += 100;  // adjust depth for = (double arrow extender)
  });
  MathJax.Hub.Register.LoadHook(SVG.fontDir+"/Size5/Regular/Main.js",function () {
    var u;
    u = SVG.FONTDATA.DELIMITERS[0x23DE].stretch.rep[0];
    SVG.FONTDATA.FONTS[SIZE5][u][0] += 200;  // adjust height for brace extender
    SVG.FONTDATA.FONTS[SIZE5][u][1] += 200;  // adjust depth for brace extender
    u = SVG.FONTDATA.DELIMITERS[0x23DF].stretch.rep[0];
    SVG.FONTDATA.FONTS[SIZE5][u][0] += 200;  // adjust height for brace extender
    SVG.FONTDATA.FONTS[SIZE5][u][1] += 200;  // adjust depth for brace extender
  });

  AJAX.loadComplete(SVG.fontDir + "/fontdata.js");

})(MathJax.OutputJax.SVG,MathJax.ElementJax.mml,MathJax.Ajax,MathJax.Hub);
