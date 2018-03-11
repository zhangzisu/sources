#include <algorithm>
#include <iostream>
int n, a[100], max, min;
int main() {
    std::cin >> n >> a[1];
    max = min = 1;
    for (int i = 2; i <= n; i++) {
        std::cin >> a[i];
        if (a[i] > a[max]) max = i;
        if (a[i] < a[min]) min = i;
    }
    std::cout << n * 2 - 2 << std::endl;
    if (std::abs(a[max]) > std::abs(a[min])) {
        for (int i = 1; i <= n; i++)
            if (i != max) std::cout << max << ' ' << i << std::endl;
        for (int i = 2; i <= n; i++)
            std::cout << i - 1 << ' ' << i << std::endl;
    } else {
        for (int i = 1; i <= n; i++)
            if (i != min) std::cout << min << ' ' << i << std::endl;
        for (int i = n - 1; i > 0; i--)
            std::cout << i + 1 << ' ' << i << std::endl;
    }
    return 0;
}