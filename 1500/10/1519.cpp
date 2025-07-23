#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <cstdint>

using integer = unsigned long long;

struct Profile {
    unsigned size;
    uint64_t state;

    explicit Profile(unsigned size)
        : size(size)
        , state(0)
    {}

    Profile shift() const
    {
        Profile p(size);
        p.state = state << 4;
        return p;
    }

    unsigned get(unsigned x) const
    {
        return (state >> 4 * x) & 0xF;
    }

    void set(unsigned x, unsigned v)
    {
        state &= ~(integer(0xF) << 4 * x);
        state |= integer(v) << 4 * x;
    }

    void normalize()
    {
        unsigned t[16] = {}, next_id = 1;
        for (unsigned i = 0; i < size; ++i) {
            const unsigned x = get(i);
            if (x == 0)
                continue;

            if (t[x] == 0)
                t[x] = next_id++;

            set(i, t[x]);
        }
    }
};

bool operator <(const Profile& lhs, const Profile& rhs)
{
    return lhs.state < rhs.state;
}

integer solve(const std::vector<std::string>& grid)
{
    const std::pair<size_t, size_t> b = { grid.size(), grid[0].size() };

    std::pair<size_t, size_t> t = b;
    for (size_t i = 0; i < b.first; ++i) {
        for (size_t j = 0; j < b.second; ++j) {
            if (grid[i][j] == '.')
                t = { i, j };
        }
    }

    if (t == b)
        return 0;

    integer k = 0;

    std::map<Profile, integer> dp[2];
    dp[0][Profile(b.second+1)] = 1;
    for (size_t r = 0, q = 0; r < b.first; ++r) {
        const size_t nr = 1 - q;

        dp[nr].clear();
        for (const auto& [profile, count] : dp[q]) {
            if (profile.get(b.second) == 0) {
                Profile p = profile.shift();
                p.normalize();
                dp[nr][p] += count;
            }
        }

        q = nr;

        for (size_t c = 0; c < b.second; ++c) {
            const size_t nc = 1 - q;

            dp[nc].clear();
            for (const auto& [profile, count] : dp[q]) {
                const unsigned L = profile.get(c), U = profile.get(c+1);

                if (grid[r][c] == '*') {
                    if (L == 0 && U == 0)
                        dp[nc][profile] += count;

                    continue;
                }

                const bool in_last_empty_cell = (r == t.first && c == t.second);

                if (L == 0 && U == 0) {
                    if (!in_last_empty_cell) {
                        Profile p = profile;
                        p.set(c + 0, 15);
                        p.set(c + 1, 15);
                        p.normalize();
                        dp[nc][p] += count;
                    }
                    continue;
                }
                if (L == 0 || U == 0) {
                    const unsigned x = std::max(L, U);
                    if (c + 1 < b.second || !in_last_empty_cell) {
                        Profile p = profile;
                        p.set(c + 0, x);
                        p.set(c + 1, 0);
                        p.normalize();
                        dp[nc][p] += count;
                    }
                    if (r + 1 < b.first || !in_last_empty_cell) {
                        Profile p = profile;
                        p.set(c + 0, 0);
                        p.set(c + 1, x);
                        p.normalize();
                        dp[nc][p] += count;
                    }
                    continue;
                }
                if (L != U) {
                    Profile p = profile;
                    p.set(c + 0, 0);
                    p.set(c + 1, 0);
                    for (unsigned i = 0; i <= b.second; ++i) {
                        if (p.get(i) == U)
                            p.set(i, L);
                    }
                    p.normalize();
                    dp[nc][p] += count;
                    continue;
                }

                if (in_last_empty_cell) {
                    Profile p = profile;
                    p.set(c + 0, 0);
                    p.set(c + 1, 0);

                    bool is_hamiltonian = true;
                    for (unsigned i = 0; i <= b.second; ++i) {
                        if (p.get(i) != 0) {
                            is_hamiltonian = false;
                            break;
                        }
                    }

                    if (is_hamiltonian)
                        k += count;
                }
            }

            q = nc;
        }
    }

    return k;
}

int main()
{
    size_t n, m;
    std::cin >> n >> m;

    std::vector<std::string> grid(std::max(n, m), std::string(std::min(n, m), ' '));
    for (size_t i = 0; i < n; ++i) {
        std::string s;
        std::cin >> s;

        for (size_t j = 0; j < m; ++j)
            (n > m ? grid[i][j] : grid[j][i]) = s[j];
    }

    std::cout << solve(grid) << '\n';

    return 0;
}
