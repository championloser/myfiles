#!/usr/bin/perl
print "Pleasee input r:";
chomp($r=<STDIN>);
if($r lt 0)
  {print 0 ."\n";}
else
  {
    $s=2*3.1415926*$r;
    print $s."\n";
  }
