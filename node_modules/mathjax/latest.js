/*
 *  /MathJax/latest.js
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

(function(){var h={"cdnjs.cloudflare.com":{api:"https://api.cdnjs.com/libraries/mathjax?fields=version",version:"version",mathjax:"https://cdnjs.cloudflare.com/ajax/libs/mathjax/"},"cdn.rawgit.com":{api:"https://api.github.com/repos/mathjax/mathjax/releases/latest",version:"tag_name",mathjax:"https://cdn.rawgit.com/mathjax/MathJax/"},"cdn.jsdelivr.net":{api:"https://api.jsdelivr.com/v1/jsdelivr/libraries?name=mathjax&lastversion=*",version:"lastversion",mathjax:"https://cdn.jsdelivr.net/mathjax/"}};function g(q){if(console&&console.log){console.log(q)}}function e(){if(document.currentScript){return document.currentScript}var r=document.getElementsByTagName("script");for(var v=0,q=r.length;v<q;v++){var t=r[v];for(var s in h){if(h.hasOwnProperty(s)){var u=h[s].mathjax;if(t.src&&t.src.substr(0,u.length)===u){return t}}}}}function a(r){if(!r){return}var q=r.src.replace(/https:\/\//,"").replace(/[\/\?].*/,"");return h[q]}var l=/(?:^|;\s*)mjx\.latest=([^;]*)(?:;|$)/;function d(){var q;try{q=l.exec(document.cookie)}catch(r){}if(q&&q[1]!==""){return q[1]}}function c(q){cookie="mjx.latest="+q;var s=new Date();s.setDate(s.getDate()+7);cookie+="; expires="+s.toGMTString();cookie+="; path=/";try{document.cookie=cookie}catch(r){}}function j(){if(window.XMLHttpRequest){return new XMLHttpRequest()}if(window.ActiveXObject){try{return new ActiveXObject("Msxml2.XMLHTTP")}catch(q){}try{return new ActiveXObject("Microsoft.XMLHTTP")}catch(q){}}}function o(r){var q=document.createElement("script");q.type="text/javascript";q.async=true;q.src=r;var s=document.head||document.getElementsByTagName("head")[0]||document.body;if(s){s.appendChild(q)}else{g("Can't find the document <head> element")}}function i(){var q=e();if(q){o(q.src.replace(/\/latest\.js/,"/MathJax.js"))}else{g("Can't determine the URL for loading MathJax")}}function m(q,r,s){var t=j();if(t){t.onreadystatechange=function(){if(t.readyState===4){if(t.status===200){var v=JSON.parse(t.responseText);if(v instanceof Array){v=v[0]}var u=v[q.version];if(u.substr(0,2)==="2."){c(u);o(q.mathjax+v[q.version]+s+"/MathJax.js"+r);return}}else{g("Problem acquiring MathJax version: status = "+t.status)}i()}};t.open("GET",q.api,true);t.send(null)}else{g("Can't create XMLHttpRequest object");i()}}var n=e();var p=a(n);if(p){var b=n.src.replace(/.*?(\?|$)/,"$1");b+=(b?"&":"?")+"latest";var f=(n.src.match(/\/unpacked\/latest\.js/)?"/unpacked":"");var k=d();if(k){o(p.mathjax+k+f+"/MathJax.js"+b)}else{m(p,b,f)}}else{i()}})();
