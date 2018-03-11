#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<map>
std::map<long long, int> M;
#define MAXN 100010
#define SRTN 315
long long p, a[MAXN], ans[MAXN], now = 0;
int s[MAXN], pos[MAXN], cnt[MAXN], n, m;
struct Query{
	int l, r, p;
	inline bool friend operator < (const Query &a, const Query &b){
		if(a.l / SRTN == b.l / SRTN)return a.r < b.r;
		else return a.l < b.l;
	}
}q[MAXN];
inline long long fuck(long long x, long long d, long long p){
    long long ret = 1;
    while(d){
        if(d & 1)ret = ret * x % p;
        x = x * x % p;
        d >>= 1;
    }
    return ret;
}
char buf[MAXN];
inline long long calc(int x){ return cnt[pos[x]] * (cnt[pos[x]] - 1); }
int main(){
    scanf("%lld%s%d", &p, buf, &m);
	n = strlen(buf);
	for(int i = 1;i <= n;i++)s[i] = buf[i - 1] ^ 48;
	if(p == 2 || p == 5){
		for(int i = 1;i <= n;i++)ans[i] = ans[i - 1] + (s[i] % p == 0);
        for(int i = 1;i <= n;i++)pos[i] = pos[i - 1] + (s[i] % p == 0) * i;
		while(m--){
			int l, r; scanf("%d%d", &l, &r); printf("%lld\n", pos[r] - pos[l - 1] - 1LL * (ans[r] - ans[l - 1]) * (l - 1));
		}
		return 0;
	}
	long long tmp = 1; int all = 0;
	for(int i = n;i >= 1;i--){
        (tmp *= 10) %= p;
        a[i] = (a[i + 1] + tmp * s[i] % p) % p;
        if(!M.count(a[i]))M[a[i]] = ++all;
    }

	for(int i = 1;i <= n + 1;i++)pos[i] = M[a[i]];

	for(int i = 1;i <= m;i++)scanf("%d%d", &q[i].l, &q[i].r), q[i].p = i, q[i].r++;
	std::sort(q + 1, q + m + 1);
	int l = 1, r = 0;
	for(int i = 1;i <= m;i++){
		for(;r > q[i].r;r--){ now -= calc(r);     cnt[pos[r]]--;     now += calc(r);    }
		for(;r < q[i].r;r++){ now -= calc(r + 1); cnt[pos[r + 1]]++; now += calc(r + 1);}
		for(;l > q[i].l;l--){ now -= calc(l - 1); cnt[pos[l - 1]]++; now += calc(l - 1);}
		for(;l < q[i].l;l++){ now -= calc(l);     cnt[pos[l]]--;     now += calc(l);    }
		ans[q[i].p] = now >> 1;
	}
	for(int i = 1;i <= m;i++)printf("%lld\n", ans[i]);
    return 0;
}
