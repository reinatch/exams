#include "bigint.hpp"
#include <sstream>
#include <algorithm>

std::string to_string_c98(unsigned long long n) {
    if (n == 0) return "0";
    std::string result;
    while (n > 0) {
        result = char('0' + (n % 10)) + result;
        n /= 10;
    }
    return result;
}

bool all_digits(const std::string& str) {
    for (size_t i = 0; i < str.length(); ++i) {
        if (!isdigit(str[i])) return false;
    }
    return true;
}

bigint::bigint() : value("0") {}

bigint::bigint(const std::string& str) {
    if (str.empty() || !all_digits(str)) {
        value = "0";
    } else {
        value = str;
    }
}

bigint::bigint(unsigned long long num) : value(to_string_c98(num)) {}

bigint::bigint(const bigint& other) : value(other.value) {}

bigint& bigint::operator=(const bigint& other) {
    if (this != &other) {
        value = other.value;
    }
    return *this;
}

bigint::~bigint() {}

std::string bigint::to_string() const {
    return value;
}

bigint bigint::operator+(const bigint& other) const {
    std::string a = value;
    std::string b = other.value;
    std::string result;
    
    int carry = 0;
    int i = a.length() - 1;
    int j = b.length() - 1;
    
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += (a[i--] - '0');
        if (j >= 0) sum += (b[j--] - '0');
        
        result = char(sum % 10 + '0') + result;
        carry = sum / 10;
    }
    
    return bigint(result);
}

bigint& bigint::operator+=(const bigint& other) {
    *this = *this + other;
    return *this;
}

bigint bigint::operator-(const bigint& other) const {
    (void)other;
    return bigint();
}

bigint& bigint::operator++() {
    *this += bigint(1);
    return *this;
}

bigint bigint::operator++(int) {
    bigint temp(*this);
    ++(*this);
    return temp;
}

bigint bigint::operator<<(size_t shift) const {
    return bigint(value + std::string(shift, '0'));
}

bigint& bigint::operator<<=(size_t shift) {
    value += std::string(shift, '0');
    return *this;
}

bigint& bigint::operator>>=(size_t shift) {
    if (shift >= value.size()) {
        value = "0";
    } else {
        value = value.substr(0, value.size() - shift);
    }
    return *this;
}

bool bigint::operator<(const bigint& other) const {
    if (value.size() != other.value.size()) {
        return value.size() < other.value.size();
    }
    return value < other.value;
}

bool bigint::operator>(const bigint& other) const {
    return other < *this;
}

bool bigint::operator<=(const bigint& other) const {
    return !(other < *this);
}

bool bigint::operator>=(const bigint& other) const {
    return !(*this < other);
}

bool bigint::operator==(const bigint& other) const {
    return value == other.value;
}

bool bigint::operator!=(const bigint& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const bigint& bi) {
    os << bi.to_string();
    return os;
}
