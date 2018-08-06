#include <bits/stdc++.h>
char buf[100];
double a, b;
int main() {
    FILE *out = fopen("userout", "r");
    FILE *ans = fopen("answer", "r");
    while (~fscanf(ans, "%lf", &b)) {
        fscanf(out, "%s", buf);
        if (!isdigit(buf[0])) {
            fprintf(stdout, "0");
            fprintf(stderr, "Too young too simple, sometimes naive!");
            return 0;
        }
        sscanf(buf, "%lf", &a);
        if (fabs(a - b) > 1e-6) {
            fprintf(stdout, "0");
            fprintf(stderr, "ni de chengxu shuchu la cuowu de daan");
            return 0;
        }
    }

    fprintf(stdout, "100");
    fprintf(stderr, "ni de chengxu tongguo la zhege dian");
}