#!/bin/bash

num='^[0-9]+$'
filename=$1
filename2=$2
#if ! [[ ${filename:${#filename}-4} = '.cor' ]] || ! [[ ${filename:${#filename}-4} = '.cor' ]] || ! [[ $3 =~ $num ]] || ! [[ $4 =~ $num ]] ; then
#   echo "$0 [*.cor] [*.cor] [begin (0-9)] [end (0-9)]"
#   exit 1
#fi

make -j 8
if [[ test -ne 0 ]] ; then
	exit 1
fi

i=$3

while [ $i -le $4 ]
do
	printf "Testing cycle $i"
#	./corewar -n -1 $filename -n -2 $filename2 -d $i > a
	#	./corewar_zaz $filename $filename2 -d $i > b
#	./corewar -n -1 champ/winner/Bazou.cor -n -2 champ/winner/_.cor -n -3 champ/winner/Octobre_Rouge_V4.2.cor -d $i > a
#	./champ/corewar_zaz champ/winner/Bazou.cor champ/winner/_.cor champ/winner/Octobre_Rouge_V4.2.cor -d $i > b
	
	./corewar -n -1 test.cor -n -2 asm.d/unitest_asm/valid/Car.cor -n -3 asm.d/unitest_asm/valid/Car.cor -n -4 asm.d/unitest_asm/valid/Car.cor -d $i > a
	./champ/corewar_zaz test.cor asm.d/unitest_asm/valid/Car.cor asm.d/unitest_asm/valid/Car.cor asm.d/unitest_asm/valid/Car.cor -d $i > b
	diff a b > c
	ret=$?
	if test $ret -eq 1 ; then
		printf " \x1B[31mFAILED\x1B[0m\n"
		cat c
		exit 1
	fi
	printf " \x1B[32mOK\x1B[0m "
	printf " "\\r
	((i++))
done
echo ""
/bin/rm -f a b c
exit 0
