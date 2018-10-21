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
var ascii2jax = function() {};

ascii2jax.prototype.config = {
    doc: {},
    delimiters: [
        ['`', '`']
    ], // The star/stop delimiter pairs for asciimath code

    skipTags: ["script", "noscript", "style", "textarea", "pre", "code", "annotation", "annotation-xml"],
    // The names of the tags whose contents will not be
    // scanned for math delimiters

    ignoreClass: "asciimath2jax_ignore", // the class name of elements whose contents should
    // NOT be processed by asciimath2jax.  Note that this
    // is a regular expression, so be sure to quote any
    // regexp special characters

    processClass: "asciimath2jax_process", // the class name of elements whose contents SHOULD
    // be processed when they appear inside ones that
    // are ignored.  Note that this is a regular expression,
    // so be sure to quote any regexp special characters

};

ascii2jax.prototype.PreProcess = function(element) {
    if (typeof(element) === "string") {
        element = this.config.doc.getElementById(element)
    }
    if (!element) {
        element = this.config.doc.body
    }
    if (this.createPatterns()) {
        this.scanElement(element, element.nextSibling)
    }
};

ascii2jax.prototype.createPatterns = function() {
    var starts = [],
        parts = [],
        i, m, config = this.config;
    this.match = {};
    if (config.delimiters.length === 0) {
        return false
    }
    for (i = 0, m = config.delimiters.length; i < m; i++) {
        starts.push(this.patternQuote(config.delimiters[i][0]));
        this.match[config.delimiters[i][0]] = {
            mode: "",
            end: config.delimiters[i][1],
            pattern: this.endPattern(config.delimiters[i][1])
        };
    }
    this.start = new RegExp(starts.sort(this.sortLength).join("|"), "g");
    this.skipTags = new RegExp("^(" + config.skipTags.join("|") + ")$", "i");
    var ignore = [];
    if (this.config.preRemoveClass) {
        ignore.push(this.config.preRemoveClass)
    }
    if (config.ignoreClass) {
        ignore.push(config.ignoreClass)
    }
    this.ignoreClass = (ignore.length ? new RegExp("(^| )(" + ignore.join("|") + ")( |$)") : /^$/);
    this.processClass = new RegExp("(^| )(" + config.processClass + ")( |$)");
    return true;
};

ascii2jax.prototype.patternQuote = function(s) {
    return s.replace(/([\^$(){}+*?\-|\[\]\:\\])/g, '\\$1')
};

ascii2jax.prototype.endPattern = function(end) {
    return new RegExp(this.patternQuote(end) + "|\\\\.", "g");
};

ascii2jax.prototype.sortLength = function(a, b) {
    if (a.length !== b.length) {
        return b.length - a.length
    }
    return (a == b ? 0 : (a < b ? -1 : 1));
};

ascii2jax.prototype.scanElement = function(element, stop, ignore) {
    var cname, tname, ignoreChild, process;
    while (element && element != stop) {
        if (element.nodeName.toLowerCase() === '#text') {
            if (!ignore) {
                element = this.scanText(element)
            }
        } else {
            cname = (typeof(element.className) === "undefined" ? "" : element.className);
            tname = (typeof(element.tagName) === "undefined" ? "" : element.tagName);
            if (typeof(cname) !== "string") {
                cname = String(cname)
            } // jsxgraph uses non-string class names!
            process = this.processClass.exec(cname);
            if (element.firstChild && !cname.match(/(^| )MathJax/) &&
                (process || !this.skipTags.exec(tname))) {
                ignoreChild = (ignore || this.ignoreClass.exec(cname)) && !process;
                this.scanElement(element.firstChild, stop, ignoreChild);
            }
        }
        if (element) {
            element = element.nextSibling
        }
    }
};

ascii2jax.prototype.scanText = function(element) {
    if (element.nodeValue.replace(/\s+/, '') == '') {
        return element
    }
    var match, prev;
    this.search = {
        start: true
    };
    this.pattern = this.start;
    while (element) {
        this.pattern.lastIndex = 0;
        while (element && element.nodeName.toLowerCase() === '#text' &&
            (match = this.pattern.exec(element.nodeValue))) {
            if (this.search.start) {
                element = this.startMatch(match, element)
            } else {
                element = this.endMatch(match, element)
            }
        }
        if (this.search.matched) {
            element = this.encloseMath(element)
        }
        if (element) {
            do {
                prev = element;
                element = element.nextSibling
            }
            while (element && (element.nodeName.toLowerCase() === 'br' ||
                    element.nodeName.toLowerCase() === '#comment'));
            if (!element || element.nodeName !== '#text') {
                return prev
            }
        }
    }
    return element;
};

ascii2jax.prototype.startMatch = function(match, element) {
    var delim = this.match[match[0]];
    if (delim != null) {
        this.search = {
            end: delim.end,
            mode: delim.mode,
            open: element,
            olen: match[0].length,
            opos: this.pattern.lastIndex - match[0].length
        };
        this.switchPattern(delim.pattern);
    }
    return element;
};

ascii2jax.prototype.endMatch = function(match, element) {
    if (match[0] == this.search.end) {
        this.search.close = element;
        this.search.cpos = this.pattern.lastIndex;
        this.search.clen = (this.search.isBeginEnd ? 0 : match[0].length);
        this.search.matched = true;
        element = this.encloseMath(element);
        this.switchPattern(this.start);
    }
    return element;
};

ascii2jax.prototype.switchPattern = function(pattern) {
    pattern.lastIndex = this.pattern.lastIndex;
    this.pattern = pattern;
    this.search.start = (pattern === this.start);
};

ascii2jax.prototype.encloseMath = function(element) {
    var search = this.search,
        close = search.close,
        CLOSE, math;
    if (search.cpos === close.length) {
        close = close.nextSibling
    } else {
        close = close.splitText(search.cpos)
    }
    if (!close) {
        CLOSE = close = search.close.parentNode.appendChild(this.config.doc.createTextNode(""));
    }
    search.close = close;
    math = (search.opos ? search.open.splitText(search.opos) : search.open);
    while (math.nextSibling && math.nextSibling !== close) {
        if (math.nextSibling.nodeValue !== null) {
            if (math.nextSibling.nodeName === "#comment") {
                math.nodeValue += math.nextSibling.nodeValue.replace(/^\[CDATA\[((.|\n|\r)*)\]\]$/, "$1");
            } else {
                math.nodeValue += math.nextSibling.nodeValue;
            }
        } else if (this.msieNewlineBug) {
            math.nodeValue += (math.nextSibling.nodeName.toLowerCase() === "br" ? "\n" : " ");
        } else {
            math.nodeValue += " ";
        }
        math.parentNode.removeChild(math.nextSibling);
    }
    var AM = math.nodeValue.substr(search.olen, math.nodeValue.length - search.olen - search.clen);
    math.parentNode.removeChild(math);
    math = this.createMathTag(search.mode, AM);
    this.search = {};
    this.pattern.lastIndex = 0;
    if (CLOSE) {
        CLOSE.parentNode.removeChild(CLOSE)
    }
    return math;
};

ascii2jax.prototype.insertNode = function(node) {
    var search = this.search;
    search.close.parentNode.insertBefore(node, search.close);
};

ascii2jax.prototype.createMathTag = function(mode, tex) {
    var script = this.config.doc.createElement("script");
    script.type = 'math/AsciiMath';
    script.text = tex;
    this.insertNode(script);
    return script;
};

ascii2jax.prototype.filterPreview = function(asciimath) {
    return asciimath
};

exports.ascii2jax = new ascii2jax();
