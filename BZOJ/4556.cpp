#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define MAXN 100010
int cnt = 1, last = 1;
struct state{
    int son[26], len, link;
    inline int& operator[](int index){return son[index];}
}sam[MAXN];
inline void extend(int x){
    int p=last,np=++cnt,q,nq;
    last=np;
    sam[np].len=sam[p].len+1;
    for(;p&&!sam[p][x];p=sam[p].link)sam[p][x]=np;
    if(!p)return sam[np].link=1,void();
    q=sam[p][x];
    if(sam[q].len==sam[p].len+1)return sam[np].link=q,void();
    memcpy(sam[nq=++cnt].son,sam[q].son,sizeof(int)*26);
    
}
int main(){
    //
    return 0;
}