#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>

#include <cassert>

struct Term {
    long long factor = 1;
    std::array<int, 26> powers = {};

    Term() = default;

    explicit Term(const std::string& t)
    {
        std::string s;
        for (const char c : t) {
            if (c == '+')
                continue;

            if (c == '-') {
                factor = -1;
                continue;
            }

            if (c != '*') {
                s.push_back(c);
                continue;
            }

            assert(!s.empty());
            if (isdigit(s[0])) {
                factor *= std::stoi(s);
            } else {
                assert(isalpha(s[0]));
                const unsigned x = s[0] - 'a';

                if (s.size() == 1) {
                    ++powers[x];
                } else {
                    assert(s.size() > 2 && s[1] == '^');
                    for (size_t i = 2; i < s.size(); ++i)
                        assert(isdigit(s[i]));

                    powers[x] += std::stoi(s.substr(2));
                }
            }

            s.clear();
        }
    }
};

bool operator <(const Term& lhs, const Term& rhs)
{
    int b = 0;
    for (size_t i = 0; i < 26; ++i)
        b += lhs.powers[i] - rhs.powers[i];

    return b != 0 ? b > 0 : lhs.powers > rhs.powers;
}

Term operator *(const Term& lhs, const Term& rhs)
{
    Term product;
    product.factor = lhs.factor * rhs.factor;
    if (product.factor != 0) {
        for (size_t i = 0; i < 26; ++i)
            product.powers[i] = lhs.powers[i] + rhs.powers[i];
    }
    return product;
}

std::vector<Term> parse_polynomial(const std::string& p)
{
    std::vector<Term> terms;

    std::string t;
    for (const char c : p) {
        if (isspace(c))
            continue;

        if ((c == '+' || c == '-') && !t.empty()) {
            t.push_back('*');
            terms.emplace_back(t);
            t.clear();
        }

        t.push_back(c);
    }

    return terms;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::vector<Term> ps[2];
    for (size_t i = 0; i < 2; ++i) {
        std::string buffer;
        std::getline(std::cin, buffer);

        buffer.push_back('+');
        ps[i] = parse_polynomial(buffer);
    }

    std::vector<Term> product;
    for (const auto& u : ps[0]) {
        for (const auto& v : ps[1])
            product.push_back(u * v);
    }

    std::sort(product.begin(), product.end());

    for (size_t i = 1; i < product.size(); ++i) {
        if (product[i].powers == product[i-1].powers) {
            product[i-1].factor += product[i].factor;
            product.erase(product.begin() + i--);
        }
    }

    std::string output;
    {
        const std::array<int, 26> e = {};

        for (auto& t : product) {
            if (t.factor == 0)
                continue;

            if (output.empty()) {
                if (t.factor < 0)
                    output.push_back('-');
            } else {
                output.push_back("-+"[t.factor > 0]);
                output.push_back(' ');
            }

            if (abs(t.factor) != 1 || t.powers == e)
                output.append(std::to_string(abs(t.factor)));

            for (size_t i = 0; i < 26; ++i) {
                if (t.powers[i] == 0)
                    continue;

                if (!output.empty() && isalnum(output.back()))
                    output.push_back('*');

                output.push_back(char('a' + i));

                if (t.powers[i] != 1) {
                    output.push_back('^');
                    output.append(std::to_string(t.powers[i]));
                }
            }

            output.push_back(' ');
        }

        if (output.empty())
            output.push_back('0');
    }

    std::cout << output << '\n';

    return 0;
}
