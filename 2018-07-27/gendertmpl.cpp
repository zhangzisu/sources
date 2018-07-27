#include <cstdlib>
#include <iostream>
#include <set>
#include <string>
int n;
std::set<std::string> m, f;
std::string str;
std::string getName(std::string name) {
    if (m.count(name)) return "Male";
    if (f.count(name)) return "Female";
    return rand() & 1 ? "Male" : "Female";
}
int main() {
    // Code injection
    srand(19260817);
    std::ios::sync_with_stdio(false);
    std::cin >> n;
    while (n--) {
        std::cin >> str;
        std::cout << getName(str) << std::endl;
    }
    return 0;
}