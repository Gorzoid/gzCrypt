#include "bigint.hpp"
#include <algorithm>

namespace gzCrypt
{

    std::istream& operator>>(std::istream& is, bigint&)
    {
        throw std::runtime_error("Not yet implemented.");
    }

    std::ostream& operator<<(std::ostream& os, const bigint& x)
    {
        throw std::runtime_error("Not yet implemented.");
    }

    bigint subtract_abs(const bigint& x, const bigint& y)
    {

    }
    
    bigint operator+(const bigint& x, const bigint& y)
    {
        if(x.m_sign != y.m_sign)
        {
            return y.m_sign ? subtract_abs(x,y) : subtract_abs(y, x);
        }

        bigint ret;
        ret.m_sign = x.m_sign;

        bigint::value_type carry = 0;

        for(size_t i = 0; i < std::max(x.m_digits.size(),y.m_digits.size()); ++i)
        {
            auto dx = i<x.m_digits.size() ? x.m_digits[i] : 0, dy = i<y.m_digits.size() ? y.m_digits[i] : 0;
            if(dx || dy)
            {
                if(i >= ret.m_digits.size()) ret.m_digits.resize(i+1);

                carry += dx + dy;

                ret.m_digits[i] = carry;

                carry = carry < dx; // If sum is smaller then carry = 1
            }
        }

        return ret;
    }

    bigint operator-(const bigint& x, const bigint& y)
    {
        
    }

    int bigint::compare(const bigint& other) const
    {
        auto it1 = m_digits.begin(), it2 = other.m_digits.begin();
        for(; it1 != m_digits.end() && it2 != other.m_digits.end(); ++it1, ++it2)
        {
            if(*it1 != *it2)
            {
                return *it1 < *it2 ? -1 : 1;
            }
        }

        if(it1 != m_digits.end())
            return std::find_if(it1,m_digits.end(), [](auto x){return x>0;}) != m_digits.end() ? 1 : 0;

        if(it2 != other.m_digits.end())
            return std::find_if(it2,other.m_digits.end(), [](auto x){return x>0;}) != other.m_digits.end() ? -1 : 0;

        return 0;
    }

    bool operator==(const bigint& x, const bigint& y)
    {
        return x.compare(y) == 0;
    }
    bool operator!=(const bigint& x, const bigint& y)
    {
        return x.compare(y) != 0;
    }
    bool operator>(const bigint& x, const bigint& y)
    {
        return x.compare(y) > 0;
    }
    bool operator<(const bigint& x, const bigint& y)
    {
        return x.compare(y) < 0;
    }
    bool operator>=(const bigint& x, const bigint& y)
    {
        return x.compare(y) >= 0;
    }
    bool operator<=(const bigint& x, const bigint& y)
    {
        return x.compare(y) <= 0;
    }
}
