#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#define EPS 1e-4
#define MAXN 1010
#define MAXM 1020100
int n, k, x[MAXN], y[MAXN], u[MAXM], v[MAXM], ps[MAXM], p[MAXN], m = 0;
double w[MAXM];
inline double $(double x1, double y1, double x2, double y2){
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
inline int cmp(const int &a, const int &b){return w[a] < w[b];}
inline int find(int x){return x == p[x] ? x : p[x] = find(p[x]);}
int main(){
	scanf("%d%d", &n, &k);
	for(int i = 1;i <= n;i++)scanf("%d%d", &x[i], &y[i]);
	for(int i = 1;i <= n;i++){
		for(int j = i + 1;j <= n;j++, m++){
			u[m] = i, v[m] = j, ps[m] = m;
			w[m] = $(x[i], y[i], x[j], y[j]);
		}
	}
	std::sort(ps, ps + m, cmp);
	for(int i = 1;i <= n;i++)p[i] = i;
	for(int i = 0;i < m;i++){
		int U = find(u[ps[i]]), V = find(v[ps[i]]);
		if(U == V)continue;
		if(n-- > k)p[U] = V;
		else return printf("%.2f\n", w[ps[i]]) - 1;
	}
	return 0;
}
