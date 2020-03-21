#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cctype>
class BigInteger {
private:
    std::vector<int> num;
    bool negative;
    static BigInteger _add(const BigInteger& A, const BigInteger& B, const bool& negative = false);
    static BigInteger _sub(const BigInteger&, const BigInteger&);
    explicit BigInteger(const bool& negative = false) : negative(negative) {}
    void string2BigNumber(const char*);
    BigInteger substr(const size_t& start, const size_t& length)const;
    BigInteger pow10(const size_t&)const;
    static BigInteger karatsuba(const BigInteger&, const BigInteger&);
    void remove_front_zero();
    static BigInteger _divide(BigInteger A, const BigInteger& B, BigInteger& mod);
public:
    explicit BigInteger(int);
    explicit BigInteger(short);
    explicit BigInteger(long);
    explicit BigInteger(long long);
    explicit BigInteger(unsigned long long);
    explicit BigInteger(unsigned int);
    explicit BigInteger(unsigned long);
    explicit BigInteger(unsigned short);
    explicit BigInteger(const char*);
    explicit BigInteger(const std::string&);
    std::string to_string()const;

    static BigInteger add(const BigInteger&, const BigInteger&);
    static BigInteger sub(const BigInteger&, const BigInteger&);
    BigInteger operator+(const BigInteger&)const;
    BigInteger& operator+=(const BigInteger&);
    BigInteger operator-(const BigInteger&)const;
    BigInteger& operator-=(const BigInteger&);

    static BigInteger mul(const BigInteger&, const BigInteger&);
    static BigInteger mul2(const BigInteger&, const BigInteger&);
    static BigInteger mul3(const BigInteger&, const BigInteger&);
    BigInteger operator*(const BigInteger&)const;
    BigInteger& operator*=(const BigInteger&);

    static int compare(const BigInteger& A, const BigInteger& B);
    bool operator<(const BigInteger& other)const;
    bool operator<=(const BigInteger& other)const;
    bool operator>(const BigInteger& other)const;
    bool operator>=(const BigInteger& other)const;
    bool operator==(const BigInteger& other)const;

    static BigInteger divide(const BigInteger& A, const BigInteger& B);
    static BigInteger mod(const BigInteger& A, const BigInteger& B);
    BigInteger operator/(const BigInteger& other)const;
    BigInteger& operator/=(const BigInteger& other);
    BigInteger operator%(const BigInteger& other)const;
    BigInteger& operator%=(const BigInteger& other);

    BigInteger& operator-();
    friend std::ostream& operator<<(std::ostream& out, const BigInteger& A);
    bool operator==(const std::string& other)const;
};
