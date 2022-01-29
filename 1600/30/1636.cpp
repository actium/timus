#include <iostream>

int main()
{
    unsigned t1, t2;
    std::cin >> t1 >> t2;

    unsigned p = 0;
    for (size_t i = 0; i < 10; ++i) {
        unsigned x;
        std::cin >> x;

        p += x;
    }

    std::cout << (t1 + p * 20 <= t2 ? "No chance." : "Dirty debug :(") << '\n';

    return 0;
}
