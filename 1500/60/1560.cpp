#include <array>
#include <iostream>
#include <utility>
#include <vector>

#include <cassert>
#include <cstdint>

namespace modular_arithmetic {

    unsigned modulus;

    class Integer {
    public:
        constexpr Integer() noexcept
            : residue_(0)
        {}

        Integer(long long value) noexcept
            : residue_(value < 0 ? value % modulus + modulus : value % modulus)
        {}

        [[nodiscard]] constexpr operator unsigned() const noexcept
        {
            return residue_;
        }

        Integer& operator +=(const Integer& rhs) noexcept
        {
            if (modulus - residue_ <= rhs.residue_)
                residue_ -= modulus;

            residue_ += rhs.residue_;
            return *this;
        }

        Integer& operator -=(const Integer& rhs) noexcept
        {
            if (residue_ < rhs.residue_)
                residue_ += modulus;

            residue_ -= rhs.residue_;
            return *this;
        }

        Integer& operator *=(const Integer& rhs) noexcept
        {
            residue_ = static_cast<uint64_t>(residue_) * rhs.residue_ % modulus;
            return *this;
        }

        Integer& operator /=(const Integer& rhs) noexcept
        {
            return *this *= rhs.invert();
        }

        [[nodiscard]] Integer invert() const noexcept
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

    }; // class Integer

    Integer operator -(const Integer& number) noexcept
    {
        return modulus - static_cast<unsigned>(number);
    }

    Integer operator +(const Integer& lhs, const Integer& rhs) noexcept
    {
        return Integer(lhs) += rhs;
    }

    Integer operator -(const Integer& lhs, const Integer& rhs) noexcept
    {
        return Integer(lhs) -= rhs;
    }

    Integer operator *(const Integer& lhs, const Integer& rhs) noexcept
    {
        return Integer(lhs) *= rhs;
    }

    Integer operator /(const Integer& lhs, const Integer& rhs) noexcept
    {
        return Integer(lhs) /= rhs;
    }

    std::ostream& operator <<(std::ostream& output, const Integer& number)
    {
        return output << static_cast<unsigned>(number);
    }

} // namespace modular_arithmetic

template <typename T>
class BinaryIndexedTree {
public:
    template <typename Iterator>
    BinaryIndexedTree(Iterator begin, Iterator end)
    {
        nodes_.emplace_back();
        nodes_.insert(nodes_.end(), begin, end);

        initialize();
    }

    template <typename U>
    void update(unsigned index, U delta)
    {
        for (++index; index < nodes_.size(); index += index & -index)
            nodes_[index] += delta;
    }

    // returns the sum of elements in the range [range_begin; range_end)
    T sum(unsigned range_begin, unsigned range_end) const
    {
        auto sum = T();
        while (range_end > range_begin) {
            sum += nodes_[range_end];
            range_end &= range_end - 1;
        }
        while (range_begin > range_end) {
            sum -= nodes_[range_begin];
            range_begin &= range_begin - 1;
        }
        return sum;
    }

private:
    void initialize()
    {
        for (unsigned i = 1; i < nodes_.size(); ++i) {
            if (const unsigned p = i + (i & -i); p < nodes_.size())
                nodes_[p] += nodes_[i];
        }
    }

private:
    std::vector<T> nodes_;

    static constexpr unsigned w = __builtin_clz(1);

}; // class BinaryIndexedTree<T>

struct Poly {
    using integer = modular_arithmetic::Integer;

    std::array<integer, 5> s = { 1 };

    Poly(int x = 0)
    {
        s[1] = x;
    }

    Poly& operator +=(const Poly& rhs)
    {
        std::array<integer, 5> ns = {};
        for (size_t i = 0; i < 5; ++i) {
            for (size_t j = 0; i + j < 5; ++j)
                ns[i+j] += s[i] * rhs.s[j];
        }
        s = ns;
        return *this;
    }

    Poly& operator -=(const Poly& rhs)
    {
        return *this += rhs.inverse();
    }

    Poly inverse() const
    {
        Poly v;
        v.s[1] = -s[1];
        v.s[2] = s[1] * s[1] - s[2];
        v.s[3] = -s[1] * s[1] * s[1] + integer(2) * s[1] * s[2] - s[3];
        v.s[4] = s[1] * s[1] * s[1] * s[1] - integer(3) * s[1] * s[1] * s[2] + integer(2) * s[1] * s[3] + s[2] * s[2] - s[4];
        return v;
    }
};

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, m;
    std::cin >> n >> m;

    std::cin >> modular_arithmetic::modulus;

    std::vector<int> a(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> a[i];

    std::vector<Poly> data(n);
    for (size_t i = 0; i < n; ++i)
        data[i] = a[i];

    BinaryIndexedTree<Poly> bit(data.begin(), data.end());
    for (size_t i = 0; i < m; ++i) {
        std::string type;
        std::cin >> type;

        if (type == "I") {
            unsigned index;
            std::cin >> index;

            int delta;
            std::cin >> delta;

            const auto old_value = a[index-1];
            a[index-1] += delta;

            Poly factor = a[index-1];
            factor -= old_value;
            bit.update(index-1, factor);
        } else {
            unsigned lb, ub, k;
            std::cin >> lb >> ub >> k;

            const auto poly = bit.sum(lb - 1, ub);
            for (size_t i = 0; i <= k; ++i)
                std::cout << poly.s[i] << " \n"[i==k];
        }
    }

    return 0;
}
