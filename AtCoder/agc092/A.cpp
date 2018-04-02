#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 26
int n, vis[MAXN], flag;
char buf[MAXN + 10];
char ans[MAXN + 10];
int main() {
    scanf("%s", buf);
    n = strlen(buf);
    for (int i = 0; i < n; i++) {
        for (int j = buf[i] - 'a'; j < 26; j++) {
            if (!vis[j]) {
                vis[j] = 1;
                ans[i] = j + 'a';
                flag |= j != buf[i] - 'a';
                goto succ;
            }
        }
        return puts("-1"), 0;
    succ:
        continue;
    }
    if (!flag) {
        for (int j = 0; j < 26; j++)
            if (!vis[j]) {
                ans[n] = j + 'a';
                goto ok;
            }
        return puts("-1"), 0;
    ok:;
    }
    puts(ans);
    return 0;
}