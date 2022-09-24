#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    size_t n;
    std::cin >> n;

    std::vector<std::vector<unsigned>> s(n, std::vector<unsigned>(3));
    for (size_t i = 0; i < n; ++i)
        std::cin >> s[i][0] >> s[i][1] >> s[i][2];

    std::sort(s.begin(), s.end());

    unsigned t = 0, d = 0;
    for (size_t i = 0; i < n; ++i) {
        if (t < s[i][0])
            t = s[i][0];

        t += s[i][1];

        if (s[i][2] < t)
            d = std::max(d, t - s[i][2]);
    }

    std::cout << d << '\n';

    return 0;
}
