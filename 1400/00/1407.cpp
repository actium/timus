/*

a = [0] * 101
b = [0] * 101
m = [0] * 101

a[1] = 5
b[1] = 1
m[1] = 2

for i in range(2, 101):
    if b[i-1] % 2 == 1:
        m[i] = 1
        b[i] = (a[i-1] + b[i-1]) // 2
    else:
        m[i] = 2
        b[i] = (2 * a[i-1] + b[i-1]) // 2

    a[i] = a[i-1] * 5

print("".join(str(x) for x in m[:0:-1]))

*/

#include <iostream>

int main()
{
    unsigned n;
    std::cin >> n;

    std::cout << "1211211211221121211211121122122211212221112122111122212112212121112121121122111112111211111212122112" << '\n';

    return 0;
}
