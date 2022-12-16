import * as colors from "colors";
import * as fs from "node:fs";
import * as path from "path";
import * as cmd from "child_process";
import { unified } from "unified";
import remarkParse from "remark-parse";
import { visit } from "unist-util-visit";
import yargs from "yargs";
import { hideBin } from "yargs/helpers";
import { exit } from "node:process";

//main start
let parg = await yargs(hideBin(process.argv)).usage("$0 [args]").argv;
let runPath = path.parse(process.argv[1]).dir;
console.log("Checker running at: " + runPath);

let errFlagFile = await getFileContent(runPath + "/checker_flag.json");
let errFlag = JSON.parse(errFlagFile);
if (parg.h) {
  console.log(
    "Usage: \n" +
      "\t-h\tShow help.\n" +
      "\t-f <path>\tCheck specified path.\n" +
      "\t-a\tCheck all files.\n" +
      "\t-s\tSort results according to files' name.\n" +
      "\t-r\tShow suggestions. Implies -s.\n" +
      "\t-q\tCheck files quietly.\n" +
      "\t--after=<time>, --before=<time>, --author=<time>, --grep<time>\tCheck matched files. Implies -a.\n"
  );
  exit(0);
}
let FileLog = await getChangedFilesByLog(),
  FileLs = await getChangedFilesByDiff();
let FileTotal: string = "";
if (parg.after || parg.before || parg.author || parg.grep || parg.a) FileTotal += FileLog;
else FileTotal += FileLs;
checkFiles(parseFileList(FileTotal));
//main end

function getChangedFilesByLog(): Promise<string> {
  let args = "";
  if (parg.after) args += '--after="' + parg.after + '" ';
  if (parg.before) args += '--before="' + parg.before + '" ';
  if (parg.author) args += '--author="' + parg.author + '" ';
  if (parg.grep) args += '--grep="' + parg.grep + '" ';
  if (parg.f) args += parg.f + " ";
  if (parg.d) console.log("[debug]Running: " + 'git log --format="" --name-only ' + args);
  return new Promise((resolve, reject) => {
    cmd.exec(
      'git log --format="" --name-only ' + args,
      {
        encoding: "utf-8"
      },
      (error, stdout, stderr) => {
        if (error) reject(stderr);
        else resolve(stdout);
      }
    );
  });
}

function getChangedFilesByDiff(): Promise<string> {
  let args = "";
  if (parg.f) args = parg.f + " ";
  else args = "--cached " + runPath + "/../..";
  if (parg.d) console.log("[debug]Running: " + "git ls-files " + "--exclude-standard " + args);
  return new Promise((resolve, reject) => {
    cmd.exec(
      "git diff --name-only " + args,
      {
        encoding: "utf-8"
      },
      (error, stdout, stderr) => {
        if (error) reject(stderr);
        else resolve(stdout);
      }
    );
  });
}

function parseFileList(fileBuf: string) {
  let fileList: string[] = new Array();
  while (fileBuf.length > 0) {
    let file = fileBuf.substring(0, fileBuf.search(/\n/));
    if (!fileList.includes(file) && fs.existsSync(file)) fileList.push(file);
    fileBuf = fileBuf.substring(fileBuf.search(/\n/) + 1);
  }
  fileList.sort();

  if (!parg.q) {
    console.log("-----------------------");
    console.log("Detected files:");
    console.log("-----------------------");
    fileList.forEach(file => console.log(file));
    console.log("----------------------------");
    console.log("Checking every changed file:");
    console.log("----------------------------");
  }

  return fileList;
}

async function checkFiles(fileList: string[]) {
  let errList: string[] = new Array();
  for (const file of fileList) {
    errList = errList.concat(await checkFile(file));
  }
  if (errList[0]) printErr(errList), exit(1);
  exit(0);
}

async function checkFile(file: string) {
  if (!parg.q) console.log("[info] Checking " + file + ":");

  //Get bare file name
  let pFile = path.parse(file);
  let fileBase = pFile.base;
  let fileName = pFile.name;
  let fileExt: string = pFile.ext;

  //Check file name valid
  let errList: string[] = new Array();
  if (errFlag.fileNameInvalid && fileBase.search(/[^\w\-\+\.]/) !== -1) errList.push(fileNameInvalid(file));
  //if (fileName.search(/README.md|index.md/) !== -1) return errList;

  //Check if it is docs
  if (file.search(/docs/) === -1) return errList;

  //Check file name lowercase
  if (
    errFlag.fileNameNotLower &&
    fileName.toLowerCase() !== fileName &&
    fileName.toUpperCase() !== fileName &&
    fileName.search(/C\+\+/) === -1
  ) {
    errList.push(fileNameNotLower(file));
    if (parg.r) errList.push("[info] Suggestion: " + fileBase.toLowerCase());
  }

  //Check file name _
  if (errFlag.fileNameLine && fileName.search(/[\_\s]/) !== -1) {
    errList.push(fileNameLine(file));
    if (parg.r) errList.push("[info] Suggestion: " + fileBase.replaceAll(/[\_\s]/g, "-"));
  }

  //Check if it is markdown
  if (fileExt.search(/md/) === -1) return errList;

  let fileContent: string = await getFileContent(file);

  let fileTree = unified().use(remarkParse).parse(fileContent);

  visit(fileTree, node => {
    if (node.type !== "image") return;

    //Pre-processing
    let imgSrc = node.url;

    let pImg = path.parse(imgSrc);

    if (!parg.q)
      console.log(
        "[Info] Caught image reference: " +
          imgSrc +
          " at " +
          file +
          ":" +
          node.position?.start.line +
          ":" +
          node.position?.start.column
      );

    //Check if image resourse name contains file name
    if (errFlag.imgRefNameInvalid && imgSrc.search(RegExp(fileName)) === -1) {
      errList.push(imgRefNameInvalid(imgSrc, file, node.position?.start.line, node.position?.start.column));

      if (parg.r) errList.push("[info] Suggestion: " + fileName + "-" + pImg.base);
    }

    //Check if image resourse is from web
    if (errFlag.imgRefFromWeb && imgSrc.search(/\:\/\//) !== -1)
      errList.push(imgRefFromWeb(imgSrc, file, node.position?.start.line, node.position?.start.column));

    //Check if image resourse format is recommended
    if (errFlag.imgFormatNotRecommended && pImg.ext.toLowerCase().search(/gif/) !== -1) {
      errList.push(imgFormatNotRecommended(imgSrc, file, node.position?.start.line, node.position?.start.column));

      if (parg.r) errList.push("[info] Suggestion: " + pImg.name + ".svg or " + pImg.name + ".apng");
    }
  });

  while (fileContent.search(/```/) !== -1) {
    let fileCut = fileContent.substring(fileContent.search(/```/) + 3);
    let fileCode = fileCut.substring(0, fileCut.search(/```/));

    fileCode = fileCode.replaceAll(/[^\r\n]/g, " ");

    fileContent =
      fileContent.substring(0, fileContent.search(/```/)) +
      "   " +
      fileCode +
      "   " +
      fileCut.substring(fileCut.search(/```/) + 3);
  }

  fileTree = unified().use(remarkParse).parse(fileContent);

  visit(fileTree, node => {
    if (node.type === "heading") {
      if (errFlag.h1Used && node.depth === 1)
        errList.push(h1Used(file, node.position?.start.line, node.position?.start.column));
      if (errFlag.tooDeepHeading && node.depth >= 5)
        errList.push(tooDeepHeading(file, node.position?.start.line, node.position?.start.column));
    }

    if (node.type === "text") {
      if (
        errFlag.OIWIKINotBold &&
        node.value.search(/OI\sWIKI/) !== -1 &&
        node.value.search(/\*\*OI\sWIKI\*\*/) === -1
      ) {
        errList.push(OIWIKINotBold(file, node.position?.start.line, node.position?.start.column));

        if (parg.r) errList.push("[info] Suggestion: '**OI WIKI**'");
      }

      if (errFlag.deleteLineUsed && node.value.search(/(\~\~)+/) !== -1 && node.value.search(/\$/) === -1) {
        errList.push(deleteLineUsed(file, node.position?.start.line, node.position?.start.column));

        if (parg.r) errList.push("[info] Suggestion: remove '~~'");
      }

      if (errFlag.emptysetUsed && node.value.search(/\\emptyset/) !== -1) {
        errList.push(emptysetUsed(file, node.position?.start.line, node.position?.start.column));

        if (parg.r) errList.push("[info] Suggestion: '\\varnothing'");
      }

      if (errFlag.doubleEqualSigns && node.value.search(/\=\=/) !== -1) {
        errList.push(doubleEqualSigns(file, node.position?.start.line, node.position?.start.column));

        if (parg.r) errList.push("[info] Suggestion: use '=' instead");
      }

      if (errFlag.tooManySquareBrackets && node.value.search(/[\w]+\[[\w\s\+\-\*\/]+\]\[[\w\s\+\-\*\/]+\]/) !== -1) {
        errList.push(tooManySquareBrackets(file, node.position?.start.line, node.position?.start.column));

        if (parg.r) errList.push("[info] Suggestion: 'f_{i,j,k}' or 'f(i,j,k)'");
      }

      if (errFlag.threeDotsUsage && node.value.search(/\.\.\./) !== -1) {
        errList.push(threeDotsUsage(file, node.position?.start.line, node.position?.start.column));

        if (parg.r) errList.push("[info] Suggestion: '\\cdots', '\\ldots', '\\vdots', '\\ddots'");
      }

      if (
        errFlag.useSplitAndEqnarray &&
        (node.value.search(/\{split\}/) !== -1 || node.value.search(/\{eqnarray\}/) !== -1)
      ) {
        errList.push(useSplitAndEqnarray(file, node.position?.start.line, node.position?.start.column));

        if (parg.r) errList.push("[info] Suggestion: 'align', 'aligned' or 'equation'");
      }

      if (errFlag.unequalSignIllegal && (node.value.search(/\\lt/) !== -1 || node.value.search(/\\gt/) !== -1)) {
        errList.push(unequalSignIllegal(file, node.position?.start.line, node.position?.start.column));

        if (parg.r) errList.push("[info] Suggestion: '<' or '>'");
      }

      if (errFlag.useChoose && node.value.search(/\\choose/) !== -1) {
        errList.push(useChoose(file, node.position?.start.line, node.position?.start.column));

        if (parg.r) errList.push("[info] Suggestion: '\\dbinom{n}{m}'");
      }

      let wordList = ["log", "ln", "lg", "sin", "cos", "tan", "gcd"];
      for (const word of wordList)
        if (
          errFlag.wordUsageIllegal &&
          node.value.search(RegExp("\\b" + word + "\\b")) !== -1 &&
          node.value.search(RegExp("\\\\" + word + "\\b")) === -1
        ) {
          errList.push(wordUsageIllegal(file, node.position?.start.line, node.position?.start.column));

          if (parg.r) errList.push("[info] Suggestion: '\\" + word + "' or '\\operatorname{" + word + "}'");
        }
    }
  });

  return errList;
}

function getFileContent(file: string): Promise<string> {
  return new Promise((resolve, reject) => {
    fs.readFile(file, "utf8", (err, data) => {
      if (err) {
        console.error(err);
        reject(err);
      }
      resolve(data);
    });
  });
}

function fileNameInvalid(file: string) {
  return "[Warning] [fileNameInvalid] File name " + file + " is invalid";
}

function fileNameNotLower(file: string) {
  return "[Warning] [fileNameNotLower] File name " + file + " is not lowercase";
}

function fileNameLine(file: string) {
  return "[Warning] [fileNameLine] File name " + file + " contains invalid spaces or underlines";
}

function imgRefNameInvalid(imgSrc: string, file: string, line: number | undefined, column: number | undefined) {
  return (
    "[Warning] [imgRefNameInvalid] Image resourse " +
    imgSrc +
    " does not contain file name at " +
    file +
    ":" +
    line +
    ":" +
    column
  );
}

function imgRefFromWeb(imgSrc: string, file: string, line: number | undefined, column: number | undefined) {
  return "[Warning] [imgRefFromWeb] Image resourse " + imgSrc + " is from web at " + file + ":" + line + ":" + column;
}

function imgFormatNotRecommended(imgSrc: string, file: string, line: number | undefined, column: number | undefined) {
  return (
    "[Warning] [imgFormatNotRecommended] Image resourse " +
    imgSrc +
    " is not in a recommended format, used at " +
    file +
    ":" +
    line +
    ":" +
    column
  );
}

function h1Used(file: string, line: number | undefined, column: number | undefined) {
  return "[Error] [h1Used] There is a 1st depth heading in file " + file + ":" + line + ":" + column;
}

function tooDeepHeading(file: string, line: number | undefined, column: number | undefined) {
  return "[Warning] [tooDeepHeading] The headings are too deep in file " + file + ":" + line + ":" + column;
}

function emptysetUsed(file: string, line: number | undefined, column: number | undefined) {
  return "[Warning] [emptysetUsed] \\emptyset is used at " + file + ":" + line + ":" + column;
}

function doubleEqualSigns(file: string, line: number | undefined, column: number | undefined) {
  return "[Warning] [doubleEqualSigns] Double equal signs at " + file + ":" + line + ":" + column;
}

function tooManySquareBrackets(file: string, line: number | undefined, column: number | undefined) {
  return "[Warning] [tooManySquareBrackets] Too many square brackets at " + file + ":" + line + ":" + column;
}

function threeDotsUsage(file: string, line: number | undefined, column: number | undefined) {
  return "[Warning] [threeDotsUsage] Three dots usage at " + file + ":" + line + ":" + column;
}

function useSplitAndEqnarray(file: string, line: number | undefined, column: number | undefined) {
  return (
    "[Error] [useSplitAndEqnarray] Split and eqnarray are forbidden, but found at " + file + ":" + line + ":" + column
  );
}

function unequalSignIllegal(file: string, line: number | undefined, column: number | undefined) {
  return "[Error] [unequalSignIllegal] Illegal unequal sign at " + file + ":" + line + ":" + column;
}

function useChoose(file: string, line: number | undefined, column: number | undefined) {
  return "[Warning] [useChoose] \\choose is used at " + file + ":" + line + ":" + column;
}

function wordUsageIllegal(file: string, line: number | undefined, column: number | undefined) {
  return "[Warning] [wordUsageIllegal] An illegal word usage at " + file + ":" + line + ":" + column;
}

function OIWIKINotBold(file: string, line: number | undefined, column: number | undefined) {
  return "[Warning] [OIWIKINotBold] 'OI WIKI' is not bold in file " + file + ":" + line + ":" + column;
}

function deleteLineUsed(file: string, line: number | undefined, column: number | undefined) {
  return "[Warning] [deleteLineUsed] Delete line is used in file " + file + ":" + line + ":" + column;
}

function printErr(errList: string[]) {
  colors.green;
  if (!parg.s && !parg.r) errList.sort();
  errList.forEach(err => {
    if (err.search(/Warning/) !== -1) console.log(err.yellow);
    else if (err.search(/Error/) !== -1) console.log(err.red);
    else console.log(err);
  });
}
