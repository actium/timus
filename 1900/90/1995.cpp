#include <iostream>
#include <vector>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, k;
    std::cin >> n >> k;

    unsigned p;
    std::cin >> p;

    std::vector<unsigned> w(n, 1);
    for (size_t i = n - k, x = i; i < n; ++i) {
        if (x * 100 < i * p)
            x = i;

        w[i] = w[x-1] + 1;
    }

    unsigned long long s = 0;
    for (const unsigned v : w)
        s += v;

    std::cout << s << '\n';
    for (const unsigned v : w)
        std::cout << v << ' ';

    return 0;
}
