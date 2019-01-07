#include <cstdio>
#include <vector>
typedef long long lnt;

class SetAndSet {
	const static int MAX = 20;
	int p[100];
	inline int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }

       public:
	lnt countandset(std::vector<int> a) {
		std::vector<int> digits;
		std::vector<int> pos[MAX];
		for (int i = 0; i < MAX; i++) {
			for (int j = 1; j < (int)a.size(); j++) {
				if (((a[j] ^ a[0]) >> i) & 1) {
					digits.push_back(i);
					break;
				}
			}
		}
		for (int i = 0; i < (int)digits.size(); i++) {
			for (int j = 0; j < (int)a.size(); j++) {
				if ((~a[j] >> digits[i]) & 1) {
					pos[i].push_back(j);
				}
			}
		}
		lnt result = 0;
		for (int i = 0; i < (1 << (int)digits.size()); i++) {
			for (int j = 0; j < (int)a.size(); j++) p[j] = j;
			for (int j = 0; j < (int)digits.size(); j++) {
				if ((i >> j) & 1) {
					for (int k = 1; k < (int)pos[j].size(); k++) {
						p[find(pos[j][k])] = find(pos[j][0]);
					}
				}
			}
			int count = 0;
			for (int j = 0; j < (int)a.size(); j++) count += find(j) == j;
			lnt tmp = (1LL << count) - 2;
			if (__builtin_popcount(i) & 1) {
				result -= tmp;
			} else {
				result += tmp;
			}
			// fprintf(stderr, "%d -> %lld\n", i, tmp);
		}
		return result;
	}
};