#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
int n, m, val[1 << 20], f[1 << 20], g[1 << 20], bin[20], log[20];
char buf[1 << 20];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < 1 << n; i++) scanf("%1d", val[i]);
	bin[0] = 1;
	for (int i = 1; i < 20; i++) bin[i] = bin[i - 1] << 1;
	log[0] = -1;
	for (int i = 1; i < 1 << n; i++) log[i] = log[i >> 1] + 1;
	for (int i = 0; i < (1 << n); i++) f[i] = val[i], g[i] = val[((1 << n) - 1) ^ i];
	for (int d = 0; d < n; d++)
		for (int i = 0; i < 1 << n; i++)
			if (!((i >> d) & 1))
				f[i] += f[i | (1 << d)], g[i] += g[i | (1 << d)];
	while (m--) {
		int s0 = 0, s1 = 0, s = 0;
		scanf("%s", buf);
		for (int i = 0; i < n; i++) {
			if (buf[i] == '1')
				s1 |= 1 << (n - i - 1);
			else if (buf[i] == '0')
				s0 |= 1 << (n - i - 1);
			else
				s |= 1 << (n - i - 1);
		}
		if()
	}
	return 0;
}