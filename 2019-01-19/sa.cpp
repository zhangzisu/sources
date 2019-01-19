#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MOD 1000000007
#define MAXN 550
long double x[100][100];
inline void Gauss(int n) {
	for (int i = 0; i < n; i++) {
		int p = i;
		while (p < n && std::abs(x[p][i]) < 1e-18) p++;
		if (p != i) {
			for (int j = i; j <= n; j++) std::swap(x[i][j], x[p][j]);
		}
		for (p = 0; p < n; p++) {
			if (i == p) continue;
			long double tmp = x[p][i] / x[i][i];
			for (int j = i; j <= n; j++)
				x[p][j] -= x[i][j] * tmp;
		}
	}
}
int main() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%Lf", &x[i][0]);
		for (int j = 1; j < n; j++) x[i][j] = x[i][j - 1] * x[i][0];
		scanf("%Lf", &x[i][n]);
	}
    for(int i=0;i<n;i++){
        for(int j=0;j<=n;j++)printf("%Lf ", x[i][j]);
        puts("");
    }
	Gauss(n);
    for(int i=0;i<n;i++){
        for(int j=0;j<=n;j++)printf("%Lf ", x[i][j]);
        puts("");
    }
	for (int i = 0; i < n; i++) printf("%.18Lf\n", x[i][n] / x[i][i]);
}