#include <iostream>

int main()
{
    unsigned n, t, o;
    std::cin >> n >> t >> o;

    const unsigned f = o + t;
    for (unsigned i = 0; i < n; ++i) {
        unsigned s;
        std::cin >> s;

        std::cout << s + (f - s) / 2.0 << '\n';
    }

    return 0;
}
