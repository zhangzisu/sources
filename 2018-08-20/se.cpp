#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 40
const int INF = 0x7FFFFFFF;
int t, n, x, A[MAXN], B[MAXN];
int main() {
    A[1] = A[2] = 1;
    for (int i = 3; i <= 30; i++) A[i] = A[i - 2] + A[i - 1];
    for (int i = 2; i <= 30; i++) B[i] = B[i - 1] + A[i - 1];
    for (int i = 1; i <= 30; i++) printf("%d\n", B[i]);
    return 0;
}