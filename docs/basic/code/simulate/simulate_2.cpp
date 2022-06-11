#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#define for_i_in_hand for (itr i = hand.begin(); i < hand.end(); i++)
#define itr std::vector<card>::iterator

using std::cin;
using std::cout;
using std::endl;

struct card {
  bool avai;
  char card;
};

class Pig {
 public:
  // 方法
  void identity_set(char id);  // 身份初始化

  void turn_start();  // 回合开始
  void draw();        // 抽一张牌
  void act();         // 出牌阶段

  void use_card(itr i, char ch);  // 使用卡牌
  bool find_and_use(char ch);     // 在手牌中寻找并打出一张牌
  int dec_health();               // 生命值减少
  int inc_health();               // 生命值增加
  void jump();                    // 跳身份
  void go_rebel_like();           // 进入类反状态
  void ungo_rebel_like();         // 取消类反状态
  void unequip();                 // 卸下诸葛连弩
  void hurt(Pig &that);           // 对that造成伤害
  bool close_to_death();          // 进入濒死状态
  void slay(Pig &that);           // 杀死that
  void slain();                   // 被杀死

  bool use_admission(char ch);  // 是否可能在出牌阶段使用该卡牌
  int try_kill();               // 寻找杀对象
  void kill(Pig &that);         // 杀
  bool kill_respond();          // 响应杀
  int try_fight();              // 寻找决斗对象
  void fight(Pig &that);        // 决斗
  void invasion();              // 南蛮入侵
  bool invasion_respond();      // 响应南蛮入侵
  void arrows();                // 万箭齐发
  bool arrows_respond();        // 响应万箭齐发
  void crossbow();              // 装备诸葛连弩
  bool first_watertight_ask(Pig &that);  // 使用无懈可击的第一阶段
  bool against_watertight_ask();         // 无懈可击的对抗阶段

  // 变量
  int num;                 // 在数组中的编号
  std::vector<card> hand;  // 手牌
  char identity;           // 身份
  int health;              // 剩余生命值

  bool equipped;     // 是否装备着诸葛连弩
  bool dead;         // 是否死亡
  bool kill_used;    // 本回合是否已经使用过杀
  bool jumped;       // 是否已经跳身份
  bool rebel_liked;  // 是否处于类反状态
};

class Input {
 public:
  void main_input();  // 主输入

  void in_n_and_m();       // 输入n和m
  void in_id_and_cards();  // 输入身份和起始手牌
  void in_card_heap();     // 输入牌堆
};

int n, m;               // n表示总猪数，m表示牌堆的牌数量
int main_pig;           // 主猪编号
int anti_num = 0;       // 当前剩余反猪数量
int heap_top = 1;       // 牌堆顶
bool gameover;          // 是否可以结束游戏
char win;               // 胜利方
char card_heap[20000];  // 牌堆
Input In;               // Input对象
Pig pig[20];            // 记录各猪

const bool debug = false;  // 调试入口，改为真即输出调试信息

void num_set();     // 从数组编号向各猪num属性映射
void heap_copy();   // 复制牌堆最后一张牌
void print();       // 输出结果
void initialize();  // 猪的初始化

int main()  // entrance
{
  In.main_input();  // 输入
  initialize();
  num_set();
  heap_copy();
  pig[main_pig].jump();  // 主猪一开始是跳的
  if (anti_num == 0)     // 特判：场上没有反猪，主猪方直接胜利
  {
    win = 'M';
    print();
    return 0;
  }
  register int i = 0;  // 轮到的猪
  while (1)            // 主循环
  {
    i = i % n + 1;
    if (pig[i].dead) continue;  // 跳过死亡的猪
    if (debug) printf("%d's turn started\n\n", i);
    pig[i].turn_start();  // 回合开始
    if (gameover)         // 检测游戏是否结束
    {
      print();
      break;  // 输出结果，程序结束
    }
  }
  return 0;
}

void num_set() {
  for (register int i = 1; i <= n; ++i) pig[i].num = i;
}

void heap_copy() {
  register char ch = card_heap[m];
  for (register int i = m + 1; i <= 5000; i++) {
    card_heap[i] = ch;  // 复制最后一张牌
  }
}

void print() {
  if (win == 'M') {
    printf("MP\n");
  } else {
    printf("FP\n");
  }
  for (int i = 1; i <= n; i++) {
    if (pig[i].dead) {
      printf("DEAD\n");
    } else {
      Pig s = pig[i];
      for (itr i = s.hand.begin(); i < s.hand.end(); i++) {
        if (i->avai) printf("%c ", i->card);
      }
      printf("\n");
    }
  }
}

void initialize() {
  for (int i = 1; i <= n; i++)  // 信息初始化
  {
    pig[i].health = 4;
    pig[i].equipped = false;
    pig[i].dead = false;
    pig[i].kill_used = false;
    pig[i].jumped = false;
    pig[i].rebel_liked = false;
  }
}

void Input::main_input() {
  in_n_and_m();
  in_id_and_cards();
  in_card_heap();
}

void Input::in_n_and_m()  //
{
  scanf("%d %d", &n, &m);
}

void Input::in_id_and_cards()  //
{
  char s[10];
  char ch;
  for (int i = 1; i <= n; i++) {
    scanf("%s", s);
    if (s[0] == 'M') {
      main_pig = i;  // 记录主猪编号
    } else if (s[0] == 'F') {
      anti_num++;  // 记录反贼数量
    }
    pig[i].identity_set(s[0]);        // 身份初始化
    while ((ch = getchar()) != '\n')  // 寻找下一张手牌
    {
      if (ch >= 'A' && ch <= 'Z') {
        pig[i].hand.push_back(card{true, ch});  // 加入手牌
      }
    }
  }
}

void Input::in_card_heap() {
  char ch;
  for (register int i = 1; i <= m; ++i) {
    while ((ch = getchar()) < 'A' || ch > 'Z') continue;
    card_heap[i] = ch;
  }
}

void Pig::identity_set(char id) { identity = id; }

void Pig::turn_start() {
  draw();
  draw();  // 抽两张牌
  if (debug) {
    for (int i = 1; i <= n; i++) {
      if (pig[i].dead) continue;
      printf("%d %c %d:", pig[i].num, pig[i].identity, pig[i].health);
      Pig s = pig[i];
      for (itr i = s.hand.begin(); i < s.hand.end(); i++)
        if (i->avai) printf("%c ", i->card);
      printf("\n");
    }
  }
  act();              // 出牌阶段开始
  kill_used = false;  // 重置出杀检测
  if (debug) cout << endl;
}

void Pig::draw() {
  hand.push_back(card{true, card_heap[heap_top++]});  // 加入一张手牌，牌堆顶后移
}

void Pig::act() {
  bool flag = true;
  while (flag)  // 扫了一遍手牌，如果没有出牌，则结束出牌阶段
  {
    flag = false;
    for (itr i = hand.begin(); i != hand.end(); i++) {
      if (i->avai && use_admission(i->card)) {
        use_card(i, i->card);
        if (dead || gameover) return;
        // 注意：这只猪有可能在决斗中自杀身亡，这时不能让它继续出牌
        // 如果游戏结束，那么立即返回
        i = hand.begin() - 1;
        // 使用一张牌后，前面的牌可能变得可用，此时需要回到第一张手牌重新扫描手牌
        // 之所以要-1，是因为在for循环末尾i++
        flag = true;  // 使用了牌
      }
    }
  }
}

bool Pig::find_and_use(char ch) {
  for_i_in_hand {
    if (i->card == ch && i->avai)  // 如果是想要的牌而且没出过
    {
      i->avai = false;  // 懒惰删除，标记牌已使用过
      if (debug) cout << num << " used a " << ch << endl;
      return true;  // 使用了牌，返回真
    }
  }
  return false;  // 找不到牌，返回假
}

void Pig::use_card(itr i, char ch) {
  int tmp;
  switch (ch) {
    case 'K':                // 杀
      if (tmp = try_kill())  // 用tmp记下杀的对象，决斗同
      {
        i->avai = false;
        if (debug) printf("%d used a kill to %d\n", num, tmp);
        kill(pig[tmp]);
      }
      break;
    case 'P':  // 桃
      i->avai = false;
      if (debug) printf("%d used a peach\n", num);
      inc_health();
      break;
    case 'F':
      if (tmp = try_fight()) {
        i->avai = false;
        if (debug) printf("%d used a fight to %d\n", num, tmp);
        fight(pig[tmp]);
      }
      break;
    case 'N':
      i->avai = false;
      if (debug) printf("%d used a invasion\n", num);
      invasion();
      break;
    case 'W':
      i->avai = false;
      if (debug) printf("%d used a arrows\n", num);
      arrows();
      break;
    case 'Z':
      i->avai = false;
      if (debug) printf("%d used a crossbow\n", num);
      crossbow();
  }
}

inline int Pig::dec_health() { return --health; }

inline int Pig::inc_health() { return ++health; }

inline void Pig::jump() { jumped = true; }

inline void Pig::go_rebel_like() { rebel_liked = true; }

inline void Pig::ungo_rebel_like() { rebel_liked = false; }

inline void Pig::unequip() { equipped = false; }

inline void Pig::hurt(Pig &that) {
  that.dec_health();  // 生命值减少
  if (debug) printf("%d hurts %d,left health %d\n", num, that.num, that.health);
  if (that.health == 0 && that.close_to_death())  // 濒死检查
  {
    if (debug) cout << that.num << " died" << endl;
    this->slay(that);  // 击杀处理
  }
}

bool Pig::close_to_death() {
  // 找桃
  for (itr i = hand.begin(); i < hand.end(); i++) {
    if (i->card == 'P' && i->avai) {
      i->avai = false;
      inc_health();
      return false;
    }
  }
  return true;
}

void Pig::slay(Pig &that) {
  that.slain();
  if (that.identity == 'M')  // 主公死亡，反贼胜利
  {
    win = 'F';
    gameover = true;
  } else if (that.identity == 'F')  // 反贼死亡
  {
    anti_num--;
    if (anti_num == 0)  // 反贼全灭，主公胜利
    {
      win = 'M';
      gameover = true;
      return;  // 胜利后不进行奖励抽牌
    }
    draw(), draw(), draw();
  } else if (identity == 'M' && that.identity == 'Z')  // 主公杀忠臣
  {
    for (itr i = hand.begin(); i < hand.end(); i++) {
      i->avai = false;
    }
    unequip();
  }
}

inline void Pig::slain()  //
{
  dead = true;
}

bool Pig::use_admission(char ch)  //
{
  if (ch == 'P' && health < 4)
    return true;  // 生命值不满时才允许使用桃
  else if ((ch == 'K' && try_kill()) || (ch == 'F' && try_fight()) ||
           ch == 'N' || ch == 'W' || ch == 'Z')
    return true;  // 使用杀和决斗必须有对象
  return false;
}

int Pig::try_kill() {
  // 返回值为0，表示无猪可杀。返回值不为0，即为被指定为杀的对象的猪的编号
  if (kill_used && !equipped) return 0;  // 本回合不得再出杀
  if (identity == 'M')                   // 主猪杀猪
  {
    for (int i = num % n + 1; i != num; i = i % n + 1) {
      if (pig[i].dead) continue;  // 跳过死亡猪，寻找逆时针第一只猪，下同
      if (pig[i].rebel_liked ||
          (pig[i].identity == 'F' &&
           pig[i].jumped))  // 检测下一只猪是否为类反猪或反猪
      {
        return i;
      } else  // 不是，不杀
      {
        return 0;
      }
    }
  } else if (identity == 'Z')  // 忠猪杀猪
  {
    for (int i = num % n + 1; i != num; i = i % n + 1) {
      if (pig[i].dead) continue;
      if (pig[i].identity == 'F' && pig[i].jumped)  // 需求反猪
      {
        return i;
      } else {
        return 0;
      }
    }
  } else  // 反猪杀猪
  {
    int i;
    for (i = num % n + 1; i != num; i = i % n + 1) {
      if (pig[i].dead) continue;
      if (pig[i].identity != 'F' && pig[i].jumped)  // 需求反猪
      {
        return i;
      } else {
        return 0;
      }
    }
  }
}

inline void Pig::kill(Pig &that) {
  jump();                    // 杀必然跳身份
  ungo_rebel_like();         // 杀必然脱离类反状态
  kill_used = true;          // 本回合使用了杀
  if (!that.kill_respond())  // 响应为假，说明无闪可出
  {
    hurt(that);
  }
}

inline bool Pig::kill_respond() {
  return find_and_use('D');  // 在手牌中寻找闪来抵消杀
}

int Pig::try_fight() {
  if (identity == 'M') {
    for (int i = num % n + 1; i != num; i = i % n + 1) {
      if (pig[i].dead) continue;
      if (pig[i].rebel_liked || (pig[i].identity == 'F' && pig[i].jumped)) {
        return i;
      }
    }
  } else if (identity == 'Z') {
    for (int i = num % n + 1; i != num; i = i % n + 1) {
      if (pig[i].dead) continue;
      if (pig[i].identity == 'F' && pig[i].jumped) {
        return i;
      }
    }
  } else  // 反猪必然对主猪决斗
  {
    return main_pig;
  }
  return 0;
}

void Pig::fight(Pig &that) {
  jump();
  ungo_rebel_like();
  if (first_watertight_ask(that)) return;  // 为对方询问无懈可击
  if (identity == 'M' && that.identity == 'Z')  // 主猪决斗忠猪，忠猪必然放弃
  {
    hurt(that);
    return;
  }
  int hurted;  // 记录被杀者
  while (1)    // 直到一方无杀才跳出循环
  {
    if (!that.find_and_use('K')) {
      hurted = 2;
      break;
    }
    if (!find_and_use('K')) {
      hurted = 1;
      break;
    }
  }
  if (hurted == 1) {
    that.hurt(*this);
  } else {
    hurt(that);
  }
}

void Pig::invasion() {
  for (int i = num % n + 1; i != num; i = i % n + 1) {
    if (pig[i].dead) continue;
    if (debug) cout << "invasion->" << i << endl;
    if (first_watertight_ask(pig[i])) continue;
    if (!pig[i].invasion_respond()) {
      hurt(pig[i]);
      if (gameover) return;
      if (pig[i].identity == 'M' && !jumped)  // 类反猪判定
      {
        go_rebel_like();
      }
    }
  }
}

inline bool Pig::invasion_respond() { return find_and_use('K'); }

void Pig::arrows() {
  for (int i = num % n + 1; i != num; i = i % n + 1) {
    if (pig[i].dead) continue;
    if (debug) cout << "arrows->" << i << endl;
    if (first_watertight_ask(pig[i])) continue;
    if (!pig[i].arrows_respond()) {
      hurt(pig[i]);
      if (gameover) return;
      if (pig[i].identity == 'M' && !jumped) {
        go_rebel_like();
      }
    }
  }
}

inline bool Pig::arrows_respond() { return find_and_use('D'); }

inline void Pig::crossbow() { equipped = true; }

bool Pig::first_watertight_ask(Pig &that) {
  if (!that.jumped)
    return false;  // 无猪（注意：包括它自己）为未跳者进行无懈可击
  bool flag = true;
  for (int i = num; i != num || flag; i = i % n + 1) {
    flag = false;
    if (pig[i].dead) continue;
    if (that.identity == 'M' && pig[i].identity == 'F') continue;
    if (that.identity == 'Z' && pig[i].identity == 'F') continue;
    if (that.identity == 'F' && pig[i].identity == 'Z') continue;
    if (that.identity == 'F' && pig[i].identity == 'M') continue;  // 寻找同势力
    if (pig[i].find_and_use('J')) {
      pig[i].jump();
      return !pig[i].against_watertight_ask();  // 对抗开始
    }
  }
  return false;
}

bool Pig::against_watertight_ask() {
  for (int i = num % n + 1; i != num; i = i % n + 1) {
    if (pig[i].dead) continue;
    if (identity == 'M' && pig[i].identity == 'Z') continue;
    if (identity == 'Z' && pig[i].identity == 'Z') continue;
    if (identity == 'F' && pig[i].identity == 'F') continue;
    if (identity == 'Z' && pig[i].identity == 'M') continue;  // 寻找异势力
    if (pig[i].find_and_use('J')) {
      pig[i].jump();
      return !pig[i].against_watertight_ask();
    }
  }
  return false;
}