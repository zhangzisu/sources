#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define MAXN 12
int n, m;
long long f[2][1 << MAXN];
int main(){
	while(~scanf("%d%d", &n, &m) && n && m){
		if(n & 1 && m & 1){puts("0");continue;}
		int pre = 0, now = 1;
		memset(f[now], 0, sizeof(f[now]));
		f[now][0] = 1;
		for(int i = 0;i < n;i++){
			for(int j = 0;j < m;j++){
				std::swap(pre, now);
				memset(f[now], 0, sizeof(f[now]));
				const int u = 1 << j, l = 1 << (j + 1);
				for(int s = 0;s < (1 << (m + 1));s++){
					int k = s;
					if(!j){
						if((k >> m) & 1)continue;
						k <<= 1;
					}
					if((u & k) && (l & k))continue;
					else if(u & k){
						f[now][k ^ u] += f[pre][s];
					}else if(l & k){
						f[now][k ^ l] += f[pre][s];
					}else{
						f[now][k ^ u] += f[pre][s];
						f[now][k ^ l] += f[pre][s];
					}
				}
			}
		}
		printf("%lld\n", f[now][0]);
	}
}
