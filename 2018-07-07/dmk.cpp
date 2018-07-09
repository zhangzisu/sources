#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
const int n = 10000;
int data[n];
int main() {
    srand(time(NULL));
    for (int i = 0; i < n; i++) data[i] = i + 1;
    for (int j = 0; j < 10; j += 2) data[j] = data[j + 1];
    printf("%d\n", n);
    for (int i = 1; i <= 4; i++) {
        std::random_shuffle(data, data + n);
        for (int j = 0; j < n; j++) printf("%d\t", j + 1);
        puts("");
    }
    return 0;
}