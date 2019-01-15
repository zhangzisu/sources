#include "mine.h"
#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 16
#define MAXM 30
#define MAXS 10000
static const int dx[] = {1, 1, 0, -1, -1, -1, 0, 1};
static const int dy[] = {0, 1, 1, 1, 0, -1, -1, -1};
int son[MAXN * MAXM * MAXS][10], cnt = 1;
inline void generate(int x, int q, int n, int m) {
	static int board[MAXN][MAXM];
	memset(board, 0, sizeof(board));
	int tot = 0;
	while (tot < q) {
		x = 48271ll * x % 2147483647;
		int y = x % (n * m);
		int r = y / m, c = y % m;
		if (!board[r][c]) {
			board[r][c] = 9;
			++tot;
		}
	}
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			if (!board[i][j]) {
				for (int k = 0; k < 8; ++k) {
					int x = i + dx[k], y = j + dy[k];
					if (x >= 0 && x < n && y >= 0 && y < m && board[x][y] == 9) ++board[i][j];
				}
			}
	int p = 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int &x = son[p][board[i][j]];
			if (!x) x = ++cnt;
			p = x;
		}
	}
}
void sweep(int n, int m, int q) {
	for (int s = 100; s <= 10000; s++) generate(s, q, n, m);
	int p = 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int valid = 0;
			for (int k = 0; k < 10; k++) valid += !!son[p][k];
			assert(valid);
			if (valid == 1) {
				for (int k = 0; k < 10; k++) {
					if (son[p][k]) {
						if (k != 9) open(i, j);
						p = son[p][k];
						break;
					}
				}
			} else {
				int result = open(i, j);
				if (result == -1) result = 9;
				p = son[p][result];
			}
		}
	}
}
