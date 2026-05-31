#include <array>
#include <iostream>
#include <vector>

constexpr unsigned oo = ~0u;

struct Segment {
    unsigned s;
    unsigned t;
};

std::istream& operator >>(std::istream& input, Segment& segment)
{
    return input >> segment.s >> segment.t;
}

unsigned solve(const std::vector<std::pair<Segment, Segment>>& exams, const std::vector<Segment>& trips)
{
    const size_t n = exams.size(), m = trips.size();

    std::vector<unsigned> c[4];
    for (size_t i = 0; i < 4; ++i)
        c[i].resize(n);

    for (size_t i = 1, j = 0; i < n; ++i) {
        while (j > 0 && trips[j].s > exams[i-1].first.t)
            --j;

        for ( ; j < m && trips[j].t < exams[i].second.s; ++j) {
            c[0][i] += (trips[j].s > exams[i-1].first.t && trips[j].t < exams[i].first.s);
            c[1][i] += (trips[j].s > exams[i-1].first.t && trips[j].t < exams[i].second.s);
            c[2][i] += (trips[j].s > exams[i-1].second.t && trips[j].t < exams[i].first.s);
            c[3][i] += (trips[j].s > exams[i-1].second.t && trips[j].t < exams[i].second.s);
        }
    }

    std::array<unsigned, 2> dp = {};
    for (size_t i = 1; i < n; ++i) {
        dp = {
            std::max(dp[0] + c[0][i], dp[1] + c[2][i]),
            std::max(dp[0] + c[1][i], dp[1] + c[3][i]),
        };
    }
    return std::max(dp[0], dp[1]);
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, m;
    std::cin >> n >> m;

    std::vector<std::pair<Segment, Segment>> exams(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> exams[i].first >> exams[i].second;

    std::vector<Segment> trips(m);
    for (size_t i = 0; i < m; ++i)
        std::cin >> trips[i];

    exams.insert(exams.begin(), std::make_pair(Segment { 0, 0 }, Segment { 0, 0 }));
    exams.insert(exams.end(), std::make_pair(Segment { oo, oo }, Segment { oo, oo }));

    std::cout << solve(exams, trips) << '\n';

    return 0;
}
