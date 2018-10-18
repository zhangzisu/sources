struct HashMap {
    const static int MOD = 19260817;
    const static int SIZE = 5000010;
    int head[MOD], next[SIZE], tot;
    lnt key[SIZE];
    double val[SIZE];
    inline HashMap() {
        memset(head, 0, sizeof(head));
        tot = 0;
    }
    inline double* get(lnt k) {
        int p = k % MOD;
        for (int i = head[p]; i; i = next[i]) {
            if (key[i] == k) return val + i;
        }
        next[++tot] = head[p], key[tot] = k, head[p] = tot;
        return val + tot;
    }
} map;