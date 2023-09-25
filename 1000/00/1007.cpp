#include <iostream>
#include <string>
#include <vector>

std::string solve(const std::string& s, size_t n)
{
    const size_t m = s.length();

    std::vector<unsigned> p(1 + m), q(1 + m);
    for (size_t i = 0; i < m; ++i) {
        p[i+1] = p[i] + (s[i] == '0' ? 0 : i + 1);
        q[i+1] = q[i] + (s[i] - '0');
    }

    if (n < m) {
        for (size_t x = 1; x <= m; ++x) {
            if ((p[x-1] + (p[m] - p[x]) - (q[m] - q[x])) % (n + 1) == 0)
                return s.substr(0, x - 1) + s.substr(x);
        }
    }

    if (n > m) {
        for (const char d : { '0', '1' }) {
            for (size_t x = 0; x <= m; ++x) {
                if ((p[x] + (x + 1) * (d - '0') + (p[m] - p[x]) + (q[m] - q[x])) % (n + 1) == 0)
                    return s.substr(0, x) + d + s.substr(x);
            }
        }
    }

    for (size_t x = 1; x <= m; ++x) {
        if (s[x-1] == '1' && (p[x-1] + p[m] - p[x]) % (n + 1) == 0)
            return s.substr(0, x - 1) + '0' + s.substr(x);
    }

    return s;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::string s;
    while (std::cin >> s)
        std::cout << solve(s, n) << '\n';

    return 0;
}
