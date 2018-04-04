#include<cstdio>
#include<cstdlib>
#include<set>
using std::set;
#define MAXN 200010
#define MOD 1061109559
#define BASE 2333
int po[MAXN], A[MAXN], B[MAXN], col[MAXN], n;
inline int a(int x, int y) { return ((A[y] - (long long)A[x - 1] * po[y - x + 1] % MOD) + MOD) % MOD; }
char buf[MAXN];

int main() {
	scanf("%d", &n);
    scanf("%s", buf + 1);

	po[0] = 1;
	for (int i = 1; i <= n; i++)po[i] = (long long)po[i - 1] * BASE % MOD;
	for (int i = 1; i <= n; i++)A[i] = ((long long)A[i - 1] * BASE + buf[i]-'a') % MOD;

    for(int i = 1;i <= ((n + 1) / 2);i++){
        const int L = i;
        const int R = n + 1 - i;
        const int len = R - L + 1;
        register int l = 1, r = len - 1,ans = -1;
    }
	return 0;
}