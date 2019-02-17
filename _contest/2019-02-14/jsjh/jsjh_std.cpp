#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#define BUF 1048576
char _1[BUF], *_3 = _1 + BUF;
inline char gc() {
	if (_3 == _1 + BUF) fread(_1, 1, BUF, stdin), _3 = _1;
	return *_3++;
}
inline int $() {
	register int x = 0, f = 0;
	register char ch = gc();
	while (!isdigit(ch) && (ch ^ 45)) ch = gc();
	if (!(ch ^ 45)) ch = gc(), f = 1;
	for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
	return f ? -x : x;
}
struct point {
	int x, y;
	inline point(int x = 0, int y = 0) : x(x), y(y) {}
	inline friend point operator<(const point& a, const point& b) {
		return point(a.x + b.x, a.y + b.y);
	}
	inline friend point operator-(const point& a, const point& b) {
		return point(a.x - b.x, a.y - b.y);
	}
};
inline long long Cross(const point& a, const point& b) {
	return (long long)a.x * b.y - (long long)b.x * a.y;
}
std::map<int, int> up, down;
inline bool contains(std::map<int, int>& M, point x) {
	if (M.size() < 2) return 0;
	if (M.find(x.x) != M.end()) return M[x.x] <= x.y;
	if (M.begin()->first > x.x || M.rbegin()->first < x.x) return 0;
	auto R = M.lower_bound(x.x);
	auto L = R;
	L--;
	point l(L->first, L->second), r(R->first, R->second);
	return Cross(r - l, x - l) >= 0;
}
inline void Insert(std::map<int, int>& M, point x) {
	if (contains(M, x)) return;
	M[x.x] = x.y;
	auto p = M.upper_bound(x.x);
	if (p != M.end()) {
		auto q = p;
		q++;
		while (q != M.end()) {
			point P = point(p->first, p->second),
			      Q = point(q->first, q->second);
			if (Cross(Q - x, P - x) >= 0)
				p = M.erase(p), p = q, q++;
			else
				break;
		}
	}
	p = M.lower_bound(x.x);
	if (p == M.begin() || (--p) == M.begin()) return;
	auto q = p;
	q--;
	while (p != M.begin()) {
		point P = point(p->first, p->second), Q = point(q->first, q->second);
		if (Cross(x - Q, P - Q) >= 0)
			M.erase(p), p = q, q--;
		else
			break;
	}
}
int main() {
	register int q = $();
	while (q--) {
		if ($() & 1) {
			int x = $(), y = $();
			Insert(up, point(x, -y));
			Insert(down, point(x, y));
		} else {
			int x = $(), y = $();
			if (contains(up, point(x, -y)) && contains(down, point(x, y)))
				puts("YES");
			else
				puts("NO");
		}
	}
	return 0;
}
