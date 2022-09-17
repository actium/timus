#include <iostream>

int main()
{
    unsigned n, k;
    std::cin >> n >> k;

    unsigned s = 0;
    for (size_t i = 0; i < k; ++i) {
        unsigned x;
        std::cin >> x;
        
        s += n - x;
    }

    std::cout << n - std::min(n, s) << '\n';

    return 0;
}
