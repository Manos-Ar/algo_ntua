#!/bin/bash
#
## A script to check all testcases for your program. (Version 2: Only one program execution)
## To use it, pass as a parameter your executable file, e.g.: $ ./autotest.sh ./poleodomia
## You may have to change the for loop condition based on the number of testcases.

for ((i=1; i<=40; i=i+1))
do

	echo "-------- Output$i --------"

	## Show Runtime and save the program's output ##
	echo "YOUR TIME:"
	time -p OUT=$(eval "${1} < input${i}.txt")
	echo

	## Prints Expected Output ##
	echo -n "EXP. OUTPUT: "
	cat output$i.txt

	## Prints Produced Output ##
	echo "YOUR OUPUT: $OUT"

	## Check for correct result ##
	echo -n "COMPARISON RESULT: "
	DIFF=$(diff <(echo "$OUT") <(cat output$i.txt))
	if [ "$DIFF" = "" ]
	then echo "SUCCESS!!"
	else
		echo "FAIL!!"
	fi

	echo
	echo
done
