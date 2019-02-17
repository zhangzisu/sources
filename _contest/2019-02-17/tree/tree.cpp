#include<iostream>
#include<cstring>
#include<cstdio>
#define next fdsjhkf

using namespace std;

const int mo=1e9+7;

int to[1001],next[1001],first[1001],n,k,f[301][301],e1=0;
int sz[301],jie[301],inv[301],g[301];
int tmp1[305],tmp2[305],tmp3[305];

void insert(int o,int p)
{
	to[e1]=p;next[e1]=first[o];first[o]=e1++;
}

int mi(int o,int p)
{
	int u=1;
	while(p>0)
	{
		if(p&1) u=1ll*u*o%mo;
		o=1ll*o*o%mo;
		p>>=1;
	}
	return u;
}

int C(int o,int p) 
{
	if(o<0||p<0||o<p) return 0;
	return 1ll*jie[o]*inv[p]%mo*inv[o-p]%mo;
}

void dfs(int o,int p)
{
	sz[o]=1;f[o][0]=1;
	for(int v=first[o];v!=-1;v=next[v])
		if(to[v]!=p)
		{
			dfs(to[v],o);
			for(int i=0;i<=sz[o];i++)
				for(int j=0;j<=sz[to[v]];j++)
					for(int s=0;s<=min(i,j);s++)
					{
						int yu=1ll*f[to[v]][j]*f[o][i]%mo*C(i,s)%mo*C(j,s)%mo*jie[s]%mo;
						if(i+j-2*s>=0) g[i+j-2*s]=(g[i+j-2*s]+yu)%mo;
					}
			sz[o]+=sz[to[v]];
			for(int i=0;i<=sz[o];i++) f[o][i]=g[i];
			for(int i=0;i<=k;i++) g[i]=0;
		}
	for(int i=0;i<=k+1;i++) tmp1[i]=tmp2[i]=tmp3[i]=0;
	for(int i=0;i<=k;i++) tmp1[i]=(tmp1[i]+f[o][i]);
	for(int i=0;i<k;i++) tmp2[i+1]=(tmp2[i+1]+f[o][i]);
	for(int i=1;i<=k+1;i++) tmp3[i-1]=(tmp3[i-1]+1ll*f[o][i]*i%mo);
	for(int i=0;i<=k;i++) 
		f[o][i]=((tmp1[i]+tmp2[i])%mo+tmp3[i])%mo;
	for(int i=k+1;i<=sz[o];i++) f[o][i]=0;
}

int main()
{
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	memset(first,-1,sizeof(first));
	scanf("%d%d",&n,&k);
	jie[0]=inv[0]=1;
	for(int i=1;i<=300;i++) jie[i]=1ll*jie[i-1]*i%mo;
	inv[300]=mi(jie[300],mo-2);
	for(int i=299;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mo;
	for(int i=1;i<n;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		insert(x,y);
		insert(y,x);
	}
	dfs(1,0);
	cout<<f[1][0]<<endl;
	fclose(stdin);
	fclose(stdout);
	return 0;
}
