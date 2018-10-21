/*************************************************************
 *
 *  MathJax/jax/output/HTML-CSS/fonts/Neo-Euler/Variants/Regular/Main.js
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

MathJax.OutputJax['HTML-CSS'].FONTDATA.FONTS['NeoEulerMathJax_Variants'] = {
  directory: 'Variants/Regular',
  family: 'NeoEulerMathJax_Variants',
  testString: '\u00A0\u2032\u2033\u2034\u2035\u2036\u2037\u2057\uE200\uE201\uE202\uE203\uE204\uE205\uE206',
  0x20: [0,0,333,0,0],
  0xA0: [0,0,333,0,0],
  0x2032: [559,-41,329,48,299],
  0x2033: [559,-41,640,48,610],
  0x2034: [559,-41,950,48,920],
  0x2035: [559,-41,329,48,299],
  0x2036: [559,-41,640,48,610],
  0x2037: [559,-41,950,48,919],
  0x2057: [559,-41,1260,48,1230],
  0xE200: [493,13,501,41,456],
  0xE201: [469,1,501,46,460],
  0xE202: [474,-1,501,59,485],
  0xE203: [474,182,501,38,430],
  0xE204: [476,192,501,10,482],
  0xE205: [458,184,501,47,441],
  0xE206: [700,13,501,45,471],
  0xE207: [468,181,501,37,498],
  0xE208: [706,10,501,40,461],
  0xE209: [470,182,501,27,468]
};

MathJax.Callback.Queue(
  ["initFont",MathJax.OutputJax["HTML-CSS"],"NeoEulerMathJax_Variants"],
  ["loadComplete",MathJax.Ajax,MathJax.OutputJax["HTML-CSS"].fontDir+"/Variants/Regular/Main.js"]
);
