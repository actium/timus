#include <algorithm>
#include <iostream>

using integer = unsigned long long;

/*
unsigned count_factors(integer x)
{
    unsigned q = 1;
    for (integer i = 2; i * i <= x; ++i) {
        unsigned k = 0;
        while (x % i == 0) {
            x /= i;
            ++k;
        }
        q *=  k + 1;
    }
    return x == 1 ? q : 2 * q;
}

void initialize()
{
    std::vector<unsigned> primes;

    const auto is_prime = [&](unsigned x) {
        for (const unsigned p : primes) {
            if (x % p == 0)
                return false;
        }
        return true;
    };

    std::vector<integer> q = { 1 };

    const auto generate = [&](unsigned x) {
        for (size_t i = 0; i < q.size(); ++i) {
            if (q[i] * x <= 1000000000000000000)
                q.push_back(q[i] * x);
        }

        std::sort(q.begin(), q.end());

        unsigned k = 1;
        for (size_t i = 1; i < q.size(); ++i) {
            const unsigned c = count_factors(q[i]);
            if (c <= k) {
                q[i] = q[i-1];
            } else {
                k = c;
            }
        }

        q.erase(std::unique(q.begin(), q.end()), q.end());
    };

    for (unsigned i = 2; i < 38; ++i) {
        if (!is_prime(i))
            continue;
    }
}
*/

constexpr std::pair<integer, unsigned> s[] = {
    { 1, 1 },
    { 2, 2 },
    { 4, 3 },
    { 6, 4 },
    { 12, 6 },
    { 24, 8 },
    { 36, 9 },
    { 48, 10 },
    { 60, 12 },
    { 120, 16 },
    { 180, 18 },
    { 240, 20 },
    { 360, 24 },
    { 720, 30 },
    { 840, 32 },
    { 1260, 36 },
    { 1680, 40 },
    { 2520, 48 },
    { 5040, 60 },
    { 7560, 64 },
    { 10080, 72 },
    { 15120, 80 },
    { 20160, 84 },
    { 25200, 90 },
    { 27720, 96 },
    { 45360, 100 },
    { 50400, 108 },
    { 55440, 120 },
    { 83160, 128 },
    { 110880, 144 },
    { 166320, 160 },
    { 221760, 168 },
    { 277200, 180 },
    { 332640, 192 },
    { 498960, 200 },
    { 554400, 216 },
    { 665280, 224 },
    { 720720, 240 },
    { 1081080, 256 },
    { 1441440, 288 },
    { 2162160, 320 },
    { 2882880, 336 },
    { 3603600, 360 },
    { 4324320, 384 },
    { 6486480, 400 },
    { 7207200, 432 },
    { 8648640, 448 },
    { 10810800, 480 },
    { 14414400, 504 },
    { 17297280, 512 },
    { 21621600, 576 },
    { 32432400, 600 },
    { 36756720, 640 },
    { 43243200, 672 },
    { 61261200, 720 },
    { 73513440, 768 },
    { 110270160, 800 },
    { 122522400, 864 },
    { 147026880, 896 },
    { 183783600, 960 },
    { 245044800, 1008 },
    { 294053760, 1024 },
    { 367567200, 1152 },
    { 551350800, 1200 },
    { 698377680, 1280 },
    { 735134400, 1344 },
    { 1102701600, 1440 },
    { 1396755360, 1536 },
    { 2095133040, 1600 },
    { 2205403200, 1680 },
    { 2327925600, 1728 },
    { 2793510720, 1792 },
    { 3491888400, 1920 },
    { 4655851200, 2016 },
    { 5587021440, 2048 },
    { 6983776800, 2304 },
    { 10475665200, 2400 },
    { 13967553600, 2688 },
    { 20951330400, 2880 },
    { 27935107200, 3072 },
    { 41902660800, 3360 },
    { 48886437600, 3456 },
    { 64250746560, 3584 },
    { 73329656400, 3600 },
    { 80313433200, 3840 },
    { 97772875200, 4032 },
    { 128501493120, 4096 },
    { 146659312800, 4320 },
    { 160626866400, 4608 },
    { 240940299600, 4800 },
    { 293318625600, 5040 },
    { 321253732800, 5376 },
    { 481880599200, 5760 },
    { 642507465600, 6144 },
    { 963761198400, 6720 },
    { 1124388064800, 6912 },
    { 1606268664000, 7168 },
    { 1686582097200, 7200 },
    { 1927522396800, 7680 },
    { 2248776129600, 8064 },
    { 3212537328000, 8192 },
    { 3373164194400, 8640 },
    { 4497552259200, 9216 },
    { 6746328388800, 10080 },
    { 8995104518400, 10368 },
    { 9316358251200, 10752 },
    { 13492656777600, 11520 },
    { 18632716502400, 12288 },
    { 26985313555200, 12960 },
    { 27949074753600, 13440 },
    { 32607253879200, 13824 },
    { 46581791256000, 14336 },
    { 48910880818800, 14400 },
    { 55898149507200, 15360 },
    { 65214507758400, 16128 },
    { 93163582512000, 16384 },
    { 97821761637600, 17280 },
    { 130429015516800, 18432 },
    { 195643523275200, 20160 },
    { 260858031033600, 20736 },
    { 288807105787200, 21504 },
    { 391287046550400, 23040 },
    { 577614211574400, 24576 },
    { 782574093100800, 25920 },
    { 866421317361600, 26880 },
    { 1010824870255200, 27648 },
    { 1444035528936000, 28672 },
    { 1516237305382800, 28800 },
    { 1732842634723200, 30720 },
    { 2021649740510400, 32256 },
    { 2888071057872000, 32768 },
    { 3032474610765600, 34560 },
    { 4043299481020800, 36864 },
    { 6064949221531200, 40320 },
    { 8086598962041600, 41472 },
    { 10108248702552000, 43008 },
    { 12129898443062400, 46080 },
    { 18194847664593600, 48384 },
    { 20216497405104000, 49152 },
    { 24259796886124800, 51840 },
    { 30324746107656000, 53760 },
    { 36389695329187200, 55296 },
    { 48519593772249600, 57600 },
    { 60649492215312000, 61440 },
    { 72779390658374400, 62208 },
    { 74801040398884800, 64512 },
    { 106858629141264000, 65536 },
    { 112201560598327200, 69120 },
    { 149602080797769600, 73728 },
    { 224403121196654400, 80640 },
    { 299204161595539200, 82944 },
    { 374005201994424000, 86016 },
    { 448806242393308800, 92160 },
    { 673209363589963200, 96768 },
    { 748010403988848000, 98304 },
    { 897612484786617600, 103680 },
};

void test_case()
{
    integer n;
    std::cin >> n;

    auto it = std::upper_bound(std::begin(s), std::end(s), n, [](integer x, const std::pair<integer, unsigned>& it) {
        return x < it.first;
    });
    --it;
    std::cout << it->first << ' ' << it->second << '\n';
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t t;
    std::cin >> t;

    while (t-- > 0)
        test_case();

    return 0;
}