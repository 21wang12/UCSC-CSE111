#!/usr/bin/perl
# $Ie$
#
# NAME
#    hours.perl - compute differences in times
#
# SYNOPSIS
#    hours.perl timespec...
#
# DESCRIPTION
#    Given a list of time specs on the command line, compute
#    the sum or diffferences between time specs.
#
# SYNTAX
#    timespec : H?H:MM +- minutes | H?H:MM +- H?H:MM
#

$0 =~ s|.*/||;
use strict;
use warnings;

sub minutes($$) {
   my ($hour, $min) = @_;
   return $hour * 60 + $min;
}

sub hhmm($) {
   my ($timemin) = @_;
   my $hour = int ($timemin / 60);
   my $min = $timemin - $hour * 60;
   return sprintf "%02d:%02d", $hour, $min;
}

sub timespec($) {
   my ($spec) = @_;
   if ($spec =~ m/^\s*(\d+):(\d\d)\s*([+-])\s*(\d+)\s*$/) {
      # HH:MM+min, HH:MM-min
      my ($hour, $min, $posneg, $deltamin) = ($1, $2, $3, $4);
      my $startmin = minutes $hour, $min;
      my $endmin = $startmin + "$posneg$deltamin";
      printf "%s + %d min = %s\n",
             hhmm $startmin, $deltamin, hhmm $endmin;
   }elsif ($spec =~ m/^\s*(\d+):(\d\d)\s*([+-])\s*(\d+):(\d\d)\s*$/) {
      my ($hour1, $min1, $posneg, $hour2, $min2) = ($1, $2, $3, $4, $5);
      my $minutes1 = minutes $hour1, $min1;
      my $minutes2 = minutes $hour2, $min2;
      my $deltamin = $minutes1 + "$posneg$minutes2";
      printf "%s $posneg %s = %3d min = %s\n",
             hhmm $minutes1, hhmm $minutes2, $deltamin, hhmm $deltamin;
   }else {
      print STDERR "$0: $spec: invalid timespec\n";
      print STDERR "timespec : H?H:MM + minutes | H?H:MM - H?H:MM\n";
   }
}

if (@ARGV) {
   timespec $_ for @ARGV;
}else {
   print "Usage: $0 timespec...\n";
   print STDERR "timespec : H?H:MM + minutes | H?H:MM - H?H:MM\n";
   exit 1;
}

