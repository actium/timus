#include <iostream>
#include <vector>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n, d;
    std::cin >> n >> d;

    std::vector<unsigned> a(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> a[i];

    std::vector<unsigned> p(n);
    for (unsigned i = n, c = 0; i-- > 0; ) {
        p[i] = std::min(d, a[i] + c);

        if (a[i] + c > d)
            c = a[i] + c - d;
        else
            c = 0;
    }

    unsigned long long s = 0, t = 0;
    for (unsigned i = 0, c = 0; i < n; ++i) {
        s += p[i];
        t += c;

        if (p[i] + c > a[i])
            c = p[i] + c - a[i];
        else
            c = 0;
    }

    std::cout << s << ' ' << t << '\n';

    return 0;
}
