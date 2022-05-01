// $Id: ctypes.cpp,v 1.10 2021-08-08 16:47:59-07 - - $

#include <cctype>
#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

unordered_map<size_t,string> cntrls {
   {0x00, "NUL"}, {0x01, "SOH"}, {0x02, "STX"}, {0x03, "ETX"},
   {0x04, "EOT"}, {0x05, "ENQ"}, {0x06, "ACK"}, {0x07, "BEL"},
   {0x08, "BS "}, {0x09, "HT "}, {0x0A, "LF "}, {0x0B, "VT "},
   {0x0C, "FF "}, {0x0D, "CR "}, {0x0E, "SO "}, {0x0F, "SI "},
   {0x10, "DLE"}, {0x11, "DC1"}, {0x12, "DC2"}, {0x13, "DC3"},
   {0x14, "DC4"}, {0x15, "NAK"}, {0x16, "SYN"}, {0x17, "ETB"},
   {0x18, "CAN"}, {0x19, "EM "}, {0x1A, "SUB"}, {0x1B, "ESC"},
   {0x1C, "FS "}, {0x1D, "GS "}, {0x1E, "RS "}, {0x1F, "US "},
   {0x7F, "DEL"},
};

vector<pair<int(*)(int),string>> ctypes {
   {isalnum, "alnum"},
   {isalpha, "alpha"},
   {isascii, "ascii"},
   {isblank, "blank"},
   {iscntrl, "cntrl"},
   {isdigit, "digit"},
   {isgraph, "graph"},
   {islower, "lower"},
   {isprint, "print"},
   {ispunct, "punct"},
   {isspace, "space"},
   {isupper, "upper"},
   {isxdigit, "xdigit"},
};

int main() {
   for (int chr = 0; chr <= 255; ++chr) {
      ostringstream line;
      if (isprint(chr)) {
         line << "'" << char(chr) << "'";
      }else {
         auto ctrl = cntrls.find (chr);
         if (ctrl == cntrls.end()) line << "   ";
                              else line << ctrl->second;
      }
      line << " 0x" << setw(2) << hex << setfill('0')
           << uppercase << chr
           << " 0" << setw(3) << oct << setfill('0') << chr
           << " " << setw(3) << dec << setfill(' ') << chr;
      bool want_print = false;
      for (auto ctype : ctypes) {
         if (ctype.first (chr)) {
            line << " " << ctype.second;
            want_print = true;
         }
      }
      if (want_print) cout << line.str() << endl;
   }
}
