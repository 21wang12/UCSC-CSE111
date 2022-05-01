#!/usr/bin/perl
# $Id: edit-sfile.perl,v 1.2 2022-03-14 17:52:45-07 - - $

#
# edit-sfile - edit asm .s files
#
# Usage: edit-sfile asm-sfiles...
#
# Edits an sfile.s removing directives, then adding the
# original source file at the beginning.
#

$0 =~ s|.*/||;
$SIG{__DIE__} = sub {print STDERR "@_"; exit 1};
use strict;
use warnings;

my @directives = qw (

   \.align
   \.byte
   \.cfi_
   \.data$
   \.file
   \.globl
   \.ident
   \.long
   \.p2align
   \.quad
   \.section
   \.size
   \.space
   \.text$
   \.type
   \.word

);

my @suffixes = qw (
   _begin:
   _end:
);


die "Usage: $0 sfiles...\n" unless @ARGV > 0;

for my $filename (@ARGV) {
   open my $file, "<$filename" or warn "$0: $filename: $!\n" and next;
   my @contents = <$file>;
   close $file;

   my $oldlines = @contents;
   my @output;
   MAIN: for my $line (@contents) {
      for my $directive (@directives) {
         next MAIN if $line =~ m/^\s+$directive\s+/;
      }
      for my $suffix (@suffixes) {
         next MAIN if $line =~ m/$suffix$/;
      }
      next MAIN if $line =~ m/^\s+\.cfi_/;
      $line =~ s|/\*.*?\*/||;
      next MAIN if $line =~ m/^\s*$/;
      push @output, $line;
   }
   my $newlines = @output;

   open $file, ">$filename" or warn" $0: $filename: $!\n" and next;
   print $file @output;
   close $file;
   print "$0: $filename: $oldlines => $newlines\n";
}

