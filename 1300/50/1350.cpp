#include <iostream>
#include <set>
#include <string>
#include <vector>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::set<std::string> p;
    for (size_t i = 0; i < n; ++i) {
        std::string s;
        std::cin >> s;

        p.insert(s);
    }

    size_t k;
    std::cin >> k;

    std::vector<std::vector<std::string>> b(k + 1);
    for (size_t i = 0; i <= k; ++i) {
        size_t q;
        std::cin >> q;

        b[i].resize(q);
        for (std::string& s : b[i])
            std::cin >> s;
    }

    size_t m;
    std::cin >> m;

    for (const std::string& s : b[0])
        p.erase(s);

    for (size_t i = 1; i <= k; ++i) {
        unsigned q = 0;
        for (const std::string& s : b[i])
            q += p.count(s);

        if (q == 0) {
            std::cout << "YES" << '\n';
        } else {
            std::cout << (p.size() - q < m ? "NO" : "MAYBE") << '\n';
        }
    }

    return 0;
}
