#!/usr/bin/perl
# $Id: seconds.perl,v 1.6 2022-01-29 23:38:37-08 - - $

use strict;
use warnings;



sub seconds($) {
   my $yearlen = 365.2425;
   my $monthlen = $yearlen / 12;
   my ($sec) = @_;
   return $sec, "seconds" if $sec < 60;
   my $min = $sec / 60;
   return $min, "minutes" if $min < 60;
   my $hours = $min / 60;
   return $hours, "hours" if $hours < 24;
   my $days = $hours / 24;
   return $days, "days" if $days < $monthlen;
   my $months = $days / $monthlen;
   return $months, "months" if $months < 12;
   my $years = $days / $yearlen;
   return $years, "years";
}

for my $exp (1..12) {
   my $seconds = 10 ** $exp;
   printf "%6.6g seconds = %6.6g %s\n", $seconds, seconds $seconds;
}
