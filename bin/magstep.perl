#!/usr/bin/perl
# $Id: magstep.perl,v 1.4 2021-10-12 21:30:11-07 - - $

use strict;
use warnings;

for my $loop (-2..20) {
   my $magstep = $loop / 2;
   printf "magstep %4.1f = %s\n", $magstep, 1.2 ** $magstep;
}

