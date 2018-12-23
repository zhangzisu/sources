#include <algorithm>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
typedef long long lnt;
struct complex {
    lnt real, image;
    inline complex(lnt real = 0, lnt image = 0) : real(real), image(image) {}
    inline complex friend operator+(complex a, complex b) {
        return complex(a.real + b.real, a.image + b.image);
    }
    inline complex friend operator-(complex a, complex b) {
        return complex(a.real - b.real, a.image - b.image);
    }
    inline complex friend operator*(complex a, complex b) {
        return complex(a.real * b.real - a.image * b.image, a.real * b.image + a.image * b.real);
    }
};
lnt x, y;
std::vector<int> ans;
int main() {
    freopen("guangzhou.in", "r", stdin);
    freopen("guangzhou.out", "w", stdout);
    scanf("%lld%lld", &x, &y);
    complex cur(x, y);
    for (int i = 0; cur.real || cur.image; i++) {
        complex next = cur * complex(-1, 1);
        if (next.real & 1) {
            cur.real--;
            ans.push_back(i);
        }
        cur = cur * complex(-1, 1);
        cur.real /= 2, cur.image /= 2;
    }
    printf("%llu\n", ans.size());
    for (int i = 0; i < (int)ans.size(); i++) printf("%d\n", ans[i]);
    return 0;
}