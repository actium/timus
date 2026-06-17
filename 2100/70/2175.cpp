#include <iostream>
#include <map>
#include <vector>

using integer = unsigned long long;

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<integer> a(1+n);
    for (size_t i = 1; i <= n; ++i)
        std::cin >> a[i];

    std::map<unsigned, integer> s;
    s.emplace(1, a[1]);
    for (unsigned i = 2; i <= n; ++i) {
        if (a[i] > s.rbegin()->second)
            s.emplace(i, a[i]);
    }

    size_t q;
    std::cin >> q;

    while (q-- != 0) {
        unsigned p, d;
        std::cin >> p >> d;

        if (d != 0) {
            a[p] += d;

            auto it = s.lower_bound(p);
            if (it == s.begin() || std::prev(it)->second < a[p]) {
                while (it != s.end() && it->second <= a[p])
                    it = s.erase(it);

                s.emplace(p, a[p]);
            }
        }

        std::cout << s.size() << '\n';
    }

    return 0;
}
