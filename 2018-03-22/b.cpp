#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
int n, ans;
char buf[100000];
inline bool compare(int i, int j, int l){
    for(int d = 0;d < l;d++){
        if(buf[i + d] != buf[j + d])return 0;
    }
    return 1;
}
int main(){
    scanf("%d%s", &n, buf + 1);
    ans = n;
    for(int i = 1;i + i <= n;i++){
        if(compare(1, 1 + i, i))ans = std::min(ans, n - (i + i) + 1 + i);
    }
    printf("%d\n", ans);
    return 0;
}