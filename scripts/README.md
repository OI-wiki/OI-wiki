# scripts

本目录存放了用于测试、构建和整理代码的一些脚本。

-   `pre-build` 运行于构建前的脚本
    - `install-theme.sh, install-theme-vendor.sh` 安装 mkdocs 主题，与主题中所用的第三方库
    - `pre-build.sh` 在 CI 上构建生产环境站点时所运行的脚本，包括安装主题与调整配置
-   `post-build` 运行于构建后的脚本
    - `commits-info` 渲染每个页面中与 Git commits 有关的信息（更新时间，贡献者列表等）
    - `math` 渲染每个页面中的数学公式（**注：** 在预览构建中，公式在前端渲染）
    - `redirect` 生成跳转页面
-   `post-deploy` 运行于主站生产环境部署后的脚本
    - `baidu-push.sh, convert-sitemap.py` 将 sitemap 转换并推送到百度搜索
-   `netlify` 用于 Netlify 上的预览构建的脚本（参见 `/netlify.toml`）
    - `build.sh` 在 Netlify 上的构建全过程（手动安装依赖）
    - `install-python.sh` 在 Netlify 上安装指定版本的 Python

以下是与构建无关的脚本：

- `test.py` 测试文档中的实例代码正常编译运行并通过样例
    - `single-run.cpp` 运行单个代码
- `check-characters.py` 扫描修改的 Markdown 文件中可替换为对应 CJK 字符的部首（和笔画字符）
- `celebration.py` 自动创建庆祝 star 数量的 issue
-   `utils` 一些工具
    - `find_jk.py` 寻找源文件中非中文码位的汉字字符
