#!/usr/bin/perl
# $Id: length-lines.perl,v 1.5 2021-11-20 12:33:11-08 - - $

#
# NAME
#    length-lines - count number of lines of various lengths
#
# SYNOPSIS
#    length-lines [-v] filename...
#
# OPTIONS
#    -v  print names of files being counted
#

$0 =~ s|.*/||;
use strict;
use warnings;

use Getopt::Std;
my %opts;
getopts "v", \%opts;
my $verbose = $opts{"v"};

sub key($) {
   my ($len) = @_;
   my $modulus = 10;
   $len = int ($len / $modulus) * $modulus;
   return sprintf "%2d..%2d", $len, $len + $modulus - 1;
}

my %file_stats;
my @arg_filenames;

my %line_lengths;
my $line_count = 0;
my $max_line_len = 0;
for my $filename (@ARGV) {
   open my $file, "<$filename"
        or warn "$0: $filename: $!\n" and next;
   push @arg_filenames, $filename;
   while (defined (my $line = <$file>)) {
      $file_stats{$filename}{CHARS} += length $line;
      ++$file_stats{$filename}{LINES};
      chomp $line;
      my $len = length $line;
      $max_line_len = $len if $max_line_len < $len;
      ++$line_lengths{key $len};
      ++$line_count;
   }
   close $file;
}

if ($verbose) {
   for my $filename (@arg_filenames) {
      printf "%7d %7d %s\n",
             $file_stats{$filename}{LINES},
             $file_stats{$filename}{CHARS},
             $filename;
   }
}

my $total = 0;
printf "%-7s %13s %13s\n", qw (length range-count cumulative);
for my $key (sort keys %line_lengths) {
   my $len = $line_lengths{$key};
   $total += $len;
   my $keycopy = $key;
   $keycopy =~ s/..$/sprintf "%2d", $max_line_len/e
         if $keycopy =~ m/..$/ && $& > $max_line_len;
   printf "%-7s %6d %5.1f%% %6d %5.1f%%\n",
          $keycopy, $len, $len / $line_count * 100, 
          $total, $total / $line_count * 100;;
}

