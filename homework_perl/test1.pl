#!/usr/bin/perl
use 5.010;
sub marine
{
  state $n = 0;
  $n += 1;
  print "hello,$n.\n";

}
&marine;
&marine;
&marine;
