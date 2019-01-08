#include<algorithm>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#define MAXN 1000010
int t,k,n,s[MAXN],a[MAXN],b[MAXN],map[26],vis[26];
char buf[MAXN];
bool dfs(int p,int l,int r){
	if((l&&r)||p>n)return 1;
	if(~map[s[p]])return(l||map[s[p]]>=a[p])&&(r||map[s[p]]<=b[p])&&dfs(p+1,l||map[s[p]]>a[p],r||map[s[p]]<b[p]);
	for(int i=0;i<k;i++){
		if(!vis[i]&&(l||i>=a[p])&&(r||i<=b[p])){
			vis[map[s[p]]=i]=1;
			if(dfs(p+1,l||i>a[p],r||i<b[p]))return 1;
			vis[i]=0,map[s[p]]=-1;
		}
	}
	return 0;
}
inline void output(){
	puts("YES");
	for(int i=0;i<k;i++){
		if(~map[i])continue;
		for(int j=0;j<k;j++){
			if(vis[j])continue;
			vis[map[i]=j]=1;
			break;
		}
	}
	for(int i=0;i<k;i++)putchar(map[i]+'a');
	putchar(10);
}
int main(){
	for(scanf("%d",&t);t;t--){
		scanf("%d",&k);
		scanf("%s",buf+1);
		n=strlen(buf+1);
		for(int i=1;i<=n;i++)s[i]=buf[i]-'a';
		scanf("%s",buf+1);
		for(int i=1;i<=n;i++)a[i]=buf[i]-'a';
		scanf("%s",buf+1);
		for(int i=1;i<=n;i++)b[i]=buf[i]-'a';
		memset(map,-1,sizeof(map));
		memset(vis,0,sizeof(vis));
		if(dfs(1,0,0)){
			output();
		}else{
			puts("NO");
		}
	}
	return 0;
}