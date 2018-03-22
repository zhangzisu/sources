#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 1010
int n;
long long a[MAXN], b0, b1, c0, c1, d0, d1;
std::vector<int> answer;
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
    for (int i = 1; i <= n; i++) {
        if ((i & 1) == 0) {
            b0 += a[i];
        } else {
            b1 += a[i];
        }
    }
    for (int i = 1; i <= n; i += 2)
        if (a[i] < 0)
            c1 += a[i];
        else
            break;
    for (int i = 2; i <= n; i += 2)
        if (a[i] < 0)
            c0 += a[i];
        else
            break;

    for (int i = n - (n & 1 ? 0 : 1); i >= 1; i -= 2)
        if (a[i] < 0)
            d1 += a[i];
        else
            break;
    for (int i = n - (n & 1); i >= 1; i -= 2)
        if (a[i] < 0)
            d0 += a[i];
        else
            break;
    if ((b0 - c0 - d0) < (b1 - c1 - d1)) {
        printf("%lld\n", b1 - c1 - d1);
        if (!(n & 1)) answer.push_back(n), n--;
        int rev = 0, i = 2;
        if (c1) {
            for (; a[i + 1] < 0; i += 2) answer.push_back(i - (rev++));
            answer.push_back(1);
            rev++;
        }
        if (d1) {
            for (; n > 2 && a[n - 2] < 0; n -= 2) answer.push_back(n - 1 - rev);
            answer.push_back(n - rev);
            n--;
        }
        for (; i <= n; i += 2) answer.push_back(i - (rev++));
    } else {
        printf("%lld\n", b0 - c0 - d0);
        int rev = 1, i = 3;
        answer.push_back(1);
        n--;
        if (!(n & 1)) answer.push_back(n), n--;
        if (c1) {
            for (; a[i + 1] < 0; i += 2) answer.push_back(i - (rev++));
            answer.push_back(1);
            rev++;
        }
        if (d1) {
            for (; n > 2 && a[n - 2] < 0; n -= 2) answer.push_back(n - 1 - rev);
            answer.push_back(n - rev);
            n--;
        }
        for (; i <= n; i += 2) answer.push_back(i - (rev++));
    }
    printf("%lu\n", answer.size());
    for (auto i : answer) printf("%d\n", i);
    return 0;
}