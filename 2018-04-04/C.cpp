#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
int n;

int main() {
    scanf("%d",&n);
    for(int i = 1;i <= 4;i++)
    for(int j = 1;j <= 4;j++)if(i != j)
    for(int k = 1;k <= 4;k++)if(i != k && j != k)
    for(int l = 1;l <= 4;l++)if(i != l && j != l && k != l)
    printf("{%d,%d,%d,%d},",i,j,k,l),n++;
    puts("");printf("%d\n",n);
    return 0;
}