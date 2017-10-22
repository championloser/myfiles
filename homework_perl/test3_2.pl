#!/usr/bin/perl
@num=<STDIN>;
@name=qw(undef fred betty barney dino wilma pebbles bamm-bamm);
foreach $num (@num)
  {
    print $name[$num]," ";
  }
print "\n";

