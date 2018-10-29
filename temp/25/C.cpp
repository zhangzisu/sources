#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MOD 1000000000
int len;
char buf[1000010];
inline bool isWhiteChar(char c) { return c == ' ' || c == '\t' || c == '\n'; }
struct interger {
	int val, flag;
	inline interger(int val = 0, int flag = 0) : val(val), flag(flag) {}
	inline interger &operator=(int x) {
		val = x;
		flag = 0;
		return *this;
	}
	inline interger &operator+=(interger other) {
		flag |= other.flag;
		if (val + other.val > 1000000000) flag = 1;
		val = (val + other.val) % MOD;
		return *this;
	}
	inline int friend operator<=(interger a, interger b) {
		return a.val <= b.val;
	}
} val[26];
inline interger getVal(char c) { return isalpha(c) ? val[c - 'A'] : interger(c - '0', 0); }
inline void eval(const char *s, int len) {
	if (!len) return;
	while (isWhiteChar(*s)) s++, len--;
	while (isWhiteChar(*(s + len - 1))) len--;
	if (s[1] == '=') {
		interger &left_expr = val[s[0] - 'A'];
		interger right_expr = getVal(s[2]);
		left_expr = right_expr;
	} else if (s[1] == '+') {
		assert(s[2] == '=');
		interger &left_expr = val[s[0] - 'A'];
		interger right_expr = getVal(s[3]);
		left_expr += right_expr;
	} else {
		assert(s[0] == 'f' && s[1] == 'o' && s[2] == 'r');
		interger &loop_var = val[s[4] - 'A'];
		interger start = getVal(s[6]);
		interger end = getVal(s[8]);
		for (loop_var = start; loop_var <= end; loop_var += 1) {
			eval(s + 10, len - 10);
		}
		loop_var += -1;
	}
}
int main() {
	while (true) {
		int x = getchar();
		if (x == -1) break;
		if (x == '\n') {
			eval(buf, len);
			len = 0;
		} else {
			buf[len++] = x;
		}
	}
    eval(buf, len);
	for (int i = 0; i < 26; i++) {
		if (val[i].flag || val[i].val) {
			if (val[i].flag) {
				printf("%c=...%09d\n", i + 'A', val[i].val);
			} else {
				printf("%c=%d\n", i + 'A', val[i].val);
			}
		}vue
	}
	return 0;
}