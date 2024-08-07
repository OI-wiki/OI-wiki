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

hookMkdocsMaterial();

document$.subscribe(function () {
  matchColor();

  globalThis["OffsetsInjectionReview"] instanceof Object &&
    OffsetsInjectionReview.setupReview instanceof Function &&
    OffsetsInjectionReview.setupReview(document.body, {
      apiEndpoint: "{apiEndpoint}" // api endpoint injected here, see: scripts/post-build/offsets-inject/task-handler.ts
    });
});
