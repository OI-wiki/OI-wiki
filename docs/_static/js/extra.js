window.addEventListener('load', function () {
  var p = localStorage.getItem("data-md-color-primary");
  if (p) {
    document.body.setAttribute('data-md-color-primary', p);
  }
  var a = localStorage.getItem('data-md-color-accent');
  if (a) {
    document.body.setAttribute('data-md-color-accent', a);
  }
}, false);

(() => {
  function spreadTheme() {
    var theme = document.body.dataset.mdColorScheme === 'slate' ? 'dark' : 'light';
    var giscus = document.querySelector('iframe.giscus-frame');
    if (!giscus) return;
    giscus.contentWindow.postMessage({ giscus: { setConfig: { theme: theme } } }, 'https://giscus.app');
  }

  var oldHref = null;
  var pageObserver = new MutationObserver(function (mutations) {
    mutations.forEach(() => {

      if (oldHref !== document.location.href) {
        oldHref = document.location.href;

        window.addEventListener('message', function (event) {
          if (event.origin !== 'https://giscus.app') return;
          if (!(typeof event.data === 'object' && event.data.giscus)) return;
          spreadTheme();
        }, { once: true });
      }

      mutations
        .filter(function (mut) { return mut.type === 'attributes' && mut.attributeName === 'data-md-color-scheme' })
        .forEach(spreadTheme);
    });
  });
  pageObserver.observe(document.body, { childList: true, subtree: true, attributes: true });
})();
