#include<cstdio>
#include<cctype>
#include<cstdlib>
#include<cstring>
inline int $(){
	register int x = 0;register char ch = getchar();
	while(!isdigit(ch))ch = getchar();
	for(;isdigit(ch);ch = getchar())x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
#define MAXN 100010
#include<set>
#include<map>
#include<queue>
std::set<int> next[MAXN];
std::map<std::pair<int, int>, int> M;
std::queue<std::pair<int, int> > Q;
int n = $();
int p[MAXN];
inline int find(int x){return x == p[x] ? x : p[x] = find(p[x]);}
int main(){
	for(int i = 1;i <= n;i++)p[i] = i;
	for(int i = 2;(i >> 1) < n;i++){
		int x = $(), y = $();
		if(x > y)std::swap(x, y);
		next[x].insert(y);next[y].insert(x);
		if(++M[std::make_pair(x, y)] == 2)Q.push(std::make_pair(x, y));
	}
	for(int i = 1;i < n;i++){
		register int x = 0, y = 0;
		while(x == y){
			if(Q.empty())return puts("NO"), 0;
			x = find(Q.front().first), y = find(Q.front().second);
			Q.pop();
		}
		if(next[x].size() > next[y].size())std::swap(x, y);
		p[x] = y;
		for(auto i : next[x]){
			if(find(i) == y)continue;
			next[y].insert(find(i));
			std::pair<int, int> add = std::make_pair(std::min(find(i), y), std::max(find(i), y));
			if(++M[add] == 2)Q.push(add);
		}
		next[y].erase(x);
	}
	puts("YES");
	return 0;
}
