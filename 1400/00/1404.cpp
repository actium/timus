#include <iostream>
#include <string>

int main()
{
    std::string s;
    std::cin >> s;

    unsigned d = 5;
    for (char& c : s) {
        c -= d;
        if (c < 'a')
            c += 26;

        d = (d + c - 'a') % 26;
    }

    std::cout << s << '\n';

    return 0;
}
