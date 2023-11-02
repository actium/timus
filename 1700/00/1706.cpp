#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class SuffixArray {
public:
    explicit SuffixArray(std::string_view s)
    {
        const size_t size = s.length();

        const auto shift = [size](unsigned position, unsigned k) {
            position += k;
            if (position >= size)
                position -= size;

            return position;
        };

        const auto sort = [size](const std::vector<unsigned>& positions, const std::vector<unsigned>& ranks) {
            std::vector<unsigned> frequencies(1 + size);
            for (size_t i = 0; i < size; ++i)
                ++frequencies[1 + ranks[i]];

            std::vector<unsigned>& bucket_positions = frequencies;
            for (size_t i = 1; i < size; ++i)
                bucket_positions[i] += frequencies[i - 1];

            std::vector<unsigned> new_positions(size);
            for (const unsigned position : positions)
                new_positions[bucket_positions[ranks[position]]++] = position;

            return new_positions;
        };

        positions_.resize(size);
        {
            for (size_t i = 0; i < size; ++i)
                positions_[i] = i;
        }

        std::sort(positions_.begin(), positions_.end(), [&](unsigned i, unsigned j) {
            return s[i] < s[j];
        });

        ranks_.resize(size);
        {
            unsigned last_position = positions_[0];
            for (const unsigned position : positions_) {
                ranks_[position] = ranks_[last_position];
                if (s[position] != s[last_position])
                    ++ranks_[position];

                last_position = position;
            }
        }

        std::vector<unsigned> ranks(size);
        for (size_t k = 1; k < size && ranks_[positions_.back()] + 1 != size; k *= 2) {
            for (size_t i = 0; i < size; ++i)
                positions_[i] = shift(positions_[i], size - k);

            std::swap(ranks_, ranks);
            positions_ = sort(positions_, ranks);

            unsigned last_position = positions_[0];
            ranks_[last_position] = 0;
            for (const unsigned position : positions_) {
                ranks_[position] = ranks_[last_position];
                if (ranks[position] != ranks[last_position] || ranks[shift(position, k)] != ranks[shift(last_position, k)])
                    ++ranks_[position];

                last_position = position;
            }
        }

        lcps_.resize(size);
        {
            for (size_t i = 0, k = 0; i + 1 < size; ++i, k -= (k > 0)) {
                const size_t j = positions_[ranks_[i] - 1];
                while (s[i + k] == s[j + k])
                    ++k;

                lcps_[ranks_[i]] = k;
            }
        }
    }

    unsigned operator [](size_t index) const
    {
        return positions_[index];
    }

    unsigned lcp(size_t index) const
    {
        return lcps_[index];
    }

private:
    std::vector<unsigned> positions_;
    std::vector<unsigned> ranks_;
    std::vector<unsigned> lcps_;

}; // class SuffixArray

unsigned count_substrings(std::string& s, size_t i, size_t k)
{
    const char x = s[i + k];
    s[i + k] = ' ';

    const SuffixArray sa(std::string_view(s.data() + i, k + 1));

    unsigned q = 0;
    for (size_t i = 1; i <= k; ++i)
        q += k - sa[i] - sa.lcp(i);

    s[i + k] = x;
    return q;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned k;
    std::cin >> k;

    std::string s;
    std::cin >> s;

    s += s.substr(0, k);
    for (size_t i = k; i < s.length(); ++i)
        std::cout << count_substrings(s, i - k, k) << ' ';

    return 0;
}
