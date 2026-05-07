# AlgorithmTeachingAssistant

**AlgorithmTeachingAssistant** 是一个基于 **RAG（检索增强生成）知识库** 的 ACM/ICPC 竞赛算法教学助手，采用 **苏格拉底式教学法**，引导学生主动思考，培养独立解题能力．

## 项目特点

-   **本地优先**：使用本地嵌入模型（支持中文、英文、代码），保护隐私，无需外部 API
-   **多语言支持**：三种嵌入模型自动切换（中文/BAAI/bge-small-zh-v1.5、英文/BAAI/bge-small-en-v1.5、代码/jina-embeddings-v2-base-code）
-   **增量更新**：基于文件哈希的增量索引构建，提升效率
-   **苏格拉底式教学**：通过引导性提问帮助学生深入理解算法原理，而非直接灌输答案
-   **难度自适应**：根据学生水平动态调整题目难度

## 快速开始

### 环境要求

-   Python 3.8+
-   依赖包：`chromadb`,`sentence-transformers`,`jieba`

### 安装方式

#### 使用 npx skill 安装（推荐）

```bash
npx skill install https://github.com/Swcmb/AlgorithmTeachingAssistant
```

#### 手动克隆安装

```bash
git clone https://github.com/Swcmb/AlgorithmTeachingAssistant
cd AlgorithmTeachingAssistant
pip install -r scripts/requirements.txt
```

### 构建索引

```bash
# 增量构建（推荐）
python -m scripts.build_index

# 全量重建
python -m scripts.build_index --rebuild

# 查看统计信息
python -m scripts.build_index --stats
```

### 执行检索

```bash
# 基本检索
python -m scripts.retrieve --query "动态规划背包问题" --top_k 5

# 按分类过滤（basic/dp/ds/graph/math/string）
python -m scripts.retrieve --query "树状数组" --category ds --top_k 3
```

## 在 AI 代理中使用

### 在 Claude Code 中使用

#### 方式一：作为 Skill 安装

1.  打开 Claude Code
2.  进入 **设置 > 智能体 > 技能中心**
3.  点击 **安装技能**
4.  输入 `https://github.com/Swcmb/AlgorithmTeachingAssistant`
5.  点击安装

#### 方式二：手动配置

在 Claude Code 的配置中添加以下内容：

```json
{
  "skills": {
    "AlgorithmTeachingAssistant": {
      "path": "/path/to/AlgorithmTeachingAssistant",
      "commands": {
        "retrieve": "python -m scripts.retrieve --query \"{query}\" --top_k 5",
        "build_index": "python -m scripts.build_index",
        "update_wiki": "python -m scripts.update_wiki --rebuild"
      }
    }
  }
}
```

### API 使用示例

```python
from scripts.retrieve import KnowledgeRetriever, RAGPipeline

# 初始化检索器
retriever = KnowledgeRetriever(use_local_models=True)

# 执行查询
results = retriever.search(query="Dijkstra 最短路径", top_k=5, category="graph")

# 使用 RAG 管道
pipeline = RAGPipeline(retriever)
result = pipeline.query("什么是动态规划", top_k=3)

# 处理结果
for result in results:
    print(f"标题: {result['title']}")
    print(f"分类: {result['category']}")
    print(f"评分: {result['score']}")
    print(f"摘要: {result['summary']}")
    print(f"来源: {result['source']}")
```

## 苏格拉底式教学方法

### 提问层次

| 层次      | 类型     | 示例                   | 目的     |
| ------- | ------ | -------------------- | ------ |
| Level 1 | 事实性问题  | "这个算法的时间复杂度是多少？"     | 检验基础认知 |
| Level 2 | 理解性问题  | "为什么需要使用这种数据结构？"     | 检验理解深度 |
| Level 3 | 应用性问题  | "用这个算法怎么解决这个问题？"     | 检验应用能力 |
| Level 4 | 分析评价问题 | "这种方法和另一种方法各有什么优缺点？" | 培养深度思考 |

### 实战提问技巧

1.  **反问追击**：答对时追问思路，答错时引导反思
2.  **对比启发**：通过场景对比帮助理解概念差异
3.  **极端假设**：通过极端情况理解本质原理
4.  **错误引导**：故意给出错误思路让学生纠正
5.  **角色互换**：让学生当老师，加深理解

## 知识库模块分类

| 分类         | 核心内容                        |
| ---------- | --------------------------- |
| **basic**  | 复杂度、枚举、模拟、排序、二分、分治、贪心       |
| **dp**     | 背包、区间、状压、树形、数位、DP 优化        |
| **ds**     | 并查集、树状数组、线段树、平衡树、分块         |
| **graph**  | DFS/BFS、最短路、MST、SCC、网络流、二分图 |
| **string** | 哈希、KMP、Trie、AC 自动机、后缀自动机    |
| **math**   | 数论、组合数学、线性代数、多项式、博弈论        |

## 典型使用场景

| 场景   | 输入示例                      | 处理流程                     |
| ---- | ------------------------- | ------------------------ |
| 概念理解 | "什么是动态规划？"                | 引导提问 → 解释核心思想 → 复杂度分析    |
| 算法实现 | "用 Python 实现 Dijkstra 算法" | 引导描述步骤 → 提供代码 → 复杂度分析    |
| 解题思路 | "如何解决最长公共子序列问题？"          | 问题分析 → 状态定义 → 转移方程推导     |
| 代码调试 | "我的二分查找总是死循环"             | 追问代码逻辑 → 引导发现问题 → 边界条件分析 |

## 学习路线

### 入门阶段

-   语言基础（Python/C++）
-   模拟/枚举
-   基础排序
-   前缀和/差分
-   二分查找

### 提高阶段

-   贪心算法
-   基础动态规划
-   DFS/BFS
-   并查集
-   STL 容器

### 进阶阶段

-   区间 DP/背包 DP
-   最短路算法
-   线段树/树状数组
-   字符串哈希/KMP

### 高级阶段

-   状压 DP/树形 DP
-   网络流
-   平衡树
-   后缀自动机
-   数论/组合数学

## 项目结构

    AlgorithmTeachingAssistant/
    ├── SKILL.md                    # 核心指令文件
    ├── README.md                   # 项目说明文档
    ├── models/                     # 本地嵌入模型
    │   ├── bge-small-zh-v1.5/      # 中文语义模型
    │   ├── bge-small-en-v1.5/      # 英文语义模型
    │   └── jina-embeddings-v2-base-code/  # 代码嵌入模型
    ├── scripts/                    # Python 脚本模块
    │   ├── common.py               # 通用工具函数
    │   ├── retrieve.py             # 知识检索模块
    │   ├── build_index.py          # 索引构建脚本
    │   ├── update_wiki.py          # OI-wiki 更新脚本
    │   └── requirements.txt        # 依赖清单
    └── references/db/              # RAG 知识库
        ├── summaries/              # 模块摘要
        ├── markdown/               # Markdown 文档（463+文件）
        ├── code/                   # 代码示例（458+文件）
        ├── doc/docs/               # OI Wiki 原始文档
        └── embeddings/             # ChromaDB 向量索引

## 相关链接

-   **GitHub 仓库**:<https://github.com/Swcmb/AlgorithmTeachingAssistant>
-   **OI Wiki**:<https://oi-wiki.org>

## 许可证

MIT License

## 贡献

欢迎提交 Issue 和 Pull Request！参与贡献请参考 [贡献指南](https://github.com/OI-wiki/OI-wiki/blob/master/.github/CONTRIBUTING.md)．
