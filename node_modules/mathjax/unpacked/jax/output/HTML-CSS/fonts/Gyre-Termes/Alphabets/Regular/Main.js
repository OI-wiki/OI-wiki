/*************************************************************
 *
 *  MathJax/jax/output/HTML-CSS/fonts/Gyre-Termes/Alphabets/Regular/Main.js
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

MathJax.OutputJax['HTML-CSS'].FONTDATA.FONTS['GyreTermesMathJax_Alphabets'] = {
  directory: 'Alphabets/Regular',
  family: 'GyreTermesMathJax_Alphabets',
  testString: '\u00A0\u0E3F\u2103\u2107\u2109\u2116\u2117\u211E\u2120\u2122\u2126\u212A\u212B\u212E\uFEFF',
  0x20: [0,0,250,0,0],
  0xA0: [0,0,250,0,0],
  0xE3F: [745,83,667,17,593],
  0x2103: [676,14,1029,57,995],
  0x2107: [676,14,475,48,427],
  0x2109: [676,0,929,57,919],
  0x2116: [669,15,1001,0,957],
  0x2117: [686,14,760,30,730],
  0x211E: [662,0,667,17,659],
  0x2120: [669,-297,939,40,899],
  0x2122: [662,-305,980,40,941],
  0x2126: [676,0,853,80,773],
  0x212A: [662,0,722,34,723],
  0x212B: [896,0,722,15,706],
  0x212E: [596,0,742,40,702],
  0xFEFF: [0,0,0,0,0]
};

MathJax.Callback.Queue(
  ["initFont",MathJax.OutputJax["HTML-CSS"],"GyreTermesMathJax_Alphabets"],
  ["loadComplete",MathJax.Ajax,MathJax.OutputJax["HTML-CSS"].fontDir+"/Alphabets/Regular/Main.js"]
);
