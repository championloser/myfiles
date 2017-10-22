#!/usr/bin/perl
use 5.010;
sub greet
{
  state $sum = 0;
  state @name;
  foreach my $i (@_){push @name,$i; $sum=$sum+1;}
  if($sum == 1){print "Hi @_! You are the first one here!\n";}
  else {print "Hi @_! ".$name[$#name-1]."is also here!\n";}
  
}
greet("Fred");
greet("Barney");
greet("Wilma");
