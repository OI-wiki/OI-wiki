import fs from "fs";

import { AUTHORS_FILE, fetchAuthors } from "./authors-cache.js";

// Increase this value carefully since it should cause API token limit exceeded
const fetchConcurrency = Number(process.argv[2]) || 1;

const result = await fetchAuthors(null, fetchConcurrency);
await fs.promises.writeFile(AUTHORS_FILE, JSON.stringify(result, null, 2), "utf-8");
