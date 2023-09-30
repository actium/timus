#include <iostream>
#include <string>

#include <cmath>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned w, d;
    std::cin >> w >> d;

    int x0, y0;
    std::cin >> x0 >> y0;

    int x1, y1;
    std::cin >> x1 >> y1;

    std::string p;
    std::cin >> p;

    for (const char c : p) {
        switch (c) {
            case 'L':
                x0 = -x0;
                break;
            case 'R':
                x0 = 2 * w - x0;
                break;
            case 'F':
                y0 = -y0;
                break;
            case 'B':
                y0 = 2 * d - y0;
                break;
        }
    }

    std::cout << std::fixed << hypot(x0 - x1, y0 - y1) << '\n';

    return 0;
}
