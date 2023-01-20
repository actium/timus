#include <iostream>
#include <map>
#include <vector>

int main()
{
    size_t n;
    std::cin >> n;

    std::map<std::string, std::vector<std::string>> v;
    for (size_t i = 0; i < n; ++i) {
        std::string p;
        std::cin >> p >> std::ws;

        std::string s;
        std::getline(std::cin, s);

        v[p].push_back(s);
    }

    unsigned k = 0, q = 0;
    for (const auto& e : v) {
        unsigned dk = 0, dq = 0;
        for (const std::string& s : e.second) {
            if (s == "CE")
                continue;

            dk |= (s != "AC" && s.back() == '7');
            dq |= (s == "AC" || s.back() >= '6');
        }
        k += dk, q += dq;
    }

    std::cout << k << ' ' << q << '\n';

    return 0;
}
