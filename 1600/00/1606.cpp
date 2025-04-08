#include <algorithm>
#include <iostream>
#include <vector>

struct Point {
    unsigned i;
    unsigned x;
    unsigned y;
};

struct Solution {
    unsigned length = 1;
    unsigned index = 0;
    const Solution* parent = nullptr;
};

void solve(std::vector<Point>& p)
{
    const size_t n = p.size();

    std::sort(p.begin(), p.end(), [](const Point& lhs, const Point& rhs) {
        return lhs.y < rhs.y;
    });

    std::vector<Solution> s[2];
    for (size_t i = 0; i < 2; ++i)
        s[i].resize(n);

    for (size_t i = 1; i < n; ++i) {
        if (p[i-1].x < p[i].x) {
            s[0][i] = { s[1][i-1].length + 1, i, &s[1][i-1] };
            s[1][i] = s[1][i-1];
        } else {
            s[1][i] = { s[0][i-1].length + 1, i, &s[0][i-1] };
            s[0][i] = s[0][i-1];
        }
    }

    const Solution* x = (s[0][n-1].length > s[1][n-1].length ? &s[0][n-1] : &s[1][n-1]);

    std::cout << x->length << '\n';
    while (x != nullptr) {
        std::cout << p[x->index].i << ' ';
        x = x->parent;
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<Point> p(n);
    for (size_t i = 0; i < n; ++i) {
        p[i].i = i + 1;
        std::cin >> p[i].x >> p[i].y;
    }

    solve(p);

    return 0;
}
