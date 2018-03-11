#include <iostream>
#include <string>
using namespace std;
int main() {
    string s;
    cin >> s;
    int n = s.length(), ans = n;
    for (int i = 1; i < n; i++)
        if (s[i - 1] != s[i]) ans = std::min(ans, std::max(i, n - i));
    printf("%d\n", ans);
    return 0;
}