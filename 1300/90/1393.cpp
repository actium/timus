#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class SuffixArray {
public:
    explicit SuffixArray(std::string_view s)
        : s_(s)
    {
        const size_t n = s_.length();

        p_.resize(n);
        for (size_t i = 0; i < n; ++i)
            p_[i] = i;

        std::sort(p_.begin(), p_.end(), [this](size_t i, size_t j) {
            return s_[i] < s_[j];
        });

        std::vector<unsigned> c(n);
        for (size_t i = 1; i < n; ++i)
            c[p_[i]] = c[p_[i-1]] + (s_[p_[i]] != s_[p_[i-1]]);

        for (unsigned k = 1; k < n; k *= 2) {
            for (size_t i = 0; i < n; ++i)
                p_[i] = (p_[i] - k + n) % n;

            sort(p_, c);

            std::vector<unsigned> q(n);
            {
                size_t x = p_[0];
                for (const size_t y : p_) {
                    q[y] = q[x] + (c[y] != c[x] || c[(y + k) % n] != c[(x + k) % n]);
                    x = y;
                }
            }
            c.swap(q);
        }

        lcp_.resize(n);
        for (size_t i = 0, k = 0; i < n - 1; ++i) {
            if (k > 0)
                --k;

            const size_t j = p_[c[i] - 1];
            while (s_[i+k] == s_[j+k])
                ++k;

            lcp_[c[i]] = k;
        }
    }

    double compute_average_lcp(unsigned n) const
    {
        double s = 0;
        for (size_t i = 1, z = 0; i < p_.size(); ++i) {
            if (p_[i] < n) {
                unsigned k = std::min(lcp_[i], n);
                for (size_t j = i-1; j > z; --j)
                    k = std::min(k, lcp_[j]);

                s += k;
                z = i;
            }
        }
        return s / (n - 1);
    }

private:
    static void sort(std::vector<size_t>& p, const std::vector<unsigned>& c)
    {
        const size_t n = p.size();

        std::vector<unsigned> x(1 + n);
        for (size_t i = 0; i < n; ++i)
            ++x[1 + c[i]];

        for (size_t i = 1; i < n; ++i)
            x[i] += x[i-1];

        std::vector<size_t> q(n);
        for (const size_t i : p)
            q[x[c[i]]++] = i;

        p.swap(q);
    }

private:
    const std::string_view s_;

    std::vector<size_t> p_;
    std::vector<unsigned> lcp_;

}; // class SuffixArray

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::string s;
    std::cin >> s;

    const std::string t = s + s + ' ';

    std::cout << std::fixed << SuffixArray(t).compute_average_lcp(n) << '\n';

    return 0;
}
