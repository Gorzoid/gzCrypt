#include <vector>
#include <cstdint>
#include <iostream>
#include <type_traits>
#include <limits>

namespace gzCrypt
{
    using namespace std;
    class biguint
    {
    public:
        using wdigit_t = std::uint64_t;
        using digit_t = std::uint32_t;
        static const size_t nbits = sizeof(digit_t)*8;

        biguint() = default;
        template<typename T, typename = std::enable_if_t<std::is_integral<std::remove_reference_t<T>>::value>>
        biguint(T&& x) : m_digits( {static_cast<digit_t>( std::forward<T>(x) )} )
        {
            trim();
        }

        static std::pair<biguint,biguint> divrem(biguint dividend, const biguint& divisor);
        static int compare(const biguint& lhs, const biguint& rhs);

        friend std::istream& operator>>(std::istream& is, biguint&);
        friend std::ostream& operator<<(std::ostream& os, const biguint&);
        
        operator bool() const;

        biguint& operator++();
        biguint operator++(int);
        biguint& operator--();
        biguint operator--(int);
        
        biguint& operator+=(const biguint& rhs);
        biguint& operator-=(const biguint& rhs);

        template<typename T>
        biguint& operator*=(T&& rhs)
        {
            return *this = std::move(*this) * std::forward<T>(rhs);
        }

        template<typename T>
        biguint& operator/=(T&& rhs)
        {
            return *this = std::move(*this) / std::forward<T>(rhs);
        }

        template<typename T>
        biguint& operator%=(T&& rhs)
        {
            return *this = std::move(*this) % std::forward<T>(rhs);
        }
    private:

        void trim();

        std::vector<digit_t> m_digits;
    };

    biguint operator+(biguint lhs, const biguint& rhs);
    biguint operator-(biguint lhs, const biguint& rhs);
    biguint operator*(biguint lhs, const biguint& rhs);
    biguint operator/(biguint lhs, const biguint& rhs);
    biguint operator%(biguint lhs, const biguint& rhs);

    bool operator==(const biguint& lhs, const biguint& rhs);
    bool operator!=(const biguint& lhs, const biguint& rhs);
    bool operator>(const biguint& lhs, const biguint& rhs);
    bool operator<(const biguint& lhs, const biguint& rhs);
    bool operator>=(const biguint& lhs, const biguint& rhs);
    bool operator<=(const biguint& lhs, const biguint& rhs);

    // Template functions to remove ambigious operator error.

    template<typename T, typename = std::enable_if_t<std::is_integral<std::remove_reference_t<T>>::value>>
	biguint operator+(biguint lhs, T&& rhs) { return std::move(lhs) + biguint(std::forward<T>(rhs)); }
    template<typename T, typename = std::enable_if_t<std::is_integral<std::remove_reference_t<T>>::value>>
	biguint operator-(biguint lhs, T&& rhs) { return std::move(lhs) - biguint(std::forward<T>(rhs)); }
    template<typename T, typename = std::enable_if_t<std::is_integral<std::remove_reference_t<T>>::value>>
	biguint operator*(biguint lhs, T&& rhs) { return std::move(lhs) * biguint(std::forward<T>(rhs)); }
    template<typename T, typename = std::enable_if_t<std::is_integral<std::remove_reference_t<T>>::value>>
	biguint operator/(biguint lhs, T&& rhs) { return std::move(lhs) / biguint(std::forward<T>(rhs)); }
    template<typename T, typename = std::enable_if_t<std::is_integral<std::remove_reference_t<T>>::value>>
	biguint operator%(biguint lhs, T&& rhs) { return std::move(lhs) % biguint(std::forward<T>(rhs)); }

    template<typename T, typename = std::enable_if_t<std::is_integral<std::remove_reference_t<T>>::value>>
	biguint operator+(T&& lhs, const biguint& rhs) { return biguint(std::forward<T>(lhs)) + rhs; }
    template<typename T, typename = std::enable_if_t<std::is_integral<std::remove_reference_t<T>>::value>>
	biguint operator-(T&& lhs, const biguint& rhs) { return biguint(std::forward<T>(lhs)) - rhs; }
    template<typename T, typename = std::enable_if_t<std::is_integral<std::remove_reference_t<T>>::value>>
	biguint operator*(T&& lhs, biguint rhs) { return biguint(std::forward<T>(lhs)) * std::move(rhs); }
    template<typename T, typename = std::enable_if_t<std::is_integral<std::remove_reference_t<T>>::value>>
	biguint operator/(T&& lhs, const biguint& rhs) { return biguint(std::forward<T>(lhs)) / rhs; }
    template<typename T, typename = std::enable_if_t<std::is_integral<std::remove_reference_t<T>>::value>>
	biguint operator%(T&& lhs, const biguint& rhs) { return biguint(std::forward<T>(lhs)) % rhs; }

    template<typename T, typename = std::enable_if_t<std::is_integral<std::remove_reference_t<T>>::value>>
	bool operator==(const biguint& lhs, T&& rhs) { return lhs == biguint(std::forward<T>(rhs)); }
    template<typename T, typename = std::enable_if_t<std::is_integral<std::remove_reference_t<T>>::value>>
	bool operator!=(const biguint& lhs, T&& rhs) { return lhs != biguint(std::forward<T>(rhs)); }
    template<typename T, typename = std::enable_if_t<std::is_integral<std::remove_reference_t<T>>::value>>
	bool operator>(const biguint& lhs, T&& rhs) { return lhs > biguint(std::forward<T>(rhs)); }
    template<typename T, typename = std::enable_if_t<std::is_integral<std::remove_reference_t<T>>::value>>
	bool operator<(const biguint& lhs, T&& rhs) { return lhs < biguint(std::forward<T>(rhs)); }
    template<typename T, typename = std::enable_if_t<std::is_integral<std::remove_reference_t<T>>::value>>
	bool operator>=(const biguint& lhs, T&& rhs) { return lhs >= biguint(std::forward<T>(rhs)); }
    template<typename T, typename = std::enable_if_t<std::is_integral<std::remove_reference_t<T>>::value>>
	bool operator<=(const biguint& lhs, T&& rhs) { return lhs <= biguint(std::forward<T>(rhs)); }

    template<typename T, typename = std::enable_if_t<std::is_integral<std::remove_reference_t<T>>::value>>
	bool operator==(T&& lhs, const biguint& rhs) { return biguint(std::forward<T>(lhs)) == rhs; }
    template<typename T, typename = std::enable_if_t<std::is_integral<std::remove_reference_t<T>>::value>>
	bool operator!=(T&& lhs, const biguint& rhs) { return biguint(std::forward<T>(lhs)) != rhs; }
    template<typename T, typename = std::enable_if_t<std::is_integral<std::remove_reference_t<T>>::value>>
	bool operator>(T&& lhs, const biguint& rhs) { return biguint(std::forward<T>(lhs)) > rhs; }
    template<typename T, typename = std::enable_if_t<std::is_integral<std::remove_reference_t<T>>::value>>
	bool operator<(T&& lhs, const biguint& rhs) { return biguint(std::forward<T>(lhs)) < rhs; }
    template<typename T, typename = std::enable_if_t<std::is_integral<std::remove_reference_t<T>>::value>>
	bool operator>=(T&& lhs, const biguint& rhs) { return biguint(std::forward<T>(lhs)) >= rhs; }
    template<typename T, typename = std::enable_if_t<std::is_integral<std::remove_reference_t<T>>::value>>
	bool operator<=(T&& lhs, const biguint& rhs) { return biguint(std::forward<T>(lhs)) <= rhs; }

}
