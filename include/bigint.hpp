#include <vector>
#include <cstdint>
#include <iostream>

namespace gzCrypt
{
    class bigint
    {
    public:
        using value_type = std::uintmax_t;
        bigint() = default;
        bigint(std::intmax_t x) : m_digits(x==0 ? 0 : 1, std::abs(x)), m_sign(x < 0ll)
        {
        }

        
        int compare(const bigint&) const;

        friend std::istream& operator>>(std::istream& is, bigint&);
        friend std::ostream& operator<<(std::ostream& os, const bigint&);
        friend bigint operator+(const bigint& x, const bigint& y);
        friend bigint operator-(const bigint& x, const bigint& y);
    private:
        std::vector<value_type> m_digits;
        bool m_sign;
    };

    bool operator==(const bigint& x, const bigint& y);
    bool operator!=(const bigint& x, const bigint& y);
    bool operator>(const bigint& x, const bigint& y);
    bool operator<(const bigint& x, const bigint& y);
    bool operator>=(const bigint& x, const bigint& y);
    bool operator<=(const bigint& x, const bigint& y);
}
