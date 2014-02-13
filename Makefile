#	Zack Schrag
#	CS356
#	2-13-2014


all:	transposition-encr transposition-decr

transposition-encr:	encrypt.o encrypt-main.o
	g++ -Wall -I. encrypt.o encrypt-main.o -o transposition-encr

encrypt.o:	encrypt.cpp encrypt.h
	g++ -Wall -g -I. encrypt.cpp -c -o encrypt.o

encrypt-main.o:	encrypt-main.cpp matrix.tpp encrypt.h
	g++ -Wall -g -I. encrypt-main.cpp -c -o encrypt-main.o

transposition-decr:	decrypt.o decrypt-main.o
	g++ -Wall -I. decrypt.o decrypt-main.o -o transposition-decr

decrypt.o:	decrypt.cpp decrypt.h
	g++ -Wall -g -I. decrypt.cpp -c -o decrypt.o

decrypt-main.o:	decrypt-main.cpp matrix.tpp decrypt.h
	g++ -Wall -g -I. decrypt-main.cpp -c -o decrypt-main.o

clean:
		rm -f *.o
		rm -f transposition-encr
		rm -f transposition-decr
