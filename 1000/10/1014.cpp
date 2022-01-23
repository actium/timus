#include <iostream>
#include <string>

int main()
{
    unsigned n;
    std::cin >> n;

    if (n == 0) {
        std::cout << 10 << '\n';
        return 0;
    }

    if (n == 1) {
        std::cout << 1 << '\n';
        return 0;
    }

    std::string q;
    for (unsigned i = 9; i > 1; --i) {
        while (n % i == 0) {
            q.push_back('0' + i);
            n /= i;
        }
    }

    if (n == 1) {
        while (!q.empty()) {
            std::cout << q.back();
            q.pop_back();
        }
        std::cout << '\n';
    } else {
        std::cout << -1 << '\n';
    }

    return 0;
}
