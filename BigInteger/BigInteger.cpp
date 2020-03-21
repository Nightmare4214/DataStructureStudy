#include <cstring>
#include <cassert>
#include <algorithm>
#include "BigInteger.hpp"

BigInteger::BigInteger(int input) : negative(false) {
    if (input < 0) {
        negative = true;
        num.emplace_back(-input % 10);
        input /= -10;
        negative = true;
    }
    else if (0 == input) {
        num.emplace_back(0);
    }
    while (input) {
        num.emplace_back(input % 10);
        input /= 10;
    }
}

BigInteger::BigInteger(short input) : negative(false) {
    if (input < 0) {
        negative = true;
        num.emplace_back(-input % 10);
        input /= -10;
        negative = true;
    }
    else if (0 == input) {
        num.emplace_back(0);
    }
    while (input) {
        num.emplace_back(input % 10);
        input /= 10;
    }
}

BigInteger::BigInteger(long input) : negative(false) {
    if (input < 0) {
        negative = true;
        num.emplace_back(-input % 10);
        input /= -10;
        negative = true;
    }
    else if (0 == input) {
        num.emplace_back(0);
    }
    while (input) {
        num.emplace_back(input % 10);
        input /= 10;
    }
}

BigInteger::BigInteger(long long input) : negative(false) {
    if (input < 0) {
        negative = true;
        num.emplace_back(-input % 10);
        input /= -10;
        negative = true;
    }
    else if (0 == input) {
        num.emplace_back(0);
    }
    while (input) {
        num.emplace_back(input % 10);
        input /= 10;
    }
}

BigInteger::BigInteger(unsigned long long input) : negative(false) {
    if (0 == input) {
        num.emplace_back(0);
    }
    while (input) {
        num.emplace_back(input % 10);
        input /= 10;
    }
}

BigInteger::BigInteger(unsigned int input) : negative(false) {
    if (0 == input) {
        num.emplace_back(0);
    }
    while (input) {
        num.emplace_back(input % 10);
        input /= 10;
    }
}

BigInteger::BigInteger(unsigned long input) : negative(false) {
    if (0 == input) {
        num.emplace_back(0);
    }
    while (input) {
        num.emplace_back(input % 10);
        input /= 10;
    }
}

BigInteger::BigInteger(unsigned short input) : negative(false) {
    if (0 == input) {
        num.emplace_back(0);
    }
    while (input) {
        num.emplace_back(input % 10);
        input /= 10;
    }
}

BigInteger::BigInteger(const std::string& s) : negative(false) {
    string2BigNumber(s.c_str());
}

BigInteger::BigInteger(const char* s) : negative(false) {
    string2BigNumber(s);
}
/**
 * 字符串转大数
 * @param s 字符串
 */
void BigInteger::string2BigNumber(const char* s) {
    negative = false;
    int start = 0;
    size_t len = strlen(s);
    //去掉前置空格
    while (start < len && ' ' == s[start]) {
        ++start;
    }
    if (start == len) {
        num.emplace_back(0);
        return;
    }
    //正负号
    if (s[start] == '+') {
        ++start;
    }
    else if (s[start] == '-') {
        ++start;
        negative = true;
    }
    //没有数字
    if (start == len || !isdigit(s[start])) {
        negative = false;
        num.emplace_back(0);
        return;
    }
    int end = start;
    //找最后一个数字
    while (end < len && isdigit(s[end])) {
        ++end;
    }
    --end;
    //去掉前导0
    while (start < end && '0' == s[start]) {
        ++start;
    }
    if (start == end && '0' == s[start]) {
        negative = false;
        num.emplace_back(0);
        return;
    }
    while (end >= start) {
        num.emplace_back(s[end] - '0');
        --end;
    }
}

/**
 * 截取
 * @param start 开始
 * @param length 长度
 * @return 大数
 */
BigInteger BigInteger::substr(const size_t& start, const size_t& length)const {
    size_t len = std::min(length, num.size());
    if (len <= 0 || start >= num.size() || start + len > num.size()) {
        return BigInteger(0);
    }
    BigInteger result(false);
    for (size_t i = 0; i < len; ++i) {
        result.num.emplace_back(num[start + i]);
    }
    result.remove_front_zero();
    return result;
}

/**
 * A*10^p
 * @param p 次幂
 * @return 大数
 */
BigInteger BigInteger::pow10(const size_t& p)const {
    if (0 == num.back()) {
        return *this;
    }
    BigInteger result(false);
    result.num.resize(p, 0);
    for (const int& c : num) {
        result.num.push_back(c);
    }
    return result;
}
/**
 * 去除前导0
 */
void BigInteger::remove_front_zero() {
    while (!num.empty() && 0 == num.back()) {
        num.pop_back();
    }
    if (num.empty()) {
        num.emplace_back(0);
        negative = false;
    }
}
/**
 * 大数乘法karatsuba
 * @param A 大数
 * @param B 大数
 * @return 大数
 */
BigInteger BigInteger::karatsuba(const BigInteger& A, const BigInteger& B) {
    //递归终止条件
    if (A.num.size() == 1 && B.num.size() == 1) {
        return mul(A,B);
    }
    else if (0 == A.num.back() || 0 == B.num.back()) {
        return BigInteger(0);
    }
    size_t lenA = A.num.size(),
            lenB = B.num.size(),
            half = (std::max(lenA, lenB) + 1) / 2;  //向上取整
/* 拆分为a, b, c, d */
    BigInteger A_high = A.substr(half, lenA - half);
    BigInteger A_low = A.substr(0, half);
    BigInteger B_high = B.substr(half, lenB - half);
    BigInteger B_low = B.substr(0, half);

    // 计算z2, z0, z1, 此处的乘法使用递归
    BigInteger z2 = karatsuba(A_high, B_high);
    BigInteger z0 = karatsuba(A_low, B_low);
    BigInteger z1 = karatsuba(A_high + A_low, B_high + B_low) - z0 - z2;

    return z2.pow10(half << 1u) + z1.pow10(half) + z0;
}

std::string BigInteger::to_string() const {
    std::string result;
    if (negative) {
        result = "-";
    }
    for (auto it = num.crbegin(); it != num.crend(); ++it) {
        result += std::to_string(*it);
    }
    return result;
}

/**
 * A的绝对值+B的绝对值
 * |A|+|B|
 * @param A 大数A
 * @param B 大数B
 */
BigInteger BigInteger::_add(const BigInteger& A, const BigInteger& B, const bool& negative) {
    int carry = 0;
    BigInteger result(negative);
    auto it_A = A.num.cbegin(), it_B = B.num.cbegin(),
            A_end = A.num.cend(), B_end = B.num.cend();
    while (it_A != A_end && it_B != B_end) {
        result.num.emplace_back(*it_A + *it_B + carry);
        carry = result.num.back() / 10;
        result.num.back() %= 10;
        ++it_A;
        ++it_B;
    }
    while (it_A != A_end) {
        result.num.emplace_back(*it_A + carry);
        carry = result.num.back() / 10;
        result.num.back() %= 10;
        ++it_A;
    }
    while (it_B != B_end) {
        result.num.emplace_back(*it_B + carry);
        carry = result.num.back() / 10;
        result.num.back() %= 10;
        ++it_B;
    }
    if (carry != 0) {
        result.num.emplace_back(carry);
    }
    return result;
}
/**
 * A的绝对值-B的绝对值
 * |A|-|B|
 * @param A 大数A
 * @param B 大数B
 */
BigInteger BigInteger::_sub(const BigInteger& A, const BigInteger& B) {
    auto r_A = A.num.crbegin(), r_B = B.num.crbegin(), A_rend = A.num.crend();
    auto it_A = A.num.cbegin(), it_B = B.num.cbegin(), A_end = A.num.cend(), B_end = B.num.cend();
    BigInteger result;
    //A<B,结果是负的
    if (A.num.size() < B.num.size()) {
        std::swap(it_A, it_B);
        std::swap(A_end, B_end);
    }
    else if (A.num.size() == B.num.size()) {//A和B一样长
        while (r_A != A_rend && *r_A == *r_B) {
            ++r_A;
            ++r_B;
        }
        if (r_A == A_rend) {//A==B,返回0
            result.num.emplace_back(0);
            return result;
        }
        else if (*r_A < *r_B) {//A<B,结果是负的
            std::swap(it_A, it_B);
            std::swap(A_end, B_end);
        }
    }
    int carry = 0;  //借位
    while (it_A != A_end && it_B != B_end) {
        if (*it_A >= *it_B + carry) {
            result.num.emplace_back(*it_A - *it_B - carry);
            carry = 0;
        }
        else {
            result.num.emplace_back(*it_A - *it_B - carry + 10);
            carry = 1;
        }
        ++it_A;
        ++it_B;
    }
    while (it_A != A_end) {
        if (*it_A >= carry) {
            result.num.emplace_back(*it_A - carry);
            carry = 0;
        }
        else {
            result.num.emplace_back(*it_A - carry + 10);
            carry = 1;
        }
        ++it_A;
    }
    //去除前导0
    result.remove_front_zero();
    return result;
}

BigInteger BigInteger::add(const BigInteger& A, const BigInteger& B) {
    //同号
    if (A.negative == B.negative) {
        //绝对值相加，最后符号与A，B相同
        return _add(A, B, A.negative);
    }
    else if (A.negative) {//A负，B正,相当于B-|A|
        return _sub(B, A);
    }
    //A正，B负,相当于A-|B|
    return _sub(A, B);
}

BigInteger BigInteger::sub(const BigInteger& A, const BigInteger& B) {
    //A<0,B<0,A-B=|B|-|A|
    if (A.negative && B.negative) {
        return _sub(B, A);
    }
    else if (A.negative) {  //A<0,B>0,-(|A|+|B|)
        return _add(A, B, true);
    }
    else if (B.negative) {  //A>0,B<0,|A|+|B|
        return _add(A, B, false);
    }
    //A>0,B>0,|A|-|B|
    return _sub(A, B);
}
/**
 * 重载运算符+
 * @param other 另一个大数
 * @return 大数
 */
BigInteger BigInteger::operator+(const BigInteger& other) const {
    return add(*this, other);
}
/**
 * 重载运算符+=
 * @param other 另一个大数
 * @return 大数
 */
BigInteger& BigInteger::operator+=(const BigInteger& other) {
    *this = add(*this, other);
    return *this;
}
/**
 * 重载运算符-
 * @param other 另一个大数
 * @return 大数
 */
BigInteger BigInteger::operator-(const BigInteger& other) const {
    return sub(*this, other);
}
/**
 * 重载运算符-=
 * @param other 另一个大数
 * @return 大数
 */
BigInteger& BigInteger::operator-=(const BigInteger& other) {
    *this = sub(*this, other);
    return *this;
}
/**
 * 大数乘法（模拟手算）
 * @param A 大数
 * @param B 大数
 * @return 大数
 */
BigInteger BigInteger::mul(const BigInteger& A, const BigInteger& B) {
    //其中一个是0
    if (0 == A.num.back() || 0 == B.num.back()) {
        return BigInteger(0);
    }
    BigInteger result(A.negative != B.negative);
    //预留空间
    result.num.resize(A.num.size() + B.num.size(), 0);
    for (size_t i = 0; i < A.num.size(); ++i) {
        for (size_t j = 0; j < B.num.size(); ++j) {
            result.num[i + j] += A.num[i] * B.num[j];
            result.num[i + j + 1] += result.num[i + j] / 10;
            result.num[i + j] %= 10;
        }
    }
    //去除前导0
    result.remove_front_zero();
    return result;
}
/**
 * 大数乘法（累计进位)
 * @param A 大数
 * @param B 大数
 * @return 大数
 */
BigInteger BigInteger::mul2(const BigInteger& A, const BigInteger& B) {
    //其中一个是0
    if (0 == A.num.back() || 0 == B.num.back()) {
        return BigInteger(0);
    }
    BigInteger result(A.negative != B.negative);
    //预留空间
    result.num.resize(A.num.size() + B.num.size(), 0);
    for (size_t i = 0; i < A.num.size(); ++i) {
        for (size_t j = 0; j < B.num.size(); ++j) {
            result.num[i + j] += A.num[i] * B.num[j];
            //            result.num[i+j+1]+=result.num[i+j]/10;
            //            result.num[i+j]%=10;
        }
    }
    //进位
    for (size_t i = 0; i + 1 < result.num.size(); ++i) {
        result.num[i + 1] += result.num[i] / 10;
        result.num[i] %= 10;
    }
    //去除前导0
    result.remove_front_zero();
    return result;
}
/**
 * 重载运算符*
 * @param other 另一个大数
 * @return 大数
 */
BigInteger BigInteger::operator*(const BigInteger& other)const {
    return mul3(*this, other);
}
/**
 * 重载运算符*=
 * @param other 另一个大数
 * @return 大数
 */
BigInteger& BigInteger::operator*=(const BigInteger& other) {
    *this = mul3(*this, other);
    return *this;
}
/**
 * 大数乘法（Karatsuba)
 * @param A 大数
 * @param B 大数
 * @return 大数
 */
BigInteger BigInteger::mul3(const BigInteger& A, const BigInteger& B) {
    BigInteger result = karatsuba(A, B);
    result.negative = A.negative != B.negative;
    return result;
}
/**
 * int(A/B)
 * @param A 被除数
 * @param B 除数
 * @param mod 模
 * @return 商
 */
BigInteger BigInteger::_divide(BigInteger A, const BigInteger& B, BigInteger& mod) {
    assert(B.num.back() != 0);
    int cmp = compare(A, B);
    //A<B,A//B=0 A%B=A;
    if (-1 == cmp) {
        mod = A;
        return BigInteger(0);
    }
    else if (0 == cmp) {  //A==B,A//B=1 A%B=0
        mod = BigInteger(0);
        return BigInteger(1);
    }
    BigInteger result(A.negative != B.negative);
    size_t lenA = A.num.size(), lenB = B.num.size();
    long long pos;
    result.num.resize(A.num.size(), 0);
    while (cmp != -1) {
        //商的位置
        pos = static_cast<long long>(lenA - lenB);
        for (size_t i = 1; i <= lenB; ++i) {
            if (A.num[lenA - i] > B.num[lenB - i]) {
                break;
            }
            else if (A.num[lenA - i] < B.num[lenB - i]) {  //不够除，所以要退一位
                --pos;
                break;
            }
        }
        //算完了
        if (pos < 0) {
            break;
        }
        int carry = 0;
        size_t i = pos;
        for (size_t j = 0; i < lenA && j < lenB; ++i, ++j) {
            //借位
            if (A.num[i] < B.num[j] + carry) {
                A.num[i] = A.num[i] - B.num[j] - carry + 10;
                carry = 1;
            }
            else {
                A.num[i] = A.num[i] - B.num[j] - carry;
                carry = 0;
            }
        }
        while (i < lenA) {
            if (A.num[i] >= carry) {
                A.num[i] -= carry;
                break;
            }
            A.num[i] = A.num[i] - carry + 10;
            carry = 1;
            ++i;
        }
        //商对应位置+1
        ++result.num[pos];
        //去除前导0，更新长度
        A.remove_front_zero();
        lenA = A.num.size();

        cmp = compare(A, B);
    }
    //去除前导0
    result.remove_front_zero();
    mod = A;
    return result;
}
/**
 * 比较A和B的大小，大于返回1，小于返回-1，等于返回0
 * @param A 大数
 * @param B 大数
 * @return 比较结果
 */
int BigInteger::compare(const BigInteger& A, const BigInteger& B) {
    auto r_A = A.num.crbegin(), r_B = B.num.crbegin(), A_rend = A.num.crend();

    if (A.num.size() < B.num.size()) {
        return -1;
    }
    else if (A.num.size() == B.num.size()) {  //A和B一样长
        while (r_A != A_rend && *r_A == *r_B) {
            ++r_A;
            ++r_B;
        }
        if (r_A == A_rend) {
            return 0;
        }
        else if (*r_A < *r_B) {
            return -1;
        }
    }
    return 1;
}
/**
 * 重载运算符<
 * @param other 另一个大数
 * @return 比较结果
 */
bool BigInteger::operator<(const BigInteger& other) const {
    return -1 == compare(*this, other);
}
/**
 * 重载运算符<=
 * @param other 另一个大数
 * @return 比较结果
 */
bool BigInteger::operator<=(const BigInteger& other) const {
    return compare(*this, other) != 1;
}
/**
 * 重载运算符>
 * @param other 另一个大数
 * @return 比较结果
 */
bool BigInteger::operator>(const BigInteger& other) const {
    return 1 == compare(*this, other);
}
/**
 * 重载运算符>=
 * @param other 另一个大数
 * @return 比较结果
 */
bool BigInteger::operator>=(const BigInteger& other) const {
    return compare(*this, other) != -1;
}
/**
 * 重载运算符==
 * @param other 另一个大数
 * @return 比较结果
 */
bool BigInteger::operator==(const BigInteger& other) const {
    return 0 == compare(*this, other);
}
/**
 * 大数除法
 * @param A 大数
 * @param B 大数
 * @return 大数
 */
BigInteger BigInteger::divide(const BigInteger& A, const BigInteger& B) {
    BigInteger mod;
    return _divide(A, B, mod);
}
/**
 * 大数取摸
 * @param A 大数
 * @param B 大数
 * @return 大数
 */
BigInteger BigInteger::mod(const BigInteger& A, const BigInteger& B) {
    BigInteger mod;
    _divide(A, B, mod);
    return mod;
}
/**
 * 重载运算符/
 * @param other 另一个大数
 * @return 大数
 */
BigInteger BigInteger::operator/(const BigInteger& other) const {
    return divide(*this, other);
}
/**
 * 重载运算符/=
 * @param other 另一个大数
 * @return 大数
 */
BigInteger& BigInteger::operator/=(const BigInteger& other) {
    *this = divide(*this, other);
    return *this;
}
/**
 * 重载运算符%
 * @param other 另一个大数
 * @return 大数
 */
BigInteger BigInteger::operator%(const BigInteger& other) const {
    return mod(*this, other);
}
/**
 * 重载运算符%=
 * @param other 另一个大数
 * @return 大数
 */
BigInteger& BigInteger::operator%=(const BigInteger& other) {
    *this = mod(*this, other);
    return *this;
}
/**
 * 重载运算符-(负号)
 * @param other 另一个大数
 * @return 大数
 */
BigInteger& BigInteger::operator-() {
    this->negative = !this->negative;
    return *this;
}
/**
 * 重载输出
 * @param out 输出
 * @param A 大数
 * @return 输出
 */
std::ostream& operator<<(std::ostream& out, const BigInteger& A) {
    //    if(A.negative)putchar('-');
    //    for(auto it=A.num.crbegin();it!=A.num.crend();++it)putchar(*it+'0');
    out << A.to_string();
    return out;
}
/**
 * 重载运算符==
 * @param other 大数字符串
 * @return 比较结果
 */
bool BigInteger::operator==(const std::string& other) const {
    return other == to_string();
}
