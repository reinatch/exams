#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>
#include <string>

class bigint {
private:
    std::string value;

public:
    bigint();
    bigint(const std::string& str);
    bigint(unsigned long long num);
    bigint(const bigint& other);
    bigint& operator=(const bigint& other);
    ~bigint();
    
    std::string to_string() const;
    bigint operator+(const bigint& other) const;
    bigint& operator+=(const bigint& other);
    bigint operator-(const bigint& other) const;
    bigint& operator++();
    bigint operator++(int);
    bigint operator<<(size_t shift) const;
    bigint& operator<<=(size_t shift);
    bigint& operator>>=(size_t shift);
    
    bool operator<(const bigint& other) const;
    bool operator>(const bigint& other) const;
    bool operator<=(const bigint& other) const;
    bool operator>=(const bigint& other) const;
    bool operator==(const bigint& other) const;
    bool operator!=(const bigint& other) const;
    
    friend std::ostream& operator<<(std::ostream& os, const bigint& bi);
};

#endif // BIGINT_HPP
