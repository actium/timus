#include <iostream>
#include <map>
#include <string>

constexpr std::string_view t[3] = {
    "Slideshow",
    "So-so",
    "Perfect",
};

const std::string_view& evaluate(unsigned w, unsigned h, const std::map<unsigned, unsigned>& d, unsigned p)
{
    unsigned long long x = w * h;
    for (auto it = d.rbegin(); it != d.rend(); ++it) {
        for (unsigned j = 0; j < it->second; ++j) {
            x *= it->first;

            if (p < 10 * x)
                return t[0];
        }
    }

    return p < 10 * x ? t[0] : p < 60 * x ? t[1] : t[2];
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::map<std::string, unsigned> options;
    std::map<unsigned, unsigned> d;
    for (size_t i = 0; i < n; ++i) {
        std::string s;
        std::cin >> s;

        unsigned k;
        std::cin >> k;

        options[s] = k;
        ++d[k];
    }

    unsigned w, h, p;
    std::cin >> w >> h >> p;

    size_t m;
    std::cin >> m;

    std::cout << evaluate(w, h, d, p) << '\n';

    for (size_t i = 0; i < m; ++i) {
        std::string x;
        std::cin >> x;

        if (x[0] == 'R') {
            std::cin >> w >> h;
        } else {
            std::string s;
            std::cin >> s;

            x[1] == 'n' ? ++d[options[s]] : --d[options[s]];
        }

        std::cout << evaluate(w, h, d, p) << '\n';
    }

    return 0;
}
