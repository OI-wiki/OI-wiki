/*************************************************************
 *
 *  MathJax/jax/output/HTML-CSS/fonts/Latin-Modern/Misc/Regular/Main.js
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

MathJax.OutputJax['HTML-CSS'].FONTDATA.FONTS['LatinModernMathJax_Misc'] = {
  directory: 'Misc/Regular',
  family: 'LatinModernMathJax_Misc',
  testString: '\u00A0\u20A1\u20AC\u275A\u27A1',
  0x20: [0,0,332,0,0],
  0xA0: [0,0,332,0,0],
  0x20A1: [728,45,722,56,665],
  0x20AC: [705,22,627,54,571],
  0x275A: [694,83,525,227,297],
  0x27A1: [468,-31,977,56,921]
};

MathJax.Callback.Queue(
  ["initFont",MathJax.OutputJax["HTML-CSS"],"LatinModernMathJax_Misc"],
  ["loadComplete",MathJax.Ajax,MathJax.OutputJax["HTML-CSS"].fontDir+"/Misc/Regular/Main.js"]
);
