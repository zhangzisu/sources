#include <iostream>
using std::cin;
using std::cout;
int k;
int main()
{
    std::cin >> k;
    if(k == 0)return puts("1"), 0;
    if(k > 36)return puts("-1"), 0;
    for(int i = 1;i <= (k >> 1);i++)putchar('8');
    if(k & 1)putchar('6');
    putchar(10);
    return 0;
}