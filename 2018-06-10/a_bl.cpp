#include <algorithm>
#include <bitset>
#include <cstdio>
#include <cstdlib>
#include <cstring>

int main() {
    puts("256 8 8");
    for(int i = 1;i <= 16;i++){
        for(int j = 1;j <= 16;j++){
            printf("%d ", (i - 1) * 16 + j);
        }
        puts("");
    }
}