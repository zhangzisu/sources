#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
char buf[100010];
int n = 0;
inline int get(char c) { return c - 'A'; }
int main() {
    scanf("%s", buf + 1);
    n = strlen(buf + 1);
    for (int i = 1; i <= n - ; i++) {
        if (buf[i] != '.' && buf[i + 1] != '.' && buf[i + 2] != '.') {
            if (buf[i] != buf[i + 1] && buf[i + 1] != buf[i + 2] && buf[i + 2] != buf[i]) {
                return puts("Yes"), 0;
            }
        }
    }
    puts("No");
    return 0;
}