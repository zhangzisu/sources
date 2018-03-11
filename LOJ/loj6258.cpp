#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define BUF 1048576
char _1[BUF], *_3 = _1 + BUF;
inline char gc() {
    if (_3 == _1 + BUF) fread(_1, 1, BUF, stdin), _3 = _1;
    return *_3++;
}
inline int $() {
    register int x = 0;
    register char ch = gc();
    while (!isdigit(ch)) ch = gc();
    for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return x;
}
#include <functional>
#include <list>
#include <queue>
#include <vector>
#define MAXN 100010
int n, s[MAXN];
std::priority_queue<std::pair<int, int>> Q;
std::list<int> V[MAXN];
int BIT[MAXN];
inline int lowbit(int x) { return x & -x; }
inline void add(int p, int v) {
    for (; p <= n; p += lowbit(p)) BIT[p] += v;
}
inline int qry(int p) {
    register int ret = 0;
    for (; p; p -= lowbit(p)) ret += BIT[p];
    return ret;
}
int main() {
    register int _ = $();
    while (_--) {
        memset(BIT, 0, sizeof(BIT));
        while (!Q.empty()) Q.pop();
        n = $();
        for (int i = 1; i <= n; i++) V[i].clear();
        for (int i = 1; i <= n; i++) s[i] = $();
        register int q = $();
        while (q--) {
            int t = $(), id, l, r;
            while (Q.size() && Q.top().first >= -t) {
                int x = Q.top().second;
                add(x, 1);
                V[x].pop_front();
                Q.pop();
            }
            switch ($()) {
                case 0:
                    id = $();
                    Q.push(std::make_pair(-t - s[id], id));
                    V[id].push_back(t + s[id]);
                    break;
                case 1:
                    if (!qry(n)) {
                        puts("Yazid is angry.");
                    } else {
                        register int l = 0, r = n, x = -1;
                        while (l <= r) {
                            int mid = (l + r) >> 1;
                            if (qry(mid))
                                x = mid, r = mid - 1;
                            else
                                l = mid + 1;
                        }
                        add(x, -1);
                        printf("%d\n", x);
                    }
                    break;
                case 2:
                    id = $();
                    if (!(qry(id) - qry(id - 1))) {
                        if (V[id].size())
                            printf("%d\n", V[id].front() - t);
                        else
                            puts("YJQQQAQ is angry.");
                    } else {
                        puts("Succeeded!");
                        add(id, -1);
                    }
                    break;
                case 3:
                    l = $(), r = $();
                    printf("%d\n", qry(r) - qry(l - 1));
                    break;
            }
        }
    }
    return 0;
}