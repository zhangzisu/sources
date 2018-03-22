#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define MOD 1000000007
#define MAXN 50010
#define $ long long
inline void up($ &x, $ y){
    x += y;
    if(x >= MOD)x -= MOD;
}
struct Matrix{
    $ d[3][3];
    inline Matrix(){memset(d, 0, sizeof(d));}
    inline Matrix($ _00, $ _01, $ _02, $ _10, $ _11, $ _12, $ _20 ,$ _21, $ _22){
        d[0][0] = _00; d[0][1] = _01; d[0][2] = _02;
        d[1][0] = _10; d[1][1] = _11; d[1][2] = _12;
        d[2][0] = _20; d[2][1] = _21; d[2][2] = _22;
    }
    inline friend Matrix operator * (const Matrix &a, const Matrix &b){
        Matrix c;
        for($ i = 0;i < 3;i++)
            for($ j = 0;j  <3;j++)
                for($ k = 0;k  <3;k++)
                    up(c.d[i][j], 1LL * a.d[i][k] * b.d[k][j] % MOD);
        return c;
    }
}a(1,1,0,1,1,1,0,1,1)
,b(0,0,0,0,1,1,0,1,1)
,c(0,0,0,0,0,0,0,0,1)
,d(1,0,0,0,0,0,0,0,1)
,e(1,0,0,0,0,0,0,0,0)
,f(1,1,0,1,1,0,0,0,0)
,g(0,0,0,1,0,0,0,0,0)
,h(0,0,0,0,1,0,0,0,0);
struct block{
    $ x;
    $ y;
    $ d;
}dd[MAXN];
$ N, n;
$ m;
inline void apply(const Matrix &trans, Matrix &ans, $ d){
    Matrix tmp = trans;
    while(d){
        if(d & 1)ans = tmp * ans;
        tmp = tmp * tmp;
        d >>= 1;
    }
}
int fucker[3];
inline int status(){
    return ((fucker[2]?1:0)<<2)|((fucker[1]?1:0)<<1)|(fucker[0]?1:0);
}
int main(){
    scanf("%lld%lld", &N, &m);
    dd[++n] = {0, 1, n};
    for($ i = 1;i <= N;i++){
        $ x; $ y;
        scanf("%lld%lld", &x, &y);
        dd[++n] = {x, y, n};
        scanf("%lld", &y);
        dd[++n] = {-x, y, n};
    }
    dd[++n] = {0, m, n};
    std::sort(dd + 1, dd + n + 1, [](auto a, auto b){return a.y == b.y ? a.d < b.d : a.y < b.y;});

    for($ i = 2;i <= n;i++){
        $ len = dd[i].y - dd[i - 1].y;
        switch(status()){
            case 0x0:apply(a, g, len); break;
            case 0x1:apply(f, g, len); break;
            case 0x2:apply(d, g, len); break;
            case 0x3:apply(e, g, len); break;
            case 0x4:apply(b, g, len); break;
            case 0x5:apply(h, g, len); break;
            case 0x6:apply(c, g, len); break;
            case 0x7:puts("0"); return 0;
        }
        if(dd[i].x > 0){
            fucker[3 - dd[i].x]++;
        }
        if(dd[i].x < 0){
            fucker[3 + dd[i].x]--;
        }
        for(int i = 0;i < 3;i++)if(fucker[i])g.d[2 - i][0] = 0;
    }
    printf("%lld\n", g.d[1][0]);
    return 0;
}