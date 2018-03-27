#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define MAXN 500010
struct node{
    int son[26], link, len;
    inline node(){memset(son,0,sizeof(son));link=len=0;}
    inline node(node &arg){memcpy(son,arg.son,sizeof(son));link=arg.link;len=arg.len;}
    inline int &operator [] (int index){return son[index];}
}sam[MAXN];
int cnt = 1, last = 1;
inline void insert(int x){
    int now = ++cnt;
    sam[now].len = sam[last].len + 1;
    int pre = last;
    while(pre && !sam[pre][x])sam[pre][x] = now;
    if(!pre)return sam[now].link = 1, void();
    int son = sam[pre][x];
    if(sam[pre].len + 1 == sam[son].len)return sam[now].link = son, void();
    int clone = ++cnt;
    sam[clone] = node(sam[son]);
    sam[clone].len = sam[pre].len + 1;
    while(pre && sam[pre][x] == son)sam[pre][x] = clone;
    sam[now].link = sam[son].link = clone;
}

int main(){
    //
    return 0;
}