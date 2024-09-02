function matchColor() {
  const palettle = localStorage.getItem("/.__palette");
  if (
    (palettle !== null && JSON.parse(palettle)?.color?.scheme !== "default") ||
    (palettle === null && window.matchMedia("(prefers-color-scheme: dark)").matches)
  ) {
    document.documentElement.classList.add("review_dark_mode");
  } else {
    document.documentElement.classList.remove("review_dark_mode");
  }
}

function hookMkdocsMaterial() {
  document.querySelector(".md-header__option").addEventListener("click", e => {
    if (!(e.target instanceof HTMLInputElement)) return;
    setTimeout(matchColor, 0); // wait for the theme to be applied
  });
}

function stringToHash(string) {

  let hash = 0;

  if (string.length == 0) return hash;

  for (i = 0; i < string.length; i++) {
    char = string.charCodeAt(i);
    hash = ((hash << 5) - hash) + char;
    hash = hash & hash;
  }

  return hash;
}

// has ?enable_feedback_sys=true parameter
if (location.search.includes("enable_feedback_sys=true")) {
  localStorage.setItem("enable_feedback_sys", "true");
}

if (localStorage.getItem("giscus-session") && stringToHash(localStorage.getItem("giscus-session")) % 100 < 20) {
  localStorage.setItem("enable_feedback_sys", "true");
}

if (localStorage.getItem("enable_feedback_sys") === "true") {
  hookMkdocsMaterial();

  document$.subscribe(function () {
    matchColor();

    globalThis["OIWikiFeedbackSysFrontend"] instanceof Object &&
      OIWikiFeedbackSysFrontend.setupReview instanceof Function &&
      OIWikiFeedbackSysFrontend.setupReview(document.body, {
        apiEndpoint: "{apiEndpoint}" // api endpoint injected here, see: scripts/post-build/inject-feedback-sys-frontend/task-handler.ts
      });
  });
}
