#include <iostream>
#include <string>

std::string multiply(std::string lhs, std::string rhs)
{
    const size_t n = lhs.length(), m = rhs.length();

    std::string product(n + m, '0');
    for (size_t i = 0; i < n; ++i) {
        const unsigned d1 = lhs[i] - '0';

        for (size_t j = 0; j < m; ++j) {
            const unsigned d2 = rhs[j] - '0';

            const unsigned c = product[i+j] - '0';
            const unsigned y = d1 * d2 + c;

            product[i+j] = '0' + y % 10;
            product[i+j+1] += y / 10;
        }
    }
    while (product.back() == '0')
        product.pop_back();

    return product;
}

std::string raise(std::string base, unsigned power)
{
    std::string value = "1";
    while (power != 0) {
        if (power % 2 == 1)
            value = multiply(value, base);

        base = multiply(base, base);
        power /= 2;
    }
    return value;
}

std::string reverse(const std::string& s)
{
    return std::string(s.crbegin(), s.crend());
}

int main()
{
    unsigned n;
    std::cin >> n;

    if (n < 5) {
        std::cout << n << '\n';
    } else {
        switch (n % 3) {
            case 0:
                std::cout << reverse(raise("3", n / 3)) << '\n';
                break;
            case 1:
                std::cout << reverse(multiply(raise("3", n / 3 - 1), "4")) << '\n';
                break;
            case 2:
                std::cout << reverse(multiply(raise("3", n / 3), "2")) << '\n';
                break;
        }
    }

    return 0;
}
