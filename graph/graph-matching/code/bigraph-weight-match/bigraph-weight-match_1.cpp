#include <algorithm>
#include <cstdio>
#include <cstring>
#include <list>
using namespace std;
typedef long long LL;
const LL INF = (LL)1e15;
const int MAXV = 105;

int N, mateS[MAXV], mateT[MAXV], p[MAXV];
LL u[MAXV], v[MAXV], slack[MAXV];
LL W[MAXV][MAXV];
bool m[MAXV];
list<int> Q;

void readMatrix() {
  scanf("%d", &N);
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++) scanf("%lld", &W[i][j]);
}

void initHungarian() {
  memset(mateS, -1, sizeof(mateS));
  memset(mateT, -1, sizeof(mateT));
  for (int i = 0; i < N; i++) {
    u[i] = -INF;
    for (int j = 0; j < N; j++) u[i] = max(u[i], W[i][j]);
    v[i] = 0;
  }
}

void augment(int j) {
  int i, next;
  do {
    i = p[j];
    mateT[j] = i;
    next = mateS[i];
    mateS[i] = j;
    if (next != -1) j = next;
  } while (next != -1);
}

LL hungarian() {
  int nres = 0;
  for (int i = 0; i < N; i++)
    if (mateS[i] == -1) nres++;

  while (nres > 0) {
    for (int i = 0; i < N; i++) {
      m[i] = false;
      p[i] = -1;
      slack[i] = INF;
    }
    bool aug = false;
    Q.clear();
    for (int i = 0; i < N; i++)
      if (mateS[i] == -1) {
        Q.push_back(i);
        break;
      }

    do {
      int i, j;
      i = Q.front();
      Q.pop_front();
      m[i] = true;
      j = 0;

      while (aug == false && j < N) {
        if (mateS[i] != j) {
          LL minSlack = u[i] + v[j] - W[i][j];
          if (minSlack < slack[j]) {
            slack[j] = minSlack;
            p[j] = i;
            if (slack[j] == 0) {
              if (mateT[j] == -1) {
                augment(j);
                aug = true;
                nres--;
              } else
                Q.push_back(mateT[j]);
            }
          }
        }
        j++;
      }

      if (aug == false && Q.size() == 0) {
        LL minSlack = INF;
        for (int k = 0; k < N; k++)
          if (slack[k] > 0) minSlack = min(minSlack, slack[k]);
        for (int k = 0; k < N; k++)
          if (m[k]) u[k] -= minSlack;

        int x = -1;
        bool X[MAXV];
        for (int k = 0; k < N; k++)
          if (slack[k] == 0)
            v[k] += minSlack;
          else {
            slack[k] -= minSlack;
            if (slack[k] == 0 && mateT[k] == -1) x = k;
            if (slack[k] == 0)
              X[k] = true;
            else
              X[k] = false;
          }

        if (x == -1) {
          for (int k = 0; k < N; k++)
            if (X[k]) Q.push_back(mateT[k]);
        } else {
          augment(x);
          aug = true;
          nres--;
        }
      }
    } while (aug == false);
  }

  LL ans = 0;
  for (int i = 0; i < N; i++) ans += (u[i] + v[i]);
  return ans;
}

void dynamicHungarian() {
  char type[2];
  LL w;
  int i, j;

  scanf("%s", type);
  if (type[0] == 'C') {
    scanf("%d%d%lld", &i, &j, &w);
    if ((w < W[i][j]) && (mateS[i] == j)) {
      W[i][j] = w;
      if (mateS[i] != -1) {
        mateT[mateS[i]] = -1;
        mateS[i] = -1;
      }
    } else if ((w > W[i][j]) && (u[i] + v[j] < w)) {
      W[i][j] = w;
      u[i] = -INF;
      for (int c = 0; c < N; c++) u[i] = max(u[i], W[i][c] - v[c]);
      if (mateS[i] != j) {
        mateT[mateS[i]] = -1;
        mateS[i] = -1;
      }
    } else
      W[i][j] = w;
  } else if (type[0] == 'X') {
    scanf("%d", &i);
    for (int c = 0; c < N; c++) scanf("%lld", &W[i][c]);
    if (mateS[i] != -1) {
      mateT[mateS[i]] = -1;
      mateS[i] = -1;
    }
    u[i] = -INF;
    for (int c = 0; c < N; c++) u[i] = max(u[i], W[i][c] - v[c]);
  } else if (type[0] == 'Y') {
    scanf("%d", &j);
    for (int r = 0; r < N; r++) scanf("%lld", &W[r][j]);
    if (mateT[j] != -1) {
      mateS[mateT[j]] = -1;
      mateT[j] = -1;
    }
    v[j] = -INF;
    for (int r = 0; r < N; r++) v[j] = max(v[j], W[r][j] - u[r]);
  } else if (type[0] == 'A') {
    i = j = N++;
    u[i] = -INF;
    for (int c = 0; c < N; c++) u[i] = max(u[i], W[i][c] - v[c]);
    v[j] = -INF;
    for (int r = 0; r < N; r++) v[j] = max(v[j], W[r][j] - u[r]);
  } else if (type[0] == 'Q')
    printf("%lld\n", hungarian());
}

int main() {
  readMatrix();
  initHungarian();
  LL ans = hungarian();
  int M;
  scanf("%d", &M);
  while (M--) dynamicHungarian();
  return 0;
}