#!/usr/bin/perl
@name=<STDIN>;
@name1=sort @name;
print "\n";
print @name1,"\n";
foreach $name1 (@name1) 
  {
    chomp $name1;
    print $name1," ";
  }
print "\n\n";
print @name1,"\n";
