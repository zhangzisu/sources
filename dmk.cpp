#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

const int N = 10000, m = 1, q = 10000;
std::vector<std::string> gen;
std::string random_string(int len) {
    std::string ret;
    for (int i = 0; i < len; i++) ret += (rand() & 1) ? 'a' : 'b';
    return ret;
}
int n;
int main() {
    int len = 0;
    while (len <= N) {
        int next = rand() % 100 + 1;
        if (len + next > N) break;
        gen.push_back(random_string(next));
        len += next;
    }
    printf("%d %d %d\n", n = (int)gen.size(), m, q);
    for (auto i : gen) printf("%s\n", i.c_str());
    for (int i = 1; i <= n; i++) printf("%d ", rand() % m + 1);
    puts("");
    for(int i=1;i<=m;i++)printf("%d ",rand()%1000000+1);
    puts("");
    int pre=0;
    for(int i=1;i<=n;i++)printf("%d ",pre=(rand()%1000+1+pre));
    puts("");
    for(int i=0;i<q;i++){
        if(rand()&1){
        int next=rand()%100+1;
        printf("1 %s\n", random_string(next).c_str());
        }else{
            printf("2 %d %d\n", rand()%n+1,rand()%m+1);
        }
    }
    return 0;
}