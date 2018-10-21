const jsdom = require('jsdom');
const { JSDOM } = jsdom;
const util = require('util');
const EventEmitter = require('events').EventEmitter;
const tex = require('./tex.js').tex2jax;
const ascii = require('./ascii.js').ascii2jax;
const mathml = require('./mathml.js').mathml2jax;
// HACK isolate confingurations cf #22
const texconfig = JSON.stringify(tex.config);
const asciiconfig = JSON.stringify(ascii.config);

let count = 0;  // global count of jobs (for job IDs)
let mathjax, typeset;  // mathjax-node instance (initialized with exports.init)
let _outputJax = ['mml', 'html', 'svg'];  // output options in typesetConfig
let _outputHandlers = {};  // custom handlers for saving conversion results to DOM
let _started = false;  // is mathjax-node currently working?

function MjPageJob(id, options, callback) {
    this.id = id || Math.random();
    this.options = options;
    this.callback = callback;

    this._parsedFormulasCache = {};  // keeping state between callbacks
    this._outstandingHandlers = {};  // counter for outstanding async operations on files
}

util.inherits(MjPageJob, EventEmitter);
MjPageJob.prototype.constructor = MjPageJob;


MjPageJob.prototype.run = function() {
    const htmlstring = this.options.htmlstring,
      configOptions = this.options.configOptions,
      typesetOptions = this.options.typesetOptions,
      callback = this.callback;

    // `config` extends options for mathjax-node's config method, cf https://github.com/mathjax/MathJax-node/wiki/Configuration-options#configoptions
    const config = {
        // mathjax-node-page specific
        format: ["MathML", "TeX", "AsciiMath"], // determines type of pre-processors to run
        output: '', // global override for output option; 'svg', 'html' or 'mml'
        tex: {}, // configuration options for tex pre-processor
        ascii: {}, // configuration options for ascii pre-processor
        singleDollars: false, // allow single-dollar delimiter for inline TeX
        fragment: false, // return body.innerHTML instead of full document
        cssInline: true,  // determines whether inline css should be added (leaving false still allows to add css as a separate file using beforeSerialization event hook)
        jsdom: {
            // NOTE these are not straight jsdom configuration options (cf. below)
            runScripts: 'outside-only', // set to "dangerously" to execute scripts from the HTML source
            virtualConsole: true
        },
        //
        // standard mathjax-node options
        //
        displayMessages: false, // determines whether Message.Set() calls are logged
        displayErrors: false, // determines whether error messages are shown on the console
        undefinedCharError: false, // determines whether unknown characters are saved in the error array
        extensions: '', // a convenience option to add MathJax extensions
        fontURL: 'https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.2/fonts/HTML-CSS', // for webfont urls in the CSS for HTML output
        MathJax: {} // options MathJax configuration, see https://docs.mathjax.org
    };
    const mjstate = {};
    // defaults for mathjax-node's typeset method
    const typesetConfig = {
        ex: 6, // ex-size in pixels
        width: 100, // width of container (in ex) for linebreaking and tags
        useFontCache: true, // use <defs> and <use> in svg output?
        useGlobalCache: false, // use common <defs> for all equations?
        state: mjstate, // track global state
        linebreaks: false, // do linebreaking?
        equationNumbers: "none", // or "AMS" or "all"
        math: "", // the math to typeset
        html: false, // generate HTML output?
        css: false, // generate CSS for HTML output?
        mml: false, // generate mml output?
        svg: false, // generate svg output?
        speakText: true, // add spoken annotations to svg output?
        speakRuleset: "mathspeak", // set speech ruleset (default (chromevox rules), mathspeak)
        speakStyle: "default", // set speech style (mathspeak:  default, brief, sbrief)
        timeout: 10 * 1000, // 10 second timeout before restarting MathJax
    };


    //merge configurations into defaults
    const mergeConfig = function(conf, confDefaults) {
        for (let index in conf) {
            confDefaults[index] = conf[index];
        }
    };

    mergeConfig(configOptions, config);
    mergeConfig(typesetOptions, typesetConfig);

    // override output options with global option
    if (_outputJax.indexOf(config.output) > -1) {
        for (let jax of _outputJax) {
            typesetConfig[jax] = (jax === config.output);
        }
    }

    // generate css for html and svg outputs, if global css option is provided
    if (config.cssInline && (typesetConfig['svg'] || typesetConfig['html'])) {
        typesetConfig['css'] = true;
    }

    // Create jsdom options (cf. defaults for config.jsdom)
    const jsdomConfig = {
        runScripts: config.jsdom.runScript,
    };
    // translate 'true' option
    if (config.jsdom.virtualConsole === true) {
        config.jsdom.virtualConsole = new jsdom.VirtualConsole();
        config.jsdom.virtualConsole.sendTo(console);
    }

    // set up DOM basics
    const doc = new JSDOM(htmlstring, config.jsdom);
    const window = doc.window;
    const document = window.document;

    //rewrite custom scripts types from core MathJax
    const rewriteScripts = function(oldType, newType) {
        const scripts = document.querySelectorAll('script[type="' + oldType + '"]');
        for (let script of scripts) script.setAttribute('type', newType);
    };
    rewriteScripts('math/tex', 'math/inline-TeX');
    rewriteScripts('math/tex; mode=display', 'math/TeX');
    rewriteScripts('math/asciimath', 'math/asciiMath');

    // configure mathjax-node
    mathjax.config(config);

    // configure and pre-process
    if (config.format.indexOf('MathML') > -1) {
        window.mathml = mathml;
        window.mathml.config.doc = document;
        window.mathml.PreProcess();
    }
    // HACK clone configuration cf #22
    tex.config = JSON.parse(texconfig);
    if (config.format.indexOf('TeX') > -1) {
        if (config.MathJax.tex2jax) {
            mergeConfig(config.MathJax.tex2jax, tex.config);
        }
        window.tex = tex;
        window.tex.config.doc = document;
        if (config.singleDollars) {
            window.tex.config.inlineMath.push(['$', '$']);
            window.tex.config.processEscapes = true;
        }
        window.tex.PreProcess();
    }
    // HACK clone configuration cf #22
    ascii.config = JSON.parse(asciiconfig);
    if (config.format.indexOf('AsciiMath') > -1) {
        if (config.MathJax.ascii2jax) {
            mergeConfig(config.MathJax.ascii2jax, ascii.config);
        }
        window.ascii = ascii;
        window.ascii.config.doc = document;
        window.ascii.PreProcess();
    }

    const scriptNodes = document.querySelectorAll(`
        script[type="math/TeX"],
        script[type="math/inline-TeX"],
        script[type="math/AsciiMath"],
        script[type="math/MathML"],
        script[type="math/MathML-block"]`
    );
    const scripts = Array.from(scriptNodes);
    // Move references to end of pile to allow forward-looking references
    scripts.forEach( (a, i) => {
        // TODO refine to handle everything but near-circular (i.e., "eq1 has reference to eq2 and vice versa") references
        if (a.textContent.includes('\\ref') || a.textContent.includes('\\eqref') ) scripts.push(scripts.splice(i, 1)[0]);
    })
    // prepare state for async execution
    this._parsedFormulasCache = [];
    this._outstandingHandlers = 0;

    // convert with mathjax-node (async launch)
    let index = 0;
    let script;
    // Start and run mathjax-node
    if(!_started) {
        mathjax.start();
        _started = true;
    }
    while (script = scripts[index]) {
        const conf = typesetConfig;
        const format = conf.format = script.getAttribute('type').slice(5);
        if (format === 'MathML-block') conf.format = 'MathML';
        conf.math = script.text;

        /**
         * @name ParsedFormula
         * @type Object
         * @proprety {number} id - index of formula on the page
         * @property {number} jobID - mjpage job ID; formulas belonging to the same page run have the same jobID
         * @proprety {string} node - DOM node with the formula (contents change before and after conversion)
         * @property {string} sourceFormula - the source formula
         * @property {string} sourceFormat - the source formula format (e.g. "inline-TeX")
         * @property {object} outputFormula - the converted formula result from mathjax-node typeset function;
         * use outputFormula[outputFormat] to get the resulting formula string
         * @property {string} outputFormat - the resulting formula format (e.g. "svg")
         */
        let parsedFormula = {
            id: index,
            jobID: this.id,
            node: script,  // has script element before manipulation
            sourceFormula: conf.math,
            sourceFormat: conf.format,
            outputFormula: null,
            outputFormat: this.getOutputProperty(conf)
        };
        conf.state.parsedFormula = parsedFormula; // for access from typeset callback
        this.emit("beforeConversion", parsedFormula);

        // create DOM wrapper
        const wrapper = document.createElement('span');
        if (format === 'TeX' || format === 'MathML-block') wrapper.className = 'mjpage mjpage__block';
        else wrapper.className = 'mjpage';
        script.parentNode.replaceChild(wrapper, script);

        typeset(conf, (result, options) => {  // async call
            if(!options) console.error("typeset function did not return options object needed for state keeping");
            let parsedFormula = options ? options.state.parsedFormula : result;
            if (result.errors) {
                console.error(`Formula ${parsedFormula.sourceFormula} contains the following errors:\n`, result.errors);
                this._outstandingHandlers--;
                return;
            }

            let prop = this.getOutputProperty(conf);
            if(_outputHandlers[prop]) {
                // user defined custom output handler (e.g. for png output)
                _outputHandlers[prop].call(this, wrapper, result[prop]);
            } else {
                // default handling is writing result to wrapper contents (e.g. for html, mml, svg outputs)
                wrapper.innerHTML = result[prop];
            }

            parsedFormula.outputFormula = result;
            parsedFormula.node = wrapper;
            this._parsedFormulasCache.push(parsedFormula);
            // Since this call is async, decrease the counter of async operations to make sure all formulas are processed
            this._outstandingHandlers--;

            this.emit("afterConversion", parsedFormula);
            if (this._outstandingHandlers === 0) {
                this.emit('ready');
            }
        });

        this._outstandingHandlers++;
        index++;
    }

    // when all formulas are parsed, relies on ready event internally to invoke the cb
    this.once('ready', () => {
        // a dummy call to wait for mathjax-node to finish
        const conf = typesetConfig;
        conf.format = 'TeX';
        if(!conf.math) conf.math = '';
        typeset(conf, (result) => {
            // NOTE cf https://github.com/mathjax/MathJax-node/issues/283
            if (index > 0) {
                if (typesetConfig.svg && !typesetConfig.png) result.css = `
                            .mjpage .MJX-monospace {
                            font-family: monospace
                            }

                            .mjpage .MJX-sans-serif {
                            font-family: sans-serif
                            }

                            .mjpage {
                            display: inline;
                            font-style: normal;
                            font-weight: normal;
                            line-height: normal;
                            font-size: 100%;
                            font-size-adjust: none;
                            text-indent: 0;
                            text-align: left;
                            text-transform: none;
                            letter-spacing: normal;
                            word-spacing: normal;
                            word-wrap: normal;
                            white-space: nowrap;
                            float: none;
                            direction: ltr;
                            max-width: none;
                            max-height: none;
                            min-width: 0;
                            min-height: 0;
                            border: 0;
                            padding: 0;
                            margin: 0
                            }

                            .mjpage * {
                            transition: none;
                            -webkit-transition: none;
                            -moz-transition: none;
                            -ms-transition: none;
                            -o-transition: none
                            }

                            .mjx-svg-href {
                            fill: blue;
                            stroke: blue
                            }

                            .MathJax_SVG_LineBox {
                            display: table!important
                            }

                            .MathJax_SVG_LineBox span {
                            display: table-cell!important;
                            width: 10000em!important;
                            min-width: 0;
                            max-width: none;
                            padding: 0;
                            border: 0;
                            margin: 0
                            }

                            .mjpage__block {
                            text-align: center;
                            margin: 1em 0em;
                            position: relative;
                            display: block!important;
                            text-indent: 0;
                            max-width: none;
                            max-height: none;
                            min-width: 0;
                            min-height: 0;
                            width: 100%
                            }`;
                if (result.css && config.cssInline) {
                    let styles = document.createElement('style');
                    styles.setAttribute('type', 'text/css');
                    styles.appendChild(document.createTextNode(result.css));
                    document.head.appendChild(styles);
                }
                if (result.svg && typesetConfig.useGlobalCache) {
                    let globalSVG = document.createElementNS('http://www.w3.org/2000/svg', 'svg');
                     globalSVG.setAttribute('xmlns', 'http://www.w3.org/2000/svg');
                     globalSVG.style.display = 'none';
                    // TODO `globalSVG.appendChild(document.importNode(state.defs,true))` throws error
                    // `globablSVG.appendChild(mjstate.defs)`` throws WrongDocumentError so above seems correct
                    globalSVG.innerHTML = mjstate.defs.outerHTML;
                    document.body.appendChild(globalSVG);
                }
            }

            // clear cache
            delete this._parsedFormulasCache;
            delete this._outstandingHandlers;
            _started = false;

            this.emit('beforeSerialization', document, result.css);
            let output = '';
            if (config.fragment) output = document.body.innerHTML;
            else output = doc.serialize();
            window.close();
            callback(output);

            // prevent memory leaks
            this.removeAllListeners('beforeConversion')
                .removeAllListeners('afterConversion')
                .removeAllListeners('beforeSerialization');
        });
    });

    // no formulas to parse, hence call ready event handler immediately
    if (index === 0) {
        this.emit('ready');
    }

    return this;
};

MjPageJob.prototype.getOutputProperty = function (conf) {
    let res;
    for (let prop of _outputJax) {
        if(conf[prop]) {
            res = prop;
        }
    }

    return res;
};

/**
 * Add new output option and, optionally, assign an output handler for writing result to a DOM node.
 * Can be used to customize DOM result for default outputs, i.e. "html", "svg", "mml".
 * @param output {string} - new output option for mathjax-node (e.g. "png" if you are using mathjax-node-svg2png)
 * @param [handler] {function} - function that takes wrapper DOM element and mjnode conversion result and
 * modifies the DOM element. For example, the following is valid handler: (wrapper, data) => wrapper.innerHTML = data.
 */
exports.addOutput = function (output, handler) {
    if(!_outputJax.includes(output)) {
        _outputJax.push(output);
    }

    if(handler && handler instanceof Function) {
        _outputHandlers[output] = handler;
    }

    return this;
};

/**
 * Initialize mathjax-node-page instance with appropriate mathjax-node.
 * Call when no active tasks are running on mathjax-node.
 * @param [MjNode] {object} - pass custom mathjax-node instance; leave empty for default mathjax-node
 */
exports.init = function (MjNode) {
    if(_started) {
        console.error(`mjpage was already initialized and is currently running.`);
        return;
    }

    mathjax = MjNode || require('mathjax-node');
    typeset = mathjax.typeset;
};

/**
 * Runs mathjax-node-page conversion.
 * @param htmlstring {string} - a string with HTML
 * @param configOptions {object} - specifies page-wide options
 * @param typesetOptions {object} - expects mathjax-node configuration options
 * @param callback {function} - called with output result upon completion
 * @returns {MjPageJob} - returns job instance, which is event emitter
 */
exports.mjpage = function (htmlstring, configOptions, typesetOptions, callback) {
    // init on the first run
    if(!mathjax) {
        exports.init();
    }

    let job = new MjPageJob(count++, {htmlstring, configOptions, typesetOptions}, callback);
    process.nextTick(() => job.run()); // need to run after returning the job to allow event handling
    return job;
};
