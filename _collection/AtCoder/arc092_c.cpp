#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <list>
#include <vector>
#define MAXN 1010
int n;
long long a[MAXN];
inline std::pair<std::vector<int>, long long> calcAns(int start) {
    long long result = 0, max = start;
    std::vector<int> indexes;
    for (int i = start; i <= n; i += 2) {
        if (a[i] > 0LL) result += a[i], indexes.push_back(i);
        if (a[i] > a[max]) max = i;
    }
    if (!result) result = a[max], indexes.push_back(max);
    return {indexes, result};
}

std::vector<int> result;

inline std::list<int> fill(std::vector<int> v) {
    std::list<int> result;
    static int tmp[MAXN];
    memset(tmp, 0, sizeof(tmp));
    for (auto i : v) tmp[i] = 1;
    for (int i = 1; i <= n; i++) result.push_back(tmp[i]);
    return result;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
    auto l = calcAns(1), r = calcAns(2);

    if (l.second < r.second) std::swap(l, r);
    printf("%lld\n", l.second);
    auto status = fill(l.first);
    while (!status.back()) result.push_back(status.size()), status.pop_back();
    while (!status.front()) result.push_back(1), status.pop_front();
    while (status.size() > 2) {
        auto c = status.begin();
        auto a = c++;
        auto b = c++;
        int pos = 2;
        while (c != status.end()) {
            if (!(*a ^ *c)) {
                result.push_back(pos);
                status.insert(a, *a);
                status.erase(a);
                status.erase(b);
                status.erase(c);
                break;
            }
            a = b, b = c, c++;
            pos++;
        }
    }
    printf("%lu\n", result.size());
    for (auto i : result) printf("%d\n", i);
    return 0;
}