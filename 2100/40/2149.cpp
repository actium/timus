#include <iostream>
#include <string>

int main()
{
    size_t n;
    std::cin >> n >> std::ws;

    std::string s[3];
    for (size_t i = 0; i < 3; ++i)
        std::getline(std::cin, s[i]);

    unsigned f[4] = {}, k = n / 2;
    for (size_t i = 0; i < k; ++i) {
        if (s[0][i*5] == '<') {
            ++f[0];
            ++f[2 + i%2];
        }
    }
    for (size_t i = k; i < n; ++i) {
        if (s[0][i*5] == '<') {
            ++f[1];
            ++f[2 + i%2];
        }
    }

    const unsigned c = std::min(k - f[0] + f[1], k - f[1] + f[0]);
    const unsigned d = std::min(k - f[2] + f[3], k - f[3] + f[2]);

    std::cout << std::min(c, d) << '\n';

    return 0;
}
