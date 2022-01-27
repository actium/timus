#include <iostream>
#include <vector>

int main()
{
    unsigned n;
    std::cin >> n;

    std::vector<unsigned> ids[101];
    while (n-- != 0) {
        unsigned id, m;
        std::cin >> id >> m;

        ids[m].push_back(id);
    }

    for (int m = 100; m >= 0; --m) {
        for (const unsigned id : ids[m])
            std::cout << id << ' ' << m << '\n';
    }

    return 0;
}
