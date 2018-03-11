#include<cstdio>
#include<cctype>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define BUF 1048576
char _1[BUF], *_3 = _1 + BUF;
inline char gc() { if (_3 == _1 + BUF)fread(_1, 1, BUF, stdin), _3 = _1; return *_3++; }
inline long long $(){
	register long long x = 0;register char ch = gc();
	while(!isdigit(ch))ch = gc();
	for(;isdigit(ch);ch = gc())x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
int sb[200000];
int main(){
	register int t = $();
	while(t--){
		register int n = $(), m = $();
		memset(sb, 0, sizeof(sb));
		register long long sum1 = 0, sum2 = 0, a[2], cnt = 0;
		for(int i = 0;i < n;i++)sb[$() % m]++;
		for(int i = 0;i < m;i++){
			sum1 += (long long)i * (sb[i] >> 1);
			(sum2 += (long long)i * sb[i]) %= m;
			if(sb[i] & 1)a[cnt++] = i;
			if(cnt > 2){puts("MAOMAMAO");goto fail;}
		}
		if(!(sum2 % m)){puts("MAOMAMAO");goto fail;}
		if(cnt == 2){
			if(!((sum1 + a[1]) % m) || !((sum1 + a[0]) % m))puts("MAMAMA");
			else puts("MAOMAMAO");
		}else if(cnt == 1){
			if(!((sum1 + a[0]) % m))puts("MAMAMA");
			else {
				if(!(sum1 % m))puts("MAOMAOMAO");
				else puts("MAOMAMAO");
			}
		}else puts("MAOMAMAO");
		fail:;
	}
}
