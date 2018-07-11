#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;

const int MAXN = 65;
lnt x[MAXN];
vector<lnt> f;

lnt Pollard_Rho(lnt n, int c) {
    lnt i = 1, k = 2, x = rand()%(n-1)+1, y = x;
    while(true) {
        i++;
        x = (multi(x, x, n) + c)%n;
        lnt p = gcd((y-x+n)%n, n);
        if(p != 1 && p != n) return p;
        if(y == x) return n;
        if(i == k) {
            y = x;
            k <<= 1;
        }
    }
}

void find(lnt n, int c) {
    if(n == 1) return;
    if(Miller_Rabin(n)) {
        f.push_back(n);
        return;
    }
    lnt p = n, k = c;
    while(p >= n) p = Pollard_Rho(p, c--);
    find(p, k);
    find(n/p, k);
}