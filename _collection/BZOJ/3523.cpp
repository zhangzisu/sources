#include<cstdio>
#include<cctype>
#include<cstdlib>
inline int $() {
	register int x = 0, f = 0; register char ch = getchar();
	while (!isdigit(ch) && (ch ^ 45))ch = getchar();
	if (!(ch ^ 45))f = 1, ch = getchar();
	for (; isdigit(ch); ch = getchar())x = (x << 1) + (x << 3) + (ch ^ 48);
	return f ? -x : x;
}
#include<algorithm>
#include<queue>
#define MAXN 1000010
int n = $(), s = $(), e = $(), m, a[MAXN], ans[MAXN];
struct node{
	int x, y;
	inline node(int x = 0, int y = 0):x(x), y(y){}
	inline friend bool operator < (const node &a, const node &b){
		return a.y == b.y ? !(a.x == e) : a.y < b.y;
	}
};
std::priority_queue<node> Q;
int main(){
	for(int i = 1;i <= n;i++){
		node now = node(i, $());
		if(now.x == s)now.y--;
		if(now.x == e)now.y--;
		if(now.y < 0)return puts("0"), 0;
		m += now.y;
		if(now.y)Q.push(now);
	}
	ans[0] = s;ans[m + 1] = e;
	for(int i = 1;i <= m;i++){
		node now = Q.top();Q.pop();
		if(now.x != ans[i - 1]){
			ans[i] = now.x;now.y--;
			if(now.y)Q.push(now);
		}else{
			if(Q.empty())return puts("0"), 0;
			node oth = Q.top();Q.pop();
			ans[i] = oth.x;oth.y--;
			if(oth.y)Q.push(oth);
			Q.push(now);
		}
	}
	if(ans[m] == ans[m + 1])return puts("0"), 0;
	for(int i = 0;i <= m + 1;i++)printf("%d ", ans[i]);
	puts("");
	return 0;
}
