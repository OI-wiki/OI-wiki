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

- `get_files_to_test.py`、`correctness_check.py`、`ub-check.py` 与 `test_utils.py` 测试文档中的示例代码（详见下方「示例代码测试」）
- `check-characters.py` 扫描修改的 Markdown 与 TeX 文件中的异常非可见字符与可替换为对应 CJK 字符的部首（和笔画字符）
- `celebration.py` 自动创建庆祝 star 数量的 issue
- `linter_patch.py` 用于协助 bot 修正错误的文档格式化结果
-   `linter` `linter_patch.py` 的一部分，详见 `linter/README.md`
-   `utils` 一些工具
    - `find_jk.py` 寻找源文件中非中文码位的汉字字符

## 示例代码测试

`docs/**/code/` 下的示例代码（目前支持 C++ 与 Python）由以下脚本在 CI 中测试：

- `get_files_to_test.py` 根据改动的文件生成待测试的主文件列表。改动文件从环境变量 `all_changed_files` 读入（由 tj-actions/changed-files 提供），结果写入 `$GITHUB_OUTPUT`：每种语言一个以空格分隔的主文件列表 `TEST_<LANG>_FILES`，以及一个表示列表是否非空的布尔标记 `HAS_<LANG>`。
- `correctness_check.py` 编译并运行示例代码，再用测试数据校验输出。待测试文件从环境变量 `FILES_TO_TEST` 读入，语言由 `--language` 参数指定（目前为 `cpp` 或 `py`），结果写入 `$GITHUB_STEP_SUMMARY`。Python 示例代码由运行本脚本的同一个解释器执行。
- `ub-check.py` 用多种编译器、语言标准与优化等级交叉检查 C++ 示例代码里是否存在未定义行为。
- `test_utils.py` 供上面两个脚本共用的辅助模块，负责从主文件推导辅助文件、测试数据与 `.skip_test` 标记。

相关的约定：

- 示例代码的测试数据放在把路径中的 `code` 换成 `examples` 的目录下，例如 `docs/math/code/foo/foo.cpp` 的测试数据是 `docs/math/examples/foo/foo.in` 与 `foo.ans`。只有同时存在 `.in` 与 `.ans` 的数据才会被用于测试。
- 变体文件（`foo.1.cpp`、`foo.aux1.cpp` 等）不会被单独测试，它们作为 `foo.cpp` 的辅助文件一起参与测试。
- 在示例代码旁边放一个 `foo.skip_test` 空文件即可跳过对 `foo` 的测试。
- 不在 `code` 目录下的 Python 文件（例如 `docs/**/images/` 下画图的脚本）不会被测试。
