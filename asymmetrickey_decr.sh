#!/bin/bash
# asymmetrickey_decr

# Check that correct number of arguments is passed
if [ "$#" -ne 2 ];
then
	echo "Usage: asymmetrickey_encr.sh <file1> <file2>"
	exit
fi

d=""
n=""
while read line
do
	#echo $line;
	ctr=0;
	for element in ${line/,} ; do
		if [ $ctr -eq 0 ];
		then 
			d=$element
		elif [ $ctr -eq 1 ];
		then
			n=$element
		fi
		let ctr++
	done
done < $1

privateKey="$d, $n"

#a=1
#while [ $a -lt $n ]
#do
#m=$a
#echo ""
#echo "d: $d"
#echo "plaintext: $m" 
#m_to_e=$(echo $m^$e | bc)
#encrypt=$(echo $m_to_e%$n | bc)
#echo "ciphertext: $encrypt"
#encrypt_to_d=$(echo $encrypt^$d | bc)
#encrypt_to_d=$(echo $encrypt_to_d | tr -d "\\\\" | tr -d " ")
#echo "encrypt_to_d: $encrypt_to_d"
#decrypt=$(echo $encrypt_to_d%$n | bc)
#echo "decrypted text: $decrypt"
#echo ""
#let a++
#done

message="" #$(echo $1 | tr " " "\n")

printf "" :> "Zack-Schrag.plaintext";
while read line
do
	message+=$line
done < $2
echo $message

















