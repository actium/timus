#include <iostream>
#include <vector>

void solve(unsigned n)
{
    std::vector<std::vector<unsigned>> flags = { { n }, { n } };

    unsigned k = 2;
    for (unsigned c = n - 1; c >= k; ++k) {
        flags.emplace_back();

        for (size_t i = 0; i < k; ++i) {
            flags[i].push_back(c);
            flags[k].push_back(c);
            --c;
        }
    }

    std::cout << k << '\n';
    for (const std::vector<unsigned>& f : flags) {
        std::cout << f.size();
        for (const unsigned c : f)
            std::cout << ' ' << c;

        std::cout << '\n';
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n;
    std::cin >> n;

    solve(n);

    return 0;
}
