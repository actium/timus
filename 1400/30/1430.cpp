#include <iostream>

unsigned solve(unsigned a, unsigned b, unsigned n)
{
    std::pair<unsigned, unsigned> v = { n, 0 };

    for (unsigned d = 0; d <= n; d += a) {
        const unsigned r = (n - d) % b;
        if (r < v.first) {
            v.first = r;
            v.second = d;
            continue;
        }

        if (d > a && d % b == a % b)
            break;
    }

    return v.second;
}

int main()
{
    unsigned a, b, n;
    std::cin >> a >> b >> n;

    if (a > b) {
        const unsigned d = solve(a, b, n);
        std::cout << d / a << ' ' << (n - d) / b << '\n';
    } else {
        const unsigned d = solve(b, a, n);
        std::cout << (n - d) / a << ' ' << d / b << '\n';
    }

    return 0;
}
