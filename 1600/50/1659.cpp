#include <cstdio>

struct Point {
    double x;
    double y;
};

int main()
{
    Point p[9];
    for (size_t i = 0; i < 3; ++i)
        scanf("%lf %lf", &p[i].x, &p[i].y);

    p[3].x = (p[0].x + p[1].x + p[2].x) / 3;
    p[3].y = (p[0].y + p[1].y + p[2].y) / 3;

    for (size_t i = 0; i < 3; ++i) {
        p[6+i].x = 2 * p[3].x - p[i].x;
        p[6+i].y = 2 * p[3].y - p[i].y;
    }

    p[4].x = (2 * p[3].x + p[1].x) / 3;
    p[4].y = (2 * p[3].y + p[1].y) / 3;

    p[5].x = (2 * p[3].x + p[8].x) / 3;
    p[5].y = (2 * p[3].y + p[8].y) / 3;

    for (size_t i = 3; i < 9; ++i)
        printf("%.7f %.7f\n", p[i].x, p[i].y);

    return 0;
}
