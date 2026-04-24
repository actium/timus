#include <iostream>
#include <string>
#include <vector>

#include <cassert>

constexpr unsigned M = 1'000'000'007;

template <typename T = std::string_view>
std::vector<unsigned> Z(T&& s)
{
    const size_t n = s.size();

    assert(n != 0 && "empty data");

    std::vector<unsigned> z(n);
    for (unsigned i = 1, j = 0; i < n; ++i) {
        if (i < j + z[j])
            z[i] = std::min(j + z[j] - i, z[i-j]);

        while (i + z[i] < n && s[z[i]] == s[i+z[i]])
            ++z[i];

        if (j + z[j] < i + z[i])
            j = i;
    }
    return z;
}

unsigned count_matches(const std::string& t, const std::string& p)
{
    const std::vector<unsigned> z = Z(p + '#' + t);

    unsigned k = 0;
    for (size_t n = p.size(), i = n + 1; i < z.size(); ++i)
        k += (z[i] >= n);

    return k;
}

struct Segment {
    size_t length;
    std::string prefix;
    std::string suffix;
    unsigned match_count;

    void normalize(size_t n)
    {
        if (prefix.length() > n)
            prefix = prefix.substr(0, n);

        if (suffix.length() > n)
            suffix = suffix.substr(suffix.length() - n);
    }

    static Segment create(const std::string& t, const std::string& p)
    {
        Segment s;
        {
            s.length = t.length();
            s.prefix = t;
            s.suffix = t;
            s.normalize(p.length());
            s.match_count = count_matches(t, p);
        }
        return s;
    }

    static Segment merge(const Segment& lhs, const Segment& rhs, const std::string& p)
    {
        const size_t n = p.length();

        Segment s;
        {
            s.length = std::min(lhs.length + rhs.length, 2 * n);
            s.prefix = lhs.prefix + rhs.prefix;
            s.suffix = lhs.suffix + rhs.suffix;
            s.normalize(n);
            s.match_count = lhs.match_count + rhs.match_count;

            const size_t du = (lhs.length >= n), dv = (rhs.length >= n);
            s.match_count += count_matches(lhs.suffix.substr(du) + rhs.prefix.substr(0, n-dv), p);
            s.match_count %= M;
        }
        return s;
    }
};

unsigned solve(const std::string& p, const std::string& a, const std::string& b, const std::vector<std::pair<unsigned, unsigned>>& c)
{
    std::vector<Segment> segments = {
        Segment::create(a, p),
        Segment::create(b, p),
    };

    for (const auto& [u, v] : c)
        segments.push_back(Segment::merge(segments[u-1], segments[v-1], p));

    return segments.back().match_count;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::string p;
    std::cin >> p;

    std::string a, b;
    std::cin >> a >> b;

    size_t m;
    std::cin >> m;

    std::vector<std::pair<unsigned, unsigned>> c(m);
    for (size_t i = 0; i < m; ++i)
        std::cin >> c[i].first >> c[i].second;

    std::cout << solve(p, a, b, c) << '\n';

    return 0;
}
