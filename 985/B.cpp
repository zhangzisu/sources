#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
int n, m, A[2001][2001], B[2001];
int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            char x;
            std::cin >> x;
            A[i][j] = x ^ 48;
        }
    for (int j = 1; j <= m; j++)
        for (int i = 1; i <= n; i++)
            B[j] += A[i][j] == 1;
    for (int i = 1; i <= n; i++) {
        bool ddd = 0;
        for (int j = 1; j <= m; j++) {
            if (B[j] == 1 && A[i][j] == 1) {
                ddd = 1;
                break;
            }
            if (!B[j]) break;
        }
        if (!ddd) {
            return puts("YES"), 0;
        }
    }
    return puts("NO"), 0;
}