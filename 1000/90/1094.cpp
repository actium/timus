#include <iostream>
#include <string>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::string s;
    std::getline(std::cin, s);

    std::string t(80, ' ');
    {
        unsigned x = 0;
        for (const char c : s) {
            if (c == '<') {
                x -= (x > 0);
                continue;
            }

            if (c != '>')
                t[x] = c;

            x = (x + 1) % 80;
        }
    }

    std::cout << t << '\n';

    return 0;
}
