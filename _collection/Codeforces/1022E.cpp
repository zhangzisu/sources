#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <string>
char buf[50];
inline int interaction(int x0, int y0, int x1, int y1) {
	printf("? %d %d %d %d\n", x0, y0, x1, y1);
	fflush(stdout);
	scanf("%s", buf);
	return buf[0] == 'Y';
}
int n;
inline int judgeL(int x, int y) {
	if (n - x + n - y < n - 1) return -1;
	return interaction(x, y, n, n);
}
inline int judgeR(int x, int y) {
	if (x - 1 + y - 1 < n - 1) return -1;
	return interaction(1, 1, x, y);
}
std::map<std::pair<int, int>, std::string> M;
int main() {
	scanf("%d", &n);
	std::string tmp = "";
	std::pair<int, int> now(1, 1);
	M[now] = tmp;
	while (now != std::make_pair(n, n)) {
		int result = judgeL(now.first + 1, now.second);
		if (~result) {
			if (result)
				tmp.push_back('D'), now.first++;
			else
				tmp.push_back('R'), now.second++;
			M[now] = tmp;
		} else {
			break;
		}
	}
	tmp = "";
	now = std::make_pair(n, n);
	do {
		if (M.count(now)) {
			std::reverse(tmp.begin(), tmp.end());
			printf("! %s%s\n", M[now].c_str(), tmp.c_str());
			return 0;
		}
		int result = judgeR(now.first, now.second - 1);
		if (result)
			tmp.push_back('R'), now.second--;
		else
			tmp.push_back('D'), now.first--;
	} while (now != std::make_pair(1, 1));
	return 0;
}