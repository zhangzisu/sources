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
					printf("GO pos = %d, rest = %d\n", pos, rest);

					int AA, BB;
					int nearst = std::min(AA = *A.lower_bound(pos), BB = *B.lower_bound(pos));

					if (rest - nearst + pos < 0) {
						A.insert(pos + rest);
						B.insert(pos + rest);
						break;
					}

					if (AA == nearst) {
						int cur = nearst;
						B.insert(nearst);
						while (A.find(cur) != A.end()) A.erase(cur++);
						if (B.find(cur) != B.end()) {
							rest -= nearst - pos;
							pos = cur;
							B.erase(cur);
							continue;
						}
						A.insert(cur);
						break;
					} else {
						int cur = nearst;
						A.insert(nearst);
						while (B.find(cur) != B.end()) B.erase(cur++);
						if (A.find(cur) != A.end()) {
							rest -= nearst - pos;
							pos = cur;
							A.erase(cur);
							continue;
						}
						B.insert(cur);
						break;
					}
				}
			}
		}
	}
	A.insert(0);
	B.insert(0);

	auto it = --A.end();
	for (int j = *--it; j; j--) {
		if (j == *it) {
			it--;
			printf("1");
		} else {
			printf("0");
		}
	}
	printf("\n");
	it = --B.end();
	for (int j = *--it; j; j--) {
		if (j == *it) {
			it--;
			printf("1");
		} else {
			printf("0");
		}
	}
	printf("\n");

	return 0;
}
