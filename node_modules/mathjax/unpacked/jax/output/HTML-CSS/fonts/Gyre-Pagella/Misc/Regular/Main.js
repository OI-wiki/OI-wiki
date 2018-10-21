/*************************************************************
 *
 *  MathJax/jax/output/HTML-CSS/fonts/Gyre-Pagella/Misc/Regular/Main.js
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

MathJax.OutputJax['HTML-CSS'].FONTDATA.FONTS['GyrePagellaMathJax_Misc'] = {
  directory: 'Misc/Regular',
  family: 'GyrePagellaMathJax_Misc',
  testString: '\u00A0\u20A1\u20A4\u20A6\u20A9\u20AB\u20AC\u20B1\u20B2\u27A1',
  0x20: [0,0,250,0,0],
  0xA0: [0,0,250,0,0],
  0x20A1: [775,83,709,22,670],
  0x20A4: [694,13,500,12,478],
  0x20A6: [692,20,831,17,813],
  0x20A9: [700,9,1000,8,984],
  0x20AB: [692,34,542,40,502],
  0x20AC: [689,20,500,-2,501],
  0x20B1: [692,3,604,22,580],
  0x20B2: [775,83,763,22,728],
  0x27A1: [450,-50,995,80,915]
};

MathJax.Callback.Queue(
  ["initFont",MathJax.OutputJax["HTML-CSS"],"GyrePagellaMathJax_Misc"],
  ["loadComplete",MathJax.Ajax,MathJax.OutputJax["HTML-CSS"].fontDir+"/Misc/Regular/Main.js"]
);
