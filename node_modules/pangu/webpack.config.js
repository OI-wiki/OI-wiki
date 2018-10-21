var _ = require('underscore');
var fs = require('fs');
var webpack = require('webpack');

var packageInfo = require('./package.json');

var uglifyPlugin = new webpack.optimize.UglifyJsPlugin({
  include: /\.min\.js$/,
  minimize: true
})

var bannerTemplate = fs.readFileSync('src/browser/banner.txt', {encoding: 'utf8'});
var bannerText = _.template(bannerTemplate)(packageInfo);
var bannerPlugin = new webpack.BannerPlugin(bannerText, {
  include: /^pangu/,
  raw: true,
  entryOnly: true
});

var entryPath = './src/browser/pangu.js';

module.exports = {
  entry: {
    'pangu': entryPath,
    'pangu.min': entryPath
  },
  output: {
    path: './dist/browser/',
    filename: '[name].js',
    library: 'pangu',
    libraryTarget: 'umd',
    umdNamedDefine: true
  },
  devtool: 'source-map',
  module: {
    loaders: [
      {
        test: /\.js$/,
        exclude: /node_modules/,
        loader: 'babel-loader',
        query: {
          plugins: ['add-module-exports'],
          presets: ['es2015']
        }
      }
    ]
  },
  plugins: [
    uglifyPlugin,
    bannerPlugin
  ]
}
