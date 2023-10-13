import { HTMLElement } from "node-html-parser";

import { TaskHandler } from "../html-postprocess.js";

const ROOT_URL = new URL("https://oi-wiki.org/");

export const taskHandler = new (class implements TaskHandler<void> {
  async process(document: HTMLElement) {
    document.getElementsByTagName("a").forEach(element => {
      const href = element.getAttribute("href");
      if (new URL(href, ROOT_URL).origin !== ROOT_URL.origin) {
        if ((element.getAttribute("target") || "").trim() === "") {
          element.setAttribute("target", "_blank");
        }
      }
    });
  }
})();
