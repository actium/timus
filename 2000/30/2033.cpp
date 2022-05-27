#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

struct Record {
    std::string f;
    std::string n;
    unsigned p;
};

int main()
{
    std::vector<Record> r(6);
    for (size_t i = 0; i < 6; ++i)
        std::cin >> r[i].f >> r[i].n >> r[i].p;

    std::map<std::string, unsigned> f;
    for (const Record& q : r)
        ++f[q.n];

    std::sort(r.begin(), r.end(), [&](const Record& x, const Record& y) {
        return f[x.n] != f[y.n] ? f[x.n] > f[y.n] : x.p < y.p;
    });

    std::cout << r[0].n << '\n';

    return 0;
}
