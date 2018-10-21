/* -*- Mode: Javascript; indent-tabs-mode:nil; js-indent-level: 2 -*- */
/* vim: set ts=2 et sw=2 tw=80: */

/*************************************************************
 *
 *  MathJax/extensions/TeX/newcommand.js
 *  
 *  Implements the \newcommand, \newenvironment and \def
 *  macros, and is loaded automatically when needed.
 *
 *  ---------------------------------------------------------------------
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

MathJax.Extension["TeX/newcommand"] = {
  version: "2.7.5"
};

MathJax.Hub.Register.StartupHook("TeX Jax Ready",function () {
  
  var TEX = MathJax.InputJax.TeX;
  var TEXDEF = TEX.Definitions;
  
  TEXDEF.Add({
    macros: {
      newcommand:       'NewCommand',
      renewcommand:     'NewCommand',
      newenvironment:   'NewEnvironment',
      renewenvironment: 'NewEnvironment',
      def:              'MacroDef',
      'let':            'Let'
    }
  },null,true);

  TEX.Parse.Augment({

    /*
     *  Implement \newcommand{\name}[n][default]{...}
     */
    NewCommand: function (name) {
      var cs = this.trimSpaces(this.GetArgument(name)),
          n  = this.GetBrackets(name),
          opt = this.GetBrackets(name),
          def = this.GetArgument(name);
      if (cs.charAt(0) === "\\") {cs = cs.substr(1)}
      if (!cs.match(/^(.|[a-z]+)$/i)) {
        TEX.Error(["IllegalControlSequenceName",
                   "Illegal control sequence name for %1",name]);
      }
      if (n) {
        n = this.trimSpaces(n);
        if (!n.match(/^[0-9]+$/)) {
          TEX.Error(["IllegalParamNumber",
                     "Illegal number of parameters specified in %1",name]);
        }
      }
      this.setDef(cs,['Macro',def,n,opt]);
    },
    
    /*
     *  Implement \newenvironment{name}[n][default]{begincmd}{endcmd}
     */
    NewEnvironment: function (name) {
      var env  = this.trimSpaces(this.GetArgument(name)),
          n    = this.GetBrackets(name),
          opt  = this.GetBrackets(name),
          bdef = this.GetArgument(name),
          edef = this.GetArgument(name);
      if (n) {
        n = this.trimSpaces(n);
        if (!n.match(/^[0-9]+$/)) {
          TEX.Error(["IllegalParamNumber",
                     "Illegal number of parameters specified in %1",name]);
        }
      }
      this.setEnv(env,['BeginEnv',[null,'EndEnv'],bdef,edef,n,opt]);
    },
    
    /*
     *  Implement \def command
     */
    MacroDef: function (name) {
      var cs     = this.GetCSname(name),
          params = this.GetTemplate(name,"\\"+cs),
          def    = this.GetArgument(name);
      if (!(params instanceof Array)) {this.setDef(cs,['Macro',def,params])}
        else {this.setDef(cs,['MacroWithTemplate',def].concat(params))}
    },
    
    /*
     *  Implements the \let command
     */
    Let: function (name) {
      var cs = this.GetCSname(name), macro;
      var c = this.GetNext(); if (c === "=") {this.i++; c = this.GetNext()}
      //
      //  All \let commands create entries in the macros array, but we
      //  have to look in the various mathchar and delimiter arrays if
      //  the source isn't a macro already, and attach the data to a
      //  macro with the proper routine to process it.
      //
      //  A command of the form \let\cs=char produces a macro equivalent
      //  to \def\cs{char}, which is as close as MathJax can get for this.
      //  So \let\bgroup={ is possible, but doesn't work as it does in TeX.
      //
      if (c === "\\") {
        name = this.GetCSname(name);
        macro = this.csFindMacro(name);
        if (!macro) {
          if (TEXDEF.mathchar0mi.hasOwnProperty(name))    {macro = ["csMathchar0mi",TEXDEF.mathchar0mi[name]]}  else
          if (TEXDEF.mathchar0mo.hasOwnProperty(name))    {macro = ["csMathchar0mo",TEXDEF.mathchar0mo[name]]}  else
          if (TEXDEF.mathchar7.hasOwnProperty(name))      {macro = ["csMathchar7",TEXDEF.mathchar7[name]]}      else 
          if (TEXDEF.delimiter.hasOwnProperty("\\"+name)) {macro = ["csDelimiter",TEXDEF.delimiter["\\"+name]]} else
          return;
        }
      } else {macro = ["Macro",c]; this.i++}
      this.setDef(cs,macro);
    },
    
    /*
     *  Get a CS name or give an error
     */
    GetCSname: function (cmd) {
      var c = this.GetNext();
      if (c !== "\\") {
        TEX.Error(["MissingCS",
                   "%1 must be followed by a control sequence", cmd])
      }
      var cs = this.trimSpaces(this.GetArgument(cmd));
      return cs.substr(1);
    },
    
    /*
     *  Get a \def parameter template
     */
    GetTemplate: function (cmd,cs) {
      var c, params = [], n = 0;
      c = this.GetNext(); var i = this.i;
      while (this.i < this.string.length) {
        c = this.GetNext();
        if (c === '#') {
          if (i !== this.i) {params[n] = this.string.substr(i,this.i-i)}
          c = this.string.charAt(++this.i);
          if (!c.match(/^[1-9]$/)) {
            TEX.Error(["CantUseHash2",
                       "Illegal use of # in template for %1",cs]);
          }
          if (parseInt(c) != ++n) {
            TEX.Error(["SequentialParam",
                       "Parameters for %1 must be numbered sequentially",cs]);
          }
          i = this.i+1;
        } else if (c === '{') {
          if (i !== this.i) {params[n] = this.string.substr(i,this.i-i)}
          if (params.length > 0) {return [n,params]} else {return n}
        }
        this.i++;
      }
      TEX.Error(["MissingReplacementString",
                 "Missing replacement string for definition of %1",cmd]);
    },
    
    /*
     *  Process a macro with a parameter template
     */
    MacroWithTemplate: function (name,text,n,params) {
      if (n) {
        var args = []; this.GetNext();
        if (params[0] && !this.MatchParam(params[0])) {
          TEX.Error(["MismatchUseDef",
                     "Use of %1 doesn't match its definition",name]);
        }
        for (var i = 0; i < n; i++) {args.push(this.GetParameter(name,params[i+1]))}
        text = this.SubstituteArgs(args,text);
      }
      this.string = this.AddArgs(text,this.string.slice(this.i));
      this.i = 0;
      if (++this.macroCount > TEX.config.MAXMACROS) {
        TEX.Error(["MaxMacroSub1",
                   "MathJax maximum macro substitution count exceeded; " +
                   "is there a recursive macro call?"]);
      }
    },
    
    /*
     *  Process a user-defined environment
     */
    BeginEnv: function (begin,bdef,edef,n,def) {
      if (n) {
        var args = [];
        if (def != null) {
          var optional = this.GetBrackets("\\begin{"+name+"}");
          args.push(optional == null ? def : optional);
        }
        for (var i = args.length; i < n; i++) {args.push(this.GetArgument("\\begin{"+name+"}"))}
        bdef = this.SubstituteArgs(args,bdef);
        edef = this.SubstituteArgs([],edef); // no args, but get errors for #n in edef
      }
      this.string = this.AddArgs(bdef,this.string.slice(this.i)); this.i = 0;
      return begin;
    },
    EndEnv: function (begin,bdef,edef,n) {
      var end = "\\end{\\end\\"+begin.name+"}"; // special version of \end for after edef
      this.string = this.AddArgs(edef,end+this.string.slice(this.i)); this.i = 0;
      return null;
    },
    
    /*
     *  Find a single parameter delimited by a trailing template
     */
    GetParameter: function (name,param) {
      if (param == null) {return this.GetArgument(name)}
      var i = this.i, j = 0, hasBraces = 0;
      while (this.i < this.string.length) {
        var c = this.string.charAt(this.i);
        if (c === '{') {
          if (this.i === i) {hasBraces = 1}
          this.GetArgument(name); j = this.i - i;
        } else if (this.MatchParam(param)) {
          if (hasBraces) {i++; j -= 2}
          return this.string.substr(i,j);
	} else if (c === "\\") {
	  this.i++; j++; hasBraces = 0;
	  var match = this.string.substr(this.i).match(/[a-z]+|./i);
	  if (match) {this.i += match[0].length; j = this.i - i}
        } else {
          this.i++; j++; hasBraces = 0;
        }
      }
      TEX.Error(["RunawayArgument","Runaway argument for %1?",name]);
    },
    
    /*
     *  Check if a template is at the current location.
     *  (The match must be exact, with no spacing differences.  TeX is
     *   a little more forgiving than this about spaces after macro names)
     */
    MatchParam: function (param) {
      if (this.string.substr(this.i,param.length) !== param) {return 0}
      if (param.match(/\\[a-z]+$/i) &&
          this.string.charAt(this.i+param.length).match(/[a-z]/i)) {return 0}
      this.i += param.length;
      return 1;
    }
    
  });
  
  TEX.Environment = function (name) {
    TEXDEF.environment[name] = ['BeginEnv',[null,'EndEnv']].concat([].slice.call(arguments,1));
    TEXDEF.environment[name].isUser = true;
  }

  MathJax.Hub.Startup.signal.Post("TeX newcommand Ready");

});

MathJax.Ajax.loadComplete("[MathJax]/extensions/TeX/newcommand.js");
