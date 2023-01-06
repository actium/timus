#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

class Index {
public:
    unsigned size() const
    {
        return items_.size();
    }

    unsigned operator [](const std::string& item)
    {
        const auto it = ids_.find(item);
        if (it != ids_.end())
            return it->second;

        const unsigned id = items_.size();
        ids_.emplace(item, id);
        items_.push_back(item);
        return id;
    }

    const std::string& operator [](unsigned id) const
    {
        return items_[id];
    }

private:
    std::vector<std::string> items_;
    std::map<std::string, unsigned> ids_;

}; // class Index

void solve(const std::vector<unsigned>& s)
{
    const unsigned n = s.size();

    const auto check = [&](unsigned p) {
        std::set<unsigned> v;
        for (unsigned i = 0; i < n; i += p) {
            std::set<unsigned> c;
            for (unsigned j = 0; j < p; ++j) {
                if (s[i+j] == 0)
                    continue;

                if (v.count(s[i+j]) != 0)
                    return false;

                c.insert(s[i+j]);
                if (c.size() > 1)
                    return false;
            }

            v.insert(c.begin(), c.end());
        }
        return true;
    };

    for (unsigned i = 1; i <= n; ++i) {
        if (n % i == 0 && check(n / i))
            std::cout << i << ' ';
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    Index index;
    index["unknown"];

    unsigned n;
    std::cin >> n;

    std::vector<unsigned> sequence(n);

    bool wrong = false;
    for (unsigned i = 0; i < n; ++i) {
        std::string s;
        std::cin >> s;

        const unsigned x = index[s];
        if (x != 0 && x + 1 != index.size())
            wrong = true;

        sequence[i] = x;
    }

    if (wrong) {
        std::cout << "Igor is wrong." << '\n';
    } else {
        solve(sequence);
    }

    return 0;
}
