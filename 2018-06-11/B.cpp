#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
int p, n;
char buf[2010];
int main() {
    scanf("%d%d%s", &n, &p, buf + 1);
    int all = (n - 1) / p + 1, flag = 1;
    for (int i = 1; i < all; i++) {
        //compare i with i + 1
        for (int j = 1; j <= p; j++) {
            int p1 = (i - 1) * p + j;
            int p2 = i * p + j;
            if (p2 > n) break;
            if (buf[p1] != '.' && buf[p2] != '.') {
                if (buf[p1] != buf[p2]) flag = 0;
            } else if (buf[p1] == '.' && buf[p2] == '.') {
                flag = 0;
                buf[p1] = '1';
                buf[p2] = '0';
            } else if (buf[p1] == '.') {
                flag = 0;
                buf[p1] = '0' + ('1' - buf[p2]);
            } else {
                flag = 0;
                buf[p2] = '0' + ('1' - buf[p1]);
            }
        }
    }
    if (flag) return puts("No"), 0;
    for (int i = 1; i <= n; i++) putchar(buf[i] != '.' ? buf[i] : '0');
    return 0;
}