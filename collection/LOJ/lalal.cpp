#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cctype>
inline int $(){
	register int x = 0; register char ch = getchar();
	while(!isdigit(ch))ch = getchar();
	for(;isdigit(ch);ch = getchar())x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}

#define MAXN 200010
#define INFLL 2000000000000000000LL
int n, m, k;
long long w[MAXN], pre[MAXN], suf[MAXN], dis[MAXN], t;
inline long long getDis(int x, int y){
	if(x > y)std::swap(x, y);
	return pre[y] - pre[x];
}
std::pair<int, long long> edge[MAXN];
long long tag[MAXN << 2], ans;
inline void pushDown(int);
inline long long query(long long *a, int n, int l, int r, int L, int R){
	if(l == L && r == R)return a[n];
	int mid = (l + r) >> 1; pushDown(n);
	if(R <= mid)return query(a, n << 1, l, mid, L, R);
	if(L > mid)return query(a, n << 1 | 1, mid + 1, r, L, R);
	return std::min(query(a, n << 1, l, mid, L, mid), query(a, n << 1 | 1, mid + 1, r, mid + 1, R));
}
inline void modify(long long *a, int n, int l, int r, int p, long long v){
	if(l == r) return void(a[n] = v);
	int mid = (l + r) >> 1; pushDown(n);
	if(p <= mid)modify(a, n << 1, l, mid, p, v);
	else modify(a, n << 1 | 1, mid + 1, r, p, v);
	a[n] = std::min(a[n << 1], a[n << 1 | 1]);
}
long long min0[MAXN << 2], min1[MAXN << 2];
inline void reset(){
	min0[1] = INFLL;
	min1[1] = INFLL;
	tag[1] = 1;
}
inline void pushDown(int n){
	if(tag[n]){
		tag[n << 1] = tag[n << 1 | 1] = 1;
		min0[n << 1] = min0[n << 1 | 1] = INFLL;
		min1[n << 1] = min1[n << 1 | 1] = INFLL;
	}
	tag[n] = 0;
}
inline long long getDisByTime(int pos, int t){
	if(t <= 0)return INFLL;
	int L = std::max(1, pos - t + 1);
	int R = std::min(n, pos + t - 1);
	return
		std::min(
			query(min0, 1, 1, n, pos, R) - pre[pos],
			query(min1, 1, 1, n, L, pos) - suf[pos]
		);
}
inline long long GDBTL(int pos, int t){
	if(t <= 0)return INFLL;
	int L = std::max(1, pos - t + 1);
	return query(min1, 1, 1, n, L, pos) - suf[pos];
}
inline long long GDBTR(int pos, int t){
	if(t <= 0)return INFLL;
	int R = std::min(n, pos + t - 1);
	return query(min0, 1, 1, n, pos, R) - pre[pos];
}
int main(){
	n = $(), m = $();
	for(int i = 2;i <= n;i++)w[i] = $();
	for(int i = 1;i <= n;i++)pre[i] = pre[i - 1] + w[i];
	for(int i = n;i >= 1;i--)suf[i] = suf[i + 1] + w[i + 1];

	while(m--){
		k = $();
		for(int i = 1;i <= k;i++)edge[i].first = $(), edge[i].second = $();
		std::sort(edge + 1, edge + k + 1);
		ans = 0;
		reset();
		for(int i = 1;i <= k;i++){
			int x = edge[i].first, y = edge[i].second;
			//printf("MIN0 [%d] = %lld\n", x, y + pre[x]);
			modify(min0, 1, 1, n, x, y + pre[x]);
			//printf("MIN1 [%d] = %lld\n", x, y + suf[x]);
			modify(min1, 1, 1, n, x, y + suf[x]);
		}

		for(int i = 1;i <= k;i++){
			int x = edge[i].first, y = edge[i].second, tmp = 0;
			modify(min0, 1, 1, n, x, INFLL);
			modify(min1, 1, 1, n, x, INFLL);
			register int l = 1, r = x - 1, L = x, R = x;
			while(l <= r){
				int mid = (l + r) >> 1;
				int t = x - mid + 1;
				long long d0 = getDisByTime(mid, t);
				long long d1 = getDis(mid, x) + y;
				if(d1 < d0)L = mid, r = mid - 1;
				else l = mid + 1;
			}
			l = x + 1, r = n;
			while(l <= r){
				int mid = (l + r) >> 1;
				int t = mid - x + 1;
				long long d0 = getDisByTime(mid, t);
				long long d1 = getDis(mid, x) + y;
				if(d1 < d0)R = mid, l = mid + 1;
				else r = mid - 1;
				if(d1 == d0){
					long long d2 = getDisByTime(mid, t - 1);
					if(d2 != d0)tmp++;
				}
			}
			//printf("POS %d RANGE [%d - %d]\n", x, L, R);
			ans += (R - L + 1);
			ans += tmp;
			modify(min0, 1, 1, n, x, y + pre[x]);
			modify(min1, 1, 1, n, x, y + suf[x]);
		}
		printf("%lld\n", ans);
	}
	return 0;
}