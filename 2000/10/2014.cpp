#include <algorithm>
#include <vector>

#include <cstdio>

using integer = long long;

class SegmentTree {
    struct Node {
        integer sum = 0;
        integer min = 0;
    };

public:
    explicit SegmentTree(size_t size)
        : size_(1)
    {
        while (size_ < size)
            size_ *= 2;

        data_.resize(2 * size_);
    }

    void set(size_t index, integer value)
    {
        set(index, value, 1, 0, size_);
    }

    integer query() const
    {
        return std::min<integer>(data_[1].min, 0);
    }

private:
    void set(size_t index, integer value, size_t x, size_t lx, size_t rx)
    {
        if (lx + 1 == rx) {
            data_[x].sum = value;
            data_[x].min = value;
            return;
        }

        const size_t mx = (lx + rx) / 2;
        if (index < mx) {
            set(index, value, x<<1|0, lx, mx);
        } else {
            set(index, value, x<<1|1, mx, rx);
        }

        data_[x].sum = data_[x<<1|0].sum + data_[x<<1|1].sum;
        data_[x].min = std::min(data_[x<<1|0].min, data_[x<<1|0].sum + data_[x<<1|1].min);
    }

private:
    size_t size_;

    std::vector<Node> data_;

}; // class SegmentTree

void solve(std::vector<std::pair<int, unsigned>>& letters)
{
    const size_t n = letters.size();

    std::vector<unsigned> ts(n);
    for (size_t i = 0; i < n; ++i)
        ts[i] = letters[i].second;

    std::sort(ts.begin(), ts.end());

    SegmentTree st(n);
    for (size_t i = 0; i < n; ++i) {
        const size_t x = std::lower_bound(ts.begin(), ts.end(), letters[i].second) - ts.begin();
        st.set(x, letters[i].first);
        printf("%lld\n", st.query());
    }
}

int main()
{
    unsigned n;
    scanf("%u", &n);

    std::vector<std::pair<int, unsigned>> letters(n);
    for (unsigned i = 0; i < n; ++i) {
        unsigned dd, dm, th, tm;
        scanf("%d %02u.%02u %02u:%02u", &letters[i].first, &dd, &dm, &th, &tm);

        letters[i].second = ((dm * 31 + dd) * 24 + th) * 60 + tm;
    }

    solve(letters);

    return 0;
}
