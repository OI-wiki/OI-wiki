MathJax.Hub.Register.StartupHook("TeX Jax Ready", function () {
  MathJax.InputJax.TeX.Definitions.Add({
    macros: {
      test: ["Macro", "\text{This is a Test}"]
    }
  });
});

MathJax.Ajax.loadComplete("[test]/test.js");
