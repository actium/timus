#include <algorithm>
#include <iostream>
#include <vector>

struct Friend {
    unsigned p;
    unsigned v;
};

struct Apartment {
    unsigned i;
    unsigned p;
    unsigned v;
};

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned p, v[2];
    std::cin >> p >> v[0] >> v[1];

    unsigned n;
    std::cin >> n;

    std::vector<Friend> f(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> f[i].p >> f[i].v;

    unsigned m;
    std::cin >> m;

    std::vector<Apartment> a[2];
    for (unsigned i = 0; i < m; ++i) {
        unsigned k, p, v;
        std::cin >> k >> p >> v;

        a[k-1].push_back({i, p, v});
    }

    std::pair<int, unsigned> o1 = { -1, 0 };
    for (size_t i = 0; i < 2; ++i) {
        const size_t k = a[i].size();

        std::sort(a[i].begin(), a[i].end(), [](const Apartment& x, const Apartment& y) {
            return std::make_pair(x.p, x.v) < std::make_pair(y.p, y.v);
        });

        for (size_t j = 0; j < k && a[i][j].p <= p; ++j) {
            const int c = v[i] + a[i][j].v;
            if (c > o1.first) {
                o1.first = c;
                o1.second = a[i][j].i + 1;
            }
        }
    }

    std::pair<int, std::pair<unsigned, unsigned>> o2 = { -1, {0, 0} };
    for (size_t i = 0; i < n; ++i) {
        const size_t k = a[1].size();

        for (size_t j = 0; j < k && a[1][j].p <= 2 * p && a[1][j].p <= 2 * f[i].p; ++j) {
            const int c = f[i].v + a[1][j].v;
            if (c > o2.first) {
                o2.first = c;
                o2.second.first = i + 1;
                o2.second.second = a[1][j].i + 1;
            }
        }
    }

    if (o1.first == -1 && o2.first == -1) {
        std::cout << "Forget about apartments. Live in the dormitory.";
    } else if (o1.first > o2.first) {
        std::cout << "You should rent the apartment #" << o1.second << " alone.";
    } else {
        std::cout << "You should rent the apartment #" << o2.second.second << " with the friend #" << o2.second.first << ".";
    }

    return 0;
}
