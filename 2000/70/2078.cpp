#include <iostream>
#include <vector>

unsigned count(const std::vector<unsigned>& s)
{
    unsigned v = 0;

    size_t j = 0;
    for (size_t i = 0; i < 9; ++i) {
        unsigned d = s[j++];
        if (d == 10) {
            d += s[j] + s[j+1];
        } else {
            d += s[j++];
            if (d == 10)
                d += s[j];
        }
        v += d;
    }
    while (j < s.size())
        v += s[j++];

    return v;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned a[10];
    for (size_t i = 0; i < 10; ++i)
        std::cin >> a[i];

    std::vector<unsigned> w, b;
    for (size_t i = 0; i < 9; ++i) {
        b.push_back(a[i]);
        if (a[i] != 10)
            b.push_back(0);

        w.push_back(0);
        w.push_back(a[i]);
    }

    if (a[9] > 20) {
        w.push_back(10); w.push_back(a[9] - 20); w.push_back(10);
        b.push_back(10); b.push_back(10); b.push_back(a[9] - 20);
    } else if (a[9] >= 10) {
        w.push_back(0); w.push_back(10); w.push_back(a[9] - 10);
        b.push_back(10); b.push_back(a[9] - 10); b.push_back(0);
    } else {
        w.push_back(0); w.push_back(a[9]);
        b.push_back(a[9]); b.push_back(0);
    }

    std::cout << count(w) << ' ' << count(b) << '\n';

    return 0;
}
