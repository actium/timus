#include <iostream>
#include <string>

int main()
{
    std::string a;
    std::cin >> a;

    const char c = a.back(); a.pop_back();
    const unsigned r = std::stoi(a);

    if (r < 3) {
        switch (c) {
            case 'A': case 'D':
                std::cout << "window" << '\n';
                break;

            default:
                std::cout << "aisle" << '\n';
        }
    }
    if (r >= 3 && r <= 20) {
        switch (c) {
            case 'A': case 'F':
                std::cout << "window" << '\n';
                break;

            default:
                std::cout << "aisle" << '\n';
        }
    }
    if (r > 20) {
        switch (c) {
            case 'A': case 'K':
                std::cout << "window" << '\n';
                break;

            case 'C': case 'D': case 'G': case 'H':
                std::cout << "aisle" << '\n';
                break;

            default:
                std::cout << "neither" << '\n';
        }
    }

    return 0;
}
