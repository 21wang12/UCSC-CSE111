#ifndef _ARITHMETIC_H_
#define _ARITHMETIC_H_

#include <cmath>
#include <cstdlib>
using namespace std;

#define EPS 1e-2

// Ref: https://stackoverflow.com/questions/24999861/determining-if-two-numbers-are-almost-equal-and-outputting-the-result
#define EQ(a, b) (std::abs(a-b)<=0.015*std::min(std::abs(a),std::abs(b)))
// #define EQ(a, b) (std::abs(a-b)<EPS)

#define GT true
#define GE true
#define LT true
#define LE true

#endif