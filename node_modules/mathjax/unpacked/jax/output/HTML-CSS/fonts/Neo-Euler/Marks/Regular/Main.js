/*************************************************************
 *
 *  MathJax/jax/output/HTML-CSS/fonts/Neo-Euler/Marks/Regular/Main.js
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

MathJax.OutputJax['HTML-CSS'].FONTDATA.FONTS['NeoEulerMathJax_Marks'] = {
  directory: 'Marks/Regular',
  family: 'NeoEulerMathJax_Marks',
  testString: '\u00A0\u0305\u030F\u0311\u0323\u0324\u0325\u032E\u032F\u0330\u0331\u0332\u2036\u2037\u20D6',
  0x20: [0,0,333,0,0],
  0xA0: [0,0,333,0,0],
  0x305: [615,-570,0,-445,-53],
  0x30F: [683,-502,0,-497,-154],
  0x311: [671,-513,0,-390,-108],
  0x323: [-93,193,0,-225,-125],
  0x324: [-93,193,0,-399,-100],
  0x325: [-43,243,0,-349,-149],
  0x32E: [-78,207,0,-388,-83],
  0x32F: [-78,207,0,-388,-83],
  0x330: [-95,196,0,-389,-68],
  0x331: [-116,169,0,-405,-93],
  0x332: [-120,165,0,-445,-53],
  0x2036: [782,-422,433,30,386],
  0x2037: [782,-422,626,30,578],
  0x20D6: [750,-479,287,-131,287],
  0x20DB: [642,-542,0,-599,-100],
  0x20DC: [642,-542,0,-799,-100],
  0x20DD: [716,216,1000,55,944],
  0x20E1: [750,-479,449,0,449],
  0x20EE: [50,221,287,-131,287],
  0x20EF: [50,221,287,0,418]
};

MathJax.Callback.Queue(
  ["initFont",MathJax.OutputJax["HTML-CSS"],"NeoEulerMathJax_Marks"],
  ["loadComplete",MathJax.Ajax,MathJax.OutputJax["HTML-CSS"].fontDir+"/Marks/Regular/Main.js"]
);
