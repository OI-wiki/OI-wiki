'use strict';

var _createClass = function () { function defineProperties(target, props) { for (var i = 0; i < props.length; i++) { var descriptor = props[i]; descriptor.enumerable = descriptor.enumerable || false; descriptor.configurable = true; if ("value" in descriptor) descriptor.writable = true; Object.defineProperty(target, descriptor.key, descriptor); } } return function (Constructor, protoProps, staticProps) { if (protoProps) defineProperties(Constructor.prototype, protoProps); if (staticProps) defineProperties(Constructor, staticProps); return Constructor; }; }();

function _classCallCheck(instance, Constructor) { if (!(instance instanceof Constructor)) { throw new TypeError("Cannot call a class as a function"); } }

function _possibleConstructorReturn(self, call) { if (!self) { throw new ReferenceError("this hasn't been initialised - super() hasn't been called"); } return call && (typeof call === "object" || typeof call === "function") ? call : self; }

function _inherits(subClass, superClass) { if (typeof superClass !== "function" && superClass !== null) { throw new TypeError("Super expression must either be null or a function, not " + typeof superClass); } subClass.prototype = Object.create(superClass && superClass.prototype, { constructor: { value: subClass, enumerable: false, writable: true, configurable: true } }); if (superClass) Object.setPrototypeOf ? Object.setPrototypeOf(subClass, superClass) : subClass.__proto__ = superClass; }

var fs = require('fs');

var Pangu = require('../shared/core').Pangu;

var NodePangu = function (_Pangu) {
  _inherits(NodePangu, _Pangu);

  function NodePangu() {
    var filePrefix = arguments.length <= 0 || arguments[0] === undefined ? 'readable.' : arguments[0];

    _classCallCheck(this, NodePangu);

    var _this = _possibleConstructorReturn(this, Object.getPrototypeOf(NodePangu).call(this));

    _this.filePrefix = filePrefix;
    return _this;
  }

  _createClass(NodePangu, [{
    key: 'spacingFile',
    value: function spacingFile(path) {
      var _this2 = this;

      var callback = arguments.length <= 1 || arguments[1] === undefined ? function () {} : arguments[1];

      return new Promise(function (resolve, reject) {
        fs.readFile(path, 'utf8', function (err, data) {
          if (err) {
            reject(err);
            return callback(err);
          }

          var spacingData = _this2.spacing(data);

          resolve(spacingData);
          return callback(null, spacingData);
        });
      });
    }
  }, {
    key: 'spacingFileSync',
    value: function spacingFileSync(path) {
      try {
        return this.spacing(fs.readFileSync(path, 'utf8'));
      } catch (err) {
        throw err;
      }
    }

    // TODO
    // spacingFileFromURL(url, callback) {
    // }

    // TODO
    // spacingHTML(html, callback) {
    // }

  }]);

  return NodePangu;
}(Pangu);

var pangu = new NodePangu();

exports = module.exports = pangu;
exports.Pangu = NodePangu;