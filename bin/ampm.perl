#!/usr/bin/perl
# $Id: ampm.perl,v 1.5 2021-04-10 16:43:52-07 - - $

$0 =~ s|.*/||;
use POSIX qw (strftime);

@localtime = (0,0,0,0,0,0,0,0,0,);

for $hour (0..23) {
   $localtime[2] = $hour;
   $ampm = strftime "%I:%M %p", @localtime;
   $ampm =~ s/^0/ /;
   $table[$hour] = strftime "%H:%M = $ampm", @localtime;
}

for $hour (0..11) {
   print "$table[$hour]    $table[$hour + 12]\n";
}
