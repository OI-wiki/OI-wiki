import fs from "fs";

import { AUTHORS_FILE, fetchAuthors } from "./authors-cache.js";

const result = await fetchAuthors(null);
await fs.promises.writeFile(AUTHORS_FILE, JSON.stringify(result, null, 2), "utf-8");
