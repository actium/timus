#include <iostream>

#include <cstdlib>
#include <ctime>

void test_case(unsigned n)
{
    for (unsigned i = n; i > 1; --i) {
        for (unsigned j = 2; j <= i; ++j)
            std::cout << '?' << ' ' << j-1 << ' ' << j << '\n';
    }

    const unsigned x = 1 + rand() % (n - 1);

    std::cout << '!' << ' ' << x << ' ' << x + 1 << '\n';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    srand(time(nullptr));

    unsigned m;
    std::cin >> m;

    for (unsigned i = 0; i < m; ++i)
        test_case(2 + i);

    return 0;
}
