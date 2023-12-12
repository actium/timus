#include <iostream>
#include <vector>

int main()
{
    unsigned n;
    std::cin >> n;

    unsigned k = 2;

    std::vector<unsigned> digits = { 5 };
    for (unsigned i = 1, c = 0; i < n; ++i) {
        digits.push_back(0);

        unsigned long long v = 0;
        for (unsigned j = 1; j < i / 2 + 1; ++j) {
            const unsigned q = i - j, t = digits[j] * digits[q];
            v += t + (j != q ? t : 0);
        }

        const unsigned t = v % 10 + c + (i > 1 ? digits[i-1] : digits[i-1] / 2);
        digits[i] = t % 10;
        c = v / 10 + t / 10;

        if (digits[i] != 0 && digits[i] != 9)
            ++k;
    }

    std::cout << n + k << '\n';

    return 0;
}
