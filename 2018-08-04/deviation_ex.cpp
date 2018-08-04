#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#include <map>
inline int $() {
    register int x = 0;
    register char ch = getchar();
    while (!isdigit(ch)) ch = getchar();
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return x;
}
#define MAXN 100010
#define INF 0x3F3F3F3F
int t, n, m, cnt, A[MAXN], B[MAXN], a[MAXN], b[MAXN];
std::set<int> S;
struct node_t{
    std::map<int, int> son;
    int fail;
    inline void init(){
        son.clear();
        fail = 0;
    }
}ACM[MAXN];
inline void insert(int *a, int len){
    int p = 1;
    for(int i = 1;i <= len;i++){
        if(!ACM[p].son.count(a[i]))
    }
}
int main() {
#ifndef DEBUG
    freopen("deviation.in", "r", stdin);
    freopen("deviation.out", "w", stdout);
#endif
    for (t = $(); t; t--) {
        S.clear();
        n = $();
        for (int i = 1; i <= n; i++) A[i] = $();
        m = $();
        for (int i = 1; i <= m; i++) B[i] = $();
        if (m == 1) {
            int f1, f2, f3, f4, f5;
            f1 = 0;
            f2 = INF;
            f3 = 0;
            f4 = INF;
            f5 = 0;
            for (int i = 1; i <= n; i++)
                if (A[i] == B[1]) {
                    S.insert(B[1] - A[i]);
                    f2 = std::min(f2, std::abs(B[1] - A[i]));
                    f3++;
                    f4 = std::min(f4, i);
                    f5 = std::max(f5, i);
                }
            f1 = S.size();
            if (!f1)
                puts("0 0 0 0 0");
            else
                printf("%d %d %d %d %d\n", f1, f2, f3, f4, f5);
            continue;
        }
        for (int i = 1; i < n; i++) a[i] = A[i + 1] - A[i];
        for (int i = 1; i < m; i++) b[i] = B[i + 1] - B[i];
        n--, m--;
        for (int i = 1; i <= n; i++) printf("%d%c", a[i], " \n"[i == n]);
        for (int i = 1; i <= m; i++) printf("%d%c", b[i], " \n"[i == m]);
        int f1, f2, f3, f4, f5;
        f1 = 0;
        f2 = INF;
        f3 = 0;
        f4 = INF;
        f5 = 0;
        for (int i = 1; i <= (n - m + 1); i++) {
            unsigned hA = GET_HASH(HASH[0], i, i + m - 1, 0);
            unsigned hB = GET_HASH(HASH[1], i, i + m - 1, 1);
            if (hA == ORI[0][m] && hB == ORI[1][m]) {
                S.insert(B[1] - A[i]);
                f2 = std::min(f2, std::abs(B[1] - A[i]));
                f3++;
                f4 = std::min(f4, i);
                f5 = std::max(f5, i);
            }
        }
        f1 = S.size();
        if (!f1)
            puts("0 0 0 0 0");
        else
            printf("%d %d %d %d %d\n", f1, f2, f3, f4, f5);
    }
    return 0;
}