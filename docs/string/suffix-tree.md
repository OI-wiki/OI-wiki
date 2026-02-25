后缀树是一种维护一个字符串所有后缀的数据结构．

## 一些记号

记构建后缀树的母串为 $S$，长度为 $n$，字符集为 $\Sigma$．

令 $S[i]$ 表示 $S$ 中的第 $i$ 个字符，其中 $1 \le i \le n$．

令 $S [l, r]$ 表示 $S$ 中第 $l$ 个字符至第 $r$ 个字符组成的字符串，称为 $S$ 的一个子串．

记 $S [i, n]$ 为 $S$ 的以 $i$ 开头的后缀，$S [1, i]$ 为 $S$ 的以 $i$ 结尾的前缀．

## 定义

定义字符串 $S$ 的 **后缀 trie** 为将 S 的所有后缀插入至 trie 树中得到的字典树．在后缀 trie 中，节点 x 对应的字符串为从根节点走到 x 的路径上经过的字符拼接而成的字符串．记后
缀 trie 中所有对应 $S$ 的某个后缀的节点为后缀节点．

容易看出后缀 trie 的优越性质：它的非根节点恰好能接受 $S$ 的所有本质不同非空子串．但构建后缀 trie 的时空复杂度均为 $O(n^2)$，在很多情况下不能接受，所以我们引入后缀树的概念．

如果令后缀 trie 中所有拥有多于一个儿子的节点和后缀节点为关键点，定义只保留关键点，将非关键点形成的链压缩成一条边形成的压缩 trie 树为 **后缀树 (Suffix Tree)**．如果仅令后缀 trie 中所有拥有多于一个儿子的节点和叶结点为关键点，定义只保留关键点形成的压缩 trie 树为 **隐式后缀树 (Implicit Suffix Tree)**．容易看出隐式后缀树为后缀树进一步压缩后得到的结果．

在后缀树和隐式后缀树中，每条边对应一个字符串；每个非根节点 $x$ 对应了一个字符串集合，为从根节点走到 $x$ 的父亲节点 $fa_x$ 经过的字符串，拼接上 $fa_x$ 至 $x$ 的树边对应的字符串的任意一个非空前缀，称为 $str_x$．同时，在隐式后缀树中，称一个没有对应任何节点的后缀为 **隐式后缀**．

下图从左至右分别为以字符串 $\texttt{cabab}$ 为母串构建的后缀 trie、后缀树和隐式后缀树．

![suffix-tree\_cabab1.png](./images/suffix-tree1.png)

考虑将 $S$ 的后缀逐个插入至后缀 trie 中．从第二次插入开始，每次最多新增一个拥有多于一个儿子的节点和一个后缀节点，所以后缀树中节点个数最多为 $2n$ 个，十分优秀．

## 后缀树的建立

### 支持前端动态添加字符的算法

反串建 SAM 建出的 parent 树就是这个串的后缀树，所以我们将反串的字符逐个加入 SAM 即可．

???+ note "参考实现"
    ```cpp
    struct SuffixAutomaton {
      int tot, lst;
      int siz[N << 1];
      int buc[N], id[N << 1];
    
      struct Node {
        int len, link;
        int ch[26];
      } st[N << 1];
    
      SuffixAutomaton() : tot(1), lst(1) {}
    
      void extend(int ch) {
        int cur = ++tot, p = lst;
        lst = cur;
        siz[cur] = 1, st[cur].len = st[p].len + 1;
        for (; p && !st[p].ch[ch]; p = st[p].link) st[p].ch[ch] = cur;
        if (!p)
          st[cur].link = 1;
        else {
          int q = st[p].ch[ch];
          if (st[q].len == st[p].len + 1)
            st[cur].link = q;
          else {
            int pp = ++tot;
            st[pp] = st[q];
            st[pp].len = st[p].len + 1;
            st[cur].link = st[q].link = pp;
            for (; p && st[p].ch[ch] == q; p = st[p].link) st[p].ch[ch] = pp;
          }
        }
      }
    } SAM;
    ```

### 支持后端动态添加字符的算法

Ukkonen 算法是一种增量构造算法．我们依次向树中插入串 $S$ 的每一个字符，并在每一次插入之后正确地维护当前的后缀树．

#### 朴素算法

首先介绍一下一种较为暴力的构建方式，我们用字符串 $\texttt {abbbc}$ 来演示一下构建的过程．

初始建立一个根节点，称为 $0$ 号节点．同时每条边我们维护一个区间 $[l,r]$ 表示这条边上的字符串为 $S[l,r]$．另外，维护已经插入的字符个数 $m$，初始为 $0$．

首先插入字符 $\texttt a$，直接从 $0$ 号节点伸出一条边，标为 $[1,\infty]$，指向一个新建的节点．这里的 $\infty$ 是一个极大值，可理解为串的结尾，这样在插入新字符时，这条边会自动的包含新的字符．

![suffix-tree\_a.webp](./images/suffix-tree2.webp)

接下来我们插入字符 $\texttt b$，同样从 $0$ 伸出一条边，标为 $[2,\infty⁡]$．注意到之前延伸出的边 $[1,\infty]$ 的意义自动地发生了变化，随着串结尾的改变，其表示的串从 $\texttt a$ 变为了 $\texttt {ab}$．这样是正确的，因为之前所有后缀都已经以一个叶节点的形式出现在树中，只需要向所有叶节点的末端插入一个当前字符即可．

![suffix-tree\_ab.webp](./images/suffix-tree3.webp)

接下来，我们要再次插入一个字符 $\texttt b$，但是 $\texttt b$ 是之前已经插入的字符串的一个子串，因此原树已经包含 $\texttt b$，此时，我们什么都不做，记录一个 $k$ 表示 $S[k,m]$ 是当前最长的隐式后缀．

![suffix-tree\_abb.webp](./images/suffix-tree4.webp)

接下来我们插入另一个 $\texttt b$．因为前一个 $\texttt b$ 没有插入成功，此时 $k=3$，代表要插入的后缀为 $\texttt {bb}$．我们从根开始向下寻找 $\texttt {bb}$，发现也在原树之中．同样，我们还是什么都不做．

![suffix-tree\_abbb.webp](./images/suffix-tree5.webp)

注意到我们没有管 $k$ 之后的后缀．因为如果 $S[k,m]$ 是一个隐式后缀，那么对于 $l>k$，$S[l,m]$ 都是隐式后缀．因为由 $S[k,m]$ 为隐式后缀可知，存在字符 $c$ 使得 $S[k, m] + c$ 为 $S$ 的子串，所以 $S [ l, m] + c$ 也为 $S$ 的子串，由隐式后缀树的定义可知 $S[ l, m]$ 也不作为叶结点出现．

接下来我们插入 $\texttt c$，此时 $k=3$，因此我们需要沿着根向下寻找 $\texttt {bbc}$，发现不在原树中．我们需要在 $\texttt {bb}$ 处代表的节点延伸出一条为 $[5,\infty]$ 的出边．但发现这个节点其实不存在，而是包含在一条边中，因此我们需要分裂这条边，创建一个新节点，再在创建的节点处伸展出我们要创建的出边．此时成功插入，令 $k\to k+1$，因为 $S[k,m]$ 不再是隐式后缀．

![suffix-tree\_abbbc1.webp](./images/suffix-tree6.webp)

接下来，因为 $k$ 变化了，我们重复这个过程，直到再次出现隐式后缀，或 $k>m$（在这个例子中，是后者）．

![suffix-tree\_abbbc2.webp](./images/suffix-tree7.webp)

构建过程结束．

该算法每次暴力从根向下寻找并插入的复杂度最坏为 $O(n)$，所以总的复杂度为 $O(n^2)$．

#### 后缀链接

朴素算法慢主要是因为每次 extend 都要从根找到最长隐式后缀的插入位置．所以考虑把这个位置记下来．首先，我们采用一个二元组 $(now,rem)$ 来描述当前这个最长的被隐式包含的后缀 $S[k,m]$．沿着节点 $now$ 的开头为 $S[m-rem+1]$ 的出边走长度 $rem$ 到达的位置应该唯一表示一个字符串，每次插入新的字符时，我们只需要从 $now$ 和 $rem$ 描述的位置查找即可．

现在，我们只需要在 $k\to k + 1$ 时更新 $(now,rem)$．此时如果 $now=0$，只需要让 $rem \to rem-1$，因为下一个要插入的后缀是刚才插入的长度 $-1$．否则，设 $str_{now}$ 对应的子串为 $S[l,r]$，我们需要找到一个节点 $now'$ 对应 $S[l+1,r]$，令 $now\to now'$ 即可．

首先有引理：对隐式后缀树中任意非叶非根节点 $x$，在树中存在另一非叶节点 $y$，使得 $str_y$ 是 $str_x$ 对应的子串删去开头的字符．

证明．令 $s$ 表示 $str_x$ 删去开头字符形成的字符串．由隐式后缀树的定义可知，存在两个不同的字符 $c_1,c_2$，满足 $str_x + c1$ 与 $str_x + c_2$ 均为 $S$ 的子串．所以，$s + c_1$ 与 $s + c_2$ 也为 $S$ 的子串，所以 $s$ 在后缀 trie 中也对应了一个有分叉的关键点，即在隐式后缀 trie 中存在 $y$ 使得 $str_y=s$．证毕．

由该引理，我们定义 $\operatorname{Link}(x)=y$，称为 x 的 **后缀链接 (Suffix Link)**．于是 $now'=\operatorname{Link}(now)$ 一定存在．现在我们只要能求出隐式后缀树中所有非根非叶节点的 $\operatorname{Link}$ 即可．

#### 扩展规则

在介绍 Ukkonen 算法之前，我们首先需要理解算法的核心：**三条扩展规则**．对于每个阶段 $i$，算法需要将字符 $S[i]$ 添加到所有当前后缀的末尾．根据后缀在树中的位置，应用以下规则：

-   **规则 1（叶节点扩展）**：如果路径终止于叶节点，则自动延长叶边．由于叶边的右端点为 $\infty$（全局结束指针），所有叶节点会隐式地同时扩展，无需显式操作．

-   **规则 2（创建新叶节点）**：如果路径终止于非叶节点（内部节点或边的中间位置），且不存在以当前字符开头的出边，则需要：
    -   **情况 A**：若位置恰好在某个节点上，直接从该节点创建新的叶边．
    -   **情况 B**：若位置在某条边的中间，需要先分裂该边创建新的内部节点，再从新节点创建叶边．

-   **规则 3（隐式扩展/早停）**：如果路径终止于非叶节点，且存在以当前字符开头的出边，则当前后缀已经隐式存在于树中，不需要任何操作．此时可以立即停止当前阶段的扩展（因为更短的后缀也一定是隐式的）．

#### 关键优化技术

Ukkonen 算法通过以下优化达到 $O(n)$ 时间复杂度：

1.  **边标签压缩**：用索引对 $(start, end)$ 代替实际字符串存储边标签，空间从 $O(n^2)$ 降至 $O(n)$．

2.  **全局结束指针（Global End）**：所有叶节点的边共享一个全局结束指针．当插入新字符时，只需将此指针加一，即可在 $O(1)$ 时间内完成所有叶节点的扩展（规则 1）．这利用了 "一旦成为叶节点，永远是叶节点" 的性质．

3.  **后缀链接（Suffix Link）**：内部节点之间的快速跳转．若节点 $v$ 对应字符串 $x\alpha$（$x$ 为单个字符，$\alpha$ 为可能为空的字符串），则 $\operatorname{Link}(v)$ 指向对应字符串 $\alpha$ 的节点．

4.  **Skip/Count 技巧**：当已知要遍历的路径长度时，可以直接跳过整条边而无需逐字符比较，加速边的遍历．

5.  **早停优化**：一旦应用规则 3，当前阶段可以立即停止，因为所有更短的后缀也一定是隐式的．

#### Ukkonen 算法

Ukkonen 算法的整体流程如下：

为了构建隐式后缀树，我们从前往后加入 $S$ 中的字符．假设根节点为 $0$，且当前已经建出 $S[1, m]$ 的隐式后缀树且维护好了后缀链接．$S [1, m]$ 的最长隐式后缀为 $S [k, m]$，在树中的位置为 $(now, rem)$．设 $S [m + 1] = x$, 现在我们需要加入字符 $x$．此时，$S [1, m]$ 的每一个后缀都需要在末尾添加字符 $x$．由于所有显式后缀都对应树中某个叶结点，它们父边右端点为 $\infty$，无需维护．所以，现在我们只用考虑隐式后缀末尾添加 x 对树的形态产生的影响．首先考虑 $S [k, m]$，有两种情况：

1.  $(now, rem)$ 位置已经存在 $x$ 的转移．此时后缀树形态不会发生变化．由于 $S [k, m+1]$ 已经在后缀树中出现，所以对于 $l > k$，$S [ l, m + 1]$ 也会在后缀树中出现，此时只需将 $rem\to rem + 1$，不需做任何修改．
2.  $(now, rem)$ 不存在 $x$ 的转移．如果 $(now, rem)$ 恰好为树中的节点，则此节点新增一条出边 $x$；否则需要对节点进行分裂，在此位置新增一个节点，并在新增节处添加出边 $x$．此时对于 $l > k$，我们并不知道 $S [ l, m]$ 会对后缀树形态造成什么影响，所以我们还需继续考虑 $S [k + 1, m]$．考虑怎么求出 $S [k + 1, m]$ 在后缀树中的位置：如果 $now$ 不为 $0$，可以利用后缀链接，令 $now = \operatorname{Link}(now)$；否则，令 $rem\to rem − 1$．最后令 $k\to k + 1$，再次重复这个过程．

每一步都只消耗常数时间，而算法在插入全部的字符后停止，所以时间复杂度为 $O(n)$．

由于 Ukkonen 算法只能处理出 $S$ 的隐式后缀树，而隐式后缀树在一些问题中的功能可能不如后缀树强大，所以在需要时，可以在 $S$ 的末端添加一个从未出现过的字符，这时 S 的所有后缀可以和树的所有叶子一一对应．

???+ note "参考实现"
    ```cpp
    struct SuffixTree {
      int ch[M + 5][RNG + 1], st[M + 5], len[M + 5], link[M + 5];
      int s[N + 5];
      int now{1}, rem{0}, n{0}, tot{1};
    
      SuffixTree() { len[0] = inf; }
    
      int new_node(int s, int le) {
        ++tot;
        st[tot] = s;
        len[tot] = le;
        return tot;
      }
    
      void extend(int x) {
        s[++n] = x;
        ++rem;
        for (int lst{1}; rem;) {
          while (rem > len[ch[now][s[n - rem + 1]]])
            rem -= len[now = ch[now][s[n - rem + 1]]];
          int &v{ch[now][s[n - rem + 1]]}, c{s[st[v] + rem - 1]};
          if (!v || x == c) {
            lst = link[lst] = now;
            if (!v)
              v = new_node(n, inf);
            else
              break;
          } else {
            int u{new_node(st[v], rem - 1)};
            ch[u][c] = v;
            ch[u][x] = new_node(n, inf);
            st[v] += rem - 1;
            len[v] -= rem - 1;
            lst = link[lst] = v = u;
          }
          if (now == 1)
            --rem;
          else
            now = link[now];
        }
      }
    } Tree;
    ```

???+ note "参考实现（Python 工程风格，带详细注释）"
    以下是具有完整类型注解和详细文档的 Python 实现，便于理解算法细节：
    
    ```python
    """
    Ukkonen's Suffix Tree: Linear-Time Online Construction Algorithm
    
    Extension Rules:
        Rule 1: Path ends at a leaf → Extend the leaf edge (implicit via global end)
        Rule 2: Path ends at non-leaf with no continuation → Create new leaf node
        Rule 3: Path ends at non-leaf with matching continuation → Do nothing (implicit)
    
    Key Optimizations:
        1. Edge-label compression: Store (start, end) indices instead of substrings
        2. Suffix links: O(1) transitions between internal nodes during extensions
        3. Skip/Count trick: Rapid edge traversal using known edge lengths
        4. Global end pointer: Implicit Rule 1 extensions in O(1) amortized time
        5. Early termination: Stop phase on Rule 3 application (showstopper)
    
    References:
        [1] Ukkonen, E. (1995). "On-line construction of suffix trees"
            Algorithmica, 14(3), 249-260.
        [2] Gusfield, D. (1997). "Algorithms on Strings, Trees, and Sequences"
            Cambridge University Press. Chapter 6.
    """
    
    from typing import Dict, List, Optional, Tuple, Union
    
    
    class GlobalEnd:
        """
        Mutable container for the global end index of leaf nodes.
    
        All leaf edges share this common end point. By incrementing it once,
        all leaf edges extend simultaneously in O(1) time.
        This implements the "once a leaf, always a leaf" property.
        """
    
        def __init__(self, index: int = -1):
            self.index = index
    
        def increment(self) -> int:
            """Advance the global end and return the new value."""
            self.index += 1
            return self.index
    
    
    class SuffixTreeNode:
        """
        Node in the suffix tree data structure.
    
        Edge labels are stored as index pairs (start, end) into the original string,
        reducing space from O(n²) to O(n).
    
        Attributes:
            children: Map from first character to child node
            suffix_link: Pointer to suffix-linked node (None for leaves)
            edge_start_index: Start position of edge label in original string
            edge_end_index: End position (int for internal, GlobalEnd for leaves)
        """
    
        def __init__(self, start: int, end: Union[int, GlobalEnd]):
            self.children: Dict[str, "SuffixTreeNode"] = {}
            self.suffix_link: Optional["SuffixTreeNode"] = None
            self.edge_start_index: int = start
            self.edge_end_index: Union[int, GlobalEnd] = end
    
        def get_child(self, char: str) -> Optional["SuffixTreeNode"]:
            """Retrieve child node by edge's first character, or None."""
            return self.children.get(char)
    
        def get_edge_length(self) -> int:
            """Compute the length of the incoming edge label."""
            if self.edge_start_index == -1:
                return 0
            end = (
                self.edge_end_index.index
                if isinstance(self.edge_end_index, GlobalEnd)
                else self.edge_end_index
            )
            return end - self.edge_start_index + 1
    
        def is_leaf(self) -> bool:
            """Check if this node is a leaf (has GlobalEnd as end index)."""
            return isinstance(self.edge_end_index, GlobalEnd)
    
        def is_root(self) -> bool:
            """Check if this node is the root."""
            return self.edge_start_index == -1
    
    
    class UkkonenSuffixTree:
        """
        Suffix tree constructed using Ukkonen's online algorithm.
    
        Example:
            >>> tree = UkkonenSuffixTree("banana$")
            >>> tree.get_suffix_array()
            [6, 5, 3, 1, 0, 4, 2]
        """
    
        def __init__(self, text: str):
            self.text = text
            self.size = len(text)
            self.root = self._build_tree()
    
        def _build_tree(self) -> SuffixTreeNode:
            """Implement Ukkonen's algorithm with all optimizations."""
            # Initialize root with self-referencing suffix link
            root = SuffixTreeNode(-1, -1)
            root.suffix_link = root
    
            # Global end pointer for O(1) leaf extensions (Rule 1)
            global_end = GlobalEnd(-1)
    
            # Active point: (node, edge_char, length_on_edge)
            active_node = root
            active_edge = ""
            active_length = 0
    
            # For skip/count optimization
            total_steps = 0
    
            # Previous internal node awaiting suffix link
            prev_internal_node: Optional[SuffixTreeNode] = None
    
            # Last j where Rule 1 or 2 was applied
            last_rule_12_j = -1
    
            # Process each phase (add character at position i)
            for i in range(self.size):
                # Implicit extension of all leaves via global_end
                global_end.increment()
                prev_internal_node = None
    
                # Process extensions for this phase
                j = last_rule_12_j + 1
                while j <= i:
                    current_char = self.text[i]
    
                    if active_length == 0:
                        active_edge = current_char
    
                    # Navigate using skip/count
                    next_node = active_node.get_child(active_edge)
                    next_node, active_node, active_edge, active_length, total_steps = (
                        self._skip_count_traverse(
                            next_node,
                            active_node,
                            active_edge,
                            active_length,
                            j,
                            total_steps,
                        )
                    )
    
                    # Apply extension rules
                    if next_node is None:
                        # Rule 2 (Case A): No outgoing edge - create new leaf
                        new_leaf = SuffixTreeNode(i, global_end)
                        active_node.children[active_edge] = new_leaf
                        if prev_internal_node:
                            prev_internal_node.suffix_link = active_node
                        prev_internal_node = None
                        last_rule_12_j = j
    
                    elif (
                        self.text[next_node.edge_start_index + active_length]
                        == current_char
                    ):
                        # Rule 3: Character exists - implicit extension (showstopper)
                        if prev_internal_node:
                            prev_internal_node.suffix_link = active_node
                        active_length += 1
                        break  # Early termination
    
                    else:
                        # Rule 2 (Case B): Split edge and create new leaf
                        split_end = next_node.edge_start_index + active_length - 1
                        split_node = SuffixTreeNode(next_node.edge_start_index, split_end)
                        active_node.children[active_edge] = split_node
    
                        # Create new leaf for current suffix
                        new_leaf = SuffixTreeNode(i, global_end)
                        split_node.children[current_char] = new_leaf
    
                        # Reconnect existing subtree
                        next_node.edge_start_index += active_length
                        split_node.children[self.text[next_node.edge_start_index]] = (
                            next_node
                        )
    
                        # Handle suffix links
                        if prev_internal_node:
                            prev_internal_node.suffix_link = split_node
                        prev_internal_node = split_node
                        last_rule_12_j = j
    
                    # Update active point for next extension
                    if active_node.is_root() and active_length > 0:
                        active_length -= 1
                        if j + 1 < self.size:
                            active_edge = self.text[j + 1]
    
                    if total_steps > 0:
                        total_steps -= 1
    
                    if not active_node.is_root():
                        active_node = active_node.suffix_link or root
    
                    j += 1
    
            return root
    
        def _skip_count_traverse(
            self,
            next_node: Optional[SuffixTreeNode],
            active_node: SuffixTreeNode,
            active_edge: str,
            active_length: int,
            j: int,
            total_steps: int,
        ) -> Tuple[Optional[SuffixTreeNode], SuffixTreeNode, str, int, int]:
            """
            Skip/Count optimization for rapid edge traversal.
    
            When we know the length of the path to traverse, we can skip entire
            edges without character-by-character comparison.
            """
            if next_node is None:
                return next_node, active_node, active_edge, active_length, total_steps
    
            edge_length = next_node.get_edge_length()
            position = j + total_steps
    
            while edge_length <= active_length:
                active_length -= edge_length
                total_steps += edge_length
                position += edge_length
    
                if position < self.size:
                    active_edge = self.text[position]
    
                active_node = next_node
                next_node = next_node.get_child(active_edge)
    
                if next_node is None:
                    break
                edge_length = next_node.get_edge_length()
    
            return next_node, active_node, active_edge, active_length, total_steps
    
        def get_suffix_array(self) -> List[int]:
            """Extract suffix array via DFS traversal."""
            suffix_array: List[int] = []
            self._dfs_collect_suffixes(self.root, 0, suffix_array)
            return suffix_array
    
        def _dfs_collect_suffixes(
            self, node: SuffixTreeNode, depth: int, result: List[int]
        ) -> None:
            """DFS to collect suffix positions in lexicographic order."""
            edge_length = 0 if node.is_root() else node.get_edge_length()
    
            if node.is_leaf():
                suffix_start = self.size - depth - edge_length
                result.append(suffix_start)
            else:
                for char in sorted(node.children.keys()):
                    self._dfs_collect_suffixes(
                        node.children[char], depth + edge_length, result
                    )
    
        def print_tree(
            self, node: Optional[SuffixTreeNode] = None, indent: int = 0
        ) -> None:
            """Print tree structure for debugging."""
            if node is None:
                node = self.root
                print("ROOT")
    
            for char, child in sorted(node.children.items()):
                end = (
                    child.edge_end_index.index
                    if isinstance(child.edge_end_index, GlobalEnd)
                    else child.edge_end_index
                )
                edge_label = self.text[child.edge_start_index : end + 1]
                node_type = "LEAF" if child.is_leaf() else "INTERNAL"
                print("  " * (indent + 1) + f"--[{edge_label}]--> {node_type}")
                self.print_tree(child, indent + 1)
    
    
    # 使用示例
    if __name__ == "__main__":
        tree = UkkonenSuffixTree("banana$")
        tree.print_tree()
        print(f"Suffix Array: {tree.get_suffix_array()}")
    ```

## 复杂度分析

| 操作       | 时间复杂度        | 空间复杂度  |
| -------- | ------------ | ------ |
| 后缀树构建    | $O(n)$       | $O(n)$ |
| 后缀数组提取   | $O(n)$       | $O(n)$ |
| 子串匹配     | $O(m)$       | $O(1)$ |
| 最长公共前缀查询 | $O(1)$（预处理后） | $O(n)$ |

其中 $n$ 为文本长度，$m$ 为模式串长度．

## 作用

后缀树上每一个节点到根的路径都是 $S$ 的一个非空子串，这在处理很多字符串问题时都很有用．

后缀树的 DFS 序就是后缀数组．后缀树的一个子树也就对应到后缀数组上的一个区间．后缀树上两个后缀的最长公共前缀是它们对应的叶节点的 LCA，因此，后缀数组的 height 的结论可以理解为树上若干个节点的 LCA 等于 DFS 序最小的和最大的节点的 LCA．

## 例题

### [洛谷 P3804【模板】后缀自动机（SAM）](https://www.luogu.com.cn/problem/P3804)

题意：

给定一个只包含小写字母的字符串 $S$．

请你求出 $S$ 的所有出现次数不为 $1$ 的子串的出现次数乘上该子串长度的最大值．

??? note "解法"
    建出插入一个终止符的隐式后缀树．树上每条从根出发的路径都构成子串．一个显示后缀的出现次数即为对应节点子树内的叶子节点个数，隐式后缀不用考虑，因为一个隐式后缀的出现次数等于向下走到的第一个节点对应显示后缀的出现次数，而且一定没有该显示后缀长．所以遍历整棵树，求出每个节点子树内叶子个数和每个节点到根的路径长度．如果叶子个数 $>1$ 则更新答案．复杂度 $O(|S||\Sigma|)$．

??? note "参考代码"
    ```cpp
    --8<-- "docs/string/code/suffix-tree/suffix-tree_1.cpp"
    ```

### [CF235C Cyclical Quest](https://codeforces.com/problemset/problem/235/C)

题意：给定一个小写字母主串 $S$ 和 $n$ 个询问串，求每个询问串 $x_i$ 的所有循环同构在主串中出现的次数总和．

??? note "解法"
    建立插入终止符的隐式后缀树．
    
    枚举当前在那个循环节，记录在树上能查找到多长的前缀．
    
    重复类似 Ukkonen 算法的过程，记录当前能匹配到的位置 $(now,rem)$．每次尝试插入下一个字符，如果成功则继续插入，否则跳出循环．
    
    如果某一个次成功匹配了当前的循环节，且该循环节之前没出现过，则更新答案．
    
    然后切换到下个循环节的时候，我们要删去当前匹配的子串开头的字符：这正好就相当于令 $now \to \operatorname{Link}(now)$．当然，如果 $now=1$ 则直接让 $rem\to rem-1$ 就行了．
    
    复杂度 $O(|S||\Sigma|+\sum|x_i|)$

??? note "参考代码"
    ```cpp
    --8<-- "docs/string/code/suffix-tree/suffix-tree_2.cpp"
    ```

## 参考文献

### 原始学术论文

1.  Ukkonen, E. (1995). "On-line construction of suffix trees".*Algorithmica*, 14(3), 249-260.
2.  Gusfield, D. (1997). "Algorithms on Strings, Trees, and Sequences: Computer Science and Computational Biology".*Cambridge University Press*. Chapter 6: Linear-Time Construction of Suffix Trees.
3.  McCreight, E. M. (1976). "A space-economical suffix tree construction algorithm".*Journal of the ACM*, 23(2), 262-272.
4.  Weiner, P. (1973). "Linear pattern matching algorithms".*14th Annual Symposium on Switching and Automata Theory*, 1-11.

### 中文资料

5.  2021 国家集训队论文《后缀树的构建》代晨昕
6.  [炫酷后缀树魔术 - EternalAlexander 的博客](https://www.luogu.com.cn/blog/EternalAlexander/xuan-ku-hou-zhui-shu-mo-shu)
