#include <bits/stdc++.h>
using namespace std;
const bool diff[3][3] = {{0, 0, 1}, {0, 0, 1}, {1, 1, 0}};
const int M = 2005;
int n, m, fanzhu, deadfan, rounds, tmp[M], used[M];
char ch, cu;

struct PIGS {
  int iden, bloods, perfo, dead, nxt, equip, cnt;
  char cards[M];
} a[15];

deque<char> cards_pile;

void _file() {
  freopen("pigs.in", "r", stdin);
  freopen("pigs.out", "w", stdout);
}

inline char read() {
  ch = getchar();
  while (ch < 'A' || ch > 'Z') ch = getchar();
  return ch;
}

void _init() {
  scanf("%d%d", &n, &m), fanzhu = deadfan = 0;
  for (int i = 1, las = 0; i <= n; i++) {
    a[i].bloods = a[i].cnt = 4, a[i].dead = a[i].perfo = a[i].equip = 0,
    a[i].nxt = i % n + 1;
    cu = read(), fanzhu += (cu == 'F'),
    a[i].iden = (cu != 'F') ? ((cu != 'Z') ? 0 : 1) : 2, cu = read();
    for (int j = 1; j <= 4; j++) a[i].cards[j] = read();
  }
  a[1].perfo = 1;
  for (int i = 1; i <= m; i++) cards_pile.push_back(read());
}

void get_cards(int cur) {
  a[cur].cards[++a[cur].cnt] = cards_pile.front();
  if (cards_pile.size() > 1) cards_pile.pop_front();
}

bool ought(int cur) {
  int nxt = a[cur].nxt;
  if (a[nxt].perfo == 0)
    return 0;
  else if (a[nxt].perfo == 1)
    return diff[a[cur].iden][a[nxt].iden];
  else
    return a[cur].iden == 0;
}

int atk(int cur) {
  if (a[cur].iden == 2) return 1;
  for (int nxt = a[cur].nxt; nxt != cur; nxt = a[nxt].nxt)
    if (!a[nxt].dead)
      if ((a[nxt].iden == 2 && a[nxt].perfo == 1) ||
          (a[cur].iden == 0 && a[nxt].perfo == -1))
        return nxt;
  return -1;
}

void pend(int x, int y) {
  if (a[x].iden == 0 && a[y].iden == 1) {
    for (int i = 1; i <= a[x].cnt; i++) used[i] = rounds;
    a[x].equip = 0;
  } else if (a[y].iden == 2)
    get_cards(x), get_cards(x), get_cards(x);
}

int find(int cur, char aim) {
  for (int i = 1; i <= a[cur].cnt; i++)
    if (a[cur].cards[i] == aim) return i;
  return 0;
}

void adjust(int cur, int s, int t) {
  for (int i = s; i < t; i++) a[cur].cards[i] = a[cur].cards[i + 1];
}

void respond_peach(int cur, int user) {
  int re = find(cur, 'P');
  if (cur == user) {
    re = 0;
    for (int i = 1; i <= a[cur].cnt; i++)
      if (used[i] != rounds && a[cur].cards[i] == 'P') {
        re = i;
        break;
      }
    if (re) used[re] = rounds, a[cur].bloods++;
    return;
  }
  if (re) a[cur].bloods++, adjust(cur, re, a[cur].cnt), a[cur].cnt--;
}

bool respond_dodge(int cur) {
  int re = find(cur, 'D');
  if (re) adjust(cur, re, a[cur].cnt), a[cur].cnt--;
  return re;
}

bool respond_kill(int cur, int user) {
  int re = find(cur, 'K');
  if (cur == user) {
    re = 0;
    for (int i = 1; i <= a[cur].cnt; i++)
      if (used[i] != rounds && a[cur].cards[i] == 'K') {
        re = i;
        break;
      }
    if (re) used[re] = rounds;
    return re;
  }
  if (re) adjust(cur, re, a[cur].cnt), a[cur].cnt--;
  return re;
}

bool respond_wuxie(int cur, int user) {
  int re = find(cur, 'J');
  if (cur == user) {
    re = 0;
    for (int i = 1; i <= a[cur].cnt; i++)
      if (used[i] != rounds && a[cur].cards[i] == 'J') {
        re = i;
        break;
      }
    if (re) used[re] = rounds;
    return re;
  }
  if (re) adjust(cur, re, a[cur].cnt), a[cur].cnt--;
  return re;
}

void lose_blood(int cur, int user) {
  a[cur].bloods--;
  if (a[cur].bloods < 1) respond_peach(cur, user);
}

void change_link(int cur) {
  for (int pre = 1; pre <= n; pre++)
    if (!a[pre].dead && a[pre].nxt == cur) {
      a[pre].nxt = a[cur].nxt;
      break;
    }
}

void do_peach(int cur) { a[cur].bloods++; }

void do_kill(int cur) {
  int nxt = a[cur].nxt;
  a[cur].perfo = 1;
  if (!respond_dodge(nxt)) {
    lose_blood(nxt, cur);
    if (a[nxt].bloods < 1)
      deadfan += (a[nxt].iden == 2), a[nxt].dead = 1, a[cur].nxt = a[nxt].nxt;
    if (fanzhu == deadfan || a[1].dead) return;
    if (a[nxt].bloods < 1) pend(cur, nxt);
  }
}

bool do_wuxie(int user, int cur, int aim, int now) {
  bool ret = now;
  for (int nxt = cur;;)
    if (!a[nxt].dead) {
      if (!now) {
        if (!diff[a[nxt].iden][a[aim].iden])
          if (respond_wuxie(nxt, user)) {
            a[nxt].perfo = 1;
            return do_wuxie(user, nxt, aim, 1 - now);
          }
      } else {
        if (diff[a[nxt].iden][a[aim].iden])
          if (respond_wuxie(nxt, user)) {
            a[nxt].perfo = 1;
            return do_wuxie(user, nxt, aim, 1 - now);
          }
      }
      nxt = a[nxt].nxt;
      if (nxt == cur) break;
    }
  return ret;
}

void do_fight(int cur, int aim, int user) {
  a[cur].perfo = 1;
  if (a[aim].perfo == 1) {
    if (do_wuxie(cur, cur, aim, 0)) return;
  }
  for (;;) {
    if (a[cur].iden == 0 && a[aim].iden == 1) {
      lose_blood(aim, user);
      if (a[aim].bloods < 1)
        deadfan += (a[aim].iden == 2), a[aim].dead = 1, change_link(aim);
      if (fanzhu == deadfan || a[1].dead) return;
      if (a[aim].bloods < 1) pend(cur, aim);
      return;
    } else if (!respond_kill(aim, user)) {
      lose_blood(aim, user);
      if (a[aim].bloods < 1)
        deadfan += (a[aim].iden == 2), a[aim].dead = 1, change_link(aim);
      if (fanzhu == deadfan || a[1].dead) return;
      if (a[aim].bloods < 1) pend(cur, aim);
      return;
    }
    if (!respond_kill(cur, user)) {
      lose_blood(cur, user);
      if (a[cur].bloods < 1)
        deadfan += (a[cur].iden == 2), a[cur].dead = 1, change_link(cur);
      if (fanzhu == deadfan || a[1].dead) return;
      if (a[cur].bloods < 1) pend(aim, cur);
      return;
    }
  }
}

void do_nanzhu(int cur) {
  for (int nxt = a[cur].nxt; nxt != cur; nxt = a[nxt].nxt)
    if (!a[nxt].dead) {
      if (a[nxt].perfo == 1) {
        if (do_wuxie(cur, cur, nxt, 0)) continue;
      }
      if (!respond_kill(nxt, cur)) {
        lose_blood(nxt, cur);
        if (nxt == 1 && a[cur].perfo == 0) a[cur].perfo = -1;
        if (a[nxt].bloods < 1)
          deadfan += (a[nxt].iden == 2), a[nxt].dead = 1, change_link(nxt);
        if (fanzhu == deadfan || a[1].dead) return;
        if (a[nxt].bloods < 1) pend(cur, nxt);
      }
    }
}

void do_wanjian(int cur) {
  for (int nxt = a[cur].nxt; nxt != cur; nxt = a[nxt].nxt)
    if (!a[nxt].dead) {
      if (a[nxt].perfo == 1) {
        if (do_wuxie(cur, cur, nxt, 0)) continue;
      }
      if (!respond_dodge(nxt)) {
        lose_blood(nxt, cur);
        if (nxt == 1 && a[cur].perfo == 0) a[cur].perfo = -1;
        if (a[nxt].bloods < 1)
          deadfan += (a[nxt].iden == 2), a[nxt].dead = 1, change_link(nxt);
        if (fanzhu == deadfan || a[1].dead) return;
        if (a[nxt].bloods < 1) pend(cur, nxt);
      }
    }
}

void do_zhuge(int cur) { a[cur].equip = 1; }

bool dis_cards(int cur) {
  memset(used, 0, sizeof used);
  int i, cntused, totkill = 0, counts, ret = -1, aim;
  char now;
  for (rounds = 1;; rounds++) {
    cntused = counts = 0;
    for (i = 1; i <= a[cur].cnt; i++)
      if (used[i] != rounds) {
        now = a[cur].cards[i];
        switch (now) {
          case 'P':
            if (a[cur].bloods < 4)
              do_peach(cur), used[i] = rounds, cntused++, i = a[cur].cnt;
            break;
          case 'K':
            if ((!totkill || a[cur].equip) && ought(cur))
              do_kill(cur), used[i] = rounds, cntused++, totkill++,
                            i = a[cur].cnt;
            break;
          case 'F':
            aim = atk(cur);
            if (aim != -1)
              do_fight(cur, aim, cur), used[i] = rounds, cntused++,
                                       i = a[cur].cnt;
            break;
          case 'N':
            do_nanzhu(cur), used[i] = rounds, cntused++, i = a[cur].cnt;
            break;
          case 'W':
            do_wanjian(cur), used[i] = rounds, cntused++, i = a[cur].cnt;
            break;
          case 'Z':
            do_zhuge(cur), used[i] = rounds, cntused++, i = a[cur].cnt;
            break;
          default:
            break;
        }
        if (fanzhu == deadfan || a[1].dead) {
          ret = 1;
          break;
        }
        if (a[cur].dead) {
          ret = 0;
          break;
        }
      }
    for (int i = 1; i <= a[cur].cnt; i++)
      if (used[i] != rounds) tmp[++counts] = a[cur].cards[i];
    for (int i = 1; i <= counts; i++) a[cur].cards[i] = tmp[i];
    a[cur].cnt = counts;
    if (!cntused && ret != 1) ret = 0;
    if (ret > -1) return ret;
  }
}

bool playing(int cur) {
  get_cards(cur), get_cards(cur);
  return dis_cards(cur);
}

void _duel() {
  for (int i = 1, event = 0; !event && fanzhu > 0; i = a[i].nxt)
    if (!a[i].dead) event = playing(i);
}

void _print() {
  printf("%s\n", a[1].dead ? "FP" : "MP");
  for (int i = 1; i <= n; i++) {
    if (a[i].dead)
      printf("%s", "DEAD");
    else {
      if (a[i].cnt > 0) printf("%c", a[i].cards[1]);
      for (int j = 2; j <= a[i].cnt; j++) printf(" %c", a[i].cards[j]);
    }
    puts("");
  }
}

int main() {
  _init();
  _duel();
  _print();
  return 0;
}
