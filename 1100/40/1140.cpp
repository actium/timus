#include <iostream>

int main()
{
    size_t n;
    std::cin >> n;

    int x = 0, y = 0, z = 0;
    for (size_t i = 0; i < n; ++i) {
        char o;
        std::cin >> o;

        int d;
        std::cin >> d;

        if (o == 'X')
            x += d;

        if (o == 'Y')
            y += d;

        if (o == 'Z')
            z += d;
    }

    const int xy_x = x - z, xy_y = y + z, xy = abs(xy_x) + abs(xy_y);
    const int yz_y = y + x, yz_z = z - x, yz = abs(yz_y) + abs(yz_z);
    const int zx_z = z + y, zx_x = x + y, zx = abs(zx_z) + abs(zx_x);

    const auto answer = [](int a, int b, char ca, char cb) {
        std::cout << (a != 0) + (b != 0) << '\n';

        if (a != 0)
            std::cout << ca << ' ' << -a << '\n';
        if (b != 0)
            std::cout << cb << ' ' << -b << '\n';
    };

    if (xy <= yz && xy <= zx) {
        answer(xy_x, xy_y, 'X', 'Y');
    } else if (yz <= zx && yz <= xy) {
        answer(yz_y, yz_z, 'Y', 'Z');
    } else {
        answer(zx_z, zx_x, 'Z', 'X');
    }

    return 0;
}
