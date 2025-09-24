import module from "module";
import fs from "fs";
import path from "path";
import url from "url";
import stream from "stream/promises";
import crypto from "crypto";
import { HTMLElement } from "node-html-parser";

import { mathjax } from "@mathjax/src/js/mathjax.js";
import { TeX } from "@mathjax/src/js/input/tex.js";
import { CHTML } from "@mathjax/src/js/output/chtml.js";
import { LiteAdaptor, liteAdaptor } from "@mathjax/src/js/adaptors/liteAdaptor.js";
import { RegisterHTMLHandler } from "@mathjax/src/js/handlers/html.js";
import { AssistiveMmlHandler } from "@mathjax/src/js/a11y/assistive-mml.js";
import type { MathDocument } from "@mathjax/src/js/core/MathDocument.js";
import type { LiteDocument } from "@mathjax/src/js/adaptors/lite/Document.js";
import type { LiteElement } from "@mathjax/src/js/adaptors/lite/Element.js";
import "@mathjax/src/js/util/asyncLoad/esm.js";

import "@mathjax/src/js/input/tex/ams/AmsConfiguration.js";
import "@mathjax/src/js/input/tex/base/BaseConfiguration.js";
import "@mathjax/src/js/input/tex/boldsymbol/BoldsymbolConfiguration.js";
import "@mathjax/src/js/input/tex/colorv2/ColorV2Configuration.js";
import "@mathjax/src/js/input/tex/html/HtmlConfiguration.js";
import "@mathjax/src/js/input/tex/noundefined/NoUndefinedConfiguration.js";
import "@mathjax/src/js/input/tex/physics/PhysicsConfiguration.js";

import { TaskHandler, log } from "../html-postprocess.js";

// All HTML files will reference the CSS file with relative paths (to the HTML file)
// The CSS file will reference the fonts files with relative paths (to the CSS file)
const MATHJAX_TARGET_CSS_FILE = "assets/stylesheets/mathjax.css";
const MATHJAX_TARGET_FONTS_DIR = "assets/fonts/mathjax";

const FONT_PKG = "@mathjax/mathjax-newcm-font";

// Mark the client-side math rendering script with an extra query parameter
// to remove it when using server-side rendering
const MATH_CSR_SCRIPT_SUFFIX = "?math-csr";

export class MathRenderer {
  private adaptor: LiteAdaptor;
  private document: MathDocument<LiteElement, any, LiteDocument>;
  private css: string;

  async initialize() {
    this.adaptor = liteAdaptor();
    AssistiveMmlHandler(RegisterHTMLHandler(this.adaptor));

    const inputJax = new TeX({
      packages: ["ams", "base", "boldsymbol", "colorv2", "html", "noundefined", "physics"]
    });
    const outputJax = new CHTML<LiteElement, unknown, LiteDocument>({
      // in windows, relative return with \, so need to replace
      fontURL: path.relative(path.dirname(MATHJAX_TARGET_CSS_FILE), MATHJAX_TARGET_FONTS_DIR).replaceAll("\\", "/"),
      adaptiveCSS: false,
      displayOverflow: "scroll"
    });

    this.document = mathjax.document("", {
      InputJax: inputJax,
      OutputJax: outputJax
    });

    await outputJax.font.loadDynamicFiles();

    this.css = this.adaptor.cssText(outputJax.styleSheet(this.document));
  }

  getCSS() {
    return this.css;
  }

  render(math: string, isDisplay: boolean) {
    const element = this.document.convert(math, { display: isDisplay }) as LiteElement;
    // @ts-expect-error the .create() method is wrongly set to protected
    const emptyImg = this.adaptor.create("img");
    this.adaptor.setAttribute(
      emptyImg,
      "src",
      "data:image/gif;base64,R0lGODlhAQABAIAAAAAAAP///yH5BAEAAAAALAAAAAABAAEAAAIBRAA7"
    );
    this.adaptor.setAttribute(emptyImg, "title", math);
    this.adaptor.append(element, emptyImg);
    return this.adaptor.outerHTML(element);
  }
}

export const taskHandler = new (class implements TaskHandler<void> {
  // Emit fonts and CSS file
  async globalInitialize(siteDir: string) {
    log("Copying MathJax fonts");
    const req = module.createRequire(import.meta.url);

    const fontPkgDir = path.dirname(req.resolve(`${FONT_PKG}/package.json`));
    const fontsSourceDir = path.join(fontPkgDir, "chtml", "woff2");
    const fontsDestDir = path.join(siteDir, MATHJAX_TARGET_FONTS_DIR);

    const fontFilesToCopy = await fs.promises.readdir(fontsSourceDir);

    await fs.promises.mkdir(fontsDestDir, { recursive: true });
    await Promise.all(
      fontFilesToCopy.map(filename =>
        fs.promises.copyFile(path.join(fontsSourceDir, filename), path.join(fontsDestDir, filename))
      )
    );

    log("Writing MathJax CSS");
    const renderer = new MathRenderer();
    await renderer.initialize();
    const cssDestFile = path.join(siteDir, MATHJAX_TARGET_CSS_FILE);
    await fs.promises.mkdir(path.dirname(cssDestFile), { recursive: true });
    await fs.promises.writeFile(cssDestFile, renderer.getCSS(), "utf-8");

    log("Remove client-side rendering assets");
    await fs.promises.rm(path.join(siteDir, "_static/js/math-csr.js"));
    await fs.promises.rm(path.join(siteDir, "assets/vendor/mathjax"), { recursive: true });
  }

  siteDir: string;
  renderer: MathRenderer;

  async initialize(_: void, siteDir: string) {
    this.siteDir = siteDir;

    this.renderer = new MathRenderer();
    await this.renderer.initialize();
  }

  async process(document: HTMLElement, filePath: string) {
    const mathElements = document.querySelectorAll("div.arithmatex, span.arithmatex");
    mathElements.map(element => {
      // MKdocs outputs "\(xxxxxxx\)", so we need to remove the border
      const texCode = element.textContent.slice(2, -2);
      const isDisplay = element.tagName === "DIV";

      const html = this.renderer.render(texCode, isDisplay);
      element.replaceWith(html);
    });

    // Inject CSS <link> element (not checking if we have maths since we use instant loading)
    const htmlFilePathToRoot = path.relative(this.siteDir, filePath);
    const cssFilePathToHtml = path.relative(path.dirname(htmlFilePathToRoot), MATHJAX_TARGET_CSS_FILE);
    const cssDestFile = path.join(this.siteDir, MATHJAX_TARGET_CSS_FILE);
    const hash = crypto.createHash("sha256");
    await stream.pipeline(fs.createReadStream(cssDestFile), hash);
    const cssChecksum = await hash.digest("hex");
    document
      .querySelector("head")
      .insertAdjacentHTML("beforeend", `<link rel="stylesheet" href="${cssFilePathToHtml}?hash=${cssChecksum}">`);

    // Remove client-side rendering script
    document
      .querySelectorAll("script")
      .filter(element => element.getAttribute("src")?.endsWith(MATH_CSR_SCRIPT_SUFFIX))
      .forEach(element => element.remove());
  }
})();
