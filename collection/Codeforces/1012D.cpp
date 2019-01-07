#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <vector>
char buf[200010];
std::deque<std::pair<bool, int>> A, B;
std::vector<std::pair<int, int>> op;
int main() {
	scanf("%s", buf);
	for (int i = 0, len = 0; buf[i]; i++) {
		len++;
		if (buf[i] != buf[i + 1]) {
			A.emplace_back(buf[i] != 'a', len);
			len = 0;
		}
	}
	scanf("%s", buf);
	for (int i = 0, len = 0; buf[i]; i++) {
		len++;
		if (buf[i] != buf[i + 1]) {
			B.emplace_back(buf[i] != 'a', len);
			len = 0;
		}
	}
	while (A.size() != 1 || B.size() != 1) {
		auto a = A.front();
		auto b = B.front();
		A.pop_front();
		B.pop_front();
		if (a.first ^ b.first) {
			if (A.empty()) {
				A.push_back(b);
				B.front().second += a.second;
			} else if (B.empty()) {
				A.front().second += b.second;
				B.push_back(a);
			} else {
				A.front().second += b.second;
				B.front().second += a.second;
			}
			op.emplace_back(a.second, b.second);
		} else {
			if (A.size() > B.size()) {
				B.push_front(b);
				B.front().second += a.second;
                op.emplace_back(a.second, 0);
			} else {
				A.push_front(a);
				A.front().second += b.second;
                op.emplace_back(0, b.second);
			}
		}
	}
	printf("%d\n", (int)op.size());
	for (auto x : op) printf("%d %d\n", x.first, x.second);
	return 0;
}