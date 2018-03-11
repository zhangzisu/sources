#include<cstdio>
#include<cstring>
#define MAXN 1000010
int n, op, l, r;
int va[MAXN << 2], vo[MAXN << 2], lt[MAXN << 2];
const int MAX = (1 << 30) - 1;
inline void pushDown(int n){
    if(!~lt[n])return;
    va[n << 1] = va[n << 1 | 1] = lt[n];
    vo[n << 1] = vo[n << 1 | 1] = lt[n];
    lt[n << 1] = lt[n << 1 | 1] = lt[n];
    lt[n] = -1;
}
inline void pushUp(int n){
    va[n] = va[n << 1] & va[n << 1 | 1];
    vo[n] = vo[n << 1] | vo[n << 1 | 1];
}
int Query(int n, int l, int r, int p){
    if(l == r)return va[n];
    int mid = (l + r) >> 1;pushDown(n);
    if(p <= mid)return Query(n << 1, l, mid, p);
    else return Query(n << 1 | 1, mid + 1, r, p);
}
void Increase(int n, int l, int r, int p, int v){
	if(l == r){va[n] += v;vo[n] += v;return;}
	int mid = (l + r) >> 1;pushDown(n);
	if(p <= mid)Increase(n << 1, l, mid, p, v);
	else Increase(n << 1 | 1, mid + 1, r, p, v);
	pushUp(n);
}
void Modify(int n, int l, int r, int L, int R, int v){
    if(l == L && r == R){
	    lt[n] = va[n] = vo[n] = v;
	    return;
	}
    int mid = (l + r) >> 1;pushDown(n);
    if(R <= mid)Modify(n << 1, l, mid, L, R, v);
    else if(L > mid)Modify(n << 1 | 1, mid + 1, r, L, R, v);
    else Modify(n << 1, l, mid, L, mid, v), Modify(n << 1 | 1, mid + 1, r, mid + 1, R, v);
    pushUp(n);
}
int Find0(int n, int l, int r, int p){
	if(va[n] == MAX)return 0;
    if(l == r)return l;
    int mid = (l + r) >> 1;pushDown(n);
    if(p <= mid){
    	int rt = Find0(n << 1, l, mid, p);
    	return rt ? rt : Find0(n << 1 | 1, mid + 1, r, p);
	}
	return Find0(n << 1 | 1, mid + 1, r, p);
}
int Find1(int n, int l, int r, int p){
    if(!vo[n])return 0;
    if(l == r)return l;
    int mid = (l + r) >> 1;pushDown(n);
    if(p <= mid){
    	int rt = Find1(n << 1, l, mid, p);
    	return rt ? rt : Find1(n << 1 | 1, mid + 1, r, p);
	}
	return Find1(n << 1 | 1, mid + 1, r, p);
}
inline void Add(int p1, int x){
	int now = Query(1, 1, MAXN, p1);
	if(now + x <= MAX)Increase(1, 1, MAXN, p1, x);
	else{
		Increase(1, 1, MAXN, p1, x - MAX - 1);
		int p2 = Find0(1, 1, MAXN, p1 + 1);
		if(p1 + 1 < p2)Modify(1, 1, MAXN, p1 + 1, p2 - 1, 0);
		Increase(1, 1, MAXN, p2, 1);
	}
}
inline void Del(int p1, int x){
	int now = Query(1, 1, MAXN, p1);
	if(now >= x)Increase(1, 1, MAXN, p1, -x);
	else{
		Increase(1, 1, MAXN, p1, MAX + 1 - x);
		int p2 = Find1(1, 1, MAXN, p1 + 1);
		if(p1 + 1 < p2)Modify(1, 1, MAXN, p1 + 1, p2 - 1, MAX);
		Increase(1, 1, MAXN, p2, -1);
	}
}
inline void print(unsigned x){
	for(int i = 29;i >= 0;i--)putchar(((x >> i) & 1) ^ 48);
}
inline void print(){
	for(int i = 3;i;i--)print(Query(1, 1, MAXN, i)), putchar(' ');
    puts("");
}
int main(){
    scanf("%d%*d%*d%*d", &n);
    while(n--){
	    scanf("%d", &op);
	    if(op & 1){
		    scanf("%d%d", &l, &r);
		    int p1 = r / 30 + 1, p2 = r % 30;int val;
		    if(!l)continue;
		    if(l < 0){
				val = -l;
				Del(p1, (val << p2) & MAX);
				Del(p1 + 1, val >> (30 - p2));
			}else{
				val = l;
				Add(p1, (val << p2) & MAX);
				Add(p1 + 1, val >> (30 - p2));
			}
			//print();
		}else{
		    scanf("%d", &l);
		    int p1 = l / 30 + 1, p2 = l % 30;
		    printf("%d\n", (Query(1, 1, MAXN, p1) >> p2) & 1);
		}
	}
    return 0;
}
