#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

struct Sphere {
    int x;
    int y;
    int z;
    unsigned r;
};

bool in_cluster(const Sphere& s, const Sphere& t)
{
    const int dx = s.x - t.x, dy = s.y - t.y, dz = s.z - t.z;

    return dx * dx + dy * dy + dz * dz < (s.r + t.r) * (s.r + t.r);
}

void solve(const std::vector<Sphere>& s)
{
    const size_t k = s.size();

    std::vector<size_t> r(k);
    for (size_t i = 0; i < k; ++i)
        r[i] = i;

    const auto resolve = [&](size_t x) {
        while (x != r[x])
            x = std::exchange(r[x], r[r[x]]);

        return x;
    };

    for (size_t i = 1; i < k; ++i) {
        for (size_t j = 0; j < i; ++j) {
            if (in_cluster(s[i], s[j]))
                r[resolve(i)] = resolve(j);
        }
    }

    std::vector<std::vector<size_t>> c(k);
    for (size_t i = 0; i < k; ++i)
        c[resolve(i)].push_back(i);

    std::sort(c.begin(), c.end());

    for (const std::vector<size_t>& v : c) {
        if (v.empty())
            continue;

        std::cout << v[0];
        for (size_t i = 1; i < v.size(); ++i)
            std::cout << ", " << v[i];
        std::cout << '\n';
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t k;
    std::cin >> k;

    std::vector<Sphere> s(k);
    for (size_t i = 0; i < k; ++i)
        std::cin >> s[i].x >> s[i].y >> s[i].z >> s[i].r;

    solve(s);

    return 0;
}