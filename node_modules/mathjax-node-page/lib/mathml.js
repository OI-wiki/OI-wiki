/************************************************************************
 *  Copyright (c) 2016 The MathJax Consortium
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
var mathml2jax = function() {};

mathml2jax.prototype.config = {
    doc: {},
};
mathml2jax.prototype.MMLnamespace = "http://www.w3.org/1998/Math/MathML";

mathml2jax.prototype.PreProcess = function(element) {
    if (typeof(element) === "string") {
         element = this.config.doc.getElementById(element)
    }
    if (!element) {
        element = this.config.doc.body
    }
    // BUG jsdom failed to loop through getElementsByTagName results?
    var maths = element.querySelectorAll('math');
    for (var m = 0; m < maths.length; m++){
      this.ProcessMath(maths[m]);
    }

};

mathml2jax.prototype.ProcessMath = function(math) {
    var parent = math.parentNode;
    var script = this.config.doc.createElement("script");
    script.type = "math/MathML";
    if (math.getAttribute('display') === 'block') script.type += '-block';
    parent.replaceChild(script, math);
    script.text = math.outerHTML;
};


exports.mathml2jax = new mathml2jax();
