#include <cstdio>
const int M = 6;
const int K = 4;
int step[100010], ban[100010], pow[M + 1], cnt, all;
inline bool over(int x, int y) {
    for (int i = 0; i < M; i++) {
        int valX = x / pow[i] % K;
        int valY = y / pow[i] % K;
        if (valX < valY) return 0;
    }
    return 1;
}
int main() {
    pow[0] = 1;
    for (int i = 1; i <= M; i++) pow[i] = pow[i - 1] * K;
    for (int i = 0; i < pow[M]; i++) {
        step[++cnt] = i;
    }
    printf("RAW states : %d\n", cnt);
    for (int i = 1; i <= cnt; i++) {
        if (!ban[i]) {
            for (int j = 1; j <= cnt; j++) {
                if (!ban[j]) {
                    if (over(step[i], step[j])) ban[j] = 1;
                }
            }
        }
    }
    for (int i = 1; i <= cnt; i++) {
        if (!ban[i]) {
            all++;
        }
    }
    printf("Opt states : %d\n", all);
    return 0;
}