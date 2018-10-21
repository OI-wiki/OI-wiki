/*
 *  /MathJax/localization/br/br.js
 *
 *  Copyright (c) 2009-2018 The MathJax Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

MathJax.Localization.addTranslation("br",null,{menuTitle:"brezhoneg",version:"2.7.5",isLoaded:true,domains:{_:{version:"2.7.5",isLoaded:true,strings:{MathProcessingError:"Fazi o treta\u00F1 ar formulenn",MathError:"Fazi er formulenn",LoadFile:"O karga\u00F1 %1",Loading:"O karga\u00F1",LoadFailed:"N'eus ket bet gallet karga\u00F1 %1",ProcessMath:"Treta\u00F1 ar formulenno\u00F9 : %1%%",Processing:"O treta\u00F1",TypesetMath:"Aoza\u00F1 formulenno\u00F9 : %1%%",Typesetting:"Aoza\u00F1",MathJaxNotSupported:"Ne c'hall ket ho merdeer ober gant MathJax",ErrorTips:"Alio\u00F9 dizreina\u00F1 : implijout %%1, ensellet %%2, e letrin ar merdeer"}},FontWarnings:{},"HTML-CSS":{},HelpDialog:{},MathML:{},MathMenu:{},TeX:{}},plural:function(a){if(a%10===1&&!(a%100===11||a%100===71||a%100===91)){return 1}if(a%10===2&&!(a%100===12||a%100===72||a%100===92)){return 2}if((a%10===3||a%10===4||a%10===9)&&!(10<=a%100&&a%100<=19||70<=a%100&&a%100<=79||90<=a%100&&a%100<=99)){return 3}if(a!==0&&a%1000000===0){return 4}return 5},number:function(a){return a}});MathJax.Ajax.loadComplete("[MathJax]/localization/br/br.js");
