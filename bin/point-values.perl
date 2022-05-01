#!/usr/bin/perl
# $Id: point-values.perl,v 1.9 2021-10-31 16:20:10-07 - - $

sub pointvalue($$$) {
   my ($component, $fraction, $max) = @_;
   print "\n",
         "The value of 1 point in a $component worth $fraction\n",
         "of a course, graded out of $max points is:\n";
   printf "1 pt = %.6f of a $component\n", my $value = 1 / $max;
   printf "1 pt = %.6f of the course\n", $value *= $fraction;
   printf "1 pt = %.6f of a quarter (3 courses/quarter)\n", $value /= 3;
   printf "1 pt = %.6f of a year (3 quarters/year)\n", $value /= 3;
   printf "1 pt = %.6f of the diploma (4 years)\n", $value /= 4;
}

pointvalue ("assignment",   0.13, 60);
pointvalue ("midterm exam", 0.21, 40);
pointvalue ("final exam",   0.27, 50);

