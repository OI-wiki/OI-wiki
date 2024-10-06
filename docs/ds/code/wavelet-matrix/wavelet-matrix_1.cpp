#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

struct Bits {
    vector<unsigned long long> b;
    vector<int> sum;
	int len;
    Bits(int n) {
		len = n >> 6;
        b.resize(len + 1, 0);
        sum.resize(len + 1, 0);
    }
    // 第 k 位（从 1 开始编号）设为 1
    void set(int k) {
        k--; // 内部从 0 开始存储
        b[k >> 6] |= (1ull << (k & 0x3f));
    }
    // 设定完毕后调用
    void prepare() {
        for (int i = 0; i < b.size(); i++) {
            if (i) sum[i] = sum[i - 1];
            sum[i] += __builtin_popcountll(b[i]);
        }
    }
    int count1(int k) {
        int res = 0;
        int hi = (k >> 6), lo = (k & 0x3f);
        if (hi) res += sum[hi - 1];
        // (1 << lo) - 1 取了小于 lo 的位，正好符合从 0 开始存储
        res += __builtin_popcountll(b[hi] & ((1ull << lo) - 1ull));
        return res;
    }
};

struct WaveletMatrix {
	vector<Bits> b;
	int n;
	// 实际上构造 Wavelet Matrix 之后，不难 O(log n) 求出原始的 a[i]
	// 注意 a 将被修改
	WaveletMatrix(int n, int *a) {
		this -> n = n;
		b.resize(32, Bits(n));
		for (int j = 31; j >= 0; j--) {
			for (int i = 1; i <= n; i++) if ((a[i] >> j) & 1) b[j].set(i);
			b[j].prepare();
			stable_partition(a + 1, a + n + 1, [&](int x) { return (x >> j) & 1; });
		}
	}
	int kth(int l, int r, int k) {
		int res = 0;
		for (int j = 31; j >= 0; j--) {
			int l1 = b[j].count1(l - 1), r1 = b[j].count1(r);
			if (r1 - l1 >= k) l = l1 + 1, r = r1, res |= (1 << j);
			else {
				int l0 = l - 1 - l1, r0 = r - r1;
				int total = b[j].count1(n);
				l = total + l0 + 1, r = total + r0;
				k -= (r1 - l1);
			}
		}
		return res;
	}
};

const int MAXN(2e5 + 5);

int a[MAXN];
int n, m;

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	WaveletMatrix w(n, a);
	while (m--) {
		int l, r, k; scanf("%d %d %d", &l, &r, &k);
		printf("%d\n", w.kth(l, r, r - l + 2 - k));
	}
	return 0;
}
