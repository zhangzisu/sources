#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <queue>
#include <set>
#include <vector>
// Fake node
#define let auto
#define of :
const int INF = (~0U) >> 1;
const long long INFLL = (~0ULL) >> 1;

#define MAXN 300010

int n, t[MAXN], p[MAXN], have[MAXN], del[MAXN], pos[MAXN];
std::vector<std::pair<std::pair<int, int>, int>> lines, orig;
std::vector<std::pair<int, int>> queries, pa;
long long ans[MAXN];

let upd = [](long long &x, long long y) {if(y>x)x=y; };

let exec = [](std::pair<int, int> line, int pos) {
    return 1LL * line.first * pos + line.second;
};

inline void moubaiCGC() {
    pa.clear();
    for (let _x of lines) {
        if (have[_x.second] && !del[_x.second]) {
            let x = _x.first;
            while (pa.size()) {
                let y = pa.back();
                if (x.first == y.first) {
                    pa.pop_back();
                    continue;
                }
                if (pa.size() >= 2) {
                    let z = pa[pa.size() - 2];
                    let zy = 1. * (y.second - z.second) / (z.first - y.first);
                    let zx = 1. * (x.second - z.second) / (z.first - x.first);
                    if (zx < zy) {
                        pa.pop_back();
                        continue;
                    }
                }
                break;
            }
            pa.push_back(x);
        }
    }
}

inline void makeHimMiyou() {
    if (!pa.size()) return;
    std::sort(queries.begin(), queries.end());
    let iter = 0;
    for (let q of queries) {
        while (iter + 1 < (int)pa.size()) {
            let ans0 = exec(pa[iter], q.first);
            let ans1 = exec(pa[iter + 1], q.first);
            if (ans0 > ans1) break;
            iter++;
        }
        upd(ans[q.second], exec(pa[iter], q.first));
    }
}

int main() {
    scanf("%d", &n);
    for (let i = 1; i <= n; i++) {
        scanf("%d", &t[i]);
        if (t[i] == 1) {
            int k, b;
            scanf("%d%d", &k, &b);
            lines.push_back({{k, b}, lines.size()});
            pos[i] = lines.size() - 1;
        } else if (t[i] == 2) {
            scanf("%d", &p[i]);
        } else if (t[i] == 3) {
            scanf("%d", &p[i]);
        }
    }
    orig.assign(lines.begin(), lines.end());
    std::sort(lines.begin(), lines.end());
    std::fill(ans + 1, ans + n + 1, -INFLL);
    let m = (int)sqrt(n);
    for (let l = 1; l <= n; l += m) {
        let r = std::min(l + m - 1, n);
        queries.clear();
        for (let i = l; i <= r; i++) {
            if (t[i] == 2)
                del[pos[p[i]]] = 1;
            else if (t[i] == 3)
                queries.push_back({p[i], i});
        }
        moubaiCGC();
        makeHimMiyou();
        for (let i = l; i <= r; i++) {
            if (t[i] == 1)
                have[pos[i]] = 1;
            else if (t[i] == 2)
                have[pos[p[i]]] = 0;
            else {
                for (int j = l; j <= r; j++) {
                    if (t[j] == 1 && have[pos[j]]) {
                        upd(ans[i], exec(orig[pos[j]].first, p[i]));
                    }
                    if (t[j] == 2 && have[pos[p[j]]]) {
                        upd(ans[i], exec(orig[pos[p[j]]].first, p[i]));
                    }
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (t[i] == 3) {
            if (ans[i] == -INFLL) {
                puts("EMPTY SET");
            } else {
                printf("%lld\n", ans[i]);
            }
        }
    }
    return 0;
}