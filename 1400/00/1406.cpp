#include <iostream>
#include <string>

int main()
{
    std::string sn;
    std::cin >> sn;

    const size_t n = sn.length();

    unsigned k = 0, s = 0;
    while (k < n && (s == 0 || sn[n-1-k] == '9')) {
        s += sn[n-1-k] - '0';
        ++k;
    }

    if (k == n) {
        std::cout << -1 << '\n';
    } else {
        ++sn[n-1-k], --s;

        for (size_t i = 0; i < k; ++i) {
            const unsigned d = std::min<unsigned>(9, s);
            sn[n-1-i] = '0' + d;
            s -= d;
        }

        std::cout << sn << '\n';
    }

    return 0;
}
