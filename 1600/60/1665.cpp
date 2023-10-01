#include <iostream>

const char* solve(unsigned n)
{
    unsigned p = 0;
    while (n % 2 == 0) {
        ++p;
        n /= 2;
    }

    if (p % 2 == 0)
        return n == 1 ? "NO" : "YES";

    if (n == 1)
        return "YES";

    for (unsigned i = 3; i * i <= n; i += 2) {
        if (n % i == 0)
            return "YES";
    }

    return "NO";
}

void test_case()
{
    unsigned n;
    std::cin >> n;

    std::cout << solve(n) << '\n';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t t;
    std::cin >> t;

    while (t-- > 0)
        test_case();

    return 0;
}
