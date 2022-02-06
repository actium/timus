#include <iostream>
#include <string>

int main()
{
    bool b = true;
    for (std::string s; std::getline(std::cin, s); ) {
        for (char c : s) {
            if (c == '.' || c == '!' || c == '?')
                b = true;

            if (isalpha(c)) {
                c = (b ? toupper(c) : tolower(c));
                b = false;
            }

            std::cout << c;
        }
        std::cout << '\n';
    }

    return 0;
}
