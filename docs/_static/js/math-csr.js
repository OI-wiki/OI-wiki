MathJax = {
  chtml: {
    matchFontHeight: false
  }
};

document$.subscribe(function () {
  MathJax.typesetPromise();
});
