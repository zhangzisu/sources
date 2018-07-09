#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#define MAXN 1000010
const int INF = ~(0U) >> 2;

int n, m, k, a[MAXN], b[MAXN];
char buf[MAXN];
std::set<int> A, B;

int main(int argc, char const *argv[]) {
	scanf("%d%d%d", &n, &m, &k);
	scanf("%s", buf + 1);
	std::reverse(buf + 1, buf + n + 1);
	for (int i = 1; i <= n; i++) a[i] = buf[i] == '1';
	scanf("%s", buf + 1);
	std::reverse(buf + 1, buf + m + 1);
	for (int i = 1; i <= m; i++) b[i] = buf[i] == '1';
	n = std::max(n, m);
	A.insert(INF);
	B.insert(INF);
	for (int i = n; i; i--) {
		if (a[i] || b[i]) {
			if (!a[i]) {
				B.insert(i);
			} else if (!b[i]) {
				A.insert(i);
			} else {
				int rest = k;
				int pos = i;
				while (rest) {
					int AA, BB;
					int nearst = std::min(AA = *A.lower_bound(pos), B = *B.lower_bound(pos));

					if (rest - nearst + pos < 0) {
						A.insert(pos + rest);
						B.insert(pos + rest);
						break;
					}

					if (AA == nearst) {
						int cur = nearst;
						B.insert(nearst);
						while (AA == cur) A.erase(A.begin()), cur++;
						if (B.find(cur) != B.end()) {
							rest -= cur - pos;
							pos = cur;
							B.erase(cur);
							continue;
						}
						break;
					} else {
						int cur = nearst;
						A.insert(nearst);
						while (*B.begin() == cur) B.erase(B.begin()), cur++;
						if (AA == cur) {
							rest -= cur - pos;
							pos = cur;
							A.erase(cur);
							continue;
						}
						break;
					}
				}
			}
		}
	}
	for (int i = 1; A.size() > 1 && B.size() > 1; i++) {
		if (*A.begin() != i && *B.begin() != i) putchar('0');
		if (*A.begin() == i) A.erase(A.begin()), putchar('1');
		if (*B.begin() == i) B.erase(B.begin()), putchar('1');
	}
	return 0;
}
