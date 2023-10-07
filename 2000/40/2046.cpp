#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> split(const std::string& s)
{
    std::vector<std::string> t;

    std::istringstream iss(s);
    for (std::string x; iss >> x; ) {
        if (t.empty() || t.back().size() + x.size() > 9) {
            t.push_back(x);
        } else {
            t.back().push_back(' ');
            t.back().append(x);
        }
    }

    for (std::string& x : t)
        x.resize(10, ' ');

    return t;
}

int main()
{
    size_t n;
    std::cin >> n >> std::ws;

    std::vector<std::string> s[4][3];
    for (size_t i = 0; i < n; ++i) {
        std::string c;
        std::getline(std::cin, c);

        std::string d;
        std::cin >> d;

        unsigned e;
        std::cin >> e >> std::ws;

        if (d == "Tuesday") {
            s[e-1][0] = split(c);
            continue;
        }
        if (d == "Thursday") {
            s[e-1][1] = split(c);
            continue;
        }
        if (d == "Saturday") {
            s[e-1][2] = split(c);
            continue;
        }
    }

    std::cout << "+----------+----------+----------+" << '\n';
    for (size_t i = 0; i < 4; ++i) {
        const size_t q = std::max(std::max(s[i][0].size(), s[i][1].size()), std::max<size_t>(s[i][2].size(), 1));
        for (size_t j = 0; j < q; ++j) {
            std::cout << '|';
            for (size_t k = 0; k < 3; ++k)
                std::cout << (j < s[i][k].size() ? s[i][k][j] : std::string(10, ' ')) << '|';

            std::cout << '\n';
        }

        std::cout << "+----------+----------+----------+" << '\n';
    }

    return 0;
}
