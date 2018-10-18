#include<bits/stdc++.h>

using namespace std;

#define N 300000

int n,m,x,y,z,dep[N],dep2[N],par[N][20],len[N][20],fa[N][20],tot,head[N],ans[N];
struct edge{int v,l,nxt;}e[N];
struct node{
	int x,y,z,i;
	bool operator < (const node &p) const{
		return z<p.z;
	}
}q[N];
void add(int x,int y,int z){
	e[++tot].v=y; e[tot].l=z; e[tot].nxt=head[x]; head[x]=tot;
}

int lca(int x,int y){
	if (dep[x]>dep[y])
		for (int i=18;i>=0;--i)
			if (dep[par[x][i]]>=dep[y]) x=par[x][i];
	if (dep[x]<dep[y])
		for (int i=18;i>=0;--i)
			if (dep[par[y][i]]>=dep[x]) y=par[y][i];
	for (int i=18;i>=0;--i)
		if (par[x][i]!=par[y][i]){
			x=par[x][i]; y=par[y][i];
		}
	return x==y?x:par[x][0];
}

void dfs(int u){
	for (int i=1;i<=18;++i){
		par[u][i]=par[par[u][i-1]][i-1];
		len[u][i]=len[u][i-1]+len[par[u][i-1]][i-1];
	}
	for (int i=head[u],v;i;i=e[i].nxt)
		if ((v=e[i].v)!=par[u][0]){
			par[v][0]=u; len[v][0]=e[i].l;
			dep[v]=dep[u]+1; dep2[v]=dep2[u]+e[i].l;
			dfs(v);
		}
}

void build(int u,int k){
	int o=u,l=k;
	for (int i=18;i>=0;--i)
		if (len[o][i]<=l){
			l-=len[o][i];
			o=par[o][i];
		}
	fa[u][0]=o;
	for (int i=1;i<=18;++i)
		fa[u][i]=fa[fa[u][i-1]][i-1];
	for (int i=head[u],v;i;i=e[i].nxt)
		if ((v=e[i].v)!=par[u][0]) build(v,k);
}

int main(){
	scanf("%d",&n);
	for (int i=1;i<n;++i){
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z); add(y,x,z);
	}
	scanf("%d",&m);
	for (int i=1;i<=m;++i){
		scanf("%d%d%d",&q[i].x,&q[i].y,&q[i].z);
		q[i].i=i;
	}
	dep[1]=dep2[1]=1; dfs(1);
	sort(q+1,q+m+1);
	for (int i=1;i<=m;++i){
		x=q[i].x,y=q[i].y,z=q[i].z;
		if (q[i].z>100){
			int o=lca(x,y),tmp=0;
			while (dep2[x]-dep2[o]>z){
				int l=z;
				for (int i=18;i>=0;--i)
					if (len[x][i]<=l){
						l-=len[x][i];
						x=par[x][i];
					}
				++tmp;
			}
			while (dep2[y]-dep2[o]>z){
				int l=z;
				for (int i=18;i>=0;--i)
					if (len[y][i]<=l){
						l-=len[y][i];
						y=par[y][i];
					}
				++tmp;
			}
			int d=dep2[x]-dep2[o]+dep2[y]-dep2[o];
			if (d) ++tmp;
			if (d>z) ++tmp;
			ans[q[i].i]=tmp;
		}
		else{
			if (q[i].z!=q[i-1].z) build(1,q[i].z);
			int o=lca(x,y),tmp=0;
			for (int i=18;i>=0;--i)
				if (dep[fa[x][i]]>dep[o]){
					x=fa[x][i];
					tmp+=1<<i;
				}
			for (int i=18;i>=0;--i)
				if (dep[fa[y][i]]>dep[o]){
					y=fa[y][i];
					tmp+=1<<i;
				}
			int d=dep2[x]-dep2[o]+dep2[y]-dep2[o];
			if (d) ++tmp;
			if (d>z) ++tmp;
			ans[q[i].i]=tmp;
		}
	}
	for (int i=1;i<=m;++i) printf("%d\n",ans[i]);
	
	return 0;
}