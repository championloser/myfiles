#!/usr/bin/perl
sub getaverage
  {
    my $ave;
    my $sum=0;
    my $num=@_;
    foreach my $i (@_)
      {
        $sum=$sum+$i;
      }
    $ave=$sum/$num;
    return $ave;
  }
sub above_average
  {
    my $average=&getaverage(@_);
    my @aboveave;
    foreach my $i (@_)
      {
        if($i>$average){push @aboveave,$i;}
      }
    return @aboveave;
  }
my @fred = above_average(1..10);
print "\@fred is @fred\n";
print "(Should be 6 7 8 9 10)\n";
my @barney = above_average(100,1..10);
print "\@barney is @barney\n";
print "(Should be just 100)\n";

