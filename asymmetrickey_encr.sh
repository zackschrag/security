#!/bin/bash
# asymmetrickey_encr

# Check that correct number of arguments is passed
if [ "$#" -ne 2 ];
then
	echo "Usage: asymmetrickey_encr.sh <file1> <file2>"
	exit
fi

publicKey=""
e=""
n=""
while read line
do
	#echo $line;
	ctr=0;
	for element in ${line/,} ; do
		if [ $ctr -eq 0 ];
		then 
			e=$element
		elif [ $ctr -eq 1 ];
		then
			n=$element
		fi
		let ctr++
	done
done < $1

publicKey="$e, $n"
#p=11
#q=7
#p_times_q=$(echo $p*$q | bc)
#p_minus_one=$(echo $p-1 | bc)
#q_minus_one=$(echo $q-1 | bc)
#totient_n=$(echo $p_minus_one*$q_minus_one | bc)

#d=1
#while [ $d -lt $totient_n ]
#do
#	d_times_e=$(echo $d*$e | bc)
#	d_times_e_mod_totient=$(echo $d_times_e%$totient_n | bc)

#	if [ $d_times_e_mod_totient -eq 1 ]; then
#		break
#	fi
#	let d++
#done

# at this point we have generated d correctly
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



printf "" :> "Zack-Schrag.ciphertext";
while read line
do
	echo "$line" | while read -n 1 i; do
		asc=$(printf "%d\n" "'$i")
		if [ $asc -eq 0 ]; then
			ciphertext=$(echo $asc^$e%$n | bc)
			printf "\n%d\n" $ciphertext >> "Zack-Schrag.ciphertext";
		elif [ $asc -eq 46 ]; then
			printf "" >> "Zack-Schrag.ciphertext";
		else
			ciphertext=$(echo $asc^$e%$n | bc)
			printf "%d " $ciphertext >> "Zack-Schrag.ciphertext";
		fi

	done
done < $2
