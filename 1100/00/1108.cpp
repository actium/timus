#include <iostream>
#include <string>

std::string increment(std::string x)
{
    x.push_back('0');
    for (size_t i = 0; ++x[i] == '9' + 1; ++i)
        x[i] = '0';

    if (x.back() == '0')
        x.pop_back();

    return x;
}

std::string decrement(std::string x)
{
    for (size_t i = 0; --x[i] == '0' - 1; ++i)
        x[i] = '9';

    return x;
}

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

std::string reverse(const std::string& s)
{
    return std::string(s.crbegin(), s.crend());
}

int main()
{
    unsigned n;
    std::cin >> n;

    std::string a = "2";
    while (--n != 0) {
        std::cout << reverse(a) << '\n';
        a = increment(multiply(a, decrement(a)));
    }
    std::cout << reverse(a) << '\n';

    return 0;
}
