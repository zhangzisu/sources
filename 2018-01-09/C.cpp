#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
#include<vector>
int n, g1, g2, V;
long long ans = 0, pfx[MAXN], sum[MAXN];
std::vector<std::pair<int, int> > V1, V2, ret;
inline int sb(const std::pair<int, int>&a, const std::pair<int, int>&b){
	return a.second < b.second;
}
int main()<%
	scanf("%d%d", &n, &V);
	for(int i = 1;i <= n;i++){
		int w, v;
		scanf("%d%d", &w, &v);
		if(w == 1)V1.push_back(std::make_pair(v, i));
		else V2.push_back(std::make_pair(v, i));
	}
	std::sort(V1.begin(), V1.end());
	std::sort(V2.begin(), V2.end());
	std::reverse(V1.begin(), V1.end());
	std::reverse(V2.begin(), V2.end());
	for(int i = 0;i < (int)V1.size();i++)pfx[i] = (i ? pfx[i - 1] : 0) + V1[i].first;
	for(int i = 0;i < (int)V2.size();i++)sum[i] = (i ? sum[i - 1] : 0) + V2[i].first;
	ans = pfx[std::min((int)V1.size() - 1, V - 1)];
	g1 = std::min((int)V1.size() - 1, V - 1);g2 = -1;
	for(int i = 0;i < (int)V2.size();i++){
		int ret = V - ((i + 1) << 1);
		if(ret < 0)break;
		long long tmp = pfx[std::min(ret - 1, (int)V1.size() - 1)];
		if(tmp + sum[i] > ans){
			g2 = i;
			g1 = std::min(ret - 1, (int)V1.size() - 1);
			ans = tmp + sum[i];
		}
	}
	for(int i = 0;i <= g1;i++)ret.push_back(V1[i]);
	for(int i = 0;i <= g2;i++)ret.push_back(V2[i]);
	printf("%lld\n", ans);
	std::sort(ret.begin(), ret.end(), sb);
	for(int i = 0;i < (int)ret.size();i++)printf("%d ", ret[i].second);
	puts("");
	return 0;
%>
