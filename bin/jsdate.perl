#!/usr/bin/perl
# $Id: jsdate.perl,v 1.67 2021-09-29 15:45:44-07 - - $

$0 =~ s|.*/||;
use strict;
use POSIX qw (strftime);
use warnings;

my @functions;
my %descriptions;
while (defined (my $line = <DATA>)) {
   chomp $line;
   my ($function, $description) = $line =~ m/(.*)\|(.*)/g;
   push @functions, $function;
   $descriptions{$function} = $description;
}

my $outfile = $0;
$outfile =~ s/\.perl$/.html/ or die "$outfile: s/.perl/.html/ failed";
open JSDATE, ">$outfile" or die "$0: $outfile: $!";
print "open >$outfile: OK\n";

my $new_date = <<'________END________';
var date = new Date();
________END________

my $time_ampm_1 = <<'________END________';
function time_ampm_1() {
   var hour = parseInt (date.getHours(), 10);
   var min = ":" + ("0" + date.getMinutes()).slice (-2);
   return (hour % 12 || 12) + min + (hour < 12 ? " AM" : " PM");
}
________END________

my $time_ampm_2 = <<'________END________';
function time_ampm_2() {
   return date.toLocaleTimeString().replace (/:\d\d\s/, " ");
}
________END________

my $date_time_1 = <<'________END________';
function date_time_1() {
   var day = date.toDateString().replace(/ \d+$/,"").replace(/ 0/," ");
   var time = date.toLocaleTimeString().replace (/:\d\d\s/, " ");
   return day + " @ " + time;
}
________END________

my $new_date_html = $new_date;
my $time_ampm_1_html = $time_ampm_1;
my $time_ampm_2_html = $time_ampm_2;
my $date_time_1_html = $date_time_1;
my %html_chars = qw (& &amp; < &lt; > &gt;);
map {
   s/[&<>]/$html_chars{$&}/gm;
   s/^\s+/"&numsp;" x (length $&)/gme;
   s/\n/<BR>\n/gm;
}  $new_date_html,
   $time_ampm_1_html,
   $time_ampm_2_html,
   $date_time_1_html;

print JSDATE <<________END________;
<HEAD>
<STYLE>
BODY {
   color: #00FF00;
   background-color: #000000;
}
TABLE {
   border: 1px solid #00FF00;
   border-spacing: 0;
}
TD {
   border: 1px solid #00FF00;
   padding-top: 0.25ex;
   padding-bottom: 0.25ex;
   padding-left: 0.333em;
   padding-right: 0.333em;
   vertical-align: top;
}
CODE {
   display: block;
   white-space: pre;
}
</STYLE>
<SCRIPT>
$new_date
$time_ampm_1
$time_ampm_2
$date_time_1
________END________

for my $fn (@functions) {
   print JSDATE "function date_$fn { return date.$fn; }\n";
}

print JSDATE <<________END________;
</SCRIPT>
</HEAD>
________END________

sub fn_row($) {
my ($fn) = @_;
<<________END________
<TR>
<TD>$fn</TD>
<TD><SPAN id="$fn">
<SCRIPT>document.getElementById ("$fn").innerHTML = date_$fn;
</SCRIPT></SPAN></TD>
<TD> $descriptions{$fn} </TD>
</TR>
________END________
}

print JSDATE <<________END________;
<BODY>
<TABLE>
<TR>
<TD>date.valueOf()</TD>
<TD><SPAN id="new_date">
<SCRIPT>
document.getElementById ("new_date").innerHTML = date.valueOf();
</SCRIPT></SPAN></TD>
<TD>$new_date_html</TD>
</TR>
<TR>
<TD>time_ampm_1()</TD>
<TD><SPAN id="time_ampm_1">
<SCRIPT>
document.getElementById ("time_ampm_1").innerHTML = time_ampm_1();
</SCRIPT></SPAN></TD>
<TD>$time_ampm_1_html</TD>
</TR>
<TR>
<TD>time_ampm_2()</TD>
<TD><SPAN id="time_ampm_2">
<SCRIPT>
document.getElementById ("time_ampm_2").innerHTML = time_ampm_2();
</SCRIPT></SPAN></TD>
<TD>$time_ampm_2_html</TD>
</TR>
<TR>
<TD>date_time_1()</TD>
<TD><SPAN id="date_time_1">
<SCRIPT>
document.getElementById ("date_time_1").innerHTML = date_time_1();
</SCRIPT></SPAN></TD>
<TD>$date_time_1_html</TD>
</TR>
________END________

print JSDATE fn_row ($_) for @functions;

print JSDATE <<________END________;
</TABLE>
</BODY>
________END________

my $created = strftime "%A %Y %B %e \@ %I:%M:%S %p %Z", localtime $^T;
$created =~ s/\s+0/ /g;
printf JSDATE "<P>Created by %s: %s\n", $0, $created;

close JSDATE;

__DATA__
toLocaleString()|Converts Date object to string, using locale
toLocaleDateString()|Get date portion of Date object, using locale
toLocaleTimeString()|Get time portion of Date object, using locale
toString()|Converts Date object to string
toDateString()|Converts date portion of Date object to string
toTimeString()|Converts time portion of Date object to string
getFullYear()|Get year as four digit number (yyyy)
getMonth()|Get month as number (0-11)
getDate()|Get day as number (1-31)
getHours()|Get hour (0-23)
getMinutes()|Get minute (0-59)
getSeconds()|Get second (0-59)
getMilliseconds()|Get millisecond (0-999)
getTime()|Get time (milliseconds since January 1, 1970)
getDay()|Get weekday as number (0-6)
getTimezoneOffset()|Get difference between UTC and local time, minutes
toISOString()|Get date, using ISO standard
toUTCString()|Converts Date object to string, UTC
getUTCFullYear()|Get year, UTC
getUTCMonth()|Get month, UTC (from 0-11)
getUTCDate()|Get day of month, UTC (from 1-31)
getUTCHours()|Get hour, UTC (from 0-23)
getUTCMinutes()|Get minutes, UTC (from 0-59)
getUTCSeconds()|Get seconds, UTC (from 0-59)
getUTCMilliseconds()|Get milliseconds, UTC (from 0-999)
getUTCDay()|Get day of week, UTC (from 0-6)
toJSON()|Date as a string, formatted as a JSON date
