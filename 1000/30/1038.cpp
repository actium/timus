#include <iostream>
#include <string>

int main()
{
    unsigned error_count = 0, word_count = 0, word_length = 0;
    for (std::string s; std::cin >> s; ) {
        for (const char c : s) {
            if (c == '.' || c == '?' || c == '!')
                word_count = 0;

            if (!isalpha(c)) {
                word_length = 0;
                continue;
            }

            if (word_length++ == 0) {
                error_count += (word_count == 0 && islower(c));
                ++word_count;
            } else {
                error_count += (word_count != 0 && isupper(c));
            }
        }

        word_length = 0;
    }

    std::cout << error_count << '\n';

    return 0;
}
