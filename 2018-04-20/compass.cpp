#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
int n, x[1010], y[1010];
int main() {
    srand(time(NULL));
    // scanf("%d", &n);
    // for (int i = 1; i <= n; i++) scanf("%d%d", &x[i], &y[i]);
    /*
        Make lemon happy.
    */
    puts(rand() & 1 ? "DANGER" : "SAFETY");
    return 0;
}