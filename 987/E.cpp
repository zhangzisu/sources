#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 1000010
typedef long long lnt;
lnt n, a[MAXN], tmp[MAXN], cnt;
void mergesort(lnt l, lnt r) {
    if (l >= r) return;
    lnt m = (l + r) / 2;
    lnt i = l, j = m + 1, k = 0;
    while (i <= m && j <= r) {
        if (a[i] > a[j]) {
            tmp[k++] = a[j++];
            cnt += m - i + 1;
        } else {
            tmp[k++] = a[i++];
        }
    }
    while (i <= m) tmp[k++] = a[i++];
    while (j <= r) tmp[k++] = a[j++];
    for (i = 0; i < k; i++) a[i + l] = tmp[i];
}
void mergearray(lnt l, lnt r) {
    if (l >= r) return;
    lnt m = (l + r) / 2;
    mergearray(l, m);
    mergearray(m + 1, r);
    mergesort(l, r);
}

int main() {
    scanf("%I64d", &n);
    for (lnt i = 0; i < n; i++) scanf("%I64d", &a[i]);
    mergearray(0, n - 1);
    lnt petr = (n * 3) & 1;
    cnt = cnt & 1;
    puts(cnt == petr ? "Petr" : "Um_nik");
}
