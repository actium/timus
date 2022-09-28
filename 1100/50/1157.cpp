#include <iostream>

int main()
{
    constexpr unsigned N = 10000;

    unsigned m, n, k;
    std::cin >> m >> n >> k;

    unsigned d[1 + N] = {};
    for (unsigned i = 1; i <= N; ++i) {
        for (unsigned j = i; j <= N; j += i)
            ++d[j];

        d[i] = (d[i] + 1) / 2;
    }

    unsigned l = k + 1;
    while (l <= N && (d[l] != n || d[l-k] != m))
        ++l;

    std::cout << (l <= N ? l : 0) << '\n';

    return 0;
}
