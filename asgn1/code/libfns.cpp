// $Id: libfns.cpp,v 1.1 2021-12-28 13:54:01-08 - - $

#include "libfns.h"

//
// This algorithm would be more efficient with operators
// *=, /=2, and is_odd.  But we leave it here.
//

bigint pow (const bigint& base_arg, const bigint& exponent_arg) {
   bigint base (base_arg);
   bigint exponent (exponent_arg);
   static const bigint ZERO ("0");
   static const bigint ONE ("1");
   static const bigint TWO ("2");

   DEBUGF ('^', "zero = " << ZERO << ", one = " << ONE<< "two = "<<TWO);
   DEBUGF ('^', "base = " << base << ", exponent = " << exponent);
   if (base == ZERO) return ZERO;
   bigint result = ONE;
   if (exponent < ZERO) {
      base = ONE / base;
      exponent = - exponent;
   }
   while (exponent > ZERO) {
      if (exponent % TWO == ONE) {
         result = result * base;
         exponent = exponent - ONE;
      }else {
         base = base * base;
         exponent = exponent / TWO;
      }
   }
   DEBUGF ('^', "result = " << result);
   return result;
}

