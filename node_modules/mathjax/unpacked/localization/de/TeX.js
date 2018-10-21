/*************************************************************
 *
 *  MathJax/localization/de/TeX.js
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
MathJax.Localization.addTranslation("de","TeX",{
        version: "2.7.5",
        isLoaded: true,
        strings: {
          ExtraOpenMissingClose: "Zus\u00E4tzliche \u00F6ffnende, oder fehlende schlie\u00DFende Klammer",
          ExtraCloseMissingOpen: "Zus\u00E4tzliche schlie\u00DFende, oder fehlende \u00F6ffnende Klammer",
          MissingLeftExtraRight: "Fehlendes '\\left' oder zus\u00E4tzliches '\\right'",
          MissingScript: "Fehlendes Argument im Hoch- oder Tiefstellen",
          ExtraLeftMissingRight: "Zus\u00E4tzliches '\\left' oder fehlendes '\\right'",
          Misplaced: "%1 falsch gesetzt",
          MissingOpenForSub: "Fehlende \u00F6ffnende Klammer beim Tiefstellen",
          MissingOpenForSup: "Fehlende \u00F6ffnende Klammer beim Hochstellen",
          AmbiguousUseOf: "Mehrdeutige Verwendung von %1",
          EnvBadEnd: "\\begin{%1} endet mit \\end{%2}",
          EnvMissingEnd: "\\end{%1} fehlt",
          MissingBoxFor: "Fehlender Rahmen f\u00FCr: %1",
          MissingCloseBrace: "Fehlende schlie\u00DFende Klammer",
          UndefinedControlSequence: "Nicht definierter Befehl: %1",
          DoubleExponent: "Doppeltes Hochstellen: Klammern f\u00FCr eine eindeutige Zuordnung verwenden",
          DoubleSubscripts: "Doppeltes Tiefstellen: Klammern f\u00FCr eine eindeutige Zuordnung verwenden",
          DoubleExponentPrime: "Prime f\u00FChrt zu doppeltem Hochstellen: Klammern f\u00FCr eine eindeutige Zuordnung verwenden",
          CantUseHash1: "Das Zeichen '#' ist ein Makroparameter und kann nicht im Mathematikmodus verwendet werden.",
          MisplacedMiddle: "%1 muss zwischen '\\left' und '\\right' stehen",
          MisplacedLimits: "%1 ist nur bei Operatoren erlaubt",
          MisplacedMoveRoot: "%1 muss innerhalb einer Wurzel stehen",
          MultipleCommand: "Zu viele %1",
          IntegerArg: "Das Argument in %1 muss ganzzahlig sein",
          NotMathMLToken: "%1 ist kein Token-Element",
          InvalidMathMLAttr: "Unzul\u00E4ssiges MathML-Attribut: %1",
          UnknownAttrForElement: "%1 ist kein zul\u00E4ssiges Attribut f\u00FCr %2",
          MaxMacroSub1: "Maximale Anzahl an Makro-Ersetzungen ist erreicht; wird ein rekursiver Makroaufruf verwendet?",
          MaxMacroSub2: "Maximale Anzahl an Ersetzungen ist erreicht; wird eine rekursive LaTeX-Umgebung verwendet?",
          MissingArgFor: "Fehlendes Argument in %1",
          ExtraAlignTab: "Zus\u00E4tzlicher Ausrichtungstabulator im '\\cases' Text",
          BracketMustBeDimension: "Das Klammer-Argument f\u00FCr %1 muss eine Dimension sein",
          InvalidEnv: "Ung\u00FCltiger Umgebungsname: \u201E%1\u201C",
          UnknownEnv: "Ung\u00FCltige Umgebung: \u201E%1\u201C",
          ExtraCloseLooking: "Zus\u00E4tzliche schlie\u00DFende Klammer w\u00E4hrend der Suche nach %1",
          MissingCloseBracket: "Argument zu %1 wurde nicht mit ']' geschlossen",
          MissingOrUnrecognizedDelim: "Fehlendes oder nicht erkanntes Begrenzungszeichen bei %1",
          MissingDimOrUnits: "Fehlende Dimension oder Einheiten bei %1",
          TokenNotFoundForCommand: "Konnte %1 nicht f\u00FCr %2 finden",
          MathNotTerminated: "Mathematischer Ausdruck im Textfeld nicht abgeschlossen",
          IllegalMacroParam: "Ung\u00FCltiger Makroparameterbezug",
          MaxBufferSize: "Interne Puffergr\u00F6\u00DFe \u00FCberschritten; wird ein rekursiver Makroaufruf verwendet?",
          CommandNotAllowedInEnv: "%1 ist in der Umgebung %2 nicht erlaubt",
          MultipleLabel: "Bezeichner '%1' mehrfach definiert",
          CommandAtTheBeginingOfLine: "%1 muss am Zeilenanfang stehen",
          IllegalAlign: "Ung\u00FCltige Ausrichtung in %1",
          BadMathStyleFor: "Falsches \u201Emath style\u201C-Argument: %1",
          PositiveIntegerArg: "Das Argument zu %1 muss eine positive Ganzzahl sein",
          ErroneousNestingEq: "Fehlerhafte Verschachtelung von Gleichungen",
          MultlineRowsOneCol: "Zeilen in der %1-Umgebung m\u00FCssen genau eine Spalte haben",
          MultipleBBoxProperty: "%1 wurde zweimal in %2 angegeben",
          InvalidBBoxProperty: "'%1' scheint keine Farbe, Abstands-Dimension oder Stil zu sein",
          ExtraEndMissingBegin: "Zus\u00E4tzliches %1 oder fehlendes \\begingroup",
          GlobalNotFollowedBy: "'%1' nicht von '\\let', '\\def' oder '\\newcommand' gefolgt",
          UndefinedColorModel: "Farbmodell '%1' nicht definiert",
          ModelArg1: "Farbwerte f\u00FCr Farbmodell '%1' ben\u00F6tigen 3 Werte",
          InvalidDecimalNumber: "Ung\u00FCltige Dezimalzahl",
          ModelArg2: "Farbwerte f\u00FCr Farbmodell '%1' m\u00FCssen zwischen %2 und %3 liegen",
          InvalidNumber: "Ung\u00FCltige Zahl",
          NewextarrowArg1: "Das erste Argument von %1 muss Name einer Befehlsfolge sein",
          NewextarrowArg2: "Zweites Argument von %1 m\u00FCssen zwei ganze Zahlen sein, durch Komma getrennt",
          NewextarrowArg3: "Das dritte Argument von %1 muss die Nummer eines Unicode-Zeichens sein",
          NoClosingChar: "Kann schlie\u00DFende %1 nicht finden",
          IllegalControlSequenceName: "Ung\u00FCltige Befehlsfolge f\u00FCr %1",
          IllegalParamNumber: "Ung\u00FCltige Anzahl von Parametern in %1",
          MissingCS: "%1 muss von Befehlsfolge gefolgt werden",
          CantUseHash2: "Ung\u00FCltige Verwendung von # in Definition von %1",
          SequentialParam: "Parameter von %1 m\u00FCssen fortlaufend nummeriert sein",
          MissingReplacementString: "Ersetzende Zeichenkette f\u00FCr Definition von %1 fehlt",
          MismatchUseDef: "Verwendung von %1 passt nicht zur Definition",
          RunawayArgument: "Nichtgeschlossenes Argument f\u00FCr %1?",
          NoClosingDelim: "Kein schlie\u00DFendes Begrenzungszeichen f\u00FCr %1 gefunden"
        }
});

MathJax.Ajax.loadComplete("[MathJax]/localization/de/TeX.js");
