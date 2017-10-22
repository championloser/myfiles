#!/bin/bash
if [ ! -n "$2" ]
then 
   	num=0
else
	num=$2
fi
ls *.h |xargs grep -A $num $1
