#include <iostream>
#include <vector>

struct Interval {
    int lb;
    int ub;
    int v;
};

std::istream& operator >>(std::istream& input, std::vector<Interval>& f)
{
    size_t n;
    input >> n;

    f.resize(n);
    for (Interval& i : f)
        input >> i.lb >> i.ub >> i.v;

    return input;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::vector<Interval> f1, f2;
    std::cin >> f1 >> f2;

    std::vector<Interval> f;
    {
        size_t i = 0, j = 0;
        while (i < f1.size() && j < f2.size()) {
            if (f1[i].lb < f2[j].lb) {
                f.push_back({f1[i].lb, std::min(f1[i].ub, f2[j].lb), f1[i].v});
                f1[i].lb = std::min(f1[i].ub, f2[j].ub);
            }
            if (f1[i].ub <= f2[j].ub) {
                ++i;
                continue;
            }
            if (f2[j].ub <= f1[i].lb) {
                ++j;
                continue;
            }
            f1[i].lb = f2[j].ub;
        }

        while (i < f1.size())
            f.push_back(f1[i++]);
    }

    std::cout << f.size();
    for (const Interval& i : f)
        std::cout << ' ' << i.lb << ' ' << i.ub << ' ' << i.v;

    return 0;
}
