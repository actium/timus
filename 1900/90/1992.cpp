#include <iostream>
#include <vector>

struct Node {
    unsigned p = 0;
    unsigned l = 0;
    unsigned r = 0;
};

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::vector<Node> history(1);
    std::vector<unsigned> clones(1);

    size_t n, m;
    std::cin >> n >> m;

    for (size_t i = 0; i < n; ++i) {
        std::string t;
        std::cin >> t;

        if (t == "learn") {
            unsigned c, p;
            std::cin >> c >> p;

            history.push_back({p, clones[c-1], 0});
            clones[c-1] = history.size() - 1;
            continue;
        }
        if (t == "rollback") {
            unsigned c;
            std::cin >> c;

            const unsigned x = clones[c-1], l = history[x].l;
            history.push_back({history[l].p, history[l].l, x});
            clones[c-1] = history.size() - 1;
            continue;
        }
        if (t == "relearn") {
            unsigned c;
            std::cin >> c;

            clones[c-1] = history[clones[c-1]].r;
            continue;
        }
        if (t == "clone") {
            unsigned c;
            std::cin >> c;

            clones.push_back(clones[c-1]);
            continue;
        }
        if (t == "check") {
            unsigned c;
            std::cin >> c;

            const unsigned p = history[clones[c-1]].p;
            if (p == 0)
                std::cout << "basic" << '\n';
            else
                std::cout << p << '\n';
        }
    }

    return 0;
}
