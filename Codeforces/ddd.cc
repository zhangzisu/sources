#include <bits/stdc++.h>

using namespace std;

const int N = 5043;
const int M = 12;

bool dp[N][(1 << M)];

typedef pair<int, int> pt;

#define x first
#define y second

vector<int> bits[(1 << M)];

int main() {
    string s;
    cin >> s;
    int n = s.size();
    string ans;
    dp[0][0] = 1;
    vector<pt> cur;
    cur.push_back(make_pair(0, 0));
    int final_sz = n;
    int cur_len = 1;
    int cnt = 0;
    while ((1 << cnt) < n)
        cnt++;
    cnt--;

    for (int i = 0; i < (1 << cnt); i++)
        for (int j = 0; j < cnt; j++)
            if ((i & (1 << j)) == 0)
                bits[i].push_back(j);
    while (final_sz > cur_len) {
        final_sz -= cur_len;
        cur_len *= 2;
    }
    while (ans.size() < final_sz) {
        char min_chr = 'z';
        for (int i = 0; i < cur.size(); i++) {
            auto x = cur[i];
            for (auto y : bits[x.y]) {
                if (dp[x.x + (1 << y)][x.y ^ (1 << y)] == 0) {
                    cur.push_back(make_pair(x.x + (1 << y), x.y ^ (1 << y)));
                    dp[x.x + (1 << y)][x.y ^ (1 << y)] = 1;
                    printf("DDD (%d, %d)\n", x.x,x.y);
                }
            }
            min_chr = min(min_chr, s[x.x]);
        }
        vector<pt> new_cur;
        ans.push_back(min_chr);
        for (auto x : cur)
            if (s[x.x] == min_chr) {
                dp[x.x + 1][x.y] = 1;
                new_cur.push_back(make_pair(x.x + 1, x.y));
                printf("AAA (%d, %d)\n", x.x+1,x.y);
            }
        cur = new_cur;
    }
    cout << ans << endl;
}