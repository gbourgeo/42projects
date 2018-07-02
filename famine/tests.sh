#/bin/bash

make re

rm -rf /tmp/test/ /tmp/test2/
mkdir -p /tmp/test/ /tmp/test2/

gcc -o Ressources/elf64 -m64 Ressources/sample.c
cp Ressources/elf64 /tmp/test/.
cp Ressources/elf64 /tmp/test2/.

echo -n "Test 1: The Infection... "
./Famine
strings_test=$(strings /tmp/test/* | grep Famine | wc -l)
strings_test2=$(strings /tmp/test2/* | grep Famine | wc -l)
if [ $strings_test != "1" ] || [ $strings_test2 != "1" ]
then
	echo -n "\e[31;1m"
	echo "Failed !"
	echo "Expected: 1"
	echo "Got     : $strings_test"
	echo "\e[0m"
	exit
fi
expected=$(./Ressources/elf64)
got=$(/tmp/test/elf64)
got2=$(/tmp/test2/elf64)
if [ "$expected" != "$got" ] || [ "$expected" != "$got2" ]
then
	echo -n "\e[31;1m"
	echo "Failed !"
	echo "\tExpected: " $expected
	echo "\tGot     : " $got
	echo "\tGot2    : " $got2
	echo "\e[0m"
	exit
fi
echo "\e[32;1mOK !\e[0m"

echo -n "Test 2: No Re-infection... "
./Famine
strings_test=$(strings /tmp/test/* | grep Famine | wc -l)
strings_test2=$(strings /tmp/test2/* | grep Famine | wc -l)
if [ $strings_test != "1" ] || [ $strings_test2 != "1" ]
then
	echo -n "\e[31;1m"
	echo "Failed !"
	echo "Expected: 1"
	echo "Got     : $strings_test"
	echo "\e[0m"
	exit
fi
echo "\e[32;1mOK !\e[0m"

echo -n "Test 3: No Infection on unsupported file type... "
gcc -o Ressources/elf32 -m32 Ressources/sample.c
cp Ressources/elf32 /tmp/test/.
cp Ressources/elf32 /tmp/test2/.
cp auteur /tmp/test/.
cp auteur /tmp/test2/.
./Famine
strings_test=$(strings /tmp/test/* | grep Famine | wc -l)
strings_test2=$(strings /tmp/test2/* | grep Famine | wc -l)
if [ $strings_test != "1" ] || [ $strings_test2 != "1" ]
then
	echo -n "\e[31;1m"
	echo "Failed !"
	echo "Expected: 1"
	echo "Got     : $strings_test"
	echo "\e[0m"
	exit
fi
echo "\e[32;1mOK !\e[0m"

echo -n "Test 4: Infection on system binaries... "
cp /bin/echo /tmp/test/.
cp /bin/echo /tmp/test2/.
./Famine
expected=$(/bin/echo COUCOU LES ZAMIS)
got=$(/tmp/test/echo COUCOU LES ZAMIS)
got2=$(/tmp/test2/echo COUCOU LES ZAMIS)
if [ "$expected" != "$got" ] || [ "$expected" != "$got2" ]
then
	echo -n "\e[31;1m"
	echo "Failed ! (/bin/echo COUCOU LES ZAMIS)"
	echo "Expected: " $expected
	echo "Got     : " $got
	echo "Got2    : " $got2
	echo "\e[0m"
	exit
fi

cp /bin/ls /tmp/test/.
cp /bin/ls /tmp/test2/.
./Famine
expected=$(/bin/ls)
got=$(/tmp/test/ls)
got2=$(/tmp/test2/ls)
if [ "$expected" != "$got" ] || [ "$expected" != "$got2" ]
then
	echo -n "\e[31;1m"
	echo "Failed ! (/bin/ls)"
	echo "Expected: " $expected
	echo "Got     : " $got
	echo "Got2    : " $got2
	echo "\e[0m"
	exit
fi
expected=$(/bin/ls -la /bin)
got=$(/tmp/test/ls -la /bin)
got2=$(/tmp/test2/ls -la /bin)
if [ "$expected" != "$got" ] || [ "$expected" != "$got2" ]
then
	echo -n "\e[31;1m"
	echo "Failed ! (/bin/ls -la /bin)"
	echo "Expected: " $expected
	echo "Got     : " $got
	echo "Got2    : " $got2
	echo "\e[0m"
	exit
fi

cp /bin/date /tmp/test/.
cp /bin/date /tmp/test2/.
./Famine
expected=$(/bin/date)
got=$(/tmp/test/date)
got2=$(/tmp/test2/date)
if [ "$expected" != "$got" ] || [ "$expected" != "$got2" ]
then
	echo -n "\e[31;1m"
	echo "Failed ! (/bin/date)"
	echo "Expected: " $expected
	echo "Got     : " $got
	echo "Got2    : " $got2
	echo "\e[0m"
	exit
fi

cp /bin/bash /tmp/test/.
cp /bin/bash /tmp/test2/.
./Famine
strings_test=$(strings /tmp/test/* | grep Famine | wc -l)
strings_test2=$(strings /tmp/test2/* | grep Famine | wc -l)
expected=$(/bin/bash -c ls)
got=$(/tmp/test/bash -c ls)
got2=$(/tmp/test2/bash -c ls)
if [ $strings_test != "5" ] || [ $strings_test2 != "5" ]
then
	echo -n "\e[31;1m"
	echo "Failed ! (/bin/bash -c ls)"
	echo "Expected: 2"
	echo "Got     : " $strings_test
	echo "Got2    : " $strings_test2
	echo "\e[0m"
	exit
elif [ "$expected" != "$got" ] || [ "$expected" != "$got2" ]
then
	echo -n "\e[31;1m"
	echo "Failed ! (/bin/bash -c ls)"
	echo "Expected: " $expected
	echo "Got     : " $got
	echo "Got2    : " $got2
	echo "\e[0m"
	exit
fi

cp /bin/cat /tmp/test/.
cp /bin/cat /tmp/test2/.
./Famine
expected=$(/bin/cat /tmp/test/auteur)
got=$(/tmp/test/cat /tmp/test/auteur)
got2=$(/tmp/test2/cat /tmp/test/auteur)
if [ "$expected" != "$got" ] || [ "$expected" != "$got2" ]
then
	echo -n "\e[31;1m"
	echo "Failed ! (/bin/cat /tmp/test/auteur)"
	echo "Expected: " $expected
	echo "Got     : " $got
	echo "Got2    : " $got2
	echo "\e[0m"
	exit
fi
echo "\e[32;1mOK !\e[0m"

rm -rf /tmp/test/ /tmp/test2/
mkdir -p /tmp/test/ /tmp/test2/
cp Ressources/elf64 /tmp/test/.
./Famine

echo -n "Test 5: The Propagation... "
cp Ressources/elf64 /tmp/test2/.
cp Ressources/elf32 /tmp/test/.
cp Ressources/elf32 /tmp/test2/.
cp auteur /tmp/test/.
cp auteur /tmp/test2/.
cp Makefile /tmp/test/.
cp Makefile /tmp/test2/.
cp /usr/libx32/libutil.a /tmp/test/.
cp /usr/libx32/libutil.a /tmp/test2/.
cp /bin/echo /tmp/test/.
cp /bin/echo /tmp/test2/.
cp /bin/ls /tmp/test/.
cp /bin/ls /tmp/test2/.
cp /bin/date /tmp/test/.
cp /bin/date /tmp/test2/.
cp /bin/bash /tmp/test/.
cp /bin/bash /tmp/test2/.
cp /bin/cat /tmp/test/.
cp /bin/cat /tmp/test2/.
/tmp/test/elf64 1>/dev/null
expected=$(./Ressources/elf64)
got=$(/tmp/test/elf64)
got2=$(/tmp/test2/elf64)
if [ "$expected" != "$got" ] || [ "$expected" != "$got2" ]
then
	echo -n "\e[31;1m"
	echo "Failed !"
	echo "\tExpected: " $expected
	echo "\tGot     : " $got
	echo "\tGot2    : " $got2
	echo "\e[0m"
	exit
fi
expected=$(./Ressources/elf32)
got=$(/tmp/test/elf32)
got2=$(/tmp/test2/elf32)
if [ "$expected" != "$got" ] || [ "$expected" != "$got2" ]
then
	echo -n "\e[31;1m"
	echo "Failed !"
	echo "\tExpected: " $expected
	echo "\tGot     : " $got
	echo "\tGot2    : " $got2
	echo "\e[0m"
	exit
fi
expected=$(cat auteur)
got=$(cat /tmp/test/auteur)
got2=$(cat /tmp/test2/auteur)
if [ "$expected" != "$got" ] || [ "$expected" != "$got2" ]
then
	echo -n "\e[31;1m"
	echo "Failed !"
	echo "\tExpected: " $expected
	echo "\tGot     : " $got
	echo "\tGot2    : " $got2
	echo "\e[0m"
	exit
fi
expected=$(cat Makefile)
got=$(cat /tmp/test/Makefile)
got2=$(cat /tmp/test2/Makefile)
if [ "$expected" != "$got" ] || [ "$expected" != "$got2" ]
then
	echo -n "\e[31;1m"
	echo "Failed !"
	echo "\tExpected: " $expected
	echo "\tGot     : " $got
	echo "\tGot2    : " $got2
	echo "\e[0m"
	exit
fi
expected=$(/bin/echo COUCOU LES ZAMIS)
got=$(/tmp/test/echo COUCOU LES ZAMIS)
got2=$(/tmp/test2/echo COUCOU LES ZAMIS)
if [ "$expected" != "$got" ] || [ "$expected" != "$got2" ]
then
	echo -n "\e[31;1m"
	echo "Failed ! (/bin/echo COUCOU LES ZAMIS)"
	echo "Expected: " $expected
	echo "Got     : " $got
	echo "Got2    : " $got2
	echo "\e[0m"
	exit
fi
expected=$(/bin/ls)
got=$(/tmp/test/ls)
got2=$(/tmp/test2/ls)
if [ "$expected" != "$got" ] || [ "$expected" != "$got2" ]
then
	echo -n "\e[31;1m"
	echo "Failed ! (/bin/ls)"
	echo "Expected: " $expected
	echo "Got     : " $got
	echo "Got2    : " $got2
	echo "\e[0m"
	exit
fi
expected=$(/bin/date)
got=$(/tmp/test/date)
got2=$(/tmp/test2/date)
if [ "$expected" != "$got" ] || [ "$expected" != "$got2" ]
then
	echo -n "\e[31;1m"
	echo "Failed ! (/bin/date)"
	echo "Expected: " $expected
	echo "Got     : " $got
	echo "Got2    : " $got2
	echo "\e[0m"
	exit
fi
expected=$(/bin/bash -c ls)
got=$(/tmp/test/bash -c ls)
got2=$(/tmp/test2/bash -c ls)
if [ "$expected" != "$got" ] || [ "$expected" != "$got2" ]
then
	echo -n "\e[31;1m"
	echo "Failed ! (/bin/bash -c ls)"
	echo "Expected: " $expected
	echo "Got     : " $got
	echo "Got2    : " $got2
	echo "\e[0m"
	exit
fi
expected=$(/bin/cat /tmp/test/auteur)
got=$(/tmp/test/cat /tmp/test/auteur)
got2=$(/tmp/test2/cat /tmp/test/auteur)
if [ "$expected" != "$got" ] || [ "$expected" != "$got2" ]
then
	echo -n "\e[31;1m"
	echo "Failed ! (/bin/cat /tmp/test/auteur)"
	echo "Expected: " $expected
	echo "Got     : " $got
	echo "Got2    : " $got2
	echo "\e[0m"
	exit
fi
strings_test=$(strings /tmp/test/* | grep "Famine " | wc -l)
strings_test2=$(strings /tmp/test2/* | grep "Famine " | wc -l)
if [ $strings_test != "6" ] || [ $strings_test2 != "6" ]
then
	echo -n "\e[31;1m"
	echo "Failed !"
	echo "Expected: 6"
	echo "Got     : " $strings_test
	echo "Got2    : " $strings_test2
	echo "\e[0m"
	exit
fi
echo "\e[32;1mOK !\e[0m"

echo -n "Test 6: No-reinfection v2... "
./Famine
/tmp/test/elf64 1>/dev/null
/tmp/test/cat auteur 1>/dev/null
/tmp/test/ls 1>/dev/null
/tmp/test/echo toto 1>/dev/null
/tmp/test/bash -c ls 1>/dev/null
/tmp/test/elf64 1>/dev/null
/tmp/test/cat auteur 1>/dev/null
/tmp/test/ls 1>/dev/null
/tmp/test/echo toto 1>/dev/null
/tmp/test/bash -c ls 1>/dev/null
./Famine
strings_test=$(strings /tmp/test/* | grep "Famine " | wc -l)
strings_test2=$(strings /tmp/test2/* | grep "Famine " | wc -l)
if [ $strings_test != "6" ] || [ $strings_test2 != "6" ]
then
	echo -n "\e[31;1m"
	echo "Failed !"
	echo "Expected: 6"
	echo "Got     : " $strings_test
	echo "Got2    : " $strings_test2
	echo "\e[0m"
	exit
fi
echo "\e[32;1mOK !\e[0m"

rm -rf /tmp/test /tmp/test2
exit
