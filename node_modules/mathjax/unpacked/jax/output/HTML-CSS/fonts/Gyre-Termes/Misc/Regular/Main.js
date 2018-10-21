/*************************************************************
 *
 *  MathJax/jax/output/HTML-CSS/fonts/Gyre-Termes/Misc/Regular/Main.js
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

MathJax.OutputJax['HTML-CSS'].FONTDATA.FONTS['GyreTermesMathJax_Misc'] = {
  directory: 'Misc/Regular',
  family: 'GyreTermesMathJax_Misc',
  testString: '\u00A0\u20A1\u20A4\u20A6\u20A9\u20AB\u20AC\u20B1\u20B2\u27A1',
  0x20: [0,0,250,0,0],
  0xA0: [0,0,250,0,0],
  0x20A1: [745,83,667,28,633],
  0x20A4: [676,8,500,12,490],
  0x20A6: [662,11,722,12,707],
  0x20A9: [662,11,944,5,932],
  0x20AB: [662,28,482,40,442],
  0x20AC: [674,15,500,4,497],
  0x20B1: [662,0,556,16,542],
  0x20B2: [745,83,722,32,709],
  0x27A1: [470,-30,1030,80,950]
};

MathJax.Callback.Queue(
  ["initFont",MathJax.OutputJax["HTML-CSS"],"GyreTermesMathJax_Misc"],
  ["loadComplete",MathJax.Ajax,MathJax.OutputJax["HTML-CSS"].fontDir+"/Misc/Regular/Main.js"]
);
