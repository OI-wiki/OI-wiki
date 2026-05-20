
constexpr int SEED = 5489;

// --8<-- [start:core]

#include <iostream>
#include <vector>
#include <random>

using namespace std;

struct myrand {
  vector<unsigned int> vec;
  int l, j, k, cur;

  template<class URBG>
  myrand(int l, int j, int k, URBG &&rng) {
    this->l = l;
    this->j = j;
    this->k = k;
    cur = 0;
    for (int i = 0; i < l; i++) {
      vec.push_back(rng());  // 先用其他方法生成随机序列中的前几个元素
    }
  }

  unsigned int next() {
    vec[cur] = vec[(cur - j + l) % l] * vec[(cur - k + l) % l];
    // 这里用 unsigned 类型是为了实现自动对 2^32 取模
    return vec[cur++];
  }
};

myrand rnd(11, 4, 7, mt19937(SEED)); // 最后一个可以换成其它随机数生成器，自行设置种子

int main() {
  unsigned int x = rnd.next();
  cout << x << endl;
  return 0;
}

// --8<-- [end:core]
