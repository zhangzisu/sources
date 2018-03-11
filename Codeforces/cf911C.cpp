#include <iostream>
int x, y, z;
int main() {
    std::cin >> x >> y >> z;
    if (x > y) std::swap(x, y);
    if (y > z) std::swap(y, z);
    if (x > y) std::swap(x, y);
    if (y > z) std::swap(y, z);
    if (x == 1 || y == 1 || z == 1) goto succ;
    if ((x == 2 && y == 2) || (x == 2 && z == 2) || (y == 2 && z == 2))
        goto succ;
    if (x == 3 && y == 3 && z == 3) goto succ;
    if (x == 2 && y == 4 && z == 4) goto succ;
    puts("NO");
    return 0;
succ:
    puts("YES");
    return 0;
}