#include <iostream>

int main()
{
    size_t n;
    std::cin >> n;

    unsigned f[3] = {};
    for (size_t i = 0; i < n; ++i) {
        unsigned x;
        std::cin >> x;

        ++f[x-1];
    }

    const auto test = [&] {
        if (f[0] * f[1] * f[2] != 0)
            return true;

        for (size_t x = 0; x < 3; ++x) {
            if (f[x] > 1 && f[(x+1)%3] > 1)
                return true;

            if (f[x] == 1 && n >= 6)
                return true;
        }

        return false;
    };

    std::cout << (test() ? "Yes" : "No") << '\n';

    return 0;
}
