#include <iostream>
#include <string>

int main()
{
    std::string s;
    for (std::string p = "aaaa"; s.length() < 1000000; ) {
        s += p.substr(1);

        size_t i = 3;
        while (p[i] == 'z')
            p[i--] = 'a';

        ++p[i];
    }

    std::cout << s.substr(0, 1000000) << '\n';

    return 0;
}
