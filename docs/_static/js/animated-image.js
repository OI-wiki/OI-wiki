/* 动图播放控制 */
(function (root, factory) {
  'use strict';
  var api = factory();
  if (typeof module === 'object' && module.exports) {
    module.exports = api;
  } else {
    root.AnimatedImage = api;
  }
})(typeof globalThis !== 'undefined' ? globalThis : this, function () {
  'use strict';

  /* 帧解码 */
  var MIME_BY_EXT = {
    '.gif': 'image/gif',
    '.png': 'image/png',
    '.apng': 'image/png',
    '.webp': 'image/webp'
  };
  var MAX_FRAMES = 400;
  var MAX_DECODE_PIXELS = 120 * 1024 * 1024;

  function decodeFrames(buffer, type) {
    if (typeof ImageDecoder === 'undefined') {
      return Promise.resolve(null);
    }

    var decoder;
    try {
      decoder = new ImageDecoder({ data: buffer, type: type, preferAnimation: true });
    } catch (err) {
      return Promise.resolve(null);
    }

    function fail() {
      try {
        decoder.close();
      } catch (err) {
        /* 忽略 */
      }
      return null;
    }

    return decoder.tracks.ready
      .then(function () {
        var track = decoder.tracks.selectedTrack;
        if (!track || !track.animated || track.frameCount < 2 || track.frameCount > MAX_FRAMES) {
          return fail();
        }

        var count = track.frameCount;
        var frames = [];
        var width = 0;
        var height = 0;
        var first = null;

        function step(index) {
          return decoder.decode({ frameIndex: index }).then(function (result) {
            var frame = result.image;
            width = frame.displayWidth;
            height = frame.displayHeight;
            frames.push({ delay: frame.duration ? frame.duration / 1000 : 100 });
            if (index !== 0) {
              frame.close();
              return;
            }
            return createImageBitmap(frame).then(function (bitmap) {
              first = bitmap;
              frame.close();
            });
          });
        }

        return step(0).then(function () {
          if (count * width * height > MAX_DECODE_PIXELS) {
            return fail();
          }
          var chain = Promise.resolve();
          for (var i = 1; i < count; i++) {
            chain = chain.then(step.bind(null, i));
          }
          return chain.then(function () {
            if (frames.length < 2) {
              return fail();
            }
            return {
              width: width,
              height: height,
              frames: frames,
              decoder: decoder,
              first: first
            };
          });
        });
      })
      .catch(function () {
        return fail();
      });
  }

  function createDecoderPainter(decoded) {
    var canvas = document.createElement('canvas');
    canvas.width = decoded.width;
    canvas.height = decoded.height;
    var ctx = canvas.getContext('2d');
    var token = 0;
    var drawn = -1;

    function paint(source) {
      ctx.clearRect(0, 0, canvas.width, canvas.height);
      ctx.drawImage(source, 0, 0);
    }

    if (decoded.first) {
      paint(decoded.first);
      drawn = 0;
    }

    return {
      canvas: canvas,
      seek: function (index) {
        if (index === drawn) {
          return;
        }
        var current = ++token;
        decoded.decoder
          .decode({ frameIndex: index })
          .then(function (result) {
            var frame = result.image;
            if (current === token) {
              paint(frame);
              drawn = index;
            }
            frame.close();
          })
          .catch(function () {
            /* 忽略 */
          });
      }
    };
  }

  /* 播放器 */

  var ICONS = {
    play: '<svg viewBox="0 0 24 24" aria-hidden="true"><path d="M8 5v14l11-7z"/></svg>',
    pause: '<svg viewBox="0 0 24 24" aria-hidden="true"><path d="M6 19h4V5H6v14zm8-14v14h4V5h-4z"/></svg>',
    caret: '<svg class="anim-speed-caret" viewBox="0 0 24 24" aria-hidden="true"><path d="M7 10l5 5 5-5z"/></svg>'
  };

  var EXT_ATTR = 'data-anim-state';

  function makeButton(label, icon, handler) {
    var button = document.createElement('button');
    button.type = 'button';
    button.className = 'anim-btn';
    button.title = label;
    button.setAttribute('aria-label', label);
    button.innerHTML = icon;
    button.addEventListener('click', function (event) {
      event.preventDefault();
      event.stopPropagation();
      handler();
    });
    return button;
  }

  function formatTime(seconds) {
    var s = Math.max(0, seconds);
    var m = Math.floor(s / 60);
    var r = Math.floor(s % 60);
    return m + ':' + (r < 10 ? '0' : '') + r;
  }

  function createTimeline(durations) {
    var starts = [0];
    for (var i = 0; i < durations.length; i++) {
      starts.push(starts[i] + Math.max(0, durations[i]));
    }
    var total = starts[durations.length] || 0;
    return {
      total: total,
      indexAt: function (t) {
        var lo = 0;
        var hi = durations.length - 1;
        while (lo < hi) {
          var mid = (lo + hi + 1) >> 1;
          if (starts[mid] <= t) {
            lo = mid;
          } else {
            hi = mid - 1;
          }
        }
        return lo;
      }
    };
  }

  var SPEEDS = [0.5, 0.75, 1, 1.25, 1.5, 2];
  var speedMenuSeq = 0;

  function makeSpeedMenu(controller) {
    var root = document.createElement('div');
    root.className = 'anim-speed';

    var menuId = 'anim-speed-menu-' + ++speedMenuSeq;
    var trigger = document.createElement('button');
    trigger.type = 'button';
    trigger.className = 'anim-speed-trigger';
    trigger.setAttribute('aria-haspopup', 'listbox');
    trigger.setAttribute('aria-expanded', 'false');
    trigger.setAttribute('aria-controls', menuId);
    trigger.setAttribute('aria-label', '播放速度 1x');
    trigger.innerHTML = '<span class="anim-speed-label">1x</span>' + ICONS.caret;
    var label = trigger.querySelector('.anim-speed-label');

    var menu = document.createElement('div');
    menu.id = menuId;
    menu.className = 'anim-speed-menu';
    menu.setAttribute('role', 'listbox');
    menu.setAttribute('aria-label', '播放速度');
    menu.hidden = true;

    var items = [];
    var current = 1;
    var opened = false;

    for (var s = 0; s < SPEEDS.length; s++) {
      var item = document.createElement('button');
      item.type = 'button';
      item.className = 'anim-speed-item';
      item.setAttribute('role', 'option');
      item.setAttribute('aria-selected', String(SPEEDS[s] === current));
      item.textContent = SPEEDS[s] + 'x';
      item.tabIndex = -1;
      items.push(item);
      menu.appendChild(item);
    }

    function selectedIndex() {
      for (var i = 0; i < SPEEDS.length; i++) {
        if (SPEEDS[i] === current) {
          return i;
        }
      }
      return 0;
    }

    function focusItem(index) {
      var total = items.length;
      items[((index % total) + total) % total].focus();
    }

    function choose(rate) {
      current = rate;
      label.textContent = rate + 'x';
      trigger.setAttribute('aria-label', '播放速度 ' + rate + 'x');
      for (var i = 0; i < items.length; i++) {
        items[i].setAttribute('aria-selected', String(SPEEDS[i] === rate));
      }
      if (controller.setSpeed) {
        controller.setSpeed(rate);
      }
    }

    function onDocumentDown(event) {
      if (!root.contains(event.target)) {
        closeMenu(false);
      }
    }

    function onDocumentFocus(event) {
      if (!root.contains(event.target)) {
        closeMenu(false);
      }
    }

    function openMenu(index) {
      if (opened) {
        return;
      }
      opened = true;
      menu.hidden = false;
      root.classList.add('is-open');
      trigger.setAttribute('aria-expanded', 'true');
      document.addEventListener('mousedown', onDocumentDown, true);
      document.addEventListener('focusin', onDocumentFocus, true);
      focusItem(typeof index === 'number' ? index : selectedIndex());
    }

    function closeMenu(returnFocus) {
      if (!opened) {
        return;
      }
      opened = false;
      menu.hidden = true;
      root.classList.remove('is-open');
      trigger.setAttribute('aria-expanded', 'false');
      document.removeEventListener('mousedown', onDocumentDown, true);
      document.removeEventListener('focusin', onDocumentFocus, true);
      if (returnFocus) {
        trigger.focus();
      }
    }

    trigger.addEventListener('click', function (event) {
      event.preventDefault();
      event.stopPropagation();
      if (opened) {
        closeMenu(true);
      } else {
        openMenu();
      }
    });

    trigger.addEventListener('keydown', function (event) {
      if (event.key === 'ArrowDown' || event.key === 'ArrowUp') {
        event.preventDefault();
        event.stopPropagation();
        openMenu(selectedIndex());
      }
    });

    menu.addEventListener('click', function (event) {
      var index = items.indexOf(event.target);
      if (index >= 0) {
        event.preventDefault();
        event.stopPropagation();
        choose(SPEEDS[index]);
        closeMenu(true);
      }
    });

    menu.addEventListener('keydown', function (event) {
      var key = event.key;
      if (key === 'Escape') {
        event.preventDefault();
        event.stopPropagation();
        closeMenu(true);
        return;
      }
      if (key === 'Tab') {
        closeMenu(true);
        return;
      }
      if (key !== 'ArrowDown' && key !== 'ArrowUp' && key !== 'Home' && key !== 'End') {
        return;
      }
      event.preventDefault();
      if (key === 'Home') {
        focusItem(0);
      } else if (key === 'End') {
        focusItem(items.length - 1);
      } else {
        var active = items.indexOf(document.activeElement);
        var base = active < 0 ? selectedIndex() : active;
        focusItem(base + (key === 'ArrowDown' ? 1 : -1));
      }
    });

    root.appendChild(trigger);
    root.appendChild(menu);

    return { element: root };
  }

  function createControls(controller) {
    var controls = document.createElement('div');
    controls.className = 'anim-controls';

    var range = document.createElement('input');
    range.type = 'range';
    range.className = 'anim-range';
    range.min = '0';
    range.max = '1';
    range.step = '0.0001';
    range.value = '0';
    range.setAttribute('aria-label', '播放进度');

    var timeEl = document.createElement('span');
    timeEl.className = 'anim-time';

    var speedMenu = makeSpeedMenu(controller);

    var playing = false;
    var scrubbing = false;
    var raf = null;

    var playButton = makeButton('播放', ICONS.play, function () {
      if (playing) {
        pause();
      } else {
        play();
      }
    });

    function paintFill(pct) {
      var percent = (Math.min(1, Math.max(0, pct)) * 100).toFixed(2) + '%';
      range.style.setProperty(
        '--anim-fill',
        'linear-gradient(to right, #fff ' + percent + ', rgba(255, 255, 255, 0.3) ' + percent + ')'
      );
    }

    function paint() {
      var total = controller.total || 0;
      var t = controller.time();
      var pct = total > 0 ? Math.min(1, Math.max(0, t / total)) : 0;
      range.value = String(pct);
      paintFill(pct);
      timeEl.textContent = formatTime(t) + ' / ' + formatTime(total);
    }

    function frame(now) {
      if (!playing) {
        return;
      }
      if (!scrubbing) {
        controller.tick(now);
        paint();
      }
      raf = window.requestAnimationFrame(frame);
    }

    function play() {
      if (playing) {
        return;
      }
      playing = true;
      controller.play();
      playButton.innerHTML = ICONS.pause;
      playButton.title = '暂停';
      playButton.setAttribute('aria-label', '暂停');
      paint();
      raf = window.requestAnimationFrame(frame);
    }

    function pause() {
      if (!playing) {
        return;
      }
      playing = false;
      window.cancelAnimationFrame(raf);
      controller.pause();
      playButton.innerHTML = ICONS.play;
      playButton.title = '播放';
      playButton.setAttribute('aria-label', '播放');
      paint();
    }

    range.addEventListener('input', function () {
      scrubbing = true;
      var pct = parseFloat(range.value);
      var total = controller.total || 0;
      paintFill(pct);
      timeEl.textContent = formatTime(pct * total) + ' / ' + formatTime(total);
    });

    range.addEventListener('change', function () {
      scrubbing = false;
      controller.seek(parseFloat(range.value) * (controller.total || 0));
      paint();
    });

    controls.appendChild(playButton);
    controls.appendChild(range);
    controls.appendChild(timeEl);
    controls.appendChild(speedMenu.element);

    return { element: controls, play: play, pause: pause };
  }

  function enableTouchToggle(wrapper, controls) {
    wrapper.addEventListener('click', function (event) {
      if (!window.matchMedia || !window.matchMedia('(hover: none)').matches) {
        return;
      }
      var target = event.target;
      if (target && target.closest && target.closest('.anim-controls')) {
        return;
      }
      controls.classList.toggle('is-visible');
    });
  }

  function createFramesController(decoded, painter) {
    var timeline = createTimeline(
      decoded.frames.map(function (frame) {
        return frame.delay / 1000;
      })
    );
    var mediaTime = 0;
    var last = 0;
    var index = -1;
    var speed = 1;

    function show(t) {
      var clamped = timeline.total > 0 ? Math.min(t, timeline.total - 0.0001) : 0;
      var next = timeline.indexAt(clamped);
      if (next !== index) {
        index = next;
        painter.seek(next);
      }
    }

    return {
      total: timeline.total,
      time: function () {
        return mediaTime;
      },
      seek: function (t) {
        mediaTime = Math.max(0, Math.min(timeline.total, t));
        last = 0;
        show(mediaTime);
      },
      play: function () {
        last = 0;
      },
      pause: function () {
        last = 0;
      },
      setSpeed: function (value) {
        speed = value > 0 ? value : 1;
        last = 0;
      },
      tick: function (now) {
        if (!last) {
          last = now;
          return;
        }
        mediaTime += ((now - last) / 1000) * speed;
        last = now;
        if (timeline.total > 0 && mediaTime >= timeline.total) {
          mediaTime %= timeline.total;
        }
        show(mediaTime);
      }
    };
  }

  function buildPlayer(img, decoded) {
    var painter = createDecoderPainter(decoded);
    var canvas = painter.canvas;

    canvas.className = 'anim-canvas';
    canvas.setAttribute('role', 'img');
    if (img.alt) {
      canvas.setAttribute('aria-label', img.alt);
    }

    var wrapper = document.createElement('div');
    wrapper.className = 'anim-image';

    var controller = createFramesController(decoded, painter);
    var box = createControls(controller);

    wrapper.appendChild(canvas);
    wrapper.appendChild(box.element);
    enableTouchToggle(wrapper, box.element);

    if (img.parentNode) {
      img.parentNode.replaceChild(wrapper, img);
    }

    controller.seek(0);
    box.play();
  }

  /* SVG 动画 */

  function parseSvgDuration(text) {
    var max = 0;
    var re = /dur\s*=\s*"(\d+(?:\.\d+)?)(ms|s)?"/g;
    var m;
    while ((m = re.exec(text))) {
      var v = parseFloat(m[1]);
      if (m[2] === 'ms') {
        v /= 1000;
      }
      if (v > max) {
        max = v;
      }
    }
    return max || 20;
  }

  function createSvgController(root, duration) {
    var speed = 1;
    var native = true;
    var last = 0;

    function clamp(t) {
      return Math.max(0, Math.min(duration - 0.001, t));
    }

    function useNative() {
      try {
        root.unpauseAnimations();
      } catch (err) {
        /* 忽略 */
      }
      native = true;
      last = 0;
    }

    function useManual() {
      try {
        root.pauseAnimations();
      } catch (err) {
        /* 忽略 */
      }
      native = false;
      last = 0;
    }

    return {
      total: duration,
      time: function () {
        var t = 0;
        try {
          t = root.getCurrentTime() % duration;
        } catch (err) {
          t = 0;
        }
        return t < 0 ? 0 : t;
      },
      seek: function (t) {
        try {
          root.setCurrentTime(clamp(t));
        } catch (err) {
          /* 忽略 */
        }
        last = 0;
      },
      play: function () {
        if (speed === 1) {
          useNative();
        } else {
          useManual();
        }
      },
      pause: function () {
        try {
          root.pauseAnimations();
        } catch (err) {
          /* 忽略 */
        }
        native = false;
        last = 0;
      },
      setSpeed: function (value) {
        speed = value > 0 ? value : 1;
        if (speed === 1) {
          useNative();
        } else {
          useManual();
        }
      },
      tick: function (now) {
        if (native) {
          return;
        }
        if (!last) {
          last = now;
          return;
        }
        var t = root.getCurrentTime() + ((now - last) / 1000) * speed;
        last = now;
        try {
          root.setCurrentTime(t % duration);
        } catch (err) {
          /* 忽略 */
        }
      }
    };
  }

  function buildSvgPlayer(img, text) {
    var doc;
    try {
      doc = new DOMParser().parseFromString(text, 'image/svg+xml');
    } catch (err) {
      img.setAttribute(EXT_ATTR, 'failed');
      return;
    }
    var source = doc.documentElement;
    if (!source || source.nodeName.toLowerCase() !== 'svg') {
      img.setAttribute(EXT_ATTR, 'failed');
      return;
    }

    var w = parseFloat(source.getAttribute('width')) || img.naturalWidth || 600;
    var h = parseFloat(source.getAttribute('height')) || img.naturalHeight || 400;
    if (!source.getAttribute('viewBox')) {
      source.setAttribute('viewBox', '0 0 ' + w + ' ' + h);
    }

    var wrapper = document.createElement('div');
    wrapper.className = 'anim-image';
    wrapper.style.width = w + 'px';

    var holder = document.createElement('div');
    holder.className = 'anim-svg';
    var shadow = holder.attachShadow({ mode: 'open' });
    var style = document.createElement('style');
    style.textContent = ':host{display:block}svg{display:block;width:100%;height:auto}';
    shadow.appendChild(style);

    var svg = document.importNode(source, true);
    svg.removeAttribute('width');
    svg.removeAttribute('height');
    shadow.appendChild(svg);
    var root = shadow.querySelector('svg');

    var duration = parseSvgDuration(text);
    var controller = createSvgController(root, duration);
    var box = createControls(controller);

    wrapper.appendChild(holder);
    wrapper.appendChild(box.element);
    enableTouchToggle(wrapper, box.element);

    if (img.alt) {
      holder.setAttribute('role', 'img');
      holder.setAttribute('aria-label', img.alt);
    }

    if (img.parentNode) {
      img.parentNode.replaceChild(wrapper, img);
    }

    controller.seek(0);
    box.play();
  }

  function processSvgImage(img, src) {
    img.setAttribute(EXT_ATTR, 'pending');
    fetch(src, { cache: 'force-cache' })
      .then(function (res) {
        if (!res.ok) {
          throw new Error('HTTP ' + res.status);
        }
        return res.text();
      })
      .then(function (text) {

        if (!/<animate|<set[\s>]/i.test(text)) {
          img.setAttribute(EXT_ATTR, 'static');
          return;
        }
        buildSvgPlayer(img, text);
      })
      .catch(function () {
        img.setAttribute(EXT_ATTR, 'failed');
      });
  }

  /* 入口 */

  function extensionOf(src) {
    var path = src.split('?')[0].split('#')[0];
    var dot = path.lastIndexOf('.');
    return dot === -1 ? '' : path.slice(dot).toLowerCase();
  }

  function processImage(img) {
    if (img.getAttribute(EXT_ATTR)) {
      return;
    }
    var src = img.getAttribute('src');
    if (!src) {
      return;
    }

    var ext = extensionOf(src);
    if (ext === '.svg') {
      processSvgImage(img, src);
      return;
    }
    var type = MIME_BY_EXT[ext];
    if (!type) {
      return;
    }

    img.setAttribute(EXT_ATTR, 'pending');

    var bufferPromise;
    try {
      bufferPromise = fetch(src, { cache: 'force-cache' }).then(function (res) {
        if (!res.ok) {
          throw new Error('HTTP ' + res.status);
        }
        return res.arrayBuffer();
      });
    } catch (err) {
      img.removeAttribute(EXT_ATTR);
      return;
    }

    bufferPromise
      .then(function (buffer) {
        return decodeFrames(buffer, type);
      })
      .then(function (decoded) {
        if (!decoded || decoded.frames.length < 2) {
          img.setAttribute(EXT_ATTR, 'static');
          return;
        }
        buildPlayer(img, decoded);
      })
      .catch(function () {
        img.setAttribute(EXT_ATTR, 'failed');
      });
  }

  function scan(root) {
    var scope = root || document;
    var images = scope.querySelectorAll('.md-content img');
    for (var i = 0; i < images.length; i++) {
      processImage(images[i]);
    }
  }

  function init() {
    if (typeof document === 'undefined') {
      return;
    }
    scan(document);

    if (typeof MutationObserver !== 'undefined') {
      var observer = new MutationObserver(function (records) {
        for (var i = 0; i < records.length; i++) {
          var added = records[i].addedNodes;
          for (var j = 0; j < added.length; j++) {
            var node = added[j];
            if (node.nodeType !== 1) {
              continue;
            }
            if (node.tagName === 'IMG' && node.closest && node.closest('.md-content')) {
              processImage(node);
            } else if (node.querySelectorAll) {
              var imgs = node.querySelectorAll('.md-content img');
              for (var k = 0; k < imgs.length; k++) {
                processImage(imgs[k]);
              }
            }
          }
        }
      });
      observer.observe(document.body, { childList: true, subtree: true });
    }
  }

  if (typeof document !== 'undefined') {
    if (document.readyState === 'loading') {
      document.addEventListener('DOMContentLoaded', init);
    } else {
      init();
    }
  }

  return {
    decodeFrames: decodeFrames,
    init: init,
    _createDecoderPainter: createDecoderPainter
  };
});
