#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <set>
const int maxn = 1000, maxm = 5000;
int a[maxn];
inline int rand(int x) {
    long long d = ((long long)rand() << 16) + rand();
    return d % x;
}
std::set<int> set;
int main() {
    srand(time(NULL));
    for (int i = 0; i < maxn; i++) a[i] = rand(200000);
    for (int i = 0; i < maxm; i++) {
        int u = rand(maxn), v = rand(maxn);
        set.insert(std::abs(a[u] - a[v]));
    }
    printf("%lu\n", set.size());
}