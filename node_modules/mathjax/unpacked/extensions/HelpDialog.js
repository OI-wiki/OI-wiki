/*************************************************************
 *
 *  MathJax/extensions/HelpDialog.js
 *  
 *  Implements the MathJax Help dialog box.
 *
 *  ---------------------------------------------------------------------
 *  
 *  Copyright (c) 2013-2018 The MathJax Consortium
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

(function (HUB,HTML,AJAX,OUTPUT,LOCALE) {

  var HELP = MathJax.Extension.Help = {
    version: "2.7.5"
  };

  var STIXURL = "http://www.stixfonts.org/";
  var MENU = MathJax.Menu;
  var FALSE, KEY;
  HUB.Register.StartupHook("MathEvents Ready",function () {
    FALSE = MathJax.Extension.MathEvents.Event.False;
    KEY = MathJax.Extension.MathEvents.Event.KEY;
  });

  
  var CONFIG = HUB.CombineConfig("HelpDialog",{

    styles: {
      "#MathJax_Help": {
        position:"fixed", left:"50%", width:"auto", "max-width": "90%", "text-align":"center",
        border:"3px outset", padding:"1em 2em", "background-color":"#DDDDDD", color:"black",
        cursor: "default", "font-family":"message-box", "font-size":"120%",
        "font-style":"normal", "text-indent":0, "text-transform":"none",
        "line-height":"normal", "letter-spacing":"normal", "word-spacing":"normal",
        "word-wrap":"normal", "white-space":"wrap", "float":"none", "z-index":201,

        "border-radius": "15px",                     // Opera 10.5 and IE9
        "-webkit-border-radius": "15px",             // Safari and Chrome
        "-moz-border-radius": "15px",                // Firefox
        "-khtml-border-radius": "15px",              // Konqueror

        "box-shadow":"0px 10px 20px #808080",         // Opera 10.5 and IE9
        "-webkit-box-shadow":"0px 10px 20px #808080", // Safari 3 and Chrome
        "-moz-box-shadow":"0px 10px 20px #808080",    // Forefox 3.5
        "-khtml-box-shadow":"0px 10px 20px #808080",  // Konqueror
        filter: "progid:DXImageTransform.Microsoft.dropshadow(OffX=2, OffY=2, Color='gray', Positive='true')" // IE
      },
      "#MathJax_Help.MathJax_MousePost": {
        outline:"none"
      },
      
      "#MathJax_HelpContent": {
        overflow:"auto", "text-align":"left", "font-size":"80%",
        padding:".4em .6em", border:"1px inset", margin:"1em 0px",
        "max-height":"20em", "max-width":"30em", "background-color":"#EEEEEE"
      },
      
      "#MathJax_HelpClose": {
        position:"absolute", top:".2em", right:".2em",
        cursor:"pointer",
        display:"inline-block",
        border:"2px solid #AAA",
        "border-radius":"18px",
        "-webkit-border-radius": "18px",             // Safari and Chrome
        "-moz-border-radius": "18px",                // Firefox
        "-khtml-border-radius": "18px",              // Konqueror
        "font-family":"'Courier New',Courier",
        "font-size":"24px",
        color:"#F0F0F0"
      },
      "#MathJax_HelpClose span": {
        display:"block", "background-color":"#AAA", border:"1.5px solid",
        "border-radius":"18px",
        "-webkit-border-radius": "18px",             // Safari and Chrome
        "-moz-border-radius": "18px",                // Firefox
        "-khtml-border-radius": "18px",              // Konqueror
        "line-height":0, 
        padding:"8px 0 6px"     // may need to be browser-specific
      },
      "#MathJax_HelpClose:hover": {
        color:"white!important",
        border:"2px solid #CCC!important"
      },
      "#MathJax_HelpClose:hover span": {
        "background-color":"#CCC!important"
      },
      "#MathJax_HelpClose:hover:focus": {
        outline:"none"
      }
    }
  });
  
  /*
   *  Handle the Help Dialog box
   */
  HELP.Dialog = function (event) {
    LOCALE.loadDomain("HelpDialog",["Post",HELP,event]);
  };
  
  HELP.Post = function (event) {
    this.div = MENU.Background(this);
    var help = HTML.addElement(this.div,"div",{
      id: "MathJax_Help", tabIndex: 0, onkeydown: HELP.Keydown
    },LOCALE._("HelpDialog",[
      ["b",{style:{fontSize:"120%"}},[["Help","MathJax Help"]]],
      ["div",{id: "MathJax_HelpContent", tabIndex: 0},[
        ["p",{},[["MathJax",
          "*MathJax* is a JavaScript library that allows page authors to include " +
          "mathematics within their web pages.  As a reader, you don't need to do " +
          "anything to make that happen."]]
        ],
        ["p",{},[["Browsers",
          "*Browsers*: MathJax works with all modern browsers including IE6+, Firefox 3+, " +
          "Chrome 0.2+, Safari 2+, Opera 9.6+ and most mobile browsers."]]
        ],
        ["p",{},[["Menu",
          "*Math Menu*: MathJax adds a contextual menu to equations.  Right-click or " +
          "CTRL-click on any mathematics to access the menu."]]
        ],
        ["div",{style:{"margin-left":"1em"}},[
          ["p",{},[["ShowMath",
            "*Show Math As* allows you to view the formula's source markup " +
            "for copy & paste (as MathML or in its original format)."]]
          ],
          ["p",{},[["Settings",
            "*Settings* gives you control over features of MathJax, such as the " +
            "size of the mathematics, and the mechanism used to display equations."]]
          ],
          ["p",{},[["Language",
            "*Language* lets you select the language used by MathJax for its menus " +
            "and warning messages."]]
          ],
        ]],
        ["p",{},[["Zoom",
          "*Math Zoom*: If you are having difficulty reading an equation, MathJax can " +
          "enlarge it to help you see it better."]]
        ],
        ["p",{},[["Accessibilty",
          "*Accessibility*: MathJax will automatically work with screen readers to make " +
          "mathematics accessible to the visually impaired."]]
        ],
        ["p",{},[["Fonts",
          "*Fonts*: MathJax will use certain math fonts if they are installed on your " +
          "computer; otherwise, it will use web-based fonts.  Although not required, " +
          "locally installed fonts will speed up typesetting.  We suggest installing " +
          "the [STIX fonts](%1).",STIXURL]]
        ]
      ]],
      ["a",{href:"http://www.mathjax.org/"},["www.mathjax.org"]],
      ["span",{id: "MathJax_HelpClose", onclick: HELP.Remove,
               onkeydown: HELP.Keydown, tabIndex: 0, role: "button",
	       "aria-label": LOCALE._(["HelpDialog","CloseDialog"],"Close help dialog")},
        [["span",{},["\u00D7"]]]
      ]
    ]));
    if (event.type === "mouseup") help.className += " MathJax_MousePost";
    help.focus();
    LOCALE.setCSS(help);
    var doc = (document.documentElement||{});
    var H = window.innerHeight || doc.clientHeight || doc.scrollHeight || 0;
    if (MENU.prototype.msieAboutBug) {
      help.style.width = "20em"; help.style.position = "absolute";
      help.style.left = Math.floor((document.documentElement.scrollWidth - help.offsetWidth)/2)+"px";
      help.style.top = (Math.floor((H-help.offsetHeight)/3)+document.body.scrollTop)+"px";
    } else {
      help.style.marginLeft = Math.floor(-help.offsetWidth/2)+"px";
      help.style.top = Math.floor((H-help.offsetHeight)/3)+"px";
    }
  };
  HELP.Remove = function (event) {
    if (HELP.div) {document.body.removeChild(HELP.div); delete HELP.div}
  };
  HELP.Keydown = function(event) {
    if (event.keyCode === KEY.ESCAPE ||
        (this.id === "MathJax_HelpClose" &&
         (event.keyCode === KEY.SPACE || event.keyCode === KEY.RETURN))) {
      HELP.Remove(event);
      MENU.CurrentNode().focus();
      FALSE(event);
    }
  },

  MathJax.Callback.Queue(
    HUB.Register.StartupHook("End Config",{}), // wait until config is complete
    ["Styles",AJAX,CONFIG.styles],
    ["Post",HUB.Startup.signal,"HelpDialog Ready"],
    ["loadComplete",AJAX,"[MathJax]/extensions/HelpDialog.js"]
  );

})(MathJax.Hub,MathJax.HTML,MathJax.Ajax,MathJax.OutputJax,MathJax.Localization);
