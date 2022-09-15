#include <iostream>
#include <vector>

int main()
{
    size_t n;
    std::cin >> n;

    std::vector<unsigned> a(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> a[i];

    unsigned x[2];
    std::cin >> x[0] >> x[1];

    std::vector<unsigned> ps(1+n);
    for (size_t i = 0; i < n; ++i)
        ps[1+i] = ps[i] + a[i];

    if (x[0] < x[1]) {
        const unsigned d = (x[1] - x[0]) / 2;
        const unsigned v1 = ps[x[0]+d], v2 = ps[n] - v1;
        std::cout << v1 << ' ' << v2 << '\n';
    }
    if (x[1] < x[0]) {
        const unsigned d = (x[0] - x[1] - 1) / 2;
        const unsigned v2 = ps[x[1]+d], v1 = ps[n] - v2;
        std::cout << v1 << ' ' << v2 << '\n';
    }
    if (x[0] == x[1]) {
        const unsigned v1 = std::max(ps[x[0]], ps[n] - ps[x[0]-1]), v2 = ps[n] - v1;
        std::cout << v1 << ' ' << v2 << '\n';
    }

    return 0;
}
