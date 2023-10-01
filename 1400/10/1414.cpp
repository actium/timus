#include <iostream>
#include <string>

class Trie {
    struct Node {
        Node* subnodes[10+26] = {};
        bool terminal = false;

        void insert(const std::string_view& word, size_t index)
        {
            if (index == word.size()) {
                terminal = true;
                return;
            }

            const size_t label = (word[index] <= '9' ? word[index] - '0' : 10 + word[index] - 'a');
            if (subnodes[label] == nullptr)
                subnodes[label] = new Node();

            subnodes[label]->insert(word, index + 1);
        }

        void search(const std::string_view& prefix, size_t index) const
        {
            if (index == prefix.size()) {
                unsigned count = 20;
                print(std::string(2, ' ').append(prefix), count);
                return;
            }

            const size_t label = (prefix[index] <= '9' ? prefix[index] - '0' : 10 + prefix[index] - 'a');
            if (subnodes[label] != nullptr)
                subnodes[label]->search(prefix, index + 1);
        }

        void print(const std::string& prefix, unsigned& count) const
        {
            if (count == 0)
                return;

            if (terminal) {
                std::cout << prefix << '\n';
                --count;
            }

            for (size_t i = 0; i < 10; ++i) {
                if (subnodes[i] != nullptr)
                    subnodes[i]->print(prefix + char('0' + i), count);
            }
            for (size_t i = 0; i < 26; ++i) {
                if (subnodes[10 + i] != nullptr)
                    subnodes[10 + i]->print(prefix + char('a' + i), count);
            }
        }
    };

public:
    void insert(const std::string_view& word)
    {
        root_.insert(word, 0);
    }

    void search(const std::string_view& prefix) const
    {
        std::cout << prefix << '\n';

        root_.search(prefix, 0);
    }

private:
    Node root_;

}; // class Trie

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    Trie t;
    t.insert("sun");

    std::string s;
    while (std::getline(std::cin, s)) {
        const std::string_view w(s.data() + 1, s.length() - 1);

        if (s[0] == '+')
            t.insert(w);
        else
            t.search(w);
    }

    return 0;
}
