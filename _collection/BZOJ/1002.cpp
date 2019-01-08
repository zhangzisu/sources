#define ALL 1, 1, top
const int N = 1e5;
int fa[N + 1], ch[N + 1][2], H[N + 1], top, root;
set<int> S;
typedef set<int>::iterator iter;
inline int Hash(int x) {
    return lower_bound(H + 1, H + top + 1, x) - H;
}
struct Seg {
    int d[N * 4];
    void down(int o) {
        if (d[o]) {
            d[o * 2] += d[o];
            d[o * 2 + 1] += d[o];
            d[o] = 0;
        }
    }

    void modify(int x, int v, int o, int l, int r) {
        if (l == r) return d[o] = v, void();
        down(o);
        int m = (l + r) / 2;
        x <= m ? modify(x, v, o * 2, l, m) : modify(x, v, o * 2 + 1, m + 1, r);
    }
    int query(int x, int o, int l, int r) {
        if (l == r) return d[o];
        down(o);
        int m = (l + r) / 2;
        return x <= m ? query(x, o * 2, l, m) : query(x, o * 2 + 1, m + 1, r);
    }
    void add(int L, int R, int v, int o, int l, int r) {
        if (L <= l && r <= R) return d[o] += v, void();
        down(o);
        int m = (l + r) / 2;
        if (L <= m) add(L, R, v, o * 2, l, m);
        if (R > m) add(L, R, v, o * 2 + 1, m + 1, r);
    }
} T;
int insert(int x) {
    int d;
    fa[x] = ch[x][0] = ch[x][1] = 0;

    if (S.empty()) {
        root = x;
        d = 1;
    } else {
        iter it = S.upper_bound(x);
        if (it != S.end() && !ch[*it][0])
            ch[fa[x] = *it][0] = x;
        else {
            --it;
            ch[fa[x] = *it][1] = x;
        }
        d = T.query(fa[x], ALL) + 1;
    }
    S.insert(x);
    T.modify(x, d, ALL);
    return d;
}
int spaly(int t) {
    if (!ch[root][t]) return 1;

    int x = t ? *S.rbegin() : *S.begin(), d = T.query(x, ALL), y = ch[x][t ^ 1], z = fa[x];
    ch[fa[y] = z][t] = y;
    ch[fa[root] = x][t ^ 1] = root;
    fa[x] = 0;
    root = x;

    T.modify(x, 1, ALL);
    if (z) {
        if (t)
            T.add(1, z, 1, ALL);
        else
            T.add(z, top, 1, ALL);
    }
    return d;
}
void remove(int t) {
    int r = ch[root][t ^ 1];
    S.erase(root);
    fa[r] = 0;
    root = r;
    T.add(1, top, -1, ALL);
}
struct Op {
    int c, k;
} O[N];
int main() {
    int m;
    scanf("%d", &m);
    rep(i, 0, m) {
        scanf("%d", &O[i].c);
        if (O[i].c == 1) {
            scanf("%d", &O[i].k);
            H[++top] = O[i].k;
        }
    }
    sort(H + 1, H + top + 1);
    top = unique(H + 1, H + top + 1) - H - 1;
    rep(i, 0, m) {
        const Op& o = O[i];
        if (o.c == 1)
            printf("%d\n", insert(Hash(o.k)));
        else
            printf("%d\n", spaly(o.c & 1));
        if (o.c >= 4)
            remove(o.c & 1);
    }
    return 0;
}