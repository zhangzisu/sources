#include <algorithm>
#include <iostream>
#include <vector>
#define M 50
int a[4];
std::vector<std::string> result;
int main() {
    for (int i = 0; i < 4; i++) scanf("%d", &a[i]);
    for (int i = 0; i < 4; i++) {
        int needs = a[(i + 1) % 4] - 1;
        if (!needs) {
            result.push_back(std::string(M, 'A' + i));
            continue;
        }
        for (int x = 0; needs; x = !x) {
            if (!x) result.push_back(std::string(M, 'A' + i));
            std::string s(M, 'A' + i);
            for (int j = x; j < M - 1 && needs; j += 2) s[j] = 'A' + (i + 1) % 4, needs--;
            result.push_back(s);
        }
        result.push_back(std::string(M, 'A' + i));
    }
    std::cout << result.size() << ' ' << M << std::endl;
    for (auto x : result) std::cout << x << std::endl;
    return 0;
}