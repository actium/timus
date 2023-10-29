#include <iostream>
#include <map>
#include <string>

#include <cmath>

unsigned input()
{
    std::string s;
    std::cin >> s;

    std::string t = s.substr(s.find('.') + 1);
    t.resize(3, '0');

    const unsigned d = std::stoi(t);
    return s[0] == '-' ? (1000 - d) % 1000 : d;
}

unsigned distance(const std::pair<unsigned, unsigned>& d)
{
    const unsigned dx = std::min(d.first, 1000 - d.first);
    const unsigned dy = std::min(d.second, 1000 - d.second);
    return dx * dx + dy * dy;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::map<std::pair<unsigned, unsigned>, unsigned> f;
    for (size_t i = 0; i < n; ++i) {
        const unsigned dx = input();
        const unsigned dy = input();

        ++f[std::make_pair(dx, dy)];
    }

    auto it = f.begin();
    for (auto jt = f.begin(); jt != f.end(); ++jt) {
        if (jt->second < it->second)
            continue;

        if (jt->second > it->second || distance(jt->first) < distance(it->first))
            it = jt;
    }

    printf("%u %.5f\n", it->second, sqrt(distance(it->first) / 1000000.0));

    return 0;
}
