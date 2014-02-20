#!/bin/bash
# generate

p=257
q=313
n=$(echo $p*$q | bc)
p_minus_one=$(echo $p-1 | bc)
q_minus_one=$(echo $q-1 | bc)
totient_n=$(echo $p_minus_one*$q_minus_one | bc)

i=1
ctr=0
while [ $i -lt $totient_n ]
do
	gcd=$(echo "gcd ($i,$totient_n)" | bc gcd)
	if [ $gcd -eq 1 ]; then
		#echo "$i "
		let ctr++
		if [ $ctr -eq 200 ]; then
			break;
		fi
	fi
	let i++
done
echo $i
e=$i

j=1
while [ $j -lt $totient_n ]
do
	j_times_e=$(echo $j*$e | bc)
	j_times_e_mod_totient_n=$(echo $j_times_e%$totient_n | bc)
	if [ $j_times_e_mod_totient_n -eq 1 ]; then
		break;
	fi
	let j++
done
echo $j
d=$j
echo "$e, $n" > Zack-Schrag.publickey
echo "$d, $n" > private_key
