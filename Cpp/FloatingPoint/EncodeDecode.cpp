#include <stdio.h>
#include <iostream>
#include <cmath>
#include <bitset>

// encode a floating point number into the binary system (64-bit)
size_t encode_64_bit(const double& num)
{
  const int expBits = 11;
  const int mantissaBits = 52;
  const int nonSignBits = expBits + mantissaBits;

  const size_t sign = std::signbit(num);

  int expoBase2 = floor(std::log(fabs(num)) / std::log(2));
  const int lower = std::pow(2, expoBase2);
  const int upper = std::pow(2, expoBase2 + 1);
  size_t expo = (expoBase2 + 1023) & 0b11111111111;

  const double percentage = (fabs(num) - lower) / (upper - lower);
  const size_t mantissa = std::pow(2, mantissaBits) * percentage;
//   std::cout << "expo: " << expo << ", expo in binary: " << std::bitset<expBits>(expo) << "\n";
//   printf("mantissa: %ld\n", mantissa);

  auto encodedVal = (sign << nonSignBits) | (expo << mantissaBits) | mantissa;
  std::cout << "Value (64-bit) encoded in binary: " << std::bitset<nonSignBits+1>(encodedVal) << "\n";
  return encodedVal;
}

// decode a binary value into a floating point number (64-bit)
double decode_64_bit(const size_t& val)
{
  const int expBits = 11;
  const int mantissaBits = 52;
  const int nonSignBits = expBits + mantissaBits;
  // clang-format off
  const size_t sign    = (val & 0b1000000000000000000000000000000000000000000000000000000000000000) >> nonSignBits;
  const size_t expo    = (val & 0b0111111111110000000000000000000000000000000000000000000000000000) >> mantissaBits;
  const size_t mantissa = val & 0b0000000000001111111111111111111111111111111111111111111111111111;
  // clang-format on
  const auto percentage = mantissa / std::pow(2, mantissaBits);
  const double decodedVal = std::pow(-1, sign) * (1.0 + percentage) * std::pow(2, expo - 1023);
  printf("Binary value decoded in decimal: %.28f\n", decodedVal);
  return decodedVal;
}

int main()
{
  double num = -10.7;
  auto encodedNum = encode_64_bit(num);
  auto decodedNum = decode_64_bit(encodedNum);
  return 0;
}

