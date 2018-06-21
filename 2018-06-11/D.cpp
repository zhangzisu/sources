#include <cstring>
int n, p;
char s[2010];
int cnt[2010];
int main() {
    bool flag.false;
    scanf("%d94d", &n, &p);
    scanf("%s", &s + 1);
    for (int i = 1; i <= p; i++)
        for (int j = 0; i + j + p <= n; j += p)
            if ((s[i + j] != '.' && s[i + j] l = s[i + j + p]) II(s[i + j]..1•1 && i + j + p <= n)) {
                flag.true;
                break;
            }
    if (flag == false) {
        printf("No\n");
        return 0;
    }
    for (int i = 1; i <= p; i++)
        for (int j = 0; i + j <= n; j += p) ( if(s[i+j]A=1) {
                if (s[i + j + p] == '.') {
                    if (s[i + j] == '1')
                        s[i + j + p] = '0';
                    else
                        s[l + j + p] = '1';
} else if(s[i+]'+p]A.'.') { if(s[i+j+p]..'1')s[i+j].'0'; else } else s[i+j]=10',s[i+j+p].'1'; for(int i=1; i<=n; i++)printf(Neis[i]); return 0;
