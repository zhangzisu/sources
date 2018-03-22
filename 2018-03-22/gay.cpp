#include<bits/stdc++.h>
#define N 500005
using namespace std;
int n,x,y,a[N],maxx;
inline bool check(){
	int xx=(a[1]-1)/y;xx++;int yy=a[1]-(xx-1)*y;
	for (int i=2;i<=n;i++){
		int xxx=(a[i]-1)/y;xxx++;
		int yyy=a[i]-(xxx-1)*y;
		if (xxx!=xx&&yyy!=yy) return false;
		xx=xxx;yy=yyy;
	}return true;
}
int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	for (int i=2;i<=n;i++){
		if (a[i]==a[i-1]){puts("NO");return 0;}
		if (a[i]!=a[i-1]+1&&a[i]!=a[i-1]-1){
			int yy=abs(a[i]-a[i-1]);
			if (yy==y) continue;
			else if (!y) y=yy;
			else{puts("NO");return 0;}
		}
	}
	if (y==0){
		sort(a+1,a+n+1);
		puts("YES");
		printf("%d %d\n",1,a[n]+1);
		return 0;
	}
	if (!check()){puts("NO");return 0;}
	puts("YES");
	for (int i=1;i<=n;i++){
		int xx=(a[i]-1)/y;xx++;
		maxx=max(maxx,xx);
	}printf("%d %d\n",maxx,y);
	return 0;
}