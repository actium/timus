#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

unsigned solve(std::string& x, std::string& y)
{
    std::reverse(x.begin(), x.end());
    std::reverse(y.begin(), y.end());

    const size_t m = std::max(x.size(), y.size());
    x.resize(m, '0');
    y.resize(m, '0');

    std::vector<unsigned> z(m, static_cast<unsigned>(m));
    for (size_t i = m-1; i > 0; --i)
        z[i-1] = static_cast<unsigned>(x[i] == y[i] ? i : z[i]);

    unsigned k = 0;
    for (size_t i = 0; i < m; ++i) {
        if (x[i] == '1' && y[i] == '1')
            k = std::max<unsigned>(k, z[i] - i);
    }
    return 2 + k;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::string x, y;
    std::cin >> x >> y;

    std::cout << solve(x, y) << '\n';

    return 0;
}
