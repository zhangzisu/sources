#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
typedef long long lnt;
typedef unsigned long long ulnt;
int n, F, s[MAXN];
ulnt hash1[MAXN], hash2[MAXN], pw1[MAXN], pw2[MAXN];
const ulnt base1 = 23, base2 = 39;
ulnt hash(ulnt* arr, ulnt* pw, int l, int r) {
    return arr[r] - arr[l - 1] * pw[r - l + 1];
}

int main() {
    scanf("%d%d", &n, &F);
    for (int i = 1; i <= n; i++) scanf("%d", &s[i]);
    pw1[0] = pw2[0] = 1;
    for (int i = 1; i <= n; i++) {
        pw1[i] = pw1[i - 1] * base1;
        hash1[i] = hash1[i - 1] * base1 + s[i];
        pw2[i] = pw2[i - 1] * base2;
        hash2[i] = hash2[i - 1] * base2 + s[i];
    }
    lnt ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int len = 1; len <= n; len++) {
            if (i + len - 1 + F + len > n) break;
            int l1 = i, r1 = l1 + len - 1;
            int l2 = i + len + F, r2 = l2 + len - 1;
            if (
                hash(hash1, pw1, l1, r1) == hash(hash1, pw1, l2, r2) &&
                hash(hash2, pw2, l1, r1) == hash(hash2, pw2, l2, r2)) ans++;
        }
    }
    printf("%lld\n", ans);
    return 0;
}