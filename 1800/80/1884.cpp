#include <algorithm>
#include <iostream>
#include <vector>

double solve(std::vector<unsigned>& dl, std::vector<unsigned>& dr)
{
    std::sort(dl.begin(), dl.end(), std::greater<unsigned>());
    std::sort(dr.begin(), dr.end(), std::greater<unsigned>());

    unsigned t = 0;
    while (dl.size() + dr.size() != 0) {
        if (!dl.empty() && t >= (dl.back() + 5) * 9) {
            dl.pop_back();
            continue;
        }
        if (!dl.empty() && t + 72 > dl.back() * 9) {
            t = (dl.back() + 5) * 9;
            dl.pop_back();
            continue;
        }
        if (!dr.empty() && t + 72 >= (dr.back() + 5) * 9) {
            dr.pop_back();
            continue;
        }
        if (!dr.empty() && t + 144 > dr.back() * 9) {
            t = (dr.back() - 3) * 9;
            dr.pop_back();
            continue;
        }
        break;
    }
    return t / 50.0;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<unsigned> dl(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> dl[i];

    size_t m;
    std::cin >> m;

    std::vector<unsigned> dr(m);
    for (size_t i = 0; i < m; ++i)
        std::cin >> dr[i];

    std::cout << std::fixed << solve(dl, dr) << '\n';

    return 0;
}
