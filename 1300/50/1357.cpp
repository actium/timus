#include <iostream>
#include <string>
#include <vector>

#include <cmath>

unsigned parse_timestamp(const std::string& t)
{
    const unsigned h = (t[0] - '0') * 10 + (t[1] - '0');
    const unsigned m = (t[3] - '0') * 10 + (t[4] - '0');
    const unsigned s = (t[6] - '0') * 10 + (t[7] - '0');
    return (h * 60 + m) * 60 + s;
}

void print_timestamp(unsigned t, unsigned k)
{
    const unsigned h = t / 3600, r = t % 3600;

    char buffer[9];
    sprintf(buffer, "%02u:%02u:%02u", h % 24, r / 60, r % 60);

    for (unsigned i = 0; i < k; ++i)
        std::cout << buffer << '\n';
}

struct Kettle {
    double last_event_time;
    double last_temperature;
    unsigned pending_count;

    double compute_boiling_time() const
    {
        return (100 - last_temperature) * 4190 * (pending_count * 0.2) / 400;
    }
};

void solve(const std::vector<unsigned>& ts)
{
    const size_t n = ts.size();

    Kettle kettle = { 0, 0, 0 };
    for (size_t i = 0; i < n; ++i) {
        const double dt = kettle.compute_boiling_time();
        if (kettle.last_event_time + dt <= ts[i] || kettle.pending_count == 5) {
            const unsigned t = std::ceil(kettle.last_event_time + dt);
            print_timestamp(t, kettle.pending_count);
            kettle = { std::max(t, ts[i]), 20, 1 };
        } else {
            const double t = (kettle.last_event_time < ts[i] ? ts[i] : kettle.last_event_time);
            const double dT = 400 * (t - kettle.last_event_time) / (4190 * kettle.pending_count * 0.2);
            kettle.last_event_time = t;
            kettle.last_temperature += dT;
            kettle.last_temperature = kettle.last_temperature * kettle.pending_count * 0.2 + 4;
            kettle.last_temperature /= ++kettle.pending_count * 0.2;
        }
    }

    const double dt = kettle.compute_boiling_time();
    print_timestamp(std::ceil(kettle.last_event_time + dt), kettle.pending_count);
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<unsigned> ts(n);
    for (size_t i = 0; i < n; ++i) {
        std::string t;
        std::cin >> t;

        ts[i] = parse_timestamp(t);
    }

    if (n != 0)
        solve(ts);

    return 0;
}
