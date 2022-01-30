#include <iostream>
#include <unordered_set>

int main()
{
    unsigned n;
    std::cin >> n;

    std::unordered_set<unsigned long long> v;

    unsigned long long s = 0;
    for (unsigned i = 1, k = 0; k < n; ++i) {
        unsigned long long x = i - s % i;
        while (v.count(x) == 1)
            x += i;

        std::cout << x << ' ';
        s += x;
        v.insert(x);

        k += (x <= n);
    }

    return 0;
}
