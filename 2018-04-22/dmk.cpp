#include <cstdio>
#include <cstdlib>
#include <ctime>

int main() {
    srand(time(NULL));
    puts("10 10 10 10");
    for(int i = 0;i < 10;i++)printf("%d %d %d\n", rand() % 10 + 1, rand() % 10 + 1, rand() % 10 + 1);
    return 0;
}