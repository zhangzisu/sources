#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
int n;
std::string s[6];
std::string ss[6];

int no[6], all = 0;
int main() {
    std::cin >> n;
    ss[0] = "Power";
    ss[1] = "Time";
    ss[2] = "Space";
    ss[3] = "Soul";
    ss[4] = "Reality";
    ss[5] = "Mind";
    for (int i = 0; i < n; i++) {
        std::cin >> s[i];
        if (s[i] == "purple") s[i] = "Power";
        if (s[i] == "green") s[i] = "Time";
        if (s[i] == "blue") s[i] = "Space";
        if (s[i] == "orange") s[i] = "Soul";
        if (s[i] == "red") s[i] = "Reality";
        if (s[i] == "yellow") s[i] = "Mind";
    }
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < n; j++) {
            if (ss[i] == s[j]) {
                goto ddd;
            }
        }
        all++;
        no[i] = 1;
    ddd:
        continue;
    }
    printf("%d\n", all);
    for (int i = 0; i < 6; i++)
        if (no[i]) std::cout << ss[i] << std::endl;
    return 0;
}