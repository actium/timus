#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>

class Index {
public:
    size_t operator [](const std::string& q)
    {
        const auto s = x_.emplace(q, v_.size());
        if (s.second)
            v_.push_back(s.first->first);

        return s.first->second;
    }

    std::string_view operator [](size_t q) const
    {
        return v_[q];
    }

private:
    std::vector<std::string_view> v_;
    std::map<std::string, size_t> x_;

}; // class Index

class BitVector {
public:
    bool is_empty() const
    {
        return data_.empty();
    }

    void set(size_t index)
    {
        const size_t i = index / 64, j = index % 64;
        if (data_.size() <= i)
            data_.resize(i + 1);

        data_[i] |= uint64_t(1) << j;
    }

    BitVector& operator &=(const BitVector& rhs)
    {
        const size_t k = std::min(data_.size(), rhs.data_.size());

        data_.resize(k);
        for (size_t i = 0; i < k; ++i)
            data_[i] &= rhs.data_[i];

        return *this;
    }

private:
    std::vector<uint64_t> data_;

    friend std::set<std::string_view> operator *(const BitVector& v, const Index& x)
    {
        std::set<std::string_view> s;
        for (size_t i = 0; i < v.data_.size(); ++i) {
            for (uint64_t u = v.data_[i]; u != 0; u -= u & -u)
                s.insert(x[i * 64 + __builtin_ctzll(u)]);
        }
        return s;
    }

}; // class BitVector

void parse(const std::string& s, Index& x, std::map<std::string, BitVector>& u)
{
    std::istringstream iss(s);

    std::string id;
    iss >> id;
    id.pop_back();

    BitVector& v = u[id];
    for (std::string q; iss >> q; v.set(x[q]));
}

void handle(const std::string& s, const Index& x, const std::map<std::string, BitVector>& u)
{
    BitVector v;

    std::istringstream iss(s);
    for (std::string q; iss >> q; ) {
        const auto it = u.find(q);

        if (v.is_empty())
            v = it->second;
        else
            v &= it->second;
    }

    const std::set<std::string_view> rs = v * x;
    if (!rs.empty()) {
        for (const std::string_view& q : rs)
            std::cout << q << ' ';
    } else {
        std::cout << "No solution.";
    }
    std::cout << '\n';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    Index x;

    size_t n;
    std::cin >> n >> std::ws;

    std::map<std::string, BitVector> u;
    for (size_t i = 0; i < n; ++i) {
        std::string s;
        std::getline(std::cin, s);

        parse(s, x, u);
    }

    size_t m;
    std::cin >> m >> std::ws;

    for (size_t i = 0; i < m; ++i) {
        std::string s;
        std::getline(std::cin, s);

        handle(s, x, u);
    }

    return 0;
}
