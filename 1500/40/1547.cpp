#include <iostream>
#include <vector>

void increment(std::vector<unsigned>& v)
{
    for (size_t i = v.size()-1; ++v[i] == 26; v[i--] = 0);
}

void decrement(std::vector<unsigned>& v)
{
    for (size_t i = v.size()-1; v[i]-- == 0; v[i--] = 25);
}

std::pair<std::vector<unsigned>, unsigned> divide(const std::vector<unsigned>& lhs, unsigned rhs)
{
    std::pair<std::vector<unsigned>, unsigned> v = {};
    for (const unsigned d : lhs) {
        v.second = 26 * v.second + d;
        v.first.push_back(v.second / rhs);
        v.second %= rhs;
    }
    return v;
}

std::vector<unsigned> add(const std::vector<unsigned>& lhs, const std::vector<unsigned>& rhs)
{
    const size_t n = lhs.size();

    std::vector<unsigned> s(n);
    {
        unsigned c = 0;
        for (size_t i = n-1; ~i != 0; --i) {
            c += lhs[i] + rhs[i];
            s[i] = c % 26;
            c /= 26;
        }
    }
    return s;
}

std::vector<unsigned> subtract(const std::vector<unsigned>& lhs, const std::vector<unsigned>& rhs)
{
    const size_t n = lhs.size();

    std::vector<unsigned> d(n);
    {
        unsigned c = 0;
        for (size_t i = n-1; ~i != 0; --i) {
            if (lhs[i] < c + rhs[i]) {
                d[i] = 26 + lhs[i] - (c + rhs[i]);
                c = 1;
            } else {
                d[i] = lhs[i] - (c + rhs[i]);
                c = 0;
            }
        }
    }
    return d;
}

void solve(unsigned n, unsigned m)
{
    std::vector<std::vector<unsigned>> s(1 + n, std::vector<unsigned>(1 + n));
    for (size_t i = 1; i <= n; ++i)
        for (size_t j = n-i; j < n; s[i][j++] = 1);

    const auto decode = [&](std::vector<unsigned> r) {
        size_t x = n;
        while (s[x] > r)
            --x;

        r = subtract(r, s[x]);

        std::string p;
        for (size_t i = n-x; i <= n; ++i)
            p.push_back(char('a' + r[i]));

        return p;
    };

    const auto [p, r] = divide(s[n], m);

    std::vector<unsigned> b = s[0];
    for (unsigned i = 1; i <= m; ++i) {
        std::vector<unsigned> e = add(b, p);
        if (i <= r)
            increment(e);

        std::cout << decode(b) << '-';

        b = e;
        decrement(e);

        std::cout << decode(e) << '\n';
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n, m;
    std::cin >> n >> m;

    solve(n, m);

    return 0;
}
