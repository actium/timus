#include <iostream>
#include <string>

int main()
{
    std::string a, b;
    std::cin >> a >> b;

    const size_t n = a.length(), m = b.length();

    unsigned i = 0, j = 0, t = 0;
    for ( ; i < n && j < m; ++t) {
        const unsigned di = (a[i] != 'L' || b[j] == 'L');
        const unsigned dj = (b[j] != 'L' || a[i] == 'L');

        i += di;
        j += dj;
    }

    std::cout << t + (n - i) + (m - j) << '\n';

    return 0;
}
