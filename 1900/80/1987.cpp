#include <iostream>
#include <vector>

struct Segment {
    unsigned a;
    unsigned b;
};

bool operator <(const Segment& lhs, const Segment& rhs)
{
    return lhs.b - lhs.a < rhs.b  - rhs.a;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t n;
    std::cin >> n;

    std::vector<Segment> s(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> s[i].a >> s[i].b;

    size_t m;
    std::cin >> m;

    std::vector<size_t> t;
    for (size_t i = 0; m > 0; --m) {
        unsigned x;
        std::cin >> x;

        while (!t.empty() && s[t.back()].b < x)
            t.pop_back();

        for ( ; i < n && s[i].a <= x; ++i) {
            if (s[i].b < x)
                continue;

            if (t.empty() || s[i] < s[t.back()])
                t.push_back(i);
        }

        std::cout << int(t.empty() ? -1 : 1 + t.back()) << '\n';
    }

    return 0;
}
