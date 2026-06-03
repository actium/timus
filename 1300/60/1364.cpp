#include <iostream>
#include <vector>

constexpr int dr[4] = { 0, 1, 0, -1 };
constexpr int dc[4] = { 1, 0, -1, 0 };

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n, m;
    std::cin >> n >> m;

    unsigned tr, tc;
    std::cin >> tr >> tc;

    unsigned xr, xc;
    std::cin >> xr >> xc;

    unsigned t;
    std::cin >> t;

    std::vector<std::pair<unsigned, unsigned>> q;
    {
        std::vector<std::vector<bool>> v(1+n, std::vector<bool>(1+m));
        for (unsigned r = 1, c = 0, d = 0; r != tr || c != tc; ) {
            const auto nr = r + dr[d], nc = c + dc[d];
            if (nr == 0 || nr > n || nc == 0 || nc > m || v[nr][nc])
                d = (d + 1) % 4;

            r += dr[d];
            c += dc[d];

            q.emplace_back(r, c);
            v[r][c] = true;
        }
    }

    size_t p = 0;
    while (q[p].first != xr || q[p].second != xc)
        ++p;

    const size_t b = (p > t ? p - t : 0), e = (p + t < q.size() ? p + t + 1 : q.size());
    for (size_t i = b; i < e; ++i)
        std::cout << q[i].first << ' ' << q[i].second << '\n';

    return 0;
}
