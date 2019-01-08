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
#include<map>
#define MAXN 100010
std::map<int, int> M1, M2;
int n = $(), k = $(), a[MAXN], b[MAXN], mid;
long long s1, s2, ans = 0x3F3F3F3F3F3F3F3F, c1, c2;
inline void add(int &x, std::map<int, int> &M, long long &c, long long &s){M[x]++;c++;s += x;}
inline void del(int &x, std::map<int, int> &M, long long &c, long long &s){if(!--M[x])M.erase(x);c--;s -= x;}
int main(){
	for(int i = 1;i <= n;i++)b[i] = a[i] = $();
	std::sort(b + 1, b + k + 1);
	for(int i = 1;i <= (k / 2);i++)M1[b[i]]++, s1 += b[i], c1++;
	for(int i = (k / 2) + 1;i <= k;i++)M2[b[i]]++, s2 += b[i], c2++;
	mid = M2.begin()->first;
	ans = std::min(ans, c1 * mid - s1 + s2 - c2 * mid);
	for(int i = k + 1;i <= n;i++){
		if(a[i] >= mid)add(a[i], M2, c2, s2);
		else add(a[i], M1, c1, s1);
		if(a[i - k] >= mid)del(a[i - k], M2, c2, s2);
		else del(a[i - k], M1, c1, s1);
		while(c1 < c2){
			int x = M2.begin()->first;add(x, M1, c1, s1);del(x, M2, c2, s2);mid = M2.begin()->first;
		}
		while(c1 > c2){
			int x = M1.rbegin()->first;add(x, M2, c2, s2);del(x, M1, c1, s1);mid = M2.begin()->first;
		}
		ans = std::min(ans, c1 * mid - s1 + s2 - c2 * mid);
	}
	printf("%lld\n", ans);
	return 0;
}
