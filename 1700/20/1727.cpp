#include <iostream>
#include <vector>

unsigned f(unsigned x)
{
    unsigned s = 0;
    while (x != 0) {
        s += x % 10;
        x /= 10;
    }
    return s;
}

int main()
{
    unsigned n;
    std::cin >> n;

    std::vector<unsigned> s;
    for (unsigned x = 6999; x > 0; --x) {
        const unsigned p = f(x);
        if (p <= n) {
            s.push_back(x);
            n -= p;
        }
    }

    std::cout << s.size() << '\n';
    for (const unsigned x : s)
        std::cout << x << ' ';

    return 0;
}
