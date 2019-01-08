#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
struct state {
	int a, b, c;
	inline friend bool operator==(state a, state b) {
		return a.a == b.a && a.b == b.b && a.c == b.c;
	}
	inline friend bool operator!=(state a, state b) {
		return a.a != b.a || a.b != b.b || a.c != b.c;
	}
} A, B;
int deepA, deepB, tmp, ans = 0;
inline void sort(int &a, int &b, int &c) {
	if (a > b) std::swap(a, b);
	if (b > c) std::swap(b, c);
	if (a > b) std::swap(a, b);
}
inline state fa(state x, int maxStep, int &realStep) {
	for (int count = (realStep = 0); maxStep; maxStep -= count, realStep += count) {
		int dx = x.b - x.a;
		int dy = x.c - x.b;
		if (dx == dy) break;
		if (dx < dy) {
			count = std::min(maxStep, (dy - 1) / dx);
			x.b = x.c - (dy - count * dx);
			x.a = x.b - dx;
		} else {
			count = std::min(maxStep, (dx - 1) / dy);
			x.b = x.a + (dx - count * dy);
			x.c = x.b + dy;
		}
	}
	return x;
}
int main() {
	scanf("%d%d%d%d%d%d", &A.a, &A.b, &A.c, &B.a, &B.b, &B.c);
	sort(A.a, A.b, A.c);
	sort(B.a, B.b, B.c);
	if (fa(A, 0x3F3F3F3F, deepA) != fa(B, 0x3F3F3F3F, deepB)) return puts("NO"), 0;
	if (deepA < deepB) {
		std::swap(A, B);
		std::swap(deepA, deepB);
	}
	A = fa(A, deepA - deepB, ans);
	for (int i = 30; ~i; i--) {
		if (fa(A, 1 << i, tmp) != fa(B, 1 << i, tmp)) {
			A = fa(A, 1 << i, tmp);
			B = fa(B, 1 << i, tmp);
			ans += 2 << i;
		}
	}
	if (A != B) ans += 2;
	puts("YES");
	printf("%d\n", ans);
	return 0;
}