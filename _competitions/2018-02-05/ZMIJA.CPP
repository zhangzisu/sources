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
#define MAXN 1010
int n, m, ans, l[MAXN], r[MAXN];
int main(){
	freopen("ZMIJA.IN", "r", stdin);
	freopen("ZMIJA.OUT", "w", stdout);

	scanf("%d%d", &n, &m);
	for(int i = 1;i <= n;i++){
		l[i] = r[i] = -1;
		for(int j = 1;j <= m;j++){
			if(_() == 'J'){
				if(!~l[i])l[i] = j;
				r[i] = j;
			}
		}
		if(i == 1 && !~l[i] && !~r[i])i--, n--;
	}
	int pos = 1;
	for(int i = n;i;i--){
		int dr = (n - i) & 1;
		if(!~l[i] && !~r[i])ans++;
		else if(dr){
			ans += std::abs(pos - r[i]);
			ans += r[i] - l[i];
			pos = l[i];
			ans++;
		}else{
			ans += std::abs(pos - l[i]);
			ans += r[i] - l[i];
			pos = r[i];
			ans++;
		}
	}
	printf("%d\n", ans - 1);
	return 0;
}