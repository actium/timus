#include <iostream>
#include <string>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string t;
    for (std::string s; std::getline(std::cin, s); t.push_back(' '))
        t += s;

    const auto count = [&](unsigned k) {
        unsigned d = 0, q = 0;
        for (const char c : t) {
            unsigned r = 36;
            if (c >= '0' && c <= '9')
                r = c - '0';
            if (c >= 'A' && c <= 'Z')
                r = c - 'A' + 10;

            if (r < k) {
                d = 1;
            } else {
                q += d;
                d = 0;
            }
        }
        return q;
    };

    std::pair<unsigned, unsigned> r = { 0, 0 };
    for (unsigned i = 2; i <= 36; ++i) {
        const unsigned q = count(i);
        if (q > r.second) {
            r.first = i;
            r.second = q;
        }
    }

    std::cout << r.first << ' ' << r.second << '\n';

    return 0;
}
