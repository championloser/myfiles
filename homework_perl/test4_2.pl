#!/usr/bin/perl
sub total
  {
    my $sum=0;
    foreach my $i (@_)
      {$sum =$sum + $i;}
    return $sum;
  }
my $fred_total = total(1..1000);
print "The total from 1 to 1000 is $fred_total.\n";

