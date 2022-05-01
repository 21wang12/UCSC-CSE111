#!/usr/bin/perl

use Cwd;
use strict;
use warnings;

my $fmt = "%-8s [%s]\n";

my $command = "/usr/bin/pwd";
open PWD, "$command |";
my $pwd = <PWD>;
close PWD;
chomp $pwd;
printf $fmt, $command, $pwd;

printf $fmt, "ENV{PWD}", $ENV{PWD};

my $qx_pwd = qx(pwd);
chomp $qx_pwd;
printf $fmt, "qx(pwd)", $qx_pwd;

my $cwd = cwd();
printf $fmt, "cwd()", $cwd;

my $getcwd = getcwd();
printf $fmt, "getcwd()", $qx_pwd;

