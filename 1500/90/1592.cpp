#include <algorithm>
#include <vector>

#include <cstdio>

void solve(std::vector<unsigned>& ts)
{
    const size_t n = ts.size();

    std::sort(ts.begin(), ts.end());

    unsigned s = 0;
    for (size_t i = 0; i < n; ++i)
        s += 43200 - ts[i];

    std::pair<size_t, unsigned> x = { 0, s };
    for (size_t i = 1; i < n; ++i) {
        s += (ts[i] - ts[i-1]) * n - 43200;
        if (s < x.second) {
            x.first = i;
            x.second = s;
        }
    }

    unsigned t = ts[x.first];
    if (t < 3600)
        t += 43200;

    printf("%u:%02u:%02u\n", t / 60 / 60, t / 60 % 60, t % 60);
}

int main()
{
    unsigned n;
    scanf("%u", &n);

    std::vector<unsigned> ts(n);
    for (unsigned i = 0; i < n; ++i) {
        unsigned h, m, s;
        scanf("%u:%02u:%02u", &h, &m, &s);

        ts[i] = (h % 12 * 60 + m) * 60 + s;
    }

    solve(ts);

    return 0;
}
