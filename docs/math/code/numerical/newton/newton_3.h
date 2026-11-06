#ifndef OI_WIKI_NEWTON_3_H
#define OI_WIKI_NEWTON_3_H

#include <stdexcept>
#include <string>
#include <vector>

// 仅提供牛顿迭代所需的非负大整数运算，十进制数位按低位在前存储。
class BigInteger {
  std::vector<int> digits;

  void trim() {
    while (!digits.empty() && digits.back() == 0) digits.pop_back();
  }

  void halve() {
    int remainder = 0;
    for (std::size_t i = digits.size(); i > 0; --i) {
      int current = remainder * 10 + digits[i - 1];
      digits[i - 1] = current / 2;
      remainder = current % 2;
    }
    trim();
  }

  // 调用方保证当前值不小于 other。
  void subtract(const BigInteger& other) {
    int borrow = 0;
    for (std::size_t i = 0; i < digits.size(); ++i) {
      digits[i] -= borrow + (i < other.digits.size() ? other.digits[i] : 0);
      borrow = digits[i] < 0;
      if (borrow) digits[i] += 10;
    }
    trim();
  }

 public:
  BigInteger(int value = 0) {
    while (value > 0) {
      digits.push_back(value % 10);
      value /= 10;
    }
  }

  BigInteger(const std::string& value) {
    std::size_t first = !value.empty() && value[0] == '+' ? 1 : 0;
    for (std::size_t i = value.size(); i > first; --i)
      digits.push_back(value[i - 1] - '0');
    trim();
  }

  int signum() const { return digits.empty() ? 0 : 1; }

  int bitLength() const {
    BigInteger value = *this;
    int length = 0;
    while (value.signum() != 0) {
      value.halve();
      ++length;
    }
    return length;
  }

  BigInteger shiftLeft(int count) const {
    BigInteger result = *this;
    while (count-- > 0) result = result.add(result);
    return result;
  }

  BigInteger shiftRight(int count) const {
    BigInteger result = *this;
    while (count-- > 0 && result.signum() != 0) result.halve();
    return result;
  }

  BigInteger divide(const BigInteger& other) const {
    if (other.signum() == 0) throw std::domain_error("division by zero");
    BigInteger quotient, remainder;
    quotient.digits.resize(digits.size());
    for (std::size_t i = digits.size(); i > 0; --i) {
      remainder.digits.insert(remainder.digits.begin(), digits[i - 1]);
      remainder.trim();
      while (remainder.compareTo(other) >= 0) {
        remainder.subtract(other);
        ++quotient.digits[i - 1];
      }
    }
    quotient.trim();
    return quotient;
  }

  BigInteger add(const BigInteger& other) const {
    BigInteger result;
    int carry = 0;
    for (std::size_t i = 0;
         i < digits.size() || i < other.digits.size() || carry; ++i) {
      int sum = carry;
      if (i < digits.size()) sum += digits[i];
      if (i < other.digits.size()) sum += other.digits[i];
      result.digits.push_back(sum % 10);
      carry = sum / 10;
    }
    return result;
  }

  int compareTo(const BigInteger& other) const {
    if (digits.size() != other.digits.size())
      return digits.size() < other.digits.size() ? -1 : 1;
    for (std::size_t i = digits.size(); i > 0; --i)
      if (digits[i - 1] != other.digits[i - 1])
        return digits[i - 1] < other.digits[i - 1] ? -1 : 1;
    return 0;
  }

  std::string toString() const {
    if (digits.empty()) return "0";
    std::string result;
    for (std::size_t i = digits.size(); i > 0; --i)
      result.push_back(static_cast<char>('0' + digits[i - 1]));
    return result;
  }
};

#endif
