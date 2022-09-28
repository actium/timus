#include <iostream>
#include <string>

int main()
{
    size_t n;
    std::cin >> n;

    std::string v(1 + n, '0');
    for (size_t i = 0; i < n; ++i) {
        unsigned a, b;
        std::cin >> a >> b;

        v[i+1] += a + b;
    }

    for (size_t i = n; i > 0; --i) {
        if (v[i] > '9') {
            v[i] -= 10;
            v[i-1] += 1;
        }
    }

    std::cout << (v[0] == '0' ? v.substr(1) : v) << '\n';

    return 0;
}
