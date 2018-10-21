//
//  We need to load cssstyle's parsers.js, but its location differs
//  between node 4 and node 5, so check which one we have.
//

var PARSERS = 'cssstyle/lib/parsers.js';

//
//  Patch for CSSStyleDeclaration lengthRegEx so that it includes ex units
//  (plus a number of other units that are left out)
//  
var FixValueType = function () {
  var parsers = require(PARSERS);
  
  var integerRegEx = /^[\-+]?[0-9]+$/;
  var numberRegEx = /^[\-+]?[0-9]*\.[0-9]+$/;
  var lengthRegEx = /^(0|[\-+]?[0-9]*\.?[0-9]+(in|cm|mm|pt|pc|px|em|ex|ch|rem|vh|vw|vmin|vmax))$/;
  var percentRegEx = /^[\-+]?[0-9]*\.?[0-9]+%$/;
  var urlRegEx = /^url\(\s*([^\)]*)\s*\)$/;
  var stringRegEx = /^(\"[^\"]*\"|\'[^\']*\')$/;
  var colorRegEx1 = /^#[0-9a-fA-F][0-9a-fA-F][0-9a-fA-F]([0-9a-fA-F][0-9a-fA-F][0-9a-fA-F])?$/;
  var colorRegEx2 = /^rgb\(([^\)]*)\)$/;
  var colorRegEx3 = /^rgba\(([^\)]*)\)$/;
  var angleRegEx = /^([\-+]?[0-9]*\.?[0-9]+)(deg|grad|rad)$/;

  parsers.valueType = function valueType(val) {
    var TYPES = parsers.TYPES;
    if (val === '' || val === null) return TYPES.NULL_OR_EMPTY_STR;
    if (typeof val === 'number') val = val.toString();
    if (typeof val !== 'string') return undefined;

    if (integerRegEx.test(val)) return TYPES.INTEGER;
    if (numberRegEx.test(val))  return TYPES.NUMBER;
    if (lengthRegEx.test(val))  return TYPES.LENGTH;
    if (percentRegEx.test(val)) return TYPES.PERCENT;
    if (urlRegEx.test(val))     return TYPES.URL;
    if (stringRegEx.test(val))  return TYPES.STRING;
    if (angleRegEx.test(val))   return TYPES.ANGLE;
    if (colorRegEx1.test(val))  return TYPES.COLOR;
    var res = colorRegEx2.exec(val);
    var parts;
    if (res !== null) {
      parts = res[1].split(/\s*,\s*/);
      if (parts.length !== 3) return undefined;
      if (parts.every(percentRegEx.test.bind(percentRegEx)) ||
          parts.every(integerRegEx.test.bind(integerRegEx))) return TYPES.COLOR;
      return undefined;
    }
    res = colorRegEx3.exec(val);
    if (res !== null) {
      parts = res[1].split(/\s*,\s*/);
      if (parts.length !== 4) return undefined;
      if (parts.slice(0, 3).every(percentRegEx.test.bind(percentRegEx)) ||
          parts.every(integerRegEx.test.bind(integerRegEx))) {
        if (numberRegEx.test(parts[3])) return TYPES.COLOR;
      }
      return undefined;
    }
    val = val.toLowerCase();
    switch (val) {
     case 'maroon':
     case 'red':
     case 'orange':
     case 'yellow':
     case 'olive':
     case 'purple':
     case 'fuchsia':
     case 'white':
     case 'lime':
     case 'green':
     case 'navy':
     case 'blue':
     case 'aqua':
     case 'teal':
     case 'black':
     case 'silver':
     case 'gray':
      // the following are deprecated in CSS3
     case 'activeborder':
     case 'activecaption':
     case 'appworkspace':
     case 'background':
     case 'buttonface':
     case 'buttonhighlight':
     case 'buttonshadow':
     case 'buttontext':
     case 'captiontext':
     case 'graytext':
     case 'highlight':
     case 'highlighttext':
     case 'inactiveborder':
     case 'inactivecaption':
     case 'inactivecaptiontext':
     case 'infobackground':
     case 'infotext':
     case 'menu':
     case 'menutext':
     case 'scrollbar':
     case 'threeddarkshadow':
     case 'threedface':
     case 'threedhighlight':
     case 'threedlightshadow':
     case 'threedshadow':
     case 'window':
     case 'windowframe':
     case 'windowtext':
      return TYPES.COLOR;
     default:
      return TYPES.KEYWORD;
    }
  };
}


//
//  Patch jsdom functions
//
exports.patch = function (JSDOM) {
  var window = new JSDOM('').window;
  var document = window.document;

  var div = document.createElement("div");

  //
  //  Check if units of ex are allowed
  //
  div.style.marginTop = "3ex";
  if (div.style.marginTop !== "3ex") FixValueType();
}
