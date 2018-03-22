#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
int n, ans;
char buf[100000];
int main(){
    scanf("%d%s", &n, buf + 1);
    ans = n;
    for(int i = 1;i < n;i++){
        if((buf[i] == 'R' && buf[i + 1] == 'U') || (buf[i] == 'U' && buf[i + 1] == 'R')){
            ans--;
            i++;
        }
    }
    printf("%d\n", ans);
    return 0;
}