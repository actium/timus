#include <iostream>
#include <numeric>

class RationalNumber {
public:
    explicit RationalNumber(const std::string& s)
    {
        const size_t u = s.find(' '), v = s.find('/');
        if (u == std::string::npos && v == std::string::npos) {
            numerator_ = std::stoll(s);
            denominator_ = 1;
        }
        if (v != std::string::npos) {
            numerator_ = std::stoll(s.substr(u + 1));
            denominator_ = std::stoll(s.substr(v + 1));
        }
        if (u != std::string::npos) {
            const long long integer = std::stoll(s);
            numerator_ += std::llabs(integer) * denominator_;
            if (integer < 0)
                numerator_ = -numerator_;
        }

        simplify();
    }

    RationalNumber& operator +=(const RationalNumber& rhs)
    {
        numerator_ = numerator_ * rhs.denominator_ + rhs.numerator_ * denominator_;
        denominator_ *= rhs.denominator_;
        simplify();
        return *this;
    }

    RationalNumber& operator -=(const RationalNumber& rhs)
    {
        numerator_ = numerator_ * rhs.denominator_ - rhs.numerator_ * denominator_;
        denominator_ *= rhs.denominator_;
        simplify();
        return *this;
    }

    RationalNumber& operator *=(const RationalNumber& rhs)
    {
        numerator_ *= rhs.numerator_;
        denominator_ *= rhs.denominator_;
        simplify();
        return *this;
    }

    RationalNumber& operator /=(const RationalNumber& rhs)
    {
        numerator_ *= rhs.denominator_;
        denominator_ *= rhs.numerator_;
        normalize();
        simplify();
        return *this;
    }

private:
    void normalize()
    {
        if (denominator_ < 0) {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }
    }

    void simplify()
    {
        const long long d = std::gcd(std::llabs(numerator_), denominator_);
        numerator_ /= d;
        denominator_ /= d;
    }

private:
    long long numerator_;
    long long denominator_;

    friend std::ostream& operator <<(std::ostream& output, const RationalNumber& v)
    {
        if (v.numerator_ < 0)
            output << '-';

        const char* separator = "";
        if (std::llabs(v.numerator_) >= v.denominator_ || v.numerator_ == 0) {
            output << std::llabs(v.numerator_) / v.denominator_;
            separator = " ";
        }

        if (v.numerator_ % v.denominator_ != 0)
            output << separator << std::llabs(v.numerator_) % v.denominator_ << '/' << v.denominator_;

        return output;
    }

}; // class RationalNumber

int main()
{
    std::string lhs, op, rhs;
    std::getline(std::cin, lhs);
    std::getline(std::cin, op);
    std::getline(std::cin, rhs);

    if (op == "+")
        std::cout << (RationalNumber(lhs) += RationalNumber(rhs)) << '\n';

    if (op == "-")
        std::cout << (RationalNumber(lhs) -= RationalNumber(rhs)) << '\n';

    if (op == "*")
        std::cout << (RationalNumber(lhs) *= RationalNumber(rhs)) << '\n';

    if (op == "/")
        std::cout << (RationalNumber(lhs) /= RationalNumber(rhs)) << '\n';

    return 0;
}
