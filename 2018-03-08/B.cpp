#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
int n, k, t;
long long state;
inline int digit() {
    char ch = getchar();
    while (!isdigit(ch)) ch = getchar();
    return ch ^ 48;
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &k);
        for (int i = state = 0; i < n; i++) state = (state << 1) | digit();
        if(n == k){ puts("0"); continue; }
        
    }
    return 0;
}