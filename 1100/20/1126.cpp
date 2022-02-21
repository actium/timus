#include <iostream>
#include <set>
#include <vector>

int main()
{
    unsigned m;
    std::cin >> m;

    std::vector<unsigned> v;
    for (int x; std::cin >> x && x != -1; v.push_back(x));

    std::multiset<unsigned> q;
    for (size_t i = 0, n = v.size(); i < n; ++i) {
        q.insert(v[i]);

        if (q.size() > m)
            q.erase(q.find(v[i-m]));

        if (q.size() == m)
            std::cout << *q.rbegin() << '\n';
    }

    return 0;
}
