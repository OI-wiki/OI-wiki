import { HTMLElement } from "node-html-parser";
import { TaskHandler } from "../html-postprocess.js";
import * as fs from "fs";
import * as path from "path";


// 读取data.json
function getArchiveLinkMap(jsonPath: string): Record<string, any> {
  try {
    const raw = fs.readFileSync(jsonPath, "utf8");
    return JSON.parse(raw);
  } catch (e) {
    console.error("读取data.json失败", e);
    return {};
  }
}

const archiveLinkData = getArchiveLinkMap("scripts\\post-build\\archive-link\\data.json");

export const taskHandler = new (class implements TaskHandler<void> {
  async process(document: HTMLElement) {
    const data = archiveLinkData;

    document.getElementsByTagName("a").forEach(element => {
      // 检查a标签是否包裹图片
      const hasImg = element.querySelector && element.querySelector("img");
      if (hasImg) return;

      const link = element.getAttribute("href");
      if (!link || !data[link]) return;

      const archiveUrl = data[link]["archiveLink"]

      if (archiveUrl == null) return;

      let archivedA = null;
      if (data[link]["status"] != 0) {
        archivedA = new HTMLElement("a", {}, "[存档]");
        archivedA.setAttribute("href", archiveUrl);
        archivedA.setAttribute("target", "_blank");
        archivedA.setAttribute("rel", "noopener noreferrer");
        archivedA.set_content("[存档]");
      }
      else {
        archivedA = new HTMLElement("a", {}, "[原链]");
        archivedA.setAttribute("href", link);
        archivedA.setAttribute("target", "_blank");
        archivedA.setAttribute("rel", "noopener noreferrer");
        archivedA.set_content("[原链]");
        element.setAttribute("href", archiveUrl);
      }
      

      // 构造sup
      const sup = new HTMLElement("sup", {}, "");
      sup.appendChild(archivedA);

      // 插入sup到a标签后
      element.after(sup);
    });
  }
})();
