#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>

int n = 0;
const int body_length = 10;
std::vector<std::pair<int, int>> V;

int main() {
    srand(time(NULL));
    for (int i = 1; i < body_length; i++) {
        V.push_back({i, i + 1});
    }
    n = body_length;
    for (int i = 1; i <= body_length; i++) {
        int cnt = rand() % 5;
        while (cnt--) V.push_back({++n, i});
    }
    printf("%d\n", n);
    for (auto x : V) printf("%d %d\n", x.first, x.second);
    return 0;
}