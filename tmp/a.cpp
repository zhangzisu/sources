#include<bits/stdc++.h>
#define N 20000005
#define inf 1000000000
#define lim 2000000000
using namespace std; 
struct segment_beats{
	int cnt,rt;//,ls[N],rs[N];
	struct node{
		int a,b,c,d;
		int l,r;
		inline node(){a=c=0;b=d=-inf;}
	}d[N];
	inline segment_beats(){cnt=0;rt=0;memset(d,0,sizeof(d));}
	inline void pushdown(int k){
		//if (!ls[k]) ls[k]=++cnt,d[cnt].a=0,d[cnt].b=-inf,d[cnt].c=0,d[cnt].d=-inf;
		//if (!rs[k]) rs[k]=++cnt,d[cnt].a=0,d[cnt].b=-inf,d[cnt].c=0,d[cnt].d=-inf;
		node &K=d[k];
		if (!K.l) K.l=++cnt;
		if (!K.r) K.r=++cnt;
		//node &lson=d[ls[k]];
		node &lson=d[K.l];
		lson.c=max(lson.c,K.c+lson.a);
		lson.d=max(K.d,max(lson.d,lson.b+K.c));
		lson.a=max(-inf,K.a+lson.a);
		lson.b=max(lson.b+K.a,K.b);
		//node &rson=d[rs[k]];
		node &rson=d[K.r];
		rson.c=max(rson.c,K.c+rson.a);
		rson.d=max(K.d,max(rson.d,rson.b+K.c));
		rson.a=max(-inf,K.a+rson.a);
		rson.b=max(rson.b+K.a,K.b);
		K.a=K.c=0;K.b=K.d=-inf;
	}
	void update(int &k,int l,int r,int x,int y,int a,int b){
		if (!k) k=++cnt,d[cnt].a=0,d[cnt].b=-inf,d[cnt].c=0,d[cnt].d=-inf;
		if (x<=l&&y>=r){
			d[k].a=max(-inf,d[k].a+a);
			d[k].b=max(d[k].b+a,b);
			d[k].c=max(d[k].a,d[k].c);
			d[k].d=max(d[k].b,d[k].d);
			return;
		}
		int mid=(1ll*l+1ll*r)/2ll;
		pushdown(k);
		//if (x<=mid) update(ls[k],l,mid,x,y,a,b);
		//if (y>mid) update(rs[k],mid+1,r,x,y,a,b);
		if (x<=mid) update(d[k].l,l,mid,x,y,a,b);
		if (y>mid) update(d[k].r,mid+1,r,x,y,a,b);
	}
	inline int query(int k,int l,int r,int x){
		while (l<r){
 			if (!k) return 0;
 			int mid=(1ll*l+1ll*r)/2ll;
 			pushdown(k);
			//if (x<=mid) k=ls[k],r=mid;
			//else l=mid+1,k=rs[k];
			if (x<=mid) k=d[k].l,r=mid;
			else l=mid+1,k=d[k].r;
		}
		if (!k) return 0;
		return max(d[k].c,d[k].d);
	}
}t1,t2,t3,t4;
int Q,K,opt,lastans,x,y;
signed main(){
	scanf("%d%d",&Q,&K);
	while (Q--){
		scanf("%d%d",&opt,&x);
		//x^=lastans;
		if (opt==1){
			scanf("%d",&y);
			t1.update(t1.rt,1,lim,max(1,x-K),min(x+K,lim),y,0);
 			t2.update(t2.rt,1,lim,max(1,x-K),min(x+K,lim),y,-inf); 
			printf("fuck %d - %d\n", max(1,x-K),min(x+K,lim));
		}
		else if (opt==2){
			scanf("%d",&y);
			t3.update(t3.rt,1,lim,max(1,x-K),min(x+K,lim),y,0);
			t4.update(t4.rt,1,lim,max(1,x-K),min(x+K,lim),y,-inf);
			printf("fuck %d - %d\n", max(1,x-K),min(x+K,lim));
		}
		else {
			lastans=t1.query(t1.rt,1,lim,x);
			lastans=max(lastans,t3.query(t3.rt,1,lim,x));
			lastans=max(lastans,t2.query(t2.rt,1,lim,x)+t4.query(t4.rt,1,lim,x));
			printf("%d\n",lastans);
		}
	}
	return 0;
}