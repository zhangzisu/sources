#include <bits/stdc++.h>
using namespace std;
#define mp make_pair
int n, m;
map<pair<int, int>, int> Mp;
int main() {
	srand(time(NULL));
	freopen("E.in", "w", stdout);
	int n = 100;
	int m = 3000;
	printf("%d %d\n", n, m);
	for (int i = 1; i <= m; i++) {
		int u = rand() % n + 1, v = rand() % n + 1;
		while (u == v || Mp.count(mp(u, v))) u = rand() % n + 1, v = rand() % n + 1;
		Mp[mp(u, v)] = 1;
		Mp[mp(v, u)] = 1;
		printf("%d %d\n", u, v);
	}
	return 0;
}
