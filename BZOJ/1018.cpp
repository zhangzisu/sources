#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define MAXN 100000
struct martix{
	/*
		1-2 1-2
		| | | |
		3-4 3-4
	*/
	bool $12, $13, $14, $23, $24, $34;
	inline martix(bool value = false){
		$12 = $13 = $14 = $23 = $24 = $34 = value;
	}
	inline bool isConnect(int left, int right){
		if(left == 0){
			if(right == 0)return $12;
			else return $14;
		}else{
			if(right == 0)return $23;
			else return $34;
		}
	}
}val[MAXN << 2];
bool HLT[MAXN], VLT[2][MAXN];
inline martix Merge(const martix &a, const martix &b, int pos){
	martix ret;
	ret.$13 = a.$13;ret.$24 = b.$24;
	if(VLT[0][pos]){
		ret.$12 |= a.$12 && b.$12;
		ret.$14 |= a.$12 && b.$14;
		ret.$23 |= a.$23 && b.$12;
		ret.$34 |= a.$23 && b.$14;
	}
	if(VLT[1][pos]){
		ret.$12 |= a.$14 && b.$23;
		ret.$14 |= a.$14 && b.$34;
		ret.$23 |= a.$34 && b.$23;
		ret.$34 |= a.$34 && b.$34;
	}
	if(VLT[0][pos] && VLT[1][pos]){
		ret.$13 |= a.$12 && b.$13 && a.$34;
		ret.$24 |= b.$12 && a.$24 && b.$34;
	}
	return ret;
}
void Build(int n, int l, int r){
	if(l == r){
		val[n] = martix(HLT[l] = 0);
		val[n].$12 = val[n].$34 = 1;
		return;
	}
	int mid = (l + r) >> 1;
	Build(n << 1, l, mid);Build(n << 1 | 1, mid + 1, r);
	val[n] = martix(0);
}
martix Query(int n, int l, int r, int L, int R){
	if(l == L && r == R)return val[n];
	int mid = (l + r) >> 1;
	if(R <= mid)return Query(n << 1, l, mid, L, R);
	if(L > mid)return Query(n << 1 | 1, mid + 1, r, L, R);
	return Merge(Query(n << 1, l, mid, L, mid), Query(n << 1 | 1, mid + 1, r, mid + 1, R), mid);
}
void Modify(int n, int l, int r, int p){
	if(l == r){
		val[n] = martix(HLT[l]);
		val[n].$12 = val[n].$34 = 1;
		return;
	}
	int mid = (l + r) >> 1;
	if(p <= mid)Modify(n << 1, l, mid, p);
	else Modify(n << 1 | 1, mid + 1, r, p);
	val[n] = Merge(val[n << 1], val[n << 1 | 1], mid);
}
void _Modify(int n, int l, int r, int p){
	int mid = (l + r) >> 1;
	if(p == mid){
		val[n] = Merge(val[n << 1], val[n << 1 | 1], mid);
		return;
	}
	if(p < mid)_Modify(n << 1, l, mid, p);
	else _Modify(n << 1 | 1, mid + 1, r, p);
	val[n] = Merge(val[n << 1], val[n << 1 | 1], mid);
}
int n, r1, c1, r2, c2;
char buf[100];
int main(){
	scanf("%d", &n);
	Build(1, 1, n);
	while(~scanf("%s", buf)){
		martix a, b, c;
		switch(buf[0]){
			case 'C':
				scanf("%d%d%d%d", &r1, &c1, &r2, &c2);r1--;r2--;
				if(c1 > c2)std::swap(c1, c2), std::swap(r1, r2);
				if(c1 == c2)HLT[c1] = 0, Modify(1, 1, n, c1);
				else VLT[r1][c1] = 0, _Modify(1, 1, n, c1);
				break;
			case 'O':
				scanf("%d%d%d%d", &r1, &c1, &r2, &c2);r1--;r2--;
				if(c1 > c2)std::swap(c1, c2), std::swap(r1, r2);
				if(c1 == c2)HLT[c1] = 1, Modify(1, 1, n, c1);
				else VLT[r1][c1] = 1, _Modify(1, 1, n, c1);
				break;
			case 'A':
				scanf("%d%d%d%d", &r1, &c1, &r2, &c2);r1--;r2--;
				if(c1 > c2)std::swap(c1, c2), std::swap(r1, r2);
				if(r1 == r2 && c1 == c2){puts("Y");continue;}
				a = Query(1, 1, n, c1, c2);
				b = Query(1, 1, n, 1, c1);
				c = Query(1, 1, n, c2, n);
				if(c1 == c2){
					if(HLT[c1] || b.$24 || c.$13)puts("Y");
					else puts("N");
					continue;
				}
				if(a.isConnect(r1, r2) || (b.$24 && a.isConnect(!r1, r2)) || (c.$13 && a.isConnect(r1, !r2)) || (b.$24 && c.$13 && a.isConnect(!r1, !r2)))
					puts("Y");
				else
					puts("N");
				break;
			case 'E':
				return 0;
		}
	}
	return 0;
}
