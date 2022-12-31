#include <iostream>

void solve(unsigned n)
{
    if (n * 6 > 100000) {
        std::cout << "TOO LONG" << '\n';
        return;
    }

    if (n == 1) {
        std::cout << 'a' << '\n';
        std::cout << 'b' << '\n';
        std::cout << 'c' << '\n';
        return;
    }

    const unsigned k = n / 3, r = n % 3;
    for (const char* p : {"abc", "acb", "bac", "bca", "cab", "cba"}) {
        for (unsigned i = 0; i < k; ++i)
            std::cout << p;
        for (unsigned i = 0; i < r; ++i)
            std::cout << p[i];
        std::cout << '\n';
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned n;
    std::cin >> n;

    solve(n);

    return 0;
}
