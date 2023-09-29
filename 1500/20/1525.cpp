#include <iostream>
#include <string>

using integer = unsigned long long;

integer solve(unsigned n, unsigned m, unsigned k, const std::string& s)
{
    int lb[3] = {}, x[3] = {}, ub[3] = {};
    for (const char c : s) {
        switch (c) {
            case 'l':
                lb[0] = std::min(lb[0], --x[0]);
                break;
            case 'r':
                ub[0] = std::max(ub[0], ++x[0]);
                break;
            case 'u':
                lb[1] = std::min(lb[1], --x[1]);
                break;
            case 'd':
                ub[1] = std::max(ub[1], ++x[1]);
                break;
            case 'f':
                lb[2] = std::min(lb[2], --x[2]);
                break;
            case 'b':
                ub[2] = std::max(ub[2], ++x[2]);
                break;
        }
    }

    n -= std::min<unsigned>(ub[0] - lb[0], n - 1);
    m -= std::min<unsigned>(ub[1] - lb[1], m - 1);
    k -= std::min<unsigned>(ub[2] - lb[2], k - 1);

    return 1ull * n * m * k;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n, m, k;
    std::cin >> n >> m >> k;

    std::string s;
    std::cin >> s;

    std::cout << solve(n, m, k, s) << '\n';

    return 0;
}
