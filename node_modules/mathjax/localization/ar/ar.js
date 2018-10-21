/*
 *  /MathJax/localization/ar/ar.js
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

MathJax.Localization.addTranslation("ar",null,{menuTitle:"\u0627\u0644\u0639\u0631\u0628\u064A\u0629",fontDirection:"rtl",version:"2.7.5",isLoaded:true,domains:{_:{version:"2.7.5",isLoaded:true,strings:{MathProcessingError:"\u062E\u0637\u0623 \u0645\u0639\u0627\u0644\u062C\u0629 \u0631\u064A\u0627\u0636\u064A\u0629",MathError:"\u062E\u0637\u0623 \u0631\u064A\u0627\u0636\u064A",LoadFile:"\u062A\u062D\u0645\u064A\u0644 %1",Loading:"\u062C\u0627\u0631\u064D \u0627\u0644\u062A\u062D\u0645\u064A\u0644",LoadFailed:"\u0641\u0634\u0644 \u062A\u062D\u0645\u064A\u0644 \u0627\u0644\u0645\u0644\u0641: %1",ProcessMath:"\u0639\u0645\u0644\u064A\u0629 \u0631\u064A\u0627\u0636\u064A\u0629: %1%%",Processing:"\u0645\u0639\u0627\u0644\u062C\u0629",TypesetMath:"\u062A\u0646\u0636\u064A\u062F \u0631\u064A\u0627\u0636\u064A: %1%%",Typesetting:"\u062A\u0646\u0636\u064A\u062F",MathJaxNotSupported:"\u0645\u062A\u0635\u0641\u062D\u0643 \u0644\u0627 \u064A\u062F\u0639\u0645 \u0645\u0627\u062B\u062C\u0627\u0643\u0633"}},FontWarnings:{},"HTML-CSS":{},HelpDialog:{},MathML:{},MathMenu:{},TeX:{}},plural:function(a){if(a===0){return 1}if(a===1){return 2}if(a===2){return 3}if(3<=a%100&&a%100<=10){return 4}if(11<=a%100&&a%100<=99){return 5}return 6},number:function(a){return String(a).replace("/([0-9])/g","\\U066$1").replace(".","\\U066B")}});MathJax.Ajax.loadComplete("[MathJax]/localization/ar/ar.js");
