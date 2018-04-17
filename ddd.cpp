#include <bitset>
#include <cstdio>
#include <cstdlib>
#include <cstring>
int real = (500 - 1) / 64 + 1;
struct bitset {
    const static int T = 5001;
    unsigned long long val[T / 64 + 1];
    inline void clear() { memset(val, 0, sizeof(val)); }
    inline void set(int x) { val[x / 64] |= 1ULL << (x % 64); }
    inline void operator=(const bitset &b) {
        memcpy(val, b.val, sizeof(val));
    }
    inline friend bitset operator&(const bitset &a, const bitset &b) {
        bitset rt;
        for (int i = 0; i < real; i++) rt.val[i] = a.val[i] & b.val[i];
        return rt;
    }
    inline friend bitset operator|(const bitset &a, const bitset &b) {
        bitset rt;
        for (int i = 0; i < real; i++) rt.val[i] = a.val[i] | b.val[i];
        return rt;
    }
    inline friend bitset operator^(const bitset &a, const bitset &b) {
        bitset rt;
        for (int i = 0; i < real; i++) rt.val[i] = a.val[i] ^ b.val[i];
        return rt;
    }
    inline friend bool operator==(const bitset &a, const bitset &b) {
        for (int i = 0; i < real; i++)
            if (a.val[i] != b.val[i]) return 0;
        return 1;
    }
    inline int count() {
        int ret = 0;
        for (int i = 0; i < real; i++) ret += popcount(val[i]);
        return ret;
    }
    inline bool none() {
        for (int i = 0; i < real; i++)
            if (val[i]) return 0;
        return 1;
    }
    inline bitset() { this->clear(); }
} a, c;
std::bitset<500> b, d;

int main() {
    // for (int i = 0; i < 500; i++)
    //     if (rand() % 2) a.set(i), b.set(i);
    int x;
    while (1) {
        switch (rand() % 4) {
            case 0:
                x = rand() % 500;
                a.set(x);
                b.set(x);
                printf("BOTH SET %d\n", x);
                break;
            case 1:
                //a = a ^ c;
                //b = b ^ d;
                break;
            case 2:
                //a = a ^ a;
                //b = b ^ b;
                break;
            case 3:
                //a = a & c;
                //b = b & d;
                break;
        }
        if (a.count() != b.count()) {
            printf("a=%d, b=%u\n", a.count(), b.count());
            return 0;
        }
    }
    return 0;
}