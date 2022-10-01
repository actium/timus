#include <iostream>
#include <vector>

int main()
{
    size_t n;
    std::cin >> n;

    std::vector<unsigned> s;
    s.reserve(2 * n);
    for (size_t i = 0; i < n; ++i) {
        int x;
        std::cin >> x;

        switch (x) {
            case 0:
                if (s.size() < n - i)
                    s.insert(s.end(), s.begin(), s.end());
                break;
            case -1:
                std::cout << s.back() << '\n';
                s.pop_back();
                break;
            default:
                s.push_back(x);
                break;
        }
    }

    return 0;
}
