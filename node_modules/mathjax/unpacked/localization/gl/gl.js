/*************************************************************
 *
 *  MathJax/localization/gl/gl.js
 *
 *  Copyright (c) 2009-2018 The MathJax Consortium
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
 *
 */
MathJax.Localization.addTranslation("gl",null,{
  menuTitle: "galego",
  version: "2.7.5",
  isLoaded: true,
  domains: {
    "_": {
        version: "2.7.5",
        isLoaded: true,
        strings: {
          CookieConfig: "MathJax atopou unha cookie de configuraci\u00F3n de usuario que incl\u00FAe c\u00F3digo executable. Quere executar ese c\u00F3digo?\n\n(Deber\u00EDa premer en \"Cancelar\", a menos que vostede crease a cookie.)",
          MathProcessingError: "Erro de procesamento da f\u00F3rmula matem\u00E1tica",
          MathError: "Erro na f\u00F3rmula matem\u00E1tica",
          LoadFile: "Cargando \"%1\"",
          Loading: "Cargando",
          LoadFailed: "Erro ao cargar o ficheiro: %1",
          ProcessMath: "Procesando as f\u00F3rmulas: %1%%",
          Processing: "Procesando",
          TypesetMath: "Compo\u00F1endo as f\u00F3rmulas: %1%%",
          Typesetting: "Compo\u00F1endo",
          MathJaxNotSupported: "O seu navegador non soporta MathJax"
        }
    },
    "FontWarnings": {},
    "HTML-CSS": {},
    "HelpDialog": {},
    "MathML": {},
    "MathMenu": {},
    "TeX": {}
  },
  plural: function (n) {
      if (n === 1) return 1; // one
      return 2; // other
    },
  number: function (n) {
      return n;
    }
});

MathJax.Ajax.loadComplete("[MathJax]/localization/gl/gl.js");
