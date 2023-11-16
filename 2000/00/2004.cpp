#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n;
    std::cin >> n;

    const unsigned k = 1 << n, m = k - 1;

    std::string s(k + n - 1, '0');
    {
        std::vector<bool> v(k);

        unsigned x = m - 1;
        for (auto it = s.begin() + n; it != s.end(); ++it) {
            v[x] ? ++x : ++*it;
            v[x] = true;

            x <<= 1;
            x &= m;
        }
    }

    std::cout << s << '\n';

    return 0;
}
