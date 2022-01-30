#include <iostream>
#include <string>

int main()
{
    unsigned h, w, n;
    std::cin >> h >> w >> n;

    unsigned c = 0, k = 0;
    while (n-- > 0) {
        std::string s;
        std::cin >> s;

        if (c < s.length()) {
            ++k;
            c = w;
        }

        c -= std::min<unsigned>(c, s.length() + 1);
    }

    std::cout << (k + h - 1) / h << '\n';

    return 0;
}
