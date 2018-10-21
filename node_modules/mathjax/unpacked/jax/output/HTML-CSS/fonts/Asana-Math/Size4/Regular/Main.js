/*************************************************************
 *
 *  MathJax/jax/output/HTML-CSS/fonts/Asana-Math/Size4/Regular/Main.js
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

MathJax.OutputJax['HTML-CSS'].FONTDATA.FONTS['AsanaMathJax_Size4'] = {
  directory: 'Size4/Regular',
  family: 'AsanaMathJax_Size4',
  testString: '\u0302\u0303\u0306\u030C\u2016\u2044\u20D6\u20D7\u221A\u27C5\u27C6\u27E6\u27E7',
  0x20: [0,0,249,0,0],
  0x7C: [1428,887,272,86,187],
  0x302: [783,-627,2017,0,2017],
  0x303: [772,-642,1864,0,1865],
  0x306: [664,-506,1761,0,1762],
  0x30C: [792,-627,1959,0,1960],
  0x2016: [1428,887,553,86,468],
  0x2044: [1234,955,564,-254,568],
  0x20D6: [790,-519,3579,0,3579],
  0x20D7: [790,-519,3579,0,3579],
  0x221A: [3175,0,946,63,979],
  0x27C5: [1276,1276,450,53,397],
  0x27C6: [1276,1276,450,53,397],
  0x27E6: [1704,852,534,84,504],
  0x27E7: [1704,852,534,84,504]
};

MathJax.Callback.Queue(
  ["initFont",MathJax.OutputJax["HTML-CSS"],"AsanaMathJax_Size4"],
  ["loadComplete",MathJax.Ajax,MathJax.OutputJax["HTML-CSS"].fontDir+"/Size4/Regular/Main.js"]
);
