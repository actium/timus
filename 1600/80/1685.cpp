#include <iostream>
#include <string>

void decode(const std::string& s, size_t i, size_t k, std::string& t)
{
    if (k > 2)
        decode(s, i+1, (k-1)/2, t);

    t.push_back(s[i]);

    if (k > 1)
        decode(s, i+(k+1)/2, k/2, t);
}

int main()
{
    std::string s;
    std::getline(std::cin, s);

    std::string t;
    decode(s, 0, s.length(), t);

    std::cout << t << '\n';

    return 0;
}
