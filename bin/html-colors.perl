#!/usr/bin/perl
# $Id: html-colors.perl,v 1.28 2021-10-11 13:59:47-07 - - $
# Make html color table.

$0 =~ s|.*/||;
use strict;
use warnings;

my $htfile = $0;
$htfile =~ s/\.perl$/.html/ or die "$htfile: s/.perl/.html/ failed";
open HTML, ">$htfile" or die "$0: $htfile: $!";
print "open >$htfile: OK\n";

sub color($) {
   my ($color) = @_;
   my $result = "#";
   $result .= sprintf "%02X", ($color >> $_ & 1) * 0xFF for 2, 1, 0;
   return $result;
}
my @colors = qw (Black Blue Green Cyan Red Magenta Yellow White);

my $html_style = <<____END_HTML_STYLE____;
   <TITLE>$0 &gt;$htfile</TITLE>
   <STYLE>
   TABLE {
      border-style: solid;
      border-width: 2px;
      border-spacing: 0;
   }
   TD {
      font-size: 1.1em;
      line-height: 0.9em;
      border-style: solid;
      border-width: 2px;
      padding-top: 0.25ex;
      padding-bottom: 0.125ex;
      padding-left: 0.5em;
      padding-right: 0.5em;
   }
   </STYLE>
____END_HTML_STYLE____
$html_style =~ s/^\s{3}//mg;

print HTML "<HEAD>\n$html_style</HEAD>\n";
print HTML "<BODY>\n";
print HTML "<TABLE>\n";

for my $bkgnd (0..7) {
   my $bgcolor = color $bkgnd;
   print HTML "<TR>\n";
   for my $text (0..7) {
      my $txtcolor = color $text;
      print HTML "<TD bgcolor=$bgcolor><FONT color=$txtcolor><B>\n";
      print HTML "$colors[$text]<BR><KBD>$txtcolor</KBD><BR>\n";
      print HTML "$colors[$bkgnd]<BR><KBD>$bgcolor</KBD><BR>\n";
      print HTML "</B></TD>\n";
   }
   print HTML "</TR>\n";
}

print HTML "</TABLE>\n";
printf HTML "<KBD>Possible colors = (2**8)**3 = %d**3 = %d</KBD>\n",
            2**8, (2**8)**3;
print HTML "</BODY>\n";
close HTML;
