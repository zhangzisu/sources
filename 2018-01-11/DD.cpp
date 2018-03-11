#include<bits/stdc++.h>

using namespace std;

#define N 300000
#define MAXN 200010
#define eps (double)1e-6
int n,m;
//double mn[N*4],tag[N*4],
double ans;
struct node{
    int l,r,w,v;
    bool operator < (const node p) const{return l<p.l;}
}a[N];


double val[MAXN << 2], tag[MAXN << 2];
int calcmax(int n, int l, int r){
	if(l == r)return n;
	int mid = (l + r) >> 1;
	return calcmax(n << 1 | 1, mid + 1, r);
}
inline void pushDown(int n){
	val[n << 1] = std::min(val[n << 1], tag[n]);
	val[n << 1 | 1] = std::min(val[n << 1 | 1], tag[n]);
	tag[n << 1] = std::min(tag[n << 1], tag[n]);
	tag[n << 1 | 1] = std::min(tag[n << 1 | 1], tag[n]);
	tag[n] = 1e9;
}
void Modify(int n, int l, int r, int L, int R, double v){
	if(l == L && r == R)return (void)(val[n] = std::min(val[n], v), tag[n] = std::min(tag[n], v));
	int mid = (l + r) >> 1;pushDown(n);
	if(R <= mid)Modify(n << 1, l, mid, L, R, v);
	else if(L > mid)Modify(n << 1 | 1, mid + 1, r, L, R, v);
	else Modify(n << 1, l, mid, L, mid, v), Modify(n << 1 | 1, mid + 1, r, mid + 1, R, v);
	val[n] = std::min(val[n << 1], val[n << 1 | 1]);
}
double Query(int n, int l, int r, int L, int R){
	if(!L || !R)return 0;
	if(l == L && r == R)return val[n];
	int mid = (l + r) >> 1;pushDown(n);
	if(R <= mid)return Query(n << 1, l, mid, L, R);
	if(L > mid)return Query(n << 1 | 1, mid + 1, r, L, R);
	return std::min(Query(n << 1, l, mid, L, mid), Query(n << 1 | 1, mid + 1, r, mid + 1, R));
}

#undef ls
#undef rs

int MMAX;

double check(double x){//printf("check -> %.3f\n",x);
	std::fill(val + 1, val + MMAX + 1, 1e9);
	std::fill(tag + 1, tag + MMAX + 1, 1e9);
    //build(1,1,m); 
	double ret=0;
    for (int i=1;i<=n;i++){//puts("-------");
        double val=1.0*a[i].w-a[i].v*x; if (val<0){ret+=val; val=0;}// printf("val=%.3f\n",val);
        //for (int j=i+1;j<=n;j++)
        //    if (a[j].r<a[i].r){nxt=j+1; if (1.0*a[j].w-a[j].v*x<0) val+=1.0*a[j].w-a[j].v*x;}
        //printf("l=%d r=%d qry=%.3f\n",a[i].l,a[i].r,qry(1,1,m,a[i].l-1,m));
        Modify(1,1,m,1,a[i].r,Query(1,1,m,a[i].l-1,m)+val);
    }
    return ret+Query(1,1,m,m,m);
}
int main(){
    scanf("%d%d",&n,&m);
    MMAX = calcmax(1, 1, m);
    for (int i=1;i<=n;i++)
        scanf("%d%d%d%d",&a[i].l,&a[i].r,&a[i].w,&a[i].v);
    sort(a+1,a+n+1);
    ans=1e9; double l=0,r=1e9;
    while (r-l>eps){
        double mid=(l+r)/2;//cout<<mid<<endl;
        if (check(mid)<=0){ans=mid; r=mid;} else l=mid;
    }
    //printf("%.3f\n",check(25));
    printf("%.3f\n",ans);

    return 0;
}
