#include <iostream>
#include <vector>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t k;
    std::cin >> k;

    std::vector<int> a(k);
    for (size_t i = 0; i < k; ++i)
        std::cin >> a[i];

    bool v[11000 + 1 + 11000] = {};
    for (int x = -11000; x <= 11000; ++x) {
        int t = x;
        for (size_t i = 0; i < k; ++i)
            t = abs(t - a[i]);

        v[x + 11000] = (t <= 1);
    }

    std::vector<int> p;
    for (size_t i = 0; i <= 22000; ++i) {
        if (v[i] && p.size() % 2 == 0 || !v[i] && p.size() % 2 == 1)
            p.push_back(i - 11000);
    }

    std::cout << p.size() / 2 << '\n';
    for (size_t i = 0; i < p.size(); i += 2)
        std::cout << p[i] << ' ' << p[i+1] - 1 << '\n';

    return 0;
}
