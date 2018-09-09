#include<bits/stdc++.h>
#define pi pair<int,int>
#define mk make_pair
#define N 500005
#define int long long
using namespace std;
int T,n,Q,l,r,cnt,a[N],rt[N],ls[N*64],rs[N*64],d[N*64],ad[N*64];
vector<pi>P[N],G;
inline bool pd(int x){return (int)sqrt(x)*(int)sqrt(x)==x;}
void update(int &k,int last,int l,int r,int x,int y,int z){
	k=++cnt;ls[k]=ls[last];rs[k]=rs[last];
	d[k]=d[last]+(y-x+1)*z;ad[k]=ad[last];
	if (x<=l&&y>=r){
		ad[k]+=z;
		return;
	}
	int mid=(l+r)>>1;
	if (y<=mid) update(ls[k],ls[last],l,mid,x,y,z);
	else if (x>mid) update(rs[k],rs[last],mid+1,r,x,y,z);
	else update(ls[k],ls[last],l,mid,x,mid,z),update(rs[k],rs[last],mid+1,r,mid+1,y,z);
}
int query(int k,int l,int r,int x,int y,int add){
	if (x<=l&&y>=r) return d[k]+add*(r-l+1);
	int mid=(l+r)>>1;
	if (y<=mid) return query(ls[k],l,mid,x,y,add+ad[k]);
	else if (x>mid) return query(rs[k],mid+1,r,x,y,add+ad[k]);
	else return query(ls[k],l,mid,x,mid,add+ad[k])+query(rs[k],mid+1,r,mid+1,y,add+ad[k]);
}
signed main(){
	scanf("%lld",&T);
	while (T--){
		cnt=0;memset(rt,0,sizeof(rt));
		scanf("%lld%lld",&n,&Q);G.clear();
		for (int i=1;i<=n;i++) P[i].clear(),scanf("%lld",&a[i]);
		for (int i=1;i<=n;i++){
			vector<pi>tmp;tmp.clear();
			for (int j=0;j<(int)G.size();j++) tmp.push_back(mk(G[j].first&a[i],G[j].second));
			tmp.push_back(mk(a[i],1));
			int last=0;G.clear();
			for (int j=0;j<(int)tmp.size();j=last+1){
				last=j;
				G.push_back(mk(tmp[j].first,tmp[j].second));
				int now=G.size();now--;
				for (;last<(int)tmp.size();last++){
					if (last+1==(int)tmp.size()||tmp[last].first!=tmp[last+1].first) break;
					G[now].second+=tmp[last+1].second;
				}
			}
			P[i]=G;
		}
		for (int i=1;i<=n;i++){
			int sz=P[i].size();sz--;
			int now=i;
			rt[i]=rt[i-1];
			for (int j=sz;~j;j--){
				if (pd(P[i][j].first)){
					update(rt[i],rt[i],1,n,now-P[i][j].second+1,now,1);
                    printf("ADDED 1 to RANGE %d-%d\n", now-P[i][j].second+1,now);
                }
				now-=P[i][j].second;
			}
		}
		while (Q--){
			scanf("%lld%lld",&l,&r);
			printf("%lld\n",query(rt[r],1,n,l,r,0));
		}
	}
	return 0;
}
