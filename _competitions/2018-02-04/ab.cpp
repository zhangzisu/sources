#include<cstdio>
#include<cctype>
inline long long $(){
	register long long x = 0, f = 0; register char ch = getchar();
	while(!isdigit(ch) && (ch ^ 45))ch = getchar();
	if(!(ch ^ 45))ch = getchar(), f = 1;
	for(;isdigit(ch);ch = getchar())x = (x << 1) + (x << 3) + (ch ^ 48);
	return f ? -x : x;
}
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<bitset>
#include<vector>
const int max = 10000010;
std::bitset<max> vis;
int prime[1000010], pnt;
inline void shai(){
	for(int i = 2;i < max;i++){
		if(!vis[i])prime[++pnt] = i;
		for(int j = 1;j <= pnt && i * prime[j] < max;j++){
			vis[i * prime[j]] = 1;
			if(!(i % prime[j]))break;
		}
	}
}
std::vector<std::pair<int, int> > V;
inline unsigned long long calc(int x){
	unsigned long long ans1 = 1, ans2 = 1, tmp, sum;
	for(int i = 0;i < (int)V.size();i++){
		tmp = 1; sum = 1;
		for(int j = 1;j <= V[i].second;j++){
			tmp *= V[i].first;
			sum += tmp * tmp;
		}
		ans1 *= (V[i].second + 1);
		ans2 *= sum;
	}
	return ans2 - ans1 * x;
}

inline void reslove(int x){
	for(int i = 1;1LL * prime[i] * prime[i] <= x;i++){
		if(x % prime[i])continue;
		int now = 0;
		while(!(x % prime[i]))now++, x /= prime[i];
		V.push_back(std::make_pair(prime[i], now));
	}
	if(x > 1)V.push_back(std::make_pair(x, 1));
}

int main(){
	shai();
	for(int t = $();t;t--){
		int q = $();
		reslove(q);
		printf("%llu\n", calc(q));
		V.clear();
	}
	return 0;
}