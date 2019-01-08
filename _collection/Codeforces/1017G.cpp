#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#define MAXN 100010
#define SQRT 320
struct three_t {
	int x, y, z;
	inline three_t(int x = 0, int y = 0, int z = 0) : x(x), y(y), z(z) {}
};
std::vector<int> next[MAXN];
std::vector<three_t> to[MAXN];
int n, q, t[MAXN], v[MAXN], spc[MAXN], clr[MAXN], tag[MAXN], col[MAXN], tmp[MAXN];
void build(int x, int p, int count, int delta) {
	if (spc[x]) {
		if (p) to[p].emplace_back(x, count, delta);
		count = delta = 0;
		p = x;
	} else {
		count += !col[x];
		delta += 1;
	}
	for (auto &y : next[x]) build(y, p, count, delta);
}
void setBlack(int x) {
	if (!col[x]) return void(col[x] = 1);
	tag[x]++;
	for (auto &y : to[x]) {
		if (y.y < tag[x]) {
			setBlack(y.x);
		}
	}
}
void setWhite(int x) {
	clr[x] = 1;
	col[x] = 0;
	tag[x] = 0;
	for (auto &y : to[x]) {
		y.y = y.z;
		setWhite(y.x);
	}
}
void restore(int x, int setWhite, int setBlack) {
	if (spc[x]) {
		setWhite |= clr[x];
		setBlack = tag[x];
	} else {
		col[x] = tmp[x] && !setWhite;
		if (setBlack && !col[x]) col[x] = 1, --setBlack;
	}
	for (auto &y : next[x]) restore(y, setWhite, setBlack);
}
int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);
	std::cin >> n >> q;
	for (int i = 2, x; i <= n; i++) std::cin >> x, next[x].push_back(i);
	for (int i = 1; i <= q; i++) std::cin >> t[i] >> v[i];
	for (int i = 1; i <= q; i += SQRT) {
		memset(spc, 0, sizeof(spc));
		memset(clr, 0, sizeof(clr));
		memset(tag, 0, sizeof(tag));
		memcpy(tmp, col, sizeof(tmp));
		for (int i = 1; i <= n; i++) to[i].clear();
		for (int j = 0; j < SQRT && i + j <= q; j++) spc[v[i + j]] = 1;
		build(1, 0, 0, 0);
		for (int j = 0; j < SQRT && i + j <= q; j++) {
			if (t[i + j] == 1) {
				setBlack(v[i + j]);
			} else if (t[i + j] == 2) {
				setWhite(v[i + j]);
			} else {
				std::cout << (col[v[i + j]] ? "black" : "white") << std::endl;
			}
		}
		restore(1, 0, 0);
	}
	return 0;
}