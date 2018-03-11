#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define BUF 1048576
char _1[BUF], *_3 = _1 + BUF;
inline char gc() {
    if (_3 == _1 + BUF) fread(_1, 1, BUF, stdin), _3 = _1;
    return *_3++;
}
inline int $() {
    register int x = 0;
    register char ch = gc();
    while (!isdigit(ch)) ch = gc();
    for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return x;
}
inline char c() {
    register char ch = gc();
    while (!isalpha(ch)) ch = gc();
    return ch;
}
#define MAXN 2000
#define MOD 998244353
int n = $(), m = $(), ans, col[MAXN], flag = 1;
inline int c2i(char c) { return c == 'r' ? 1 : c == 'b' ? 2 : 0; }
int a[MAXN][MAXN], f[2][MAXN][3][2][2][2];
inline void $(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}
int main() {
    for (register int i0 = 0; i0 < n; i0++) col[i0] = c2i(c());
    for (register int i0 = 0; i0 < m; i0++)
        for (register int i1 = 0; i1 < n; i1++) a[i0][i1] = $();

    for (register int cur = 0; cur < n; cur++) {
        for (register int dr = 0; dr <= 2; dr++) {
            const int pos = (cur + dr + n - 1) % n;
            for (register int i = 0; i <= (col[cur] == 1); i++) {
                for (register int j = 0; j <= (col[cur] == 2); j++) {
                    $(f[1][pos][dr][0][i][j], a[0][cur]);
                }
            }
        }
    }

    for (register int cur = 0; cur < n; cur++) {
        for (register int dr = 0; dr <= 2; dr++) {
            for (register int n1 = 0; n1 <= 1; n1++) {
                for (register int n2 = 0; n2 <= 1; n2++) {
                    $(f[1][cur][dr][1][n1][n2], f[1][cur][dr][0][n1][n2]);
                }
            }
        }
    }
    for (register int cur = 0; cur < n; cur++) {
        if (col[cur] != 1) continue;
        for (register int dr = 0; dr <= 2; dr++) {
            for (register int n1 = 0; n1 <= 1; n1++) {
                for (register int n2 = 0; n2 <= 1; n2++) {
                    $(f[1][cur][dr][n1][1][n2], f[1][cur][dr][n1][0][n2]);
                }
            }
        }
    }
    for (register int cur = 0; cur < n; cur++) {
        if (col[cur] != 2) continue;
        for (register int dr = 0; dr <= 2; dr++) {
            for (register int n1 = 0; n1 <= 1; n1++) {
                for (register int n2 = 0; n2 <= 1; n2++) {
                    $(f[1][cur][dr][n1][n2][1], f[1][cur][dr][n1][n2][0]);
                }
            }
        }
    }
    for (register int cur = 0; cur < n; cur++) {
        for (register int dr = 0; dr <= 2; dr++) {
            for (register int n0 = 0; n0 <= 1; n0++) {
                for (register int n1 = 0; n1 <= 1; n1++) {
                    for (register int n2 = 0; n2 <= 1; n2++) {
                        f[1][cur][dr][n0][n1][n2] = 1LL * f[1][cur][dr][n0][n1][n2] * a[1][cur] % MOD;
                    }
                }
            }
        }
    }

    for (register int i = 2; i < m; i++) {
        const int now = i & 1, pre = !now;
        memset(f[now], 0, sizeof(f[now]));
        for (register int cur = 0; cur < n; cur++) {
            for (register int dr = 0; dr <= 2; dr++) {
                for (register int pr = 0; pr <= 2; pr++) {
                    const int pos = (cur + pr + n - 1) % n;
                    for (register int n0 = pr != dr; n0 <= 1; n0++) {
                        const int px = (pr == dr ? n0 : 0);
                        for (register int n1 = 0; n1 <= 1; n1++) {
                            for (register int n2 = 0; n2 <= 1; n2++) {
                                $(f[now][pos][pr][px][n1][n2], f[pre][cur][dr][n0][n1][n2]);
                            }
                        }
                    }
                }
            }
        }
        for (register int cur = 0; cur < n; cur++) {
            for (register int dr = 0; dr <= 2; dr++) {
                for (register int n1 = 0; n1 <= 1; n1++) {
                    for (register int n2 = 0; n2 <= 1; n2++) {
                        $(f[now][cur][dr][1][n1][n2], f[now][cur][dr][0][n1][n2]);
                    }
                }
            }
        }
        for (register int cur = 0; cur < n; cur++) {
            if (col[cur] != 1) continue;
            for (register int dr = 0; dr <= 2; dr++) {
                for (register int n1 = 0; n1 <= 1; n1++) {
                    for (register int n2 = 0; n2 <= 1; n2++) {
                        $(f[now][cur][dr][n1][1][n2], f[now][cur][dr][n1][0][n2]);
                    }
                }
            }
        }
        for (register int cur = 0; cur < n; cur++) {
            if (col[cur] != 2) continue;
            for (register int dr = 0; dr <= 2; dr++) {
                for (register int n1 = 0; n1 <= 1; n1++) {
                    for (register int n2 = 0; n2 <= 1; n2++) {
                        $(f[now][cur][dr][n1][n2][1], f[now][cur][dr][n1][n2][0]);
                    }
                }
            }
        }
        for (register int cur = 0; cur < n; cur++) {
            for (register int dr = 0; dr <= 2; dr++) {
                for (register int n0 = 0; n0 <= 1; n0++) {
                    for (register int n1 = 0; n1 <= 1; n1++) {
                        for (register int n2 = 0; n2 <= 1; n2++) {
                            f[now][cur][dr][n0][n1][n2] = 1LL * f[now][cur][dr][n0][n1][n2] * a[i][cur] % MOD;
                        }
                    }
                }
            }
        }
    }
    for (register int cur = 0; cur < n; cur++) {
        for (register int dr = 0; dr <= 2; dr++) {
            for (register int p1 = 0; p1 <= 1; p1++) {
                for (register int p2 = 0; p2 <= 1; p2++) {
                    $(ans, f[(m - 1) & 1][cur][dr][1][p1][p2]);
                }
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}