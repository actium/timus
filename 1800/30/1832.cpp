#include <iostream>
#include <string>
#include <vector>

#include <cassert>

std::string solve(unsigned n)
{
    std::vector<unsigned> divisors;
    for (unsigned d = 1; d < n; ++d) {
        if (n % d == 0)
            divisors.push_back(d);
    }

    std::vector<unsigned> colors(1+n), options(1+n, 0x3FFFFFF);
    for (unsigned x = 1; x <= n; ++x) {
        assert(options[x] != 0);

        colors[x] = options[x] & -options[x];

        for (const unsigned d : divisors) {
            if (x + d <= n)
                options[x+d] &= ~colors[x];

            if (x <= d)
                options[x+n-d] &= ~colors[x];
        }
    }

    std::string s(n, 'a');
    for (unsigned x = 1; x <= n; ++x)
        s[x-1] += __builtin_ctz(colors[x]);

    return s;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n;
    std::cin >> n;

    std::cout << solve(n) << '\n';

    return 0;
}
