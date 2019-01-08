#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
std::pair<int, int> a0, a1, a2, a3;
std::pair<int, int> b0, b1, b2, b3;
inline void in(std::pair<int, int> &p) {
    scanf("%d%d", &p.first, &p.second);
}
void out() {
    puts("NO");
    exit(0);
}
int main(int argc, char const *argv[]) {
    in(a0), in(a1), in(a2), in(a3);
    in(b0), in(b1), in(b2), in(b3);
    int lenB = std::abs(b0.first - b2.first) + std::abs(b0.second - b2.second);
    // printf("lenb : %d\n", lenB);
    int minX = std::min(std::min(a0.first, a1.first), std::min(a2.first, a3.first));
    int minY = std::min(std::min(a0.second, a1.second), std::min(a2.second, a3.second));
    int maxX = std::max(std::max(a0.first, a1.first), std::max(a2.first, a3.first));
    int maxY = std::max(std::max(a0.second, a1.second), std::max(a2.second, a3.second));
    // printf("minx = %d, miny = %d, maxx = %d, maxy = %d\n", minX, minY, maxX, maxY);
    std::pair<int, int> key = b0;
    if (b1.second < key.second) key = b1;
    if (b2.second < key.second) key = b2;
    if (b3.second < key.second) key = b3;
    // printf("key point : (%d, %d)\n", key.first, key.second);
    if (key.second > maxY) out();
    if (key.first + maxY - minX < key.second) out();
    if (key.first < minX - lenB / 2) out();
    if (-key.first + minX + minY - lenB > key.second) out();
    if (key.second < minY - lenB) out();
    if (key.first + (minY - lenB) - (maxX) > key.second) out();
    if (key.first > maxX + lenB / 2) out();
    if (-key.first + maxX + maxY < key.second) out();
    puts("YES");
    return 0;
}
