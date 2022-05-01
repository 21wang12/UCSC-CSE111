#!/usr/bin/perl
# $Id: bold-etc.perl,v 1.9 2020-07-19 13:23:15-07 - - $

use strict;
use warnings;

my %style = (
   ""           => "",
   "bold"       => "\033[1m",
   "underlined" => "\033[4m",
   "reversed"   => "\033[7m",
);
my $RESET = "\033[0m";

for my $reversed ("", "reversed") {
   my $style = $style{$reversed};
   for my $underlined ("", "underlined") {
      $style .= $style{$underlined};
      for my $bold ("", "bold") {
         $style .= $style{$bold};
         my $text = " $bold $underlined $reversed";
         $text =~ s/\s+/ /g;
         $text =~ s/\s*$//;
         $text =~ s/^\s*$/ plain/;
         print "${style}This text is$text.$RESET\n";
      }
   }
}
