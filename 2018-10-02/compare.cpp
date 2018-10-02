#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
FILE *user = fopen("userout", "r");
FILE *output = fopen("output", "r");
char s1[100000000];
char s2[100000000];
int main() {
    while (1) {
        int r1 = fscanf(user, "%s", s1);
        int r2 = fscanf(output, "%s", s2);
        if (r1 == 1 && r2 == 1) {
            if (strcmp(s1, s2)) {
                puts("Wrong answer");
                return 1;
            }
        } else if (r1 == 1) {
            puts("User output too long");
            return 1;
        } else if (r2 == 1) {
            puts("User output too short");
            return 1;
        } else {
            break;
        }
    }
    return 0;
}