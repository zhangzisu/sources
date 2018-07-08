#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 256
int n;
int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) printf("%4d ", i ^ j);
        puts("");
    }
    return 0;
}