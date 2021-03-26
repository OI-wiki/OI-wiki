#!/usr/bin/env bash

set -e

if [ ! -d "mkdocs-material" ] ; then
  git clone --depth=1 https://github.com/OI-wiki/mkdocs-material.git
fi

if [ "$(uname)" == "Darwin" ] ; then
  # macOS sed -i 需要添加""表示不备份修改
  sed -i "" "s/name: 'material'/name: null\n  custom_dir: 'mkdocs-material\/material'\n  static_templates:\n    - 404.html/g" mkdocs.yml
else
  sed -i "s/name: 'material'/name: null\n  custom_dir: 'mkdocs-material\/material'\n  static_templates:\n    - 404.html/g" mkdocs.yml
fi