#!/usr/bin/perl
print "Please input a string:";
chomp($str=<STDIN>);
print "Please input a number:";
chomp($num=<STDIN>);
print "$str"x$num."\n";
