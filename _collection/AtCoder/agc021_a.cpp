#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
long long n;
int k = 0, flag = 1;
int main(){
    scanf("%lld", &n);
    while(n >= 10){
        flag &= (n % 10) == 9;
        n /= 10;
        k++;
    }
    printf("%d\n", (int)n + 9 * k - !flag);
    return 0;
}