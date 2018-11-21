#!/bin/bash
counter=1
while [ $counter -le 60 ]
do
	echo Frame $counter
	gnome-screenshot -f $counter
	((counter++))
	sleep 0.5
	echo 
done
echo Done!
