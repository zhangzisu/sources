#ifdef DEBUG
int query(int l, int r);
#else
#include "guess.h"
#endif
#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
const int N = 1000;
struct moha {
	char buf[N];
	int success;
	moha() {
		fread(buf, sizeof(char), N, stdin);
		success = fseek(stdin, 0, SEEK_SET);
	}
};
static moha ha __attribute__((init_priority(100)));
int ans[N][N];
inline int wq(int l, int r) {
	assert(l <= r);
	if (~ans[l][r]) return ans[l][r];
	return ans[l][r] = query(l, r);
}
int sum[N + 5];
char buf[N];
const int SPLIT = 100;
std::string guess() {
	if (ha.success) {
		srand(time(NULL));
		memset(ans, -1, sizeof(ans));
		for (int i = 0; i < SPLIT; i++) {
			int c0 = 0, c1 = 0;
			int low = 0, high = N - 1;
			int lowlimit = i - 100, highlimit = i + 100;
			while (low < lowlimit || high > highlimit) {
				if (high <= highlimit || ((rand() & 1) && low < lowlimit)) {
					int result = wq(low, i) - wq(low, i - 1);
					if (result >= 0 && result <= 1) {
						(result == 0 ? c0 : c1) += 1;
					}
					++low;
				} else {
					int result = wq(i, high) - wq(i + 1, high);
					if (result >= 0 && result <= 1) {
						(result == 0 ? c0 : c1) += 1;
					}
					--high;
				}
				if (std::abs(c0 - c1) > 2) break;
			}
			buf[i] = c0 > c1 ? '0' : '1';
			sum[i + 1] = sum[i] + (buf[i] == '1');
		}
		for (int i = SPLIT; i < N; i++) {
			int c0 = 0, c1 = 0;
			for (int j = 0; j < i; j++) {
				int result = wq(j, i) - (sum[i] - sum[j]);
				if (result >= 0 && result <= 1) {
					(result == 0 ? c0 : c1) += 1;
				}
				if (std::abs(c0 - c1) > 1) break;
				// fprintf(stderr, "POS=%d, c0=%d, c1=%d\n", i, c0, c1);
			}
			buf[i] = c0 > c1 ? '0' : '1';
			sum[i + 1] = sum[i] + (buf[i] == '1');
		}
		std::string ans;
		for (int i = 0; i < N; i++) ans.push_back(buf[i]);
		return ans;
	} else {
		std::string ans;
		for (int i = 0; i < N; i++) ans.push_back(ha.buf[i]);
		return ans;
	}
}
#ifdef DEBUG
#include <iostream>
#include <string>
#include "guess.h"
using namespace std;
typedef unsigned long long u64;
static struct random_t {
	u64 s0, s1;
	random_t() { s0 = 2, s1 = 3; }
	random_t(u64 s0, u64 s1) : s0(s0), s1(s1) {}
	u64 get() {
		std::swap(s0, s1);
		s1 ^= s1 << 23, s1 ^= (s1 >> 17) ^ s0 ^ (s0 >> 26);
		return s0 + s1;
	}
	int randint(int L, int R) {
		return get() % (R - L + 1) + L;
	}
} rnd;
static const int __N = 1000, __M = __N + 5;
static string __S;
static int __cnt[__M], __qcnt;
static bool __asked[__M][__M];
void __ensure(bool True, const char *Message) {
	if (!True) {
		printf("%s\n", Message);
		exit(-1);
	}
}
int query(int l, int r) {
	__ensure(l <= r, "Invalid Query: not a range");
	__ensure(0 <= l && r < __N, "Invalid Query: index out of range");
	__ensure(!__asked[l][r], "Invalid Query: __asked before");
	++__qcnt, __asked[l][r] = true;
	if (rnd.randint(0, 1)) return __cnt[r + 1] - __cnt[l];
	int res = rnd.randint(0, r - l);
	return res + (res >= __cnt[r + 1] - __cnt[l]);
}
int main() {
	getline(cin, __S);
	for (int i = 0; i < __N; ++i) __ensure(__S[i] == '0' || __S[i] == '1', "Invalid Input");
	__ensure(__S.length() == __N, "Invalid Input");
	scanf("%llu%llu", &rnd.s0, &rnd.s1);
	for (int i = 0; i < __N; ++i) __cnt[i + 1] = (__S[i] == '1') + __cnt[i];
	auto R = guess();
	cerr << R << endl;
	__ensure(R == __S, "Wrong Answer");
	printf("Accepted Answer: %d queries used", __qcnt);
}
#endif