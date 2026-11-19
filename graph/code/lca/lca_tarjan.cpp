#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

class Edge {
 public:
  int toVertex, fromVertex;
  int next;
  int LCA;
  Edge() : toVertex(-1), fromVertex(-1), next(-1), LCA(-1) {};
  Edge(int u, int v, int n) : fromVertex(u), toVertex(v), next(n), LCA(-1) {};
};

constexpr int MAX = 100;
int head[MAX], queryHead[MAX];
Edge edge[MAX], queryEdge[MAX];
// ancestor[r]：以 r 为根的集合中深度最小的结点
int parent[MAX], setSize[MAX], ancestor[MAX], visited[MAX];
int vertexCount, queryCount;

int find(int x) {
  if (parent[x] == x) {
    return x;
  } else {
    return parent[x] = find(parent[x]);
  }
}

// 按集合大小合并 x 与 y 所在的集合，返回合并后集合的根
int unite(int x, int y) {
  x = find(x);
  y = find(y);
  if (setSize[x] < setSize[y]) swap(x, y);
  parent[y] = x;
  setSize[x] += setSize[y];
  return x;
}

void tarjan(int u) {
  parent[u] = u;
  setSize[u] = 1;
  ancestor[u] = u;
  visited[u] = 1;

  for (int i = head[u]; i != -1; i = edge[i].next) {
    Edge& e = edge[i];
    if (!visited[e.toVertex]) {
      tarjan(e.toVertex);
      // 子树并入 u 所在的集合，合并后集合中深度最小的结点仍是 u
      ancestor[unite(u, e.toVertex)] = u;
    }
  }

  for (int i = queryHead[u]; i != -1; i = queryEdge[i].next) {
    Edge& e = queryEdge[i];
    if (visited[e.toVertex]) {
      queryEdge[i ^ 1].LCA = e.LCA = ancestor[find(e.toVertex)];
    }
  }
}

int main() {
  memset(head, 0xff, sizeof(head));
  memset(queryHead, 0xff, sizeof(queryHead));

  cin >> vertexCount >> queryCount;
  int count = 0;
  for (int i = 0; i < vertexCount - 1; i++) {
    int start = 0, end = 0;
    cin >> start >> end;

    edge[count] = Edge(start, end, head[start]);
    head[start] = count;
    count++;

    edge[count] = Edge(end, start, head[end]);
    head[end] = count;
    count++;
  }

  count = 0;
  for (int i = 0; i < queryCount; i++) {
    int start = 0, end = 0;
    cin >> start >> end;

    queryEdge[count] = Edge(start, end, queryHead[start]);
    queryHead[start] = count;
    count++;

    queryEdge[count] = Edge(end, start, queryHead[end]);
    queryHead[end] = count;
    count++;
  }

  tarjan(1);

  for (int i = 0; i < queryCount; i++) {
    Edge& e = queryEdge[i * 2];
    cout << "(" << e.fromVertex << "," << e.toVertex << ") " << e.LCA << endl;
  }

  return 0;
}
