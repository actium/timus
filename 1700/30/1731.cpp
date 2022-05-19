#include <iostream>

void print_range(unsigned x, unsigned k, unsigned p)
{
    for (unsigned i = 0; i < k; ++i) {
        std::cout << x << ' ';
        x += p;
    }
    std::cout << '\n';
}

int main()
{
    unsigned n, m;
    std::cin >> n >> m;

    print_range(1, n, 1);
    print_range(1 + n, m, n);

    return 0;
}
