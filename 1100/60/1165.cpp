#include <iostream>
#include <string>

class Integer {
public:
    Integer() = default;

    Integer(unsigned long long value)
    {
        do {
            digits_.push_back('0' + value % 10);
            value /= 10;
        } while (value != 0);
    }

    Integer(const std::string& value)
        : digits_(value.rbegin(), value.rend())
    {
        normalize();
    }

    Integer& operator ++()
    {
        digits_.push_back('0');
        for (auto it = digits_.begin(); (*it)++ == '9'; *it++ = '0');
        normalize();
        return *this;
    }

    Integer& operator --()
    {
        for (auto it = digits_.begin(); (*it)-- == '0'; *it++ = '9');
        normalize();
        return *this;
    }

    Integer& operator +=(const Integer& rhs)
    {
        const size_t m = rhs.digits_.size(), n = std::max(digits_.size(), m);
        digits_.resize(n + 1, '0');

        for (size_t i = 0; i < m; ++i) {
            digits_[i] += rhs.digits_[i] - '0';

            if (digits_[i] > '9') {
                digits_[i] -= 10;
                ++digits_[i+1];
            }
        }

        for (size_t i = m; i < n && digits_[i] > '9'; ++i) {
            digits_[i] -= 10;
            ++digits_[i+1];
        }

        normalize();
        return *this;
    }

    Integer& operator -=(const Integer& rhs)
    {
        const size_t m = rhs.digits_.size(), n = digits_.size();

        for (size_t i = 0; i < m; ++i) {
            digits_[i] -= rhs.digits_[i] - '0';

            if (digits_[i] < '0') {
                digits_[i] += 10;
                --digits_[i+1];
            }
        }

        for (size_t i = m; i < n && digits_[i] < '0'; ++i) {
            digits_[i] += 10;
            --digits_[i+1];
        }

        normalize();
        return *this;
    }

    Integer& operator *=(unsigned rhs)
    {
        unsigned carry = 0;
        for (size_t i = 0; i < digits_.size() || carry != 0; ++i) {
            if (i == digits_.size())
                digits_.push_back('0');

            const auto p = carry + (digits_[i] - '0') * rhs;
            digits_[i] = '0' + p % 10;
            carry = p / 10;
        }

        normalize();
        return *this;
    }

    bool operator <(const Integer& rhs) const
    {
        if (digits_.size() != rhs.digits_.size())
            return digits_.size() < rhs.digits_.size();

        for (auto it = digits_.rbegin(), jt = rhs.digits_.rbegin(); it != digits_.rend(); ++it, ++jt) {
            if (*it != *jt)
                return *it < *jt;
        }
        return false;
    }

    explicit operator std::string() const
    {
        return std::string(digits_.rbegin(), digits_.rend());
    }

private:
    void normalize()
    {
        while (digits_.size() > 1 && digits_.back() == '0')
            digits_.pop_back();
    }

private:
    std::string digits_;

}; // class Integer

Integer operator -(Integer lhs, const Integer& rhs)
{
    return lhs -= rhs;
}

Integer starts[201];
Integer powers[201];

void initialize()
{
    starts[0] = 1;
    powers[0] = 1;
    for (size_t i = 1; i <= 200; ++i) {
        Integer d = powers[i-1];
        d *= 9 * i;

        starts[i] = starts[i-1];
        starts[i] += d;

        powers[i] = powers[i-1];
        powers[i] *= 10;
    }
}

bool check_prefix(const std::string& a, size_t prefix_length, Integer x)
{
    while (prefix_length > 0) {
        const std::string b = static_cast<std::string>(--x);

        const size_t m = b.length();
        if (m == 0)
            return false;

        if (prefix_length <= m)
            return b.compare(m - prefix_length, prefix_length, a, 0, prefix_length) == 0;

        if (a.compare(prefix_length - m, m, b, 0, m) != 0)
            return false;

        prefix_length -= m;
    }
    return true;
}

bool check_suffix(const std::string& a, size_t suffix_length, Integer x)
{
    while (suffix_length > 0) {
        const std::string b = static_cast<std::string>(++x);

        const size_t m = b.length();
        if (m >= suffix_length)
            return b.compare(0, suffix_length, a, a.size() - suffix_length, suffix_length) == 0;

        if (a.compare(a.size() - suffix_length, m, b, 0, m) != 0)
            return false;

        suffix_length -= m;
    }
    return true;
}

Integer locate(Integer x)
{
    const auto k = static_cast<std::string>(x).length();

    x -= powers[k-1];
    x *= k;
    x += starts[k-1];
    return x;
}

Integer solve(std::string a)
{
    const size_t n = a.size();

    if (a == std::string(n, '9')) {
        a[0] = '8';
        return ++locate(a);
    }

    Integer best = (a[0] == '0' ? ++locate("1" + a) : locate(a));
    for (size_t k = 1; k <= n; ++k) {
        for (size_t p = 0; p < k; ++p) {
            if (a[p] == '0')
                continue;

            if (p == 0) {
                const Integer x = a.substr(0, k);
                if (check_suffix(a, n - k, x))
                    best = std::min(best, locate(x));
            } else if (p + k <= n) {
                const Integer x = a.substr(p, k);
                if (check_prefix(a, p, x) && check_suffix(a, n - (p + k), x))
                    best = std::min(best, locate(x) - p);
            } else {
                std::string next = static_cast<std::string>(++Integer(a.substr(0, p)));
                if (next.size() < p)
                    next = std::string(p - next.size(), '0') + next;

                const std::string s = a.substr(p);
                for (size_t q = s.size(); q > 0; --q) {
                    if (s.compare(q, s.size() - q, next, 0, s.size() - q) != 0)
                        continue;

                    Integer x = s.substr(0, q) + next;
                    if (check_prefix(a, p, x))
                        best = std::min(best, locate(x) - p);
                }
            }
        }
    }
    return best;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    initialize();

    std::string a;
    std::cin >> a;

    std::cout << static_cast<std::string>(solve(a)) << '\n';

    return 0;
}
