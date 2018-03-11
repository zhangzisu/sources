#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
string s;
vector<int> x, y;
bool F[2][40000], *f = F[0] + 20000, *g = F[1] + 20000, *t;
int main() {
    cin >> s;
    s = s + 'T';
    int flag = 0, len = 0, sumx = 0, sumy = 0, X, Y;
    cin >> X >> Y;
    for (unsigned i = 0; i < s.length(); i++) {
        if (s[i] == 'T') {
            if (flag)
                y.push_back(len), sumy += len;
            else
                x.push_back(len), sumx += len;
            len = 0;
            flag = !flag;
        } else
            len++;
    }
    g[x[0]] = 1;
    for (unsigned i = 1; i < x.size(); i++) {
        if (!x[i]) continue;
        for (int j = -sumx; j <= sumx; j++) f[j] = g[j + x[i]] | g[j - x[i]];
        t = f;
        f = g;
        g = t;
    }
    if (!g[X]) {
        cout << "No" << endl;
        return 0;
    }
    memset(F, 0, sizeof(F));
    g[0] = 1;
    for (unsigned i = 0; i < y.size(); i++) {
        if (!y[i]) continue;
        for (int j = -sumy; j <= sumy; j++) f[j] = g[j + y[i]] | g[j - y[i]];
        t = f;
        f = g;
        g = t;
    }
    if (!g[Y]) {
        cout << "No" << endl;
        return 0;
    }
    cout << "Yes" << endl;
    return 0;
}