#!/bin/bash

usage="$0 [[*.cor] [...] (1 min, 4 max)] [begin (0-9)] [end (0-9)]"
num='^[0-9]+$'

args=$#
array=($@)

if [[ $args < 3 ]] || [[ $args > 6 ]]; then
   echo $usage
   exit 1
fi

for f in array
if ! [[ ${filename:${#filename}-4} = '.cor' ]]
   echo $usage
   exit 1
fi

if ! [[ ${filename:${#filename}-4} = '.cor' ]] || ! [[ $3 =~ $num ]] || ! [[ $4 =~ $num ]] ; then
  
make -j 8
if ! [[ test -eq 0 ]] ; then
	exit 1
fi

i=$3

while [ $i -le $4 ]
do
	printf "Testing cycle $i"\\r
	./corewar -n -1 $filename -n -2 $filename2 -d $i > a
	~/Downloads/vm_champs/corewar $filename $filename2 -d $i > b
	diff a b
	ret=$?
	if test $ret -eq 1 ; then
		exit 1
	fi
	((i++))
done

exit 0
