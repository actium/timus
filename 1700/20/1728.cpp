#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::vector<std::string> t = {
        "Efremov",
        "Kantorov",
    };

    const auto index = [&](const std::string& x) {
        size_t i = 0;
        while (i < t.size() && t[i] != x)
            ++i;

        if (i == t.size())
            t.push_back(x);

        return i;
    };

    size_t n;
    std::cin >> n;

    std::vector<std::vector<size_t>> c(n);
    for (size_t i = 0; i < n; ++i) {
        size_t k;
        std::cin >> k;

        c[i].reserve(k);
        for (size_t j = 0; j < k; ++j) {
            std::string x;
            std::cin >> x;

            c[i].push_back(index(x));
        }
    }

    unsigned re, rk;
    std::cin >> re >> rk;

    size_t m;
    std::cin >> m;

    std::pair<int, int> best_candidate = { -1, 0 };
    for (size_t i = 0; i < m; ++i) {
        std::string x;
        std::cin >> x;

        unsigned r;
        std::cin >> r;

        const size_t p = index(x);

        unsigned cr[3] = { 0, rk + r, re + rk + r };
        for (size_t i = 0; i < n; ++i) {
            size_t q = p ^ 1;
            for (const size_t u : c[i])
                q ^= u;

            if (q == 0)
                cr[c[i].size() - 1] = 0;
        }

        for (size_t j = 1; j < 3; ++j) {
            if (cr[j] > best_candidate.second) {
                best_candidate.first = p;
                best_candidate.second = cr[j];
            }
        }
    }

    if (best_candidate.first == -1) {
        std::cout << "Fail" << '\n';
    } else {
        std::cout << "Win" << '\n';
        std::cout << t[best_candidate.first] << '\n';
    }

    return 0;
}
