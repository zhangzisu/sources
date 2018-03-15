#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<ctime>

inline int randInt() {return (((long long)rand() << 16) | rand()) >> 1;}
inline long long randLong() {return ((unsigned long long)randInt() << 32 | randInt()) >> 1;}

int main(){
    srand(time(NULL));
    putchar(rand()%9+'1');
    for(int i = 1;i < 1000;i++)putchar(rand()%10+'0');
    putchar(0xA);
    printf("%llu\n", randLong()%100000000000000000LL);
    return 0;
}