#include <iostream>
#include <string>

constexpr unsigned oo = ~0u;

void solve(const unsigned v[256])
{
    constexpr double R = 8.314;

    if ((v['V'] == oo || v['T'] == oo) && (v['n'] == 0 && v['p'] == 0)) {
        std::cout << "undefined" << '\n';
        return;
    }

    if ((v['V'] == oo || v['T'] == oo) && (v['n'] == 0 || v['p'] == 0)) {
        std::cout << "error" << '\n';
        return;
    }

    if (v['p'] == oo) {
        const double p = v['n'] * R * v['T'] / v['V'];
        std::cout << "p = " << std::fixed << p << '\n';
    }

    if (v['n'] == oo) {
        const double n = v['p'] * v['V'] / (R * v['T']);
        std::cout << "n = " << std::fixed << n << '\n';
    }

    if (v['V'] == oo) {
        const double V = v['n'] * R * v['T'] / v['p'];
        std::cout << "V = " << std::fixed << V << '\n';
    }

    if (v['T'] == oo) {
        const double T = v['p'] * v['V'] / (R * v['n']);
        std::cout << "T = " << std::fixed << T << '\n';
    }
}

int main()
{
    unsigned v[256] = {};

    v['p'] = v['n'] = v['V'] = v['T'] = oo;

    std::string s;
    for (size_t i = 0; i < 3; ++i) {
        std::getline(std::cin, s);

        const size_t x = s.find('=');
        v[s.front()] = std::stoi(s.substr(x + 1));
    }

    solve(v);

    return 0;
}
