/* -*- Mode: Javascript; indent-tabs-mode:nil; js-indent-level: 2 -*- */
/* vim: set ts=2 et sw=2 tw=80: */

/*************************************************************
 *
 *  MathJax/extensions/CHTML-preview.js
 *  
 *  Backward compatibility with old CHTML-preview extension.
 *  
 *  ---------------------------------------------------------------------
 *  
 *  Copyright (c) 2014-2018 The MathJax Consortium
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

MathJax.Callback.Queue(
  ["Require",MathJax.Ajax,"[MathJax]/extensions/fast-preview.js"],
  ["loadComplete",MathJax.Ajax,"[MathJax]/extensions/CHTML-preview.js"]
);
