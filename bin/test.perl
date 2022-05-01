#!/usr/bin/perl
# $Id: cpdir,v 1.1 2019-10-31 13:32:24-07 - - $

use strict;
use warnings;

$0 =~ s|^(.*/)?([^/]+)/*$|$2|;
$SIG{'__DIE__'} = sub {print STDERR "$0: @_"; exit 1};

die "test this\n";
