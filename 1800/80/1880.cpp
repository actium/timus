#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::vector<unsigned> v[5];
    for (unsigned i = 0; i < 3; ++i) {
        size_t n;
        std::cin >> n;

        v[i].resize(n);
        for (size_t j = 0; j < n; ++j)
            std::cin >> v[i][j];
    }

    std::set_intersection(v[0].cbegin(), v[0].cend(), v[1].cbegin(), v[1].cend(), std::back_inserter(v[3]));
    std::set_intersection(v[2].cbegin(), v[2].cend(), v[3].cbegin(), v[3].cend(), std::back_inserter(v[4]));

    std::cout << v[4].size() << '\n';

    return 0;
}
