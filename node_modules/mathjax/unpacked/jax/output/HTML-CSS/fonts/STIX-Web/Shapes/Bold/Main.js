/*************************************************************
 *
 *  MathJax/jax/output/HTML-CSS/fonts/STIX-Web/Shapes/Bold/Main.js
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

MathJax.OutputJax['HTML-CSS'].FONTDATA.FONTS['STIXMathJax_Shapes-bold'] = {
  directory: 'Shapes/Bold',
  family: 'STIXMathJax_Shapes',
  weight: 'bold',
  testString: '\u00A0\u2423\u25B7\u25C1\u25EC\uE000\uE001\uE0B0\uE0B1\uE0B2\uE10E\uE10F\uE28F\uE290',
  0x20: [0,0,250,0,0],
  0xA0: [0,0,250,0,0],
  0x2423: [31,120,500,40,460],
  0x25B7: [791,284,1043,70,1008],
  0x25C1: [791,284,1043,35,973],
  0x25EC: [811,127,1145,35,1110],
  0xE000: [610,25,1184,808,912],
  0xE001: [704,-75,1198,808,1224],
  0xE0B0: [752,-531,0,100,417],
  0xE0B1: [-50,271,0,100,417],
  0xE0B2: [-50,271,0,99,416],
  0xE10E: [405,-101,714,211,503],
  0xE10F: [399,-107,315,0,315],
  0xE28F: [175,0,325,-1,326],
  0xE290: [175,0,633,-1,634]
};

MathJax.Callback.Queue(
  ["initFont",MathJax.OutputJax["HTML-CSS"],"STIXMathJax_Shapes-bold"],
  ["loadComplete",MathJax.Ajax,MathJax.OutputJax["HTML-CSS"].fontDir+"/Shapes/Bold/Main.js"]
);
