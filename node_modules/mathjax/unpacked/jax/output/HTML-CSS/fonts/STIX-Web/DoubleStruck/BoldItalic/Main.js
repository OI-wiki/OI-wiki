/*************************************************************
 *
 *  MathJax/jax/output/HTML-CSS/fonts/STIX-Web/DoubleStruck/BoldItalic/Main.js
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

MathJax.OutputJax['HTML-CSS'].FONTDATA.FONTS['STIXMathJax_DoubleStruck-bold-italic'] = {
  directory: 'DoubleStruck/BoldItalic',
  family: 'STIXMathJax_DoubleStruck',
  weight: 'bold',
  style: 'italic',
  testString: '\u00A0\u2102\u210D\u2115\u2119\u211A\u211D\u2124\u213C\u213F\u2145\u2146\u2147\u2148\u2149',
  0x20: [0,0,250,0,0],
  0xA0: [0,0,250,0,0],
  0x2102: [685,14,713,35,704],
  0x210D: [669,0,773,21,808],
  0x2115: [669,0,760,27,783],
  0x2119: [669,0,497,18,715],
  0x211A: [685,74,754,35,734],
  0x211D: [669,0,727,18,718],
  0x2124: [669,0,807,23,837],
  0x213C: [449,13,730,32,715],
  0x213F: [669,0,796,35,821],
  0x2145: [669,0,748,18,733],
  0x2146: [699,13,633,45,698],
  0x2147: [462,13,575,45,540],
  0x2148: [669,0,379,40,413],
  0x2149: [669,205,421,-93,455]
};

MathJax.Callback.Queue(
  ["initFont",MathJax.OutputJax["HTML-CSS"],"STIXMathJax_DoubleStruck-bold-italic"],
  ["loadComplete",MathJax.Ajax,MathJax.OutputJax["HTML-CSS"].fontDir+"/DoubleStruck/BoldItalic/Main.js"]
);
