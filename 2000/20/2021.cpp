#include <iostream>
#include <vector>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<size_t> a[7];
    for (size_t i = 0; i < n; ++i) {
        unsigned x;
        std::cin >> x;

        a[x].push_back(i);
    }

    std::vector<size_t> b[7];
    for (size_t i = 0; i < n; ++i) {
        unsigned x;
        std::cin >> x;

        b[x].push_back(i);
    }

    unsigned v[2] = {};
    for (unsigned i = 1; i <= 6; ++i) {
        v[0] += i * a[i].size();
        v[1] += i * b[i].size();
    }

    int i = 0, di = +1, j = 6, dj = -1;
    if (v[0] < v[1]) {
        std::swap(i, j);
        std::swap(di, dj);
    }

    for (size_t k = n; k > 0; --k) {
        while (a[i].empty())
            i += di;

        while (b[j].empty())
            j += dj;

        std::cout << 1 + a[i].back() << ' ' << 1 + b[j].back() << '\n';
        a[i].pop_back();
        b[j].pop_back();
    }

    return 0;
}
