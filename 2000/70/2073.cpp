#include <iostream>
#include <string>

void print_line()
{
    std::cout << "+------------------------------+--------+-------------+" << '\n';
}

void print_record(std::string c, std::string d, std::string m)
{
    c.resize(30, ' ');
    d.resize(8, ' ');
    m.resize(13, ' ');

    std::cout << '|' << c << '|' << d << '|' << m << '|' << '\n';
}

int main()
{
    size_t n;
    std::cin >> n >> std::ws;

    print_line();
    print_record("Contest name", "Date", "ABCDEFGHIJKLM");
    print_line();

    while (n-- != 0) {
        std::string c;
        std::getline(std::cin, c);

        std::string d;
        std::getline(std::cin, d);

        size_t p, s;
        std::cin >> p >> s >> std::ws;
        std::string m(p, '.');

        while (s-- != 0) {
            std::string r;
            std::getline(std::cin, r);

            const size_t x = r[0] - 'A';
            if (m[x] != 'o')
                m[x] = 'x';

            if (r.substr(2) == "Accepted")
                m[x] = 'o';
        }

        print_record(c, d, m);
        print_line();
    }

    return 0;
}
