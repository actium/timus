#include <iostream>
#include <string>
#include <vector>

unsigned match(const std::vector<std::string>& words, std::string& word)
{
    const size_t n = words.size(), m = word.length();

    for (size_t i = 0; i < n; ++i) {
        if (words[i].length() != word.length())
            continue;

        unsigned k = 0;
        for (size_t j = 0; j < m; ++j)
            k += (words[i][j] != word[j]);

        if (k < 2) {
            word = words[i];
            return k;
        }
    }
    return 0;
}

void solve(std::vector<std::string>& words, const std::string& text)
{
    unsigned k = 0;

    std::string word;
    for (const char c : text) {
        if (isalpha(c)) {
            word.push_back(c);
            continue;
        }
        if (!word.empty()) {
            k += match(words, word);
            std::cout << word;
            word.clear();
        }
        std::cout << c;
    }

    std::cout << k << '\n';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::vector<std::string> words;
    for (std::string w; std::getline(std::cin, w), w != "#"; words.push_back(w));

    std::string text;
    for (std::string s; std::getline(std::cin, s); text.push_back('\n'))
        text.append(s);

    solve(words, text);

    return 0;
}
