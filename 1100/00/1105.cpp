#include <algorithm>
#include <iostream>
#include <vector>

void answer(const std::vector<size_t>& v)
{
    std::cout << v.size() << '\n';

    for (const auto x : v)
        std::cout << 1+x << '\n';
}

std::vector<size_t> select(const std::vector<size_t>& cs, size_t b)
{
    std::vector<size_t> s;
    for (size_t i = b; i < cs.size(); i += 2)
        s.push_back(cs[i]);

    return s;
}

bool check(double s, double t, const std::vector<std::pair<double, double>>& w, const std::vector<size_t>& cs)
{
    std::vector<std::pair<double, int>> events;
    events.emplace_back(s, 0);
    for (const size_t x : cs) {
        events.emplace_back(w[x].first, 1);
        events.emplace_back(w[x].second, -1);
    }
    events.emplace_back(t, 0);

    std::sort(events.begin(), events.end());

    double time = s, coverage = 0;
    {
        unsigned k = 0;
        for (const auto& e : events) {
            if (k == 1)
                coverage += e.first - time;

            time = e.first;
            k += e.second;
        }
    }
    return 3 * coverage >= 2 * (t - s);
}

void solve(double s, double t, const std::vector<std::pair<double, double>>& w)
{
    const size_t n = w.size();

    std::vector<size_t> p(n);
    for (size_t i = 0; i < n; ++i)
        p[i] = i;

    std::sort(p.begin(), p.end(), [&](size_t i, size_t j) {
        return w[i] < w[j];
    });

    std::vector<size_t> cs;
    {
        double b = s;

        std::pair<double, size_t> x = { s, n };
        for (const size_t i : p) {
            if (w[i].first > b) {
                cs.push_back(x.second);
                b = x.first;
            }
            x = std::max(x, std::make_pair(w[i].second, i));
        }
        if (cs.empty() || w[cs.back()].second < t)
            cs.push_back(x.second);
    }

    if (const std::vector<size_t> subset = select(cs, 0); check(s, t, w, subset))
        return answer(subset);

    if (const std::vector<size_t> subset = select(cs, 1); check(s, t, w, subset))
        return answer(subset);

    answer(cs);
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    double s, t;
    std::cin >> s >> t;

    size_t n;
    std::cin >> n;

    std::vector<std::pair<double, double>> w(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> w[i].first >> w[i].second;

    solve(s, t, w);

    return 0;
}
