#!/bin/bash

num='^[0-9]+$'
champion1=$1
champion2=$2
start_cycle=$3
end_cycle=$4

if ! [[ $(echo $champion1 | tail -c 5) = '.cor' ]] || ! [[ $(echo $champion2 | tail -c 5) = '.cor' ]]; then
	echo "Wrong champion format..."
	echo "Usage: $0 [champion 1 *.cor] [champion 2 *.cor] [begin cycle (0-9)] [end cycle (0-9)]"
	exit 1
fi
## NOT WORKING
#if ! [[ $start_cyle =~ $num ]] || ! [[ $end_cycle =~ $num ]]; then
#	echo "Wrong cycle value..."
#	echo "Usage: $0 [champion 1 *.cor] [champion 2 *.cor] [begin cycle (0-9)] [end cycle (0-9)]"
#	exit 1
#fi

make -j 8
if [[ test -ne 0 ]] ; then
	exit 1
fi

while [ $start_cycle -le $end_cycle ]
do
	printf "Testing cycle $start_cycle"
#	./corewar -n -1 $filename -n -2 $filename2 -d $i > a
	#	./corewar_zaz $filename $filename2 -d $i > b
#	./corewar -n -1 champ/winner/Bazou.cor -n -2 champ/winner/_.cor -n -3 champ/winner/Octobre_Rouge_V4.2.cor -d $i > a
#	./champ/corewar_zaz champ/winner/Bazou.cor champ/winner/_.cor champ/winner/Octobre_Rouge_V4.2.cor -d $i > b
	
	./corewar -n -1 test.cor -n -2 asm.d/unitest_asm/valid/Car.cor -n -3 asm.d/unitest_asm/valid/Car.cor -n -4 asm.d/unitest_asm/valid/Car.cor -d $start_cycle > a
	./champ/corewar_zaz test.cor asm.d/unitest_asm/valid/Car.cor asm.d/unitest_asm/valid/Car.cor asm.d/unitest_asm/valid/Car.cor -d $start_cycle > b
	diff a b > c
	ret=$?
	if test $ret -eq 1 ; then
		printf " \x1B[31mFAILED\x1B[0m\n"
		cat c
		exit 1
	fi
	printf " \x1B[32mOK\x1B[0m "
	printf " "\\r
	((start_cycle++))
done
echo ""
/bin/rm -f a b c
exit 0
