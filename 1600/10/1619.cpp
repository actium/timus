#include <iostream>

void test_case()
{
    unsigned k, m;
    std::cin >> k >> m;

    std::cout << std::fixed << (m <= k ? 1 - m / (k + 1.0) : 0.0) << '\n';
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
