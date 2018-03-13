#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 2000010
struct state{
	int son[26], link, len;
	inline state(int len = 0){
		memset(son, 0, sizeof(son));
		this->link = 0; this->len = len;
	}
	inline state(const state &source, int newlen = 0){
		memcpy(son, source.son, sizeof(son));
		this->link = source.link; this->len = newlen;
	}
	inline int& operator [] (int index) { return son[index]; }
}sam[MAXN];
int pre = 1, cnt = 1;
inline void insert(int val){
	int p = ++cnt; sam[p] = state(sam[pre].link + 1);
	int q = pre, s; pre = cnt;
	for(;q && !sam[q][val];q = sam[q].link)sam[q][val] = p;
	if(!q)return sam[p].link = 1, void();
	if(sam[s = sam[q][val]].len == sam[q].len + 1)return sam[p].link = s, void();
	int c = ++cnt; sam[c] = state(sam[s], sam[q].len + 1);
	for(;q && sam[q][val] == s;q = sam[q].link)sam[q][val] = c;
	sam[p].link = sam[s].link = c;
}

int pa[MAXN], fa[MAXN][20], deep[MAXN];
long long pos[MAXN], last[MAXN];
void dfs(int x) {
    pos[x] = last[x] = last[fa[x][0]] + deep[x] * max[x];
    for (int i = 0; i < 26; i++) {
        if (!son[x][i]) continue;
        pa[son[x][i]] = i;
        fa[son[x][i]][0] = x;
        deep[son[x][i]] = deep[x] + 1;
        dfs(son[x][i]);
        last[x] = std::max(last[x], last[son[x][i]]);
    }
}

std::pair<int, int> val[MAXN];

int n, q, p, m, g, k;
char buf[200010];
int main() {
    scanf("%s", buf);
    n = strlen(buf);
    for (int i = 0; i < n; i++) insert(buf + i);
    dfs(1);
    for(int d = 1;d < 20;d++){
        for(int i = 1;i <= cnt;i++){
            fa[i][d] = fa[fa[i][d - 1]][d - 1];
        }
    }
    for (int i = 1; i <= cnt; i++) val[i] = {pos[i], i};
    std::sort(val + 1, val + cnt + 1);
    // print(1);
    scanf("%d", &q);
    while (q--) {
        scanf("%d%d", &p, &m);
        k = 1LL * p * g % m + 1;
        int res = std::lower_bound(val + 1, val + cnt + 1, std::make_pair(k, 0))->second;
        int delta = pos[res] - k;
        int top = deep[res];
        delta %= top;
        for(int i = 0;i < 20;i++)if((delta >> i) & 1)res = fa[res][i];
        printf("%c\n", 'a' + pa[res]);
        g += pa[res] + 'a';
    }
}
