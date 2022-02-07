#include <iostream>
#include <string>
#include <vector>

constexpr const char* fn[4] = { "Slytherin", "Hufflepuff", "Gryffindor", "Ravenclaw" };

int main()
{
    size_t n;
    std::cin >> n;
    std::cin.ignore();

    std::vector<std::string> f[4];
    while (n-- > 0) {
        std::string a, b;
        std::getline(std::cin, a);
        std::getline(std::cin, b);

        switch (b[0]) {
            case 'S': f[0].push_back(std::move(a)); break;
            case 'H': f[1].push_back(std::move(a)); break;
            case 'G': f[2].push_back(std::move(a)); break;
            case 'R': f[3].push_back(std::move(a)); break;
        }
    }

    for (size_t i = 0; i < 4; ++i) {
        std::cout << fn[i] << ':' << '\n';
        for (const std::string& a : f[i])
            std::cout << a << '\n';

        std::cout << '\n';
    }

    return 0;
}
