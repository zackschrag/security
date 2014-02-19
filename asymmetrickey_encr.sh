#!/bin/bash
# asymmetrickey_encr

# Check that correct number of arguments is passed
if [ "$#" -ne 2 ];
then
	echo "Usage: asymmetrickey_encr.sh <file1> <file2>"
	exit
fi

publicKey=""
key1=""
key2=""
while read line
do
	#echo $line;
	ctr=0;
	for element in ${line/,} ; do
		if [ $ctr -eq 0 ];
		then 
			key1=$element
		elif [ $ctr -eq 1 ];
		then
			key2=$element
		fi
		let ctr++
	done
done < $1

publicKey="$key1, $key2"
#echo $key1
#echo $key2
#echo $publicKey

while read line
do
	echo "$line" | while read -n 1 i; do printf "%d " "'$i" >> "Zack-Schrag.ciphertext"; 
done

done < $2
