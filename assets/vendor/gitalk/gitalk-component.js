(function webpackUniversalModuleDefinition(root, factory) {
	if(typeof exports === 'object' && typeof module === 'object')
		module.exports = factory(require("react"), require("react-dom"));
	else if(typeof define === 'function' && define.amd)
		define(["react", "react-dom"], factory);
	else if(typeof exports === 'object')
		exports["Gitalk"] = factory(require("react"), require("react-dom"));
	else
		root["Gitalk"] = factory(root["react"], root["react-dom"]);
})(this, function(__WEBPACK_EXTERNAL_MODULE_9__, __WEBPACK_EXTERNAL_MODULE_135__) {
return /******/ (function(modules) { // webpackBootstrap
/******/ 	// The module cache
/******/ 	var installedModules = {};
/******/
/******/ 	// The require function
/******/ 	function __webpack_require__(moduleId) {
/******/
/******/ 		// Check if module is in cache
/******/ 		if(installedModules[moduleId]) {
/******/ 			return installedModules[moduleId].exports;
/******/ 		}
/******/ 		// Create a new module (and put it into the cache)
/******/ 		var module = installedModules[moduleId] = {
/******/ 			i: moduleId,
/******/ 			l: false,
/******/ 			exports: {}
/******/ 		};
/******/
/******/ 		// Execute the module function
/******/ 		modules[moduleId].call(module.exports, module, module.exports, __webpack_require__);
/******/
/******/ 		// Flag the module as loaded
/******/ 		module.l = true;
/******/
/******/ 		// Return the exports of the module
/******/ 		return module.exports;
/******/ 	}
/******/
/******/
/******/ 	// expose the modules object (__webpack_modules__)
/******/ 	__webpack_require__.m = modules;
/******/
/******/ 	// expose the module cache
/******/ 	__webpack_require__.c = installedModules;
/******/
/******/ 	// define getter function for harmony exports
/******/ 	__webpack_require__.d = function(exports, name, getter) {
/******/ 		if(!__webpack_require__.o(exports, name)) {
/******/ 			Object.defineProperty(exports, name, {
/******/ 				configurable: false,
/******/ 				enumerable: true,
/******/ 				get: getter
/******/ 			});
/******/ 		}
/******/ 	};
/******/
/******/ 	// getDefaultExport function for compatibility with non-harmony modules
/******/ 	__webpack_require__.n = function(module) {
/******/ 		var getter = module && module.__esModule ?
/******/ 			function getDefault() { return module['default']; } :
/******/ 			function getModuleExports() { return module; };
/******/ 		__webpack_require__.d(getter, 'a', getter);
/******/ 		return getter;
/******/ 	};
/******/
/******/ 	// Object.prototype.hasOwnProperty.call
/******/ 	__webpack_require__.o = function(object, property) { return Object.prototype.hasOwnProperty.call(object, property); };
/******/
/******/ 	// __webpack_public_path__
/******/ 	__webpack_require__.p = "/dist";
/******/
/******/ 	// Load entry module and return exports
/******/ 	return __webpack_require__(__webpack_require__.s = 80);
/******/ })
/************************************************************************/
/******/ ([
/* 0 */
/***/ (function(module, exports) {

var core = module.exports = { version: '2.6.12' };
if (typeof __e == 'number') __e = core; // eslint-disable-line no-undef


/***/ }),
/* 1 */
/***/ (function(module, exports) {

// https://github.com/zloirock/core-js/issues/86#issuecomment-115759028
var global = module.exports = typeof window != 'undefined' && window.Math == Math
  ? window : typeof self != 'undefined' && self.Math == Math ? self
  // eslint-disable-next-line no-new-func
  : Function('return this')();
if (typeof __g == 'number') __g = global; // eslint-disable-line no-undef


/***/ }),
/* 2 */
/***/ (function(module, exports, __webpack_require__) {

var store = __webpack_require__(35)('wks');
var uid = __webpack_require__(24);
var Symbol = __webpack_require__(1).Symbol;
var USE_SYMBOL = typeof Symbol == 'function';

var $exports = module.exports = function (name) {
  return store[name] || (store[name] =
    USE_SYMBOL && Symbol[name] || (USE_SYMBOL ? Symbol : uid)('Symbol.' + name));
};

$exports.store = store;


/***/ }),
/* 3 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";


var bind = __webpack_require__(70);

/*global toString:true*/

// utils is a library of generic helper functions non-specific to axios

var toString = Object.prototype.toString;

/**
 * Determine if a value is an Array
 *
 * @param {Object} val The value to test
 * @returns {boolean} True if value is an Array, otherwise false
 */
function isArray(val) {
  return toString.call(val) === '[object Array]';
}

/**
 * Determine if a value is undefined
 *
 * @param {Object} val The value to test
 * @returns {boolean} True if the value is undefined, otherwise false
 */
function isUndefined(val) {
  return typeof val === 'undefined';
}

/**
 * Determine if a value is a Buffer
 *
 * @param {Object} val The value to test
 * @returns {boolean} True if value is a Buffer, otherwise false
 */
function isBuffer(val) {
  return val !== null && !isUndefined(val) && val.constructor !== null && !isUndefined(val.constructor)
    && typeof val.constructor.isBuffer === 'function' && val.constructor.isBuffer(val);
}

/**
 * Determine if a value is an ArrayBuffer
 *
 * @param {Object} val The value to test
 * @returns {boolean} True if value is an ArrayBuffer, otherwise false
 */
function isArrayBuffer(val) {
  return toString.call(val) === '[object ArrayBuffer]';
}

/**
 * Determine if a value is a FormData
 *
 * @param {Object} val The value to test
 * @returns {boolean} True if value is an FormData, otherwise false
 */
function isFormData(val) {
  return (typeof FormData !== 'undefined') && (val instanceof FormData);
}

/**
 * Determine if a value is a view on an ArrayBuffer
 *
 * @param {Object} val The value to test
 * @returns {boolean} True if value is a view on an ArrayBuffer, otherwise false
 */
function isArrayBufferView(val) {
  var result;
  if ((typeof ArrayBuffer !== 'undefined') && (ArrayBuffer.isView)) {
    result = ArrayBuffer.isView(val);
  } else {
    result = (val) && (val.buffer) && (val.buffer instanceof ArrayBuffer);
  }
  return result;
}

/**
 * Determine if a value is a String
 *
 * @param {Object} val The value to test
 * @returns {boolean} True if value is a String, otherwise false
 */
function isString(val) {
  return typeof val === 'string';
}

/**
 * Determine if a value is a Number
 *
 * @param {Object} val The value to test
 * @returns {boolean} True if value is a Number, otherwise false
 */
function isNumber(val) {
  return typeof val === 'number';
}

/**
 * Determine if a value is an Object
 *
 * @param {Object} val The value to test
 * @returns {boolean} True if value is an Object, otherwise false
 */
function isObject(val) {
  return val !== null && typeof val === 'object';
}

/**
 * Determine if a value is a Date
 *
 * @param {Object} val The value to test
 * @returns {boolean} True if value is a Date, otherwise false
 */
function isDate(val) {
  return toString.call(val) === '[object Date]';
}

/**
 * Determine if a value is a File
 *
 * @param {Object} val The value to test
 * @returns {boolean} True if value is a File, otherwise false
 */
function isFile(val) {
  return toString.call(val) === '[object File]';
}

/**
 * Determine if a value is a Blob
 *
 * @param {Object} val The value to test
 * @returns {boolean} True if value is a Blob, otherwise false
 */
function isBlob(val) {
  return toString.call(val) === '[object Blob]';
}

/**
 * Determine if a value is a Function
 *
 * @param {Object} val The value to test
 * @returns {boolean} True if value is a Function, otherwise false
 */
function isFunction(val) {
  return toString.call(val) === '[object Function]';
}

/**
 * Determine if a value is a Stream
 *
 * @param {Object} val The value to test
 * @returns {boolean} True if value is a Stream, otherwise false
 */
function isStream(val) {
  return isObject(val) && isFunction(val.pipe);
}

/**
 * Determine if a value is a URLSearchParams object
 *
 * @param {Object} val The value to test
 * @returns {boolean} True if value is a URLSearchParams object, otherwise false
 */
function isURLSearchParams(val) {
  return typeof URLSearchParams !== 'undefined' && val instanceof URLSearchParams;
}

/**
 * Trim excess whitespace off the beginning and end of a string
 *
 * @param {String} str The String to trim
 * @returns {String} The String freed of excess whitespace
 */
function trim(str) {
  return str.replace(/^\s*/, '').replace(/\s*$/, '');
}

/**
 * Determine if we're running in a standard browser environment
 *
 * This allows axios to run in a web worker, and react-native.
 * Both environments support XMLHttpRequest, but not fully standard globals.
 *
 * web workers:
 *  typeof window -> undefined
 *  typeof document -> undefined
 *
 * react-native:
 *  navigator.product -> 'ReactNative'
 * nativescript
 *  navigator.product -> 'NativeScript' or 'NS'
 */
function isStandardBrowserEnv() {
  if (typeof navigator !== 'undefined' && (navigator.product === 'ReactNative' ||
                                           navigator.product === 'NativeScript' ||
                                           navigator.product === 'NS')) {
    return false;
  }
  return (
    typeof window !== 'undefined' &&
    typeof document !== 'undefined'
  );
}

/**
 * Iterate over an Array or an Object invoking a function for each item.
 *
 * If `obj` is an Array callback will be called passing
 * the value, index, and complete array for each item.
 *
 * If 'obj' is an Object callback will be called passing
 * the value, key, and complete object for each property.
 *
 * @param {Object|Array} obj The object to iterate
 * @param {Function} fn The callback to invoke for each item
 */
function forEach(obj, fn) {
  // Don't bother if no value provided
  if (obj === null || typeof obj === 'undefined') {
    return;
  }

  // Force an array if not already something iterable
  if (typeof obj !== 'object') {
    /*eslint no-param-reassign:0*/
    obj = [obj];
  }

  if (isArray(obj)) {
    // Iterate over array values
    for (var i = 0, l = obj.length; i < l; i++) {
      fn.call(null, obj[i], i, obj);
    }
  } else {
    // Iterate over object keys
    for (var key in obj) {
      if (Object.prototype.hasOwnProperty.call(obj, key)) {
        fn.call(null, obj[key], key, obj);
      }
    }
  }
}

/**
 * Accepts varargs expecting each argument to be an object, then
 * immutably merges the properties of each object and returns result.
 *
 * When multiple objects contain the same key the later object in
 * the arguments list will take precedence.
 *
 * Example:
 *
 * ```js
 * var result = merge({foo: 123}, {foo: 456});
 * console.log(result.foo); // outputs 456
 * ```
 *
 * @param {Object} obj1 Object to merge
 * @returns {Object} Result of all merge properties
 */
function merge(/* obj1, obj2, obj3, ... */) {
  var result = {};
  function assignValue(val, key) {
    if (typeof result[key] === 'object' && typeof val === 'object') {
      result[key] = merge(result[key], val);
    } else {
      result[key] = val;
    }
  }

  for (var i = 0, l = arguments.length; i < l; i++) {
    forEach(arguments[i], assignValue);
  }
  return result;
}

/**
 * Function equal to merge with the difference being that no reference
 * to original objects is kept.
 *
 * @see merge
 * @param {Object} obj1 Object to merge
 * @returns {Object} Result of all merge properties
 */
function deepMerge(/* obj1, obj2, obj3, ... */) {
  var result = {};
  function assignValue(val, key) {
    if (typeof result[key] === 'object' && typeof val === 'object') {
      result[key] = deepMerge(result[key], val);
    } else if (typeof val === 'object') {
      result[key] = deepMerge({}, val);
    } else {
      result[key] = val;
    }
  }

  for (var i = 0, l = arguments.length; i < l; i++) {
    forEach(arguments[i], assignValue);
  }
  return result;
}

/**
 * Extends object a by mutably adding to it the properties of object b.
 *
 * @param {Object} a The object to be extended
 * @param {Object} b The object to copy properties from
 * @param {Object} thisArg The object to bind function to
 * @return {Object} The resulting value of object a
 */
function extend(a, b, thisArg) {
  forEach(b, function assignValue(val, key) {
    if (thisArg && typeof val === 'function') {
      a[key] = bind(val, thisArg);
    } else {
      a[key] = val;
    }
  });
  return a;
}

module.exports = {
  isArray: isArray,
  isArrayBuffer: isArrayBuffer,
  isBuffer: isBuffer,
  isFormData: isFormData,
  isArrayBufferView: isArrayBufferView,
  isString: isString,
  isNumber: isNumber,
  isObject: isObject,
  isUndefined: isUndefined,
  isDate: isDate,
  isFile: isFile,
  isBlob: isBlob,
  isFunction: isFunction,
  isStream: isStream,
  isURLSearchParams: isURLSearchParams,
  isStandardBrowserEnv: isStandardBrowserEnv,
  forEach: forEach,
  merge: merge,
  deepMerge: deepMerge,
  extend: extend,
  trim: trim
};


/***/ }),
/* 4 */
/***/ (function(module, exports, __webpack_require__) {

var global = __webpack_require__(1);
var core = __webpack_require__(0);
var ctx = __webpack_require__(12);
var hide = __webpack_require__(10);
var has = __webpack_require__(11);
var PROTOTYPE = 'prototype';

var $export = function (type, name, source) {
  var IS_FORCED = type & $export.F;
  var IS_GLOBAL = type & $export.G;
  var IS_STATIC = type & $export.S;
  var IS_PROTO = type & $export.P;
  var IS_BIND = type & $export.B;
  var IS_WRAP = type & $export.W;
  var exports = IS_GLOBAL ? core : core[name] || (core[name] = {});
  var expProto = exports[PROTOTYPE];
  var target = IS_GLOBAL ? global : IS_STATIC ? global[name] : (global[name] || {})[PROTOTYPE];
  var key, own, out;
  if (IS_GLOBAL) source = name;
  for (key in source) {
    // contains in native
    own = !IS_FORCED && target && target[key] !== undefined;
    if (own && has(exports, key)) continue;
    // export native or passed
    out = own ? target[key] : source[key];
    // prevent global pollution for namespaces
    exports[key] = IS_GLOBAL && typeof target[key] != 'function' ? source[key]
    // bind timers to global for call from export context
    : IS_BIND && own ? ctx(out, global)
    // wrap global constructors for prevent change them in library
    : IS_WRAP && target[key] == out ? (function (C) {
      var F = function (a, b, c) {
        if (this instanceof C) {
          switch (arguments.length) {
            case 0: return new C();
            case 1: return new C(a);
            case 2: return new C(a, b);
          } return new C(a, b, c);
        } return C.apply(this, arguments);
      };
      F[PROTOTYPE] = C[PROTOTYPE];
      return F;
    // make static versions for prototype methods
    })(out) : IS_PROTO && typeof out == 'function' ? ctx(Function.call, out) : out;
    // export proto methods to core.%CONSTRUCTOR%.methods.%NAME%
    if (IS_PROTO) {
      (exports.virtual || (exports.virtual = {}))[key] = out;
      // export proto methods to core.%CONSTRUCTOR%.prototype.%NAME%
      if (type & $export.R && expProto && !expProto[key]) hide(expProto, key, out);
    }
  }
};
// type bitmap
$export.F = 1;   // forced
$export.G = 2;   // global
$export.S = 4;   // static
$export.P = 8;   // proto
$export.B = 16;  // bind
$export.W = 32;  // wrap
$export.U = 64;  // safe
$export.R = 128; // real proto method for `library`
module.exports = $export;


/***/ }),
/* 5 */
/***/ (function(module, exports, __webpack_require__) {

var isObject = __webpack_require__(8);
module.exports = function (it) {
  if (!isObject(it)) throw TypeError(it + ' is not an object!');
  return it;
};


/***/ }),
/* 6 */
/***/ (function(module, exports, __webpack_require__) {

var anObject = __webpack_require__(5);
var IE8_DOM_DEFINE = __webpack_require__(46);
var toPrimitive = __webpack_require__(31);
var dP = Object.defineProperty;

exports.f = __webpack_require__(7) ? Object.defineProperty : function defineProperty(O, P, Attributes) {
  anObject(O);
  P = toPrimitive(P, true);
  anObject(Attributes);
  if (IE8_DOM_DEFINE) try {
    return dP(O, P, Attributes);
  } catch (e) { /* empty */ }
  if ('get' in Attributes || 'set' in Attributes) throw TypeError('Accessors not supported!');
  if ('value' in Attributes) O[P] = Attributes.value;
  return O;
};


/***/ }),
/* 7 */
/***/ (function(module, exports, __webpack_require__) {

// Thank's IE8 for his funny defineProperty
module.exports = !__webpack_require__(13)(function () {
  return Object.defineProperty({}, 'a', { get: function () { return 7; } }).a != 7;
});


/***/ }),
/* 8 */
/***/ (function(module, exports) {

module.exports = function (it) {
  return typeof it === 'object' ? it !== null : typeof it === 'function';
};


/***/ }),
/* 9 */
/***/ (function(module, exports) {

module.exports = require("react");

/***/ }),
/* 10 */
/***/ (function(module, exports, __webpack_require__) {

var dP = __webpack_require__(6);
var createDesc = __webpack_require__(20);
module.exports = __webpack_require__(7) ? function (object, key, value) {
  return dP.f(object, key, createDesc(1, value));
} : function (object, key, value) {
  object[key] = value;
  return object;
};


/***/ }),
/* 11 */
/***/ (function(module, exports) {

var hasOwnProperty = {}.hasOwnProperty;
module.exports = function (it, key) {
  return hasOwnProperty.call(it, key);
};


/***/ }),
/* 12 */
/***/ (function(module, exports, __webpack_require__) {

// optional / simple context binding
var aFunction = __webpack_require__(23);
module.exports = function (fn, that, length) {
  aFunction(fn);
  if (that === undefined) return fn;
  switch (length) {
    case 1: return function (a) {
      return fn.call(that, a);
    };
    case 2: return function (a, b) {
      return fn.call(that, a, b);
    };
    case 3: return function (a, b, c) {
      return fn.call(that, a, b, c);
    };
  }
  return function (/* ...args */) {
    return fn.apply(that, arguments);
  };
};


/***/ }),
/* 13 */
/***/ (function(module, exports) {

module.exports = function (exec) {
  try {
    return !!exec();
  } catch (e) {
    return true;
  }
};


/***/ }),
/* 14 */
/***/ (function(module, exports) {

module.exports = {};


/***/ }),
/* 15 */
/***/ (function(module, exports, __webpack_require__) {

// to indexed object, toObject with fallback for non-array-like ES3 strings
var IObject = __webpack_require__(49);
var defined = __webpack_require__(29);
module.exports = function (it) {
  return IObject(defined(it));
};


/***/ }),
/* 16 */
/***/ (function(module, exports, __webpack_require__) {

// 7.1.13 ToObject(argument)
var defined = __webpack_require__(29);
module.exports = function (it) {
  return Object(defined(it));
};


/***/ }),
/* 17 */
/***/ (function(module, exports, __webpack_require__) {

var isDate = __webpack_require__(190)

var MILLISECONDS_IN_HOUR = 3600000
var MILLISECONDS_IN_MINUTE = 60000
var DEFAULT_ADDITIONAL_DIGITS = 2

var parseTokenDateTimeDelimeter = /[T ]/
var parseTokenPlainTime = /:/

// year tokens
var parseTokenYY = /^(\d{2})$/
var parseTokensYYY = [
  /^([+-]\d{2})$/, // 0 additional digits
  /^([+-]\d{3})$/, // 1 additional digit
  /^([+-]\d{4})$/ // 2 additional digits
]

var parseTokenYYYY = /^(\d{4})/
var parseTokensYYYYY = [
  /^([+-]\d{4})/, // 0 additional digits
  /^([+-]\d{5})/, // 1 additional digit
  /^([+-]\d{6})/ // 2 additional digits
]

// date tokens
var parseTokenMM = /^-(\d{2})$/
var parseTokenDDD = /^-?(\d{3})$/
var parseTokenMMDD = /^-?(\d{2})-?(\d{2})$/
var parseTokenWww = /^-?W(\d{2})$/
var parseTokenWwwD = /^-?W(\d{2})-?(\d{1})$/

// time tokens
var parseTokenHH = /^(\d{2}([.,]\d*)?)$/
var parseTokenHHMM = /^(\d{2}):?(\d{2}([.,]\d*)?)$/
var parseTokenHHMMSS = /^(\d{2}):?(\d{2}):?(\d{2}([.,]\d*)?)$/

// timezone tokens
var parseTokenTimezone = /([Z+-].*)$/
var parseTokenTimezoneZ = /^(Z)$/
var parseTokenTimezoneHH = /^([+-])(\d{2})$/
var parseTokenTimezoneHHMM = /^([+-])(\d{2}):?(\d{2})$/

/**
 * @category Common Helpers
 * @summary Convert the given argument to an instance of Date.
 *
 * @description
 * Convert the given argument to an instance of Date.
 *
 * If the argument is an instance of Date, the function returns its clone.
 *
 * If the argument is a number, it is treated as a timestamp.
 *
 * If an argument is a string, the function tries to parse it.
 * Function accepts complete ISO 8601 formats as well as partial implementations.
 * ISO 8601: http://en.wikipedia.org/wiki/ISO_8601
 *
 * If all above fails, the function passes the given argument to Date constructor.
 *
 * @param {Date|String|Number} argument - the value to convert
 * @param {Object} [options] - the object with options
 * @param {0 | 1 | 2} [options.additionalDigits=2] - the additional number of digits in the extended year format
 * @returns {Date} the parsed date in the local time zone
 *
 * @example
 * // Convert string '2014-02-11T11:30:30' to date:
 * var result = parse('2014-02-11T11:30:30')
 * //=> Tue Feb 11 2014 11:30:30
 *
 * @example
 * // Parse string '+02014101',
 * // if the additional number of digits in the extended year format is 1:
 * var result = parse('+02014101', {additionalDigits: 1})
 * //=> Fri Apr 11 2014 00:00:00
 */
function parse (argument, dirtyOptions) {
  if (isDate(argument)) {
    // Prevent the date to lose the milliseconds when passed to new Date() in IE10
    return new Date(argument.getTime())
  } else if (typeof argument !== 'string') {
    return new Date(argument)
  }

  var options = dirtyOptions || {}
  var additionalDigits = options.additionalDigits
  if (additionalDigits == null) {
    additionalDigits = DEFAULT_ADDITIONAL_DIGITS
  } else {
    additionalDigits = Number(additionalDigits)
  }

  var dateStrings = splitDateString(argument)

  var parseYearResult = parseYear(dateStrings.date, additionalDigits)
  var year = parseYearResult.year
  var restDateString = parseYearResult.restDateString

  var date = parseDate(restDateString, year)

  if (date) {
    var timestamp = date.getTime()
    var time = 0
    var offset

    if (dateStrings.time) {
      time = parseTime(dateStrings.time)
    }

    if (dateStrings.timezone) {
      offset = parseTimezone(dateStrings.timezone)
    } else {
      // get offset accurate to hour in timezones that change offset
      offset = new Date(timestamp + time).getTimezoneOffset()
      offset = new Date(timestamp + time + offset * MILLISECONDS_IN_MINUTE).getTimezoneOffset()
    }

    return new Date(timestamp + time + offset * MILLISECONDS_IN_MINUTE)
  } else {
    return new Date(argument)
  }
}

function splitDateString (dateString) {
  var dateStrings = {}
  var array = dateString.split(parseTokenDateTimeDelimeter)
  var timeString

  if (parseTokenPlainTime.test(array[0])) {
    dateStrings.date = null
    timeString = array[0]
  } else {
    dateStrings.date = array[0]
    timeString = array[1]
  }

  if (timeString) {
    var token = parseTokenTimezone.exec(timeString)
    if (token) {
      dateStrings.time = timeString.replace(token[1], '')
      dateStrings.timezone = token[1]
    } else {
      dateStrings.time = timeString
    }
  }

  return dateStrings
}

function parseYear (dateString, additionalDigits) {
  var parseTokenYYY = parseTokensYYY[additionalDigits]
  var parseTokenYYYYY = parseTokensYYYYY[additionalDigits]

  var token

  // YYYY or ±YYYYY
  token = parseTokenYYYY.exec(dateString) || parseTokenYYYYY.exec(dateString)
  if (token) {
    var yearString = token[1]
    return {
      year: parseInt(yearString, 10),
      restDateString: dateString.slice(yearString.length)
    }
  }

  // YY or ±YYY
  token = parseTokenYY.exec(dateString) || parseTokenYYY.exec(dateString)
  if (token) {
    var centuryString = token[1]
    return {
      year: parseInt(centuryString, 10) * 100,
      restDateString: dateString.slice(centuryString.length)
    }
  }

  // Invalid ISO-formatted year
  return {
    year: null
  }
}

function parseDate (dateString, year) {
  // Invalid ISO-formatted year
  if (year === null) {
    return null
  }

  var token
  var date
  var month
  var week

  // YYYY
  if (dateString.length === 0) {
    date = new Date(0)
    date.setUTCFullYear(year)
    return date
  }

  // YYYY-MM
  token = parseTokenMM.exec(dateString)
  if (token) {
    date = new Date(0)
    month = parseInt(token[1], 10) - 1
    date.setUTCFullYear(year, month)
    return date
  }

  // YYYY-DDD or YYYYDDD
  token = parseTokenDDD.exec(dateString)
  if (token) {
    date = new Date(0)
    var dayOfYear = parseInt(token[1], 10)
    date.setUTCFullYear(year, 0, dayOfYear)
    return date
  }

  // YYYY-MM-DD or YYYYMMDD
  token = parseTokenMMDD.exec(dateString)
  if (token) {
    date = new Date(0)
    month = parseInt(token[1], 10) - 1
    var day = parseInt(token[2], 10)
    date.setUTCFullYear(year, month, day)
    return date
  }

  // YYYY-Www or YYYYWww
  token = parseTokenWww.exec(dateString)
  if (token) {
    week = parseInt(token[1], 10) - 1
    return dayOfISOYear(year, week)
  }

  // YYYY-Www-D or YYYYWwwD
  token = parseTokenWwwD.exec(dateString)
  if (token) {
    week = parseInt(token[1], 10) - 1
    var dayOfWeek = parseInt(token[2], 10) - 1
    return dayOfISOYear(year, week, dayOfWeek)
  }

  // Invalid ISO-formatted date
  return null
}

function parseTime (timeString) {
  var token
  var hours
  var minutes

  // hh
  token = parseTokenHH.exec(timeString)
  if (token) {
    hours = parseFloat(token[1].replace(',', '.'))
    return (hours % 24) * MILLISECONDS_IN_HOUR
  }

  // hh:mm or hhmm
  token = parseTokenHHMM.exec(timeString)
  if (token) {
    hours = parseInt(token[1], 10)
    minutes = parseFloat(token[2].replace(',', '.'))
    return (hours % 24) * MILLISECONDS_IN_HOUR +
      minutes * MILLISECONDS_IN_MINUTE
  }

  // hh:mm:ss or hhmmss
  token = parseTokenHHMMSS.exec(timeString)
  if (token) {
    hours = parseInt(token[1], 10)
    minutes = parseInt(token[2], 10)
    var seconds = parseFloat(token[3].replace(',', '.'))
    return (hours % 24) * MILLISECONDS_IN_HOUR +
      minutes * MILLISECONDS_IN_MINUTE +
      seconds * 1000
  }

  // Invalid ISO-formatted time
  return null
}

function parseTimezone (timezoneString) {
  var token
  var absoluteOffset

  // Z
  token = parseTokenTimezoneZ.exec(timezoneString)
  if (token) {
    return 0
  }

  // ±hh
  token = parseTokenTimezoneHH.exec(timezoneString)
  if (token) {
    absoluteOffset = parseInt(token[2], 10) * 60
    return (token[1] === '+') ? -absoluteOffset : absoluteOffset
  }

  // ±hh:mm or ±hhmm
  token = parseTokenTimezoneHHMM.exec(timezoneString)
  if (token) {
    absoluteOffset = parseInt(token[2], 10) * 60 + parseInt(token[3], 10)
    return (token[1] === '+') ? -absoluteOffset : absoluteOffset
  }

  return 0
}

function dayOfISOYear (isoYear, week, day) {
  week = week || 0
  day = day || 0
  var date = new Date(0)
  date.setUTCFullYear(isoYear, 0, 4)
  var fourthOfJanuaryDay = date.getUTCDay() || 7
  var diff = week * 7 + day + 1 - fourthOfJanuaryDay
  date.setUTCDate(date.getUTCDate() + diff)
  return date
}

module.exports = parse


/***/ }),
/* 18 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";

var $at = __webpack_require__(83)(true);

// 21.1.3.27 String.prototype[@@iterator]()
__webpack_require__(45)(String, 'String', function (iterated) {
  this._t = String(iterated); // target
  this._i = 0;                // next index
// 21.1.5.2.1 %StringIteratorPrototype%.next()
}, function () {
  var O = this._t;
  var index = this._i;
  var point;
  if (index >= O.length) return { value: undefined, done: true };
  point = $at(O, index);
  this._i += point.length;
  return { value: point, done: false };
});


/***/ }),
/* 19 */
/***/ (function(module, exports) {

module.exports = true;


/***/ }),
/* 20 */
/***/ (function(module, exports) {

module.exports = function (bitmap, value) {
  return {
    enumerable: !(bitmap & 1),
    configurable: !(bitmap & 2),
    writable: !(bitmap & 4),
    value: value
  };
};


/***/ }),
/* 21 */
/***/ (function(module, exports, __webpack_require__) {

// 19.1.2.14 / 15.2.3.14 Object.keys(O)
var $keys = __webpack_require__(48);
var enumBugKeys = __webpack_require__(36);

module.exports = Object.keys || function keys(O) {
  return $keys(O, enumBugKeys);
};


/***/ }),
/* 22 */
/***/ (function(module, exports) {

var toString = {}.toString;

module.exports = function (it) {
  return toString.call(it).slice(8, -1);
};


/***/ }),
/* 23 */
/***/ (function(module, exports) {

module.exports = function (it) {
  if (typeof it != 'function') throw TypeError(it + ' is not a function!');
  return it;
};


/***/ }),
/* 24 */
/***/ (function(module, exports) {

var id = 0;
var px = Math.random();
module.exports = function (key) {
  return 'Symbol('.concat(key === undefined ? '' : key, ')_', (++id + px).toString(36));
};


/***/ }),
/* 25 */
/***/ (function(module, exports, __webpack_require__) {

var def = __webpack_require__(6).f;
var has = __webpack_require__(11);
var TAG = __webpack_require__(2)('toStringTag');

module.exports = function (it, tag, stat) {
  if (it && !has(it = stat ? it : it.prototype, TAG)) def(it, TAG, { configurable: true, value: tag });
};


/***/ }),
/* 26 */
/***/ (function(module, exports, __webpack_require__) {

__webpack_require__(88);
var global = __webpack_require__(1);
var hide = __webpack_require__(10);
var Iterators = __webpack_require__(14);
var TO_STRING_TAG = __webpack_require__(2)('toStringTag');

var DOMIterables = ('CSSRuleList,CSSStyleDeclaration,CSSValueList,ClientRectList,DOMRectList,DOMStringList,' +
  'DOMTokenList,DataTransferItemList,FileList,HTMLAllCollection,HTMLCollection,HTMLFormElement,HTMLSelectElement,' +
  'MediaList,MimeTypeArray,NamedNodeMap,NodeList,PaintRequestList,Plugin,PluginArray,SVGLengthList,SVGNumberList,' +
  'SVGPathSegList,SVGPointList,SVGStringList,SVGTransformList,SourceBufferList,StyleSheetList,TextTrackCueList,' +
  'TextTrackList,TouchList').split(',');

for (var i = 0; i < DOMIterables.length; i++) {
  var NAME = DOMIterables[i];
  var Collection = global[NAME];
  var proto = Collection && Collection.prototype;
  if (proto && !proto[TO_STRING_TAG]) hide(proto, TO_STRING_TAG, NAME);
  Iterators[NAME] = Iterators.Array;
}


/***/ }),
/* 27 */
/***/ (function(module, exports) {

exports.f = {}.propertyIsEnumerable;


/***/ }),
/* 28 */
/***/ (function(module, exports) {

// 7.1.4 ToInteger
var ceil = Math.ceil;
var floor = Math.floor;
module.exports = function (it) {
  return isNaN(it = +it) ? 0 : (it > 0 ? floor : ceil)(it);
};


/***/ }),
/* 29 */
/***/ (function(module, exports) {

// 7.2.1 RequireObjectCoercible(argument)
module.exports = function (it) {
  if (it == undefined) throw TypeError("Can't call method on  " + it);
  return it;
};


/***/ }),
/* 30 */
/***/ (function(module, exports, __webpack_require__) {

var isObject = __webpack_require__(8);
var document = __webpack_require__(1).document;
// typeof document.createElement is 'object' in old IE
var is = isObject(document) && isObject(document.createElement);
module.exports = function (it) {
  return is ? document.createElement(it) : {};
};


/***/ }),
/* 31 */
/***/ (function(module, exports, __webpack_require__) {

// 7.1.1 ToPrimitive(input [, PreferredType])
var isObject = __webpack_require__(8);
// instead of the ES6 spec version, we didn't implement @@toPrimitive case
// and the second argument - flag - preferred type is a string
module.exports = function (it, S) {
  if (!isObject(it)) return it;
  var fn, val;
  if (S && typeof (fn = it.toString) == 'function' && !isObject(val = fn.call(it))) return val;
  if (typeof (fn = it.valueOf) == 'function' && !isObject(val = fn.call(it))) return val;
  if (!S && typeof (fn = it.toString) == 'function' && !isObject(val = fn.call(it))) return val;
  throw TypeError("Can't convert object to primitive value");
};


/***/ }),
/* 32 */
/***/ (function(module, exports, __webpack_require__) {

// 19.1.2.2 / 15.2.3.5 Object.create(O [, Properties])
var anObject = __webpack_require__(5);
var dPs = __webpack_require__(85);
var enumBugKeys = __webpack_require__(36);
var IE_PROTO = __webpack_require__(34)('IE_PROTO');
var Empty = function () { /* empty */ };
var PROTOTYPE = 'prototype';

// Create object with fake `null` prototype: use iframe Object with cleared prototype
var createDict = function () {
  // Thrash, waste and sodomy: IE GC bug
  var iframe = __webpack_require__(30)('iframe');
  var i = enumBugKeys.length;
  var lt = '<';
  var gt = '>';
  var iframeDocument;
  iframe.style.display = 'none';
  __webpack_require__(50).appendChild(iframe);
  iframe.src = 'javascript:'; // eslint-disable-line no-script-url
  // createDict = iframe.contentWindow.Object;
  // html.removeChild(iframe);
  iframeDocument = iframe.contentWindow.document;
  iframeDocument.open();
  iframeDocument.write(lt + 'script' + gt + 'document.F=Object' + lt + '/script' + gt);
  iframeDocument.close();
  createDict = iframeDocument.F;
  while (i--) delete createDict[PROTOTYPE][enumBugKeys[i]];
  return createDict();
};

module.exports = Object.create || function create(O, Properties) {
  var result;
  if (O !== null) {
    Empty[PROTOTYPE] = anObject(O);
    result = new Empty();
    Empty[PROTOTYPE] = null;
    // add "__proto__" for Object.getPrototypeOf polyfill
    result[IE_PROTO] = O;
  } else result = createDict();
  return Properties === undefined ? result : dPs(result, Properties);
};


/***/ }),
/* 33 */
/***/ (function(module, exports, __webpack_require__) {

// 7.1.15 ToLength
var toInteger = __webpack_require__(28);
var min = Math.min;
module.exports = function (it) {
  return it > 0 ? min(toInteger(it), 0x1fffffffffffff) : 0; // pow(2, 53) - 1 == 9007199254740991
};


/***/ }),
/* 34 */
/***/ (function(module, exports, __webpack_require__) {

var shared = __webpack_require__(35)('keys');
var uid = __webpack_require__(24);
module.exports = function (key) {
  return shared[key] || (shared[key] = uid(key));
};


/***/ }),
/* 35 */
/***/ (function(module, exports, __webpack_require__) {

var core = __webpack_require__(0);
var global = __webpack_require__(1);
var SHARED = '__core-js_shared__';
var store = global[SHARED] || (global[SHARED] = {});

(module.exports = function (key, value) {
  return store[key] || (store[key] = value !== undefined ? value : {});
})('versions', []).push({
  version: core.version,
  mode: __webpack_require__(19) ? 'pure' : 'global',
  copyright: '© 2020 Denis Pushkarev (zloirock.ru)'
});


/***/ }),
/* 36 */
/***/ (function(module, exports) {

// IE 8- don't enum bug keys
module.exports = (
  'constructor,hasOwnProperty,isPrototypeOf,propertyIsEnumerable,toLocaleString,toString,valueOf'
).split(',');


/***/ }),
/* 37 */
/***/ (function(module, exports, __webpack_require__) {

// getting tag from 19.1.3.6 Object.prototype.toString()
var cof = __webpack_require__(22);
var TAG = __webpack_require__(2)('toStringTag');
// ES3 wrong here
var ARG = cof(function () { return arguments; }()) == 'Arguments';

// fallback for IE11 Script Access Denied error
var tryGet = function (it, key) {
  try {
    return it[key];
  } catch (e) { /* empty */ }
};

module.exports = function (it) {
  var O, T, B;
  return it === undefined ? 'Undefined' : it === null ? 'Null'
    // @@toStringTag case
    : typeof (T = tryGet(O = Object(it), TAG)) == 'string' ? T
    // builtinTag case
    : ARG ? cof(O)
    // ES3 arguments fallback
    : (B = cof(O)) == 'Object' && typeof O.callee == 'function' ? 'Arguments' : B;
};


/***/ }),
/* 38 */
/***/ (function(module, exports, __webpack_require__) {

var classof = __webpack_require__(37);
var ITERATOR = __webpack_require__(2)('iterator');
var Iterators = __webpack_require__(14);
module.exports = __webpack_require__(0).getIteratorMethod = function (it) {
  if (it != undefined) return it[ITERATOR]
    || it['@@iterator']
    || Iterators[classof(it)];
};


/***/ }),
/* 39 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";

// 25.4.1.5 NewPromiseCapability(C)
var aFunction = __webpack_require__(23);

function PromiseCapability(C) {
  var resolve, reject;
  this.promise = new C(function ($$resolve, $$reject) {
    if (resolve !== undefined || reject !== undefined) throw TypeError('Bad Promise constructor');
    resolve = $$resolve;
    reject = $$reject;
  });
  this.resolve = aFunction(resolve);
  this.reject = aFunction(reject);
}

module.exports.f = function (C) {
  return new PromiseCapability(C);
};


/***/ }),
/* 40 */
/***/ (function(module, exports) {

exports.f = Object.getOwnPropertySymbols;


/***/ }),
/* 41 */
/***/ (function(module, exports, __webpack_require__) {

exports.f = __webpack_require__(2);


/***/ }),
/* 42 */
/***/ (function(module, exports, __webpack_require__) {

var global = __webpack_require__(1);
var core = __webpack_require__(0);
var LIBRARY = __webpack_require__(19);
var wksExt = __webpack_require__(41);
var defineProperty = __webpack_require__(6).f;
module.exports = function (name) {
  var $Symbol = core.Symbol || (core.Symbol = LIBRARY ? {} : global.Symbol || {});
  if (name.charAt(0) != '_' && !(name in $Symbol)) defineProperty($Symbol, name, { value: wksExt.f(name) });
};


/***/ }),
/* 43 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";


Object.defineProperty(exports, "__esModule", {
  value: true
});
exports.omit = omit;
exports.arraysEqual = arraysEqual;
var isElementAnSFC = exports.isElementAnSFC = function isElementAnSFC(element) {
  var isNativeDOMElement = typeof element.type === 'string';

  if (isNativeDOMElement) {
    return false;
  }

  return !element.type.prototype.isReactComponent;
};
function omit(obj) {
  var attrs = arguments.length > 1 && arguments[1] !== undefined ? arguments[1] : [];

  var result = {};
  Object.keys(obj).forEach(function (key) {
    if (attrs.indexOf(key) === -1) {
      result[key] = obj[key];
    }
  });
  return result;
}

function arraysEqual(a, b) {
  var sameObject = a === b;
  if (sameObject) {
    return true;
  }

  var notBothArrays = !Array.isArray(a) || !Array.isArray(b);
  var differentLengths = a.length !== b.length;

  if (notBothArrays || differentLengths) {
    return false;
  }

  return a.every(function (element, index) {
    return element === b[index];
  });
}

function memoizeString(fn) {
  var cache = {};

  return function (str) {
    if (!cache[str]) {
      cache[str] = fn(str);
    }
    return cache[str];
  };
}

var hyphenate = exports.hyphenate = memoizeString(function (str) {
  return str.replace(/([A-Z])/g, '-$1').toLowerCase();
});

/***/ }),
/* 44 */
/***/ (function(module, exports) {



/***/ }),
/* 45 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";

var LIBRARY = __webpack_require__(19);
var $export = __webpack_require__(4);
var redefine = __webpack_require__(47);
var hide = __webpack_require__(10);
var Iterators = __webpack_require__(14);
var $iterCreate = __webpack_require__(84);
var setToStringTag = __webpack_require__(25);
var getPrototypeOf = __webpack_require__(51);
var ITERATOR = __webpack_require__(2)('iterator');
var BUGGY = !([].keys && 'next' in [].keys()); // Safari has buggy iterators w/o `next`
var FF_ITERATOR = '@@iterator';
var KEYS = 'keys';
var VALUES = 'values';

var returnThis = function () { return this; };

module.exports = function (Base, NAME, Constructor, next, DEFAULT, IS_SET, FORCED) {
  $iterCreate(Constructor, NAME, next);
  var getMethod = function (kind) {
    if (!BUGGY && kind in proto) return proto[kind];
    switch (kind) {
      case KEYS: return function keys() { return new Constructor(this, kind); };
      case VALUES: return function values() { return new Constructor(this, kind); };
    } return function entries() { return new Constructor(this, kind); };
  };
  var TAG = NAME + ' Iterator';
  var DEF_VALUES = DEFAULT == VALUES;
  var VALUES_BUG = false;
  var proto = Base.prototype;
  var $native = proto[ITERATOR] || proto[FF_ITERATOR] || DEFAULT && proto[DEFAULT];
  var $default = $native || getMethod(DEFAULT);
  var $entries = DEFAULT ? !DEF_VALUES ? $default : getMethod('entries') : undefined;
  var $anyNative = NAME == 'Array' ? proto.entries || $native : $native;
  var methods, key, IteratorPrototype;
  // Fix native
  if ($anyNative) {
    IteratorPrototype = getPrototypeOf($anyNative.call(new Base()));
    if (IteratorPrototype !== Object.prototype && IteratorPrototype.next) {
      // Set @@toStringTag to native iterators
      setToStringTag(IteratorPrototype, TAG, true);
      // fix for some old engines
      if (!LIBRARY && typeof IteratorPrototype[ITERATOR] != 'function') hide(IteratorPrototype, ITERATOR, returnThis);
    }
  }
  // fix Array#{values, @@iterator}.name in V8 / FF
  if (DEF_VALUES && $native && $native.name !== VALUES) {
    VALUES_BUG = true;
    $default = function values() { return $native.call(this); };
  }
  // Define iterator
  if ((!LIBRARY || FORCED) && (BUGGY || VALUES_BUG || !proto[ITERATOR])) {
    hide(proto, ITERATOR, $default);
  }
  // Plug for library
  Iterators[NAME] = $default;
  Iterators[TAG] = returnThis;
  if (DEFAULT) {
    methods = {
      values: DEF_VALUES ? $default : getMethod(VALUES),
      keys: IS_SET ? $default : getMethod(KEYS),
      entries: $entries
    };
    if (FORCED) for (key in methods) {
      if (!(key in proto)) redefine(proto, key, methods[key]);
    } else $export($export.P + $export.F * (BUGGY || VALUES_BUG), NAME, methods);
  }
  return methods;
};


/***/ }),
/* 46 */
/***/ (function(module, exports, __webpack_require__) {

module.exports = !__webpack_require__(7) && !__webpack_require__(13)(function () {
  return Object.defineProperty(__webpack_require__(30)('div'), 'a', { get: function () { return 7; } }).a != 7;
});


/***/ }),
/* 47 */
/***/ (function(module, exports, __webpack_require__) {

module.exports = __webpack_require__(10);


/***/ }),
/* 48 */
/***/ (function(module, exports, __webpack_require__) {

var has = __webpack_require__(11);
var toIObject = __webpack_require__(15);
var arrayIndexOf = __webpack_require__(86)(false);
var IE_PROTO = __webpack_require__(34)('IE_PROTO');

module.exports = function (object, names) {
  var O = toIObject(object);
  var i = 0;
  var result = [];
  var key;
  for (key in O) if (key != IE_PROTO) has(O, key) && result.push(key);
  // Don't enum bug & hidden keys
  while (names.length > i) if (has(O, key = names[i++])) {
    ~arrayIndexOf(result, key) || result.push(key);
  }
  return result;
};


/***/ }),
/* 49 */
/***/ (function(module, exports, __webpack_require__) {

// fallback for non-array-like ES3 and non-enumerable old V8 strings
var cof = __webpack_require__(22);
// eslint-disable-next-line no-prototype-builtins
module.exports = Object('z').propertyIsEnumerable(0) ? Object : function (it) {
  return cof(it) == 'String' ? it.split('') : Object(it);
};


/***/ }),
/* 50 */
/***/ (function(module, exports, __webpack_require__) {

var document = __webpack_require__(1).document;
module.exports = document && document.documentElement;


/***/ }),
/* 51 */
/***/ (function(module, exports, __webpack_require__) {

// 19.1.2.9 / 15.2.3.2 Object.getPrototypeOf(O)
var has = __webpack_require__(11);
var toObject = __webpack_require__(16);
var IE_PROTO = __webpack_require__(34)('IE_PROTO');
var ObjectProto = Object.prototype;

module.exports = Object.getPrototypeOf || function (O) {
  O = toObject(O);
  if (has(O, IE_PROTO)) return O[IE_PROTO];
  if (typeof O.constructor == 'function' && O instanceof O.constructor) {
    return O.constructor.prototype;
  } return O instanceof Object ? ObjectProto : null;
};


/***/ }),
/* 52 */
/***/ (function(module, exports, __webpack_require__) {

// call something on iterator step with safe closing on error
var anObject = __webpack_require__(5);
module.exports = function (iterator, fn, value, entries) {
  try {
    return entries ? fn(anObject(value)[0], value[1]) : fn(value);
  // 7.4.6 IteratorClose(iterator, completion)
  } catch (e) {
    var ret = iterator['return'];
    if (ret !== undefined) anObject(ret.call(iterator));
    throw e;
  }
};


/***/ }),
/* 53 */
/***/ (function(module, exports, __webpack_require__) {

// check on default Array iterator
var Iterators = __webpack_require__(14);
var ITERATOR = __webpack_require__(2)('iterator');
var ArrayProto = Array.prototype;

module.exports = function (it) {
  return it !== undefined && (Iterators.Array === it || ArrayProto[ITERATOR] === it);
};


/***/ }),
/* 54 */
/***/ (function(module, exports, __webpack_require__) {

// 7.3.20 SpeciesConstructor(O, defaultConstructor)
var anObject = __webpack_require__(5);
var aFunction = __webpack_require__(23);
var SPECIES = __webpack_require__(2)('species');
module.exports = function (O, D) {
  var C = anObject(O).constructor;
  var S;
  return C === undefined || (S = anObject(C)[SPECIES]) == undefined ? D : aFunction(S);
};


/***/ }),
/* 55 */
/***/ (function(module, exports, __webpack_require__) {

var ctx = __webpack_require__(12);
var invoke = __webpack_require__(94);
var html = __webpack_require__(50);
var cel = __webpack_require__(30);
var global = __webpack_require__(1);
var process = global.process;
var setTask = global.setImmediate;
var clearTask = global.clearImmediate;
var MessageChannel = global.MessageChannel;
var Dispatch = global.Dispatch;
var counter = 0;
var queue = {};
var ONREADYSTATECHANGE = 'onreadystatechange';
var defer, channel, port;
var run = function () {
  var id = +this;
  // eslint-disable-next-line no-prototype-builtins
  if (queue.hasOwnProperty(id)) {
    var fn = queue[id];
    delete queue[id];
    fn();
  }
};
var listener = function (event) {
  run.call(event.data);
};
// Node.js 0.9+ & IE10+ has setImmediate, otherwise:
if (!setTask || !clearTask) {
  setTask = function setImmediate(fn) {
    var args = [];
    var i = 1;
    while (arguments.length > i) args.push(arguments[i++]);
    queue[++counter] = function () {
      // eslint-disable-next-line no-new-func
      invoke(typeof fn == 'function' ? fn : Function(fn), args);
    };
    defer(counter);
    return counter;
  };
  clearTask = function clearImmediate(id) {
    delete queue[id];
  };
  // Node.js 0.8-
  if (__webpack_require__(22)(process) == 'process') {
    defer = function (id) {
      process.nextTick(ctx(run, id, 1));
    };
  // Sphere (JS game engine) Dispatch API
  } else if (Dispatch && Dispatch.now) {
    defer = function (id) {
      Dispatch.now(ctx(run, id, 1));
    };
  // Browsers with MessageChannel, includes WebWorkers
  } else if (MessageChannel) {
    channel = new MessageChannel();
    port = channel.port2;
    channel.port1.onmessage = listener;
    defer = ctx(port.postMessage, port, 1);
  // Browsers with postMessage, skip WebWorkers
  // IE8 has postMessage, but it's sync & typeof its postMessage is 'object'
  } else if (global.addEventListener && typeof postMessage == 'function' && !global.importScripts) {
    defer = function (id) {
      global.postMessage(id + '', '*');
    };
    global.addEventListener('message', listener, false);
  // IE8-
  } else if (ONREADYSTATECHANGE in cel('script')) {
    defer = function (id) {
      html.appendChild(cel('script'))[ONREADYSTATECHANGE] = function () {
        html.removeChild(this);
        run.call(id);
      };
    };
  // Rest old browsers
  } else {
    defer = function (id) {
      setTimeout(ctx(run, id, 1), 0);
    };
  }
}
module.exports = {
  set: setTask,
  clear: clearTask
};


/***/ }),
/* 56 */
/***/ (function(module, exports) {

module.exports = function (exec) {
  try {
    return { e: false, v: exec() };
  } catch (e) {
    return { e: true, v: e };
  }
};


/***/ }),
/* 57 */
/***/ (function(module, exports, __webpack_require__) {

var anObject = __webpack_require__(5);
var isObject = __webpack_require__(8);
var newPromiseCapability = __webpack_require__(39);

module.exports = function (C, x) {
  anObject(C);
  if (isObject(x) && x.constructor === C) return x;
  var promiseCapability = newPromiseCapability.f(C);
  var resolve = promiseCapability.resolve;
  resolve(x);
  return promiseCapability.promise;
};


/***/ }),
/* 58 */
/***/ (function(module, exports, __webpack_require__) {

var ITERATOR = __webpack_require__(2)('iterator');
var SAFE_CLOSING = false;

try {
  var riter = [7][ITERATOR]();
  riter['return'] = function () { SAFE_CLOSING = true; };
  // eslint-disable-next-line no-throw-literal
  Array.from(riter, function () { throw 2; });
} catch (e) { /* empty */ }

module.exports = function (exec, skipClosing) {
  if (!skipClosing && !SAFE_CLOSING) return false;
  var safe = false;
  try {
    var arr = [7];
    var iter = arr[ITERATOR]();
    iter.next = function () { return { done: safe = true }; };
    arr[ITERATOR] = function () { return iter; };
    exec(arr);
  } catch (e) { /* empty */ }
  return safe;
};


/***/ }),
/* 59 */
/***/ (function(module, exports, __webpack_require__) {

module.exports = { "default": __webpack_require__(105), __esModule: true };

/***/ }),
/* 60 */
/***/ (function(module, exports, __webpack_require__) {

// most Object methods by ES6 should accept primitives
var $export = __webpack_require__(4);
var core = __webpack_require__(0);
var fails = __webpack_require__(13);
module.exports = function (KEY, exec) {
  var fn = (core.Object || {})[KEY] || Object[KEY];
  var exp = {};
  exp[KEY] = exec(fn);
  $export($export.S + $export.F * fails(function () { fn(1); }), 'Object', exp);
};


/***/ }),
/* 61 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";


exports.__esModule = true;

exports.default = function (instance, Constructor) {
  if (!(instance instanceof Constructor)) {
    throw new TypeError("Cannot call a class as a function");
  }
};

/***/ }),
/* 62 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";


exports.__esModule = true;

var _defineProperty = __webpack_require__(107);

var _defineProperty2 = _interopRequireDefault(_defineProperty);

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

exports.default = function () {
  function defineProperties(target, props) {
    for (var i = 0; i < props.length; i++) {
      var descriptor = props[i];
      descriptor.enumerable = descriptor.enumerable || false;
      descriptor.configurable = true;
      if ("value" in descriptor) descriptor.writable = true;
      (0, _defineProperty2.default)(target, descriptor.key, descriptor);
    }
  }

  return function (Constructor, protoProps, staticProps) {
    if (protoProps) defineProperties(Constructor.prototype, protoProps);
    if (staticProps) defineProperties(Constructor, staticProps);
    return Constructor;
  };
}();

/***/ }),
/* 63 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";


exports.__esModule = true;

var _typeof2 = __webpack_require__(64);

var _typeof3 = _interopRequireDefault(_typeof2);

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

exports.default = function (self, call) {
  if (!self) {
    throw new ReferenceError("this hasn't been initialised - super() hasn't been called");
  }

  return call && ((typeof call === "undefined" ? "undefined" : (0, _typeof3.default)(call)) === "object" || typeof call === "function") ? call : self;
};

/***/ }),
/* 64 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";


exports.__esModule = true;

var _iterator = __webpack_require__(110);

var _iterator2 = _interopRequireDefault(_iterator);

var _symbol = __webpack_require__(112);

var _symbol2 = _interopRequireDefault(_symbol);

var _typeof = typeof _symbol2.default === "function" && typeof _iterator2.default === "symbol" ? function (obj) { return typeof obj; } : function (obj) { return obj && typeof _symbol2.default === "function" && obj.constructor === _symbol2.default && obj !== _symbol2.default.prototype ? "symbol" : typeof obj; };

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

exports.default = typeof _symbol2.default === "function" && _typeof(_iterator2.default) === "symbol" ? function (obj) {
  return typeof obj === "undefined" ? "undefined" : _typeof(obj);
} : function (obj) {
  return obj && typeof _symbol2.default === "function" && obj.constructor === _symbol2.default && obj !== _symbol2.default.prototype ? "symbol" : typeof obj === "undefined" ? "undefined" : _typeof(obj);
};

/***/ }),
/* 65 */
/***/ (function(module, exports, __webpack_require__) {

// 19.1.2.7 / 15.2.3.4 Object.getOwnPropertyNames(O)
var $keys = __webpack_require__(48);
var hiddenKeys = __webpack_require__(36).concat('length', 'prototype');

exports.f = Object.getOwnPropertyNames || function getOwnPropertyNames(O) {
  return $keys(O, hiddenKeys);
};


/***/ }),
/* 66 */
/***/ (function(module, exports, __webpack_require__) {

var pIE = __webpack_require__(27);
var createDesc = __webpack_require__(20);
var toIObject = __webpack_require__(15);
var toPrimitive = __webpack_require__(31);
var has = __webpack_require__(11);
var IE8_DOM_DEFINE = __webpack_require__(46);
var gOPD = Object.getOwnPropertyDescriptor;

exports.f = __webpack_require__(7) ? gOPD : function getOwnPropertyDescriptor(O, P) {
  O = toIObject(O);
  P = toPrimitive(P, true);
  if (IE8_DOM_DEFINE) try {
    return gOPD(O, P);
  } catch (e) { /* empty */ }
  if (has(O, P)) return createDesc(!pIE.f.call(O, P), O[P]);
};


/***/ }),
/* 67 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";


exports.__esModule = true;

var _setPrototypeOf = __webpack_require__(121);

var _setPrototypeOf2 = _interopRequireDefault(_setPrototypeOf);

var _create = __webpack_require__(125);

var _create2 = _interopRequireDefault(_create);

var _typeof2 = __webpack_require__(64);

var _typeof3 = _interopRequireDefault(_typeof2);

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

exports.default = function (subClass, superClass) {
  if (typeof superClass !== "function" && superClass !== null) {
    throw new TypeError("Super expression must either be null or a function, not " + (typeof superClass === "undefined" ? "undefined" : (0, _typeof3.default)(superClass)));
  }

  subClass.prototype = (0, _create2.default)(superClass && superClass.prototype, {
    constructor: {
      value: subClass,
      enumerable: false,
      writable: true,
      configurable: true
    }
  });
  if (superClass) _setPrototypeOf2.default ? (0, _setPrototypeOf2.default)(subClass, superClass) : subClass.__proto__ = superClass;
};

/***/ }),
/* 68 */
/***/ (function(module, exports) {

// shim for using process in browser
var process = module.exports = {};

// cached from whatever global is present so that test runners that stub it
// don't break things.  But we need to wrap it in a try catch in case it is
// wrapped in strict mode code which doesn't define any globals.  It's inside a
// function because try/catches deoptimize in certain engines.

var cachedSetTimeout;
var cachedClearTimeout;

function defaultSetTimout() {
    throw new Error('setTimeout has not been defined');
}
function defaultClearTimeout () {
    throw new Error('clearTimeout has not been defined');
}
(function () {
    try {
        if (typeof setTimeout === 'function') {
            cachedSetTimeout = setTimeout;
        } else {
            cachedSetTimeout = defaultSetTimout;
        }
    } catch (e) {
        cachedSetTimeout = defaultSetTimout;
    }
    try {
        if (typeof clearTimeout === 'function') {
            cachedClearTimeout = clearTimeout;
        } else {
            cachedClearTimeout = defaultClearTimeout;
        }
    } catch (e) {
        cachedClearTimeout = defaultClearTimeout;
    }
} ())
function runTimeout(fun) {
    if (cachedSetTimeout === setTimeout) {
        //normal enviroments in sane situations
        return setTimeout(fun, 0);
    }
    // if setTimeout wasn't available but was latter defined
    if ((cachedSetTimeout === defaultSetTimout || !cachedSetTimeout) && setTimeout) {
        cachedSetTimeout = setTimeout;
        return setTimeout(fun, 0);
    }
    try {
        // when when somebody has screwed with setTimeout but no I.E. maddness
        return cachedSetTimeout(fun, 0);
    } catch(e){
        try {
            // When we are in I.E. but the script has been evaled so I.E. doesn't trust the global object when called normally
            return cachedSetTimeout.call(null, fun, 0);
        } catch(e){
            // same as above but when it's a version of I.E. that must have the global object for 'this', hopfully our context correct otherwise it will throw a global error
            return cachedSetTimeout.call(this, fun, 0);
        }
    }


}
function runClearTimeout(marker) {
    if (cachedClearTimeout === clearTimeout) {
        //normal enviroments in sane situations
        return clearTimeout(marker);
    }
    // if clearTimeout wasn't available but was latter defined
    if ((cachedClearTimeout === defaultClearTimeout || !cachedClearTimeout) && clearTimeout) {
        cachedClearTimeout = clearTimeout;
        return clearTimeout(marker);
    }
    try {
        // when when somebody has screwed with setTimeout but no I.E. maddness
        return cachedClearTimeout(marker);
    } catch (e){
        try {
            // When we are in I.E. but the script has been evaled so I.E. doesn't  trust the global object when called normally
            return cachedClearTimeout.call(null, marker);
        } catch (e){
            // same as above but when it's a version of I.E. that must have the global object for 'this', hopfully our context correct otherwise it will throw a global error.
            // Some versions of I.E. have different rules for clearTimeout vs setTimeout
            return cachedClearTimeout.call(this, marker);
        }
    }



}
var queue = [];
var draining = false;
var currentQueue;
var queueIndex = -1;

function cleanUpNextTick() {
    if (!draining || !currentQueue) {
        return;
    }
    draining = false;
    if (currentQueue.length) {
        queue = currentQueue.concat(queue);
    } else {
        queueIndex = -1;
    }
    if (queue.length) {
        drainQueue();
    }
}

function drainQueue() {
    if (draining) {
        return;
    }
    var timeout = runTimeout(cleanUpNextTick);
    draining = true;

    var len = queue.length;
    while(len) {
        currentQueue = queue;
        queue = [];
        while (++queueIndex < len) {
            if (currentQueue) {
                currentQueue[queueIndex].run();
            }
        }
        queueIndex = -1;
        len = queue.length;
    }
    currentQueue = null;
    draining = false;
    runClearTimeout(timeout);
}

process.nextTick = function (fun) {
    var args = new Array(arguments.length - 1);
    if (arguments.length > 1) {
        for (var i = 1; i < arguments.length; i++) {
            args[i - 1] = arguments[i];
        }
    }
    queue.push(new Item(fun, args));
    if (queue.length === 1 && !draining) {
        runTimeout(drainQueue);
    }
};

// v8 likes predictible objects
function Item(fun, array) {
    this.fun = fun;
    this.array = array;
}
Item.prototype.run = function () {
    this.fun.apply(null, this.array);
};
process.title = 'browser';
process.browser = true;
process.env = {};
process.argv = [];
process.version = ''; // empty string to avoid regexp issues
process.versions = {};

function noop() {}

process.on = noop;
process.addListener = noop;
process.once = noop;
process.off = noop;
process.removeListener = noop;
process.removeAllListeners = noop;
process.emit = noop;
process.prependListener = noop;
process.prependOnceListener = noop;

process.listeners = function (name) { return [] }

process.binding = function (name) {
    throw new Error('process.binding is not supported');
};

process.cwd = function () { return '/' };
process.chdir = function (dir) {
    throw new Error('process.chdir is not supported');
};
process.umask = function() { return 0; };


/***/ }),
/* 69 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";


Object.defineProperty(exports, "__esModule", {
  value: true
});
exports.hasClassInParent = exports.formatErrorMsg = exports.getMetaContent = exports.axiosGithub = exports.axiosJSON = exports.queryStringify = exports.queryParse = undefined;

var _keys = __webpack_require__(149);

var _keys2 = _interopRequireDefault(_keys);

var _slicedToArray2 = __webpack_require__(152);

var _slicedToArray3 = _interopRequireDefault(_slicedToArray2);

var _axios = __webpack_require__(159);

var _axios2 = _interopRequireDefault(_axios);

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

var queryParse = exports.queryParse = function queryParse() {
  var search = arguments.length > 0 && arguments[0] !== undefined ? arguments[0] : window.location.search;

  if (!search) return {};
  var queryString = search[0] === '?' ? search.substring(1) : search;
  var query = {};
  queryString.split('&').forEach(function (queryStr) {
    var _queryStr$split = queryStr.split('='),
        _queryStr$split2 = (0, _slicedToArray3.default)(_queryStr$split, 2),
        key = _queryStr$split2[0],
        value = _queryStr$split2[1];
    /* istanbul ignore else */


    if (key) query[decodeURIComponent(key)] = decodeURIComponent(value);
  });

  return query;
};

var queryStringify = exports.queryStringify = function queryStringify(query) {
  var queryString = (0, _keys2.default)(query).map(function (key) {
    return key + '=' + encodeURIComponent(query[key] || '');
  }).join('&');
  return queryString;
};

var axiosJSON = exports.axiosJSON = _axios2.default.create({
  headers: {
    'Accept': 'application/json'
  }
});

var axiosGithub = exports.axiosGithub = _axios2.default.create({
  baseURL: 'https://api.github.com',
  headers: {
    'Accept': 'application/json'
  }
});

var getMetaContent = exports.getMetaContent = function getMetaContent(name, content) {
  /* istanbul ignore next */
  content || (content = 'content');
  /* istanbul ignore next */
  var el = window.document.querySelector('meta[name=\'' + name + '\']');
  /* istanbul ignore next */
  return el && el.getAttribute(content);
};

var formatErrorMsg = exports.formatErrorMsg = function formatErrorMsg(err) {
  var msg = 'Error: ';
  if (err.response && err.response.data && err.response.data.message) {
    msg += err.response.data.message + '. ';
    err.response.data.errors && (msg += err.response.data.errors.map(function (e) {
      return e.message;
    }).join(', '));
  } else {
    msg += err.message;
  }
  return msg;
};

var hasClassInParent = exports.hasClassInParent = function hasClassInParent(element) {
  for (var _len = arguments.length, className = Array(_len > 1 ? _len - 1 : 0), _key = 1; _key < _len; _key++) {
    className[_key - 1] = arguments[_key];
  }

  /* istanbul ignore next */
  var yes = false;
  /* istanbul ignore next */
  if (typeof element.className === 'undefined') return false;
  /* istanbul ignore next */
  var classes = element.className.split(' ');
  /* istanbul ignore next */
  className.forEach(function (c, i) {
    /* istanbul ignore next */
    yes = yes || classes.indexOf(c) >= 0;
  });
  /* istanbul ignore next */
  if (yes) return yes;
  /* istanbul ignore next */
  return element.parentNode && hasClassInParent(element.parentNode, className);
};

/***/ }),
/* 70 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";


module.exports = function bind(fn, thisArg) {
  return function wrap() {
    var args = new Array(arguments.length);
    for (var i = 0; i < args.length; i++) {
      args[i] = arguments[i];
    }
    return fn.apply(thisArg, args);
  };
};


/***/ }),
/* 71 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";


var utils = __webpack_require__(3);

function encode(val) {
  return encodeURIComponent(val).
    replace(/%40/gi, '@').
    replace(/%3A/gi, ':').
    replace(/%24/g, '$').
    replace(/%2C/gi, ',').
    replace(/%20/g, '+').
    replace(/%5B/gi, '[').
    replace(/%5D/gi, ']');
}

/**
 * Build a URL by appending params to the end
 *
 * @param {string} url The base of the url (e.g., http://www.google.com)
 * @param {object} [params] The params to be appended
 * @returns {string} The formatted url
 */
module.exports = function buildURL(url, params, paramsSerializer) {
  /*eslint no-param-reassign:0*/
  if (!params) {
    return url;
  }

  var serializedParams;
  if (paramsSerializer) {
    serializedParams = paramsSerializer(params);
  } else if (utils.isURLSearchParams(params)) {
    serializedParams = params.toString();
  } else {
    var parts = [];

    utils.forEach(params, function serialize(val, key) {
      if (val === null || typeof val === 'undefined') {
        return;
      }

      if (utils.isArray(val)) {
        key = key + '[]';
      } else {
        val = [val];
      }

      utils.forEach(val, function parseValue(v) {
        if (utils.isDate(v)) {
          v = v.toISOString();
        } else if (utils.isObject(v)) {
          v = JSON.stringify(v);
        }
        parts.push(encode(key) + '=' + encode(v));
      });
    });

    serializedParams = parts.join('&');
  }

  if (serializedParams) {
    var hashmarkIndex = url.indexOf('#');
    if (hashmarkIndex !== -1) {
      url = url.slice(0, hashmarkIndex);
    }

    url += (url.indexOf('?') === -1 ? '?' : '&') + serializedParams;
  }

  return url;
};


/***/ }),
/* 72 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";


module.exports = function isCancel(value) {
  return !!(value && value.__CANCEL__);
};


/***/ }),
/* 73 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";
/* WEBPACK VAR INJECTION */(function(process) {

var utils = __webpack_require__(3);
var normalizeHeaderName = __webpack_require__(165);

var DEFAULT_CONTENT_TYPE = {
  'Content-Type': 'application/x-www-form-urlencoded'
};

function setContentTypeIfUnset(headers, value) {
  if (!utils.isUndefined(headers) && utils.isUndefined(headers['Content-Type'])) {
    headers['Content-Type'] = value;
  }
}

function getDefaultAdapter() {
  var adapter;
  if (typeof XMLHttpRequest !== 'undefined') {
    // For browsers use XHR adapter
    adapter = __webpack_require__(74);
  } else if (typeof process !== 'undefined' && Object.prototype.toString.call(process) === '[object process]') {
    // For node use HTTP adapter
    adapter = __webpack_require__(74);
  }
  return adapter;
}

var defaults = {
  adapter: getDefaultAdapter(),

  transformRequest: [function transformRequest(data, headers) {
    normalizeHeaderName(headers, 'Accept');
    normalizeHeaderName(headers, 'Content-Type');
    if (utils.isFormData(data) ||
      utils.isArrayBuffer(data) ||
      utils.isBuffer(data) ||
      utils.isStream(data) ||
      utils.isFile(data) ||
      utils.isBlob(data)
    ) {
      return data;
    }
    if (utils.isArrayBufferView(data)) {
      return data.buffer;
    }
    if (utils.isURLSearchParams(data)) {
      setContentTypeIfUnset(headers, 'application/x-www-form-urlencoded;charset=utf-8');
      return data.toString();
    }
    if (utils.isObject(data)) {
      setContentTypeIfUnset(headers, 'application/json;charset=utf-8');
      return JSON.stringify(data);
    }
    return data;
  }],

  transformResponse: [function transformResponse(data) {
    /*eslint no-param-reassign:0*/
    if (typeof data === 'string') {
      try {
        data = JSON.parse(data);
      } catch (e) { /* Ignore */ }
    }
    return data;
  }],

  /**
   * A timeout in milliseconds to abort a request. If set to 0 (default) a
   * timeout is not created.
   */
  timeout: 0,

  xsrfCookieName: 'XSRF-TOKEN',
  xsrfHeaderName: 'X-XSRF-TOKEN',

  maxContentLength: -1,

  validateStatus: function validateStatus(status) {
    return status >= 200 && status < 300;
  }
};

defaults.headers = {
  common: {
    'Accept': 'application/json, text/plain, */*'
  }
};

utils.forEach(['delete', 'get', 'head'], function forEachMethodNoData(method) {
  defaults.headers[method] = {};
});

utils.forEach(['post', 'put', 'patch'], function forEachMethodWithData(method) {
  defaults.headers[method] = utils.merge(DEFAULT_CONTENT_TYPE);
});

module.exports = defaults;

/* WEBPACK VAR INJECTION */}.call(exports, __webpack_require__(68)))

/***/ }),
/* 74 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";


var utils = __webpack_require__(3);
var settle = __webpack_require__(166);
var buildURL = __webpack_require__(71);
var buildFullPath = __webpack_require__(168);
var parseHeaders = __webpack_require__(171);
var isURLSameOrigin = __webpack_require__(172);
var createError = __webpack_require__(75);

module.exports = function xhrAdapter(config) {
  return new Promise(function dispatchXhrRequest(resolve, reject) {
    var requestData = config.data;
    var requestHeaders = config.headers;

    if (utils.isFormData(requestData)) {
      delete requestHeaders['Content-Type']; // Let the browser set it
    }

    var request = new XMLHttpRequest();

    // HTTP basic authentication
    if (config.auth) {
      var username = config.auth.username || '';
      var password = config.auth.password || '';
      requestHeaders.Authorization = 'Basic ' + btoa(username + ':' + password);
    }

    var fullPath = buildFullPath(config.baseURL, config.url);
    request.open(config.method.toUpperCase(), buildURL(fullPath, config.params, config.paramsSerializer), true);

    // Set the request timeout in MS
    request.timeout = config.timeout;

    // Listen for ready state
    request.onreadystatechange = function handleLoad() {
      if (!request || request.readyState !== 4) {
        return;
      }

      // The request errored out and we didn't get a response, this will be
      // handled by onerror instead
      // With one exception: request that using file: protocol, most browsers
      // will return status as 0 even though it's a successful request
      if (request.status === 0 && !(request.responseURL && request.responseURL.indexOf('file:') === 0)) {
        return;
      }

      // Prepare the response
      var responseHeaders = 'getAllResponseHeaders' in request ? parseHeaders(request.getAllResponseHeaders()) : null;
      var responseData = !config.responseType || config.responseType === 'text' ? request.responseText : request.response;
      var response = {
        data: responseData,
        status: request.status,
        statusText: request.statusText,
        headers: responseHeaders,
        config: config,
        request: request
      };

      settle(resolve, reject, response);

      // Clean up request
      request = null;
    };

    // Handle browser request cancellation (as opposed to a manual cancellation)
    request.onabort = function handleAbort() {
      if (!request) {
        return;
      }

      reject(createError('Request aborted', config, 'ECONNABORTED', request));

      // Clean up request
      request = null;
    };

    // Handle low level network errors
    request.onerror = function handleError() {
      // Real errors are hidden from us by the browser
      // onerror should only fire if it's a network error
      reject(createError('Network Error', config, null, request));

      // Clean up request
      request = null;
    };

    // Handle timeout
    request.ontimeout = function handleTimeout() {
      var timeoutErrorMessage = 'timeout of ' + config.timeout + 'ms exceeded';
      if (config.timeoutErrorMessage) {
        timeoutErrorMessage = config.timeoutErrorMessage;
      }
      reject(createError(timeoutErrorMessage, config, 'ECONNABORTED',
        request));

      // Clean up request
      request = null;
    };

    // Add xsrf header
    // This is only done if running in a standard browser environment.
    // Specifically not if we're in a web worker, or react-native.
    if (utils.isStandardBrowserEnv()) {
      var cookies = __webpack_require__(173);

      // Add xsrf header
      var xsrfValue = (config.withCredentials || isURLSameOrigin(fullPath)) && config.xsrfCookieName ?
        cookies.read(config.xsrfCookieName) :
        undefined;

      if (xsrfValue) {
        requestHeaders[config.xsrfHeaderName] = xsrfValue;
      }
    }

    // Add headers to the request
    if ('setRequestHeader' in request) {
      utils.forEach(requestHeaders, function setRequestHeader(val, key) {
        if (typeof requestData === 'undefined' && key.toLowerCase() === 'content-type') {
          // Remove Content-Type if data is undefined
          delete requestHeaders[key];
        } else {
          // Otherwise add header to the request
          request.setRequestHeader(key, val);
        }
      });
    }

    // Add withCredentials to request if needed
    if (!utils.isUndefined(config.withCredentials)) {
      request.withCredentials = !!config.withCredentials;
    }

    // Add responseType to request if needed
    if (config.responseType) {
      try {
        request.responseType = config.responseType;
      } catch (e) {
        // Expected DOMException thrown by browsers not compatible XMLHttpRequest Level 2.
        // But, this can be suppressed for 'json' type as it can be parsed by default 'transformResponse' function.
        if (config.responseType !== 'json') {
          throw e;
        }
      }
    }

    // Handle progress if needed
    if (typeof config.onDownloadProgress === 'function') {
      request.addEventListener('progress', config.onDownloadProgress);
    }

    // Not all browsers support upload events
    if (typeof config.onUploadProgress === 'function' && request.upload) {
      request.upload.addEventListener('progress', config.onUploadProgress);
    }

    if (config.cancelToken) {
      // Handle cancellation
      config.cancelToken.promise.then(function onCanceled(cancel) {
        if (!request) {
          return;
        }

        request.abort();
        reject(cancel);
        // Clean up request
        request = null;
      });
    }

    if (requestData === undefined) {
      requestData = null;
    }

    // Send the request
    request.send(requestData);
  });
};


/***/ }),
/* 75 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";


var enhanceError = __webpack_require__(167);

/**
 * Create an Error with the specified message, config, error code, request and response.
 *
 * @param {string} message The error message.
 * @param {Object} config The config.
 * @param {string} [code] The error code (for example, 'ECONNABORTED').
 * @param {Object} [request] The request.
 * @param {Object} [response] The response.
 * @returns {Error} The created error.
 */
module.exports = function createError(message, config, code, request, response) {
  var error = new Error(message);
  return enhanceError(error, config, code, request, response);
};


/***/ }),
/* 76 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";


var utils = __webpack_require__(3);

/**
 * Config-specific merge-function which creates a new config-object
 * by merging two configuration objects together.
 *
 * @param {Object} config1
 * @param {Object} config2
 * @returns {Object} New object resulting from merging config2 to config1
 */
module.exports = function mergeConfig(config1, config2) {
  // eslint-disable-next-line no-param-reassign
  config2 = config2 || {};
  var config = {};

  var valueFromConfig2Keys = ['url', 'method', 'params', 'data'];
  var mergeDeepPropertiesKeys = ['headers', 'auth', 'proxy'];
  var defaultToConfig2Keys = [
    'baseURL', 'url', 'transformRequest', 'transformResponse', 'paramsSerializer',
    'timeout', 'withCredentials', 'adapter', 'responseType', 'xsrfCookieName',
    'xsrfHeaderName', 'onUploadProgress', 'onDownloadProgress',
    'maxContentLength', 'validateStatus', 'maxRedirects', 'httpAgent',
    'httpsAgent', 'cancelToken', 'socketPath'
  ];

  utils.forEach(valueFromConfig2Keys, function valueFromConfig2(prop) {
    if (typeof config2[prop] !== 'undefined') {
      config[prop] = config2[prop];
    }
  });

  utils.forEach(mergeDeepPropertiesKeys, function mergeDeepProperties(prop) {
    if (utils.isObject(config2[prop])) {
      config[prop] = utils.deepMerge(config1[prop], config2[prop]);
    } else if (typeof config2[prop] !== 'undefined') {
      config[prop] = config2[prop];
    } else if (utils.isObject(config1[prop])) {
      config[prop] = utils.deepMerge(config1[prop]);
    } else if (typeof config1[prop] !== 'undefined') {
      config[prop] = config1[prop];
    }
  });

  utils.forEach(defaultToConfig2Keys, function defaultToConfig2(prop) {
    if (typeof config2[prop] !== 'undefined') {
      config[prop] = config2[prop];
    } else if (typeof config1[prop] !== 'undefined') {
      config[prop] = config1[prop];
    }
  });

  var axiosKeys = valueFromConfig2Keys
    .concat(mergeDeepPropertiesKeys)
    .concat(defaultToConfig2Keys);

  var otherKeys = Object
    .keys(config2)
    .filter(function filterAxiosKeys(key) {
      return axiosKeys.indexOf(key) === -1;
    });

  utils.forEach(otherKeys, function otherKeysDefaultToConfig2(prop) {
    if (typeof config2[prop] !== 'undefined') {
      config[prop] = config2[prop];
    } else if (typeof config1[prop] !== 'undefined') {
      config[prop] = config1[prop];
    }
  });

  return config;
};


/***/ }),
/* 77 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";


/**
 * A `Cancel` is an object that is thrown when an operation is canceled.
 *
 * @class
 * @param {string=} message The message.
 */
function Cancel(message) {
  this.message = message;
}

Cancel.prototype.toString = function toString() {
  return 'Cancel' + (this.message ? ': ' + this.message : '');
};

Cancel.prototype.__CANCEL__ = true;

module.exports = Cancel;


/***/ }),
/* 78 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";


Object.defineProperty(exports, "__esModule", {
  value: true
});

var _react = __webpack_require__(9);

var _react2 = _interopRequireDefault(_react);

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

exports.default = function (_ref) {
  var src = _ref.src,
      className = _ref.className,
      alt = _ref.alt,
      _ref$defaultSrc = _ref.defaultSrc,
      defaultSrc = _ref$defaultSrc === undefined ? '//cdn.jsdelivr.net/npm/gitalk@1/src/assets/icon/github.svg' : _ref$defaultSrc;
  return _react2.default.createElement(
    'div',
    { className: 'gt-avatar ' + className },
    _react2.default.createElement('img', { src: src || defaultSrc, alt: '@' + alt, onError: function onError(e) {
        e.target.src = defaultSrc;
      } })
  );
};

/***/ }),
/* 79 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";


Object.defineProperty(exports, "__esModule", {
  value: true
});

var _react = __webpack_require__(9);

var _react2 = _interopRequireDefault(_react);

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

exports.default = function (_ref) {
  var className = _ref.className,
      text = _ref.text,
      name = _ref.name;
  return _react2.default.createElement(
    "span",
    { className: "gt-ico " + className },
    _react2.default.createElement("span", { className: "gt-svg", dangerouslySetInnerHTML: {
        __html: __webpack_require__(179)("./" + name + ".svg")
      } }),
    text && _react2.default.createElement(
      "span",
      { className: "gt-ico-text" },
      text
    )
  );
};

/***/ }),
/* 80 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";


var _promise = __webpack_require__(81);

var _promise2 = _interopRequireDefault(_promise);

var _assign = __webpack_require__(101);

var _assign2 = _interopRequireDefault(_assign);

var _getPrototypeOf = __webpack_require__(59);

var _getPrototypeOf2 = _interopRequireDefault(_getPrototypeOf);

var _classCallCheck2 = __webpack_require__(61);

var _classCallCheck3 = _interopRequireDefault(_classCallCheck2);

var _createClass2 = __webpack_require__(62);

var _createClass3 = _interopRequireDefault(_createClass2);

var _possibleConstructorReturn2 = __webpack_require__(63);

var _possibleConstructorReturn3 = _interopRequireDefault(_possibleConstructorReturn2);

var _inherits2 = __webpack_require__(67);

var _inherits3 = _interopRequireDefault(_inherits2);

var _react = __webpack_require__(9);

var _react2 = _interopRequireDefault(_react);

var _reactFlipMove = __webpack_require__(128);

var _reactFlipMove2 = _interopRequireDefault(_reactFlipMove);

var _autosize = __webpack_require__(136);

var _autosize2 = _interopRequireDefault(_autosize);

var _i18n = __webpack_require__(137);

var _i18n2 = _interopRequireDefault(_i18n);

__webpack_require__(148);

var _util = __webpack_require__(69);

var _avatar = __webpack_require__(78);

var _avatar2 = _interopRequireDefault(_avatar);

var _button = __webpack_require__(176);

var _button2 = _interopRequireDefault(_button);

var _action = __webpack_require__(177);

var _action2 = _interopRequireDefault(_action);

var _comment = __webpack_require__(178);

var _comment2 = _interopRequireDefault(_comment);

var _svg = __webpack_require__(79);

var _svg2 = _interopRequireDefault(_svg);

var _const = __webpack_require__(207);

var _getComments = __webpack_require__(208);

var _getComments2 = _interopRequireDefault(_getComments);

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

var GitalkComponent = function (_Component) {
  (0, _inherits3.default)(GitalkComponent, _Component);

  function GitalkComponent(props) {
    (0, _classCallCheck3.default)(this, GitalkComponent);

    var _this = (0, _possibleConstructorReturn3.default)(this, (GitalkComponent.__proto__ || (0, _getPrototypeOf2.default)(GitalkComponent)).call(this, props));

    _this.state = {
      user: null,
      issue: null,
      comments: [],
      localComments: [],
      comment: '',
      page: 1,
      pagerDirection: 'last',
      cursor: null,
      previewHtml: '',

      isNoInit: false,
      isIniting: true,
      isCreating: false,
      isLoading: false,
      isLoadMore: false,
      isLoadOver: false,
      isIssueCreating: false,
      isPopupVisible: false,
      isInputFocused: false,
      isPreview: false,

      isOccurError: false,
      errorMsg: ''
    };

    _this.getCommentsV3 = function (issue) {
      var _this$options = _this.options,
          clientID = _this$options.clientID,
          clientSecret = _this$options.clientSecret,
          perPage = _this$options.perPage;
      var page = _this.state.page;


      return _this.getIssue().then(function (issue) {
        if (!issue) return;

        return _util.axiosGithub.get(issue.comments_url, {
          headers: {
            Accept: 'application/vnd.github.v3.full+json'
          },
          auth: {
            username: clientID,
            password: clientSecret
          },
          params: {
            per_page: perPage,
            page: page
          }
        }).then(function (res) {
          var _this$state = _this.state,
              comments = _this$state.comments,
              issue = _this$state.issue;

          var isLoadOver = false;
          var cs = comments.concat(res.data);
          if (cs.length >= issue.comments || res.data.length < perPage) {
            isLoadOver = true;
          }
          _this.setState({
            comments: cs,
            isLoadOver: isLoadOver,
            page: page + 1
          });
          return cs;
        });
      });
    };

    _this.getRef = function (e) {
      _this.publicBtnEL = e;
    };

    _this.reply = function (replyComment) {
      return function () {
        var comment = _this.state.comment;

        var replyCommentBody = replyComment.body;
        var replyCommentArray = replyCommentBody.split('\n');
        replyCommentArray.unshift('@' + replyComment.user.login);
        replyCommentArray = replyCommentArray.map(function (t) {
          return '> ' + t;
        });
        replyCommentArray.push('');
        replyCommentArray.push('');
        if (comment) replyCommentArray.unshift('');
        _this.setState({ comment: comment + replyCommentArray.join('\n') }, function () {
          _autosize2.default.update(_this.commentEL);
          _this.commentEL.focus();
        });
      };
    };

    _this.handlePopup = function (e) {
      e.preventDefault();
      e.stopPropagation();
      var isVisible = !_this.state.isPopupVisible;
      var hideHandle = function hideHandle(e1) {
        if ((0, _util.hasClassInParent)(e1.target, 'gt-user', 'gt-popup')) {
          return;
        }
        window.document.removeEventListener('click', hideHandle);
        _this.setState({ isPopupVisible: false });
      };
      _this.setState({ isPopupVisible: isVisible });
      if (isVisible) {
        window.document.addEventListener('click', hideHandle);
      } else {
        window.document.removeEventListener('click', hideHandle);
      }
    };

    _this.handleLogin = function () {
      var comment = _this.state.comment;

      window.localStorage.setItem(_const.GT_COMMENT, encodeURIComponent(comment));
      window.location.href = _this.loginLink;
    };

    _this.handleIssueCreate = function () {
      _this.setState({ isIssueCreating: true });
      _this.createIssue().then(function (issue) {
        _this.setState({
          isIssueCreating: false,
          isOccurError: false
        });
        return _this.getComments(issue);
      }).catch(function (err) {
        _this.setState({
          isIssueCreating: false,
          isOccurError: true,
          errorMsg: (0, _util.formatErrorMsg)(err)
        });
      }).then(function (res) {
        if (res) {
          _this.setState({
            isNoInit: false
          });
        }
      });
    };

    _this.handleCommentCreate = function (e) {
      if (!_this.state.comment.length) {
        e && e.preventDefault();
        _this.commentEL.focus();
        return;
      }
      _this.setState(function (state) {
        if (state.isCreating) return;

        _this.createComment().then(function () {
          return _this.setState({
            isCreating: false,
            isOccurError: false
          });
        }).catch(function (err) {
          _this.setState({
            isCreating: false,
            isOccurError: true,
            errorMsg: (0, _util.formatErrorMsg)(err)
          });
        });
        return { isCreating: true };
      });
    };

    _this.handleCommentPreview = function (e) {
      _this.setState({
        isPreview: !_this.state.isPreview
      });

      _util.axiosGithub.post('/markdown', {
        text: _this.state.comment
      }, {
        headers: _this.accessToken && { Authorization: 'token ' + _this.accessToken }
      }).then(function (res) {
        _this.setState({
          previewHtml: res.data
        });
      }).catch(function (err) {
        _this.setState({
          isOccurError: true,
          errorMsg: (0, _util.formatErrorMsg)(err)
        });
      });
    };

    _this.handleCommentLoad = function () {
      var _this$state2 = _this.state,
          issue = _this$state2.issue,
          isLoadMore = _this$state2.isLoadMore;

      if (isLoadMore) return;
      _this.setState({ isLoadMore: true });
      _this.getComments(issue).then(function () {
        return _this.setState({ isLoadMore: false });
      });
    };

    _this.handleCommentChange = function (e) {
      return _this.setState({ comment: e.target.value });
    };

    _this.handleLogout = function () {
      _this.logout();
      window.location.reload();
    };

    _this.handleCommentFocus = function (e) {
      var distractionFreeMode = _this.options.distractionFreeMode;

      if (!distractionFreeMode) return e.preventDefault();
      _this.setState({ isInputFocused: true });
    };

    _this.handleCommentBlur = function (e) {
      var distractionFreeMode = _this.options.distractionFreeMode;

      if (!distractionFreeMode) return e.preventDefault();
      _this.setState({ isInputFocused: false });
    };

    _this.handleSort = function (direction) {
      return function (e) {
        _this.setState({ pagerDirection: direction });
      };
    };

    _this.handleCommentKeyDown = function (e) {
      var enableHotKey = _this.options.enableHotKey;

      if (enableHotKey && (e.metaKey || e.ctrlKey) && e.keyCode === 13) {
        _this.publicBtnEL && _this.publicBtnEL.focus();
        _this.handleCommentCreate();
      }
    };

    _this.options = (0, _assign2.default)({}, {
      id: window.location.href,
      number: -1,
      labels: ['Gitalk'],
      title: window.document.title,
      body: '', // window.location.href + header.meta[description]
      language: window.navigator.language || window.navigator.userLanguage,
      perPage: 10,
      pagerDirection: 'last', // last or first
      createIssueManually: false,
      distractionFreeMode: false,
      proxy: 'https://cors-anywhere.mgt.workers.dev/?https://github.com/login/oauth/access_token',
      flipMoveOptions: {
        staggerDelayBy: 150,
        appearAnimation: 'accordionVertical',
        enterAnimation: 'accordionVertical',
        leaveAnimation: 'accordionVertical'
      },
      enableHotKey: true,

      url: window.location.href,

      defaultAuthor: {
        avatarUrl: '//avatars1.githubusercontent.com/u/29697133?s=50',
        login: 'null',
        url: ''
      },

      updateCountCallback: null
    }, props.options);

    _this.state.pagerDirection = _this.options.pagerDirection;
    var storedComment = window.localStorage.getItem(_const.GT_COMMENT);
    if (storedComment) {
      _this.state.comment = decodeURIComponent(storedComment);
      window.localStorage.removeItem(_const.GT_COMMENT);
    }

    var query = (0, _util.queryParse)();
    if (query.code) {
      var code = query.code;
      delete query.code;
      var replacedUrl = '' + window.location.origin + window.location.pathname + (0, _util.queryStringify)(query) + window.location.hash;
      history.replaceState(null, null, replacedUrl);
      _this.options = (0, _assign2.default)({}, _this.options, {
        url: replacedUrl,
        id: replacedUrl
      }, props.options);

      _util.axiosJSON.post(_this.options.proxy, {
        code: code,
        client_id: _this.options.clientID,
        client_secret: _this.options.clientSecret
      }).then(function (res) {
        if (res.data && res.data.access_token) {
          _this.accessToken = res.data.access_token;

          _this.getInit().then(function () {
            return _this.setState({ isIniting: false });
          }).catch(function (err) {
            console.log('err:', err);
            _this.setState({
              isIniting: false,
              isOccurError: true,
              errorMsg: (0, _util.formatErrorMsg)(err)
            });
          });
        } else {
          // no access_token
          console.log('res.data err:', res.data);
          _this.setState({
            isOccurError: true,
            errorMsg: (0, _util.formatErrorMsg)(new Error('no access token'))
          });
        }
      }).catch(function (err) {
        console.log('err: ', err);
        _this.setState({
          isOccurError: true,
          errorMsg: (0, _util.formatErrorMsg)(err)
        });
      });
    } else {
      _this.getInit().then(function () {
        return _this.setState({ isIniting: false });
      }).catch(function (err) {
        console.log('err:', err);
        _this.setState({
          isIniting: false,
          isOccurError: true,
          errorMsg: (0, _util.formatErrorMsg)(err)
        });
      });
    }

    _this.i18n = (0, _i18n2.default)(_this.options.language);
    return _this;
  }

  (0, _createClass3.default)(GitalkComponent, [{
    key: 'componentDidUpdate',
    value: function componentDidUpdate() {
      this.commentEL && (0, _autosize2.default)(this.commentEL);
    }
  }, {
    key: 'getInit',
    value: function getInit() {
      var _this2 = this;

      return this.getUserInfo().then(function () {
        return _this2.getIssue();
      }).then(function (issue) {
        return _this2.getComments(issue);
      });
    }
  }, {
    key: 'getUserInfo',
    value: function getUserInfo() {
      var _this3 = this;

      if (!this.accessToken) {
        return new _promise2.default(function (resolve) {
          resolve();
        });
      }
      return _util.axiosGithub.get('/user', {
        headers: {
          Authorization: 'token ' + this.accessToken
        }
      }).then(function (res) {
        _this3.setState({ user: res.data });
      }).catch(function (err) {
        _this3.logout();
      });
    }
  }, {
    key: 'getIssueById',
    value: function getIssueById() {
      var _this4 = this;

      var _options = this.options,
          owner = _options.owner,
          repo = _options.repo,
          number = _options.number,
          clientID = _options.clientID,
          clientSecret = _options.clientSecret;

      var getUrl = '/repos/' + owner + '/' + repo + '/issues/' + number;

      return new _promise2.default(function (resolve, reject) {
        _util.axiosGithub.get(getUrl, {
          auth: {
            username: clientID,
            password: clientSecret
          },
          params: {
            t: Date.now()
          }
        }).then(function (res) {
          var issue = null;

          if (res && res.data && res.data.number === number) {
            issue = res.data;

            _this4.setState({ issue: issue, isNoInit: false });
          }
          resolve(issue);
        }).catch(function (err) {
          // When the status code is 404, promise will be resolved with null
          if (err.response.status === 404) resolve(null);
          reject(err);
        });
      });
    }
  }, {
    key: 'getIssueByLabels',
    value: function getIssueByLabels() {
      var _this5 = this;

      var _options2 = this.options,
          owner = _options2.owner,
          repo = _options2.repo,
          id = _options2.id,
          labels = _options2.labels,
          clientID = _options2.clientID,
          clientSecret = _options2.clientSecret;


      return _util.axiosGithub.get('/repos/' + owner + '/' + repo + '/issues', {
        auth: {
          username: clientID,
          password: clientSecret
        },
        params: {
          labels: labels.concat(id).join(','),
          t: Date.now()
        }
      }).then(function (res) {
        var createIssueManually = _this5.options.createIssueManually;

        var isNoInit = false;
        var issue = null;
        if (!(res && res.data && res.data.length)) {
          if (!createIssueManually && _this5.isAdmin) {
            return _this5.createIssue();
          }

          isNoInit = true;
        } else {
          issue = res.data[0];
        }
        _this5.setState({ issue: issue, isNoInit: isNoInit });
        return issue;
      });
    }
  }, {
    key: 'getIssue',
    value: function getIssue() {
      var _this6 = this;

      var number = this.options.number;
      var issue = this.state.issue;

      if (issue) {
        this.setState({ isNoInit: false });
        return _promise2.default.resolve(issue);
      }

      if (typeof number === 'number' && number > 0) {
        return this.getIssueById().then(function (resIssue) {
          if (!resIssue) return _this6.getIssueByLabels();
          return resIssue;
        });
      }
      return this.getIssueByLabels();
    }
  }, {
    key: 'createIssue',
    value: function createIssue() {
      var _this7 = this;

      var _options3 = this.options,
          owner = _options3.owner,
          repo = _options3.repo,
          title = _options3.title,
          body = _options3.body,
          id = _options3.id,
          labels = _options3.labels,
          url = _options3.url;

      return _util.axiosGithub.post('/repos/' + owner + '/' + repo + '/issues', {
        title: title,
        labels: labels.concat(id),
        body: body || url + ' \n\n ' + ((0, _util.getMetaContent)('description') || (0, _util.getMetaContent)('description', 'og:description') || '')
      }, {
        headers: {
          Authorization: 'token ' + this.accessToken
        }
      }).then(function (res) {
        _this7.setState({ issue: res.data });
        return res.data;
      });
    }
    // Get comments via v3 api, don't require login, but sorting feature is disable

  }, {
    key: 'getComments',
    value: function getComments(issue) {
      if (!issue) return;
      // Get comments via v4 graphql api, login required and sorting feature is available
      if (this.accessToken) return _getComments2.default.call(this, issue);
      return this.getCommentsV3(issue);
    }
  }, {
    key: 'createComment',
    value: function createComment() {
      var _this8 = this;

      var _state = this.state,
          comment = _state.comment,
          localComments = _state.localComments,
          comments = _state.comments;


      return this.getIssue().then(function (issue) {
        return _util.axiosGithub.post(issue.comments_url, {
          body: comment
        }, {
          headers: {
            Accept: 'application/vnd.github.v3.full+json',
            Authorization: 'token ' + _this8.accessToken
          }
        });
      }).then(function (res) {
        _this8.setState({
          comment: '',
          comments: comments.concat(res.data),
          localComments: localComments.concat(res.data)
        });
      });
    }
  }, {
    key: 'logout',
    value: function logout() {
      this.setState({ user: null });
      window.localStorage.removeItem(_const.GT_ACCESS_TOKEN);
    }
  }, {
    key: 'like',
    value: function like(comment) {
      var _this9 = this;

      var _options4 = this.options,
          owner = _options4.owner,
          repo = _options4.repo;
      var user = this.state.user;
      var comments = this.state.comments;


      _util.axiosGithub.post('/repos/' + owner + '/' + repo + '/issues/comments/' + comment.id + '/reactions', {
        content: 'heart'
      }, {
        headers: {
          Authorization: 'token ' + this.accessToken,
          Accept: 'application/vnd.github.squirrel-girl-preview'
        }
      }).then(function (res) {
        comments = comments.map(function (c) {
          if (c.id === comment.id) {
            if (c.reactions) {
              if (!~c.reactions.nodes.findIndex(function (n) {
                return n.user.login === user.login;
              })) {
                c.reactions.totalCount += 1;
              }
            } else {
              c.reactions = { nodes: [] };
              c.reactions.totalCount = 1;
            }

            c.reactions.nodes.push(res.data);
            c.reactions.viewerHasReacted = true;
          }
          return c;
        });

        _this9.setState({
          comments: comments
        });
      });
    }
  }, {
    key: 'unLike',
    value: function unLike(comment) {
      var _this10 = this;

      var user = this.state.user;
      var comments = this.state.comments;

      // const {  user } = this.state
      // let id
      // comment.reactions.nodes.forEach(r => {
      //   if (r.user.login = user.login) id = r.databaseId
      // })
      // return axiosGithub.delete(`/reactions/${id}`, {
      //   headers: {
      //     Authorization: `token ${this.accessToken}`,
      //     Accept: 'application/vnd.github.squirrel-girl-preview'
      //   }
      // }).then(res => {
      //   console.log('res:', res)
      // })

      var getQL = function getQL(id) {
        return {
          operationName: 'RemoveReaction',
          query: '\n          mutation RemoveReaction{\n            removeReaction (input:{\n              subjectId: "' + id + '",\n              content: HEART\n            }) {\n              reaction {\n                content\n              }\n            }\n          }\n        '
        };
      };

      _util.axiosGithub.post('/graphql', getQL(comment.gId), {
        headers: {
          Authorization: 'bearer ' + this.accessToken
        }
      }).then(function (res) {
        if (res.data) {
          comments = comments.map(function (c) {
            if (c.id === comment.id) {
              var index = c.reactions.nodes.findIndex(function (n) {
                return n.user.login === user.login;
              });
              if (~index) {
                c.reactions.totalCount -= 1;
                c.reactions.nodes.splice(index, 1);
              }
              c.reactions.viewerHasReacted = false;
            }
            return c;
          });

          _this10.setState({
            comments: comments
          });
        }
      });
    }
  }, {
    key: 'initing',
    value: function initing() {
      return _react2.default.createElement(
        'div',
        { className: 'gt-initing' },
        _react2.default.createElement('i', { className: 'gt-loader' }),
        _react2.default.createElement(
          'p',
          { className: 'gt-initing-text' },
          this.i18n.t('init')
        )
      );
    }
  }, {
    key: 'noInit',
    value: function noInit() {
      var _state2 = this.state,
          user = _state2.user,
          isIssueCreating = _state2.isIssueCreating;
      var _options5 = this.options,
          owner = _options5.owner,
          repo = _options5.repo,
          admin = _options5.admin;

      return _react2.default.createElement(
        'div',
        { className: 'gt-no-init', key: 'no-init' },
        _react2.default.createElement('p', { dangerouslySetInnerHTML: {
            __html: this.i18n.t('no-found-related', {
              link: '<a href="https://github.com/' + owner + '/' + repo + '/issues">Issues</a>'
            })
          } }),
        _react2.default.createElement(
          'p',
          null,
          this.i18n.t('please-contact', { user: [].concat(admin).map(function (u) {
              return '@' + u;
            }).join(' ') })
        ),
        this.isAdmin ? _react2.default.createElement(
          'p',
          null,
          _react2.default.createElement(_button2.default, { onClick: this.handleIssueCreate, isLoading: isIssueCreating, text: this.i18n.t('init-issue') })
        ) : null,
        !user && _react2.default.createElement(_button2.default, { className: 'gt-btn-login', onClick: this.handleLogin, text: this.i18n.t('login-with-github') })
      );
    }
  }, {
    key: 'header',
    value: function header() {
      var _this11 = this;

      var _state3 = this.state,
          user = _state3.user,
          comment = _state3.comment,
          isCreating = _state3.isCreating,
          previewHtml = _state3.previewHtml,
          isPreview = _state3.isPreview;

      return _react2.default.createElement(
        'div',
        { className: 'gt-header', key: 'header' },
        user ? _react2.default.createElement(_avatar2.default, { className: 'gt-header-avatar', src: user.avatar_url, alt: user.login }) : _react2.default.createElement(
          'a',
          { className: 'gt-avatar-github', onClick: this.handleLogin },
          _react2.default.createElement(_svg2.default, { className: 'gt-ico-github', name: 'github' })
        ),
        _react2.default.createElement(
          'div',
          { className: 'gt-header-comment' },
          _react2.default.createElement('textarea', {
            ref: function ref(t) {
              _this11.commentEL = t;
            },
            className: 'gt-header-textarea ' + (isPreview ? 'hide' : ''),
            value: comment,
            onChange: this.handleCommentChange,
            onFocus: this.handleCommentFocus,
            onBlur: this.handleCommentBlur,
            onKeyDown: this.handleCommentKeyDown,
            placeholder: this.i18n.t('leave-a-comment')
          }),
          _react2.default.createElement('div', {
            className: 'gt-header-preview markdown-body ' + (isPreview ? '' : 'hide'),
            dangerouslySetInnerHTML: { __html: previewHtml }
          }),
          _react2.default.createElement(
            'div',
            { className: 'gt-header-controls' },
            _react2.default.createElement(
              'a',
              { className: 'gt-header-controls-tip', href: 'https://guides.github.com/features/mastering-markdown/', target: '_blank' },
              _react2.default.createElement(_svg2.default, { className: 'gt-ico-tip', name: 'tip', text: this.i18n.t('support-markdown') })
            ),
            user && _react2.default.createElement(_button2.default, {
              getRef: this.getRef,
              className: 'gt-btn-public',
              onClick: this.handleCommentCreate,
              text: this.i18n.t('comment'),
              isLoading: isCreating
            }),
            _react2.default.createElement(_button2.default, {
              className: 'gt-btn-preview',
              onClick: this.handleCommentPreview,
              text: isPreview ? this.i18n.t('edit') : this.i18n.t('preview')
              // isLoading={isPreviewing}
            }),
            !user && _react2.default.createElement(_button2.default, { className: 'gt-btn-login', onClick: this.handleLogin, text: this.i18n.t('login-with-github') })
          )
        )
      );
    }
  }, {
    key: 'comments',
    value: function comments() {
      var _this12 = this;

      var _state4 = this.state,
          user = _state4.user,
          comments = _state4.comments,
          isLoadOver = _state4.isLoadOver,
          isLoadMore = _state4.isLoadMore,
          pagerDirection = _state4.pagerDirection;
      var _options6 = this.options,
          language = _options6.language,
          flipMoveOptions = _options6.flipMoveOptions,
          admin = _options6.admin;

      var totalComments = comments.concat([]);
      if (pagerDirection === 'last' && this.accessToken) {
        totalComments.reverse();
      }
      return _react2.default.createElement(
        'div',
        { className: 'gt-comments', key: 'comments' },
        _react2.default.createElement(
          _reactFlipMove2.default,
          flipMoveOptions,
          totalComments.map(function (c) {
            return _react2.default.createElement(_comment2.default, {
              comment: c,
              key: c.id,
              user: user,
              language: language,
              commentedText: _this12.i18n.t('commented'),
              admin: admin,
              replyCallback: _this12.reply(c),
              likeCallback: c.reactions && c.reactions.viewerHasReacted ? _this12.unLike.bind(_this12, c) : _this12.like.bind(_this12, c)
            });
          })
        ),
        !totalComments.length && _react2.default.createElement(
          'p',
          { className: 'gt-comments-null' },
          this.i18n.t('first-comment-person')
        ),
        !isLoadOver && totalComments.length ? _react2.default.createElement(
          'div',
          { className: 'gt-comments-controls' },
          _react2.default.createElement(_button2.default, { className: 'gt-btn-loadmore', onClick: this.handleCommentLoad, isLoading: isLoadMore, text: this.i18n.t('load-more') })
        ) : null
      );
    }
  }, {
    key: 'meta',
    value: function meta() {
      var _state5 = this.state,
          user = _state5.user,
          issue = _state5.issue,
          isPopupVisible = _state5.isPopupVisible,
          pagerDirection = _state5.pagerDirection,
          localComments = _state5.localComments;

      var cnt = (issue && issue.comments) + localComments.length;
      var isDesc = pagerDirection === 'last';
      var updateCountCallback = this.options.updateCountCallback;

      // window.GITALK_COMMENTS_COUNT = cnt

      if (updateCountCallback && {}.toString.call(updateCountCallback) === '[object Function]') {
        try {
          updateCountCallback(cnt);
        } catch (err) {
          console.log('An error occurred executing the updateCountCallback:', err);
        }
      }

      return _react2.default.createElement(
        'div',
        { className: 'gt-meta', key: 'meta' },
        _react2.default.createElement('span', { className: 'gt-counts', dangerouslySetInnerHTML: {
            __html: this.i18n.t('counts', {
              counts: '<a class="gt-link gt-link-counts" href="' + (issue && issue.html_url) + '" target="_blank">' + cnt + '</a>',
              smart_count: cnt
            })
          } }),
        isPopupVisible && _react2.default.createElement(
          'div',
          { className: 'gt-popup' },
          user ? _react2.default.createElement(_action2.default, { className: 'gt-action-sortasc' + (!isDesc ? ' is--active' : ''), onClick: this.handleSort('first'), text: this.i18n.t('sort-asc') }) : null,
          user ? _react2.default.createElement(_action2.default, { className: 'gt-action-sortdesc' + (isDesc ? ' is--active' : ''), onClick: this.handleSort('last'), text: this.i18n.t('sort-desc') }) : null,
          user ? _react2.default.createElement(_action2.default, { className: 'gt-action-logout', onClick: this.handleLogout, text: this.i18n.t('logout') }) : _react2.default.createElement(
            'a',
            { className: 'gt-action gt-action-login', onClick: this.handleLogin },
            this.i18n.t('login-with-github')
          ),
          _react2.default.createElement(
            'div',
            { className: 'gt-copyright' },
            _react2.default.createElement(
              'a',
              { className: 'gt-link gt-link-project', href: 'https://github.com/gitalk/gitalk', target: '_blank' },
              'Gitalk'
            ),
            _react2.default.createElement(
              'span',
              { className: 'gt-version' },
              _const.GT_VERSION
            )
          )
        ),
        _react2.default.createElement(
          'div',
          { className: 'gt-user' },
          user ? _react2.default.createElement(
            'div',
            { className: isPopupVisible ? 'gt-user-inner is--poping' : 'gt-user-inner', onClick: this.handlePopup },
            _react2.default.createElement(
              'span',
              { className: 'gt-user-name' },
              user.login
            ),
            _react2.default.createElement(_svg2.default, { className: 'gt-ico-arrdown', name: 'arrow_down' })
          ) : _react2.default.createElement(
            'div',
            { className: isPopupVisible ? 'gt-user-inner is--poping' : 'gt-user-inner', onClick: this.handlePopup },
            _react2.default.createElement(
              'span',
              { className: 'gt-user-name' },
              this.i18n.t('anonymous')
            ),
            _react2.default.createElement(_svg2.default, { className: 'gt-ico-arrdown', name: 'arrow_down' })
          )
        )
      );
    }
  }, {
    key: 'render',
    value: function render() {
      var _state6 = this.state,
          isIniting = _state6.isIniting,
          isNoInit = _state6.isNoInit,
          isOccurError = _state6.isOccurError,
          errorMsg = _state6.errorMsg,
          isInputFocused = _state6.isInputFocused;

      return _react2.default.createElement(
        'div',
        { className: 'gt-container' + (isInputFocused ? ' gt-input-focused' : '') },
        isIniting && this.initing(),
        !isIniting && (isNoInit ? [] : [this.meta()]),
        isOccurError && _react2.default.createElement(
          'div',
          { className: 'gt-error' },
          errorMsg
        ),
        !isIniting && (isNoInit ? [this.noInit()] : [this.header(), this.comments()])
      );
    }
  }, {
    key: 'accessToken',
    get: function get() {
      return this._accessToke || window.localStorage.getItem(_const.GT_ACCESS_TOKEN);
    },
    set: function set(token) {
      window.localStorage.setItem(_const.GT_ACCESS_TOKEN, token);
      this._accessToken = token;
    }
  }, {
    key: 'loginLink',
    get: function get() {
      var githubOauthUrl = 'https://github.com/login/oauth/authorize';
      var clientID = this.options.clientID;

      var query = {
        client_id: clientID,
        redirect_uri: window.location.href,
        scope: 'public_repo'
      };
      return githubOauthUrl + '?' + (0, _util.queryStringify)(query);
    }
  }, {
    key: 'isAdmin',
    get: function get() {
      var admin = this.options.admin;
      var user = this.state.user;


      return user && ~[].concat(admin).map(function (a) {
        return a.toLowerCase();
      }).indexOf(user.login.toLowerCase());
    }
  }]);
  return GitalkComponent;
}(_react.Component);

module.exports = GitalkComponent;

/***/ }),
/* 81 */
/***/ (function(module, exports, __webpack_require__) {

module.exports = { "default": __webpack_require__(82), __esModule: true };

/***/ }),
/* 82 */
/***/ (function(module, exports, __webpack_require__) {

__webpack_require__(44);
__webpack_require__(18);
__webpack_require__(26);
__webpack_require__(91);
__webpack_require__(99);
__webpack_require__(100);
module.exports = __webpack_require__(0).Promise;


/***/ }),
/* 83 */
/***/ (function(module, exports, __webpack_require__) {

var toInteger = __webpack_require__(28);
var defined = __webpack_require__(29);
// true  -> String#at
// false -> String#codePointAt
module.exports = function (TO_STRING) {
  return function (that, pos) {
    var s = String(defined(that));
    var i = toInteger(pos);
    var l = s.length;
    var a, b;
    if (i < 0 || i >= l) return TO_STRING ? '' : undefined;
    a = s.charCodeAt(i);
    return a < 0xd800 || a > 0xdbff || i + 1 === l || (b = s.charCodeAt(i + 1)) < 0xdc00 || b > 0xdfff
      ? TO_STRING ? s.charAt(i) : a
      : TO_STRING ? s.slice(i, i + 2) : (a - 0xd800 << 10) + (b - 0xdc00) + 0x10000;
  };
};


/***/ }),
/* 84 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";

var create = __webpack_require__(32);
var descriptor = __webpack_require__(20);
var setToStringTag = __webpack_require__(25);
var IteratorPrototype = {};

// 25.1.2.1.1 %IteratorPrototype%[@@iterator]()
__webpack_require__(10)(IteratorPrototype, __webpack_require__(2)('iterator'), function () { return this; });

module.exports = function (Constructor, NAME, next) {
  Constructor.prototype = create(IteratorPrototype, { next: descriptor(1, next) });
  setToStringTag(Constructor, NAME + ' Iterator');
};


/***/ }),
/* 85 */
/***/ (function(module, exports, __webpack_require__) {

var dP = __webpack_require__(6);
var anObject = __webpack_require__(5);
var getKeys = __webpack_require__(21);

module.exports = __webpack_require__(7) ? Object.defineProperties : function defineProperties(O, Properties) {
  anObject(O);
  var keys = getKeys(Properties);
  var length = keys.length;
  var i = 0;
  var P;
  while (length > i) dP.f(O, P = keys[i++], Properties[P]);
  return O;
};


/***/ }),
/* 86 */
/***/ (function(module, exports, __webpack_require__) {

// false -> Array#indexOf
// true  -> Array#includes
var toIObject = __webpack_require__(15);
var toLength = __webpack_require__(33);
var toAbsoluteIndex = __webpack_require__(87);
module.exports = function (IS_INCLUDES) {
  return function ($this, el, fromIndex) {
    var O = toIObject($this);
    var length = toLength(O.length);
    var index = toAbsoluteIndex(fromIndex, length);
    var value;
    // Array#includes uses SameValueZero equality algorithm
    // eslint-disable-next-line no-self-compare
    if (IS_INCLUDES && el != el) while (length > index) {
      value = O[index++];
      // eslint-disable-next-line no-self-compare
      if (value != value) return true;
    // Array#indexOf ignores holes, Array#includes - not
    } else for (;length > index; index++) if (IS_INCLUDES || index in O) {
      if (O[index] === el) return IS_INCLUDES || index || 0;
    } return !IS_INCLUDES && -1;
  };
};


/***/ }),
/* 87 */
/***/ (function(module, exports, __webpack_require__) {

var toInteger = __webpack_require__(28);
var max = Math.max;
var min = Math.min;
module.exports = function (index, length) {
  index = toInteger(index);
  return index < 0 ? max(index + length, 0) : min(index, length);
};


/***/ }),
/* 88 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";

var addToUnscopables = __webpack_require__(89);
var step = __webpack_require__(90);
var Iterators = __webpack_require__(14);
var toIObject = __webpack_require__(15);

// 22.1.3.4 Array.prototype.entries()
// 22.1.3.13 Array.prototype.keys()
// 22.1.3.29 Array.prototype.values()
// 22.1.3.30 Array.prototype[@@iterator]()
module.exports = __webpack_require__(45)(Array, 'Array', function (iterated, kind) {
  this._t = toIObject(iterated); // target
  this._i = 0;                   // next index
  this._k = kind;                // kind
// 22.1.5.2.1 %ArrayIteratorPrototype%.next()
}, function () {
  var O = this._t;
  var kind = this._k;
  var index = this._i++;
  if (!O || index >= O.length) {
    this._t = undefined;
    return step(1);
  }
  if (kind == 'keys') return step(0, index);
  if (kind == 'values') return step(0, O[index]);
  return step(0, [index, O[index]]);
}, 'values');

// argumentsList[@@iterator] is %ArrayProto_values% (9.4.4.6, 9.4.4.7)
Iterators.Arguments = Iterators.Array;

addToUnscopables('keys');
addToUnscopables('values');
addToUnscopables('entries');


/***/ }),
/* 89 */
/***/ (function(module, exports) {

module.exports = function () { /* empty */ };


/***/ }),
/* 90 */
/***/ (function(module, exports) {

module.exports = function (done, value) {
  return { value: value, done: !!done };
};


/***/ }),
/* 91 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";

var LIBRARY = __webpack_require__(19);
var global = __webpack_require__(1);
var ctx = __webpack_require__(12);
var classof = __webpack_require__(37);
var $export = __webpack_require__(4);
var isObject = __webpack_require__(8);
var aFunction = __webpack_require__(23);
var anInstance = __webpack_require__(92);
var forOf = __webpack_require__(93);
var speciesConstructor = __webpack_require__(54);
var task = __webpack_require__(55).set;
var microtask = __webpack_require__(95)();
var newPromiseCapabilityModule = __webpack_require__(39);
var perform = __webpack_require__(56);
var userAgent = __webpack_require__(96);
var promiseResolve = __webpack_require__(57);
var PROMISE = 'Promise';
var TypeError = global.TypeError;
var process = global.process;
var versions = process && process.versions;
var v8 = versions && versions.v8 || '';
var $Promise = global[PROMISE];
var isNode = classof(process) == 'process';
var empty = function () { /* empty */ };
var Internal, newGenericPromiseCapability, OwnPromiseCapability, Wrapper;
var newPromiseCapability = newGenericPromiseCapability = newPromiseCapabilityModule.f;

var USE_NATIVE = !!function () {
  try {
    // correct subclassing with @@species support
    var promise = $Promise.resolve(1);
    var FakePromise = (promise.constructor = {})[__webpack_require__(2)('species')] = function (exec) {
      exec(empty, empty);
    };
    // unhandled rejections tracking support, NodeJS Promise without it fails @@species test
    return (isNode || typeof PromiseRejectionEvent == 'function')
      && promise.then(empty) instanceof FakePromise
      // v8 6.6 (Node 10 and Chrome 66) have a bug with resolving custom thenables
      // https://bugs.chromium.org/p/chromium/issues/detail?id=830565
      // we can't detect it synchronously, so just check versions
      && v8.indexOf('6.6') !== 0
      && userAgent.indexOf('Chrome/66') === -1;
  } catch (e) { /* empty */ }
}();

// helpers
var isThenable = function (it) {
  var then;
  return isObject(it) && typeof (then = it.then) == 'function' ? then : false;
};
var notify = function (promise, isReject) {
  if (promise._n) return;
  promise._n = true;
  var chain = promise._c;
  microtask(function () {
    var value = promise._v;
    var ok = promise._s == 1;
    var i = 0;
    var run = function (reaction) {
      var handler = ok ? reaction.ok : reaction.fail;
      var resolve = reaction.resolve;
      var reject = reaction.reject;
      var domain = reaction.domain;
      var result, then, exited;
      try {
        if (handler) {
          if (!ok) {
            if (promise._h == 2) onHandleUnhandled(promise);
            promise._h = 1;
          }
          if (handler === true) result = value;
          else {
            if (domain) domain.enter();
            result = handler(value); // may throw
            if (domain) {
              domain.exit();
              exited = true;
            }
          }
          if (result === reaction.promise) {
            reject(TypeError('Promise-chain cycle'));
          } else if (then = isThenable(result)) {
            then.call(result, resolve, reject);
          } else resolve(result);
        } else reject(value);
      } catch (e) {
        if (domain && !exited) domain.exit();
        reject(e);
      }
    };
    while (chain.length > i) run(chain[i++]); // variable length - can't use forEach
    promise._c = [];
    promise._n = false;
    if (isReject && !promise._h) onUnhandled(promise);
  });
};
var onUnhandled = function (promise) {
  task.call(global, function () {
    var value = promise._v;
    var unhandled = isUnhandled(promise);
    var result, handler, console;
    if (unhandled) {
      result = perform(function () {
        if (isNode) {
          process.emit('unhandledRejection', value, promise);
        } else if (handler = global.onunhandledrejection) {
          handler({ promise: promise, reason: value });
        } else if ((console = global.console) && console.error) {
          console.error('Unhandled promise rejection', value);
        }
      });
      // Browsers should not trigger `rejectionHandled` event if it was handled here, NodeJS - should
      promise._h = isNode || isUnhandled(promise) ? 2 : 1;
    } promise._a = undefined;
    if (unhandled && result.e) throw result.v;
  });
};
var isUnhandled = function (promise) {
  return promise._h !== 1 && (promise._a || promise._c).length === 0;
};
var onHandleUnhandled = function (promise) {
  task.call(global, function () {
    var handler;
    if (isNode) {
      process.emit('rejectionHandled', promise);
    } else if (handler = global.onrejectionhandled) {
      handler({ promise: promise, reason: promise._v });
    }
  });
};
var $reject = function (value) {
  var promise = this;
  if (promise._d) return;
  promise._d = true;
  promise = promise._w || promise; // unwrap
  promise._v = value;
  promise._s = 2;
  if (!promise._a) promise._a = promise._c.slice();
  notify(promise, true);
};
var $resolve = function (value) {
  var promise = this;
  var then;
  if (promise._d) return;
  promise._d = true;
  promise = promise._w || promise; // unwrap
  try {
    if (promise === value) throw TypeError("Promise can't be resolved itself");
    if (then = isThenable(value)) {
      microtask(function () {
        var wrapper = { _w: promise, _d: false }; // wrap
        try {
          then.call(value, ctx($resolve, wrapper, 1), ctx($reject, wrapper, 1));
        } catch (e) {
          $reject.call(wrapper, e);
        }
      });
    } else {
      promise._v = value;
      promise._s = 1;
      notify(promise, false);
    }
  } catch (e) {
    $reject.call({ _w: promise, _d: false }, e); // wrap
  }
};

// constructor polyfill
if (!USE_NATIVE) {
  // 25.4.3.1 Promise(executor)
  $Promise = function Promise(executor) {
    anInstance(this, $Promise, PROMISE, '_h');
    aFunction(executor);
    Internal.call(this);
    try {
      executor(ctx($resolve, this, 1), ctx($reject, this, 1));
    } catch (err) {
      $reject.call(this, err);
    }
  };
  // eslint-disable-next-line no-unused-vars
  Internal = function Promise(executor) {
    this._c = [];             // <- awaiting reactions
    this._a = undefined;      // <- checked in isUnhandled reactions
    this._s = 0;              // <- state
    this._d = false;          // <- done
    this._v = undefined;      // <- value
    this._h = 0;              // <- rejection state, 0 - default, 1 - handled, 2 - unhandled
    this._n = false;          // <- notify
  };
  Internal.prototype = __webpack_require__(97)($Promise.prototype, {
    // 25.4.5.3 Promise.prototype.then(onFulfilled, onRejected)
    then: function then(onFulfilled, onRejected) {
      var reaction = newPromiseCapability(speciesConstructor(this, $Promise));
      reaction.ok = typeof onFulfilled == 'function' ? onFulfilled : true;
      reaction.fail = typeof onRejected == 'function' && onRejected;
      reaction.domain = isNode ? process.domain : undefined;
      this._c.push(reaction);
      if (this._a) this._a.push(reaction);
      if (this._s) notify(this, false);
      return reaction.promise;
    },
    // 25.4.5.1 Promise.prototype.catch(onRejected)
    'catch': function (onRejected) {
      return this.then(undefined, onRejected);
    }
  });
  OwnPromiseCapability = function () {
    var promise = new Internal();
    this.promise = promise;
    this.resolve = ctx($resolve, promise, 1);
    this.reject = ctx($reject, promise, 1);
  };
  newPromiseCapabilityModule.f = newPromiseCapability = function (C) {
    return C === $Promise || C === Wrapper
      ? new OwnPromiseCapability(C)
      : newGenericPromiseCapability(C);
  };
}

$export($export.G + $export.W + $export.F * !USE_NATIVE, { Promise: $Promise });
__webpack_require__(25)($Promise, PROMISE);
__webpack_require__(98)(PROMISE);
Wrapper = __webpack_require__(0)[PROMISE];

// statics
$export($export.S + $export.F * !USE_NATIVE, PROMISE, {
  // 25.4.4.5 Promise.reject(r)
  reject: function reject(r) {
    var capability = newPromiseCapability(this);
    var $$reject = capability.reject;
    $$reject(r);
    return capability.promise;
  }
});
$export($export.S + $export.F * (LIBRARY || !USE_NATIVE), PROMISE, {
  // 25.4.4.6 Promise.resolve(x)
  resolve: function resolve(x) {
    return promiseResolve(LIBRARY && this === Wrapper ? $Promise : this, x);
  }
});
$export($export.S + $export.F * !(USE_NATIVE && __webpack_require__(58)(function (iter) {
  $Promise.all(iter)['catch'](empty);
})), PROMISE, {
  // 25.4.4.1 Promise.all(iterable)
  all: function all(iterable) {
    var C = this;
    var capability = newPromiseCapability(C);
    var resolve = capability.resolve;
    var reject = capability.reject;
    var result = perform(function () {
      var values = [];
      var index = 0;
      var remaining = 1;
      forOf(iterable, false, function (promise) {
        var $index = index++;
        var alreadyCalled = false;
        values.push(undefined);
        remaining++;
        C.resolve(promise).then(function (value) {
          if (alreadyCalled) return;
          alreadyCalled = true;
          values[$index] = value;
          --remaining || resolve(values);
        }, reject);
      });
      --remaining || resolve(values);
    });
    if (result.e) reject(result.v);
    return capability.promise;
  },
  // 25.4.4.4 Promise.race(iterable)
  race: function race(iterable) {
    var C = this;
    var capability = newPromiseCapability(C);
    var reject = capability.reject;
    var result = perform(function () {
      forOf(iterable, false, function (promise) {
        C.resolve(promise).then(capability.resolve, reject);
      });
    });
    if (result.e) reject(result.v);
    return capability.promise;
  }
});


/***/ }),
/* 92 */
/***/ (function(module, exports) {

module.exports = function (it, Constructor, name, forbiddenField) {
  if (!(it instanceof Constructor) || (forbiddenField !== undefined && forbiddenField in it)) {
    throw TypeError(name + ': incorrect invocation!');
  } return it;
};


/***/ }),
/* 93 */
/***/ (function(module, exports, __webpack_require__) {

var ctx = __webpack_require__(12);
var call = __webpack_require__(52);
var isArrayIter = __webpack_require__(53);
var anObject = __webpack_require__(5);
var toLength = __webpack_require__(33);
var getIterFn = __webpack_require__(38);
var BREAK = {};
var RETURN = {};
var exports = module.exports = function (iterable, entries, fn, that, ITERATOR) {
  var iterFn = ITERATOR ? function () { return iterable; } : getIterFn(iterable);
  var f = ctx(fn, that, entries ? 2 : 1);
  var index = 0;
  var length, step, iterator, result;
  if (typeof iterFn != 'function') throw TypeError(iterable + ' is not iterable!');
  // fast case for arrays with default iterator
  if (isArrayIter(iterFn)) for (length = toLength(iterable.length); length > index; index++) {
    result = entries ? f(anObject(step = iterable[index])[0], step[1]) : f(iterable[index]);
    if (result === BREAK || result === RETURN) return result;
  } else for (iterator = iterFn.call(iterable); !(step = iterator.next()).done;) {
    result = call(iterator, f, step.value, entries);
    if (result === BREAK || result === RETURN) return result;
  }
};
exports.BREAK = BREAK;
exports.RETURN = RETURN;


/***/ }),
/* 94 */
/***/ (function(module, exports) {

// fast apply, http://jsperf.lnkit.com/fast-apply/5
module.exports = function (fn, args, that) {
  var un = that === undefined;
  switch (args.length) {
    case 0: return un ? fn()
                      : fn.call(that);
    case 1: return un ? fn(args[0])
                      : fn.call(that, args[0]);
    case 2: return un ? fn(args[0], args[1])
                      : fn.call(that, args[0], args[1]);
    case 3: return un ? fn(args[0], args[1], args[2])
                      : fn.call(that, args[0], args[1], args[2]);
    case 4: return un ? fn(args[0], args[1], args[2], args[3])
                      : fn.call(that, args[0], args[1], args[2], args[3]);
  } return fn.apply(that, args);
};


/***/ }),
/* 95 */
/***/ (function(module, exports, __webpack_require__) {

var global = __webpack_require__(1);
var macrotask = __webpack_require__(55).set;
var Observer = global.MutationObserver || global.WebKitMutationObserver;
var process = global.process;
var Promise = global.Promise;
var isNode = __webpack_require__(22)(process) == 'process';

module.exports = function () {
  var head, last, notify;

  var flush = function () {
    var parent, fn;
    if (isNode && (parent = process.domain)) parent.exit();
    while (head) {
      fn = head.fn;
      head = head.next;
      try {
        fn();
      } catch (e) {
        if (head) notify();
        else last = undefined;
        throw e;
      }
    } last = undefined;
    if (parent) parent.enter();
  };

  // Node.js
  if (isNode) {
    notify = function () {
      process.nextTick(flush);
    };
  // browsers with MutationObserver, except iOS Safari - https://github.com/zloirock/core-js/issues/339
  } else if (Observer && !(global.navigator && global.navigator.standalone)) {
    var toggle = true;
    var node = document.createTextNode('');
    new Observer(flush).observe(node, { characterData: true }); // eslint-disable-line no-new
    notify = function () {
      node.data = toggle = !toggle;
    };
  // environments with maybe non-completely correct, but existent Promise
  } else if (Promise && Promise.resolve) {
    // Promise.resolve without an argument throws an error in LG WebOS 2
    var promise = Promise.resolve(undefined);
    notify = function () {
      promise.then(flush);
    };
  // for other environments - macrotask based on:
  // - setImmediate
  // - MessageChannel
  // - window.postMessag
  // - onreadystatechange
  // - setTimeout
  } else {
    notify = function () {
      // strange IE + webpack dev server bug - use .call(global)
      macrotask.call(global, flush);
    };
  }

  return function (fn) {
    var task = { fn: fn, next: undefined };
    if (last) last.next = task;
    if (!head) {
      head = task;
      notify();
    } last = task;
  };
};


/***/ }),
/* 96 */
/***/ (function(module, exports, __webpack_require__) {

var global = __webpack_require__(1);
var navigator = global.navigator;

module.exports = navigator && navigator.userAgent || '';


/***/ }),
/* 97 */
/***/ (function(module, exports, __webpack_require__) {

var hide = __webpack_require__(10);
module.exports = function (target, src, safe) {
  for (var key in src) {
    if (safe && target[key]) target[key] = src[key];
    else hide(target, key, src[key]);
  } return target;
};


/***/ }),
/* 98 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";

var global = __webpack_require__(1);
var core = __webpack_require__(0);
var dP = __webpack_require__(6);
var DESCRIPTORS = __webpack_require__(7);
var SPECIES = __webpack_require__(2)('species');

module.exports = function (KEY) {
  var C = typeof core[KEY] == 'function' ? core[KEY] : global[KEY];
  if (DESCRIPTORS && C && !C[SPECIES]) dP.f(C, SPECIES, {
    configurable: true,
    get: function () { return this; }
  });
};


/***/ }),
/* 99 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";
// https://github.com/tc39/proposal-promise-finally

var $export = __webpack_require__(4);
var core = __webpack_require__(0);
var global = __webpack_require__(1);
var speciesConstructor = __webpack_require__(54);
var promiseResolve = __webpack_require__(57);

$export($export.P + $export.R, 'Promise', { 'finally': function (onFinally) {
  var C = speciesConstructor(this, core.Promise || global.Promise);
  var isFunction = typeof onFinally == 'function';
  return this.then(
    isFunction ? function (x) {
      return promiseResolve(C, onFinally()).then(function () { return x; });
    } : onFinally,
    isFunction ? function (e) {
      return promiseResolve(C, onFinally()).then(function () { throw e; });
    } : onFinally
  );
} });


/***/ }),
/* 100 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";

// https://github.com/tc39/proposal-promise-try
var $export = __webpack_require__(4);
var newPromiseCapability = __webpack_require__(39);
var perform = __webpack_require__(56);

$export($export.S, 'Promise', { 'try': function (callbackfn) {
  var promiseCapability = newPromiseCapability.f(this);
  var result = perform(callbackfn);
  (result.e ? promiseCapability.reject : promiseCapability.resolve)(result.v);
  return promiseCapability.promise;
} });


/***/ }),
/* 101 */
/***/ (function(module, exports, __webpack_require__) {

module.exports = { "default": __webpack_require__(102), __esModule: true };

/***/ }),
/* 102 */
/***/ (function(module, exports, __webpack_require__) {

__webpack_require__(103);
module.exports = __webpack_require__(0).Object.assign;


/***/ }),
/* 103 */
/***/ (function(module, exports, __webpack_require__) {

// 19.1.3.1 Object.assign(target, source)
var $export = __webpack_require__(4);

$export($export.S + $export.F, 'Object', { assign: __webpack_require__(104) });


/***/ }),
/* 104 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";

// 19.1.2.1 Object.assign(target, source, ...)
var DESCRIPTORS = __webpack_require__(7);
var getKeys = __webpack_require__(21);
var gOPS = __webpack_require__(40);
var pIE = __webpack_require__(27);
var toObject = __webpack_require__(16);
var IObject = __webpack_require__(49);
var $assign = Object.assign;

// should work with symbols and should have deterministic property order (V8 bug)
module.exports = !$assign || __webpack_require__(13)(function () {
  var A = {};
  var B = {};
  // eslint-disable-next-line no-undef
  var S = Symbol();
  var K = 'abcdefghijklmnopqrst';
  A[S] = 7;
  K.split('').forEach(function (k) { B[k] = k; });
  return $assign({}, A)[S] != 7 || Object.keys($assign({}, B)).join('') != K;
}) ? function assign(target, source) { // eslint-disable-line no-unused-vars
  var T = toObject(target);
  var aLen = arguments.length;
  var index = 1;
  var getSymbols = gOPS.f;
  var isEnum = pIE.f;
  while (aLen > index) {
    var S = IObject(arguments[index++]);
    var keys = getSymbols ? getKeys(S).concat(getSymbols(S)) : getKeys(S);
    var length = keys.length;
    var j = 0;
    var key;
    while (length > j) {
      key = keys[j++];
      if (!DESCRIPTORS || isEnum.call(S, key)) T[key] = S[key];
    }
  } return T;
} : $assign;


/***/ }),
/* 105 */
/***/ (function(module, exports, __webpack_require__) {

__webpack_require__(106);
module.exports = __webpack_require__(0).Object.getPrototypeOf;


/***/ }),
/* 106 */
/***/ (function(module, exports, __webpack_require__) {

// 19.1.2.9 Object.getPrototypeOf(O)
var toObject = __webpack_require__(16);
var $getPrototypeOf = __webpack_require__(51);

__webpack_require__(60)('getPrototypeOf', function () {
  return function getPrototypeOf(it) {
    return $getPrototypeOf(toObject(it));
  };
});


/***/ }),
/* 107 */
/***/ (function(module, exports, __webpack_require__) {

module.exports = { "default": __webpack_require__(108), __esModule: true };

/***/ }),
/* 108 */
/***/ (function(module, exports, __webpack_require__) {

__webpack_require__(109);
var $Object = __webpack_require__(0).Object;
module.exports = function defineProperty(it, key, desc) {
  return $Object.defineProperty(it, key, desc);
};


/***/ }),
/* 109 */
/***/ (function(module, exports, __webpack_require__) {

var $export = __webpack_require__(4);
// 19.1.2.4 / 15.2.3.6 Object.defineProperty(O, P, Attributes)
$export($export.S + $export.F * !__webpack_require__(7), 'Object', { defineProperty: __webpack_require__(6).f });


/***/ }),
/* 110 */
/***/ (function(module, exports, __webpack_require__) {

module.exports = { "default": __webpack_require__(111), __esModule: true };

/***/ }),
/* 111 */
/***/ (function(module, exports, __webpack_require__) {

__webpack_require__(18);
__webpack_require__(26);
module.exports = __webpack_require__(41).f('iterator');


/***/ }),
/* 112 */
/***/ (function(module, exports, __webpack_require__) {

module.exports = { "default": __webpack_require__(113), __esModule: true };

/***/ }),
/* 113 */
/***/ (function(module, exports, __webpack_require__) {

__webpack_require__(114);
__webpack_require__(44);
__webpack_require__(119);
__webpack_require__(120);
module.exports = __webpack_require__(0).Symbol;


/***/ }),
/* 114 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";

// ECMAScript 6 symbols shim
var global = __webpack_require__(1);
var has = __webpack_require__(11);
var DESCRIPTORS = __webpack_require__(7);
var $export = __webpack_require__(4);
var redefine = __webpack_require__(47);
var META = __webpack_require__(115).KEY;
var $fails = __webpack_require__(13);
var shared = __webpack_require__(35);
var setToStringTag = __webpack_require__(25);
var uid = __webpack_require__(24);
var wks = __webpack_require__(2);
var wksExt = __webpack_require__(41);
var wksDefine = __webpack_require__(42);
var enumKeys = __webpack_require__(116);
var isArray = __webpack_require__(117);
var anObject = __webpack_require__(5);
var isObject = __webpack_require__(8);
var toObject = __webpack_require__(16);
var toIObject = __webpack_require__(15);
var toPrimitive = __webpack_require__(31);
var createDesc = __webpack_require__(20);
var _create = __webpack_require__(32);
var gOPNExt = __webpack_require__(118);
var $GOPD = __webpack_require__(66);
var $GOPS = __webpack_require__(40);
var $DP = __webpack_require__(6);
var $keys = __webpack_require__(21);
var gOPD = $GOPD.f;
var dP = $DP.f;
var gOPN = gOPNExt.f;
var $Symbol = global.Symbol;
var $JSON = global.JSON;
var _stringify = $JSON && $JSON.stringify;
var PROTOTYPE = 'prototype';
var HIDDEN = wks('_hidden');
var TO_PRIMITIVE = wks('toPrimitive');
var isEnum = {}.propertyIsEnumerable;
var SymbolRegistry = shared('symbol-registry');
var AllSymbols = shared('symbols');
var OPSymbols = shared('op-symbols');
var ObjectProto = Object[PROTOTYPE];
var USE_NATIVE = typeof $Symbol == 'function' && !!$GOPS.f;
var QObject = global.QObject;
// Don't use setters in Qt Script, https://github.com/zloirock/core-js/issues/173
var setter = !QObject || !QObject[PROTOTYPE] || !QObject[PROTOTYPE].findChild;

// fallback for old Android, https://code.google.com/p/v8/issues/detail?id=687
var setSymbolDesc = DESCRIPTORS && $fails(function () {
  return _create(dP({}, 'a', {
    get: function () { return dP(this, 'a', { value: 7 }).a; }
  })).a != 7;
}) ? function (it, key, D) {
  var protoDesc = gOPD(ObjectProto, key);
  if (protoDesc) delete ObjectProto[key];
  dP(it, key, D);
  if (protoDesc && it !== ObjectProto) dP(ObjectProto, key, protoDesc);
} : dP;

var wrap = function (tag) {
  var sym = AllSymbols[tag] = _create($Symbol[PROTOTYPE]);
  sym._k = tag;
  return sym;
};

var isSymbol = USE_NATIVE && typeof $Symbol.iterator == 'symbol' ? function (it) {
  return typeof it == 'symbol';
} : function (it) {
  return it instanceof $Symbol;
};

var $defineProperty = function defineProperty(it, key, D) {
  if (it === ObjectProto) $defineProperty(OPSymbols, key, D);
  anObject(it);
  key = toPrimitive(key, true);
  anObject(D);
  if (has(AllSymbols, key)) {
    if (!D.enumerable) {
      if (!has(it, HIDDEN)) dP(it, HIDDEN, createDesc(1, {}));
      it[HIDDEN][key] = true;
    } else {
      if (has(it, HIDDEN) && it[HIDDEN][key]) it[HIDDEN][key] = false;
      D = _create(D, { enumerable: createDesc(0, false) });
    } return setSymbolDesc(it, key, D);
  } return dP(it, key, D);
};
var $defineProperties = function defineProperties(it, P) {
  anObject(it);
  var keys = enumKeys(P = toIObject(P));
  var i = 0;
  var l = keys.length;
  var key;
  while (l > i) $defineProperty(it, key = keys[i++], P[key]);
  return it;
};
var $create = function create(it, P) {
  return P === undefined ? _create(it) : $defineProperties(_create(it), P);
};
var $propertyIsEnumerable = function propertyIsEnumerable(key) {
  var E = isEnum.call(this, key = toPrimitive(key, true));
  if (this === ObjectProto && has(AllSymbols, key) && !has(OPSymbols, key)) return false;
  return E || !has(this, key) || !has(AllSymbols, key) || has(this, HIDDEN) && this[HIDDEN][key] ? E : true;
};
var $getOwnPropertyDescriptor = function getOwnPropertyDescriptor(it, key) {
  it = toIObject(it);
  key = toPrimitive(key, true);
  if (it === ObjectProto && has(AllSymbols, key) && !has(OPSymbols, key)) return;
  var D = gOPD(it, key);
  if (D && has(AllSymbols, key) && !(has(it, HIDDEN) && it[HIDDEN][key])) D.enumerable = true;
  return D;
};
var $getOwnPropertyNames = function getOwnPropertyNames(it) {
  var names = gOPN(toIObject(it));
  var result = [];
  var i = 0;
  var key;
  while (names.length > i) {
    if (!has(AllSymbols, key = names[i++]) && key != HIDDEN && key != META) result.push(key);
  } return result;
};
var $getOwnPropertySymbols = function getOwnPropertySymbols(it) {
  var IS_OP = it === ObjectProto;
  var names = gOPN(IS_OP ? OPSymbols : toIObject(it));
  var result = [];
  var i = 0;
  var key;
  while (names.length > i) {
    if (has(AllSymbols, key = names[i++]) && (IS_OP ? has(ObjectProto, key) : true)) result.push(AllSymbols[key]);
  } return result;
};

// 19.4.1.1 Symbol([description])
if (!USE_NATIVE) {
  $Symbol = function Symbol() {
    if (this instanceof $Symbol) throw TypeError('Symbol is not a constructor!');
    var tag = uid(arguments.length > 0 ? arguments[0] : undefined);
    var $set = function (value) {
      if (this === ObjectProto) $set.call(OPSymbols, value);
      if (has(this, HIDDEN) && has(this[HIDDEN], tag)) this[HIDDEN][tag] = false;
      setSymbolDesc(this, tag, createDesc(1, value));
    };
    if (DESCRIPTORS && setter) setSymbolDesc(ObjectProto, tag, { configurable: true, set: $set });
    return wrap(tag);
  };
  redefine($Symbol[PROTOTYPE], 'toString', function toString() {
    return this._k;
  });

  $GOPD.f = $getOwnPropertyDescriptor;
  $DP.f = $defineProperty;
  __webpack_require__(65).f = gOPNExt.f = $getOwnPropertyNames;
  __webpack_require__(27).f = $propertyIsEnumerable;
  $GOPS.f = $getOwnPropertySymbols;

  if (DESCRIPTORS && !__webpack_require__(19)) {
    redefine(ObjectProto, 'propertyIsEnumerable', $propertyIsEnumerable, true);
  }

  wksExt.f = function (name) {
    return wrap(wks(name));
  };
}

$export($export.G + $export.W + $export.F * !USE_NATIVE, { Symbol: $Symbol });

for (var es6Symbols = (
  // 19.4.2.2, 19.4.2.3, 19.4.2.4, 19.4.2.6, 19.4.2.8, 19.4.2.9, 19.4.2.10, 19.4.2.11, 19.4.2.12, 19.4.2.13, 19.4.2.14
  'hasInstance,isConcatSpreadable,iterator,match,replace,search,species,split,toPrimitive,toStringTag,unscopables'
).split(','), j = 0; es6Symbols.length > j;)wks(es6Symbols[j++]);

for (var wellKnownSymbols = $keys(wks.store), k = 0; wellKnownSymbols.length > k;) wksDefine(wellKnownSymbols[k++]);

$export($export.S + $export.F * !USE_NATIVE, 'Symbol', {
  // 19.4.2.1 Symbol.for(key)
  'for': function (key) {
    return has(SymbolRegistry, key += '')
      ? SymbolRegistry[key]
      : SymbolRegistry[key] = $Symbol(key);
  },
  // 19.4.2.5 Symbol.keyFor(sym)
  keyFor: function keyFor(sym) {
    if (!isSymbol(sym)) throw TypeError(sym + ' is not a symbol!');
    for (var key in SymbolRegistry) if (SymbolRegistry[key] === sym) return key;
  },
  useSetter: function () { setter = true; },
  useSimple: function () { setter = false; }
});

$export($export.S + $export.F * !USE_NATIVE, 'Object', {
  // 19.1.2.2 Object.create(O [, Properties])
  create: $create,
  // 19.1.2.4 Object.defineProperty(O, P, Attributes)
  defineProperty: $defineProperty,
  // 19.1.2.3 Object.defineProperties(O, Properties)
  defineProperties: $defineProperties,
  // 19.1.2.6 Object.getOwnPropertyDescriptor(O, P)
  getOwnPropertyDescriptor: $getOwnPropertyDescriptor,
  // 19.1.2.7 Object.getOwnPropertyNames(O)
  getOwnPropertyNames: $getOwnPropertyNames,
  // 19.1.2.8 Object.getOwnPropertySymbols(O)
  getOwnPropertySymbols: $getOwnPropertySymbols
});

// Chrome 38 and 39 `Object.getOwnPropertySymbols` fails on primitives
// https://bugs.chromium.org/p/v8/issues/detail?id=3443
var FAILS_ON_PRIMITIVES = $fails(function () { $GOPS.f(1); });

$export($export.S + $export.F * FAILS_ON_PRIMITIVES, 'Object', {
  getOwnPropertySymbols: function getOwnPropertySymbols(it) {
    return $GOPS.f(toObject(it));
  }
});

// 24.3.2 JSON.stringify(value [, replacer [, space]])
$JSON && $export($export.S + $export.F * (!USE_NATIVE || $fails(function () {
  var S = $Symbol();
  // MS Edge converts symbol values to JSON as {}
  // WebKit converts symbol values to JSON as null
  // V8 throws on boxed symbols
  return _stringify([S]) != '[null]' || _stringify({ a: S }) != '{}' || _stringify(Object(S)) != '{}';
})), 'JSON', {
  stringify: function stringify(it) {
    var args = [it];
    var i = 1;
    var replacer, $replacer;
    while (arguments.length > i) args.push(arguments[i++]);
    $replacer = replacer = args[1];
    if (!isObject(replacer) && it === undefined || isSymbol(it)) return; // IE8 returns string on undefined
    if (!isArray(replacer)) replacer = function (key, value) {
      if (typeof $replacer == 'function') value = $replacer.call(this, key, value);
      if (!isSymbol(value)) return value;
    };
    args[1] = replacer;
    return _stringify.apply($JSON, args);
  }
});

// 19.4.3.4 Symbol.prototype[@@toPrimitive](hint)
$Symbol[PROTOTYPE][TO_PRIMITIVE] || __webpack_require__(10)($Symbol[PROTOTYPE], TO_PRIMITIVE, $Symbol[PROTOTYPE].valueOf);
// 19.4.3.5 Symbol.prototype[@@toStringTag]
setToStringTag($Symbol, 'Symbol');
// 20.2.1.9 Math[@@toStringTag]
setToStringTag(Math, 'Math', true);
// 24.3.3 JSON[@@toStringTag]
setToStringTag(global.JSON, 'JSON', true);


/***/ }),
/* 115 */
/***/ (function(module, exports, __webpack_require__) {

var META = __webpack_require__(24)('meta');
var isObject = __webpack_require__(8);
var has = __webpack_require__(11);
var setDesc = __webpack_require__(6).f;
var id = 0;
var isExtensible = Object.isExtensible || function () {
  return true;
};
var FREEZE = !__webpack_require__(13)(function () {
  return isExtensible(Object.preventExtensions({}));
});
var setMeta = function (it) {
  setDesc(it, META, { value: {
    i: 'O' + ++id, // object ID
    w: {}          // weak collections IDs
  } });
};
var fastKey = function (it, create) {
  // return primitive with prefix
  if (!isObject(it)) return typeof it == 'symbol' ? it : (typeof it == 'string' ? 'S' : 'P') + it;
  if (!has(it, META)) {
    // can't set metadata to uncaught frozen object
    if (!isExtensible(it)) return 'F';
    // not necessary to add metadata
    if (!create) return 'E';
    // add missing metadata
    setMeta(it);
  // return object ID
  } return it[META].i;
};
var getWeak = function (it, create) {
  if (!has(it, META)) {
    // can't set metadata to uncaught frozen object
    if (!isExtensible(it)) return true;
    // not necessary to add metadata
    if (!create) return false;
    // add missing metadata
    setMeta(it);
  // return hash weak collections IDs
  } return it[META].w;
};
// add metadata on freeze-family methods calling
var onFreeze = function (it) {
  if (FREEZE && meta.NEED && isExtensible(it) && !has(it, META)) setMeta(it);
  return it;
};
var meta = module.exports = {
  KEY: META,
  NEED: false,
  fastKey: fastKey,
  getWeak: getWeak,
  onFreeze: onFreeze
};


/***/ }),
/* 116 */
/***/ (function(module, exports, __webpack_require__) {

// all enumerable object keys, includes symbols
var getKeys = __webpack_require__(21);
var gOPS = __webpack_require__(40);
var pIE = __webpack_require__(27);
module.exports = function (it) {
  var result = getKeys(it);
  var getSymbols = gOPS.f;
  if (getSymbols) {
    var symbols = getSymbols(it);
    var isEnum = pIE.f;
    var i = 0;
    var key;
    while (symbols.length > i) if (isEnum.call(it, key = symbols[i++])) result.push(key);
  } return result;
};


/***/ }),
/* 117 */
/***/ (function(module, exports, __webpack_require__) {

// 7.2.2 IsArray(argument)
var cof = __webpack_require__(22);
module.exports = Array.isArray || function isArray(arg) {
  return cof(arg) == 'Array';
};


/***/ }),
/* 118 */
/***/ (function(module, exports, __webpack_require__) {

// fallback for IE11 buggy Object.getOwnPropertyNames with iframe and window
var toIObject = __webpack_require__(15);
var gOPN = __webpack_require__(65).f;
var toString = {}.toString;

var windowNames = typeof window == 'object' && window && Object.getOwnPropertyNames
  ? Object.getOwnPropertyNames(window) : [];

var getWindowNames = function (it) {
  try {
    return gOPN(it);
  } catch (e) {
    return windowNames.slice();
  }
};

module.exports.f = function getOwnPropertyNames(it) {
  return windowNames && toString.call(it) == '[object Window]' ? getWindowNames(it) : gOPN(toIObject(it));
};


/***/ }),
/* 119 */
/***/ (function(module, exports, __webpack_require__) {

__webpack_require__(42)('asyncIterator');


/***/ }),
/* 120 */
/***/ (function(module, exports, __webpack_require__) {

__webpack_require__(42)('observable');


/***/ }),
/* 121 */
/***/ (function(module, exports, __webpack_require__) {

module.exports = { "default": __webpack_require__(122), __esModule: true };

/***/ }),
/* 122 */
/***/ (function(module, exports, __webpack_require__) {

__webpack_require__(123);
module.exports = __webpack_require__(0).Object.setPrototypeOf;


/***/ }),
/* 123 */
/***/ (function(module, exports, __webpack_require__) {

// 19.1.3.19 Object.setPrototypeOf(O, proto)
var $export = __webpack_require__(4);
$export($export.S, 'Object', { setPrototypeOf: __webpack_require__(124).set });


/***/ }),
/* 124 */
/***/ (function(module, exports, __webpack_require__) {

// Works with __proto__ only. Old v8 can't work with null proto objects.
/* eslint-disable no-proto */
var isObject = __webpack_require__(8);
var anObject = __webpack_require__(5);
var check = function (O, proto) {
  anObject(O);
  if (!isObject(proto) && proto !== null) throw TypeError(proto + ": can't set as prototype!");
};
module.exports = {
  set: Object.setPrototypeOf || ('__proto__' in {} ? // eslint-disable-line
    function (test, buggy, set) {
      try {
        set = __webpack_require__(12)(Function.call, __webpack_require__(66).f(Object.prototype, '__proto__').set, 2);
        set(test, []);
        buggy = !(test instanceof Array);
      } catch (e) { buggy = true; }
      return function setPrototypeOf(O, proto) {
        check(O, proto);
        if (buggy) O.__proto__ = proto;
        else set(O, proto);
        return O;
      };
    }({}, false) : undefined),
  check: check
};


/***/ }),
/* 125 */
/***/ (function(module, exports, __webpack_require__) {

module.exports = { "default": __webpack_require__(126), __esModule: true };

/***/ }),
/* 126 */
/***/ (function(module, exports, __webpack_require__) {

__webpack_require__(127);
var $Object = __webpack_require__(0).Object;
module.exports = function create(P, D) {
  return $Object.create(P, D);
};


/***/ }),
/* 127 */
/***/ (function(module, exports, __webpack_require__) {

var $export = __webpack_require__(4);
// 19.1.2.2 / 15.2.3.5 Object.create(O [, Properties])
$export($export.S, 'Object', { create: __webpack_require__(32) });


/***/ }),
/* 128 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";


Object.defineProperty(exports, "__esModule", {
  value: true
});

var _FlipMove = __webpack_require__(129);

var _FlipMove2 = _interopRequireDefault(_FlipMove);

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

exports.default = _FlipMove2.default;
/**
 * React Flip Move
 * (c) 2016-present Joshua Comeau
 */

module.exports = exports['default'];

/***/ }),
/* 129 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";


Object.defineProperty(exports, "__esModule", {
  value: true
});

var _slicedToArray = function () { function sliceIterator(arr, i) { var _arr = []; var _n = true; var _d = false; var _e = undefined; try { for (var _i = arr[Symbol.iterator](), _s; !(_n = (_s = _i.next()).done); _n = true) { _arr.push(_s.value); if (i && _arr.length === i) break; } } catch (err) { _d = true; _e = err; } finally { try { if (!_n && _i["return"]) _i["return"](); } finally { if (_d) throw _e; } } return _arr; } return function (arr, i) { if (Array.isArray(arr)) { return arr; } else if (Symbol.iterator in Object(arr)) { return sliceIterator(arr, i); } else { throw new TypeError("Invalid attempt to destructure non-iterable instance"); } }; }();

var _extends = Object.assign || function (target) { for (var i = 1; i < arguments.length; i++) { var source = arguments[i]; for (var key in source) { if (Object.prototype.hasOwnProperty.call(source, key)) { target[key] = source[key]; } } } return target; };

var _createClass = function () { function defineProperties(target, props) { for (var i = 0; i < props.length; i++) { var descriptor = props[i]; descriptor.enumerable = descriptor.enumerable || false; descriptor.configurable = true; if ("value" in descriptor) descriptor.writable = true; Object.defineProperty(target, descriptor.key, descriptor); } } return function (Constructor, protoProps, staticProps) { if (protoProps) defineProperties(Constructor.prototype, protoProps); if (staticProps) defineProperties(Constructor, staticProps); return Constructor; }; }();

var _react = __webpack_require__(9);

var _react2 = _interopRequireDefault(_react);

__webpack_require__(130);

var _propConverter = __webpack_require__(131);

var _propConverter2 = _interopRequireDefault(_propConverter);

var _domManipulation = __webpack_require__(134);

var _helpers = __webpack_require__(43);

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

function _classCallCheck(instance, Constructor) { if (!(instance instanceof Constructor)) { throw new TypeError("Cannot call a class as a function"); } }

function _possibleConstructorReturn(self, call) { if (!self) { throw new ReferenceError("this hasn't been initialised - super() hasn't been called"); } return call && (typeof call === "object" || typeof call === "function") ? call : self; }

function _inherits(subClass, superClass) { if (typeof superClass !== "function" && superClass !== null) { throw new TypeError("Super expression must either be null or a function, not " + typeof superClass); } subClass.prototype = Object.create(superClass && superClass.prototype, { constructor: { value: subClass, enumerable: false, writable: true, configurable: true } }); if (superClass) Object.setPrototypeOf ? Object.setPrototypeOf(subClass, superClass) : subClass.__proto__ = superClass; }
/**
 * React Flip Move
 * (c) 2016-present Joshua Comeau
 *
 * For information on how this code is laid out, check out CODE_TOUR.md
 */

/* eslint-disable react/prop-types */

var transitionEnd = (0, _domManipulation.whichTransitionEvent)();
var noBrowserSupport = !transitionEnd;

function getKey(childData) {
  return childData.key || '';
}

var FlipMove = function (_Component) {
  _inherits(FlipMove, _Component);

  function FlipMove() {
    var _ref;

    var _temp, _this, _ret;

    _classCallCheck(this, FlipMove);

    for (var _len = arguments.length, args = Array(_len), _key = 0; _key < _len; _key++) {
      args[_key] = arguments[_key];
    }

    return _ret = (_temp = (_this = _possibleConstructorReturn(this, (_ref = FlipMove.__proto__ || Object.getPrototypeOf(FlipMove)).call.apply(_ref, [this].concat(args))), _this), _this.state = {
      children: _react.Children.toArray(_this.props.children).map(function (element) {
        return _extends({}, element, {
          element: element,
          appearing: true
        });
      })
    }, _this.childrenData = {}, _this.parentData = {
      domNode: null,
      boundingBox: null
    }, _this.heightPlaceholderData = {
      domNode: null
    }, _this.remainingAnimations = 0, _this.childrenToAnimate = [], _this.runAnimation = function () {
      var dynamicChildren = _this.state.children.filter(_this.doesChildNeedToBeAnimated);

      dynamicChildren.forEach(function (child, n) {
        _this.remainingAnimations += 1;
        _this.childrenToAnimate.push(getKey(child));
        _this.animateChild(child, n);
      });

      if (typeof _this.props.onStartAll === 'function') {
        _this.callChildrenHook(_this.props.onStartAll);
      }
    }, _this.doesChildNeedToBeAnimated = function (child) {
      // If the child doesn't have a key, it's an immovable child (one that we
      // do not want to do FLIP stuff to.)
      if (!getKey(child)) {
        return false;
      }

      var childData = _this.getChildData(getKey(child));
      var childDomNode = childData.domNode;
      var childBoundingBox = childData.boundingBox;
      var parentBoundingBox = _this.parentData.boundingBox;

      if (!childDomNode) {
        return false;
      }

      var _this$props = _this.props,
          appearAnimation = _this$props.appearAnimation,
          enterAnimation = _this$props.enterAnimation,
          leaveAnimation = _this$props.leaveAnimation,
          getPosition = _this$props.getPosition;


      var isAppearingWithAnimation = child.appearing && appearAnimation;
      var isEnteringWithAnimation = child.entering && enterAnimation;
      var isLeavingWithAnimation = child.leaving && leaveAnimation;

      if (isAppearingWithAnimation || isEnteringWithAnimation || isLeavingWithAnimation) {
        return true;
      }

      // If it isn't entering/leaving, we want to animate it if it's
      // on-screen position has changed.

      var _getPositionDelta = (0, _domManipulation.getPositionDelta)({
        childDomNode: childDomNode,
        childBoundingBox: childBoundingBox,
        parentBoundingBox: parentBoundingBox,
        getPosition: getPosition
      }),
          _getPositionDelta2 = _slicedToArray(_getPositionDelta, 2),
          dX = _getPositionDelta2[0],
          dY = _getPositionDelta2[1];

      return dX !== 0 || dY !== 0;
    }, _temp), _possibleConstructorReturn(_this, _ret);
  }
  // Copy props.children into state.
  // To understand why this is important (and not an anti-pattern), consider
  // how "leave" animations work. An item has "left" when the component
  // receives a new set of props that do NOT contain the item.
  // If we just render the props as-is, the item would instantly disappear.
  // We want to keep the item rendered for a little while, until its animation
  // can complete. Because we cannot mutate props, we make `state` the source
  // of truth.


  // FlipMove needs to know quite a bit about its children in order to do
  // its job. We store these as a property on the instance. We're not using
  // state, because we don't want changes to trigger re-renders, we just
  // need a place to keep the data for reference, when changes happen.
  // This field should not be accessed directly. Instead, use getChildData,
  // putChildData, etc...


  // Similarly, track the dom node and box of our parent element.


  // If `maintainContainerHeight` prop is set to true, we'll create a
  // placeholder element which occupies space so that the parent height
  // doesn't change when items are removed from the document flow (which
  // happens during leave animations)


  // Keep track of remaining animations so we know when to fire the
  // all-finished callback, and clean up after ourselves.
  // NOTE: we can't simply use childrenToAnimate.length to track remaining
  // animations, because we need to maintain the list of animating children,
  // to pass to the `onFinishAll` handler.


  _createClass(FlipMove, [{
    key: 'componentDidMount',
    value: function componentDidMount() {
      // Run our `appearAnimation` if it was requested, right after the
      // component mounts.
      var shouldTriggerFLIP = this.props.appearAnimation && !this.isAnimationDisabled(this.props);

      if (shouldTriggerFLIP) {
        this.prepForAnimation();
        this.runAnimation();
      }
    }
  }, {
    key: 'componentWillReceiveProps',
    value: function componentWillReceiveProps(nextProps) {
      // When the component is handed new props, we need to figure out the
      // "resting" position of all currently-rendered DOM nodes.
      // We store that data in this.parent and this.children,
      // so it can be used later to work out the animation.
      this.updateBoundingBoxCaches();

      // Convert opaque children object to array.
      var nextChildren = _react.Children.toArray(nextProps.children);

      // Next, we need to update our state, so that it contains our new set of
      // children. If animation is disabled or unsupported, this is easy;
      // we just copy our props into state.
      // Assuming that we can animate, though, we have to do some work.
      // Essentially, we want to keep just-deleted nodes in the DOM for a bit
      // longer, so that we can animate them away.
      this.setState({
        children: this.isAnimationDisabled(nextProps) ? nextChildren.map(function (element) {
          return _extends({}, element, { element: element });
        }) : this.calculateNextSetOfChildren(nextChildren)
      });
    }
  }, {
    key: 'componentDidUpdate',
    value: function componentDidUpdate(previousProps) {
      // If the children have been re-arranged, moved, or added/removed,
      // trigger the main FLIP animation.
      //
      // IMPORTANT: We need to make sure that the children have actually changed.
      // At the end of the transition, we clean up nodes that need to be removed.
      var oldChildrenKeys = _react.Children.toArray(this.props.children).map(function (d) {
        return d.key;
      });
      var nextChildrenKeys = _react.Children.toArray(previousProps.children).map(function (d) {
        return d.key;
      });

      var shouldTriggerFLIP = !(0, _helpers.arraysEqual)(oldChildrenKeys, nextChildrenKeys) && !this.isAnimationDisabled(this.props);

      if (shouldTriggerFLIP) {
        this.prepForAnimation();
        this.runAnimation();
      }
    }
  }, {
    key: 'calculateNextSetOfChildren',
    value: function calculateNextSetOfChildren(nextChildren) {
      var _this2 = this;

      // We want to:
      //   - Mark all new children as `entering`
      //   - Pull in previous children that aren't in nextChildren, and mark them
      //     as `leaving`
      //   - Preserve the nextChildren list order, with leaving children in their
      //     appropriate places.
      //

      var updatedChildren = nextChildren.map(function (nextChild) {
        var child = _this2.findChildByKey(nextChild.key || '');

        // If the current child did exist, but it was in the midst of leaving,
        // we want to treat it as though it's entering
        var isEntering = !child || child.leaving;

        return _extends({}, nextChild, { element: nextChild, entering: isEntering });
      });

      // This is tricky. We want to keep the nextChildren's ordering, but with
      // any just-removed items maintaining their original position.
      // eg.
      //   this.state.children  = [ 1, 2, 3, 4 ]
      //   nextChildren         = [ 3, 1 ]
      //
      // In this example, we've removed the '2' & '4'
      // We want to end up with:  [ 2, 3, 1, 4 ]
      //
      // To accomplish that, we'll iterate through this.state.children. whenever
      // we find a match, we'll append our `leaving` flag to it, and insert it
      // into the nextChildren in its ORIGINAL position. Note that, as we keep
      // inserting old items into the new list, the "original" position will
      // keep incrementing.
      var numOfChildrenLeaving = 0;
      this.state.children.forEach(function (child, index) {
        var isLeaving = !nextChildren.find(function (_ref2) {
          var key = _ref2.key;
          return key === getKey(child);
        });

        // If the child isn't leaving (or, if there is no leave animation),
        // we don't need to add it into the state children.
        if (!isLeaving || !_this2.props.leaveAnimation) return;

        var nextChild = _extends({}, child, { leaving: true });
        var nextChildIndex = index + numOfChildrenLeaving;

        updatedChildren.splice(nextChildIndex, 0, nextChild);
        numOfChildrenLeaving += 1;
      });

      return updatedChildren;
    }
  }, {
    key: 'prepForAnimation',
    value: function prepForAnimation() {
      var _this3 = this;

      // Our animation prep consists of:
      // - remove children that are leaving from the DOM flow, so that the new
      //   layout can be accurately calculated,
      // - update the placeholder container height, if needed, to ensure that
      //   the parent's height doesn't collapse.

      var _props = this.props,
          leaveAnimation = _props.leaveAnimation,
          maintainContainerHeight = _props.maintainContainerHeight,
          getPosition = _props.getPosition;

      // we need to make all leaving nodes "invisible" to the layout calculations
      // that will take place in the next step (this.runAnimation).

      if (leaveAnimation) {
        var leavingChildren = this.state.children.filter(function (child) {
          return child.leaving;
        });

        leavingChildren.forEach(function (leavingChild) {
          var childData = _this3.getChildData(getKey(leavingChild));

          // We need to take the items out of the "flow" of the document, so that
          // its siblings can move to take its place.
          if (childData.boundingBox) {
            (0, _domManipulation.removeNodeFromDOMFlow)(childData, _this3.props.verticalAlignment);
          }
        });

        if (maintainContainerHeight && this.heightPlaceholderData.domNode) {
          (0, _domManipulation.updateHeightPlaceholder)({
            domNode: this.heightPlaceholderData.domNode,
            parentData: this.parentData,
            getPosition: getPosition
          });
        }
      }

      // For all children not in the middle of entering or leaving,
      // we need to reset the transition, so that the NEW shuffle starts from
      // the right place.
      this.state.children.forEach(function (child) {
        var _getChildData = _this3.getChildData(getKey(child)),
            domNode = _getChildData.domNode;

        // Ignore children that don't render DOM nodes (eg. by returning null)


        if (!domNode) {
          return;
        }

        if (!child.entering && !child.leaving) {
          (0, _domManipulation.applyStylesToDOMNode)({
            domNode: domNode,
            styles: {
              transition: ''
            }
          });
        }
      });
    }
  }, {
    key: 'animateChild',
    value: function animateChild(child, index) {
      var _this4 = this;

      var _getChildData2 = this.getChildData(getKey(child)),
          domNode = _getChildData2.domNode;

      if (!domNode) {
        return;
      }

      // Apply the relevant style for this DOM node
      // This is the offset from its actual DOM position.
      // eg. if an item has been re-rendered 20px lower, we want to apply a
      // style of 'transform: translate(-20px)', so that it appears to be where
      // it started.
      // In FLIP terminology, this is the 'Invert' stage.
      (0, _domManipulation.applyStylesToDOMNode)({
        domNode: domNode,
        styles: this.computeInitialStyles(child)
      });

      // Start by invoking the onStart callback for this child.
      if (this.props.onStart) this.props.onStart(child, domNode);

      // Next, animate the item from it's artificially-offset position to its
      // new, natural position.
      requestAnimationFrame(function () {
        requestAnimationFrame(function () {
          // NOTE, RE: the double-requestAnimationFrame:
          // Sadly, this is the most browser-compatible way to do this I've found.
          // Essentially we need to set the initial styles outside of any request
          // callbacks to avoid batching them. Then, a frame needs to pass with
          // the styles above rendered. Then, on the second frame, we can apply
          // our final styles to perform the animation.

          // Our first order of business is to "undo" the styles applied in the
          // previous frames, while also adding a `transition` property.
          // This way, the item will smoothly transition from its old position
          // to its new position.

          // eslint-disable-next-line flowtype/require-variable-type
          var styles = {
            transition: (0, _domManipulation.createTransitionString)(index, _this4.props),
            transform: '',
            opacity: ''
          };

          if (child.appearing && _this4.props.appearAnimation) {
            styles = _extends({}, styles, _this4.props.appearAnimation.to);
          } else if (child.entering && _this4.props.enterAnimation) {
            styles = _extends({}, styles, _this4.props.enterAnimation.to);
          } else if (child.leaving && _this4.props.leaveAnimation) {
            styles = _extends({}, styles, _this4.props.leaveAnimation.to);
          }

          // In FLIP terminology, this is the 'Play' stage.
          (0, _domManipulation.applyStylesToDOMNode)({ domNode: domNode, styles: styles });
        });
      });

      this.bindTransitionEndHandler(child);
    }
  }, {
    key: 'bindTransitionEndHandler',
    value: function bindTransitionEndHandler(child) {
      var _this5 = this;

      var _getChildData3 = this.getChildData(getKey(child)),
          domNode = _getChildData3.domNode;

      if (!domNode) {
        return;
      }

      // The onFinish callback needs to be bound to the transitionEnd event.
      // We also need to unbind it when the transition completes, so this ugly
      // inline function is required (we need it here so it closes over
      // dependent variables `child` and `domNode`)
      var transitionEndHandler = function transitionEndHandler(ev) {
        // It's possible that this handler is fired not on our primary transition,
        // but on a nested transition (eg. a hover effect). Ignore these cases.
        if (ev.target !== domNode) return;

        // Remove the 'transition' inline style we added. This is cleanup.
        domNode.style.transition = '';

        // Trigger any applicable onFinish/onFinishAll hooks
        _this5.triggerFinishHooks(child, domNode);

        domNode.removeEventListener(transitionEnd, transitionEndHandler);

        if (child.leaving) {
          _this5.removeChildData(getKey(child));
        }
      };

      domNode.addEventListener(transitionEnd, transitionEndHandler);
    }
  }, {
    key: 'triggerFinishHooks',
    value: function triggerFinishHooks(child, domNode) {
      var _this6 = this;

      if (this.props.onFinish) this.props.onFinish(child, domNode);

      // Reduce the number of children we need to animate by 1,
      // so that we can tell when all children have finished.
      this.remainingAnimations -= 1;

      if (this.remainingAnimations === 0) {
        // Remove any items from the DOM that have left, and reset `entering`.
        var nextChildren = this.state.children.filter(function (_ref3) {
          var leaving = _ref3.leaving;
          return !leaving;
        }).map(function (item) {
          return _extends({}, item, {
            appearing: false,
            entering: false
          });
        });

        this.setState({ children: nextChildren }, function () {
          if (typeof _this6.props.onFinishAll === 'function') {
            _this6.callChildrenHook(_this6.props.onFinishAll);
          }

          // Reset our variables for the next iteration
          _this6.childrenToAnimate = [];
        });

        // If the placeholder was holding the container open while elements were
        // leaving, we we can now set its height to zero.
        if (this.heightPlaceholderData.domNode) {
          this.heightPlaceholderData.domNode.style.height = '0';
        }
      }
    }
  }, {
    key: 'callChildrenHook',
    value: function callChildrenHook(hook) {
      var _this7 = this;

      var elements = [];
      var domNodes = [];

      this.childrenToAnimate.forEach(function (childKey) {
        // If this was an exit animation, the child may no longer exist.
        // If so, skip it.
        var child = _this7.findChildByKey(childKey);

        if (!child) {
          return;
        }

        elements.push(child);

        if (_this7.hasChildData(childKey)) {
          domNodes.push(_this7.getChildData(childKey).domNode);
        }
      });

      hook(elements, domNodes);
    }
  }, {
    key: 'updateBoundingBoxCaches',
    value: function updateBoundingBoxCaches() {
      var _this8 = this;

      // This is the ONLY place that parentData and childrenData's
      // bounding boxes are updated. They will be calculated at other times
      // to be compared to this value, but it's important that the cache is
      // updated once per update.
      var parentDomNode = this.parentData.domNode;

      if (!parentDomNode) {
        return;
      }

      this.parentData.boundingBox = this.props.getPosition(parentDomNode);

      this.state.children.forEach(function (child) {
        var childKey = getKey(child);

        // It is possible that a child does not have a `key` property;
        // Ignore these children, they don't need to be moved.
        if (!childKey) {
          return;
        }

        // In very rare circumstances, for reasons unknown, the ref is never
        // populated for certain children. In this case, avoid doing this update.
        // see: https://github.com/joshwcomeau/react-flip-move/pull/91
        if (!_this8.hasChildData(childKey)) {
          return;
        }

        var childData = _this8.getChildData(childKey);

        // If the child element returns null, we need to avoid trying to
        // account for it
        if (!childData.domNode || !child) {
          return;
        }

        _this8.setChildData(childKey, {
          boundingBox: (0, _domManipulation.getRelativeBoundingBox)({
            childDomNode: childData.domNode,
            parentDomNode: parentDomNode,
            getPosition: _this8.props.getPosition
          })
        });
      });
    }
  }, {
    key: 'computeInitialStyles',
    value: function computeInitialStyles(child) {
      if (child.appearing) {
        return this.props.appearAnimation ? this.props.appearAnimation.from : {};
      } else if (child.entering) {
        if (!this.props.enterAnimation) {
          return {};
        }
        // If this child was in the middle of leaving, it still has its
        // absolute positioning styles applied. We need to undo those.
        return _extends({
          position: '',
          top: '',
          left: '',
          right: '',
          bottom: ''
        }, this.props.enterAnimation.from);
      } else if (child.leaving) {
        return this.props.leaveAnimation ? this.props.leaveAnimation.from : {};
      }

      var childData = this.getChildData(getKey(child));
      var childDomNode = childData.domNode;
      var childBoundingBox = childData.boundingBox;
      var parentBoundingBox = this.parentData.boundingBox;

      if (!childDomNode) {
        return {};
      }

      var _getPositionDelta3 = (0, _domManipulation.getPositionDelta)({
        childDomNode: childDomNode,
        childBoundingBox: childBoundingBox,
        parentBoundingBox: parentBoundingBox,
        getPosition: this.props.getPosition
      }),
          _getPositionDelta4 = _slicedToArray(_getPositionDelta3, 2),
          dX = _getPositionDelta4[0],
          dY = _getPositionDelta4[1];

      return {
        transform: 'translate(' + dX + 'px, ' + dY + 'px)'
      };
    }

    // eslint-disable-next-line class-methods-use-this

  }, {
    key: 'isAnimationDisabled',
    value: function isAnimationDisabled(props) {
      // If the component is explicitly passed a `disableAllAnimations` flag,
      // we can skip this whole process. Similarly, if all of the numbers have
      // been set to 0, there is no point in trying to animate; doing so would
      // only cause a flicker (and the intent is probably to disable animations)
      // We can also skip this rigamarole if there's no browser support for it.
      return noBrowserSupport || props.disableAllAnimations || props.duration === 0 && props.delay === 0 && props.staggerDurationBy === 0 && props.staggerDelayBy === 0;
    }
  }, {
    key: 'findChildByKey',
    value: function findChildByKey(key) {
      return this.state.children.find(function (child) {
        return getKey(child) === key;
      });
    }
  }, {
    key: 'hasChildData',
    value: function hasChildData(key) {
      // Object has some built-in properties on its prototype, such as toString.  hasOwnProperty makes
      // sure that key is present on childrenData itself, not on its prototype.
      return Object.prototype.hasOwnProperty.call(this.childrenData, key);
    }
  }, {
    key: 'getChildData',
    value: function getChildData(key) {
      return this.hasChildData(key) ? this.childrenData[key] : {};
    }
  }, {
    key: 'setChildData',
    value: function setChildData(key, data) {
      this.childrenData[key] = _extends({}, this.getChildData(key), data);
    }
  }, {
    key: 'removeChildData',
    value: function removeChildData(key) {
      delete this.childrenData[key];
    }
  }, {
    key: 'createHeightPlaceholder',
    value: function createHeightPlaceholder() {
      var _this9 = this;

      var typeName = this.props.typeName;

      // If requested, create an invisible element at the end of the list.
      // Its height will be modified to prevent the container from collapsing
      // prematurely.

      var isContainerAList = typeName === 'ul' || typeName === 'ol';
      var placeholderType = isContainerAList ? 'li' : 'div';

      return _react2.default.createElement(placeholderType, {
        key: 'height-placeholder',
        ref: function ref(domNode) {
          _this9.heightPlaceholderData.domNode = domNode;
        },
        style: { visibility: 'hidden', height: 0 }
      });
    }
  }, {
    key: 'childrenWithRefs',
    value: function childrenWithRefs() {
      var _this10 = this;

      // We need to clone the provided children, capturing a reference to the
      // underlying DOM node. Flip Move needs to use the React escape hatches to
      // be able to do its calculations.
      return this.state.children.map(function (child) {
        return _react2.default.cloneElement(child.element, {
          ref: function ref(element) {
            // Stateless Functional Components are not supported by FlipMove,
            // because they don't have instances.
            if (!element) {
              return;
            }

            var domNode = (0, _domManipulation.getNativeNode)(element);
            _this10.setChildData(getKey(child), { domNode: domNode });
          }
        });
      });
    }
  }, {
    key: 'render',
    value: function render() {
      var _this11 = this;

      var _props2 = this.props,
          typeName = _props2.typeName,
          delegated = _props2.delegated,
          leaveAnimation = _props2.leaveAnimation,
          maintainContainerHeight = _props2.maintainContainerHeight;


      var props = _extends({}, delegated, {
        ref: function ref(node) {
          _this11.parentData.domNode = node;
        }
      });

      var children = this.childrenWithRefs();
      if (leaveAnimation && maintainContainerHeight) {
        children.push(this.createHeightPlaceholder());
      }

      return _react2.default.createElement(typeName, props, children);
    }
  }]);

  return FlipMove;
}(_react.Component);

exports.default = (0, _propConverter2.default)(FlipMove);
module.exports = exports['default'];

/***/ }),
/* 130 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";


// @noflow
/**
 * React Flip Move - Polyfills
 * (c) 2016-present Joshua Comeau
 */

/* eslint-disable */

if (!Array.prototype.find) {
  Array.prototype.find = function (predicate) {
    if (this === null) {
      throw new TypeError('Array.prototype.find called on null or undefined');
    }
    if (typeof predicate !== 'function') {
      throw new TypeError('predicate must be a function');
    }
    var list = Object(this);
    var length = list.length >>> 0;
    var thisArg = arguments[1];
    var value = void 0;

    for (var i = 0; i < length; i++) {
      value = list[i];
      if (predicate.call(thisArg, value, i, list)) {
        return value;
      }
    }
    return undefined;
  };
}

if (!Array.prototype.every) {
  Array.prototype.every = function (callbackfn, thisArg) {
    'use strict';

    var T, k;

    if (this == null) {
      throw new TypeError('this is null or not defined');
    }

    var O = Object(this);
    var len = O.length >>> 0;

    if (typeof callbackfn !== 'function') {
      throw new TypeError();
    }

    if (arguments.length > 1) {
      T = thisArg;
    }

    k = 0;

    while (k < len) {

      var kValue;

      if (k in O) {
        kValue = O[k];

        var testResult = callbackfn.call(T, kValue, k, O);

        if (!testResult) {
          return false;
        }
      }
      k++;
    }
    return true;
  };
}

if (!Array.isArray) {
  Array.isArray = function (arg) {
    return Object.prototype.toString.call(arg) === '[object Array]';
  };
}

/***/ }),
/* 131 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";
/* WEBPACK VAR INJECTION */(function(process) {

Object.defineProperty(exports, "__esModule", {
  value: true
});

var _typeof = typeof Symbol === "function" && typeof Symbol.iterator === "symbol" ? function (obj) { return typeof obj; } : function (obj) { return obj && typeof Symbol === "function" && obj.constructor === Symbol && obj !== Symbol.prototype ? "symbol" : typeof obj; };

var _extends = Object.assign || function (target) { for (var i = 1; i < arguments.length; i++) { var source = arguments[i]; for (var key in source) { if (Object.prototype.hasOwnProperty.call(source, key)) { target[key] = source[key]; } } } return target; };

var _createClass = function () { function defineProperties(target, props) { for (var i = 0; i < props.length; i++) { var descriptor = props[i]; descriptor.enumerable = descriptor.enumerable || false; descriptor.configurable = true; if ("value" in descriptor) descriptor.writable = true; Object.defineProperty(target, descriptor.key, descriptor); } } return function (Constructor, protoProps, staticProps) { if (protoProps) defineProperties(Constructor.prototype, protoProps); if (staticProps) defineProperties(Constructor, staticProps); return Constructor; }; }();

var _react = __webpack_require__(9);

var _react2 = _interopRequireDefault(_react);

var _errorMessages = __webpack_require__(132);

var _enterLeavePresets = __webpack_require__(133);

var _helpers = __webpack_require__(43);

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

function _classCallCheck(instance, Constructor) { if (!(instance instanceof Constructor)) { throw new TypeError("Cannot call a class as a function"); } }

function _possibleConstructorReturn(self, call) { if (!self) { throw new ReferenceError("this hasn't been initialised - super() hasn't been called"); } return call && (typeof call === "object" || typeof call === "function") ? call : self; }

function _inherits(subClass, superClass) { if (typeof superClass !== "function" && superClass !== null) { throw new TypeError("Super expression must either be null or a function, not " + typeof superClass); } subClass.prototype = Object.create(superClass && superClass.prototype, { constructor: { value: subClass, enumerable: false, writable: true, configurable: true } }); if (superClass) Object.setPrototypeOf ? Object.setPrototypeOf(subClass, superClass) : subClass.__proto__ = superClass; }
/**
 * React Flip Move | propConverter
 * (c) 2016-present Joshua Comeau
 *
 * Abstracted away a bunch of the messy business with props.
 *   - props flow types and defaultProps
 *   - Type conversion (We accept 'string' and 'number' values for duration,
 *     delay, and other fields, but we actually need them to be ints.)
 *   - Children conversion (we need the children to be an array. May not always
 *     be, if a single child is passed in.)
 *   - Resolving animation presets into their base CSS styles
 */
/* eslint-disable block-scoped-var */

var nodeEnv = void 0;
try {
  nodeEnv = process.env.NODE_ENV;
} catch (e) {
  nodeEnv = 'development';
}

function propConverter(ComposedComponent) {
  var _class, _temp;

  return _temp = _class = function (_Component) {
    _inherits(FlipMovePropConverter, _Component);

    function FlipMovePropConverter() {
      _classCallCheck(this, FlipMovePropConverter);

      return _possibleConstructorReturn(this, (FlipMovePropConverter.__proto__ || Object.getPrototypeOf(FlipMovePropConverter)).apply(this, arguments));
    }

    _createClass(FlipMovePropConverter, [{
      key: 'checkForStatelessFunctionalComponents',


      // eslint-disable-next-line class-methods-use-this
      value: function checkForStatelessFunctionalComponents(children) {
        // Skip all console warnings in production.
        // Bail early, to avoid unnecessary work.
        if (nodeEnv === 'production') {
          return;
        }

        // FlipMove does not support stateless functional components.
        // Check to see if any supplied components won't work.
        // If the child doesn't have a key, it means we aren't animating it.
        // It's allowed to be an SFC, since we ignore it.
        var childArray = _react.Children.toArray(children);
        var noStateless = childArray.every(function (child) {
          return !(0, _helpers.isElementAnSFC)(child) || typeof child.key === 'undefined';
        });

        if (!noStateless) {
          (0, _errorMessages.statelessFunctionalComponentSupplied)();
        }
      }
    }, {
      key: 'convertProps',
      value: function convertProps(props) {
        var workingProps = {
          // explicitly bypass the props that don't need conversion
          children: props.children,
          easing: props.easing,
          onStart: props.onStart,
          onFinish: props.onFinish,
          onStartAll: props.onStartAll,
          onFinishAll: props.onFinishAll,
          typeName: props.typeName,
          disableAllAnimations: props.disableAllAnimations,
          getPosition: props.getPosition,
          maintainContainerHeight: props.maintainContainerHeight,
          verticalAlignment: props.verticalAlignment,

          // Do string-to-int conversion for all timing-related props
          duration: this.convertTimingProp('duration'),
          delay: this.convertTimingProp('delay'),
          staggerDurationBy: this.convertTimingProp('staggerDurationBy'),
          staggerDelayBy: this.convertTimingProp('staggerDelayBy'),

          // Our enter/leave animations can be specified as boolean (default or
          // disabled), string (preset name), or object (actual animation values).
          // Let's standardize this so that they're always objects
          appearAnimation: this.convertAnimationProp(props.appearAnimation, _enterLeavePresets.appearPresets),
          enterAnimation: this.convertAnimationProp(props.enterAnimation, _enterLeavePresets.enterPresets),
          leaveAnimation: this.convertAnimationProp(props.leaveAnimation, _enterLeavePresets.leavePresets),

          delegated: {}
        };

        this.checkForStatelessFunctionalComponents(workingProps.children);

        // Accept `disableAnimations`, but add a deprecation warning
        if (typeof props.disableAnimations !== 'undefined') {
          if (nodeEnv !== 'production') {
            (0, _errorMessages.deprecatedDisableAnimations)();
          }

          workingProps.disableAllAnimations = props.disableAnimations;
        }

        // Gather any additional props;
        // they will be delegated to the ReactElement created.
        var primaryPropKeys = Object.keys(workingProps);
        var delegatedProps = (0, _helpers.omit)(this.props, primaryPropKeys);

        // The FlipMove container element needs to have a non-static position.
        // We use `relative` by default, but it can be overridden by the user.
        // Now that we're delegating props, we need to merge this in.
        delegatedProps.style = _extends({
          position: 'relative'
        }, delegatedProps.style);

        workingProps.delegated = delegatedProps;

        return workingProps;
      }
    }, {
      key: 'convertTimingProp',
      value: function convertTimingProp(prop) {
        var rawValue = this.props[prop];

        var value = typeof rawValue === 'number' ? rawValue : parseInt(rawValue, 10);

        if (isNaN(value)) {
          var defaultValue = FlipMovePropConverter.defaultProps[prop];

          if (nodeEnv !== 'production') {
            (0, _errorMessages.invalidTypeForTimingProp)({
              prop: prop,
              value: rawValue,
              defaultValue: defaultValue
            });
          }

          return defaultValue;
        }

        return value;
      }

      // eslint-disable-next-line class-methods-use-this

    }, {
      key: 'convertAnimationProp',
      value: function convertAnimationProp(animation, presets) {
        switch (typeof animation === 'undefined' ? 'undefined' : _typeof(animation)) {
          case 'boolean':
            {
              // If it's true, we want to use the default preset.
              // If it's false, we want to use the 'none' preset.
              return presets[animation ? _enterLeavePresets.defaultPreset : _enterLeavePresets.disablePreset];
            }

          case 'string':
            {
              var presetKeys = Object.keys(presets);

              if (presetKeys.indexOf(animation) === -1) {
                if (nodeEnv !== 'production') {
                  (0, _errorMessages.invalidEnterLeavePreset)({
                    value: animation,
                    acceptableValues: presetKeys.join(', '),
                    defaultValue: _enterLeavePresets.defaultPreset
                  });
                }

                return presets[_enterLeavePresets.defaultPreset];
              }

              return presets[animation];
            }

          default:
            {
              return animation;
            }
        }
      }
    }, {
      key: 'render',
      value: function render() {
        return _react2.default.createElement(ComposedComponent, this.convertProps(this.props));
      }
    }]);

    return FlipMovePropConverter;
  }(_react.Component), _class.defaultProps = {
    easing: 'ease-in-out',
    duration: 350,
    delay: 0,
    staggerDurationBy: 0,
    staggerDelayBy: 0,
    typeName: 'div',
    enterAnimation: _enterLeavePresets.defaultPreset,
    leaveAnimation: _enterLeavePresets.defaultPreset,
    disableAllAnimations: false,
    getPosition: function getPosition(node) {
      return node.getBoundingClientRect();
    },
    maintainContainerHeight: false,
    verticalAlignment: 'top'
  }, _temp;
}

exports.default = propConverter;
module.exports = exports['default'];
/* WEBPACK VAR INJECTION */}.call(exports, __webpack_require__(68)))

/***/ }),
/* 132 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";


Object.defineProperty(exports, "__esModule", {
  value: true
});


function warnOnce(msg) {
  var hasWarned = false;
  return function () {
    if (!hasWarned) {
      console.warn(msg);
      hasWarned = true;
    }
  };
}
var statelessFunctionalComponentSupplied = exports.statelessFunctionalComponentSupplied = warnOnce('\n>> Error, via react-flip-move <<\n\nYou provided a stateless functional component as a child to <FlipMove>. Unfortunately, SFCs aren\'t supported, because Flip Move needs access to the backing instances via refs, and SFCs don\'t have a public instance that holds that info.\n\nPlease wrap your components in a native element (eg. <div>), or a non-functional component.\n');

var invalidTypeForTimingProp = exports.invalidTypeForTimingProp = function invalidTypeForTimingProp(args) {
  return console.error('\n>> Error, via react-flip-move <<\n\nThe prop you provided for \'' + args.prop + '\' is invalid. It needs to be a positive integer, or a string that can be resolved to a number. The value you provided is \'' + args.value + '\'.\n\nAs a result,  the default value for this parameter will be used, which is \'' + args.defaultValue + '\'.\n');
};

var deprecatedDisableAnimations = exports.deprecatedDisableAnimations = warnOnce('\n>> Warning, via react-flip-move <<\n\nThe \'disableAnimations\' prop you provided is deprecated. Please switch to use \'disableAllAnimations\'.\n\nThis will become a silent error in future versions of react-flip-move.\n');

var invalidEnterLeavePreset = exports.invalidEnterLeavePreset = function invalidEnterLeavePreset(args) {
  return console.error('\n>> Error, via react-flip-move <<\n\nThe enter/leave preset you provided is invalid. We don\'t currently have a \'' + args.value + ' preset.\'\n\nAcceptable values are ' + args.acceptableValues + '. The default value of \'' + args.defaultValue + '\' will be used.\n');
};

/***/ }),
/* 133 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";


Object.defineProperty(exports, "__esModule", {
  value: true
});
var enterPresets = exports.enterPresets = {
  elevator: {
    from: { transform: 'scale(0)', opacity: '0' },
    to: { transform: '', opacity: '' }
  },
  fade: {
    from: { opacity: '0' },
    to: { opacity: '' }
  },
  accordionVertical: {
    from: { transform: 'scaleY(0)', transformOrigin: 'center top' },
    to: { transform: '', transformOrigin: 'center top' }
  },
  accordionHorizontal: {
    from: { transform: 'scaleX(0)', transformOrigin: 'left center' },
    to: { transform: '', transformOrigin: 'left center' }
  },
  none: null
};
/**
 * React Flip Move | enterLeavePresets
 * (c) 2016-present Joshua Comeau
 *
 * This contains the master list of presets available for enter/leave animations,
 * along with the mapping between preset and styles.
 */
var leavePresets = exports.leavePresets = {
  elevator: {
    from: { transform: 'scale(1)', opacity: '1' },
    to: { transform: 'scale(0)', opacity: '0' }
  },
  fade: {
    from: { opacity: '1' },
    to: { opacity: '0' }
  },
  accordionVertical: {
    from: { transform: 'scaleY(1)', transformOrigin: 'center top' },
    to: { transform: 'scaleY(0)', transformOrigin: 'center top' }
  },
  accordionHorizontal: {
    from: { transform: 'scaleX(1)', transformOrigin: 'left center' },
    to: { transform: 'scaleX(0)', transformOrigin: 'left center' }
  },
  none: null
};

// For now, appearPresets will be identical to enterPresets.
// Assigning a custom export in case we ever want to add appear-specific ones.
var appearPresets = exports.appearPresets = enterPresets;

// Embarrassingly enough, v2.0 launched with typo'ed preset names.
// To avoid penning a new major version over something so inconsequential,
// we're supporting both spellings. In a future version, these alternatives
// may be deprecated.
// $FlowFixMe
enterPresets.accordianVertical = enterPresets.accordionVertical;
// $FlowFixMe
enterPresets.accordianHorizontal = enterPresets.accordionHorizontal;
// $FlowFixMe
leavePresets.accordianVertical = leavePresets.accordionVertical;
// $FlowFixMe
leavePresets.accordianHorizontal = leavePresets.accordionHorizontal;

var defaultPreset = exports.defaultPreset = 'elevator';
var disablePreset = exports.disablePreset = 'none';

/***/ }),
/* 134 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";


Object.defineProperty(exports, "__esModule", {
  value: true
});
exports.createTransitionString = exports.getNativeNode = exports.updateHeightPlaceholder = exports.removeNodeFromDOMFlow = exports.getPositionDelta = exports.getRelativeBoundingBox = undefined;

var _extends = Object.assign || function (target) { for (var i = 1; i < arguments.length; i++) { var source = arguments[i]; for (var key in source) { if (Object.prototype.hasOwnProperty.call(source, key)) { target[key] = source[key]; } } } return target; };
/**
 * React Flip Move
 * (c) 2016-present Joshua Comeau
 *
 * These methods read from and write to the DOM.
 * They almost always have side effects, and will hopefully become the
 * only spot in the codebase with impure functions.
 */


exports.applyStylesToDOMNode = applyStylesToDOMNode;
exports.whichTransitionEvent = whichTransitionEvent;

var _reactDom = __webpack_require__(135);

var _helpers = __webpack_require__(43);

function _defineProperty(obj, key, value) { if (key in obj) { Object.defineProperty(obj, key, { value: value, enumerable: true, configurable: true, writable: true }); } else { obj[key] = value; } return obj; }

function applyStylesToDOMNode(_ref) {
  var domNode = _ref.domNode,
      styles = _ref.styles;

  // Can't just do an object merge because domNode.styles is no regular object.
  // Need to do it this way for the engine to fire its `set` listeners.
  Object.keys(styles).forEach(function (key) {
    domNode.style.setProperty((0, _helpers.hyphenate)(key), styles[key]);
  });
}

// Modified from Modernizr
function whichTransitionEvent() {
  var transitions = {
    transition: 'transitionend',
    '-o-transition': 'oTransitionEnd',
    '-moz-transition': 'transitionend',
    '-webkit-transition': 'webkitTransitionEnd'
  };

  // If we're running in a browserless environment (eg. SSR), it doesn't apply.
  // Return a placeholder string, for consistent type return.
  if (typeof document === 'undefined') return '';

  var el = document.createElement('fakeelement');

  var match = Object.keys(transitions).find(function (t) {
    return el.style.getPropertyValue(t) !== undefined;
  });

  // If no `transition` is found, we must be running in a browser so ancient,
  // React itself won't run. Return an empty string, for consistent type return
  return match ? transitions[match] : '';
}

var getRelativeBoundingBox = exports.getRelativeBoundingBox = function getRelativeBoundingBox(_ref2) {
  var childDomNode = _ref2.childDomNode,
      parentDomNode = _ref2.parentDomNode,
      getPosition = _ref2.getPosition;

  var parentBox = getPosition(parentDomNode);

  var _getPosition = getPosition(childDomNode),
      top = _getPosition.top,
      left = _getPosition.left,
      right = _getPosition.right,
      bottom = _getPosition.bottom,
      width = _getPosition.width,
      height = _getPosition.height;

  return {
    top: top - parentBox.top,
    left: left - parentBox.left,
    right: parentBox.right - right,
    bottom: parentBox.bottom - bottom,
    width: width,
    height: height
  };
};

/** getPositionDelta
 * This method returns the delta between two bounding boxes, to figure out
 * how many pixels on each axis the element has moved.
 *
 */
var getPositionDelta = exports.getPositionDelta = function getPositionDelta(_ref3) {
  var childDomNode = _ref3.childDomNode,
      childBoundingBox = _ref3.childBoundingBox,
      parentBoundingBox = _ref3.parentBoundingBox,
      getPosition = _ref3.getPosition;

  // TEMP: A mystery bug is sometimes causing unnecessary boundingBoxes to
  var defaultBox = { top: 0, left: 0, right: 0, bottom: 0, height: 0, width: 0 };

  // Our old box is its last calculated position, derived on mount or at the
  // start of the previous animation.
  var oldRelativeBox = childBoundingBox || defaultBox;
  var parentBox = parentBoundingBox || defaultBox;

  // Our new box is the new final resting place: Where we expect it to wind up
  // after the animation. First we get the box in absolute terms (AKA relative
  // to the viewport), and then we calculate its relative box (relative to the
  // parent container)
  var newAbsoluteBox = getPosition(childDomNode);
  var newRelativeBox = {
    top: newAbsoluteBox.top - parentBox.top,
    left: newAbsoluteBox.left - parentBox.left
  };

  return [oldRelativeBox.left - newRelativeBox.left, oldRelativeBox.top - newRelativeBox.top];
};

/** removeNodeFromDOMFlow
 * This method does something very sneaky: it removes a DOM node from the
 * document flow, but without actually changing its on-screen position.
 *
 * It works by calculating where the node is, and then applying styles
 * so that it winds up being positioned absolutely, but in exactly the
 * same place.
 *
 * This is a vital part of the FLIP technique.
 */
var removeNodeFromDOMFlow = exports.removeNodeFromDOMFlow = function removeNodeFromDOMFlow(childData, verticalAlignment) {
  var domNode = childData.domNode,
      boundingBox = childData.boundingBox;


  if (!domNode || !boundingBox) {
    return;
  }

  // For this to work, we have to offset any given `margin`.
  var computed = window.getComputedStyle(domNode);

  // We need to clean up margins, by converting and removing suffix:
  // eg. '21px' -> 21
  var marginAttrs = ['margin-top', 'margin-left', 'margin-right'];
  var margins = marginAttrs.reduce(function (acc, margin) {
    var propertyVal = computed.getPropertyValue(margin);

    return _extends({}, acc, _defineProperty({}, margin, Number(propertyVal.replace('px', ''))));
  }, {});

  // If we're bottom-aligned, we need to add the height of the child to its
  // top offset. This is because, when the container is bottom-aligned, its
  // height shrinks from the top, not the bottom. We're removing this node
  // from the flow, so the top is going to drop by its height.
  var topOffset = verticalAlignment === 'bottom' ? boundingBox.top - boundingBox.height : boundingBox.top;

  var styles = {
    position: 'absolute',
    top: topOffset - margins['margin-top'] + 'px',
    left: boundingBox.left - margins['margin-left'] + 'px',
    right: boundingBox.right - margins['margin-right'] + 'px'
  };

  applyStylesToDOMNode({ domNode: domNode, styles: styles });
};

/** updateHeightPlaceholder
 * An optional property to FlipMove is a `maintainContainerHeight` boolean.
 * This property creates a node that fills space, so that the parent
 * container doesn't collapse when its children are removed from the
 * document flow.
 */
var updateHeightPlaceholder = exports.updateHeightPlaceholder = function updateHeightPlaceholder(_ref4) {
  var domNode = _ref4.domNode,
      parentData = _ref4.parentData,
      getPosition = _ref4.getPosition;

  var parentDomNode = parentData.domNode;
  var parentBoundingBox = parentData.boundingBox;

  if (!parentDomNode || !parentBoundingBox) {
    return;
  }

  // We need to find the height of the container *without* the placeholder.
  // Since it's possible that the placeholder might already be present,
  // we first set its height to 0.
  // This allows the container to collapse down to the size of just its
  // content (plus container padding or borders if any).
  applyStylesToDOMNode({ domNode: domNode, styles: { height: '0' } });

  // Find the distance by which the container would be collapsed by elements
  // leaving. We compare the freshly-available parent height with the original,
  // cached container height.
  var originalParentHeight = parentBoundingBox.height;
  var collapsedParentHeight = getPosition(parentDomNode).height;
  var reductionInHeight = originalParentHeight - collapsedParentHeight;

  // If the container has become shorter, update the padding element's
  // height to take up the difference. Otherwise set its height to zero,
  // so that it has no effect.
  var styles = {
    height: reductionInHeight > 0 ? reductionInHeight + 'px' : '0'
  };

  applyStylesToDOMNode({ domNode: domNode, styles: styles });
};

var getNativeNode = exports.getNativeNode = function getNativeNode(element) {
  // When running in a windowless environment, abort!
  if (typeof HTMLElement === 'undefined') {
    return null;
  }

  // `element` may already be a native node.
  if (element instanceof HTMLElement) {
    return element;
  }

  // While ReactDOM's `findDOMNode` is discouraged, it's the only
  // publicly-exposed way to find the underlying DOM node for
  // composite components.
  var foundNode = (0, _reactDom.findDOMNode)(element);

  if (!(foundNode instanceof HTMLElement)) {
    // Text nodes are not supported
    return null;
  }

  return foundNode;
};

var createTransitionString = exports.createTransitionString = function createTransitionString(index, props) {
  var delay = props.delay,
      duration = props.duration;
  var staggerDurationBy = props.staggerDurationBy,
      staggerDelayBy = props.staggerDelayBy,
      easing = props.easing;


  delay += index * staggerDelayBy;
  duration += index * staggerDurationBy;

  var cssProperties = ['transform', 'opacity'];

  return cssProperties.map(function (prop) {
    return prop + ' ' + duration + 'ms ' + easing + ' ' + delay + 'ms';
  }).join(', ');
};

/***/ }),
/* 135 */
/***/ (function(module, exports) {

module.exports = require("react-dom");

/***/ }),
/* 136 */
/***/ (function(module, exports, __webpack_require__) {

var __WEBPACK_AMD_DEFINE_FACTORY__, __WEBPACK_AMD_DEFINE_ARRAY__, __WEBPACK_AMD_DEFINE_RESULT__;/*!
	Autosize 3.0.21
	license: MIT
	http://www.jacklmoore.com/autosize
*/
(function (global, factory) {
	if (true) {
		!(__WEBPACK_AMD_DEFINE_ARRAY__ = [exports, module], __WEBPACK_AMD_DEFINE_FACTORY__ = (factory),
				__WEBPACK_AMD_DEFINE_RESULT__ = (typeof __WEBPACK_AMD_DEFINE_FACTORY__ === 'function' ?
				(__WEBPACK_AMD_DEFINE_FACTORY__.apply(exports, __WEBPACK_AMD_DEFINE_ARRAY__)) : __WEBPACK_AMD_DEFINE_FACTORY__),
				__WEBPACK_AMD_DEFINE_RESULT__ !== undefined && (module.exports = __WEBPACK_AMD_DEFINE_RESULT__));
	} else if (typeof exports !== 'undefined' && typeof module !== 'undefined') {
		factory(exports, module);
	} else {
		var mod = {
			exports: {}
		};
		factory(mod.exports, mod);
		global.autosize = mod.exports;
	}
})(this, function (exports, module) {
	'use strict';

	var map = typeof Map === "function" ? new Map() : (function () {
		var keys = [];
		var values = [];

		return {
			has: function has(key) {
				return keys.indexOf(key) > -1;
			},
			get: function get(key) {
				return values[keys.indexOf(key)];
			},
			set: function set(key, value) {
				if (keys.indexOf(key) === -1) {
					keys.push(key);
					values.push(value);
				}
			},
			'delete': function _delete(key) {
				var index = keys.indexOf(key);
				if (index > -1) {
					keys.splice(index, 1);
					values.splice(index, 1);
				}
			}
		};
	})();

	var createEvent = function createEvent(name) {
		return new Event(name, { bubbles: true });
	};
	try {
		new Event('test');
	} catch (e) {
		// IE does not support `new Event()`
		createEvent = function (name) {
			var evt = document.createEvent('Event');
			evt.initEvent(name, true, false);
			return evt;
		};
	}

	function assign(ta) {
		if (!ta || !ta.nodeName || ta.nodeName !== 'TEXTAREA' || map.has(ta)) return;

		var heightOffset = null;
		var clientWidth = ta.clientWidth;
		var cachedHeight = null;

		function init() {
			var style = window.getComputedStyle(ta, null);

			if (style.resize === 'vertical') {
				ta.style.resize = 'none';
			} else if (style.resize === 'both') {
				ta.style.resize = 'horizontal';
			}

			if (style.boxSizing === 'content-box') {
				heightOffset = -(parseFloat(style.paddingTop) + parseFloat(style.paddingBottom));
			} else {
				heightOffset = parseFloat(style.borderTopWidth) + parseFloat(style.borderBottomWidth);
			}
			// Fix when a textarea is not on document body and heightOffset is Not a Number
			if (isNaN(heightOffset)) {
				heightOffset = 0;
			}

			update();
		}

		function changeOverflow(value) {
			{
				// Chrome/Safari-specific fix:
				// When the textarea y-overflow is hidden, Chrome/Safari do not reflow the text to account for the space
				// made available by removing the scrollbar. The following forces the necessary text reflow.
				var width = ta.style.width;
				ta.style.width = '0px';
				// Force reflow:
				/* jshint ignore:start */
				ta.offsetWidth;
				/* jshint ignore:end */
				ta.style.width = width;
			}

			ta.style.overflowY = value;
		}

		function getParentOverflows(el) {
			var arr = [];

			while (el && el.parentNode && el.parentNode instanceof Element) {
				if (el.parentNode.scrollTop) {
					arr.push({
						node: el.parentNode,
						scrollTop: el.parentNode.scrollTop
					});
				}
				el = el.parentNode;
			}

			return arr;
		}

		function resize() {
			var originalHeight = ta.style.height;
			var overflows = getParentOverflows(ta);
			var docTop = document.documentElement && document.documentElement.scrollTop; // Needed for Mobile IE (ticket #240)

			ta.style.height = 'auto';

			var endHeight = ta.scrollHeight + heightOffset;

			if (ta.scrollHeight === 0) {
				// If the scrollHeight is 0, then the element probably has display:none or is detached from the DOM.
				ta.style.height = originalHeight;
				return;
			}

			ta.style.height = endHeight + 'px';

			// used to check if an update is actually necessary on window.resize
			clientWidth = ta.clientWidth;

			// prevents scroll-position jumping
			overflows.forEach(function (el) {
				el.node.scrollTop = el.scrollTop;
			});

			if (docTop) {
				document.documentElement.scrollTop = docTop;
			}
		}

		function update() {
			resize();

			var styleHeight = Math.round(parseFloat(ta.style.height));
			var computed = window.getComputedStyle(ta, null);

			// Using offsetHeight as a replacement for computed.height in IE, because IE does not account use of border-box
			var actualHeight = computed.boxSizing === 'content-box' ? Math.round(parseFloat(computed.height)) : ta.offsetHeight;

			// The actual height not matching the style height (set via the resize method) indicates that
			// the max-height has been exceeded, in which case the overflow should be allowed.
			if (actualHeight !== styleHeight) {
				if (computed.overflowY === 'hidden') {
					changeOverflow('scroll');
					resize();
					actualHeight = computed.boxSizing === 'content-box' ? Math.round(parseFloat(window.getComputedStyle(ta, null).height)) : ta.offsetHeight;
				}
			} else {
				// Normally keep overflow set to hidden, to avoid flash of scrollbar as the textarea expands.
				if (computed.overflowY !== 'hidden') {
					changeOverflow('hidden');
					resize();
					actualHeight = computed.boxSizing === 'content-box' ? Math.round(parseFloat(window.getComputedStyle(ta, null).height)) : ta.offsetHeight;
				}
			}

			if (cachedHeight !== actualHeight) {
				cachedHeight = actualHeight;
				var evt = createEvent('autosize:resized');
				try {
					ta.dispatchEvent(evt);
				} catch (err) {
					// Firefox will throw an error on dispatchEvent for a detached element
					// https://bugzilla.mozilla.org/show_bug.cgi?id=889376
				}
			}
		}

		var pageResize = function pageResize() {
			if (ta.clientWidth !== clientWidth) {
				update();
			}
		};

		var destroy = (function (style) {
			window.removeEventListener('resize', pageResize, false);
			ta.removeEventListener('input', update, false);
			ta.removeEventListener('keyup', update, false);
			ta.removeEventListener('autosize:destroy', destroy, false);
			ta.removeEventListener('autosize:update', update, false);

			Object.keys(style).forEach(function (key) {
				ta.style[key] = style[key];
			});

			map['delete'](ta);
		}).bind(ta, {
			height: ta.style.height,
			resize: ta.style.resize,
			overflowY: ta.style.overflowY,
			overflowX: ta.style.overflowX,
			wordWrap: ta.style.wordWrap
		});

		ta.addEventListener('autosize:destroy', destroy, false);

		// IE9 does not fire onpropertychange or oninput for deletions,
		// so binding to onkeyup to catch most of those events.
		// There is no way that I know of to detect something like 'cut' in IE9.
		if ('onpropertychange' in ta && 'oninput' in ta) {
			ta.addEventListener('keyup', update, false);
		}

		window.addEventListener('resize', pageResize, false);
		ta.addEventListener('input', update, false);
		ta.addEventListener('autosize:update', update, false);
		ta.style.overflowX = 'hidden';
		ta.style.wordWrap = 'break-word';

		map.set(ta, {
			destroy: destroy,
			update: update
		});

		init();
	}

	function destroy(ta) {
		var methods = map.get(ta);
		if (methods) {
			methods.destroy();
		}
	}

	function update(ta) {
		var methods = map.get(ta);
		if (methods) {
			methods.update();
		}
	}

	var autosize = null;

	// Do nothing in Node.js environment and IE8 (or lower)
	if (typeof window === 'undefined' || typeof window.getComputedStyle !== 'function') {
		autosize = function (el) {
			return el;
		};
		autosize.destroy = function (el) {
			return el;
		};
		autosize.update = function (el) {
			return el;
		};
	} else {
		autosize = function (el, options) {
			if (el) {
				Array.prototype.forEach.call(el.length ? el : [el], function (x) {
					return assign(x, options);
				});
			}
			return el;
		};
		autosize.destroy = function (el) {
			if (el) {
				Array.prototype.forEach.call(el.length ? el : [el], destroy);
			}
			return el;
		};
		autosize.update = function (el) {
			if (el) {
				Array.prototype.forEach.call(el.length ? el : [el], update);
			}
			return el;
		};
	}

	module.exports = autosize;
});

/***/ }),
/* 137 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";


Object.defineProperty(exports, "__esModule", {
  value: true
});

exports.default = function (language) {
  return new _polyglot2.default({
    phrases: i18nMap[language] || i18nMap.en,
    locale: language
  });
};

var _polyglot = __webpack_require__(138);

var _polyglot2 = _interopRequireDefault(_polyglot);

var _zhCN = __webpack_require__(139);

var _zhCN2 = _interopRequireDefault(_zhCN);

var _zhTW = __webpack_require__(140);

var _zhTW2 = _interopRequireDefault(_zhTW);

var _en = __webpack_require__(141);

var _en2 = _interopRequireDefault(_en);

var _esES = __webpack_require__(142);

var _esES2 = _interopRequireDefault(_esES);

var _fr = __webpack_require__(143);

var _fr2 = _interopRequireDefault(_fr);

var _ru = __webpack_require__(144);

var _ru2 = _interopRequireDefault(_ru);

var _de = __webpack_require__(145);

var _de2 = _interopRequireDefault(_de);

var _pl = __webpack_require__(146);

var _pl2 = _interopRequireDefault(_pl);

var _ko = __webpack_require__(147);

var _ko2 = _interopRequireDefault(_ko);

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

var i18nMap = {
  'zh': _zhCN2.default,
  'zh-CN': _zhCN2.default,
  'zh-TW': _zhTW2.default,
  'en': _en2.default,
  'es-ES': _esES2.default,
  'fr': _fr2.default,
  'ru': _ru2.default,
  'de': _de2.default,
  'pl': _pl2.default,
  'ko': _ko2.default
};

/***/ }),
/* 138 */
/***/ (function(module, exports, __webpack_require__) {

var __WEBPACK_AMD_DEFINE_ARRAY__, __WEBPACK_AMD_DEFINE_RESULT__;//     (c) 2012 Airbnb, Inc.
//
//     polyglot.js may be freely distributed under the terms of the BSD
//     license. For all licensing information, details, and documention:
//     http://airbnb.github.com/polyglot.js
//
//
// Polyglot.js is an I18n helper library written in JavaScript, made to
// work both in the browser and in Node. It provides a simple solution for
// interpolation and pluralization, based off of Airbnb's
// experience adding I18n functionality to its Backbone.js and Node apps.
//
// Polylglot is agnostic to your translation backend. It doesn't perform any
// translation; it simply gives you a way to manage translated phrases from
// your client- or server-side JavaScript application.
//


(function(root, factory) {
  if (true) {
    !(__WEBPACK_AMD_DEFINE_ARRAY__ = [], __WEBPACK_AMD_DEFINE_RESULT__ = function() {
      return factory(root);
    }.apply(exports, __WEBPACK_AMD_DEFINE_ARRAY__),
				__WEBPACK_AMD_DEFINE_RESULT__ !== undefined && (module.exports = __WEBPACK_AMD_DEFINE_RESULT__));
  } else if (typeof exports === 'object') {
    module.exports = factory(root);
  } else {
    root.Polyglot = factory(root);
  }
}(this, function(root) {
  'use strict';

  // ### Polyglot class constructor
  function Polyglot(options) {
    options = options || {};
    this.phrases = {};
    this.extend(options.phrases || {});
    this.currentLocale = options.locale || 'en';
    this.allowMissing = !!options.allowMissing;
    this.warn = options.warn || warn;
  }

  // ### Version
  Polyglot.VERSION = '0.4.3';

  // ### polyglot.locale([locale])
  //
  // Get or set locale. Internally, Polyglot only uses locale for pluralization.
  Polyglot.prototype.locale = function(newLocale) {
    if (newLocale) this.currentLocale = newLocale;
    return this.currentLocale;
  };

  // ### polyglot.extend(phrases)
  //
  // Use `extend` to tell Polyglot how to translate a given key.
  //
  //     polyglot.extend({
  //       "hello": "Hello",
  //       "hello_name": "Hello, %{name}"
  //     });
  //
  // The key can be any string.  Feel free to call `extend` multiple times;
  // it will override any phrases with the same key, but leave existing phrases
  // untouched.
  //
  // It is also possible to pass nested phrase objects, which get flattened
  // into an object with the nested keys concatenated using dot notation.
  //
  //     polyglot.extend({
  //       "nav": {
  //         "hello": "Hello",
  //         "hello_name": "Hello, %{name}",
  //         "sidebar": {
  //           "welcome": "Welcome"
  //         }
  //       }
  //     });
  //
  //     console.log(polyglot.phrases);
  //     // {
  //     //   'nav.hello': 'Hello',
  //     //   'nav.hello_name': 'Hello, %{name}',
  //     //   'nav.sidebar.welcome': 'Welcome'
  //     // }
  //
  // `extend` accepts an optional second argument, `prefix`, which can be used
  // to prefix every key in the phrases object with some string, using dot
  // notation.
  //
  //     polyglot.extend({
  //       "hello": "Hello",
  //       "hello_name": "Hello, %{name}"
  //     }, "nav");
  //
  //     console.log(polyglot.phrases);
  //     // {
  //     //   'nav.hello': 'Hello',
  //     //   'nav.hello_name': 'Hello, %{name}'
  //     // }
  //
  // This feature is used internally to support nested phrase objects.
  Polyglot.prototype.extend = function(morePhrases, prefix) {
    var phrase;

    for (var key in morePhrases) {
      if (morePhrases.hasOwnProperty(key)) {
        phrase = morePhrases[key];
        if (prefix) key = prefix + '.' + key;
        if (typeof phrase === 'object') {
          this.extend(phrase, key);
        } else {
          this.phrases[key] = phrase;
        }
      }
    }
  };

  // ### polyglot.clear()
  //
  // Clears all phrases. Useful for special cases, such as freeing
  // up memory if you have lots of phrases but no longer need to
  // perform any translation. Also used internally by `replace`.
  Polyglot.prototype.clear = function() {
    this.phrases = {};
  };

  // ### polyglot.replace(phrases)
  //
  // Completely replace the existing phrases with a new set of phrases.
  // Normally, just use `extend` to add more phrases, but under certain
  // circumstances, you may want to make sure no old phrases are lying around.
  Polyglot.prototype.replace = function(newPhrases) {
    this.clear();
    this.extend(newPhrases);
  };


  // ### polyglot.t(key, options)
  //
  // The most-used method. Provide a key, and `t` will return the
  // phrase.
  //
  //     polyglot.t("hello");
  //     => "Hello"
  //
  // The phrase value is provided first by a call to `polyglot.extend()` or
  // `polyglot.replace()`.
  //
  // Pass in an object as the second argument to perform interpolation.
  //
  //     polyglot.t("hello_name", {name: "Spike"});
  //     => "Hello, Spike"
  //
  // If you like, you can provide a default value in case the phrase is missing.
  // Use the special option key "_" to specify a default.
  //
  //     polyglot.t("i_like_to_write_in_language", {
  //       _: "I like to write in %{language}.",
  //       language: "JavaScript"
  //     });
  //     => "I like to write in JavaScript."
  //
  Polyglot.prototype.t = function(key, options) {
    var phrase, result;
    options = options == null ? {} : options;
    // allow number as a pluralization shortcut
    if (typeof options === 'number') {
      options = {smart_count: options};
    }
    if (typeof this.phrases[key] === 'string') {
      phrase = this.phrases[key];
    } else if (typeof options._ === 'string') {
      phrase = options._;
    } else if (this.allowMissing) {
      phrase = key;
    } else {
      this.warn('Missing translation for key: "'+key+'"');
      result = key;
    }
    if (typeof phrase === 'string') {
      options = clone(options);
      result = choosePluralForm(phrase, this.currentLocale, options.smart_count);
      result = interpolate(result, options);
    }
    return result;
  };


  // ### polyglot.has(key)
  //
  // Check if polyglot has a translation for given key
  Polyglot.prototype.has = function(key) {
    return key in this.phrases;
  };


  // #### Pluralization methods
  // The string that separates the different phrase possibilities.
  var delimeter = '||||';

  // Mapping from pluralization group plural logic.
  var pluralTypes = {
    chinese:   function(n) { return 0; },
    german:    function(n) { return n !== 1 ? 1 : 0; },
    french:    function(n) { return n > 1 ? 1 : 0; },
    russian:   function(n) { return n % 10 === 1 && n % 100 !== 11 ? 0 : n % 10 >= 2 && n % 10 <= 4 && (n % 100 < 10 || n % 100 >= 20) ? 1 : 2; },
    czech:     function(n) { return (n === 1) ? 0 : (n >= 2 && n <= 4) ? 1 : 2; },
    polish:    function(n) { return (n === 1 ? 0 : n % 10 >= 2 && n % 10 <= 4 && (n % 100 < 10 || n % 100 >= 20) ? 1 : 2); },
    icelandic: function(n) { return (n % 10 !== 1 || n % 100 === 11) ? 1 : 0; }
  };

  // Mapping from pluralization group to individual locales.
  var pluralTypeToLanguages = {
    chinese:   ['fa', 'id', 'ja', 'ko', 'lo', 'ms', 'th', 'tr', 'zh'],
    german:    ['da', 'de', 'en', 'es', 'fi', 'el', 'he', 'hu', 'it', 'nl', 'no', 'pt', 'sv'],
    french:    ['fr', 'tl', 'pt-br'],
    russian:   ['hr', 'ru'],
    czech:     ['cs'],
    polish:    ['pl'],
    icelandic: ['is']
  };

  function langToTypeMap(mapping) {
    var type, langs, l, ret = {};
    for (type in mapping) {
      if (mapping.hasOwnProperty(type)) {
        langs = mapping[type];
        for (l in langs) {
          ret[langs[l]] = type;
        }
      }
    }
    return ret;
  }

  // Trim a string.
  function trim(str){
    var trimRe = /^\s+|\s+$/g;
    return str.replace(trimRe, '');
  }

  // Based on a phrase text that contains `n` plural forms separated
  // by `delimeter`, a `locale`, and a `count`, choose the correct
  // plural form, or none if `count` is `null`.
  function choosePluralForm(text, locale, count){
    var ret, texts, chosenText;
    if (count != null && text) {
      texts = text.split(delimeter);
      chosenText = texts[pluralTypeIndex(locale, count)] || texts[0];
      ret = trim(chosenText);
    } else {
      ret = text;
    }
    return ret;
  }

  function pluralTypeName(locale) {
    var langToPluralType = langToTypeMap(pluralTypeToLanguages);
    return langToPluralType[locale] || langToPluralType.en;
  }

  function pluralTypeIndex(locale, count) {
    return pluralTypes[pluralTypeName(locale)](count);
  }

  // ### interpolate
  //
  // Does the dirty work. Creates a `RegExp` object for each
  // interpolation placeholder.
  function interpolate(phrase, options) {
    for (var arg in options) {
      if (arg !== '_' && options.hasOwnProperty(arg)) {
        // We create a new `RegExp` each time instead of using a more-efficient
        // string replace so that the same argument can be replaced multiple times
        // in the same phrase.
        phrase = phrase.replace(new RegExp('%\\{'+arg+'\\}', 'g'), options[arg]);
      }
    }
    return phrase;
  }

  // ### warn
  //
  // Provides a warning in the console if a phrase key is missing.
  function warn(message) {
    root.console && root.console.warn && root.console.warn('WARNING: ' + message);
  }

  // ### clone
  //
  // Clone an object.
  function clone(source) {
    var ret = {};
    for (var prop in source) {
      ret[prop] = source[prop];
    }
    return ret;
  }

  return Polyglot;
}));


/***/ }),
/* 139 */
/***/ (function(module, exports) {

module.exports = {"init":"Gitalk 加载中 ...","no-found-related":"未找到相关的 %{link} 进行评论","please-contact":"请联系 %{user} 初始化创建","init-issue":"初始化 Issue","leave-a-comment":"我们鼓励在讨论区讨论有意义的内容及关于文章的勘误，无意义的讨论将会被管理员删除","preview":"预览","edit":"编辑","comment":"评论","support-markdown":"支持 Markdown 语法","login-with-github":"使用 GitHub 登录","first-comment-person":"来做第一个留言的人吧！","commented":"发表于","load-more":"加载更多","counts":"%{counts} 条评论","sort-asc":"从旧到新排序","sort-desc":"从新到旧排序","logout":"注销","anonymous":"未登录用户"}

/***/ }),
/* 140 */
/***/ (function(module, exports) {

module.exports = {"init":"Gitalk 載入中…","no-found-related":"未找到相關的 %{link}","please-contact":"請聯絡 %{user} 初始化評論","init-issue":"初始化 Issue","leave-a-comment":"我們鼓勵在討論區討論有意義的內容及關於文章的勘誤，無意義的討論將會被管理員刪除","preview":"預覽","edit":"編輯","comment":"評論","support-markdown":"支援 Markdown 語法","login-with-github":"使用 GitHub 登入","first-comment-person":"成為首個留言的人吧！","commented":"評論於","load-more":"載入更多","counts":"%{counts} 筆評論","sort-asc":"從舊至新排序","sort-desc":"從新至舊排序","logout":"登出","anonymous":"訪客"}

/***/ }),
/* 141 */
/***/ (function(module, exports) {

module.exports = {"init":"Gitalking ...","no-found-related":"Related %{link} not found","please-contact":"Please contact %{user} to initialize the comment","init-issue":"Init Issue","leave-a-comment":"Leave a comment","preview":"Preview","edit":"Edit","comment":"Comment","support-markdown":"Markdown is supported","login-with-github":"Login with GitHub","first-comment-person":"Be the first person to leave a comment!","commented":"commented","load-more":"Load more","counts":"%{counts} comment |||| %{counts} comments","sort-asc":"Sort by Oldest","sort-desc":"Sort by Latest","logout":"Logout","anonymous":"Anonymous"}

/***/ }),
/* 142 */
/***/ (function(module, exports) {

module.exports = {"init":"Gitalking ...","no-found-related":"Link %{link} no encontrado","please-contact":"Por favor contacta con %{user} para inicializar el comentario","init-issue":"Iniciar Issue","leave-a-comment":"Deja un comentario","preview":"Avance","edit":"Editar","comment":"Comentario","support-markdown":"Markdown es soportado","login-with-github":"Entrar con GitHub","first-comment-person":"Sé el primero en dejar un comentario!","commented":"comentó","load-more":"Cargar más","counts":"%{counts} comentario |||| %{counts} comentarios","sort-asc":"Ordenar por Antiguos","sort-desc":"Ordenar por Recientes","logout":"Salir","anonymous":"Anónimo"}

/***/ }),
/* 143 */
/***/ (function(module, exports) {

module.exports = {"init":"Gitalking ...","no-found-related":"Lien %{link} non trouvé","please-contact":"S’il vous plaît contactez %{user} pour initialiser les commentaires","init-issue":"Initialisation des issues","leave-a-comment":"Laisser un commentaire","preview":"Aperçu","edit":"Modifier","comment":"Commentaire","support-markdown":"Markdown est supporté","login-with-github":"Se connecter avec GitHub","first-comment-person":"Être le premier à laisser un commentaire !","commented":"commenter","load-more":"Charger plus","counts":"%{counts} commentaire |||| %{counts} commentaires","sort-asc":"Trier par plus ancien","sort-desc":"Trier par plus récent","logout":"Déconnexion","anonymous":"Anonyme"}

/***/ }),
/* 144 */
/***/ (function(module, exports) {

module.exports = {"init":"Gitalking ...","no-found-related":"Связанные %{link} не найдены","please-contact":"Пожалуйста, свяжитесь с %{user} чтобы инициализировать комментарий","init-issue":"Выпуск инициализации","leave-a-comment":"Оставить комментарий","preview":"Предварительный просмотр","edit":"Pедактировать","comment":"Комментарий","support-markdown":"Поддерживается Markdown","login-with-github":"Вход через GitHub","first-comment-person":"Будьте первым, кто оставил комментарий","commented":"прокомментированный","load-more":"Загрузить ещё","counts":"%{counts} комментарий |||| %{counts} комментариев","sort-asc":"Сортировать по старым","sort-desc":"Сортировать по последним","logout":"Выход","anonymous":"Анонимный"}

/***/ }),
/* 145 */
/***/ (function(module, exports) {

module.exports = {"init":"Gitalking ...","no-found-related":"Zugehöriger %{link} nicht gefunden","please-contact":"Bitte kontaktiere %{user} um den Kommentar zu initialisieren","init-issue":"Initialisiere Issue","leave-a-comment":"Hinterlasse einen Kommentar","preview":"Vorschau","edit":"Editieren","comment":"Kommentieren","support-markdown":"Markdown wird unterstützt","login-with-github":"Mit GitHub-Account anmelden","first-comment-person":"Sei die erste Person, welche einen Kommentar hinterlässt!","commented":"kommentierte","load-more":"Zeige mehr","counts":"%{counts} Kommentar |||| %{counts} Kommentare","sort-asc":"Älteste zuerst","sort-desc":"Neuste zuerst","logout":"Abmelden","anonymous":"Anonym"}

/***/ }),
/* 146 */
/***/ (function(module, exports) {

module.exports = {"init":"Gitalking ...","no-found-related":"Nie znaleziono powiązanego zgłoszenia: %{link}","please-contact":"Skontaktuj się z %{user}, aby umożliwić komentowanie","init-issue":"Utwórz zgłoszenie (GitHub Issue)","leave-a-comment":"Skomentuj","preview":"Podgląd","edit":"Edytuj","comment":"Wyślij","support-markdown":"Możesz użyć składni Markdown","login-with-github":"Zaloguj się poprzez GitHub","first-comment-person":"Skomentuj jako pierwszy!","commented":"skomentowany","load-more":"Załaduj więcej","counts":"%{counts} komentarz |||| %{counts} komentarze |||| %{counts} komentarzy","sort-asc":"Sortuj od najstarszych","sort-desc":"Sortuj od najnowszych","logout":"Wyloguj","anonymous":"Anonimowy"}

/***/ }),
/* 147 */
/***/ (function(module, exports) {

module.exports = {"init":"초기화 중 ...","no-found-related":"관련 링크를 찾을 수 없습니다: %{link} ","please-contact":"초기화를 위해 %{user} 에게 연락해 주세요","init-issue":"이슈 초기화","leave-a-comment":"댓글을 남겨보세요","preview":"미리보기","edit":"수정하기","comment":"댓글 달기","support-markdown":"마크다운(Markdown) 문법 지원","login-with-github":"GitHub로 로그인하기","first-comment-person":"첫 번째로 댓글을 남겨보세요!","commented":"님이 작성함","load-more":"더 보기","counts":"댓글 %{counts} 개","sort-asc":"오래된 댓글 먼저","sort-desc":"최신 댓글 먼저","logout":"로그아웃","anonymous":"익명"}

/***/ }),
/* 148 */
/***/ (function(module, exports) {

// removed by extract-text-webpack-plugin

/***/ }),
/* 149 */
/***/ (function(module, exports, __webpack_require__) {

module.exports = { "default": __webpack_require__(150), __esModule: true };

/***/ }),
/* 150 */
/***/ (function(module, exports, __webpack_require__) {

__webpack_require__(151);
module.exports = __webpack_require__(0).Object.keys;


/***/ }),
/* 151 */
/***/ (function(module, exports, __webpack_require__) {

// 19.1.2.14 Object.keys(O)
var toObject = __webpack_require__(16);
var $keys = __webpack_require__(21);

__webpack_require__(60)('keys', function () {
  return function keys(it) {
    return $keys(toObject(it));
  };
});


/***/ }),
/* 152 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";


exports.__esModule = true;

var _isIterable2 = __webpack_require__(153);

var _isIterable3 = _interopRequireDefault(_isIterable2);

var _getIterator2 = __webpack_require__(156);

var _getIterator3 = _interopRequireDefault(_getIterator2);

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

exports.default = function () {
  function sliceIterator(arr, i) {
    var _arr = [];
    var _n = true;
    var _d = false;
    var _e = undefined;

    try {
      for (var _i = (0, _getIterator3.default)(arr), _s; !(_n = (_s = _i.next()).done); _n = true) {
        _arr.push(_s.value);

        if (i && _arr.length === i) break;
      }
    } catch (err) {
      _d = true;
      _e = err;
    } finally {
      try {
        if (!_n && _i["return"]) _i["return"]();
      } finally {
        if (_d) throw _e;
      }
    }

    return _arr;
  }

  return function (arr, i) {
    if (Array.isArray(arr)) {
      return arr;
    } else if ((0, _isIterable3.default)(Object(arr))) {
      return sliceIterator(arr, i);
    } else {
      throw new TypeError("Invalid attempt to destructure non-iterable instance");
    }
  };
}();

/***/ }),
/* 153 */
/***/ (function(module, exports, __webpack_require__) {

module.exports = { "default": __webpack_require__(154), __esModule: true };

/***/ }),
/* 154 */
/***/ (function(module, exports, __webpack_require__) {

__webpack_require__(26);
__webpack_require__(18);
module.exports = __webpack_require__(155);


/***/ }),
/* 155 */
/***/ (function(module, exports, __webpack_require__) {

var classof = __webpack_require__(37);
var ITERATOR = __webpack_require__(2)('iterator');
var Iterators = __webpack_require__(14);
module.exports = __webpack_require__(0).isIterable = function (it) {
  var O = Object(it);
  return O[ITERATOR] !== undefined
    || '@@iterator' in O
    // eslint-disable-next-line no-prototype-builtins
    || Iterators.hasOwnProperty(classof(O));
};


/***/ }),
/* 156 */
/***/ (function(module, exports, __webpack_require__) {

module.exports = { "default": __webpack_require__(157), __esModule: true };

/***/ }),
/* 157 */
/***/ (function(module, exports, __webpack_require__) {

__webpack_require__(26);
__webpack_require__(18);
module.exports = __webpack_require__(158);


/***/ }),
/* 158 */
/***/ (function(module, exports, __webpack_require__) {

var anObject = __webpack_require__(5);
var get = __webpack_require__(38);
module.exports = __webpack_require__(0).getIterator = function (it) {
  var iterFn = get(it);
  if (typeof iterFn != 'function') throw TypeError(it + ' is not iterable!');
  return anObject(iterFn.call(it));
};


/***/ }),
/* 159 */
/***/ (function(module, exports, __webpack_require__) {

module.exports = __webpack_require__(160);

/***/ }),
/* 160 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";


var utils = __webpack_require__(3);
var bind = __webpack_require__(70);
var Axios = __webpack_require__(161);
var mergeConfig = __webpack_require__(76);
var defaults = __webpack_require__(73);

/**
 * Create an instance of Axios
 *
 * @param {Object} defaultConfig The default config for the instance
 * @return {Axios} A new instance of Axios
 */
function createInstance(defaultConfig) {
  var context = new Axios(defaultConfig);
  var instance = bind(Axios.prototype.request, context);

  // Copy axios.prototype to instance
  utils.extend(instance, Axios.prototype, context);

  // Copy context to instance
  utils.extend(instance, context);

  return instance;
}

// Create the default instance to be exported
var axios = createInstance(defaults);

// Expose Axios class to allow class inheritance
axios.Axios = Axios;

// Factory for creating new instances
axios.create = function create(instanceConfig) {
  return createInstance(mergeConfig(axios.defaults, instanceConfig));
};

// Expose Cancel & CancelToken
axios.Cancel = __webpack_require__(77);
axios.CancelToken = __webpack_require__(174);
axios.isCancel = __webpack_require__(72);

// Expose all/spread
axios.all = function all(promises) {
  return Promise.all(promises);
};
axios.spread = __webpack_require__(175);

module.exports = axios;

// Allow use of default import syntax in TypeScript
module.exports.default = axios;


/***/ }),
/* 161 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";


var utils = __webpack_require__(3);
var buildURL = __webpack_require__(71);
var InterceptorManager = __webpack_require__(162);
var dispatchRequest = __webpack_require__(163);
var mergeConfig = __webpack_require__(76);

/**
 * Create a new instance of Axios
 *
 * @param {Object} instanceConfig The default config for the instance
 */
function Axios(instanceConfig) {
  this.defaults = instanceConfig;
  this.interceptors = {
    request: new InterceptorManager(),
    response: new InterceptorManager()
  };
}

/**
 * Dispatch a request
 *
 * @param {Object} config The config specific for this request (merged with this.defaults)
 */
Axios.prototype.request = function request(config) {
  /*eslint no-param-reassign:0*/
  // Allow for axios('example/url'[, config]) a la fetch API
  if (typeof config === 'string') {
    config = arguments[1] || {};
    config.url = arguments[0];
  } else {
    config = config || {};
  }

  config = mergeConfig(this.defaults, config);

  // Set config.method
  if (config.method) {
    config.method = config.method.toLowerCase();
  } else if (this.defaults.method) {
    config.method = this.defaults.method.toLowerCase();
  } else {
    config.method = 'get';
  }

  // Hook up interceptors middleware
  var chain = [dispatchRequest, undefined];
  var promise = Promise.resolve(config);

  this.interceptors.request.forEach(function unshiftRequestInterceptors(interceptor) {
    chain.unshift(interceptor.fulfilled, interceptor.rejected);
  });

  this.interceptors.response.forEach(function pushResponseInterceptors(interceptor) {
    chain.push(interceptor.fulfilled, interceptor.rejected);
  });

  while (chain.length) {
    promise = promise.then(chain.shift(), chain.shift());
  }

  return promise;
};

Axios.prototype.getUri = function getUri(config) {
  config = mergeConfig(this.defaults, config);
  return buildURL(config.url, config.params, config.paramsSerializer).replace(/^\?/, '');
};

// Provide aliases for supported request methods
utils.forEach(['delete', 'get', 'head', 'options'], function forEachMethodNoData(method) {
  /*eslint func-names:0*/
  Axios.prototype[method] = function(url, config) {
    return this.request(utils.merge(config || {}, {
      method: method,
      url: url
    }));
  };
});

utils.forEach(['post', 'put', 'patch'], function forEachMethodWithData(method) {
  /*eslint func-names:0*/
  Axios.prototype[method] = function(url, data, config) {
    return this.request(utils.merge(config || {}, {
      method: method,
      url: url,
      data: data
    }));
  };
});

module.exports = Axios;


/***/ }),
/* 162 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";


var utils = __webpack_require__(3);

function InterceptorManager() {
  this.handlers = [];
}

/**
 * Add a new interceptor to the stack
 *
 * @param {Function} fulfilled The function to handle `then` for a `Promise`
 * @param {Function} rejected The function to handle `reject` for a `Promise`
 *
 * @return {Number} An ID used to remove interceptor later
 */
InterceptorManager.prototype.use = function use(fulfilled, rejected) {
  this.handlers.push({
    fulfilled: fulfilled,
    rejected: rejected
  });
  return this.handlers.length - 1;
};

/**
 * Remove an interceptor from the stack
 *
 * @param {Number} id The ID that was returned by `use`
 */
InterceptorManager.prototype.eject = function eject(id) {
  if (this.handlers[id]) {
    this.handlers[id] = null;
  }
};

/**
 * Iterate over all the registered interceptors
 *
 * This method is particularly useful for skipping over any
 * interceptors that may have become `null` calling `eject`.
 *
 * @param {Function} fn The function to call for each interceptor
 */
InterceptorManager.prototype.forEach = function forEach(fn) {
  utils.forEach(this.handlers, function forEachHandler(h) {
    if (h !== null) {
      fn(h);
    }
  });
};

module.exports = InterceptorManager;


/***/ }),
/* 163 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";


var utils = __webpack_require__(3);
var transformData = __webpack_require__(164);
var isCancel = __webpack_require__(72);
var defaults = __webpack_require__(73);

/**
 * Throws a `Cancel` if cancellation has been requested.
 */
function throwIfCancellationRequested(config) {
  if (config.cancelToken) {
    config.cancelToken.throwIfRequested();
  }
}

/**
 * Dispatch a request to the server using the configured adapter.
 *
 * @param {object} config The config that is to be used for the request
 * @returns {Promise} The Promise to be fulfilled
 */
module.exports = function dispatchRequest(config) {
  throwIfCancellationRequested(config);

  // Ensure headers exist
  config.headers = config.headers || {};

  // Transform request data
  config.data = transformData(
    config.data,
    config.headers,
    config.transformRequest
  );

  // Flatten headers
  config.headers = utils.merge(
    config.headers.common || {},
    config.headers[config.method] || {},
    config.headers
  );

  utils.forEach(
    ['delete', 'get', 'head', 'post', 'put', 'patch', 'common'],
    function cleanHeaderConfig(method) {
      delete config.headers[method];
    }
  );

  var adapter = config.adapter || defaults.adapter;

  return adapter(config).then(function onAdapterResolution(response) {
    throwIfCancellationRequested(config);

    // Transform response data
    response.data = transformData(
      response.data,
      response.headers,
      config.transformResponse
    );

    return response;
  }, function onAdapterRejection(reason) {
    if (!isCancel(reason)) {
      throwIfCancellationRequested(config);

      // Transform response data
      if (reason && reason.response) {
        reason.response.data = transformData(
          reason.response.data,
          reason.response.headers,
          config.transformResponse
        );
      }
    }

    return Promise.reject(reason);
  });
};


/***/ }),
/* 164 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";


var utils = __webpack_require__(3);

/**
 * Transform the data for a request or a response
 *
 * @param {Object|String} data The data to be transformed
 * @param {Array} headers The headers for the request or response
 * @param {Array|Function} fns A single function or Array of functions
 * @returns {*} The resulting transformed data
 */
module.exports = function transformData(data, headers, fns) {
  /*eslint no-param-reassign:0*/
  utils.forEach(fns, function transform(fn) {
    data = fn(data, headers);
  });

  return data;
};


/***/ }),
/* 165 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";


var utils = __webpack_require__(3);

module.exports = function normalizeHeaderName(headers, normalizedName) {
  utils.forEach(headers, function processHeader(value, name) {
    if (name !== normalizedName && name.toUpperCase() === normalizedName.toUpperCase()) {
      headers[normalizedName] = value;
      delete headers[name];
    }
  });
};


/***/ }),
/* 166 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";


var createError = __webpack_require__(75);

/**
 * Resolve or reject a Promise based on response status.
 *
 * @param {Function} resolve A function that resolves the promise.
 * @param {Function} reject A function that rejects the promise.
 * @param {object} response The response.
 */
module.exports = function settle(resolve, reject, response) {
  var validateStatus = response.config.validateStatus;
  if (!validateStatus || validateStatus(response.status)) {
    resolve(response);
  } else {
    reject(createError(
      'Request failed with status code ' + response.status,
      response.config,
      null,
      response.request,
      response
    ));
  }
};


/***/ }),
/* 167 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";


/**
 * Update an Error with the specified config, error code, and response.
 *
 * @param {Error} error The error to update.
 * @param {Object} config The config.
 * @param {string} [code] The error code (for example, 'ECONNABORTED').
 * @param {Object} [request] The request.
 * @param {Object} [response] The response.
 * @returns {Error} The error.
 */
module.exports = function enhanceError(error, config, code, request, response) {
  error.config = config;
  if (code) {
    error.code = code;
  }

  error.request = request;
  error.response = response;
  error.isAxiosError = true;

  error.toJSON = function() {
    return {
      // Standard
      message: this.message,
      name: this.name,
      // Microsoft
      description: this.description,
      number: this.number,
      // Mozilla
      fileName: this.fileName,
      lineNumber: this.lineNumber,
      columnNumber: this.columnNumber,
      stack: this.stack,
      // Axios
      config: this.config,
      code: this.code
    };
  };
  return error;
};


/***/ }),
/* 168 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";


var isAbsoluteURL = __webpack_require__(169);
var combineURLs = __webpack_require__(170);

/**
 * Creates a new URL by combining the baseURL with the requestedURL,
 * only when the requestedURL is not already an absolute URL.
 * If the requestURL is absolute, this function returns the requestedURL untouched.
 *
 * @param {string} baseURL The base URL
 * @param {string} requestedURL Absolute or relative URL to combine
 * @returns {string} The combined full path
 */
module.exports = function buildFullPath(baseURL, requestedURL) {
  if (baseURL && !isAbsoluteURL(requestedURL)) {
    return combineURLs(baseURL, requestedURL);
  }
  return requestedURL;
};


/***/ }),
/* 169 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";


/**
 * Determines whether the specified URL is absolute
 *
 * @param {string} url The URL to test
 * @returns {boolean} True if the specified URL is absolute, otherwise false
 */
module.exports = function isAbsoluteURL(url) {
  // A URL is considered absolute if it begins with "<scheme>://" or "//" (protocol-relative URL).
  // RFC 3986 defines scheme name as a sequence of characters beginning with a letter and followed
  // by any combination of letters, digits, plus, period, or hyphen.
  return /^([a-z][a-z\d\+\-\.]*:)?\/\//i.test(url);
};


/***/ }),
/* 170 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";


/**
 * Creates a new URL by combining the specified URLs
 *
 * @param {string} baseURL The base URL
 * @param {string} relativeURL The relative URL
 * @returns {string} The combined URL
 */
module.exports = function combineURLs(baseURL, relativeURL) {
  return relativeURL
    ? baseURL.replace(/\/+$/, '') + '/' + relativeURL.replace(/^\/+/, '')
    : baseURL;
};


/***/ }),
/* 171 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";


var utils = __webpack_require__(3);

// Headers whose duplicates are ignored by node
// c.f. https://nodejs.org/api/http.html#http_message_headers
var ignoreDuplicateOf = [
  'age', 'authorization', 'content-length', 'content-type', 'etag',
  'expires', 'from', 'host', 'if-modified-since', 'if-unmodified-since',
  'last-modified', 'location', 'max-forwards', 'proxy-authorization',
  'referer', 'retry-after', 'user-agent'
];

/**
 * Parse headers into an object
 *
 * ```
 * Date: Wed, 27 Aug 2014 08:58:49 GMT
 * Content-Type: application/json
 * Connection: keep-alive
 * Transfer-Encoding: chunked
 * ```
 *
 * @param {String} headers Headers needing to be parsed
 * @returns {Object} Headers parsed into an object
 */
module.exports = function parseHeaders(headers) {
  var parsed = {};
  var key;
  var val;
  var i;

  if (!headers) { return parsed; }

  utils.forEach(headers.split('\n'), function parser(line) {
    i = line.indexOf(':');
    key = utils.trim(line.substr(0, i)).toLowerCase();
    val = utils.trim(line.substr(i + 1));

    if (key) {
      if (parsed[key] && ignoreDuplicateOf.indexOf(key) >= 0) {
        return;
      }
      if (key === 'set-cookie') {
        parsed[key] = (parsed[key] ? parsed[key] : []).concat([val]);
      } else {
        parsed[key] = parsed[key] ? parsed[key] + ', ' + val : val;
      }
    }
  });

  return parsed;
};


/***/ }),
/* 172 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";


var utils = __webpack_require__(3);

module.exports = (
  utils.isStandardBrowserEnv() ?

  // Standard browser envs have full support of the APIs needed to test
  // whether the request URL is of the same origin as current location.
    (function standardBrowserEnv() {
      var msie = /(msie|trident)/i.test(navigator.userAgent);
      var urlParsingNode = document.createElement('a');
      var originURL;

      /**
    * Parse a URL to discover it's components
    *
    * @param {String} url The URL to be parsed
    * @returns {Object}
    */
      function resolveURL(url) {
        var href = url;

        if (msie) {
        // IE needs attribute set twice to normalize properties
          urlParsingNode.setAttribute('href', href);
          href = urlParsingNode.href;
        }

        urlParsingNode.setAttribute('href', href);

        // urlParsingNode provides the UrlUtils interface - http://url.spec.whatwg.org/#urlutils
        return {
          href: urlParsingNode.href,
          protocol: urlParsingNode.protocol ? urlParsingNode.protocol.replace(/:$/, '') : '',
          host: urlParsingNode.host,
          search: urlParsingNode.search ? urlParsingNode.search.replace(/^\?/, '') : '',
          hash: urlParsingNode.hash ? urlParsingNode.hash.replace(/^#/, '') : '',
          hostname: urlParsingNode.hostname,
          port: urlParsingNode.port,
          pathname: (urlParsingNode.pathname.charAt(0) === '/') ?
            urlParsingNode.pathname :
            '/' + urlParsingNode.pathname
        };
      }

      originURL = resolveURL(window.location.href);

      /**
    * Determine if a URL shares the same origin as the current location
    *
    * @param {String} requestURL The URL to test
    * @returns {boolean} True if URL shares the same origin, otherwise false
    */
      return function isURLSameOrigin(requestURL) {
        var parsed = (utils.isString(requestURL)) ? resolveURL(requestURL) : requestURL;
        return (parsed.protocol === originURL.protocol &&
            parsed.host === originURL.host);
      };
    })() :

  // Non standard browser envs (web workers, react-native) lack needed support.
    (function nonStandardBrowserEnv() {
      return function isURLSameOrigin() {
        return true;
      };
    })()
);


/***/ }),
/* 173 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";


var utils = __webpack_require__(3);

module.exports = (
  utils.isStandardBrowserEnv() ?

  // Standard browser envs support document.cookie
    (function standardBrowserEnv() {
      return {
        write: function write(name, value, expires, path, domain, secure) {
          var cookie = [];
          cookie.push(name + '=' + encodeURIComponent(value));

          if (utils.isNumber(expires)) {
            cookie.push('expires=' + new Date(expires).toGMTString());
          }

          if (utils.isString(path)) {
            cookie.push('path=' + path);
          }

          if (utils.isString(domain)) {
            cookie.push('domain=' + domain);
          }

          if (secure === true) {
            cookie.push('secure');
          }

          document.cookie = cookie.join('; ');
        },

        read: function read(name) {
          var match = document.cookie.match(new RegExp('(^|;\\s*)(' + name + ')=([^;]*)'));
          return (match ? decodeURIComponent(match[3]) : null);
        },

        remove: function remove(name) {
          this.write(name, '', Date.now() - 86400000);
        }
      };
    })() :

  // Non standard browser env (web workers, react-native) lack needed support.
    (function nonStandardBrowserEnv() {
      return {
        write: function write() {},
        read: function read() { return null; },
        remove: function remove() {}
      };
    })()
);


/***/ }),
/* 174 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";


var Cancel = __webpack_require__(77);

/**
 * A `CancelToken` is an object that can be used to request cancellation of an operation.
 *
 * @class
 * @param {Function} executor The executor function.
 */
function CancelToken(executor) {
  if (typeof executor !== 'function') {
    throw new TypeError('executor must be a function.');
  }

  var resolvePromise;
  this.promise = new Promise(function promiseExecutor(resolve) {
    resolvePromise = resolve;
  });

  var token = this;
  executor(function cancel(message) {
    if (token.reason) {
      // Cancellation has already been requested
      return;
    }

    token.reason = new Cancel(message);
    resolvePromise(token.reason);
  });
}

/**
 * Throws a `Cancel` if cancellation has been requested.
 */
CancelToken.prototype.throwIfRequested = function throwIfRequested() {
  if (this.reason) {
    throw this.reason;
  }
};

/**
 * Returns an object that contains a new `CancelToken` and a function that, when called,
 * cancels the `CancelToken`.
 */
CancelToken.source = function source() {
  var cancel;
  var token = new CancelToken(function executor(c) {
    cancel = c;
  });
  return {
    token: token,
    cancel: cancel
  };
};

module.exports = CancelToken;


/***/ }),
/* 175 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";


/**
 * Syntactic sugar for invoking a function and expanding an array for arguments.
 *
 * Common use case would be to use `Function.prototype.apply`.
 *
 *  ```js
 *  function f(x, y, z) {}
 *  var args = [1, 2, 3];
 *  f.apply(null, args);
 *  ```
 *
 * With `spread` this example can be re-written.
 *
 *  ```js
 *  spread(function(x, y, z) {})([1, 2, 3]);
 *  ```
 *
 * @param {Function} callback
 * @returns {Function}
 */
module.exports = function spread(callback) {
  return function wrap(arr) {
    return callback.apply(null, arr);
  };
};


/***/ }),
/* 176 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";


Object.defineProperty(exports, "__esModule", {
  value: true
});

var _react = __webpack_require__(9);

var _react2 = _interopRequireDefault(_react);

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

exports.default = function (_ref) {
  var className = _ref.className,
      getRef = _ref.getRef,
      onClick = _ref.onClick,
      onMouseDown = _ref.onMouseDown,
      text = _ref.text,
      isLoading = _ref.isLoading;
  return _react2.default.createElement(
    "button",
    {
      ref: function ref(el) {
        return getRef && getRef(el);
      },
      className: "gt-btn " + className,
      onClick: onClick,
      onMouseDown: onMouseDown },
    _react2.default.createElement(
      "span",
      { className: "gt-btn-text" },
      text
    ),
    isLoading && _react2.default.createElement("span", { className: "gt-btn-loading gt-spinner" })
  );
};

/***/ }),
/* 177 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";


Object.defineProperty(exports, "__esModule", {
  value: true
});

var _react = __webpack_require__(9);

var _react2 = _interopRequireDefault(_react);

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

exports.default = function (_ref) {
  var className = _ref.className,
      onClick = _ref.onClick,
      text = _ref.text;
  return _react2.default.createElement(
    "a",
    { className: "gt-action " + className, onClick: onClick },
    _react2.default.createElement(
      "span",
      { className: "gt-action-text" },
      text
    )
  );
};

/***/ }),
/* 178 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";


Object.defineProperty(exports, "__esModule", {
  value: true
});

var _getPrototypeOf = __webpack_require__(59);

var _getPrototypeOf2 = _interopRequireDefault(_getPrototypeOf);

var _classCallCheck2 = __webpack_require__(61);

var _classCallCheck3 = _interopRequireDefault(_classCallCheck2);

var _createClass2 = __webpack_require__(62);

var _createClass3 = _interopRequireDefault(_createClass2);

var _possibleConstructorReturn2 = __webpack_require__(63);

var _possibleConstructorReturn3 = _interopRequireDefault(_possibleConstructorReturn2);

var _inherits2 = __webpack_require__(67);

var _inherits3 = _interopRequireDefault(_inherits2);

var _react = __webpack_require__(9);

var _react2 = _interopRequireDefault(_react);

var _avatar = __webpack_require__(78);

var _avatar2 = _interopRequireDefault(_avatar);

var _svg = __webpack_require__(79);

var _svg2 = _interopRequireDefault(_svg);

var _distance_in_words_to_now = __webpack_require__(187);

var _distance_in_words_to_now2 = _interopRequireDefault(_distance_in_words_to_now);

var _index = __webpack_require__(200);

var _index2 = _interopRequireDefault(_index);

var _index3 = __webpack_require__(201);

var _index4 = _interopRequireDefault(_index3);

var _index5 = __webpack_require__(202);

var _index6 = _interopRequireDefault(_index5);

var _index7 = __webpack_require__(203);

var _index8 = _interopRequireDefault(_index7);

var _index9 = __webpack_require__(204);

var _index10 = _interopRequireDefault(_index9);

var _index11 = __webpack_require__(205);

var _index12 = _interopRequireDefault(_index11);

__webpack_require__(206);

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

var ZHCN = (0, _index2.default)();
var ZHTW = (0, _index4.default)();
var ES = (0, _index6.default)();
var FR = (0, _index8.default)();
var RU = (0, _index10.default)();
var PL = (0, _index12.default)();

if (typeof window !== 'undefined') {
  window.GT_i18n_distanceInWordsLocaleMap = {
    zh: ZHCN,
    'zh-CN': ZHCN,
    'zh-TW': ZHTW,
    'es-ES': ES,
    fr: FR,
    ru: RU,
    pl: PL
  };
}

var Comment = function (_Component) {
  (0, _inherits3.default)(Comment, _Component);

  function Comment() {
    (0, _classCallCheck3.default)(this, Comment);
    return (0, _possibleConstructorReturn3.default)(this, (Comment.__proto__ || (0, _getPrototypeOf2.default)(Comment)).apply(this, arguments));
  }

  (0, _createClass3.default)(Comment, [{
    key: 'shouldComponentUpdate',
    value: function shouldComponentUpdate() {
      return false;
    }
  }, {
    key: 'componentDidMount',
    value: function componentDidMount() {
      var comment = this.node;
      var emailResponse = comment.querySelector('.email-hidden-toggle>a');
      if (emailResponse) {
        emailResponse.addEventListener('click', function (e) {
          e.preventDefault();
          comment.querySelector('.email-hidden-reply').classList.toggle('expanded');
        }, true);
      }
    }
  }, {
    key: 'render',
    value: function render() {
      var _this2 = this;

      var _props = this.props,
          comment = _props.comment,
          user = _props.user,
          language = _props.language,
          _props$commentedText = _props.commentedText,
          commentedText = _props$commentedText === undefined ? '' : _props$commentedText,
          _props$admin = _props.admin,
          admin = _props$admin === undefined ? [] : _props$admin,
          replyCallback = _props.replyCallback,
          likeCallback = _props.likeCallback;

      var enableEdit = user && comment.user.login === user.login;
      var isAdmin = ~[].concat(admin).map(function (a) {
        return a.toLowerCase();
      }).indexOf(comment.user.login.toLowerCase());
      var reactions = comment.reactions;

      var reactionTotalCount = '';
      if (reactions && reactions.totalCount) {
        reactionTotalCount = reactions.totalCount;
        if (reactions.totalCount === 100 && reactions.pageInfo && reactions.pageInfo.hasNextPage) {
          reactionTotalCount = '100+';
        }
      }

      return _react2.default.createElement(
        'div',
        { ref: function ref(node) {
            _this2.node = node;
          }, className: 'gt-comment ' + (isAdmin ? 'gt-comment-admin' : '') },
        _react2.default.createElement(_avatar2.default, {
          className: 'gt-comment-avatar',
          src: comment.user && comment.user.avatar_url,
          alt: comment.user && comment.user.login
        }),
        _react2.default.createElement(
          'div',
          { className: 'gt-comment-content' },
          _react2.default.createElement(
            'div',
            { className: 'gt-comment-header' },
            _react2.default.createElement('div', { className: 'gt-comment-block-' + (user ? '2' : '1') }),
            _react2.default.createElement(
              'a',
              {
                className: 'gt-comment-username',
                href: comment.user && comment.user.html_url
              },
              comment.user && comment.user.login
            ),
            _react2.default.createElement(
              'span',
              { className: 'gt-comment-text' },
              commentedText
            ),
            _react2.default.createElement(
              'span',
              { className: 'gt-comment-date' },
              (0, _distance_in_words_to_now2.default)(comment.created_at, {
                addSuffix: true,
                locale: {
                  distanceInWords: window.GT_i18n_distanceInWordsLocaleMap[language]
                }
              })
            ),
            reactions && _react2.default.createElement(
              'a',
              { className: 'gt-comment-like', title: 'Like', onClick: likeCallback },
              reactions.viewerHasReacted ? _react2.default.createElement(_svg2.default, {
                className: 'gt-ico-heart',
                name: 'heart_on',
                text: reactionTotalCount
              }) : _react2.default.createElement(_svg2.default, {
                className: 'gt-ico-heart',
                name: 'heart',
                text: reactionTotalCount
              })
            ),
            enableEdit ? _react2.default.createElement(
              'a',
              {
                href: comment.html_url,
                className: 'gt-comment-edit',
                title: 'Edit',
                target: '_blank'
              },
              _react2.default.createElement(_svg2.default, { className: 'gt-ico-edit', name: 'edit' })
            ) : _react2.default.createElement(
              'a',
              { className: 'gt-comment-reply', title: 'Reply', onClick: replyCallback },
              _react2.default.createElement(_svg2.default, { className: 'gt-ico-reply', name: 'reply' })
            )
          ),
          _react2.default.createElement('div', {
            className: 'gt-comment-body markdown-body',
            dangerouslySetInnerHTML: {
              __html: comment.body_html
            }
          })
        )
      );
    }
  }]);
  return Comment;
}(_react.Component);

exports.default = Comment;

/***/ }),
/* 179 */
/***/ (function(module, exports, __webpack_require__) {

var map = {
	"./arrow_down.svg": 180,
	"./edit.svg": 181,
	"./github.svg": 182,
	"./heart.svg": 183,
	"./heart_on.svg": 184,
	"./reply.svg": 185,
	"./tip.svg": 186
};
function webpackContext(req) {
	return __webpack_require__(webpackContextResolve(req));
};
function webpackContextResolve(req) {
	var id = map[req];
	if(!(id + 1)) // check for number or string
		throw new Error("Cannot find module '" + req + "'.");
	return id;
};
webpackContext.keys = function webpackContextKeys() {
	return Object.keys(map);
};
webpackContext.resolve = webpackContextResolve;
module.exports = webpackContext;
webpackContext.id = 179;

/***/ }),
/* 180 */
/***/ (function(module, exports) {

module.exports = "<svg viewBox=\"0 0 1024 1024\" xmlns=\"http://www.w3.org/2000/svg\" p-id=\"1619\"><path d=\"M511.872 676.8c-0.003 0-0.006 0-0.008 0-9.137 0-17.379-3.829-23.21-9.97l-251.277-265.614c-5.415-5.72-8.743-13.464-8.744-21.984 0-17.678 14.33-32.008 32.008-32.008 9.157 0 17.416 3.845 23.25 10.009l228.045 241.103 228.224-241.088c5.855-6.165 14.113-10.001 23.266-10.001 8.516 0 16.256 3.32 21.998 8.736 12.784 12.145 13.36 32.434 1.264 45.233l-251.52 265.6c-5.844 6.155-14.086 9.984-23.223 9.984-0.025 0-0.051 0-0.076 0z\" p-id=\"1620\"></path></svg>"

/***/ }),
/* 181 */
/***/ (function(module, exports) {

module.exports = "<svg viewBox=\"0 0 1024 1024\" xmlns=\"http://www.w3.org/2000/svg\">\r\n  <path d=\"M785.333333 85.333333C774.666667 85.333333 763.2 90.133333 754.666667 98.666667L682.666667 170.666667 853.333333 341.333333 925.333333 269.333333C942.4 252.266667 942.4 222.133333 925.333333 209.333333L814.666667 98.666667C806.133333 90.133333 796 85.333333 785.333333 85.333333zM640 217.333333 85.333333 768 85.333333 938.666667 256 938.666667 806.666667 384 640 217.333333z\"></path>\r\n</svg>\r\n"

/***/ }),
/* 182 */
/***/ (function(module, exports) {

module.exports = "<svg viewBox=\"0 0 1024 1024\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">\r\n  <path d=\"M64 524C64 719.602 189.356 885.926 364.113 947.017 387.65799 953 384 936.115 384 924.767L384 847.107C248.118 863.007 242.674 773.052 233.5 758.001 215 726.501 171.5 718.501 184.5 703.501 215.5 687.501 247 707.501 283.5 761.501 309.956 800.642 361.366 794.075 387.658 787.497 393.403 763.997 405.637 743.042 422.353 726.638 281.774 701.609 223 615.67 223 513.5 223 464.053 239.322 418.406 271.465 381.627 251.142 320.928 273.421 269.19 276.337 261.415 334.458 256.131 394.888 302.993 399.549 306.685 432.663 297.835 470.341 293 512.5 293 554.924 293 592.81 297.896 626.075 306.853 637.426 298.219 693.46 258.054 747.5 262.966 750.382 270.652 772.185 321.292 753.058 381.083 785.516 417.956 802 463.809 802 513.5 802 615.874 742.99 701.953 601.803 726.786 625.381 750.003 640 782.295 640 818.008L640 930.653C640.752 939.626 640 948.664978 655.086 948.665 832.344 888.962 960 721.389 960 524 960 276.576 759.424 76 512 76 264.577 76 64 276.576 64 524Z\"></path>\r\n</svg>\r\n"

/***/ }),
/* 183 */
/***/ (function(module, exports) {

module.exports = "<svg viewBox=\"0 0 1024 1024\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\r\n  <path d=\"M527.061333 166.528A277.333333 277.333333 0 0 1 1000.618667 362.666667a277.333333 277.333333 0 0 1-81.28 196.138666l-377.173334 377.173334a42.666667 42.666667 0 0 1-60.330666 0l-377.173334-377.173334a277.376 277.376 0 0 1 392.277334-392.277333l15.061333 15.061333 15.061333-15.061333z m286.72 377.173333l45.226667-45.226666a192 192 0 0 0-135.808-327.893334 192 192 0 0 0-135.808 56.32l-45.226667 45.226667a42.666667 42.666667 0 0 1-60.330666 0l-45.226667-45.226667a192.042667 192.042667 0 0 0-271.616 271.573334L512 845.482667l301.781333-301.781334z\"></path>\r\n</svg>\r\n"

/***/ }),
/* 184 */
/***/ (function(module, exports) {

module.exports = "<svg t=\"1512463363724\" viewBox=\"0 0 1024 1024\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\r\n  <path d=\"M527.061333 166.528A277.333333 277.333333 0 0 1 1000.618667 362.666667a277.333333 277.333333 0 0 1-81.28 196.138666l-377.173334 377.173334a42.666667 42.666667 0 0 1-60.330666 0l-377.173334-377.173334a277.376 277.376 0 0 1 392.277334-392.277333l15.061333 15.061333 15.061333-15.061333z\"></path>\r\n</svg>\r\n"

/***/ }),
/* 185 */
/***/ (function(module, exports) {

module.exports = "<svg viewBox=\"0 0 1332 1024\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">\r\n  <path d=\"M529.066665 273.066666 529.066665 0 51.2 477.866666 529.066665 955.733335 529.066665 675.84C870.4 675.84 1109.333335 785.066665 1280 1024 1211.733335 682.666665 1006.933335 341.333334 529.066665 273.066666\"></path>\r\n</svg>\r\n"

/***/ }),
/* 186 */
/***/ (function(module, exports) {

module.exports = "<svg viewBox=\"0 0 1024 1024\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">\r\n  <path d=\"M512 366.949535c-16.065554 0-29.982212 13.405016-29.982212 29.879884l0 359.070251c0 16.167882 13.405016 29.879884 29.982212 29.879884 15.963226 0 29.879884-13.405016 29.879884-29.879884L541.879884 396.829419C541.879884 380.763865 528.474868 366.949535 512 366.949535L512 366.949535z\"\r\n    p-id=\"3083\"></path>\r\n  <path d=\"M482.017788 287.645048c0-7.776956 3.274508-15.553912 8.80024-21.181973 5.525732-5.525732 13.302688-8.80024 21.181973-8.80024 7.776956 0 15.553912 3.274508 21.079644 8.80024 5.525732 5.62806 8.80024 13.405016 8.80024 21.181973 0 7.776956-3.274508 15.656241-8.80024 21.181973-5.525732 5.525732-13.405016 8.697911-21.079644 8.697911-7.879285 0-15.656241-3.274508-21.181973-8.697911C485.292295 303.301289 482.017788 295.524333 482.017788 287.645048L482.017788 287.645048z\"\r\n    p-id=\"3084\"></path>\r\n  <path d=\"M512 946.844409c-239.8577 0-434.895573-195.037873-434.895573-434.895573 0-239.8577 195.037873-434.895573 434.895573-434.895573 239.755371 0 434.895573 195.037873 434.895573 434.895573C946.895573 751.806535 751.755371 946.844409 512 946.844409zM512 126.17088c-212.740682 0-385.880284 173.037274-385.880284 385.777955 0 212.740682 173.037274 385.777955 385.880284 385.777955 212.740682 0 385.777955-173.037274 385.777955-385.777955C897.777955 299.208154 724.740682 126.17088 512 126.17088z\"\r\n    p-id=\"3085\"></path>\r\n</svg>\r\n"

/***/ }),
/* 187 */
/***/ (function(module, exports, __webpack_require__) {

var distanceInWords = __webpack_require__(188)

/**
 * @category Common Helpers
 * @summary Return the distance between the given date and now in words.
 *
 * @description
 * Return the distance between the given date and now in words.
 *
 * | Distance to now                                                   | Result              |
 * |-------------------------------------------------------------------|---------------------|
 * | 0 ... 30 secs                                                     | less than a minute  |
 * | 30 secs ... 1 min 30 secs                                         | 1 minute            |
 * | 1 min 30 secs ... 44 mins 30 secs                                 | [2..44] minutes     |
 * | 44 mins ... 30 secs ... 89 mins 30 secs                           | about 1 hour        |
 * | 89 mins 30 secs ... 23 hrs 59 mins 30 secs                        | about [2..24] hours |
 * | 23 hrs 59 mins 30 secs ... 41 hrs 59 mins 30 secs                 | 1 day               |
 * | 41 hrs 59 mins 30 secs ... 29 days 23 hrs 59 mins 30 secs         | [2..30] days        |
 * | 29 days 23 hrs 59 mins 30 secs ... 44 days 23 hrs 59 mins 30 secs | about 1 month       |
 * | 44 days 23 hrs 59 mins 30 secs ... 59 days 23 hrs 59 mins 30 secs | about 2 months      |
 * | 59 days 23 hrs 59 mins 30 secs ... 1 yr                           | [2..12] months      |
 * | 1 yr ... 1 yr 3 months                                            | about 1 year        |
 * | 1 yr 3 months ... 1 yr 9 month s                                  | over 1 year         |
 * | 1 yr 9 months ... 2 yrs                                           | almost 2 years      |
 * | N yrs ... N yrs 3 months                                          | about N years       |
 * | N yrs 3 months ... N yrs 9 months                                 | over N years        |
 * | N yrs 9 months ... N+1 yrs                                        | almost N+1 years    |
 *
 * With `options.includeSeconds == true`:
 * | Distance to now     | Result               |
 * |---------------------|----------------------|
 * | 0 secs ... 5 secs   | less than 5 seconds  |
 * | 5 secs ... 10 secs  | less than 10 seconds |
 * | 10 secs ... 20 secs | less than 20 seconds |
 * | 20 secs ... 40 secs | half a minute        |
 * | 40 secs ... 60 secs | less than a minute   |
 * | 60 secs ... 90 secs | 1 minute             |
 *
 * @param {Date|String|Number} date - the given date
 * @param {Object} [options] - the object with options
 * @param {Boolean} [options.includeSeconds=false] - distances less than a minute are more detailed
 * @param {Boolean} [options.addSuffix=false] - result specifies if the second date is earlier or later than the first
 * @param {Object} [options.locale=enLocale] - the locale object
 * @returns {String} the distance in words
 *
 * @example
 * // If today is 1 January 2015, what is the distance to 2 July 2014?
 * var result = distanceInWordsToNow(
 *   new Date(2014, 6, 2)
 * )
 * //=> '6 months'
 *
 * @example
 * // If now is 1 January 2015 00:00:00,
 * // what is the distance to 1 January 2015 00:00:15, including seconds?
 * var result = distanceInWordsToNow(
 *   new Date(2015, 0, 1, 0, 0, 15),
 *   {includeSeconds: true}
 * )
 * //=> 'less than 20 seconds'
 *
 * @example
 * // If today is 1 January 2015,
 * // what is the distance to 1 January 2016, with a suffix?
 * var result = distanceInWordsToNow(
 *   new Date(2016, 0, 1),
 *   {addSuffix: true}
 * )
 * //=> 'in about 1 year'
 *
 * @example
 * // If today is 1 January 2015,
 * // what is the distance to 1 August 2016 in Esperanto?
 * var eoLocale = require('date-fns/locale/eo')
 * var result = distanceInWordsToNow(
 *   new Date(2016, 7, 1),
 *   {locale: eoLocale}
 * )
 * //=> 'pli ol 1 jaro'
 */
function distanceInWordsToNow (dirtyDate, dirtyOptions) {
  return distanceInWords(Date.now(), dirtyDate, dirtyOptions)
}

module.exports = distanceInWordsToNow


/***/ }),
/* 188 */
/***/ (function(module, exports, __webpack_require__) {

var compareDesc = __webpack_require__(189)
var parse = __webpack_require__(17)
var differenceInSeconds = __webpack_require__(191)
var differenceInMonths = __webpack_require__(193)
var enLocale = __webpack_require__(196)

var MINUTES_IN_DAY = 1440
var MINUTES_IN_ALMOST_TWO_DAYS = 2520
var MINUTES_IN_MONTH = 43200
var MINUTES_IN_TWO_MONTHS = 86400

/**
 * @category Common Helpers
 * @summary Return the distance between the given dates in words.
 *
 * @description
 * Return the distance between the given dates in words.
 *
 * | Distance between dates                                            | Result              |
 * |-------------------------------------------------------------------|---------------------|
 * | 0 ... 30 secs                                                     | less than a minute  |
 * | 30 secs ... 1 min 30 secs                                         | 1 minute            |
 * | 1 min 30 secs ... 44 mins 30 secs                                 | [2..44] minutes     |
 * | 44 mins ... 30 secs ... 89 mins 30 secs                           | about 1 hour        |
 * | 89 mins 30 secs ... 23 hrs 59 mins 30 secs                        | about [2..24] hours |
 * | 23 hrs 59 mins 30 secs ... 41 hrs 59 mins 30 secs                 | 1 day               |
 * | 41 hrs 59 mins 30 secs ... 29 days 23 hrs 59 mins 30 secs         | [2..30] days        |
 * | 29 days 23 hrs 59 mins 30 secs ... 44 days 23 hrs 59 mins 30 secs | about 1 month       |
 * | 44 days 23 hrs 59 mins 30 secs ... 59 days 23 hrs 59 mins 30 secs | about 2 months      |
 * | 59 days 23 hrs 59 mins 30 secs ... 1 yr                           | [2..12] months      |
 * | 1 yr ... 1 yr 3 months                                            | about 1 year        |
 * | 1 yr 3 months ... 1 yr 9 month s                                  | over 1 year         |
 * | 1 yr 9 months ... 2 yrs                                           | almost 2 years      |
 * | N yrs ... N yrs 3 months                                          | about N years       |
 * | N yrs 3 months ... N yrs 9 months                                 | over N years        |
 * | N yrs 9 months ... N+1 yrs                                        | almost N+1 years    |
 *
 * With `options.includeSeconds == true`:
 * | Distance between dates | Result               |
 * |------------------------|----------------------|
 * | 0 secs ... 5 secs      | less than 5 seconds  |
 * | 5 secs ... 10 secs     | less than 10 seconds |
 * | 10 secs ... 20 secs    | less than 20 seconds |
 * | 20 secs ... 40 secs    | half a minute        |
 * | 40 secs ... 60 secs    | less than a minute   |
 * | 60 secs ... 90 secs    | 1 minute             |
 *
 * @param {Date|String|Number} dateToCompare - the date to compare with
 * @param {Date|String|Number} date - the other date
 * @param {Object} [options] - the object with options
 * @param {Boolean} [options.includeSeconds=false] - distances less than a minute are more detailed
 * @param {Boolean} [options.addSuffix=false] - result indicates if the second date is earlier or later than the first
 * @param {Object} [options.locale=enLocale] - the locale object
 * @returns {String} the distance in words
 *
 * @example
 * // What is the distance between 2 July 2014 and 1 January 2015?
 * var result = distanceInWords(
 *   new Date(2014, 6, 2),
 *   new Date(2015, 0, 1)
 * )
 * //=> '6 months'
 *
 * @example
 * // What is the distance between 1 January 2015 00:00:15
 * // and 1 January 2015 00:00:00, including seconds?
 * var result = distanceInWords(
 *   new Date(2015, 0, 1, 0, 0, 15),
 *   new Date(2015, 0, 1, 0, 0, 0),
 *   {includeSeconds: true}
 * )
 * //=> 'less than 20 seconds'
 *
 * @example
 * // What is the distance from 1 January 2016
 * // to 1 January 2015, with a suffix?
 * var result = distanceInWords(
 *   new Date(2016, 0, 1),
 *   new Date(2015, 0, 1),
 *   {addSuffix: true}
 * )
 * //=> 'about 1 year ago'
 *
 * @example
 * // What is the distance between 1 August 2016 and 1 January 2015 in Esperanto?
 * var eoLocale = require('date-fns/locale/eo')
 * var result = distanceInWords(
 *   new Date(2016, 7, 1),
 *   new Date(2015, 0, 1),
 *   {locale: eoLocale}
 * )
 * //=> 'pli ol 1 jaro'
 */
function distanceInWords (dirtyDateToCompare, dirtyDate, dirtyOptions) {
  var options = dirtyOptions || {}

  var comparison = compareDesc(dirtyDateToCompare, dirtyDate)

  var locale = options.locale
  var localize = enLocale.distanceInWords.localize
  if (locale && locale.distanceInWords && locale.distanceInWords.localize) {
    localize = locale.distanceInWords.localize
  }

  var localizeOptions = {
    addSuffix: Boolean(options.addSuffix),
    comparison: comparison
  }

  var dateLeft, dateRight
  if (comparison > 0) {
    dateLeft = parse(dirtyDateToCompare)
    dateRight = parse(dirtyDate)
  } else {
    dateLeft = parse(dirtyDate)
    dateRight = parse(dirtyDateToCompare)
  }

  var seconds = differenceInSeconds(dateRight, dateLeft)
  var offset = dateRight.getTimezoneOffset() - dateLeft.getTimezoneOffset()
  var minutes = Math.round(seconds / 60) - offset
  var months

  // 0 up to 2 mins
  if (minutes < 2) {
    if (options.includeSeconds) {
      if (seconds < 5) {
        return localize('lessThanXSeconds', 5, localizeOptions)
      } else if (seconds < 10) {
        return localize('lessThanXSeconds', 10, localizeOptions)
      } else if (seconds < 20) {
        return localize('lessThanXSeconds', 20, localizeOptions)
      } else if (seconds < 40) {
        return localize('halfAMinute', null, localizeOptions)
      } else if (seconds < 60) {
        return localize('lessThanXMinutes', 1, localizeOptions)
      } else {
        return localize('xMinutes', 1, localizeOptions)
      }
    } else {
      if (minutes === 0) {
        return localize('lessThanXMinutes', 1, localizeOptions)
      } else {
        return localize('xMinutes', minutes, localizeOptions)
      }
    }

  // 2 mins up to 0.75 hrs
  } else if (minutes < 45) {
    return localize('xMinutes', minutes, localizeOptions)

  // 0.75 hrs up to 1.5 hrs
  } else if (minutes < 90) {
    return localize('aboutXHours', 1, localizeOptions)

  // 1.5 hrs up to 24 hrs
  } else if (minutes < MINUTES_IN_DAY) {
    var hours = Math.round(minutes / 60)
    return localize('aboutXHours', hours, localizeOptions)

  // 1 day up to 1.75 days
  } else if (minutes < MINUTES_IN_ALMOST_TWO_DAYS) {
    return localize('xDays', 1, localizeOptions)

  // 1.75 days up to 30 days
  } else if (minutes < MINUTES_IN_MONTH) {
    var days = Math.round(minutes / MINUTES_IN_DAY)
    return localize('xDays', days, localizeOptions)

  // 1 month up to 2 months
  } else if (minutes < MINUTES_IN_TWO_MONTHS) {
    months = Math.round(minutes / MINUTES_IN_MONTH)
    return localize('aboutXMonths', months, localizeOptions)
  }

  months = differenceInMonths(dateRight, dateLeft)

  // 2 months up to 12 months
  if (months < 12) {
    var nearestMonth = Math.round(minutes / MINUTES_IN_MONTH)
    return localize('xMonths', nearestMonth, localizeOptions)

  // 1 year up to max Date
  } else {
    var monthsSinceStartOfYear = months % 12
    var years = Math.floor(months / 12)

    // N years up to 1 years 3 months
    if (monthsSinceStartOfYear < 3) {
      return localize('aboutXYears', years, localizeOptions)

    // N years 3 months up to N years 9 months
    } else if (monthsSinceStartOfYear < 9) {
      return localize('overXYears', years, localizeOptions)

    // N years 9 months up to N year 12 months
    } else {
      return localize('almostXYears', years + 1, localizeOptions)
    }
  }
}

module.exports = distanceInWords


/***/ }),
/* 189 */
/***/ (function(module, exports, __webpack_require__) {

var parse = __webpack_require__(17)

/**
 * @category Common Helpers
 * @summary Compare the two dates reverse chronologically and return -1, 0 or 1.
 *
 * @description
 * Compare the two dates and return -1 if the first date is after the second,
 * 1 if the first date is before the second or 0 if dates are equal.
 *
 * @param {Date|String|Number} dateLeft - the first date to compare
 * @param {Date|String|Number} dateRight - the second date to compare
 * @returns {Number} the result of the comparison
 *
 * @example
 * // Compare 11 February 1987 and 10 July 1989 reverse chronologically:
 * var result = compareDesc(
 *   new Date(1987, 1, 11),
 *   new Date(1989, 6, 10)
 * )
 * //=> 1
 *
 * @example
 * // Sort the array of dates in reverse chronological order:
 * var result = [
 *   new Date(1995, 6, 2),
 *   new Date(1987, 1, 11),
 *   new Date(1989, 6, 10)
 * ].sort(compareDesc)
 * //=> [
 * //   Sun Jul 02 1995 00:00:00,
 * //   Mon Jul 10 1989 00:00:00,
 * //   Wed Feb 11 1987 00:00:00
 * // ]
 */
function compareDesc (dirtyDateLeft, dirtyDateRight) {
  var dateLeft = parse(dirtyDateLeft)
  var timeLeft = dateLeft.getTime()
  var dateRight = parse(dirtyDateRight)
  var timeRight = dateRight.getTime()

  if (timeLeft > timeRight) {
    return -1
  } else if (timeLeft < timeRight) {
    return 1
  } else {
    return 0
  }
}

module.exports = compareDesc


/***/ }),
/* 190 */
/***/ (function(module, exports) {

/**
 * @category Common Helpers
 * @summary Is the given argument an instance of Date?
 *
 * @description
 * Is the given argument an instance of Date?
 *
 * @param {*} argument - the argument to check
 * @returns {Boolean} the given argument is an instance of Date
 *
 * @example
 * // Is 'mayonnaise' a Date?
 * var result = isDate('mayonnaise')
 * //=> false
 */
function isDate (argument) {
  return argument instanceof Date
}

module.exports = isDate


/***/ }),
/* 191 */
/***/ (function(module, exports, __webpack_require__) {

var differenceInMilliseconds = __webpack_require__(192)

/**
 * @category Second Helpers
 * @summary Get the number of seconds between the given dates.
 *
 * @description
 * Get the number of seconds between the given dates.
 *
 * @param {Date|String|Number} dateLeft - the later date
 * @param {Date|String|Number} dateRight - the earlier date
 * @returns {Number} the number of seconds
 *
 * @example
 * // How many seconds are between
 * // 2 July 2014 12:30:07.999 and 2 July 2014 12:30:20.000?
 * var result = differenceInSeconds(
 *   new Date(2014, 6, 2, 12, 30, 20, 0),
 *   new Date(2014, 6, 2, 12, 30, 7, 999)
 * )
 * //=> 12
 */
function differenceInSeconds (dirtyDateLeft, dirtyDateRight) {
  var diff = differenceInMilliseconds(dirtyDateLeft, dirtyDateRight) / 1000
  return diff > 0 ? Math.floor(diff) : Math.ceil(diff)
}

module.exports = differenceInSeconds


/***/ }),
/* 192 */
/***/ (function(module, exports, __webpack_require__) {

var parse = __webpack_require__(17)

/**
 * @category Millisecond Helpers
 * @summary Get the number of milliseconds between the given dates.
 *
 * @description
 * Get the number of milliseconds between the given dates.
 *
 * @param {Date|String|Number} dateLeft - the later date
 * @param {Date|String|Number} dateRight - the earlier date
 * @returns {Number} the number of milliseconds
 *
 * @example
 * // How many milliseconds are between
 * // 2 July 2014 12:30:20.600 and 2 July 2014 12:30:21.700?
 * var result = differenceInMilliseconds(
 *   new Date(2014, 6, 2, 12, 30, 21, 700),
 *   new Date(2014, 6, 2, 12, 30, 20, 600)
 * )
 * //=> 1100
 */
function differenceInMilliseconds (dirtyDateLeft, dirtyDateRight) {
  var dateLeft = parse(dirtyDateLeft)
  var dateRight = parse(dirtyDateRight)
  return dateLeft.getTime() - dateRight.getTime()
}

module.exports = differenceInMilliseconds


/***/ }),
/* 193 */
/***/ (function(module, exports, __webpack_require__) {

var parse = __webpack_require__(17)
var differenceInCalendarMonths = __webpack_require__(194)
var compareAsc = __webpack_require__(195)

/**
 * @category Month Helpers
 * @summary Get the number of full months between the given dates.
 *
 * @description
 * Get the number of full months between the given dates.
 *
 * @param {Date|String|Number} dateLeft - the later date
 * @param {Date|String|Number} dateRight - the earlier date
 * @returns {Number} the number of full months
 *
 * @example
 * // How many full months are between 31 January 2014 and 1 September 2014?
 * var result = differenceInMonths(
 *   new Date(2014, 8, 1),
 *   new Date(2014, 0, 31)
 * )
 * //=> 7
 */
function differenceInMonths (dirtyDateLeft, dirtyDateRight) {
  var dateLeft = parse(dirtyDateLeft)
  var dateRight = parse(dirtyDateRight)

  var sign = compareAsc(dateLeft, dateRight)
  var difference = Math.abs(differenceInCalendarMonths(dateLeft, dateRight))
  dateLeft.setMonth(dateLeft.getMonth() - sign * difference)

  // Math.abs(diff in full months - diff in calendar months) === 1 if last calendar month is not full
  // If so, result must be decreased by 1 in absolute value
  var isLastMonthNotFull = compareAsc(dateLeft, dateRight) === -sign
  return sign * (difference - isLastMonthNotFull)
}

module.exports = differenceInMonths


/***/ }),
/* 194 */
/***/ (function(module, exports, __webpack_require__) {

var parse = __webpack_require__(17)

/**
 * @category Month Helpers
 * @summary Get the number of calendar months between the given dates.
 *
 * @description
 * Get the number of calendar months between the given dates.
 *
 * @param {Date|String|Number} dateLeft - the later date
 * @param {Date|String|Number} dateRight - the earlier date
 * @returns {Number} the number of calendar months
 *
 * @example
 * // How many calendar months are between 31 January 2014 and 1 September 2014?
 * var result = differenceInCalendarMonths(
 *   new Date(2014, 8, 1),
 *   new Date(2014, 0, 31)
 * )
 * //=> 8
 */
function differenceInCalendarMonths (dirtyDateLeft, dirtyDateRight) {
  var dateLeft = parse(dirtyDateLeft)
  var dateRight = parse(dirtyDateRight)

  var yearDiff = dateLeft.getFullYear() - dateRight.getFullYear()
  var monthDiff = dateLeft.getMonth() - dateRight.getMonth()

  return yearDiff * 12 + monthDiff
}

module.exports = differenceInCalendarMonths


/***/ }),
/* 195 */
/***/ (function(module, exports, __webpack_require__) {

var parse = __webpack_require__(17)

/**
 * @category Common Helpers
 * @summary Compare the two dates and return -1, 0 or 1.
 *
 * @description
 * Compare the two dates and return 1 if the first date is after the second,
 * -1 if the first date is before the second or 0 if dates are equal.
 *
 * @param {Date|String|Number} dateLeft - the first date to compare
 * @param {Date|String|Number} dateRight - the second date to compare
 * @returns {Number} the result of the comparison
 *
 * @example
 * // Compare 11 February 1987 and 10 July 1989:
 * var result = compareAsc(
 *   new Date(1987, 1, 11),
 *   new Date(1989, 6, 10)
 * )
 * //=> -1
 *
 * @example
 * // Sort the array of dates:
 * var result = [
 *   new Date(1995, 6, 2),
 *   new Date(1987, 1, 11),
 *   new Date(1989, 6, 10)
 * ].sort(compareAsc)
 * //=> [
 * //   Wed Feb 11 1987 00:00:00,
 * //   Mon Jul 10 1989 00:00:00,
 * //   Sun Jul 02 1995 00:00:00
 * // ]
 */
function compareAsc (dirtyDateLeft, dirtyDateRight) {
  var dateLeft = parse(dirtyDateLeft)
  var timeLeft = dateLeft.getTime()
  var dateRight = parse(dirtyDateRight)
  var timeRight = dateRight.getTime()

  if (timeLeft < timeRight) {
    return -1
  } else if (timeLeft > timeRight) {
    return 1
  } else {
    return 0
  }
}

module.exports = compareAsc


/***/ }),
/* 196 */
/***/ (function(module, exports, __webpack_require__) {

var buildDistanceInWordsLocale = __webpack_require__(197)
var buildFormatLocale = __webpack_require__(198)

/**
 * @category Locales
 * @summary English locale.
 */
module.exports = {
  distanceInWords: buildDistanceInWordsLocale(),
  format: buildFormatLocale()
}


/***/ }),
/* 197 */
/***/ (function(module, exports) {

function buildDistanceInWordsLocale () {
  var distanceInWordsLocale = {
    lessThanXSeconds: {
      one: 'less than a second',
      other: 'less than {{count}} seconds'
    },

    xSeconds: {
      one: '1 second',
      other: '{{count}} seconds'
    },

    halfAMinute: 'half a minute',

    lessThanXMinutes: {
      one: 'less than a minute',
      other: 'less than {{count}} minutes'
    },

    xMinutes: {
      one: '1 minute',
      other: '{{count}} minutes'
    },

    aboutXHours: {
      one: 'about 1 hour',
      other: 'about {{count}} hours'
    },

    xHours: {
      one: '1 hour',
      other: '{{count}} hours'
    },

    xDays: {
      one: '1 day',
      other: '{{count}} days'
    },

    aboutXMonths: {
      one: 'about 1 month',
      other: 'about {{count}} months'
    },

    xMonths: {
      one: '1 month',
      other: '{{count}} months'
    },

    aboutXYears: {
      one: 'about 1 year',
      other: 'about {{count}} years'
    },

    xYears: {
      one: '1 year',
      other: '{{count}} years'
    },

    overXYears: {
      one: 'over 1 year',
      other: 'over {{count}} years'
    },

    almostXYears: {
      one: 'almost 1 year',
      other: 'almost {{count}} years'
    }
  }

  function localize (token, count, options) {
    options = options || {}

    var result
    if (typeof distanceInWordsLocale[token] === 'string') {
      result = distanceInWordsLocale[token]
    } else if (count === 1) {
      result = distanceInWordsLocale[token].one
    } else {
      result = distanceInWordsLocale[token].other.replace('{{count}}', count)
    }

    if (options.addSuffix) {
      if (options.comparison > 0) {
        return 'in ' + result
      } else {
        return result + ' ago'
      }
    }

    return result
  }

  return {
    localize: localize
  }
}

module.exports = buildDistanceInWordsLocale


/***/ }),
/* 198 */
/***/ (function(module, exports, __webpack_require__) {

var buildFormattingTokensRegExp = __webpack_require__(199)

function buildFormatLocale () {
  // Note: in English, the names of days of the week and months are capitalized.
  // If you are making a new locale based on this one, check if the same is true for the language you're working on.
  // Generally, formatted dates should look like they are in the middle of a sentence,
  // e.g. in Spanish language the weekdays and months should be in the lowercase.
  var months3char = ['Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun', 'Jul', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec']
  var monthsFull = ['January', 'February', 'March', 'April', 'May', 'June', 'July', 'August', 'September', 'October', 'November', 'December']
  var weekdays2char = ['Su', 'Mo', 'Tu', 'We', 'Th', 'Fr', 'Sa']
  var weekdays3char = ['Sun', 'Mon', 'Tue', 'Wed', 'Thu', 'Fri', 'Sat']
  var weekdaysFull = ['Sunday', 'Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday', 'Saturday']
  var meridiemUppercase = ['AM', 'PM']
  var meridiemLowercase = ['am', 'pm']
  var meridiemFull = ['a.m.', 'p.m.']

  var formatters = {
    // Month: Jan, Feb, ..., Dec
    'MMM': function (date) {
      return months3char[date.getMonth()]
    },

    // Month: January, February, ..., December
    'MMMM': function (date) {
      return monthsFull[date.getMonth()]
    },

    // Day of week: Su, Mo, ..., Sa
    'dd': function (date) {
      return weekdays2char[date.getDay()]
    },

    // Day of week: Sun, Mon, ..., Sat
    'ddd': function (date) {
      return weekdays3char[date.getDay()]
    },

    // Day of week: Sunday, Monday, ..., Saturday
    'dddd': function (date) {
      return weekdaysFull[date.getDay()]
    },

    // AM, PM
    'A': function (date) {
      return (date.getHours() / 12) >= 1 ? meridiemUppercase[1] : meridiemUppercase[0]
    },

    // am, pm
    'a': function (date) {
      return (date.getHours() / 12) >= 1 ? meridiemLowercase[1] : meridiemLowercase[0]
    },

    // a.m., p.m.
    'aa': function (date) {
      return (date.getHours() / 12) >= 1 ? meridiemFull[1] : meridiemFull[0]
    }
  }

  // Generate ordinal version of formatters: M -> Mo, D -> Do, etc.
  var ordinalFormatters = ['M', 'D', 'DDD', 'd', 'Q', 'W']
  ordinalFormatters.forEach(function (formatterToken) {
    formatters[formatterToken + 'o'] = function (date, formatters) {
      return ordinal(formatters[formatterToken](date))
    }
  })

  return {
    formatters: formatters,
    formattingTokensRegExp: buildFormattingTokensRegExp(formatters)
  }
}

function ordinal (number) {
  var rem100 = number % 100
  if (rem100 > 20 || rem100 < 10) {
    switch (rem100 % 10) {
      case 1:
        return number + 'st'
      case 2:
        return number + 'nd'
      case 3:
        return number + 'rd'
    }
  }
  return number + 'th'
}

module.exports = buildFormatLocale


/***/ }),
/* 199 */
/***/ (function(module, exports) {

var commonFormatterKeys = [
  'M', 'MM', 'Q', 'D', 'DD', 'DDD', 'DDDD', 'd',
  'E', 'W', 'WW', 'YY', 'YYYY', 'GG', 'GGGG',
  'H', 'HH', 'h', 'hh', 'm', 'mm',
  's', 'ss', 'S', 'SS', 'SSS',
  'Z', 'ZZ', 'X', 'x'
]

function buildFormattingTokensRegExp (formatters) {
  var formatterKeys = []
  for (var key in formatters) {
    if (formatters.hasOwnProperty(key)) {
      formatterKeys.push(key)
    }
  }

  var formattingTokens = commonFormatterKeys
    .concat(formatterKeys)
    .sort()
    .reverse()
  var formattingTokensRegExp = new RegExp(
    '(\\[[^\\[]*\\])|(\\\\)?' + '(' + formattingTokens.join('|') + '|.)', 'g'
  )

  return formattingTokensRegExp
}

module.exports = buildFormattingTokensRegExp


/***/ }),
/* 200 */
/***/ (function(module, exports) {

function buildDistanceInWordsLocale () {
  var distanceInWordsLocale = {
    lessThanXSeconds: {
      one: '不到 1 秒',
      other: '不到 {{count}} 秒'
    },

    xSeconds: {
      one: '1 秒',
      other: '{{count}} 秒'
    },

    halfAMinute: '半分钟',

    lessThanXMinutes: {
      one: '不到 1 分钟',
      other: '不到 {{count}} 分钟'
    },

    xMinutes: {
      one: '1 分钟',
      other: '{{count}} 分钟'
    },

    xHours: {
      one: '1 小时',
      other: '{{count}} 小时'
    },

    aboutXHours: {
      one: '大约 1 小时',
      other: '大约 {{count}} 小时'
    },

    xDays: {
      one: '1 天',
      other: '{{count}} 天'
    },

    aboutXMonths: {
      one: '大约 1 个月',
      other: '大约 {{count}} 个月'
    },

    xMonths: {
      one: '1 个月',
      other: '{{count}} 个月'
    },

    aboutXYears: {
      one: '大约 1 年',
      other: '大约 {{count}} 年'
    },

    xYears: {
      one: '1 年',
      other: '{{count}} 年'
    },

    overXYears: {
      one: '超过 1 年',
      other: '超过 {{count}} 年'
    },

    almostXYears: {
      one: '将近 1 年',
      other: '将近 {{count}} 年'
    }
  }

  function localize (token, count, options) {
    options = options || {}

    var result
    if (typeof distanceInWordsLocale[token] === 'string') {
      result = distanceInWordsLocale[token]
    } else if (count === 1) {
      result = distanceInWordsLocale[token].one
    } else {
      result = distanceInWordsLocale[token].other.replace('{{count}}', count)
    }

    if (options.addSuffix) {
      if (options.comparison > 0) {
        return result + '内'
      } else {
        return result + '前'
      }
    }

    return result
  }

  return {
    localize: localize
  }
}

module.exports = buildDistanceInWordsLocale


/***/ }),
/* 201 */
/***/ (function(module, exports) {

function buildDistanceInWordsLocale () {
  var distanceInWordsLocale = {
    lessThanXSeconds: {
      one: '少於 1 秒',
      other: '少於 {{count}} 秒'
    },

    xSeconds: {
      one: '1 秒',
      other: '{{count}} 秒'
    },

    halfAMinute: '半分鐘',

    lessThanXMinutes: {
      one: '少於 1 分鐘',
      other: '少於 {{count}} 分鐘'
    },

    xMinutes: {
      one: '1 分鐘',
      other: '{{count}} 分鐘'
    },

    xHours: {
      one: '1 小時',
      other: '{{count}} 小時'
    },

    aboutXHours: {
      one: '大約 1 小時',
      other: '大約 {{count}} 小時'
    },

    xDays: {
      one: '1 天',
      other: '{{count}} 天'
    },

    aboutXMonths: {
      one: '大約 1 個月',
      other: '大約 {{count}} 個月'
    },

    xMonths: {
      one: '1 個月',
      other: '{{count}} 個月'
    },

    aboutXYears: {
      one: '大約 1 年',
      other: '大約 {{count}} 年'
    },

    xYears: {
      one: '1 年',
      other: '{{count}} 年'
    },

    overXYears: {
      one: '超過 1 年',
      other: '超過 {{count}} 年'
    },

    almostXYears: {
      one: '將近 1 年',
      other: '將近 {{count}} 年'
    }
  }

  function localize (token, count, options) {
    options = options || {}

    var result
    if (typeof distanceInWordsLocale[token] === 'string') {
      result = distanceInWordsLocale[token]
    } else if (count === 1) {
      result = distanceInWordsLocale[token].one
    } else {
      result = distanceInWordsLocale[token].other.replace('{{count}}', count)
    }

    if (options.addSuffix) {
      if (options.comparison > 0) {
        return result + '內'
      } else {
        return result + '前'
      }
    }

    return result
  }

  return {
    localize: localize
  }
}

module.exports = buildDistanceInWordsLocale


/***/ }),
/* 202 */
/***/ (function(module, exports) {

function buildDistanceInWordsLocale () {
  var distanceInWordsLocale = {
    lessThanXSeconds: {
      one: 'menos de un segundo',
      other: 'menos de {{count}} segundos'
    },

    xSeconds: {
      one: '1 segundo',
      other: '{{count}} segundos'
    },

    halfAMinute: 'medio minuto',

    lessThanXMinutes: {
      one: 'menos de un minuto',
      other: 'menos de {{count}} minutos'
    },

    xMinutes: {
      one: '1 minuto',
      other: '{{count}} minutos'
    },

    aboutXHours: {
      one: 'alrededor de 1 hora',
      other: 'alrededor de {{count}} horas'
    },

    xHours: {
      one: '1 hora',
      other: '{{count}} horas'
    },

    xDays: {
      one: '1 día',
      other: '{{count}} días'
    },

    aboutXMonths: {
      one: 'alrededor de 1 mes',
      other: 'alrededor de {{count}} meses'
    },

    xMonths: {
      one: '1 mes',
      other: '{{count}} meses'
    },

    aboutXYears: {
      one: 'alrededor de 1 año',
      other: 'alrededor de {{count}} años'
    },

    xYears: {
      one: '1 año',
      other: '{{count}} años'
    },

    overXYears: {
      one: 'más de 1 año',
      other: 'más de {{count}} años'
    },

    almostXYears: {
      one: 'casi 1 año',
      other: 'casi {{count}} años'
    }
  }

  function localize (token, count, options) {
    options = options || {}

    var result
    if (typeof distanceInWordsLocale[token] === 'string') {
      result = distanceInWordsLocale[token]
    } else if (count === 1) {
      result = distanceInWordsLocale[token].one
    } else {
      result = distanceInWordsLocale[token].other.replace('{{count}}', count)
    }

    if (options.addSuffix) {
      if (options.comparison > 0) {
        return 'en ' + result
      } else {
        return 'hace ' + result
      }
    }

    return result
  }

  return {
    localize: localize
  }
}

module.exports = buildDistanceInWordsLocale


/***/ }),
/* 203 */
/***/ (function(module, exports) {

function buildDistanceInWordsLocale () {
  var distanceInWordsLocale = {
    lessThanXSeconds: {
      one: 'moins d’une seconde',
      other: 'moins de {{count}} secondes'
    },

    xSeconds: {
      one: '1 seconde',
      other: '{{count}} secondes'
    },

    halfAMinute: '30 secondes',

    lessThanXMinutes: {
      one: 'moins d’une minute',
      other: 'moins de {{count}} minutes'
    },

    xMinutes: {
      one: '1 minute',
      other: '{{count}} minutes'
    },

    aboutXHours: {
      one: 'environ 1 heure',
      other: 'environ {{count}} heures'
    },

    xHours: {
      one: '1 heure',
      other: '{{count}} heures'
    },

    xDays: {
      one: '1 jour',
      other: '{{count}} jours'
    },

    aboutXMonths: {
      one: 'environ 1 mois',
      other: 'environ {{count}} mois'
    },

    xMonths: {
      one: '1 mois',
      other: '{{count}} mois'
    },

    aboutXYears: {
      one: 'environ 1 an',
      other: 'environ {{count}} ans'
    },

    xYears: {
      one: '1 an',
      other: '{{count}} ans'
    },

    overXYears: {
      one: 'plus d’un an',
      other: 'plus de {{count}} ans'
    },

    almostXYears: {
      one: 'presqu’un an',
      other: 'presque {{count}} ans'
    }
  }

  function localize (token, count, options) {
    options = options || {}

    var result
    if (typeof distanceInWordsLocale[token] === 'string') {
      result = distanceInWordsLocale[token]
    } else if (count === 1) {
      result = distanceInWordsLocale[token].one
    } else {
      result = distanceInWordsLocale[token].other.replace('{{count}}', count)
    }

    if (options.addSuffix) {
      if (options.comparison > 0) {
        return 'dans ' + result
      } else {
        return 'il y a ' + result
      }
    }

    return result
  }

  return {
    localize: localize
  }
}

module.exports = buildDistanceInWordsLocale


/***/ }),
/* 204 */
/***/ (function(module, exports) {

function declension (scheme, count) {
  // scheme for count=1 exists
  if (scheme.one !== undefined && count === 1) {
    return scheme.one
  }

  var rem10 = count % 10
  var rem100 = count % 100

  // 1, 21, 31, ...
  if (rem10 === 1 && rem100 !== 11) {
    return scheme.singularNominative.replace('{{count}}', count)

  // 2, 3, 4, 22, 23, 24, 32 ...
  } else if ((rem10 >= 2 && rem10 <= 4) && (rem100 < 10 || rem100 > 20)) {
    return scheme.singularGenitive.replace('{{count}}', count)

  // 5, 6, 7, 8, 9, 10, 11, ...
  } else {
    return scheme.pluralGenitive.replace('{{count}}', count)
  }
}

function buildLocalizeTokenFn (scheme) {
  return function (count, options) {
    if (options.addSuffix) {
      if (options.comparison > 0) {
        if (scheme.future) {
          return declension(scheme.future, count)
        } else {
          return 'через ' + declension(scheme.regular, count)
        }
      } else {
        if (scheme.past) {
          return declension(scheme.past, count)
        } else {
          return declension(scheme.regular, count) + ' назад'
        }
      }
    } else {
      return declension(scheme.regular, count)
    }
  }
}

function buildDistanceInWordsLocale () {
  var distanceInWordsLocale = {
    lessThanXSeconds: buildLocalizeTokenFn({
      regular: {
        one: 'меньше секунды',
        singularNominative: 'меньше {{count}} секунды',
        singularGenitive: 'меньше {{count}} секунд',
        pluralGenitive: 'меньше {{count}} секунд'
      },
      future: {
        one: 'меньше, чем через секунду',
        singularNominative: 'меньше, чем через {{count}} секунду',
        singularGenitive: 'меньше, чем через {{count}} секунды',
        pluralGenitive: 'меньше, чем через {{count}} секунд'
      }
    }),

    xSeconds: buildLocalizeTokenFn({
      regular: {
        singularNominative: '{{count}} секунда',
        singularGenitive: '{{count}} секунды',
        pluralGenitive: '{{count}} секунд'
      },
      past: {
        singularNominative: '{{count}} секунду назад',
        singularGenitive: '{{count}} секунды назад',
        pluralGenitive: '{{count}} секунд назад'
      },
      future: {
        singularNominative: 'через {{count}} секунду',
        singularGenitive: 'через {{count}} секунды',
        pluralGenitive: 'через {{count}} секунд'
      }
    }),

    halfAMinute: function (_, options) {
      if (options.addSuffix) {
        if (options.comparison > 0) {
          return 'через полминуты'
        } else {
          return 'полминуты назад'
        }
      }

      return 'полминуты'
    },

    lessThanXMinutes: buildLocalizeTokenFn({
      regular: {
        one: 'меньше минуты',
        singularNominative: 'меньше {{count}} минуты',
        singularGenitive: 'меньше {{count}} минут',
        pluralGenitive: 'меньше {{count}} минут'
      },
      future: {
        one: 'меньше, чем через минуту',
        singularNominative: 'меньше, чем через {{count}} минуту',
        singularGenitive: 'меньше, чем через {{count}} минуты',
        pluralGenitive: 'меньше, чем через {{count}} минут'
      }
    }),

    xMinutes: buildLocalizeTokenFn({
      regular: {
        singularNominative: '{{count}} минута',
        singularGenitive: '{{count}} минуты',
        pluralGenitive: '{{count}} минут'
      },
      past: {
        singularNominative: '{{count}} минуту назад',
        singularGenitive: '{{count}} минуты назад',
        pluralGenitive: '{{count}} минут назад'
      },
      future: {
        singularNominative: 'через {{count}} минуту',
        singularGenitive: 'через {{count}} минуты',
        pluralGenitive: 'через {{count}} минут'
      }
    }),

    aboutXHours: buildLocalizeTokenFn({
      regular: {
        singularNominative: 'около {{count}} часа',
        singularGenitive: 'около {{count}} часов',
        pluralGenitive: 'около {{count}} часов'
      },
      future: {
        singularNominative: 'приблизительно через {{count}} час',
        singularGenitive: 'приблизительно через {{count}} часа',
        pluralGenitive: 'приблизительно через {{count}} часов'
      }
    }),

    xHours: buildLocalizeTokenFn({
      regular: {
        singularNominative: '{{count}} час',
        singularGenitive: '{{count}} часа',
        pluralGenitive: '{{count}} часов'
      }
    }),

    xDays: buildLocalizeTokenFn({
      regular: {
        singularNominative: '{{count}} день',
        singularGenitive: '{{count}} дня',
        pluralGenitive: '{{count}} дней'
      }
    }),

    aboutXMonths: buildLocalizeTokenFn({
      regular: {
        singularNominative: 'около {{count}} месяца',
        singularGenitive: 'около {{count}} месяцев',
        pluralGenitive: 'около {{count}} месяцев'
      },
      future: {
        singularNominative: 'приблизительно через {{count}} месяц',
        singularGenitive: 'приблизительно через {{count}} месяца',
        pluralGenitive: 'приблизительно через {{count}} месяцев'
      }
    }),

    xMonths: buildLocalizeTokenFn({
      regular: {
        singularNominative: '{{count}} месяц',
        singularGenitive: '{{count}} месяца',
        pluralGenitive: '{{count}} месяцев'
      }
    }),

    aboutXYears: buildLocalizeTokenFn({
      regular: {
        singularNominative: 'около {{count}} года',
        singularGenitive: 'около {{count}} лет',
        pluralGenitive: 'около {{count}} лет'
      },
      future: {
        singularNominative: 'приблизительно через {{count}} год',
        singularGenitive: 'приблизительно через {{count}} года',
        pluralGenitive: 'приблизительно через {{count}} лет'
      }
    }),

    xYears: buildLocalizeTokenFn({
      regular: {
        singularNominative: '{{count}} год',
        singularGenitive: '{{count}} года',
        pluralGenitive: '{{count}} лет'
      }
    }),

    overXYears: buildLocalizeTokenFn({
      regular: {
        singularNominative: 'больше {{count}} года',
        singularGenitive: 'больше {{count}} лет',
        pluralGenitive: 'больше {{count}} лет'
      },
      future: {
        singularNominative: 'больше, чем через {{count}} год',
        singularGenitive: 'больше, чем через {{count}} года',
        pluralGenitive: 'больше, чем через {{count}} лет'
      }
    }),

    almostXYears: buildLocalizeTokenFn({
      regular: {
        singularNominative: 'почти {{count}} год',
        singularGenitive: 'почти {{count}} года',
        pluralGenitive: 'почти {{count}} лет'
      },
      future: {
        singularNominative: 'почти через {{count}} год',
        singularGenitive: 'почти через {{count}} года',
        pluralGenitive: 'почти через {{count}} лет'
      }
    })
  }

  function localize (token, count, options) {
    options = options || {}
    return distanceInWordsLocale[token](count, options)
  }

  return {
    localize: localize
  }
}

module.exports = buildDistanceInWordsLocale


/***/ }),
/* 205 */
/***/ (function(module, exports) {

function declensionGroup (scheme, count) {
  if (count === 1) {
    return scheme.one
  }

  var rem100 = count % 100

  // ends with 11-20
  if (rem100 <= 20 && rem100 > 10) {
    return scheme.other
  }

  var rem10 = rem100 % 10

  // ends with 2, 3, 4
  if (rem10 >= 2 && rem10 <= 4) {
    return scheme.twoFour
  }

  return scheme.other
}

function declension (scheme, count, time) {
  time = time || 'regular'
  var group = declensionGroup(scheme, count)
  var finalText = group[time] || group
  return finalText.replace('{{count}}', count)
}

function buildDistanceInWordsLocale () {
  var distanceInWordsLocale = {
    lessThanXSeconds: {
      one: {
        regular: 'mniej niż sekunda',
        past: 'mniej niż sekundę',
        future: 'mniej niż sekundę'
      },
      twoFour: 'mniej niż {{count}} sekundy',
      other: 'mniej niż {{count}} sekund'
    },

    xSeconds: {
      one: {
        regular: 'sekunda',
        past: 'sekundę',
        future: 'sekundę'
      },
      twoFour: '{{count}} sekundy',
      other: '{{count}} sekund'
    },

    halfAMinute: {
      one: 'pół minuty',
      twoFour: 'pół minuty',
      other: 'pół minuty'
    },

    lessThanXMinutes: {
      one: {
        regular: 'mniej niż minuta',
        past: 'mniej niż minutę',
        future: 'mniej niż minutę'
      },
      twoFour: 'mniej niż {{count}} minuty',
      other: 'mniej niż {{count}} minut'
    },

    xMinutes: {
      one: {
        regular: 'minuta',
        past: 'minutę',
        future: 'minutę'
      },
      twoFour: '{{count}} minuty',
      other: '{{count}} minut'
    },

    aboutXHours: {
      one: {
        regular: 'około godzina',
        past: 'około godziny',
        future: 'około godzinę'
      },
      twoFour: 'około {{count}} godziny',
      other: 'około {{count}} godzin'
    },

    xHours: {
      one: {
        regular: 'godzina',
        past: 'godzinę',
        future: 'godzinę'
      },
      twoFour: '{{count}} godziny',
      other: '{{count}} godzin'
    },

    xDays: {
      one: {
        regular: 'dzień',
        past: 'dzień',
        future: '1 dzień'
      },
      twoFour: '{{count}} dni',
      other: '{{count}} dni'
    },

    aboutXMonths: {
      one: 'około miesiąc',
      twoFour: 'około {{count}} miesiące',
      other: 'około {{count}} miesięcy'
    },

    xMonths: {
      one: 'miesiąc',
      twoFour: '{{count}} miesiące',
      other: '{{count}} miesięcy'
    },

    aboutXYears: {
      one: 'około rok',
      twoFour: 'około {{count}} lata',
      other: 'około {{count}} lat'
    },

    xYears: {
      one: 'rok',
      twoFour: '{{count}} lata',
      other: '{{count}} lat'
    },

    overXYears: {
      one: 'ponad rok',
      twoFour: 'ponad {{count}} lata',
      other: 'ponad {{count}} lat'
    },

    almostXYears: {
      one: 'prawie rok',
      twoFour: 'prawie {{count}} lata',
      other: 'prawie {{count}} lat'
    }
  }

  function localize (token, count, options) {
    options = options || {}

    var scheme = distanceInWordsLocale[token]
    if (!options.addSuffix) {
      return declension(scheme, count)
    }

    if (options.comparison > 0) {
      return 'za ' + declension(scheme, count, 'future')
    } else {
      return declension(scheme, count, 'past') + ' temu'
    }
  }

  return {
    localize: localize
  }
}

module.exports = buildDistanceInWordsLocale


/***/ }),
/* 206 */
/***/ (function(module, exports) {

// removed by extract-text-webpack-plugin

/***/ }),
/* 207 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";


Object.defineProperty(exports, "__esModule", {
  value: true
});
var GT_ACCESS_TOKEN = exports.GT_ACCESS_TOKEN = 'GT_ACCESS_TOKEN';
var GT_VERSION = exports.GT_VERSION = "1.7.0"; // eslint-disable-line
var GT_COMMENT = exports.GT_COMMENT = 'GT_COMMENT';

/***/ }),
/* 208 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";


Object.defineProperty(exports, "__esModule", {
  value: true
});

var _toConsumableArray2 = __webpack_require__(209);

var _toConsumableArray3 = _interopRequireDefault(_toConsumableArray2);

var _util = __webpack_require__(69);

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

var getQL = function getQL(vars, pagerDirection) {
  var cursorDirection = pagerDirection === 'last' ? 'before' : 'after';
  var ql = '\n  query getIssueAndComments(\n    $owner: String!,\n    $repo: String!,\n    $id: Int!,\n    $cursor: String,\n    $pageSize: Int!\n  ) {\n    repository(owner: $owner, name: $repo) {\n      issue(number: $id) {\n        title\n        url\n        bodyHTML\n        createdAt\n        comments(' + pagerDirection + ': $pageSize, ' + cursorDirection + ': $cursor) {\n          totalCount\n          pageInfo {\n            ' + (pagerDirection === 'last' ? 'hasPreviousPage' : 'hasNextPage') + '\n            ' + (cursorDirection === 'before' ? 'startCursor' : 'endCursor') + '\n          }\n          nodes {\n            id\n            databaseId\n            author {\n              avatarUrl\n              login\n              url\n            }\n            bodyHTML\n            body\n            createdAt\n            reactions(first: 100, content: HEART) {\n              totalCount\n              viewerHasReacted\n              pageInfo{\n                hasNextPage\n              }\n              nodes {\n                id\n                databaseId\n                user {\n                  login\n                }\n              }\n            }\n          }\n        }\n      }\n    }\n  }\n  ';

  if (vars.cursor === null) delete vars.cursor;

  return {
    operationName: 'getIssueAndComments',
    query: ql,
    variables: vars
  };
};

function getComments(issue) {
  var _this = this;

  var _options = this.options,
      owner = _options.owner,
      repo = _options.repo,
      perPage = _options.perPage,
      pagerDirection = _options.pagerDirection,
      defaultAuthor = _options.defaultAuthor;
  var _state = this.state,
      cursor = _state.cursor,
      comments = _state.comments;

  return _util.axiosGithub.post('/graphql', getQL({
    owner: owner,
    repo: repo,
    id: issue.number,
    pageSize: perPage,
    cursor: cursor
  }, pagerDirection), {
    headers: {
      Authorization: 'bearer ' + this.accessToken
    }
  }).then(function (res) {
    var data = res.data.data.repository.issue.comments;
    var items = data.nodes.map(function (node) {
      var author = node.author || defaultAuthor;

      return {
        id: node.databaseId,
        gId: node.id,
        user: {
          avatar_url: author.avatarUrl,
          login: author.login,
          html_url: author.url
        },
        created_at: node.createdAt,
        body_html: node.bodyHTML,
        body: node.body,
        html_url: 'https://github.com/' + owner + '/' + repo + '/issues/' + issue.number + '#issuecomment-' + node.databaseId,
        reactions: node.reactions
      };
    });

    var cs = void 0;

    if (pagerDirection === 'last') {
      cs = [].concat((0, _toConsumableArray3.default)(items), (0, _toConsumableArray3.default)(comments));
    } else {
      cs = [].concat((0, _toConsumableArray3.default)(comments), (0, _toConsumableArray3.default)(items));
    }

    var isLoadOver = data.pageInfo.hasPreviousPage === false || data.pageInfo.hasNextPage === false;
    _this.setState({
      comments: cs,
      isLoadOver: isLoadOver,
      cursor: data.pageInfo.startCursor || data.pageInfo.endCursor
    });
    return cs;
  });
}

exports.default = getComments;

/***/ }),
/* 209 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";


exports.__esModule = true;

var _from = __webpack_require__(210);

var _from2 = _interopRequireDefault(_from);

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

exports.default = function (arr) {
  if (Array.isArray(arr)) {
    for (var i = 0, arr2 = Array(arr.length); i < arr.length; i++) {
      arr2[i] = arr[i];
    }

    return arr2;
  } else {
    return (0, _from2.default)(arr);
  }
};

/***/ }),
/* 210 */
/***/ (function(module, exports, __webpack_require__) {

module.exports = { "default": __webpack_require__(211), __esModule: true };

/***/ }),
/* 211 */
/***/ (function(module, exports, __webpack_require__) {

__webpack_require__(18);
__webpack_require__(212);
module.exports = __webpack_require__(0).Array.from;


/***/ }),
/* 212 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";

var ctx = __webpack_require__(12);
var $export = __webpack_require__(4);
var toObject = __webpack_require__(16);
var call = __webpack_require__(52);
var isArrayIter = __webpack_require__(53);
var toLength = __webpack_require__(33);
var createProperty = __webpack_require__(213);
var getIterFn = __webpack_require__(38);

$export($export.S + $export.F * !__webpack_require__(58)(function (iter) { Array.from(iter); }), 'Array', {
  // 22.1.2.1 Array.from(arrayLike, mapfn = undefined, thisArg = undefined)
  from: function from(arrayLike /* , mapfn = undefined, thisArg = undefined */) {
    var O = toObject(arrayLike);
    var C = typeof this == 'function' ? this : Array;
    var aLen = arguments.length;
    var mapfn = aLen > 1 ? arguments[1] : undefined;
    var mapping = mapfn !== undefined;
    var index = 0;
    var iterFn = getIterFn(O);
    var length, result, step, iterator;
    if (mapping) mapfn = ctx(mapfn, aLen > 2 ? arguments[2] : undefined, 2);
    // if object isn't iterable or it's array with default iterator - use simple case
    if (iterFn != undefined && !(C == Array && isArrayIter(iterFn))) {
      for (iterator = iterFn.call(O), result = new C(); !(step = iterator.next()).done; index++) {
        createProperty(result, index, mapping ? call(iterator, mapfn, [step.value, index], true) : step.value);
      }
    } else {
      length = toLength(O.length);
      for (result = new C(length); length > index; index++) {
        createProperty(result, index, mapping ? mapfn(O[index], index) : O[index]);
      }
    }
    result.length = index;
    return result;
  }
});


/***/ }),
/* 213 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";

var $defineProperty = __webpack_require__(6);
var createDesc = __webpack_require__(20);

module.exports = function (object, index, value) {
  if (index in object) $defineProperty.f(object, index, createDesc(0, value));
  else object[index] = value;
};


/***/ })
/******/ ]);
});
//# sourceMappingURL=gitalk-component.js.map