#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#define MAX_POOL_SIZE 110
#define MAXN 10
struct node {
    int son[MAXN], fail;
    bool danger;
} p[MAX_POOL_SIZE];
int cnt = 0, n, l, m, root, pos[MAXN];
char s[20];
inline void insert(int x, int id) {
    for (int i = 1; s[i]; i++) {
        int nt = s[i] - 'A';
        if (!p[x].son[nt]) p[x].son[nt] = cnt++;
        x = p[x].son[nt];
    }
    p[x].danger = 1;
    pos[id] = x;
}
std::queue<int> Q;
inline void build(int root) {
    p[root].fail = 0;
    for (int i = 0; i < m; i++)
        if (p[root].son[i]) Q.push(p[root].son[i]);
    while (Q.size()) {
        int x = Q.front();
        Q.pop();
        for (int i = 0; i < m; i++) {
            int &s = p[x].son[i];
            if (!s) {
                s = p[p[x].fail].son[i];
            } else {
                p[s].fail = p[p[x].fail].son[i];
                p[s].danger |= p[x].danger;
                Q.push(s);
            }
        }
    }
}
double px[MAXN], mtx[MAX_POOL_SIZE][MAX_POOL_SIZE];
inline void Gauss_Jordan_Elimination() {
    for (int i = 0; i < cnt; i++) {
        int max = i;
        for (int j = i + 1; j < cnt; j++)
            if (fabs(mtx[j][i]) > fabs(mtx[max][i])) max = j;
        if (max != i)
            for (int j = i; j <= cnt; j++) std::swap(mtx[i][j], mtx[max][j]);
        for (int j = 0; j < cnt; j++)
            if (i != j) {
                double tmp = mtx[j][i] / mtx[i][i];
                for (int k = i; k <= cnt; k++) mtx[j][k] -= mtx[i][k] * tmp;
            }
    }
}
int main() {
    scanf("%d%d%d", &n, &l, &m);
    for (int i = 0, p, q; i < m; i++) scanf("%d%d", &p, &q), px[i] = (double)p / q;
    root = cnt++;
    for (int i = 1; i <= n; i++) scanf("%s", s + 1), insert(root, i);
    build(root);
    mtx[root][0] = mtx[root][cnt] = -1;
    for (int x = 0; x < cnt; x++) {
        if (x) mtx[x][x] = -1;
        if (p[x].danger) continue;
        for (int i = 0; i < m; i++) mtx[p[x].son[i]][x] += px[i];
    }
    // for (int i = 0; i < cnt; i++) {
    //     for (int j = 0; j <= cnt; j++) printf("%.2f ", mtx[i][j]);
    //     putchar(10);
    // }
    Gauss_Jordan_Elimination();
    // puts("Gauss_Jordan_Elimination::");
    // for (int i = 0; i < cnt; i++) {
    //     for (int j = 0; j <= cnt; j++) printf("%.2f ", mtx[i][j]);
    //     putchar(10);
    // }
    for (int i = 1; i <= n; i++) {
        double result = mtx[pos[i]][cnt] / mtx[pos[i]][pos[i]];
        if (fabs(result) < 1e-3) {
            puts("0.00");
            continue;
        }
        printf("%.2f\n", mtx[pos[i]][cnt] / mtx[pos[i]][pos[i]]);
    }
    return 0;
}