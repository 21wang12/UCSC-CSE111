// $Id: main.cpp,v 1.4 2022-01-17 12:25:05-08 - - $

#include <cassert>
#include <deque>
#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <utility>
using namespace std;

#include <unistd.h>

#include "bigint.h"
#include "debug.h"
#include "iterstack.h"
#include "libfns.h"
#include "scanner.h"
#include "util.h"

using bigint_stack = iterstack<bigint>;

void do_arith (bigint_stack& stack, const char oper) {
   if (stack.size() < 2) throw ydc_error ("stack empty");
   bigint right = stack.top();
   stack.pop();
   DEBUGF ('d', "right = " << right);
   bigint left = stack.top();
   stack.pop();
   DEBUGF ('d', "left = " << left);
   bigint result;
   switch (oper) {
      case '+': result = left + right; break;
      case '-': result = left - right; break;
      case '*': result = left * right; break;
      case '/': {
      ubigint zero{"0"};
      if(right == zero){
         stack.push(left);
         stack.push(right);
      }
      result = left / right;
      break;
      }
      case '%': result = left % right; break;
      case '^': result = pow (left, right); break;
      default: throw invalid_argument ("do_arith operator "s + oper);
   }
   DEBUGF ('d', "result = " << result);
   stack.push (result);
}

void do_clear (bigint_stack& stack, const char) {
   DEBUGF ('d', "");
   stack.clear();
}


void do_dup (bigint_stack& stack, const char) {
   if (stack.size() < 1) throw ydc_error ("stack empty");
   bigint top = stack.top();
   DEBUGF ('d', top);
   stack.push (top);
}

void do_printall (bigint_stack& stack, const char) {
   DEBUGF ('d', "");
   for (const auto& elem: stack) {
      elem.print();
      cout << endl;
   }
}

void do_print (bigint_stack& stack, const char) {
   DEBUGF ('d', "");
   if (stack.size() < 1) throw ydc_error ("stack empty");
   stack.top().print();
   cout << endl;
}

void do_debug (bigint_stack&, const char) {
   cout << "Y not implemented" << endl;
}

class ydc_quit: public exception {};
void do_quit (bigint_stack&, const char) {
   throw ydc_quit();
}

string unimplemented (char oper) {
   if (isgraph (oper)) {
      return "'"s + oper + "' ("s + octal (oper) + ") unimplemented";
   }else {
      return octal (oper) + " unimplemented"s;
   }
}

void do_function (bigint_stack& stack, const char oper) {
   DEBUGF ('d', oper);
   switch (oper) {
      case '+': do_arith    (stack, oper); break;
      case '-': do_arith    (stack, oper); break;
      case '*': do_arith    (stack, oper); break;
      case '/': do_arith    (stack, oper); break;
      case '%': do_arith    (stack, oper); break;
      case '^': do_arith    (stack, oper); break;
      case 'Y': do_debug    (stack, oper); break;
      case 'c': do_clear    (stack, oper); break;
      case 'd': do_dup      (stack, oper); break;
      case 'f': do_printall (stack, oper); break;
      case 'p': do_print    (stack, oper); break;
      case 'q': do_quit     (stack, oper); break;
      default : throw ydc_error (unimplemented (oper));
   }
}


//
// scan_options
//    Options analysis:  The only option is -Dflags. 
//
void scan_options (int argc, char** argv) {
   opterr = 0;
   for (;;) {
      int option = getopt (argc, argv, "@:");
      if (option == EOF) break;
      switch (option) {
         case '@':
            debugflags::setflags (optarg);
            break;
         default:
            error() << "-" << static_cast<char> (optopt)
                    << ": invalid option" << endl;
            break;
      }
   }
   if (optind < argc) {
      error() << "operand not permitted" << endl;
   }
}

//
// Main function.
//
int main (int argc, char** argv) {
   exec::execname (argv[0]);
   scan_options (argc, argv);
   bigint_stack operand_stack;
   scanner input;
   try {
      for (;;) {
         try {
            token lexeme = input.scan();
            switch (lexeme.symbol) {
               case tsymbol::SCANEOF:
                  throw ydc_quit();
                  break;
               case tsymbol::NUMBER:
                  operand_stack.push (bigint (lexeme.lexinfo));
                  break;
               case tsymbol::OPERATOR: {
                  char oper = lexeme.lexinfo[0];
                  do_function (operand_stack, oper);
                  break;
                  }
               default:
                  assert (false);
            }
         }catch (ydc_error& error) {
            cout << exec::execname() << ": " << error.what() << endl;
         }
         catch (domain_error& error){
            cout << "dc" << ": " << error.what() << endl;
         }
      }
   }catch (ydc_quit&) {
      // Intentionally left empty.
   }
   return exec::status();
}

