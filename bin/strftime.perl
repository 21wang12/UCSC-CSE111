#!/usr/bin/perl
# $Id: strftime.perl,v 1.3 2020-08-20 17:18:16-07 - - $

$0 =~ s|.*/||;
use strict;
use warnings;

use POSIX qw (strftime);

print "qx(date): ", qx(date);
print "%date:    ", strftime "%a %b %e %T %Z %Y\n", localtime();
print "%c:       ", strftime "%c\n", localtime();

