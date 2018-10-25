#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXV 1000010
int pri[MAXV], vis[MAXV], pnt = 0;
inline void shai() {
    for (int i = 2; i < MAXV; i++) {
        if (!vis[i]) pri[++pnt] = i;
        for (int j = 1; j <= pnt; j++) {
            if (i * pri[j] >= MAXV) break;
            vis[i * pri[j]] = 1;
            if (i % pri[j] == 0) break;
        }
    }
}
int n, m, p[MAXV];
int main() {
    shai();
    //
    return 0;
}