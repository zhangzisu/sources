#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>

char buf[201000];
int n, m, s1, s2, a[201000], b[201000], c[201000];
void o(int k) {
    m++;
    if (a[k])
        o(a[k]), printf("%d ", k);
    else
        printf("%d ", m), printf("%d ", k);
}
int main(int argc, char *argv[]) {
    scanf("%s", buf + 1);
    int n = strlen(buf + 1);
    if (buf[1] == '1' || buf[n] == '1') {
        puts("-1");
        return 0;
    }
    for (int i = 1; i <= n; i++)
        if (buf[i] == '1') {
            if (!s1) return printf("-1"), 0;
            a[i] = b[s1--];
            s2++;
            c[s2] = i;
        } else {
            if (s2) a[i] = c[s2], s2--;
            b[++s1] = i;
        }
    if (s2) return printf("-1"), 0;
    printf("%d\n", s1);
    for (int i = 1; i <= s1; i++) {
        m = 0;
        o(b[i]);
        printf("\n");
    }
    return 0;
}