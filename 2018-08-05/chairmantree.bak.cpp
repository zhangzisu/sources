#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#define MAXN 100010
int n, k, l, max, a[MAXN];
std::priority_queue<int> Q, P;
int main() {
    scanf("%d%d%d", &n, &k, &l);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    max = a[1];
    for (int i = 2; i <= n; i++) max = std::max(max, a[i]);
    for (int i = 1; i <= n - k + 1; i++) {
        while (Q.size()) Q.pop();
        for (int j = i; j <= n; j++) {
            Q.push(a[j]);
            if ((int)Q.size() > k) Q.pop();
            if ((int)Q.size() == k) P.push(-Q.top());
            if ((int)P.size() > l) P.pop();
        }
    }
    printf("%d\n", -P.top());
    return 0;
}