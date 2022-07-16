import module from "module";
import fs from "fs";
import path from "path";
import { HTMLElement } from "node-html-parser";

import { mathjax } from "mathjax-full/js/mathjax.js";
import { TeX } from "mathjax-full/js/input/tex.js";
import { CHTML } from "mathjax-full/js/output/chtml.js";
import { LiteAdaptor, liteAdaptor } from "mathjax-full/js/adaptors/liteAdaptor.js";
import { HTMLHandler } from "mathjax-full/js/handlers/html/HTMLHandler.js";
import { SafeHandler } from "mathjax-full/js/ui/safe/SafeHandler.js";
import type { MathDocument } from "mathjax-full/js/core/MathDocument.js";
import type { LiteDocument } from "mathjax-full/js/adaptors/lite/Document.js";
import type { LiteElement } from "mathjax-full/js/adaptors/lite/Element.js";

import { TaskHandler, log } from "../html-postprocess.js";

// Define the MathJax packages to load
const MATHJAX_PACKAGES = ["ams", "boldsymbol", "colorv2", "html", "noundefined", "physics"];

// All HTML files will reference the CSS file with relative paths (to the HTML file)
// The CSS file will reference the fonts files with relative paths (to the CSS file)
const MATHJAX_TARGET_CSS_FILE = "assets/stylesheets/mathjax.css";
const MATHJAX_TARGET_FONTS_DIR = "assets/fonts/mathjax";

// Mark the client-side math rendering script with an extra query parameter
// to remove it when using server-side rendering
const MATH_CSR_SCRIPT_SUFFIX = "?math-csr";

// The directory of package `mathjax-full`
const MATHJAX_SOURCE = path.dirname(module.createRequire(import.meta.url).resolve("mathjax-full/package.json"));

// Add horizontal scrollbar automatically on narrow screens
const MATHJAX_EXTRA_CSS = `
  mjx-container[jax="CHTML"][display="true"] mjx-math {
    overflow-x: auto;
    overflow-y: hidden;
    max-width: 100%;
  }
`;

export class MathRenderer {
  private adaptor: LiteAdaptor;
  private document: MathDocument<LiteElement, any, LiteDocument>;
  private css: string;

  async initialize() {
    // Load MathJax's TeX packages
    const packagesDir = path.join(MATHJAX_SOURCE, "js/input/tex");
    await Promise.all(
      MATHJAX_PACKAGES.map(async packageName => {
        const packageDir = path.join(packagesDir, packageName);
        const packageDirFiles = await fs.promises.readdir(packageDir);
        const packageConfigurationFile = packageDirFiles.find(filename => filename.endsWith("Configuration.js"));
        return await import(path.join(packageDir, packageConfigurationFile));
      })
    );

    this.adaptor = liteAdaptor();
    const inputJax = new TeX({
      packages: {
        "[+]": MATHJAX_PACKAGES
      }
    });
    const outputJax = new CHTML<LiteElement, unknown, LiteDocument>({
      fontURL: path.relative(path.dirname(MATHJAX_TARGET_CSS_FILE), MATHJAX_TARGET_FONTS_DIR),
      adaptiveCSS: false
    });

    mathjax.handlers.register(SafeHandler(new HTMLHandler(this.adaptor)));

    this.document = mathjax.document("", {
      InputJax: inputJax,
      OutputJax: outputJax
    });

    this.document.updateDocument();
    this.css = this.adaptor.textContent(outputJax.chtmlStyles);
  }

  getCSS() {
    return this.css + "\n" + MATHJAX_EXTRA_CSS;
  }

  render(math: string, isDisplay: boolean) {
    const element = this.document.convert(math, { display: isDisplay }) as LiteElement;
    this.adaptor.setAttribute(element, "title", math);
    return this.adaptor.outerHTML(element);
  }
}

export const taskHandler = new (class implements TaskHandler<void> {
  // Emit fonts and CSS file
  async globalInitialize(siteDir: string) {
    log("Copying MathJax fonts");
    const fontsSourceDir = path.join(MATHJAX_SOURCE, "es5/output/chtml/fonts/woff-v2");
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

    // Inject CSS <link> element (if rendered any math elements)
    if (mathElements.length > 0) {
      const htmlFilePathToRoot = path.relative(this.siteDir, filePath);
      const cssFilePathToHtml = path.relative(path.dirname(htmlFilePathToRoot), MATHJAX_TARGET_CSS_FILE);
      document
        .querySelector("head")
        .insertAdjacentHTML("beforeend", `<link rel="stylesheet" href="${cssFilePathToHtml}">`);
    }

    // Remove client-side rendering script
    document
      .querySelectorAll("script")
      .filter(element => element.getAttribute("src")?.endsWith(MATH_CSR_SCRIPT_SUFFIX))
      .forEach(element => element.remove());
  }
})();
