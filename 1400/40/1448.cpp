#include <iostream>
#include <string>

int main()
{
    unsigned n, b;
    std::cin >> n >> b;

    std::string s(n, '0');
    {
        unsigned k = 0;
        for (size_t i = 0; i < n; ++i) {
            if ((i + 1) * b > 100 * k) {
                ++s[i];
                ++k;
            }
        }
    }
    std::cout << s << '\n';

    return 0;
}
