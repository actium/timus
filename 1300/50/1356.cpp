#include <algorithm>
#include <iostream>
#include <vector>

std::vector<unsigned> p;

bool is_prime(unsigned x) {
    if (x == 1)
        return false;

    if (std::binary_search(p.begin(), p.end(), x))
        return true;

    for (const unsigned q : p) {
        if (x % q == 0)
            return false;
    }
    return true;
}

void initialize()
{
    p.push_back(2);

    for (unsigned i = 3; i * i <= 1000000000; i += 2) {
        if (is_prime(i))
            p.push_back(i);
    }
}

void test_case()
{
    unsigned x;
    std::cin >> x;

    if (is_prime(x)) {
        std::cout << x << '\n';
        return;
    }

    for (const unsigned q : p) {
        if (q > x)
            break;

        if (is_prime(x - q)) {
            std::cout << q << ' ' << x - q << '\n';
            return;
        }
    }

    for (const unsigned q : p) {
        for (const unsigned r : p) {
            if (q + r > x)
                break;

            if (is_prime(x - q - r)) {
                std::cout << q << ' ' << r << ' ' << x - q - r << '\n';
                return;
            }
        }
    }
}

int main()
{
    initialize();

    size_t t;
    std::cin >> t;

    while (t-- > 0)
        test_case();

    return 0;
}
