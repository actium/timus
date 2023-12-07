#include <iostream>
#include <string>
#include <vector>

template <unsigned sigma>
class PalindromeTree {
    static_assert(sigma <= 255, "sigma must be at most 255");

    struct Node {
        int length;
        int link;
        unsigned subnodes[sigma];
    };

public:
    PalindromeTree()
    {
        s_.push_back(sigma);

        nodes_.push_back({ -1, -1 });
        nodes_.push_back({ 0, 0 });

        root_ = 1;
    }

    void reserve(unsigned size)
    {
        s_.reserve(size + 1);
        nodes_.reserve(size + 2);
    }

    unsigned size() const noexcept
    {
        return nodes_.size() - 2;
    }

    void append(char c)
    {
        s_.push_back(c);

        const unsigned x = search(root_, c);
        if (nodes_[x].subnodes[c] == 0) {
            nodes_[x].subnodes[c] = nodes_.size();
            nodes_.push_back({ nodes_[x].length + 2, 1 });

            const int u = search(nodes_[x].link, c);
            if (u != -1)
                nodes_.back().link = nodes_[u].subnodes[c];
        }

        root_ = nodes_[x].subnodes[c];
    }

private:
    int search(int x, char c) const
    {
        while (x != -1 && s_[s_.length() - nodes_[x].length - 2] != c)
            x = nodes_[x].link;

        return x;
    }

private:
    std::string s_;

    std::vector<Node> nodes_;

    unsigned root_;

}; // class PalindromeTree<sigma>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::string s;
    std::cin >> s;

    const unsigned n = s.length();

    PalindromeTree<2> pt;
    pt.reserve(n);

    for (unsigned i = 0, k = 0; i < n; ++i) {
        pt.append(s[i] - 'a');
        s[i] = "01"[pt.size() != k];
        k = pt.size();
    }

    std::cout << s << '\n';

    return 0;
}
