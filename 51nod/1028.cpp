#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
const int N = 1 << 18;
const int P = (479 << 21) + 1;
const int G = 3;
const int NUM = 20;

inline long long fuck(long long a, long long p){
	long long ret = 1;
	while(p){
		if(p & 1)(ret *= a) %= P;
		(a *= a) %= P;
		p >>= 1;
	}
	return ret;
}

long long wn[NUM], a[N], b[N], n;

inline void cao(){
	for(int i = 0;i < NUM;i++){
		int t = 1 << i;
		wn[i] = fuck(G, (P - 1) / t);
	}
}
char buf[N];
inline void kao(){
	scanf("%s", buf); n = std::max(n, strlen(buf));
	for(int i = 0;buf[i];i++)a[i] = buf[i] ^ 48;
	std::reverse(a, a + strlen(buf));
	scanf("%s", buf); n = std::max(n, strlen(buf));
	for(int i = 0;buf[i];i++)b[i] = buf[i] ^ 48;
	std::reverse(b, b + strlen(buf));
	n = 1LL << (long long)ceil(log(2. * n) / log(2.));


int main(){
	
	return 0;
}
