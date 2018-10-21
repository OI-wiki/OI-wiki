/*************************************************************
 *
 *  MathJax/jax/output/HTML-CSS/fonts/Gyre-Termes/Variants/Regular/Main.js
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

MathJax.OutputJax['HTML-CSS'].FONTDATA.FONTS['GyreTermesMathJax_Variants'] = {
  directory: 'Variants/Regular',
  family: 'GyreTermesMathJax_Variants',
  testString: '\u00A0\u2032\u2033\u2034\u2035\u2036\u2037\u2057',
  0x20: [0,0,250,0,0],
  0xA0: [0,0,250,0,0],
  0x2032: [596,-150,404,66,338],
  0x2033: [596,-150,644,66,578],
  0x2034: [596,-150,884,66,818],
  0x2035: [596,-150,404,66,338],
  0x2036: [596,-150,644,66,578],
  0x2037: [596,-150,884,66,818],
  0x2057: [596,-150,1124,66,1058]
};

MathJax.Callback.Queue(
  ["initFont",MathJax.OutputJax["HTML-CSS"],"GyreTermesMathJax_Variants"],
  ["loadComplete",MathJax.Ajax,MathJax.OutputJax["HTML-CSS"].fontDir+"/Variants/Regular/Main.js"]
);
