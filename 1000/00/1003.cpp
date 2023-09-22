#include <iostream>
#include <string>
#include <unordered_map>

struct Entry {
    int a;
    int b;
    int p;
};

void test_case(unsigned n)
{
    std::unordered_map<int, Entry> data;

    unsigned q;
    std::cin >> q;

    unsigned k = 0;
    for (unsigned i = 0, d = 1; i < q; ++i, k += d) {
        Entry e;
        std::cin >> e.a >> e.b;

        std::string p;
        std::cin >> p;

        e.p = (p == "odd");

        while (d == 1) {
            const auto it = data.find(e.b);
            if (it == data.end()) {
                data.emplace(e.b, e);
                break;
            }

            const Entry x = it->second;
            if (x.a < e.a) {
                it->second.a = e.a;
                it->second.p = e.p;
                e.p ^= x.p;
                e.b = e.a - 1;
                e.a = x.a;
                continue;
            }
            if (x.a > e.a) {
                e.p ^= x.p;
                e.b = x.a - 1;
                continue;
            }
            if (x.p == e.p)
                break;

            d = 0;
        }
    }

    std::cout << k << '\n';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    for (int n; std::cin >> n && n != -1; test_case(n));

    return 0;
}
