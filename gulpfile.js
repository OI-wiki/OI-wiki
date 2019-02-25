const gulp = require('gulp')
const htmlmin = require('gulp-htmlmin')
const purifycss = require('gulp-purifycss')
const postcss = require('gulp-postcss')

gulp.task('minify:html', () => {
  return gulp.src('site/**/*.html')
    .pipe(htmlmin({
      collapseWhitespace: true,
      minifyJS: true,
      minifyCSS: true,
      minifyURLs: true,
      removeComments: true,
      removeOptionalTags: true,
      removeRedundantAttributes: true,
      removeStyleLinkTypeAttributes: true,
      removeScriptTypeAttributes: true,
      useShortDoctype: true
    }))
    .pipe(gulp.dest('site'))
})

gulp.task('minify:css', () => {
  return gulp
    .src(`site/**/*.css`)
    .pipe(purifycss([`site/**/*.html`, `site/**/*.js`]))
    .pipe(
      postcss([
        require('cssnano')()
      ])
    )
    .pipe(gulp.dest('site'))
})

gulp.task('minify', gulp.series('minify:html', 'minify:css'))
