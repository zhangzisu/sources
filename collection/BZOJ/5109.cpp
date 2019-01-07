#include<cstdio>
#include<cctype>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define BUF 1048576
char _1[BUF], *_3 = _1 + BUF;
inline char gc() { if (_3 == _1 + BUF)fread(_1, 1, BUF, stdin), _3 = _1; return *_3++; }
inline int $(){
	register int x = 0;register char ch = gc();
	while(!isdigit(ch))ch = gc();
	for(;isdigit(ch);ch = gc())x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
#define MAXN 500010
#include<set>
int n = $(), a[MAXN], c[MAXN << 1], *b = c + MAXN;
std::set<int> S;
long long ans = 0;
void slove(int l, int r){
	if(l == r){return;}
	int mid = (l + r) >> 1;
	slove(l, mid);slove(mid + 1, r);
	S.clear();
	for(register int i = mid;i >= l;i--)b[a[i]] = 0;
	for(register int i = mid;i >= l;i--)if((++b[a[i]] << 1) > (mid - i + 1))S.insert(a[i]);
	for(register int i = mid + 1;i <= r;i++)b[a[i]] = 0;
	for(register int i = mid + 1;i <= r;i++)if((++b[a[i]] << 1) > (i - mid))S.insert(a[i]);
	for(register int i = l;i <= r;i++)b[a[i]] = 0;
	for(register int x : S){
		register int min = 0x3F3F3F3F, max = -min, s = 0;
		for(register int i = mid;i >= l;i--)b[s += a[i] == x ? 1 : -1]++, min = std::min(min, s), max = std::max(max, s);
		for(register int i = max - 1;i >= min;i--)b[i] += b[i + 1];
		s = 0;
		for(register int i = mid + 1;i <= r;i++){
			s += a[i] == x ? 1 : -1;
			ans += b[1 - s < min ? min : 1 - s];
		}
		memset(b + min, 0, sizeof(int) * (max - min + 1));
	}
}
int main(){
	for(int i = 0;i <= n;i++)a[i] = $();
	slove(1, n);
	printf("%lld\n", ans + n);
	return 0;
}
