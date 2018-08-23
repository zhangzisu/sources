#include <bits/stdc++.h>
using namespace std;
#define y1 _y1
#define N 100010
#define lson (pos << 1)
#define rson (pos << 1 | 1)

int w, h, n, x1[N], y1[N], x2[N], y2[N];
int id[N * 4], fa[N * 4];
int sum[N * 8];
bool tag[N * 8];
vector<int> vx;
set<int> s;

struct data {
	int y, type, l, r;
	data() {}
	data(int _y, int _type, int _l, int _r = 0)
	    : y(_y), type(_type), l(_l), r(_r) {}
	inline bool operator<(data &d) {
		return make_pair(make_pair(y, type), make_pair(l, r)) < make_pair(make_pair(d.y, d.type), make_pair(d.l, d.r));
	}
} opt[N * 2];

int find(int x) {
	if (fa[x] == -1) return x;
	return fa[x] = find(fa[x]);
}

bool join(int x, int y) {
	int fx = find(x), fy = find(y);
	if (fx == fy) return false;
	fa[fx] = fy;
	return true;
}

void insert(int pos, int l, int r, int x, int y) {
	sum[pos] += y;
	if (l == r) return;
	int mid = (l + r) >> 1;
	if (x <= mid)
		insert(lson, l, mid, x, y);
	else
		insert(rson, mid + 1, r, x, y);
}

int query(int pos, int l, int r, int x, int y) {
	if (x <= l && r <= y) return sum[pos];
	int mid = (l + r) >> 1, re = 0;
	;
	if (x <= mid) re += query(lson, l, mid, x, y);
	if (y > mid) re += query(rson, mid + 1, r, x, y);
	return re;
}

void lazy(int pos) {
	tag[lson] = tag[rson] = 1;
	tag[pos] = 0;
}

void color(int pos, int l, int r, int x) {
	if (l == r) {
		tag[pos] = 0;
		return;
	}
	int mid = (l + r) >> 1;
	if (tag[pos]) lazy(pos);
	if (x <= mid)
		color(lson, l, mid, x);
	else
		color(rson, mid + 1, r, x);
}

void clear(int pos, int l, int r, int x, int y) {
	if (x <= l && r <= y) {
		tag[pos] = 1;
		return;
	}
	if (tag[pos]) return;
	int mid = (l + r) >> 1;
	if (x <= mid) clear(lson, l, mid, x, y);
	if (y > mid) clear(rson, mid + 1, r, x, y);
}

bool check(int pos, int l, int r, int x) {
	if (tag[pos]) return true;
	if (l == r) return false;
	int mid = (l + r) >> 1;
	if (x <= mid) return check(lson, l, mid, x);
	return check(rson, mid + 1, r, x);
}

void give(int x) {
	static int tot = 0;
	if (check(1, 0, n * 2, x))
		color(1, 0, n * 2, x), id[x] = ++tot;
}

int main() {
	cin >> w >> h >> n;
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d%d%d", &x1[i], &y1[i], &x2[i], &y2[i]);
		if (x1[i] > x2[i]) swap(x1[i], x2[i]);
		if (y1[i] > y2[i]) swap(y1[i], y2[i]);
	}
	x1[n + 1] = 0, y1[n + 1] = 0, x2[n + 1] = w, y2[n + 1] = 0;
	x1[n + 2] = 0, y1[n + 2] = h, x2[n + 2] = w, y2[n + 2] = h;
	x1[n + 3] = 0, y1[n + 3] = 0, x2[n + 3] = 0, y2[n + 3] = h;
	x1[n + 4] = w, y1[n + 4] = 0, x2[n + 4] = w, y2[n + 4] = h;
	n += 4;

	vx.push_back(-1);
	for (int i = 1; i <= n; ++i)
		vx.push_back(x1[i]), vx.push_back(x2[i]);
	sort(vx.begin(), vx.end());
	vx.erase(unique(vx.begin(), vx.end()), vx.end());
	for (int i = 1; i <= n; ++i)
		x1[i] = lower_bound(vx.begin(), vx.end(), x1[i]) - vx.begin(),
		x2[i] = lower_bound(vx.begin(), vx.end(), x2[i]) - vx.begin();

	memset(id, -1, sizeof id);
	memset(fa, -1, sizeof fa);
	s.insert(0);
	id[0] = 0;

	for (int i = n; i; --i)
		if (x1[i] == x2[i])
			opt[i] = data(y1[i], 0, x1[i]),
			opt[++n] = data(y2[i], 2, x1[i]);
		else
			opt[i] = data(y1[i], 1, x1[i], x2[i]);
	sort(opt + 1, opt + n + 1);

	long long ans = 0;
	for (int i = 1; i <= n; ++i) {
		if (opt[i].type == 0) {
			int r = opt[i].l, l = *--s.lower_bound(r);
			give(l), give(r);
			join(id[r], id[l]);
			s.insert(r);
			insert(1, 0, n * 2, r, 1);
		} else if (opt[i].type == 1) {
			int l = opt[i].l, r = opt[i].r,
			    temp = query(1, 0, n * 2, l, r);
			if (temp < 2) continue;
			ans += temp - 1;
			clear(1, 0, n * 2, l, *--s.upper_bound(r) - 1);
		} else if (opt[i].type == 2) {
			int r = opt[i].l, l = *--s.lower_bound(r);
			give(l), give(r);
			if (join(id[l], id[r])) --ans;
			s.erase(r);
			insert(1, 0, n * 2, r, -1);
		}
        fprintf(stderr, "ANS at pos %d: %d\n", opt[i].y, ans);
	}
	cout << ans << endl;
	return 0;
}