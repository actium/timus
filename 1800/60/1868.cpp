#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::string s[12];
    for (std::string& x : s)
        std::cin >> x;

    size_t n;
    std::cin >> n;

    std::vector<unsigned> f(n);
    for (size_t i = 0; i < n; ++i) {
        size_t k;
        for (std::cin >> k; k != 0; --k) {
            std::string c, d, e;
            std::cin >> c >> d >> e;

            const auto it = std::find(std::cbegin(s), std::cend(s), c);
            if (it == std::cend(s))
                continue;

            const size_t r = std::distance(std::cbegin(s), it);
            if (e == "gold" && r >= 0 && r < 4)
                ++f[i];
            if (e == "silver" && r >= 4 && r < 8)
                ++f[i];
            if (e == "bronze" && r >= 8 && r < 12)
                ++f[i];
        }
    }

    std::sort(f.begin(), f.end());
    
    std::cout << std::count(f.cbegin(), f.cend(), f.back()) * 5 << '\n';

    return 0;
}
