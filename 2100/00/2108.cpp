#include <bitset>
#include <iostream>
#include <vector>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, m;
    std::cin >> n >> m;

    std::vector<std::pair<std::bitset<1000>, std::bitset<1000>>> r(m);
    for (size_t i = 0; i < m; ++i)
        std::cin >> r[i].first >> r[i].second;

    std::bitset<1000> s;
    std::cin >> s;

    for (bool done = false; !done; ) {
        done = true;

        for (size_t i = 0; i < r.size(); ++i) {
            const auto q = s & r[i].first;
            if (q == r[i].first) {
                s |= r[i].second;
                r[i--] = std::move(r.back());
                r.pop_back();
                done = false;
            }
        }
    }

    std::cout << s.to_string().substr(1000 - n) << '\n';

    return 0;
}
