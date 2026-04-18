#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include <cassert>

class Trie {
    struct Node {
        std::vector<std::pair<char, unsigned>> subnodes;
        unsigned fail_link = 0;
        unsigned word_size = 0;

        std::pair<bool, unsigned> create_subnode(char label, unsigned subnode_index)
        {
            const auto it = std::lower_bound(subnodes.begin(), subnodes.end(), std::make_pair(label, 0u));
            if (it == subnodes.end() || it->first != label) {
                subnodes.emplace(it, label, subnode_index);
                return { true, subnode_index };
            }
            return { false, it->second };
        }

        unsigned select_subnode(char label) const
        {
            const auto it = std::lower_bound(subnodes.begin(), subnodes.end(), std::make_pair(label, 0u));
            return it != subnodes.end() && it->first == label ? it->second : 0;
        }
    };

public:
    Trie()
        : nodes_(1)
    {}

    void insert(std::string_view pattern)
    {
        unsigned node_index = 0;
        for (size_t i = 0; i < pattern.length(); ++i) {
            if (nodes_[node_index].word_size != 0)
                return;

            const auto r = nodes_[node_index].create_subnode(pattern[i], static_cast<unsigned>(nodes_.size()));
            if (r.first)
                nodes_.emplace_back();

            node_index = r.second;
        }

        nodes_[node_index].word_size = static_cast<unsigned>(pattern.length());
    }

    void commit()
    {
        std::vector<unsigned> q;
        for (const auto& [label, subnode_index] : nodes_[0].subnodes)
            q.push_back(subnode_index);

        for (size_t i = 0; i < q.size(); ++i) {
            const unsigned node_index = q[i];

            for (const auto& [label, subnode_index] : nodes_[node_index].subnodes) {
                unsigned fail_state = nodes_[node_index].fail_link;
                while (fail_state != 0 && nodes_[fail_state].select_subnode(label) == 0)
                    fail_state = nodes_[fail_state].fail_link;

                if (const unsigned x = nodes_[fail_state].select_subnode(label); x != 0)
                    fail_state = x;

                nodes_[subnode_index].fail_link = fail_state;
                nodes_[subnode_index].word_size = std::max(nodes_[subnode_index].word_size, nodes_[fail_state].word_size);

                q.push_back(subnode_index);
            }
        }
    }

    size_t search(std::string_view text) const
    {
        size_t start_position = text.length();
        for (size_t i = 0, state = 0; i < text.length(); ++i) {
            const char label = text[i];

            while (state != 0 && nodes_[state].select_subnode(label) == 0)
                state = nodes_[state].fail_link;

            state = nodes_[state].select_subnode(label);

            if (nodes_[state].word_size != 0)
                start_position = std::min(start_position, i - nodes_[state].word_size + 1);
        }
        return start_position < text.length() ? 1 + start_position : 0;
    }

private:
    std::vector<Node> nodes_;

}; // class Trie

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    Trie trie;
    {
        std::vector<std::string> p(n);
        for (size_t i = 0; i < n; ++i) {
            std::getline(std::cin, p[i]);
            assert(!p[i].empty());
        }

        std::sort(p.begin(), p.end());
        for (const auto& s : p)
            trie.insert(s);

        trie.commit();
    }

    size_t m;
    std::cin >> m;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::pair<unsigned, unsigned> match = {};
    for (size_t i = 1; i <= m; ++i) {
        std::string t;
        std::getline(std::cin, t);

        const size_t x = trie.search(t);
        if (x != 0 && match.first == 0)
            match = { i, x };
    }

    if (match.first == 0)
        std::cout << "Passed" << '\n';
    else
        std::cout << match.first << ' ' << match.second << '\n';

    return 0;
}
