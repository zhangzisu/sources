#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
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
int main() {
    auto t = complex(1, 1);
    auto f = complex(1, 2);
    auto a = f * t;
    printf("%lld %lldi\n", a.real, a.image);
    return 0;
}