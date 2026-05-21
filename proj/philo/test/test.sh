#!/bin/bash

count=0
readonly MAX_TRY=10

if [ $# -eq 0 ]
then
	echo "Error: Give your arguments."
	return 2> /dev/null || exit 1
fi

make
echo ""
echo "===TESTING PHILOSOPHERS==="
echo "===TRY <./philo $@> IN $MAX_TRY TIMES==="
echo "testing ..."

while true
do
	./philo $@ > log 2> err_log
	count=$((count + 1))

	if grep -q "died" log
	then
		echo -n "result: "
		echo "died at try $count"
		break
	fi

	if (( count == MAX_TRY ))
	then
		echo -n "result: "
		echo "No philosopher died with $count try"
		break
	fi
done
