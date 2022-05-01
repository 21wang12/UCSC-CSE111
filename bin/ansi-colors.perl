#!/usr/bin/perl
# $Id: ansi-colors.perl,v 1.1 2021-09-28 09:15:06-07 - - $
#
# Print a color table of 8bg * 8fg * 2 states (regular/bold)

$line = "-" x 77;
@colors = qw (black red green yellow blue magenta cyan white);

print "Table for 16-color terminal escape sequences.\n";
print "Replace ESC with \\033 in bash.\n";
print "Background | Foreground colors\n";
print "Colors     | ";
printf "%-8s", $_ for @colors;
print "\n";
print "$line\n";


for $bg (40..47) {
   for $bold (0..1) {
      print "\033[0mESC[${bg};1m  | ";
      for $fg (30..37) {
         if ($bold) {print "\033[${bg};1m\033[${fg};1m[${fg};1m  "}
               else {print "\033[${bg};1m\033[${fg}m[${fg}m    "}
      }
      print "\033[0m\n";
   }
   print "$line\n";
}
