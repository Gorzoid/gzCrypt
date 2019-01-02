#include "bigint.hpp"
#include <algorithm>
#include <iterator>
#include <cctype>
#include <sstream>
#include <string>

namespace gzCrypt
{

    std::istream& operator>>(std::istream& is, biguint& x)
    {
        x.m_digits.clear();

        char c;
        if(!(is >> c) || !std::isdigit(c))
        {
            is.setstate(std::ios::failbit);
            return is;
        }

        x = c - '0';

        while(is >> c)
        {
            if(!std::isdigit(c))
            {
                is.unget();
                break;
            }
            x = 10 * x + (c - '0');
        }
        return is;
    }

    std::ostream& operator<<(std::ostream& os, const biguint& x)
    {
        auto it = std::find_if(x.m_digits.rbegin(), x.m_digits.rend(), [](biguint::digit_t digit) {return digit != 0;});
        
        if(it == x.m_digits.rend())
        {
            return os << "0";
        }
        else
        {
            std::copy(it, x.m_digits.rend(), std::ostream_iterator<int>(os << "0x" << std::hex));
        }
        return os;
    }

    biguint::operator bool() const
    {
        return std::any_of(m_digits.begin(), m_digits.end(), [](digit_t x){return x != 0;});
    }

    biguint& biguint::operator++()
    {
        wdigit_t carry = 1;
        for(digit_t& d : m_digits)
        {
            carry += d;
            d = static_cast<digit_t>( carry );
            carry >>= nbits;
            if(carry == 0) break;
        }

        if(carry != 0)
            m_digits.push_back(carry);

        return *this;
    }

    biguint biguint::operator++(int)
    {
        biguint ret{*this};
        ++(*this);
        return ret;
    }

    biguint& biguint::operator--()
    {
        wdigit_t carry = -1; // all bits are set when cast to wdigit_t
        for(digit_t& d : m_digits)
        {
            carry += d;
            d = static_cast<digit_t>( carry );
            carry >>= nbits;

            if(carry == 0) break;
        }

        if(carry != 0)
            throw std::runtime_error("Unsigned bigint underflow.");

        trim();

        return *this;
    }

    biguint biguint::operator--(int)
    {
        biguint ret{*this};
        --(*this);
        return ret;
    }

    biguint& biguint::operator+=(const biguint& rhs)
    {
        if(m_digits.size() < rhs.m_digits.size())
        {
            m_digits.resize(rhs.m_digits.size(), 0u); // Assume result will be atleast as many digits as lhs and rhs.
        }

        biguint::wdigit_t carry = 0;
        size_t i = 0;

        for(; i < rhs.m_digits.size(); i++) // Iterate all digits in rhs
        {
            carry = carry + m_digits[i] + rhs.m_digits[i]; // type promotion to 64bit to avoid overflow
            m_digits[i] = static_cast<digit_t>( carry ); // downcast back to 32bit to strip carry
            carry >>= nbits; // rshift to move carry bit to LSB 
        }

        for(;carry > 0; i++) // Propagate carry until it is zero
        {
            if(i < m_digits.size())
            {
                carry += m_digits[i];
                m_digits[i] = static_cast<digit_t>( carry );
            }
            else
            {
                m_digits.push_back(static_cast<digit_t>(carry));
            }
            carry >>= nbits;
        }
        return *this;
    }

    biguint& biguint::operator-=(const biguint& rhs)
    {
        if(*this < rhs)
            throw std::runtime_error("Unsigned bigint underflow.");

        biguint::wdigit_t carry = 0;
        size_t i = 0;

        for(; i < rhs.m_digits.size(); i++) // Same logic as addition but with - operator
        {
            // 2's complement arithmetic means that the 32bits of carry will underflow correctly (assuming lhs < rhs)
            carry = carry + m_digits[i] - rhs.m_digits[i];
            m_digits[i] = static_cast<digit_t>( carry );
            carry >>= nbits;
        }

        for(;carry > 0; i++)
        {
            if(i < m_digits.size())
            {
                carry += m_digits[i];
                m_digits[i] = static_cast<digit_t>( carry );
            }
            else
            {
                m_digits.push_back(static_cast<digit_t>(carry));
            }
            carry >>= nbits;
        }

        trim();

        return *this;
    }

    std::pair<biguint,biguint> biguint::divrem(biguint dividend, const biguint& divisor)
    {
        if(!divisor) throw std::runtime_error("Divide by zero.");
        biguint quotient{};
        while(dividend >= divisor)
        {
            dividend -= divisor;
            ++quotient;
        }
        return std::make_pair(quotient, dividend);
    }

    void biguint::trim()
    {
        auto it = std::find_if(m_digits.rbegin(), m_digits.rend(), [](digit_t x){return x != 0;});
        m_digits.erase(it.base(), m_digits.end());
    }

    
    biguint operator+(biguint lhs, const biguint& rhs)
    {
        return lhs += rhs;
    }

    biguint operator-(biguint lhs, const biguint& rhs)
    {
        return lhs -= rhs;
    }

    biguint operator*(biguint lhs, const biguint& rhs)
    {
        biguint ret{};
        while(lhs)
        {
            ret += rhs;
            --lhs;
        }
        return ret;
    }

    biguint operator/(biguint lhs, const biguint& rhs)
    {
        return biguint::divrem(std::move(lhs), rhs).first;
    }

    biguint operator%(biguint lhs, const biguint& rhs)
    {
        return biguint::divrem(std::move(lhs), rhs).second;
    }

    int biguint::compare(const biguint& lhs, const biguint& rhs)
    {
        auto it1 = lhs.m_digits.rbegin(), it2 = rhs.m_digits.rbegin();

        auto szdif = static_cast<long long>(lhs.m_digits.size()) - rhs.m_digits.size();
        if(szdif > 0)
        {
            while(szdif-- > 0)
            {
                if(*it1++) return 1;
            }
        }
        else if(szdif < 0)
        {
            while(szdif++ < 0)
            {
                if(*it2++) return -1;
            }
        }

        for(; it1 != lhs.m_digits.rend() && it2 != rhs.m_digits.rend(); ++it1, ++it2)
        {
            if(*it1 != *it2)
            {
                return *it1 < *it2 ? -1 : 1;
            }
        }

        return 0;
    }

    bool operator==(const biguint& lhs, const biguint& rhs)
    {
        return biguint::compare(lhs,rhs) == 0;
    }
    bool operator!=(const biguint& lhs, const biguint& rhs)
    {
        return biguint::compare(lhs,rhs) != 0;
    }
    bool operator>(const biguint& lhs, const biguint& rhs)
    {
        return biguint::compare(lhs,rhs) > 0;
    }
    bool operator<(const biguint& lhs, const biguint& rhs)
    {
        return biguint::compare(lhs,rhs) < 0;
    }
    bool operator>=(const biguint& lhs, const biguint& rhs)
    {
        return biguint::compare(lhs,rhs) >= 0;
    }
    bool operator<=(const biguint& lhs, const biguint& rhs)
    {
        return biguint::compare(lhs,rhs) <= 0;
    }

    namespace bigint_literals
    {
        biguint operator ""_ubig(const char* str)
        {
            std::istringstream ss{ std::string{str} };

            biguint ret;
            ss >> ret;

            return ret;
        }
    }

}
