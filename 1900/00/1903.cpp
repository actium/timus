#include <iostream>
#include <utility>
#include <vector>

#include <cassert>
#include <cstdint>

constexpr unsigned M = 1'000'000'007;

namespace modular_arithmetic {

    template <unsigned M>
    class Integer {
        static_assert(M != 0, "modulus must be non-zero");

    public:
        static constexpr unsigned modulus = M;

        constexpr Integer() noexcept
            : residue_(0)
        {}

        constexpr Integer(long long value) noexcept
            : residue_(value < 0 ? value % modulus + modulus : value % modulus)
        {}

        [[nodiscard]] constexpr operator unsigned() const noexcept
        {
            return residue_;
        }

        constexpr Integer& operator +=(const Integer& rhs) noexcept
        {
            if (modulus - residue_ <= rhs.residue_)
                residue_ -= modulus;

            residue_ += rhs.residue_;
            return *this;
        }

        constexpr Integer& operator -=(const Integer& rhs) noexcept
        {
            if (residue_ < rhs.residue_)
                residue_ += modulus;

            residue_ -= rhs.residue_;
            return *this;
        }

        constexpr Integer& operator *=(const Integer& rhs) noexcept
        {
            residue_ = static_cast<uint64_t>(residue_) * rhs.residue_ % modulus;
            return *this;
        }

        constexpr Integer& operator /=(const Integer& rhs) noexcept
        {
            return *this *= rhs.invert();
        }

        constexpr Integer& operator ++() noexcept
        {
            if (++residue_ == modulus)
                residue_ = 0;

            return *this;
        }

        constexpr Integer& operator --() noexcept
        {
            if (residue_-- == 0)
                residue_ = modulus - 1;

            return *this;
        }

        constexpr void swap(Integer& other) noexcept
        {
            std::swap(residue_, other.residue_);
        }

        [[nodiscard]] constexpr Integer raise(long long power) const noexcept
        {
            if (power < 0) {
                assert(residue_ != 0);
                power = static_cast<uint64_t>(-power) * (modulus - 2) % (modulus - 1);
            }

            Integer result = 1;
            for (Integer base = *this; power != 0; power >>= 1) {
                if ((power & 1) != 0)
                    result *= base;

                base *= base;
            }
            return result;
        }

        // note: if modulus is a prime number, raise(modulus-2) also returns the inverse
        [[nodiscard]] constexpr Integer invert() const noexcept
        {
            assert(residue_ != 0);

            int64_t x = 1, y = 0, a = residue_, b = modulus;
            while (b != 0) {
                x = std::exchange(y, x - a / b * y);
                a = std::exchange(b, a % b);
            }
            assert(a == 1 && "inverse does not exist (residue is not coprime to modulus)");
            return x;
        }

    private:
        unsigned residue_;

    }; // class Integer<M>

    // returns true if the operands are congruent modulo M, false otherwise
    template <unsigned M>
    constexpr bool operator ==(const Integer<M>& lhs, const Integer<M>& rhs) noexcept
    {
        return static_cast<unsigned>(lhs) == static_cast<unsigned>(rhs);
    }

    // returns true if the operands are not congruent modulo M, false otherwise
    template <unsigned M>
    constexpr bool operator !=(const Integer<M>& lhs, const Integer<M>& rhs) noexcept
    {
        return static_cast<unsigned>(lhs) != static_cast<unsigned>(rhs);
    }

    template <unsigned M>
    constexpr Integer<M> operator +(const Integer<M>& number) noexcept
    {
        return number;
    }

    template <unsigned M>
    constexpr Integer<M> operator -(const Integer<M>& number) noexcept
    {
        return M - static_cast<unsigned>(number);
    }

    template <unsigned M>
    constexpr Integer<M> operator +(const Integer<M>& lhs, const Integer<M>& rhs) noexcept
    {
        return Integer<M>(lhs) += rhs;
    }

    template <typename T, unsigned M>
    constexpr Integer<M> operator +(const Integer<M>& lhs, T rhs) noexcept
    {
        return Integer<M>(lhs) += rhs;
    }

    template <typename T, unsigned M>
    constexpr Integer<M> operator +(T&& lhs, const Integer<M>& rhs) noexcept
    {
        return Integer<M>(lhs) += rhs;
    }

    template <unsigned M>
    constexpr Integer<M> operator -(const Integer<M>& lhs, const Integer<M>& rhs) noexcept
    {
        return Integer<M>(lhs) -= rhs;
    }

    template <typename T, unsigned M>
    constexpr Integer<M> operator -(const Integer<M>& lhs, T rhs) noexcept
    {
        return Integer<M>(lhs) -= rhs;
    }

    template <typename T, unsigned M>
    constexpr Integer<M> operator -(T&& lhs, const Integer<M>& rhs) noexcept
    {
        return Integer<M>(lhs) -= rhs;
    }

    template <unsigned M>
    constexpr Integer<M> operator *(const Integer<M>& lhs, const Integer<M>& rhs) noexcept
    {
        return Integer<M>(lhs) *= rhs;
    }

    template <typename T, unsigned M>
    constexpr Integer<M> operator *(const Integer<M>& lhs, T rhs) noexcept
    {
        return Integer<M>(lhs) *= rhs;
    }

    template <typename T, unsigned M>
    constexpr Integer<M> operator *(T&& lhs, const Integer<M>& rhs) noexcept
    {
        return Integer<M>(lhs) *= rhs;
    }

    template <unsigned M>
    constexpr Integer<M> operator /(const Integer<M>& lhs, const Integer<M>& rhs) noexcept
    {
        return Integer<M>(lhs) /= rhs;
    }

    template <typename T, unsigned M>
    constexpr Integer<M> operator /(const Integer<M>& lhs, T rhs) noexcept
    {
        return Integer<M>(lhs) /= rhs;
    }

    template <typename T, unsigned M>
    constexpr Integer<M> operator /(T&& lhs, const Integer<M>& rhs) noexcept
    {
        return Integer<M>(lhs) /= rhs;
    }

    template <unsigned M>
    constexpr Integer<M> operator ++(Integer<M>& number, int) noexcept
    {
        const Integer<M> s = number;
        ++number;
        return s;
    }

    template <unsigned M>
    constexpr Integer<M> operator --(Integer<M>& number, int) noexcept
    {
        const Integer<M> s = number;
        --number;
        return s;
    }

    template <unsigned M>
    std::istream& operator >>(std::istream& input, Integer<M>& number)
    {
        long long value;
        input >> value;
        number = value;
        return input;
    }

    template <unsigned M>
    std::ostream& operator <<(std::ostream& output, const Integer<M>& number)
    {
        return output << static_cast<unsigned>(number);
    }

} // namespace modular_arithmetic

using integer = modular_arithmetic::Integer<M>;

integer factorials[2][5001];

void precompute()
{
    factorials[0][0] = 1;
    for (unsigned i = 1; i <= 5000; ++i)
        factorials[0][i] = factorials[0][i-1] * i;

    factorials[1][5000] = factorials[0][5000].invert();
    for (unsigned i = 5000; i > 0; --i)
        factorials[1][i-1] = factorials[1][i] * i;
}

integer C(unsigned n, unsigned k)
{
    return factorials[0][n] * factorials[1][k] * factorials[1][n-k];
}

unsigned solve(const std::vector<unsigned>& c, unsigned t, unsigned k, unsigned x)
{
    const size_t n = c.size();

    precompute();

    unsigned p = 0, q = 0, r = 0;
    for (size_t i = 0; i < n; ++i) {
        p += (c[i] < c[k-1]);
        q += (i != k-1 && c[i] == c[k-1]);
        r += (c[i] > c[k-1]);
    }
    assert(p + q >= x - 1);

    integer count = 0;
    for (unsigned d = 0, max_d = std::min(p, x-1); d <= max_d; ++d) {
        for (unsigned e = 0, max_e = std::min(q, t-d-1); e <= max_e; ++e) {
            const unsigned f = d + e + 1, g = t - f;
            if (f < x || g > r)
                continue;

            count += C(p, d) * C(q, e) * C(r, g);
        }
    }
    return count;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, t;
    std::cin >> n >> t;

    std::vector<unsigned> c(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> c[i];

    unsigned k, x;
    std::cin >> k >> x;

    std::cout << solve(c, t, k, x) << '\n';

    return 0;
}
