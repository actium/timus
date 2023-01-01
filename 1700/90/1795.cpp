#include <iostream>
#include <map>
#include <string>
#include <vector>

std::pair<unsigned, std::string> input()
{
    unsigned amount;
    std::cin >> amount;

    std::string name;
    std::getline(std::cin, name);

    return std::make_pair(amount, name);
}

int main()
{
    size_t m;
    std::cin >> m;

    std::map<std::string, unsigned> c;
    for (size_t i = 0; i < m; ++i) {
        const auto [amount, name] = input();
        c.emplace(name, amount);
    }

    size_t n;
    std::cin >> n;

    std::vector<std::pair<unsigned, std::string>> q(n);
    for (size_t i = 0; i < n; ++i)
        q[i] = input();

    unsigned t = 0;
    for (size_t i = 0; i < n; ) {
        ++t;

        const auto it = c.find(q[i].second);
        if (it == c.end() || it->second == 0) {
            ++i;
            continue;
        }

        if (it->second >= q[i].first) {
            it->second -= q[i].first;
            ++i;
            continue;
        }

        if (i + 1 == n)
            break;

        q[i].first = it->second;
        std::swap(q[i], q[i+1]);
    }

    std::cout << t << '\n';

    return 0;
}
