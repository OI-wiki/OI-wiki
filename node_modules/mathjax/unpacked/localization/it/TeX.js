/*************************************************************
 *
 *  MathJax/localization/it/TeX.js
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
MathJax.Localization.addTranslation("it","TeX",{
        version: "2.7.5",
        isLoaded: true,
        strings: {
          ExtraOpenMissingClose: "Graffa d'apertura in pi\u00F9 o di chiusura mancante",
          ExtraCloseMissingOpen: "Graffa di chiusura in pi\u00F9 o d'apertura mancante",
          MissingLeftExtraRight: "Comando \\left mancante oppure \\right extra",
          MissingScript: "Argomento per l'esponente o per l'indice mancante",
          ExtraLeftMissingRight: "Comando \\left extra oppure \\right mancante",
          Misplaced: "%1 mal posizionato",
          MissingOpenForSub: "Graffa d'apertura per l'indice mancante",
          MissingOpenForSup: "Graffa d'apertura per l'esponente mancante",
          AmbiguousUseOf: "Uso ambiguo di %1",
          EnvBadEnd: "\\begin{%1} terminato con \\end{%2}",
          EnvMissingEnd: "\\end{%1} mancante",
          MissingBoxFor: "Box per %1 mancante",
          MissingCloseBrace: "Graffa di chiusura mancante",
          UndefinedControlSequence: "Sequenza di controllo %1 indefinita",
          DoubleExponent: "Esponente doppio: usa le parentesi per distinguerli",
          DoubleSubscripts: "Doppio indice: usa le parentesi per distinguerli",
          DoubleExponentPrime: "Simbolo di primo visto come secondo esponente: usa le parentesi per chiarire",
          CantUseHash1: "Non puoi usare il carattere # come parametro delle macro in modalit\u00E1 matematica",
          MisplacedMiddle: "%1 deve trovarsi tra \\left e \\right",
          MisplacedLimits: "%1 \u00E8 consentito solo con operatori",
          MisplacedMoveRoot: "%1 pu\u00F2 appare solo sotto radice",
          MultipleCommand: "%1 multipli",
          IntegerArg: "L'argomento di %1 deve essere un intero",
          NotMathMLToken: "%1 non \u00E8 un token",
          InvalidMathMLAttr: "Attributo MathML non valido: %1",
          UnknownAttrForElement: "%1 non \u00E8 un attributo riconosciuto per %2",
          MaxMacroSub1: "Numero massimo per le sostituzioni di macro superato da MathJax; forse una chiamata di macro ricorsiva?",
          MaxMacroSub2: "Numero massimo per le sostituzioni superato da MathJax; forse un'ambiente LaTeX ricorsivo?",
          MissingArgFor: "Argomento di %1 mancante",
          ExtraAlignTab: "Tabulazione d'allineamento extra nel testo di \\cases",
          BracketMustBeDimension: "L'argomento tra parentesi per %1 deve essere una dimensione",
          InvalidEnv: "Nome d'ambiente non valido '%1'",
          UnknownEnv: "Ambiente sconosciuto '%1'",
          ExtraCloseLooking: "Graffa di chiusura extra durante la ricerca di %1",
          MissingCloseBracket: "Parentesi ] per l'argomento di %1 non trovata",
          MissingOrUnrecognizedDelim: "Delimitatore per %1 mancante o non riconosciuto",
          MissingDimOrUnits: "Dimensione o sue unit\u00E1 mancanti per %1",
          TokenNotFoundForCommand: "Impossibile trovare %1 per %2",
          MathNotTerminated: "Formula non terminata in box di testo",
          IllegalMacroParam: "Riferimento a un parametro di macro illegale",
          MaxBufferSize: "Dimensione del buffer interno di MathJax superato; chiamata di macro ricorsiva?",
          CommandNotAllowedInEnv: "%1 non \u00E8 consentito nell'ambiente %2",
          MultipleLabel: "Etichetta '%1' definita pi\u00F9 volte",
          CommandAtTheBeginingOfLine: "%1 deve trovarsi all'inizio della riga",
          IllegalAlign: "Allineamento specificato in %1 illegale",
          BadMathStyleFor: "Stile math inadatto a %1",
          PositiveIntegerArg: "L'argomento di %1 deve essere un intero positivo",
          ErroneousNestingEq: "Annidamento di strutture di equazioni errato",
          MultlineRowsOneCol: "Le righe nell'ambiente %1 devono avere esattamente una colonna",
          MultipleBBoxProperty: "%1 specificato due volte in %2",
          InvalidBBoxProperty: "'%1' non sembra un colore, una spaziatura o uno stile",
          ExtraEndMissingBegin: "%1 extra oppure \\begingroup mancante",
          GlobalNotFollowedBy: "%1 non seguito da \\let, \\def o \\newcommand",
          UndefinedColorModel: "Modello colore '%1' non definito",
          ModelArg1: "I valori di colore per il modello %1 richiedono tre numeri",
          InvalidDecimalNumber: "Numero decimale non valido",
          ModelArg2: "I valori di colore per il modello %1 devono essere compresi tra %2 e %3",
          InvalidNumber: "Numero non valido",
          NewextarrowArg1: "Il primo argomento di %1 deve essere il nome di una sequenza di controllo",
          NewextarrowArg2: "Il secondo argomento di %1 devono essere due numeri separati da una virgola",
          NewextarrowArg3: "Il terzo argomento di %1 deve essere un codice di un carattere unicode",
          NoClosingChar: "Impossibile trovare la parentesi di chiusura %1",
          IllegalControlSequenceName: "Nome sequenza di controllo illegale per %1",
          IllegalParamNumber: "Numero di parametri specificato in %1 illegale",
          MissingCS: "%1 deve essere seguito da una sequenza di controllo",
          CantUseHash2: "Uso di # non consentito nel modello di %1",
          SequentialParam: "I parametri per %1 devono essere numerati consecutivamente",
          MissingReplacementString: "Stringa di sostituzione per la definizione di %1 mancante",
          MismatchUseDef: "L'uso di %1 non combacia con la sua definizione",
          RunawayArgument: "Perso un argomento per %1?",
          NoClosingDelim: "Impossibile trovare delimitatore di chiusura per %1"
        }
});

MathJax.Ajax.loadComplete("[MathJax]/localization/it/TeX.js");
