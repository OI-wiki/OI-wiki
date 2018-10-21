/*************************************************************
 *
 *  MathJax/jax/output/HTML-CSS/fonts/STIX-Web/DoubleStruck/Italic/Main.js
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

MathJax.OutputJax['HTML-CSS'].FONTDATA.FONTS['STIXMathJax_DoubleStruck-italic'] = {
  directory: 'DoubleStruck/Italic',
  family: 'STIXMathJax_DoubleStruck',
  style: 'italic',
  testString: '\u00A0\u2102\u210D\u2115\u2119\u211A\u211D\u2124\u213C\u213F\u2145\u2146\u2147\u2148\u2149',
  0x20: [0,0,250,0,0],
  0xA0: [0,0,250,0,0],
  0x2102: [666,18,702,35,702],
  0x210D: [653,0,732,17,767],
  0x2115: [653,0,727,25,755],
  0x2119: [653,0,687,17,686],
  0x211A: [666,71,723,35,713],
  0x211D: [653,0,687,17,686],
  0x2124: [653,0,754,7,750],
  0x213C: [428,12,635,40,630],
  0x213F: [653,0,750,30,780],
  0x2145: [653,0,713,17,703],
  0x2146: [683,11,581,40,634],
  0x2147: [441,11,515,40,485],
  0x2148: [653,0,293,27,346],
  0x2149: [653,217,341,-104,394]
};

MathJax.Callback.Queue(
  ["initFont",MathJax.OutputJax["HTML-CSS"],"STIXMathJax_DoubleStruck-italic"],
  ["loadComplete",MathJax.Ajax,MathJax.OutputJax["HTML-CSS"].fontDir+"/DoubleStruck/Italic/Main.js"]
);
