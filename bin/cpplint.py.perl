#!/usr/bin/perl
# $Id: cpplint.py.perl,v 1.5 2022-03-29 12:50:49-07 - - $
#
# This is a wrapper script around cpplint.py which suppresses
# some of Google's standard complaints.
#
# Files matching the pattern yy* are skipped, because they are
# expected to be generated by flex and bison (yylex.cpp and
# yyparse.cpp).  Avoid naming user-generated files starting
# with the pattern yy*.
#
# The variable $filters may be edited to change which filters
# are used by cpplint.py and which are to be suppressed.  Filters
# listed below are ignored.
#

use strict;
use warnings;
$0 =~ s|.*/||;

my $filters = join ",", grep !m/%/, qw (

   -build
   -legal
   -readability/alt_tokens
   -readability/braces
   -readability/function
   -readability/inheritance
   -readability/utf8
   -runtime/explicit
   -runtime/int
   -runtime/printf
   -runtime/references
   -runtime/string
   -whitespace

);

my $cpplint_opts="--linelength=72 --filter=$filters";

push @ARGV, glob "*.cpp *.cc" unless @ARGV;
system "cpplint.py $cpplint_opts @ARGV";
