#include <iostream>
#include <string>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned n;
    std::cin >> n;

    std::string s;
    std::cin >> s;

    const size_t m = s.length();

    unsigned p[m], r[256];
    {
        unsigned f[256] = {};
        for (size_t i = 0; i < m; ++i) {
            const size_t x = s[i];
            p[i] = f[x]++;
        }

        unsigned x = 0;
        for (size_t i = 'A'; i <= 'z'; ++i) {
            r[i] = x;
            x += f[i];
        }
    }

    std::string z(m, ' ');
    {
        --n;

        for (size_t i = 1; i <= m; ++i) {
            z[m-i] = s[n];
            n = r[s[n]] + p[n];
        }
    }

    std::cout << z << '\n';

    return 0;
}
