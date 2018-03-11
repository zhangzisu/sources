#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define _SU 28
int k, stk[_SU], m, n;
inline int judge(int x){ return !(x >> 1); }
int ans[_SU], len;
int SU;
void DFS(int d, int rd){
    if(d >= SU || rd >= SU)return;
    int t0, t1, t2, dd, tmp[_SU]; bool ok;
    for(int i = (d == 0);i < 10;i++){
        if(judge(((t0 = n * i) % 10 + stk[d]) % 10)){
            t1 = t0; t2 = 0; ok = true; dd = rd;
            memcpy(tmp, stk, sizeof(tmp));
            for(int j = d;t1 || t2 || j <= rd;j++, t1 /= 10){
                if(j >= SU)goto fail;
                stk[j] += t1 % 10 + t2;
                t2 = stk[j] / 10;
                stk[j] %= 10;
                ok &= judge(stk[j]);
                dd = std::max(dd, j);
            }
            if(ok){
                dd++;
                if(dd < len)goto succ;
                for(int j = SU - 1;~j;j--){
                    if(stk[j] < ans[j])goto succ;
                    if(stk[j] > ans[j])goto fail;
                }
                goto fail;
                succ:memcpy(ans, stk, sizeof(ans));
                len = SU = dd;
            }else{
                DFS(d + 1, dd);
            }
            fail:memcpy(stk, tmp, sizeof(stk));
        }
    }
}

int main(){
    scanf("%d%*d", &k);
    while(k--){
        scanf("%d", &n);
        if(n == 999){ puts("111111111111111111111111111"); continue; }
        memset(ans, 0, sizeof(ans));
        memset(stk, 0, sizeof(stk));
        len = 0x3F3F3F3F;
        SU = _SU;
        DFS(0, 0);
        if(len == 0x3F3F3F3F)puts("BRAK");
        else{
            int top = 0;
            for(int i = SU - 1;~i;i--){
                if(ans[i]){top = 1;}
                if(top){putchar(ans[i] ^ 48);}
            }
            putchar(10);
        }
    }
    return 0;
}