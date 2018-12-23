var gulp = require('gulp')

gulp.task('generate-service-worker', function (callback) {
  const path = require('path');
  const swPrecache = require('sw-precache');
  const rootDir = 'site'
  swPrecache.write(path.join(rootDir, 'service-worker.js'), {
    staticFileGlobs: ['site/**/*.{js,html,css,png,jpg,gif,svg,eot,ttf,woff}'],
    stripPrefix: rootDir + '/'
  }, callback);
});
