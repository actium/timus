#include <iostream>
#include <vector>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n, k, m;
    std::cin >> n >> k >> m;

    for (unsigned i = 0; i < n; ++i)
        std::cout << 1 + i % k << '\n';

    bool v[100][100] = {};
    for (unsigned s = 0, t = 0; m != 0; s = (t + 1) % n, t = s) {
        do {
            t = (t + 1) % n;
        } while (t != s && (v[s][t] || t % k == s % k));

        if (t != s) {
            std::cout << 1 + s << ' ' << 1 + t << '\n';
            v[s][t] = true;
            v[t][s] = true;
            --m;
        }
    }

    return 0;
}
