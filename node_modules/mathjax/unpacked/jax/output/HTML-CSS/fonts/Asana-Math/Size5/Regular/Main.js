/*************************************************************
 *
 *  MathJax/jax/output/HTML-CSS/fonts/Asana-Math/Size5/Regular/Main.js
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

MathJax.OutputJax['HTML-CSS'].FONTDATA.FONTS['AsanaMathJax_Size5'] = {
  directory: 'Size5/Regular',
  family: 'AsanaMathJax_Size5',
  testString: '\u0302\u0303\u030C\u27C5\u27C6',
  0x20: [0,0,249,0,0],
  0x7C: [1673,1039,288,85,203],
  0x302: [783,-627,3026,0,3026],
  0x303: [772,-642,2797,0,2797],
  0x30C: [792,-627,2940,0,2940],
  0x27C5: [1260,1803,450,53,397],
  0x27C6: [1260,1803,450,53,397]
};

MathJax.Callback.Queue(
  ["initFont",MathJax.OutputJax["HTML-CSS"],"AsanaMathJax_Size5"],
  ["loadComplete",MathJax.Ajax,MathJax.OutputJax["HTML-CSS"].fontDir+"/Size5/Regular/Main.js"]
);
