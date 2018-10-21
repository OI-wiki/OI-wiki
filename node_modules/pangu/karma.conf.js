var webpackConfig = require('./webpack.config');
delete webpackConfig['entry'];
delete webpackConfig['devtool'];

// karma-webpack 似乎沒辦法根據不同的檔案使用不同的 webpack config
// 所以如果有一個以上的檔案都透過 webpack 這個 preprocessor
// 則他們都會被 export 成 var pangu = xxx;
webpackConfig.output = {
  filename: 'pangu.js',
  library: 'pangu',
  libraryTarget: 'var'
};

module.exports = function (config) {
  config.set({
    browsers: [
      // 'Chrome'
      'PhantomJS'
    ],
    files: [
      'node_modules/chai/chai.js',
      'dist/browser/pangu.js',
      'test/browser/*.js',
      'test/_fixture/*.html'
    ],
    frameworks: [
      'mocha'
    ],
    preprocessors: {
        'dist/browser/pangu.js': ['coverage'],
        'test/browser/*.js': ['babel'],
        'test/_fixture/*.html': ['html2js']
    },
    reporters: [
      'mocha',
      'coverage'
    ],
    singleRun: true,
    babelPreprocessor: {
      options: {
        plugins: ['add-module-exports'],
        presets: ['es2015']
      }
    },
    coverageReporter: {
      type: 'lcov',
      subdir: '.'
    },
    webpack: webpackConfig,
    webpackMiddleware: {
        noInfo: true
    }
  });
};
