#include<cstdio>
#include<cctype>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define BUF 1048576
char _1[BUF], *_3 = _1 + BUF;
inline char gc() { if (_3 == _1 + BUF)fread(_1, 1, BUF, stdin), _3 = _1; return *_3++; }
inline int $(){
	register int x = 0;register char ch = gc();
	while(!isdigit(ch))ch = gc();
	for(;isdigit(ch);ch = gc())x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
inline char $$(){
	register char ch = gc();
	while(ch == '\r' || ch == '\n' || ch == '\t' || ch == ' ')ch = gc();
	return ch;
}
#include<vector>
#include<map>
int n = $(), m = $();

struct point {
	int x, y;
	inline point(int x = 0, int y = 0) : x(x), y(y) {}
	inline friend point operator+(const point& a, const point& b) {return point(a.x + b.x, a.y + b.y);}
	inline friend point operator-(const point& a, const point& b) {return point(a.x - b.x, a.y - b.y);}
	inline friend bool operator<(const point& a, const point& b) {return a.x < b.x;}
	inline friend bool operator==(const point &a, const point &b) {return a.x == b.x && a.y == b.y;}
}st;
inline long long Cross(const point& a, const point& b) {return (long long)a.x * b.y - (long long)b.x * a.y;}
std::map<int, int> up, down, tmp;
inline bool contains(std::map<int, int>& M, point x) {
	if (M.find(x.x) != M.end()) return M[x.x] <= x.y;
	if (M.size() < 2) return 0;
	if (M.begin()->first > x.x || M.rbegin()->first < x.x) return 0;
	std::map<int, int>::iterator R = M.lower_bound(x.x);
	std::map<int, int>::iterator L = R;L--;
	point l(L->first, L->second), r(R->first, R->second);
	return Cross(r - l, x - l) >= 0;
}
inline void Insert(std::map<int, int>& M, point x) {
	if (contains(M, x)) return;
	M[x.x] = x.y;
	std::map<int, int>::iterator p = M.upper_bound(x.x);
	if (p != M.end()) {
		std::map<int, int>::iterator q = p;q++;
		while (q != M.end()) {
			point P = point(p->first, p->second), Q = point(q->first, q->second);
			if (Cross(Q - x, P - x) >= 0)M.erase(p), p = q, q++;
			else break;
		}
	}
	p = M.lower_bound(x.x);
	if (p == M.begin() || (--p) == M.begin()) return;
	std::map<int, int>::iterator q = p;q--;
	while (p != M.begin()) {
		point P = point(p->first, p->second), Q = point(q->first, q->second);
		if (Cross(x - Q, P - Q) >= 0)M.erase(p), p = q, q--;
		else break;
	}
}
std::vector<point> vtx;

int map[55][55], ans = 0, res = 0;
inline int cost(int x1, int y1, int x2, int y2){
	return std::max(std::abs(x1 - x2), std::abs(y1 - y2));
}
void fill(int x, int y){
	if(~map[x][y])return;
	if(x < 0 || y < 0 || x > n || y > m)return;
	if(map[x - 1][y] == 1 || map[x][y - 1] == 1 || map[x + 1][y] == 1 || map[x][y + 1] == 1){
		map[x][y] = 2;
		vtx.push_back(point(y, x));
	}else map[x][y] = 0;
	fill(x - 1, y);fill(x + 1, y);fill(x, y - 1);fill(x, y + 1);
}
int main(){
	memset(map, -1, sizeof(map));
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			char gg = $$();
			if(gg == '*')st = point(j, i), map[i][j] = 3;
			else if(gg == 'X')map[i][j] = 1;
		}
	}

	fill(1, 1);puts("DEBUG");
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			putchar(map[i][j] == -1 ? '#' : (map[i][j] == 0 ? '_' : map[i][j] == 2 ? '$' : map[i][j] == 1 ? 'X' : '-'));
		}
		putchar(10);
	}

	vtx.push_back(st);
	std::sort(vtx.begin(), vtx.end());
	for(int i = 0;i < (int)vtx.size();i++){
		if(vtx[i].x <= st.x)Insert(up, point(vtx[i].x, -vtx[i].y));
		if(vtx[i].x >= st.x)Insert(tmp, point(vtx[i].x, -vtx[i].y));
		Insert(down, vtx[i]);
	}

	for(std::map<int, int>::iterator it = up.begin();it != up.end();it++)printf("UPC1: (%d, %d)\n", -it->second, it->first);
	for(std::map<int, int>::iterator it = tmp.begin();it != tmp.end();it++)printf("UPC2: (%d, %d)\n", -it->second, it->first);
	for(std::map<int, int>::iterator it = down.begin();it != down.end();it++)printf("DWC: (%d, %d)\n", it->second, it->first);

	std::map<int, int>::iterator p, q;
	p = q = up.begin();q++;
	while(q != up.end())ans += cost(-p->second, p->first, -q->second, q->first), p = q, q++;
	p = q = tmp.begin();q++;
	while(q != tmp.end())ans += cost(-p->second, p->first, -q->second, q->first), p = q, q++;
	ans += cost(-up.rbegin()->second, up.rbegin()->first, -tmp.begin()->second, tmp.begin()->first);
	p = q = down.begin();q++;
	while(q != down.end())ans += cost(p->second, p->first, q->second, q->first), p = q, q++;
	ans += cost(-up.begin()->second, up.begin()->first, down.begin()->second, down.begin()->first);
	ans += cost(-tmp.rbegin()->second, tmp.rbegin()->first, down.rbegin()->second, down.rbegin()->first);

	res = ans;
	printf("NOW ANS : %d\n", ans);
	
	up.clear();tmp.clear();down.clear();ans = 0;
	for(int i = 0;i < (int)vtx.size();i++){
		Insert(up, point(vtx[i].x, -vtx[i].y));
		if(vtx[i].x <= st.x)Insert(down, vtx[i]);
		if(vtx[i].x >= st.x)Insert(tmp, vtx[i]);
	}

	for(std::map<int, int>::iterator it = up.begin();it != up.end();it++)printf("UPC: (%d, %d)\n", -it->second, it->first);
	for(std::map<int, int>::iterator it = down.begin();it != down.end();it++)printf("DWC1: (%d, %d)\n", it->second, it->first);
	for(std::map<int, int>::iterator it = tmp.begin();it != tmp.end();it++)printf("DWC2: (%d, %d)\n", it->second, it->first);

	p = q = up.begin();q++;
	while(q != up.end())ans += cost(-p->second, p->first, -q->second, q->first), p = q, q++;
	p = q = down.begin();q++;
	while(q != down.end())ans += cost(p->second, p->first, q->second, q->first), p = q, q++;
	p = q = tmp.begin();q++;
	while(q != tmp.end())ans += cost(p->second, p->first, q->second, q->first), p = q, q++;
	ans += cost(down.rbegin()->second, down.rbegin()->first, tmp.begin()->second, tmp.begin()->first);
	ans += cost(-up.begin()->second, up.begin()->first, down.begin()->second, down.begin()->first);
	ans += cost(-up.rbegin()->second, up.rbegin()->first, tmp.rbegin()->second, tmp.rbegin()->first);

	res = std::min(res, ans);
	printf("NOW ANS : %d\n", ans);

	printf("%d\n", res);
	return 0;
} 
