/*************************************************************
 *
 *  MathJax/jax/output/HTML-CSS/fonts/Latin-Modern/Alphabets/Regular/Main.js
 *  
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

MathJax.OutputJax['HTML-CSS'].FONTDATA.FONTS['LatinModernMathJax_Alphabets'] = {
  directory: 'Alphabets/Regular',
  family: 'LatinModernMathJax_Alphabets',
  testString: '\u00A0\u2103\u2107\u2109\u2116\u2117\u211E\u2120\u2122\u2126\u212A\u212B\u212E\uFEFF',
  0x20: [0,0,332,0,0],
  0xA0: [0,0,332,0,0],
  0x2103: [705,22,1031,49,974],
  0x2107: [705,22,530,50,495],
  0x2109: [683,0,980,49,937],
  0x2116: [695,10,916,51,860],
  0x2117: [683,0,683,0,683],
  0x211E: [683,22,736,35,732],
  0x2120: [683,-247,883,34,827],
  0x2122: [687,-277,983,22,938],
  0x2126: [705,0,722,44,677],
  0x212A: [683,0,778,33,736],
  0x212B: [892,0,750,32,717],
  0x212E: [701,10,676,28,647],
  0xFEFF: [0,0,0,0,0]
};

MathJax.Callback.Queue(
  ["initFont",MathJax.OutputJax["HTML-CSS"],"LatinModernMathJax_Alphabets"],
  ["loadComplete",MathJax.Ajax,MathJax.OutputJax["HTML-CSS"].fontDir+"/Alphabets/Regular/Main.js"]
);
