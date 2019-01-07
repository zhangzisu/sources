#include<bits/stdc++.h>
#define N 400005
using namespace std;
int n,m,x,y,Q,K,kk,cnt,tim1,vall[N],id[N],ed[N],rt[N],top[N],dfn[N],head[N],heavyson[N],f[N/2][19],sz[N],dep[N],son[N],ls[N*24],rs[N*24],d[N*24];
struct Tree{int nxt,to;}e[N];
struct node{int x,y;}a[N];
inline bool cmp(node aa,node bb){return dfn[aa.x]<dfn[bb.x];}
inline void link(int x,int y){e[++kk].nxt=head[x];e[kk].to=y;head[x]=kk;}
void dfs1(int u,int fa){
	sz[u]=1;dfn[u]=++tim1;
	for (int i=1;i<=18;i++) f[u][i]=f[f[u][i-1]][i-1];
	for (int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if (v==fa) continue;
		f[v][0]=u;
		dep[v]=dep[u]+1;
		dfs1(v,u);
		if (!heavyson[u]||son[v]>son[heavyson[u]]) heavyson[u]=v;
		sz[u]+=sz[v];
	}
	ed[u]=tim1;
}
void insert(int &k,int last,int l,int r,int x){
	k=++cnt;ls[k]=ls[last];rs[k]=rs[last];
	d[k]=d[last]+1;
	if (l==r) return;
	int mid=(l+r)>>1;
	if (x<=mid) insert(ls[k],ls[last],l,mid,x);
	else insert(rs[k],rs[last],mid+1,r,x);
}
int query(int k,int k1,int l,int r,int x,int y){
	if (x<=l&&y>=r) return d[k]-d[k1];
	int mid=(l+r)>>1;
	if (y<=mid) return query(ls[k],ls[k1],l,mid,x,y);
	else if (x>mid) return query(rs[k],rs[k1],mid+1,r,x,y);
	else return query(ls[k],ls[k1],l,mid,x,mid)+query(rs[k],rs[k1],mid+1,r,mid+1,y);
}
int tim11=0;
void dfs2(int u,int first){
	top[u]=first;id[u]=++tim11;
	if (!heavyson[u]) return;
	dfs2(heavyson[u],first);
	for (int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if (v==f[u][0]||v==heavyson[u]) continue;
		dfs2(v,v);
	}
}
inline bool in(int x,int y){if(dfn[x]<=dfn[y]&&ed[x]>=dfn[y])return 1;return 0;}
inline int gt(int x,int y){
	if (in(heavyson[x],y)) return heavyson[x];
	while (f[top[y]][0]!=x) y=f[top[y]][0];
	return top[y];
}
inline bool check(int sta,int K,int up){
	int v=sta;int u=sta;
	for (int i=0;i<=18;i++){
		if ((1<<i)&up) u=f[u][i],up^=(1<<i);
		if (!up) break;
	}
	int ans=0;
	if (u==v) return vall[u]>=K;
	u=gt(u,v);
	if (dfn[u]!=1) ans+=query(rt[dfn[u]-1],rt[0],1,n,dfn[v],ed[v]);
	if (ed[u]!=n) ans=ans+query(rt[n],rt[ed[u]],1,n,dfn[v],ed[v]);
	return ans>=K;
}
inline int lca(int x,int y){
	while (top[x]!=top[y]){
		if (dep[top[x]]<dep[top[y]]) swap(x,y);
		x=f[top[x]][0];
	}if (dep[x]<dep[y]) return x;
	return y;
}
inline int read(){
	int f=1,w=0;char ch=getchar();
	for (;ch<'0'||ch>'9';ch=getchar()) if (ch=='-') f=-1;
	for (;ch>='0'&&ch<='9';ch=getchar()) w=w*10+ch-'0';
	return w*f;
}
void dfs3(int u,int fa){
	for (int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if (v==fa) continue;
		vall[u]+=vall[v];
	}
}
int main(){
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	n=read();m=read();
	for (int i=1;i<n;i++){
		x=read();y=read();
		link(x,y);link(y,x);
	}
	dep[1]=1;dfs1(1,-1);dfs2(1,1);
	for (int i=1;i<=m;i++){
		x=read();y=read();
		int LCA=lca(x,y);
		vall[x]++;vall[y]++;
		vall[LCA]--;
		if (f[LCA][0]) vall[f[LCA][0]]--;
		a[++cnt].x=x;a[cnt].y=y;
		if (x==y) continue;
		a[++cnt].x=y;a[cnt].y=x;
	}
	dfs3(1,-1);
	sort(a+1,a+cnt+1,cmp);
	int last=0;
	for (int i=1;i<=n;i++){
		rt[i]=rt[i-1];
		for (;last<cnt;last++){
			if (dfn[a[last+1].x]==i)
				insert(rt[i],rt[i],1,n,dfn[a[last+1].y]);
			else break;
		}
	}
	scanf("%d",&Q);
	while (Q--){
		x=read();K=read();
		int l=1;int r=dep[x]-1;
		while (l+1<r){
			int mid=(l+r)>>1;
			if (check(x,K,mid)) l=mid;
			else r=mid;
		}
		if (check(x,K,r)) printf("%d\n",r);
		else if (check(x,K,l)) printf("%d\n",l);
		else puts("0");
	}
	return 0;
}
