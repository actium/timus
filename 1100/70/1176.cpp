#include <iostream>
#include <vector>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, a;
    std::cin >> n >> a;

    std::vector<std::vector<size_t>> p(n);
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            unsigned x;
            std::cin >> x;

            if (x == 0 && j != i)
                p[i].push_back(j);
        }
    }

    std::vector<size_t> q[2];
    q[0].push_back(a - 1);
    while (!q[0].empty()) {
        const size_t x = q[0].back();
        if (!p[x].empty()) {
            q[0].push_back(p[x].back());
            p[x].pop_back();
        } else {
            q[1].push_back(x);
            q[0].pop_back();
        }
    }

    for (size_t i = q[1].size() - 1; i > 0; --i)
        std::cout << 1 + q[1][i] << ' ' << 1 + q[1][i-1] << '\n';

    return 0;
}
