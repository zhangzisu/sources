#include<cstdio>
#include<cctype>
inline int $(){
	register int x = 0; register char ch = getchar();
	while(!isdigit(ch))ch = getchar();
	for(;isdigit(ch);ch = getchar())x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
inline char _(){
	register char ch = getchar();
	while(!isalpha(ch) && (ch ^ '.'))ch = getchar();
	return ch;
}
#include<algorithm>
#include<set>
#define MAXN 510
std::set<int> S[510];
std::set<int>::iterator it;
int main(){
	//freopen("JABUKE.IN", "r", stdin);
	//freopen("JABUKE.OUT", "w", stdout);

	register int n = $(), m = $();
	for(register int i = 1;i <= n;i++)
		for(register int j = 1;j <= m;j++)
			if(_() == 'x')S[i].insert(j);
	for(int G = $();G;G--){
		int x = $(), y = $(), dltX, ans = 0x3F3F3F3F;
		if(!S[x].empty()){
			it = S[x].lower_bound(y);
			dltX = 0x3F3F3F3F;
			if(it != S[x].end())dltX = std::min(dltX, *it - y);
			if(it != S[x].begin())dltX = std::min(dltX, y - *--it);
			ans = dltX * dltX;
		}
		for(register int i = x - 1;i;i--){
			if((x - i) * (x - i) >= ans)break;
			if(S[i].empty())continue;
			it = S[i].lower_bound(y); dltX = 0x3F3F3F3F;
			if(it != S[i].end())dltX = std::min(dltX, *it - y);
			if(it != S[i].begin())dltX = std::min(dltX, y - *--it);
			ans = std::min(ans, dltX * dltX + (i - x) * (i - x));
		}
		for(register int i = x + 1;i <= n;i++){
			if((x - i) * (x - i) >= ans)break;
			if(S[i].empty())continue;
			it = S[i].lower_bound(y); dltX = 0x3F3F3F3F;
			if(it != S[i].end())dltX = std::min(dltX, *it - y);
			if(it != S[i].begin())dltX = std::min(dltX, y - *--it);
			ans = std::min(ans, dltX * dltX + (i - x) * (i - x));
		}
		printf("%d\n", ans);
		S[x].insert(y);
	}
	return 0;
}