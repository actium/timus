#include <iostream>
#include <string>

unsigned solve(const std::string& s)
{
    int b = 0, x = 0, k = 0;
    for (const char c : s) {
        b += (c == '(' ? 1 : -1);

        if (b < x) {
            x = b;
            k = 0;
        }

        k += (b == x);
    }

    return b == 0 ? k : 0;
}

int main()
{
    std::string s;
    std::cin >> s;

    std::cout << solve(s) << '\n';

    return 0;
}
