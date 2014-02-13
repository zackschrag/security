all:	p1

p1:	encrypt.o matrix.o main.o
	g++ -Wall -I. encrypt.o main.o -o p1

encrypt.o:	encrypt.cpp encrypt.h
	g++ -Wall -g -I. encrypt.cpp -c -o encrypt.o

#matrix.o:	matrix.tpp 
#	g++ -Wall -g -I. matrix.cpp -c -o matrix.o

main.o:	main.cpp matrix.tpp encrypt.h
	g++ -Wall -g -I. main.cpp -c -o main.o

clean:
		rm -f *.o
		rm -f p1
