#!/bin/bash

count=0
success=0
error=0
crash=0
nc=0

asm_entry="./asm"
asm_zaz="unitest_asm/asm_zaz"

for entry in "unitest_asm/err"/*.s
do
	count=$((count + 1))
	err=$(echo $(./asm $entry >&/dev/null ; echo $?))
	target=$(echo $entry | cut -f3 -d"/")
	if [ "$err" -eq 1 ]
	then
		success=$((success + 1))
		printf "%-40s\033[32m%40s\033[0m\n" $target "OK"
	elif [ "$err" -gt 1 ]
	then
		crash=$((crash + 1))
		printf "%-40s\033[31m%40s\033[0m\n" $target ">0"
	else
		error=$((error + 1))
		printf "%-40s\033[31m%40s\033[0m\n" $target "NO"
	fi
done

for entry in "unitest_asm/valid"/*.s
do
	count=$((count + 1))
	err=$(echo $(./asm -f . $entry >&/dev/null ; echo $?))
	target=$(echo $entry | cut -f3 -d"/")
	if [ "$err" -eq 0 ]
	then
		val=${target/".s"/".cor"}
		$(hexdump $val > file1)
		errb=$(echo $(./$asm_zaz $entry >&/dev/null; echo $?))
		if [ "$errb" -eq 0 ]
		then
			$(hexdump ${entry/".s"/".cor"} > file2)
			diff=$(diff file1 file2)
			if [ -z "$diff" ]
			then
				success=$((success + 1))
				printf "%-40s\033[32m%40s\033[0m\n" $target "OK"
			else
				error=$((error + 1))
				printf "%-40s\033[31m%40s\033[0m\n" $target "NO"
			fi
		else
			printf "%-40s\033[31m%40s\033[0m\n" $target "Zaz does not compile"
		fi
		rm file1
		rm file2
	elif [ "$err" -gt 1 ]
	then
		crash=$((crash + 1))
		printf "%-40s\033[31m%40s\033[0m\n" $target ">0"
	else
		nc=$((nc + 1))
		printf "%-40s\033[31m%40s\033[0m\n" $target "NO_COR"
	fi
done

printf "\n\t\tnumber of test : $count\n"
printf "\t\tsuccess $success - error $error - crash $crash - assemble to .cor failed $nc\n"
rm *.cor 2>&-
rm unitest_asm/valid/*.cor 2>&-
