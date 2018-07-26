#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#define MAXN 910
#define MOD 1000000007

struct ahoCorasick {
    struct trieNode {
        trieNode *next[2], *pre, *fail;
        bool danger;
    } buf[MAXN], *root, *top;
    inline ahoCorasick() {
        memset(buf, 0, sizeof(buf));
        top = buf;
        root = newNode();
    }
    inline trieNode *newNode() {
        return top++;
    }
    inline void insert(const char *str) {
        trieNode *p = root;
        for (int i = 0; str[i]; i++) {
            trieNode *&x = p->next[str[i] ^ 48];
            if (!x) (x = newNode())->pre = p;
            p = x;
        }
        p->danger = true;
    }
    inline void build() {
        std::queue<trieNode *> Q;
        Q.push(root);
        while (Q.size()) {
            trieNode *x = Q.front();
            Q.pop();
            for (int y = 0; y < 2; y++) {
                trieNode *&z = x->next[y];
                if (z) {
                    z->fail = x->fail ? x->fail->next[y] : root;
                    Q.push(z);
                } else {
                    z = x->fail ? x->fail->next[y] : root;
                }
            }
            if (x->fail) x->danger |= x->fail->danger;
        }
    }
    inline int getID(trieNode *node) {
        return node - root;
    }
    inline trieNode *getNode(int pos) {
        return root + pos;
    }
    inline trieNode *getNode(const char *str) {
        trieNode *p = root;
        for (int i = 0; str[i]; i++)
            p = p->next[str[i] ^ 48];
        return p;
    }
    inline int getStr(trieNode *node, char *output) {
        int len = 0;
        for (; node != root; node = node->pre)
            output[len++] = (node->pre->next[1] == node) ^ 48;
        std::reverse(output, output + len);
        output[len] = '\0';
        return len;
    }
    inline bool isMatch(const char *str) {
        trieNode *p = root;
        for (int i = 0; str[i]; i++) {
            p = p->next[str[i] ^ 48];
            if (p->danger) return 1;
        }
        return 0;
    }
} acm0, acm1;
typedef int arr[2][MAXN][MAXN];
arr f[2];
int winnie[MAXN][MAXN], n, m, ans;
char buf[MAXN];
inline int calc(ahoCorasick::trieNode *a, ahoCorasick::trieNode *b) {
    // fprintf(stderr, "CALC acm0: %d, acm1: %d:\n", acm0.getID(a), acm1.getID(b));
    int len0 = acm0.getStr(a, buf);
    int len1 = acm1.getStr(b, buf + len0) + len0;
    std::reverse(buf + len0, buf + len1);
    // fprintf(stderr, "STRING: %s\n", buf);
    return acm0.isMatch(buf);
}
inline void up(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%s", buf);
        acm0.insert(buf);
        std::reverse(buf, buf + strlen(buf));
        acm1.insert(buf);
    }
    acm0.build();
    acm1.build();
    for (ahoCorasick::trieNode *p = acm0.root; p != acm0.top; p++) {
        for (ahoCorasick::trieNode *q = acm1.root; q != acm1.top; q++) {
            winnie[acm0.getID(p)][acm1.getID(q)] = calc(p, q);
        }
    }
    f[0][0][acm0.getID(acm0.root)][acm1.getID(acm1.root)] = 1;
    for (register int i = 1; i <= n / 2; i++) {
        arr &pre = f[!(i & 1)], &now = f[i & 1];
        memset(now, 0, sizeof(now));
        for (register int j = 0; j < 2; j++) {
            for (ahoCorasick::trieNode *p = acm0.root; p != acm0.top; p++) {
                for (ahoCorasick::trieNode *q = acm1.root; q != acm1.top; q++) {
                    int &x = pre[j][acm0.getID(p)][acm1.getID(q)];
                    if (!x) continue;
                    for (register int c = 0; c < 2; c++) {
                        ahoCorasick::trieNode *pn = p->next[c];
                        ahoCorasick::trieNode *qn = q->next[c];
                        int sum = j;
                        if (pn->danger) sum++, pn = acm0.root;
                        if (qn->danger) sum++, qn = acm1.root;
                        if (sum >= 2) continue;
                        up(now[sum][acm0.getID(pn)][acm1.getID(qn)], x);
                    }
                }
            }
        }
    }
    if (n & 1) {
        arr &now = f[(n / 2) & 1];
        for (register int j = 0; j < 2; j++) {
            for (ahoCorasick::trieNode *p = acm0.root; p != acm0.top; p++) {
                for (ahoCorasick::trieNode *q = acm1.root; q != acm1.top; q++) {
                    for (int c = 0; c < 2; c++) {
                        ahoCorasick::trieNode *pn = p->next[c];
                        int sum = j + winnie[acm0.getID(pn)][acm1.getID(q)];
                        if (sum < 2) up(ans, now[j][acm0.getID(p)][acm1.getID(q)]);
                    }
                }
            }
        }
    } else {
        arr &now = f[(n / 2) & 1];
        for (register int j = 0; j < 2; j++) {
            for (ahoCorasick::trieNode *p = acm0.root; p != acm0.top; p++) {
                for (ahoCorasick::trieNode *q = acm1.root; q != acm1.top; q++) {
                    int sum = j + winnie[acm0.getID(p)][acm1.getID(q)];
                    if (sum < 2) up(ans, now[j][acm0.getID(p)][acm1.getID(q)]);
                }
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}