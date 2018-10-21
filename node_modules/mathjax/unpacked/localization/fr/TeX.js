/*************************************************************
 *
 *  MathJax/localization/fr/TeX.js
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
MathJax.Localization.addTranslation("fr","TeX",{
        version: "2.7.5",
        isLoaded: true,
        strings: {
          ExtraOpenMissingClose: "Accolade ouvrante superflue ou accolade fermante manquante",
          ExtraCloseMissingOpen: "Accolade fermante superflue ou accolade ouvrante manquante",
          MissingLeftExtraRight: "Commande \\left manquante ou commande \\right superflue",
          MissingScript: "Argument en exposant ou en indice manquant",
          ExtraLeftMissingRight: "Commande \\left superflue ou commande \\right manquante",
          Misplaced: "Mauvaise position pour la commande %1",
          MissingOpenForSub: "Accolade ouvrante manquante pour le script en indice",
          MissingOpenForSup: "Accolade ouvrante manquante pour le script en exposant",
          AmbiguousUseOf: "Usage ambigu de la commande %1",
          EnvBadEnd: "\\begin{%1} s'est termin\u00E9 par un \\end{%2}",
          EnvMissingEnd: "\\end{%1} manquant",
          MissingBoxFor: "Boite manquante pour la commande %1",
          MissingCloseBrace: "Accolade fermante manquante",
          UndefinedControlSequence: "S\u00E9quence de contr\u00F4le %1 non d\u00E9finie",
          DoubleExponent: "Double exposant : utilisez des accolades pour clarifier",
          DoubleSubscripts: "Double indice : utilisez des accolades pour clarifier",
          DoubleExponentPrime: "Un prime entra\u00EEne un double exposant : utilisez des accolades pour clarifier",
          CantUseHash1: "Vous ne pouvez pas utilisez le caract\u00E8re #, indiquant un param\u00E8tre de macro, dans le mode math\u00E9matique",
          MisplacedMiddle: "La commande %1 doit \u00EAtre plac\u00E9e \u00E0 l\u2019int\u00E9rieur d\u2019une section \\left ... \\right",
          MisplacedLimits: "La commande %1 n'est autoris\u00E9e que sur les op\u00E9rateurs",
          MisplacedMoveRoot: "La commande %1 n'est autoris\u00E9e qu'\u00E0 l'int\u00E9rieur d'une racine",
          MultipleCommand: "Usage multiple de la commande %1",
          IntegerArg: "L\u2019argument de la commande %1 doit \u00EAtre un entier",
          NotMathMLToken: "L'\u00E9l\u00E9ment %1 n'est pas un \u00E9l\u00E9ment MathML \u00E9l\u00E9mentaire",
          InvalidMathMLAttr: "Attribut MathML non valide: %1",
          UnknownAttrForElement: "Attribut %1 inconnu pour l'\u00E9l\u00E9ment %2",
          MaxMacroSub1: "Le nombre maximal de substitutions de macro autoris\u00E9 par MathJax a \u00E9t\u00E9 d\u00E9pass\u00E9. Y a-t-il un appel de macro r\u00E9cursif?",
          MaxMacroSub2: "Le nombre maximal de substitutions de macros autoris\u00E9 par MathJax a \u00E9t\u00E9 d\u00E9pass\u00E9. Y a-t-il un environnement LaTeX r\u00E9cursif\u202F?",
          MissingArgFor: "Argument manquant pour la commande %1",
          ExtraAlignTab: "Caract\u00E8re d'alignement '\u0026' inattendu pour le texte de la commande \\cases",
          BracketMustBeDimension: "L'argument entre crochets de la commande %1 doit \u00EAtre une dimension",
          InvalidEnv: "Nom d'environnement '%1' non valide",
          UnknownEnv: "Environnement '%1' inconnu",
          ExtraCloseLooking: "Accolade fermante superflue lors de la recherche de %1",
          MissingCloseBracket: "Impossible de trouver ']' pour l'argument de la commande %1",
          MissingOrUnrecognizedDelim: "D\u00E9limiteur manquant ou non reconnu pour la commande %1",
          MissingDimOrUnits: "Dimension ou unit\u00E9s manquantes pour la commande %1",
          TokenNotFoundForCommand: "Impossible de trouver %1 pour la commande %2",
          MathNotTerminated: "Expression math\u00E9matique non termin\u00E9e \u00E0 l'int\u00E9rieur de la boite de texte",
          IllegalMacroParam: "Param\u00E8tre de r\u00E9f\u00E9rence de macro non autoris\u00E9",
          MaxBufferSize: "Taille maximale du tampon interne de MathJax d\u00E9pass\u00E9e; y a-t-il un appel de macro r\u00E9cursif ?",
          CommandNotAllowedInEnv: "La commande %1 n'est pas autoris\u00E9e \u00E0 l'int\u00E9rieur de l'environnement %2",
          MultipleLabel: "Multiple d\u00E9finition de l'\u00E9tiquette '%1'",
          CommandAtTheBeginingOfLine: "La commande %1 doit \u00EAtre plac\u00E9e en d\u00E9but de ligne",
          IllegalAlign: "Alignement non autoris\u00E9 pour la commande %1",
          BadMathStyleFor: "Style math\u00E9matique non valide pour la commande %1",
          PositiveIntegerArg: "L'argument de la commande %1 doit \u00EAtre un entier positif",
          ErroneousNestingEq: "Embrication incorrecte des structures d'\u00E9quations",
          MultlineRowsOneCol: "Les rang\u00E9es au sein de l\u2019environnement %1 doivent avoir exactement une colonne",
          MultipleBBoxProperty: "La propri\u00E9t\u00E9 %1 est sp\u00E9cifi\u00E9e deux fois dans la commande %2",
          InvalidBBoxProperty: "La valeur '%1' ne semble pas \u00EAtre une couleur, une dimension de marge int\u00E9rieure ou un style.",
          ExtraEndMissingBegin: "Commande %1 non attendue ou commande \\begingroup manquante",
          GlobalNotFollowedBy: "Commande %1 non suivie d\u2019une commande \\let, \\def ou \\newcommand",
          UndefinedColorModel: "Le mod\u00E8le de couleur '%1' n'est pas d\u00E9fini",
          ModelArg1: "Les valeurs de couleurs pour le mod\u00E8le %1 n\u00E9cessitent 3 nombres",
          InvalidDecimalNumber: "Nombre d\u00E9cimal non valide",
          ModelArg2: "Les valeurs de couleurs pour le mod\u00E8le %1 doivent \u00EAtre comprises entre %2 et %3",
          InvalidNumber: "Nombre non valide",
          NewextarrowArg1: "Le premier argument de la commande %1 doit \u00EAtre le nom d'une s\u00E9quence de contr\u00F4le",
          NewextarrowArg2: "Le second argument de la commande %1 doit \u00EAtre deux entiers s\u00E9par\u00E9s par une virgule",
          NewextarrowArg3: "Le troisi\u00E8me argument de la commande %1 doit \u00EAtre la valeur d\u2019un caract\u00E8re unicode",
          NoClosingChar: "Impossible de trouver le d\u00E9limiteur '%1' fermant",
          IllegalControlSequenceName: "Nom de contr\u00F4le de s\u00E9quence non autoris\u00E9 pour la commande %1",
          IllegalParamNumber: "Nombre de param\u00E8tres incorrect pour la commande %1",
          MissingCS: "%1 doit \u00EAtre suivi d'une s\u00E9quence de contr\u00F4le",
          CantUseHash2: "Usage du caract\u00E8re # non autoris\u00E9 dans le mod\u00E8le pour la s\u00E9quence de contr\u00F4le %1",
          SequentialParam: "Les param\u00E8tres de la s\u00E9quence de contr\u00F4le %1 doivent \u00EAtre \u00E9num\u00E9r\u00E9s de fa\u00E7on s\u00E9quentielle",
          MissingReplacementString: "Texte de remplacement manquant pour la d\u00E9finition %1",
          MismatchUseDef: "L\u2019utilisation de la commande %1 ne correspond pas \u00E0 sa d\u00E9finition",
          RunawayArgument: "Argument non termin\u00E9 pour la commande %1?",
          NoClosingDelim: "Impossible de trouver le d\u00E9limiteur fermant pour la commande %1"
        }
});

MathJax.Ajax.loadComplete("[MathJax]/localization/fr/TeX.js");
