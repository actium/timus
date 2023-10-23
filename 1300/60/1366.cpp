#include <iostream>
#include <string>

class Integer {
public:
    explicit Integer(const std::string& value)
        : data_(value.rbegin(), value.rend())
    {}

    Integer& operator ++()
    {
        data_.push_back('0');
        for (size_t i = 0; ++data_[i] == '9' + 1; ++i)
            data_[i] = '0';

        if (data_.back() == '0')
            data_.pop_back();

        return *this;
    }

    Integer& operator --()
    {
        for (size_t i = 0; --data_[i] == '0' - 1; ++i)
            data_[i] = '9';

        return *this;
    }

    Integer& operator *=(const Integer& rhs)
    {
        const size_t n = data_.length(), m = rhs.data_.length();

        std::string product(n + m, '0');
        for (size_t i = 0; i < n; ++i) {
            const unsigned d1 = data_[i] - '0';

            for (size_t j = 0; j < m; ++j) {
                const unsigned d2 = rhs.data_[j] - '0';

                const unsigned c = product[i+j] - '0';
                const unsigned y = d1 * d2 + c;

                product[i+j] = '0' + y % 10;
                product[i+j+1] += y / 10;
            }
        }

        data_ = product;
        while (data_.size() > 1 && data_.back() == '0')
            data_.pop_back();

        return *this;
    }

private:
    std::string data_ = "0";

    friend std::ostream& operator <<(std::ostream& output, const Integer& v)
    {
        return output << std::string(v.data_.rbegin(), v.data_.rend());
    }

}; // class Integer

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n;
    std::cin >> n;

    Integer u("1"), v("0");
    for (unsigned i = 1; i < n; ++i) {
        v *= ++u;
        i % 2 == 0 ? --v : ++v;
    }

    std::cout << v << '\n';

    return 0;
}
