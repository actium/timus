#include <iostream>

using integer = unsigned long long;

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n, m;
    std::cin >> n >> m;

    unsigned k = (--m == 0 ? 0 : __builtin_clz(1) - __builtin_clz(m) + 1);

    std::pair<integer, integer> L = { 0, 1 }, M = { 1, n - k }, R = { 1, n - k - 1 };
    while (k-- != 0) {
        if ((m & 1 << k) != 0) {
            L = M;
            M.first += R.first;
            M.second += R.second;
        } else {
            R = M;
            M.first += L.first;
            M.second += L.second;
        }
    }

    std::cout << M.first << ' ' << M.second << '\n';

    return 0;
}
