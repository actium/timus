#include <iostream>
#include <vector>

int main()
{
    unsigned w;
    std::cin >> w;

    size_t n;
    std::cin >> n;

    std::vector<unsigned> c(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> c[i];

    unsigned s = 0;
    for (const unsigned x : c)
        s += x;

    std::vector<unsigned> q(1 + s), p(1 + s);
    q[0] = 1;
    for (size_t i = 0; i < n; ++i) {
        for (unsigned x = s; x >= c[i]; --x) {
            if (q[x - c[i]] != 0) {
                q[x] += q[x - c[i]];
                if (p[x] == 0)
                    p[x] = 1 + i;
            }
        }
    }

    switch (q[w]) {
        case 0:
            std::cout << 0 << '\n';
            break;

        case 1:
            {
                std::vector<bool> v(n);
                while (w != 0) {
                    v[p[w]-1] = true;
                    w -= c[p[w]-1];
                }

                for (unsigned i = 1; i <= n; ++i) {
                    if (!v[i-1])
                        std::cout << i << ' ';
                }
            }
            break;

        default:
            std::cout << -1 << '\n';
            break;
    }

    return 0;
}
