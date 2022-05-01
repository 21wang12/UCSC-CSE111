// $Id: ubigint.cpp,v 1.6 2022-03-29 13:04:12-07 - - $

#include <cctype>
#include <cstdlib>
#include <exception>
#include <stack>
#include <stdexcept>
using namespace std;

#include "debug.h"
#include "ubigint.h"

ostream& operator<< (ostream& out, const vector<uint8_t>& vec) {
   for (auto itor = vec.rbegin(); itor != vec.rend(); ++itor) {
      out << int (*itor);
   }
   return out;
}

ostream& operator<< (ostream& out, const ubigint& that) { 
   return out << "ubigint(" << that.uvalue << ")";
}

ubigint::ubigint (unsigned long that): uvalue (0) {
   if(that == 0){
      uvalue.insert(uvalue.begin(), static_cast<uint8_t>(that));
   }
   else{

      if(that<10){
         DEBUGF ('!', "2")
         uvalue.insert(uvalue.begin(),static_cast<uint8_t>(that));
      }
      else{
         while(that>=10){
            uvalue.insert
            (uvalue.begin(),static_cast<uint8_t>(that%10));
            that /= 10;
            if(that < 10){
               uvalue.insert
               (uvalue.begin(),static_cast<uint8_t>(that));
            }
         }
      }
      
      
   }
   
}

ubigint::ubigint (const string& that): uvalue(0) { 
   DEBUGF ('?', "2")
   for (char digit: that) {
      if (not isdigit (digit)) {
         throw invalid_argument ("ubigint::ubigint(" + that + ")");
      }
      uvalue.insert(uvalue.begin(), static_cast<uint8_t>(digit - '0'));
   }
}

ubigint ubigint::operator+ (const ubigint& that) const {
   ubigint result{}; 
   for(size_t it = 0; it<that.uvalue.size() || it<uvalue.size(); it++){
      if(it<that.uvalue.size()&& it < uvalue.size()){
         result.uvalue.push_back(uvalue[it] + that.uvalue[it]);
      }
      
      else if(it<that.uvalue.size()&&it >= uvalue.size()){
         result.uvalue.push_back(that.uvalue[it]);
      }
      else if(it<uvalue.size()&&it >= that.uvalue.size()){
         result.uvalue.push_back(uvalue[it]);
      }
   }
   

   //normalize
   uint8_t carry = 0;
   for(size_t i = 0; i<result.uvalue.size(); i++){
      result.uvalue[i] += carry;
      carry = 0;
      if(result.uvalue[i]>=10){
         carry = result.uvalue[i]/10;
         result.uvalue[i] %= 10;
      }
   }

   if(carry!=0){
      result.uvalue.push_back(carry);
   }
   return result;
}

ubigint ubigint::operator- (const ubigint& that) const {
   if (*this < that) throw domain_error ("ubigint::operator-(a<b)"); 
   ubigint result{};
   if(*this == that){
      result.uvalue.push_back(0);
      return result;
   }
   uint8_t carry = 0;
   uint8_t carry2 = 0;
   int digit = 0;
   for(size_t it = 0; it<that.uvalue.size() || it<uvalue.size(); it++){ 
      
      carry2 = carry;
      carry = 0;
      if(it<that.uvalue.size()&& it < uvalue.size()){
         digit = static_cast<int>(uvalue[it]-that.uvalue[it]-carry2);
         while(digit<0){
            digit+=10;
            carry ++;
         }
         result.uvalue.push_back(static_cast<uint8_t>(digit));
      }
      
      else if(it<that.uvalue.size()&&it >= uvalue.size()){
         digit = static_cast<int>(that.uvalue[it] - carry2);
         result.uvalue.push_back(digit);
      }
      else if(it<uvalue.size()&&it >= that.uvalue.size()){
         digit = static_cast<int>(uvalue[it] - carry2);
         result.uvalue.push_back(digit);
      }
   }
   while(result.uvalue.back()==0 && uvalue.size() > 1){
      result.uvalue.pop_back();
   }
   

   return result;
}

ubigint ubigint::operator* (const ubigint& that) const { 
   ubigint result; //or ubigint a = ubigint();
   ubigvalue_t p(uvalue.size()+that.uvalue.size());
   uint8_t carry;
   for(size_t i= 0; i<uvalue.size(); i++){
      carry = 0;
      for(size_t j = 0; j<that.uvalue.size();j++){
         uint8_t digit = p[i+j] + uvalue[i] * that.uvalue[j] + carry;
         p[i+j] = digit%10;
         carry = digit / 10;
      }
      p[i+that.uvalue.size()]=carry;
   }
   
   for(size_t i = 0; i<p.size(); i++){
      result.uvalue.push_back(p[i]);
   }
   while(result.uvalue.back()==0 && result.uvalue.size()>1){
      result.uvalue.pop_back();
   }
   return result;
}

void ubigint::multiply_by_2() {
   uint8_t carry = 0;
   for(size_t i=0; i<uvalue.size(); i++){
      uvalue[i] *= 2;
      uvalue[i] += carry;
      carry = 0;
      if(uvalue[i]>=10){
         carry = uvalue[i] /10;
         uvalue[i] %=10;
      }
   }
   if(carry != 0){
      uvalue.push_back(carry);
   }
}

void ubigint::divide_by_2() {
   uint8_t higher = 0;
   for(size_t i=0; i<uvalue.size(); i++){
      uvalue[i] /= 2;
      if(i < uvalue.size()-1){
         higher = uvalue[i+1];
      }else{
         higher = 0;
      }
      if(higher%2!=0){
         uvalue[i] += 5;
      }
      
   }
   while(uvalue.back()==0 && uvalue.size() > 0){
      uvalue.pop_back();
   }
}

struct quo_rem { ubigint quotient; ubigint remainder; };
quo_rem udivide (const ubigint& dividend, const ubigint& divisor_) {
   // NOTE: udivide is a non-member function.
   ubigint divisor {divisor_};
   ubigint zero {0};
   if (divisor == zero) throw domain_error ("divide by zero");
   ubigint power_of_2 {"1"};
   ubigint quotient {0};
   ubigint remainder {dividend}; // left operand, dividend
   while (divisor < remainder) {
      divisor.multiply_by_2();
      power_of_2.multiply_by_2();
   }
   while (power_of_2 > zero) {
      if (divisor <= remainder) { 
         remainder = remainder - divisor;
         quotient = quotient + power_of_2;
      }
      divisor.divide_by_2();
      power_of_2.divide_by_2();
   }
   return {.quotient = quotient, .remainder = remainder};
}

ubigint ubigint::operator/ (const ubigint& that) const {
   return udivide (*this, that).quotient;
}

ubigint ubigint::operator% (const ubigint& that) const {
   return udivide (*this, that).remainder;
}

bool ubigint::operator== (const ubigint& that) const {
   if(uvalue.size()!= that.uvalue.size()){
      return false;
   }
   for(size_t it = 0; it<that.uvalue.size(); it++){
      if(uvalue[it]!=that.uvalue[it]){
            return false;
      }
   }
   return true;
}

bool ubigint::operator< (const ubigint& that) const {
   if(*this == that){
      return false;
   }
   if(uvalue.size()<that.uvalue.size()){//compare the size
      return true;
   }
   else if(uvalue.size()>that.uvalue.size()){
      return false;
   }
   //compare each element in vector
   else if(uvalue.size()==that.uvalue.size()){
      for(size_t it = 0; it<that.uvalue.size(); it++){
         if(uvalue[uvalue.size()-it-1]<
         that.uvalue[that.uvalue.size()-it-1]){
            return true;
         }
         else if(that.uvalue[that.uvalue.size()-it-1]<
         uvalue[uvalue.size()-it-1]){
            return false;
         }
      }
      return false;
   }
   return false;
}

bool ubigint::operator> (const ubigint& that) const {
   return *this<that?false:true;
}

void ubigint::print() const {
   DEBUGF ('p', this << " -> " << *this);
   for(size_t i = 0; i<uvalue.size(); i++){
      if((i)%69==0&&i!=0){
         cout<<"\\" << endl;
      }
      cout << static_cast<int> (uvalue[uvalue.size()-i-1]);
   }
   
}

