#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class Hasher {
public:
    Hasher(const std::vector<std::string>& g, unsigned p, unsigned q, unsigned mod)
        : mod_(mod)
    {
        const size_t n = g.size(), m = g[0].length();

        initialize_powers(powers_[0], p, n, mod_);
        initialize_powers(powers_[1], q, m, mod_);

        hashes_.resize(1 + n, std::vector<unsigned>(1 + m));
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < m; ++j) {
                const unsigned hp = 1ull * powers_[0][i] * powers_[1][j] % mod_ * (g[i][j] - 'a') % mod_;
                hashes_[i+1][j+1] = (hashes_[i][j+1] + hashes_[i+1][j] + mod_ - hashes_[i][j] + hp) % mod_;
            }
        }
    }

    unsigned operator ()(size_t i, size_t j, size_t size) const
    {
        const size_t n = powers_[0].size() - 1, m = powers_[1].size() - 1;
        const unsigned ph = (hashes_[i+size][j+size] + mod_ - hashes_[i][j+size] + mod_ - hashes_[i+size][j] + hashes_[i][j]) % mod_;
        const unsigned hp = 1ull * powers_[0][n-i] * powers_[1][m-j] % mod_;
        return 1ull * ph * hp % mod_;
    }

private:
    static void initialize_powers(std::vector<unsigned>& powers, unsigned base, unsigned count, unsigned mod)
    {
        powers.reserve(count + 1);
        for (powers.push_back(1); count != 0; --count)
            powers.push_back(1ull * powers.back() * base % mod);
    }

private:
    const unsigned mod_;

    std::vector<unsigned> powers_[2];
    std::vector<std::vector<unsigned>> hashes_;

}; // class Hasher

using position_t = std::pair<size_t, size_t>;

struct Candidate {
    position_t position;
    unsigned hash;
};

struct Solution {
    size_t size = 0;
    position_t positions[2];
};

void solve(const std::vector<std::string>& g)
{
    const size_t n = g.size(), m = g[0].length();

    const Hasher hasher(g, 13, 1597, 1000000007);

    const auto identical = [&g](const position_t& fp, const position_t& sp, size_t size) {
        const size_t fi = fp.first, fj = fp.second, si = sp.first, sj = sp.second;
        for (size_t di = 0; di < size; ++di) {
            for (size_t dj = 0; dj < size; ++dj) {
                if (g[fi+di][fj+dj] != g[si+di][sj+dj])
                    return false;
            }
        }
        return true;
    };

    const auto check = [&](size_t size, Solution& solution) {
        std::vector<Candidate> cs;
        for (size_t i = 0; i + size <= n; ++i) {
            for (size_t j = 0; j + size <= m; ++j)
                cs.push_back({ std::make_pair(i, j), hasher(i, j, size) });
        }

        std::sort(cs.begin(), cs.end(), [](const Candidate& lhs, const Candidate& rhs) {
            return lhs.hash < rhs.hash;
        });

        for (size_t i = 0, j = 1; j < cs.size(); ++j) {
            if (cs[j].hash == cs[i].hash) {
                for (size_t it = i; it < j; ++it) {
                    if (identical(cs[it].position, cs[j].position, size)) {
                        solution = { size, cs[it].position, cs[j].position };
                        return true;
                    }
                }
            } else {
                i = j;
            }
        }
        return false;
    };

    Solution solution;
    {
        size_t lb = 0, ub = std::min(n, m) + 1;
        while (lb + 1 < ub) {
            const size_t mid = (lb + ub) / 2;
            (check(mid, solution) ? lb : ub) = mid;
        }
    }

    std::cout << solution.size << '\n';
    if (solution.size != 0) {
        for (const auto [r, c] : solution.positions)
            std::cout << 1 + r << ' ' << 1 + c << '\n';
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, m;
    std::cin >> n >> m;

    std::vector<std::string> g(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> g[i];

    solve(g);

    return 0;
}
