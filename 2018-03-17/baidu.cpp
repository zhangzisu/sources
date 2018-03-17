#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define MAXN 100010
#define DDDD 19
#define _ long long
_ n, k, K;
_ w[MAXN], val[1 << 18], tmp[1 << 18];

inline _ ora(_ x, _ y){return x;}
inline _ orb(_ x, _ y){return x + y;}
inline _ oria(_ x, _ y){return x;}
inline _ orib(_ x, _ y){return y - x;}

inline _ anda(_ x, _ y){return x + y;}
inline _ andb(_ x, _ y){return y;}
inline _ andia(_ x, _ y){return x - y;}
inline _ andib(_ x, _ y){return y;}

inline _ xora(_ x, _ y){return x + y;}
inline _ xorb(_ x, _ y){return x - y;}
inline _ xoria(_ x, _ y){return (x + y) / 2;}
inline _ xorib(_ x, _ y){return (x - y) / 2;}

inline void FWT(_ *a, _ n, _ (*f)(_, _), _ (*g)(_, _)){
	for(_ k = 1;k < n;k <<= 1){
		for(_ i = 0;i < n;i += (k << 1)){
			for(_ j = 0;j < k;j++){
				_ x = a[i + j], y = a[i + j + k];
				a[i + j] = f(x, y);
				a[i + j + k] = g(x, y);
			}
		}
	}
}

int main(){
#ifndef DEBUG
	freopen("baidu.in" , "r", stdin );
	freopen("baidu.out", "w", stdout);
#endif
	_ a1, a2, a3, a4;
	scanf("%lld%lld%lld%lld", &a1, &a2, &a3, &a4);
	_ fingerprint = (a1<<3)|(a2<<2)|(a3<<1)|(a4);
	scanf("%lld%lld", &n, &k); K = (1 << k) - 1;
	for(_ i = 1;i <= n;i++) scanf("%lld", &w[i]), w[i] &= K;

	//0000 all checked
	if(fingerprint == 0x0 || fingerprint == 0xF){
#ifdef DEBUG
		//puts("Type : 0000 all");
#endif
		for(_ i = 0;i < (1 << k);i++){
			if(fingerprint == 0x0)printf("%lld\n", i == 0 ? n * (n - 1) : 0);
			if(fingerprint == 0xF)printf("%lld\n", i == K ? n * (n - 1) : 0);
		}
		return 0;
	}

	//0001 and checked
	if(fingerprint == 0x1 || fingerprint == 0x8){
#ifdef DEBUG
		//puts("Type : 0001 1000 and");
#endif
		if(fingerprint == 0x8)for(_ i = 1;i <= n;i++)w[i] = K ^ w[i];
		for(_ i = 1;i <= n;i++)val[w[i]]++;
		FWT(val, 1 << k, &anda, &andb);
		for(_ i = 0;i < (1 << k);i++)val[i] *= val[i];
		FWT(val, 1 << k, &andia, &andib);
		for(_ i = 1;i <= n;i++)val[w[i] & w[i]]--;
		for(_ i = 0;i < (1 << k);i++)printf("%lld\n", val[i]);
		return 0;
	}

	//0111 or checked
	if(fingerprint == 0x7 || fingerprint == 0xE){
#ifdef DEBUG
		//puts("Type : 0111 simple or");
#endif
		if(fingerprint == 0xE)for(_ i = 1;i <= n;i++)w[i] = K ^ w[i];
		for(_ i = 1;i <= n;i++)val[w[i]]++;
		FWT(val, 1 << k, &ora, &orb);
		for(_ i = 0;i < (1 << k);i++)val[i] *= val[i];
		FWT(val, 1 << k, &oria, &orib);
		for(_ i = 1;i <= n;i++)val[w[i] | w[i]]--;
		for(_ i = 0;i < (1 << k);i++)printf("%lld\n", val[i]);
		return 0;
	}
	
	//0110 xor checked
	if(fingerprint == 0x6){
#ifdef DEBUG
		//puts("Type : 0110 simple xor");
#endif
		for(_ i = 1;i <= n;i++)val[w[i]]++;
		FWT(val, 1 << k, &xora, &xorb);
		for(_ i = 0;i < (1 << k);i++)val[i] *= val[i];
		FWT(val, 1 << k, &xoria, &xorib);
		for(_ i = 1;i <= n;i++)val[w[i] ^ w[i]]--;
		for(_ i = 0;i < (1 << k);i++)printf("%lld\n", val[i]);
		return 0;
	}
	//1001 reverse xor
	if(fingerprint == 0x9){
#ifdef DEBUG
		//puts("Type : 1001 reverse xor");
#endif
		for(_ i = 1;i <= n;i++)val[w[i]]++;
		memset(tmp, 0, sizeof(tmp));
		for(_ i = 1;i <= n;i++)tmp[K ^ w[i]]++;
		FWT(val, 1 << k, &xora, &xorb);
		FWT(tmp, 1 << k, &xora, &xorb);
		for(_ i = 0;i < (1 << k);i++)val[i] *= tmp[i];
		FWT(val, 1 << k, &xoria, &xorib);
		for(_ i = 1;i <= n;i++)val[w[i] ^ (K ^ w[i])]--;
		for(_ i = 0;i < (1 << k);i++)printf("%lld\n", val[i]);
		return 0;
	}
	
	//x checked
	if(fingerprint == 0x3 || fingerprint == 0x5 || fingerprint == 0xA || fingerprint == 0xC){
#ifdef DEBUG
		//puts("Type : x");
#endif
		memset(tmp, 0, sizeof(tmp));
		for(_ i = 1;i <= n;i++){
			if(fingerprint == 0x3 || fingerprint == 0x5)tmp[w[i]] += n - 1;
			if(fingerprint == 0xA || fingerprint == 0xC)tmp[K ^ w[i]] += n - 1;
		}
		for(_ i = 0;i < (1 << k);i++)printf("%lld\n", tmp[i]);
		return 0;
	}

	// 0010 or 0100
	if(fingerprint == 0x2 || fingerprint == 0x4){
#ifdef DEBUG
		//puts("Type : prism#0");
#endif
		for(_ i = 1;i <= n;i++)val[K ^ w[i]]++;
		for(_ i = 1;i <= n;i++)tmp[w[i]]++;
		FWT(val, 1 << k, &anda, &andb);
		FWT(tmp, 1 << k, &anda, &andb);
		for(_ i = 0;i < (1 << k);i++)val[i] *= tmp[i];
		FWT(val, 1 << k, &andia, &andib);
		for(_ i = 1;i <= n;i++)val[(K ^ w[i]) & w[i]]--;
		for(_ i = 0;i < (1 << k);i++)printf("%lld\n", val[i]);
		return 0;
	}

	// 1011 or 1101
	if(fingerprint == 0xB || fingerprint == 0xD){
#ifdef DEBUG
		//puts("Type : prism#1");
#endif
		for(_ i = 1;i <= n;i++)val[K ^ w[i]]++;
		for(_ i = 1;i <= n;i++)tmp[w[i]]++;
		FWT(val, 1 << k, &ora, &orb);
		FWT(tmp, 1 << k, &ora, &orb);
		for(_ i = 0;i < (1 << k);i++)val[i] *= tmp[i];
		FWT(val, 1 << k, &oria, &orib);
		for(_ i = 1;i <= n;i++)val[(K ^ w[i]) | w[i]]--;
		for(_ i = 0;i < (1 << k);i++)printf("%lld\n", val[i]);
		return 0;
	}
#ifndef DEBUG
	fclose(stdin);
	fclose(stdout);
#endif
}
