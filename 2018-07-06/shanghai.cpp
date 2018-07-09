#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <vector>
#define MOD 65521
#define MAXN 100010
typedef long long lnt;

int k;
lnt n;

struct Matrix {
    int **val, size;
    inline Matrix(int s = 0) {
        size = s;
        val = (int**)calloc(size, sizeof(int*));
        for (int i = 0; i < size; i++) val[i] = (int*)calloc(size, sizeof(int));
    }
    inline Matrix(const Matrix& arg) {
        size = arg.size;
        val = (int**)calloc(size, sizeof(int*));
        for (int i = 0; i < size; i++) val[i] = (int*)calloc(size, sizeof(int));
        for (int i = 0; i < size; i++) memcpy(val[i], arg.val[i], sizeof(int) * size);
    }
    inline int* operator[](int index) {
        return val[index];
    }
    inline void print() {
        puts(">>> Matrix");
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) printf("%10d", val[i][j]);
            puts("");
        }
    }
    inline friend Matrix operator*(Matrix a, Matrix b) {
        assert(a.size == b.size);
        Matrix c(a.size);
        for (int i = 0; i < a.size; i++)
            for (int j = 0; j < a.size; j++)
                for (int k = 0; k < a.size; k++)
                    c[i][j] = (1LL * a[i][k] * b[k][j] % MOD + c[i][j]) % MOD;
        return c;
    }
    inline void operator=(Matrix arg) {
        size = arg.size;
        val = (int**)calloc(size, sizeof(int*));
        for (int i = 0; i < size; i++) val[i] = (int*)calloc(size, sizeof(int));
        for (int i = 0; i < size; i++) memcpy(val[i], arg.val[i], sizeof(int) * size);
    }
} Mtx;
inline int fuck(int x, int p) {
    register int y = 1;
    while (p) {
        if (p & 1) y = 1LL * y * x % MOD;
        x = 1LL * x * x % MOD;
        p >>= 1;
    }
    return y;
}
inline int Gauss(Matrix& x, int n) {
    int ret = 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (x[i][j] < 0) x[i][j] += MOD;
    for (int i = 0; i < n; i++) {
        int p = i;
        while (p < n && !x[p][i]) p++;
        if (p >= n) return 0;
        if (p != i) {
            for (int j = i; j < n; j++) std::swap(x[i][j], x[p][j]);
            ret = MOD - ret;
        }
        ret = 1LL * ret * x[i][i] % MOD;
        int inv = fuck(x[i][i], MOD - 2);
        for (p = i + 1; p < n; p++) {
            if (!x[p][i]) continue;
            int tmp = 1LL * x[p][i] * inv % MOD;
            for (int j = i; j < n; j++)
                x[p][j] = (MOD - 1LL * x[i][j] * tmp % MOD + x[p][j]) % MOD;
        }
    }
    return ret;
}

int calc(int n) {
    Mtx = Matrix(n);
    for (int i = 0; i < n; i++) {
        for (int j = -k; j <= k; j++) {
            if (j == 0) continue;
            Mtx[i][(i + j + n) % n] = -1;
        }
        Mtx[i][i] = 2 * k;
    }
    // Mtx.print();
    return Gauss(Mtx, n - 1);
}

int cnt, fail[MAXN];
int val[MAXN], delta[MAXN];
std::vector<int> ans[MAXN];
int main() {
    scanf("%d%lld", &k, &n);

    for (int i = 1; i <= 350; i++)
        val[i] = calc(i + k * 2);
    if (n - k * 2 <= 350) return printf("%d\n", val[n - k * 2]), 0;

    for (int i = 1; i <= 350; i++) {
        int tmp = val[i];
        for (int j = 0; j < (int)ans[cnt].size(); j++)
            tmp = (tmp - 1LL * ans[cnt][j] * val[i - j - 1] % MOD + MOD) % MOD;
        delta[i] = tmp;
        if (!tmp) continue;
        fail[cnt] = i;
        if (cnt == 0) {
            ans[++cnt].resize(i);
            continue;
        }
        int mul = 1LL * delta[i] * fuck(delta[fail[cnt - 1]], MOD - 2) % MOD;
        cnt++;
        ans[cnt].resize(i - fail[cnt - 2] - 1);
        ans[cnt].push_back(mul);
        for (int j = 0; j < (int)ans[cnt - 2].size(); j++)
            ans[cnt].push_back(MOD - 1LL * ans[cnt - 2][j] * mul % MOD);
        if (ans[cnt].size() < ans[cnt - 1].size()) ans[cnt].resize(ans[cnt - 1].size());
        for (int j = 0; j < (int)ans[cnt - 1].size(); j++)
            (ans[cnt][j] += ans[cnt - 1][j]) %= MOD;
    }
    // printf("%d\n", ans[cnt].size());
    // for (int i = 0; i < ans[cnt].size(); i++) printf("%d ", val[i + 1]);
    // puts("");
    int N = ans[cnt].size();
    Matrix transform(N), inital(N);
    for (int i = 0; i < N; i++) transform[i][0] = ans[cnt][i];
    for (int i = 0; i < N - 1; i++) transform[i][i + 1] = 1;
    // transform.print();
    for (int i = 0; i < N; i++) inital[0][i] = val[N - i];
    // inital.print();
    long long count = n - N - 2 * k;
    for (; count; count >>= 1) {
        if (count & 1) inital = inital * transform;
        transform = transform * transform;
    }
    printf("%d\n", inital[0][0]);
    return 0;
}