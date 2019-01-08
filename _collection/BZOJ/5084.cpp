#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 200010
struct sam_t {
	int son[26], len, link;
	inline int &operator[](int index) {
		return son[index];
	}
} sam[MAXN];
int ans = 0;
struct history_t {
	int *x, v;
} history[8000010];
int timestamp = 0;
inline void modifyVal(int &x, int y) {
	history[++timestamp] = (history_t){&x, x};
	x = y;
}
inline void revert(int snapshot) {
	for (; timestamp > snapshot; timestamp--)
		(*history[timestamp].x) = history[timestamp].v;
}
int cnt = 1, last = 1;
inline int extent(int c) {
	modifyVal(cnt, cnt + 1);
	register int q = cnt, p = last;
	modifyVal(sam[q].len, sam[p].len + 1);
	modifyVal(last, q);
	for (; p && !sam[p][c]; p = sam[p].link) modifyVal(sam[p][c], q);
	if (!p) {
		modifyVal(sam[q].link, 1);
	} else {
		register int np = sam[p][c];
		if (sam[np].len == sam[p].len + 1) {
			modifyVal(sam[q].link, np);
		} else {
			modifyVal(cnt, cnt + 1);
			register int nq = cnt;
			modifyVal(sam[nq].link, sam[np].link);
			modifyVal(sam[nq].len, sam[p].len + 1);
			for (register int i = 0; i < 26; i++) modifyVal(sam[nq][i], sam[np][i]);
			modifyVal(sam[q].link, nq);
			modifyVal(sam[np].link, nq);
			for (; p && sam[p][c] == np; p = sam[p].link) modifyVal(sam[p][c], nq);
		}
	}
	modifyVal(ans, ans + sam[q].len - sam[sam[q].link].len);
	return timestamp;
}
char buf[MAXN];
int stack[MAXN];
int main() {
	scanf("%s", buf);
	for (register int i = 0, top = 0; buf[i]; i++) {
		if (isalpha(buf[i])) {
			stack[++top] = extent(buf[i] - 'a');
		} else {
			revert(stack[--top]);
		}
		printf("%d\n", ans);
	}
}