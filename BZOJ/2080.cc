#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
#define INF 0x3F3F3F3F
int n, a[MAXN], b[MAXN], c[MAXN];
template <class T>
class LinerSuffix {
   private:
    T max[MAXN << 2], min[MAXN << 2];

   public:
    inline LinerSuffix() {
        memset(max, 0, sizeof(max));
        memset(min, 0x3F, sizeof(min));
    }
    void insert(int n, int l, int r, int d, T v) {
        if (l == r) return void(max[n] = min[n] = v);
        int mid = (l + r) >> 1;
        if (d <= mid)
            insert(n << 1, l, mid, d, v);
        else
            insert(n << 1 | 1, mid + 1, r, d, v);
        max[n] = std::max(max[n << 1], max[n << 1 | 1]);
        min[n] = std::min(min[n << 1], min[n << 1 | 1]);
    }
    T Max(int n, int l, int r, int L, int R) {
        if (l == L && r == R) return max[n];
        int mid = (l + r) >> 1;
        if (R <= mid) return Max(n << 1, l, mid, L, R);
        if (L > mid) return Max(n << 1 | 1, mid + 1, r, L, R);
        return std::max(
            Max(n << 1, l, mid, L, mid),
            Max(n << 1 | 1, mid + 1, r, mid + 1, R));
    }
    T Min(int n, int l, int r, int L, int R) {
        if (l == L && r == R) return min[n];
        int mid = (l + r) >> 1;
        if (R <= mid) return Min(n << 1, l, mid, L, R);
        if (L > mid) return Min(n << 1 | 1, mid + 1, r, L, R);
        return std::min(
            Min(n << 1, l, mid, L, mid),
            Min(n << 1 | 1, mid + 1, r, mid + 1, R));
    }
};
LinerSuffix<std::pair<int, int>> A, B;
int vis[MAXN];
bool DFS(int x, int col) {
    if (!x) return 1;
    if (vis[x]) return vis[x] == col;
    vis[x] = col;
    A.insert(1, 1, n, x, std::make_pair(0, 0));
    B.insert(1, 1, n, a[x], std::make_pair(INF, 0));
    if (x + 1 <= c[a[x]])
        for (
            std::pair<int, int> i = A.Max(1, 1, n, x + 1, c[a[x]]);
            i.first && i.first > a[x];
            i = A.Max(1, 1, n, x + 1, c[a[x]])) {
            if (!DFS(i.second, 3 - col)) return 0;
        }
    if (b[x] + 1 <= a[x] - 1)
        for (
            std::pair<int, int> i = B.Min(1, 1, n, b[x] + 1, a[x] - 1);
            i.first != INF && i.first < x;
            i = B.Min(1, 1, n, b[x] + 1, a[x] - 1)) {
            if (!DFS(i.second, 3 - col)) return 0;
        }
    return 1;
}
int BIT[3][MAXN];
inline int lowbit(int x) { return x & -x; }
inline void set(int *a, int p) {
    for (; p <= n; p += lowbit(p)) a[p]++;
}
inline int get(int *a, int p) {
    int ret = 0;
    for (; p; p -= lowbit(p)) ret += a[p];
    return ret;
}
int main() {
    scanf("%d", &n);
    b[n + 1] = 0x3F3F3F3F;
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = n; i >= 1; i--) b[i] = std::min(b[i + 1], a[i]);
    for (int i = 1; i <= n; i++) c[b[i] + 1] = std::max(c[b[i] + 1], i);
    for (int i = 1, j = 0; i <= n; c[i++] = j)
        while (j < n && b[j + 1] < i) j++;
    for (int i = 1; i <= n; i++) {
        A.insert(1, 1, n, i, std::make_pair(a[i], i));
        B.insert(1, 1, n, a[i], std::make_pair(i, i));
    }
    for (int i = 1; i <= n; i++)
        if (!vis[i] && !DFS(i, 1)) return puts("NIE"), 0;
    for (int i = 1; i <= n; i++) {
        if(get(BIT[vis[i]], a[i] - 1) > get(BIT[vis[i]], b[i])) return puts("NIE"), 0;
        set(BIT[vis[i]], a[i]);
    }
    puts("TAK");
    for(int i = 1;i <= n;i++)printf("%d%c", vis[i], " \n"[i == n]);
    return 0;
}