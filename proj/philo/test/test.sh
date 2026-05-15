#!/bin/bash

count=0
readonly MAX_TRY=20

while true
do
	./philo $@ > log

	count=$((count + 1))

	if grep -q "died" log
	then
		echo "died at try $count"
		break
	fi

	if (( count == MAX_TRY ))
	then
		echo "No philosopher died with $count try"
		break
	fi

done
