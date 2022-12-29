#include <iostream>

int main()
{
    long long i, fi, j, fj, n;
    std::cin >> i >> fi >> j >> fj >> n;

    if (j < i) {
        std::swap(i, j);
        std::swap(fi, fj);
    }

    long double a = 0, b = 1;
    for (int k = j - i; k > 1; --k) {
        const auto c = a + b;
        a = b;
        b = c;
    }

    long long fk = (fj - a * fi) / b;
    while (i < n) {
        const auto c = fi + fk;
        fi = fk;
        fk = c;
        ++i;
    }
    while (i > n) {
        const auto c = fk - fi;
        fk = fi;
        fi = c;
        --i;
    }

    std::cout << fi << '\n';

    return 0;
}
