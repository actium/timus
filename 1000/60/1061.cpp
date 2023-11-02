#include <iostream>
#include <string>

unsigned solve(const std::string& t, size_t k)
{
    const size_t n = t.length();
    if (n < k)
        return 0;

    unsigned s = 0, q = 0;

    const auto update = [&](size_t i, int f) {
        if (t[i] == '*') {
            q += f;
        } else {
            s += (t[i] - '0') * f;
        }
    };

    for (size_t i = 0; i < k; ++i)
        update(i, 1);

    std::pair<unsigned, unsigned> v = (q == 0 ? std::make_pair(1, s) : std::make_pair(0, ~0u));
    for (size_t i = k; i < n; ++i) {
        update(i, 1);
        update(i - k, -1);

        if (q == 0 && s < v.second)
            v = std::make_pair(i - k + 2, s);
    }

    return v.first;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, k;
    std::cin >> n >> k;

    std::string t;
    t.reserve(n);
    for (std::string s; std::getline(std::cin, s); t += s);

    std::cout << solve(t, k) << '\n';

    return 0;
}
