/*
*	Zack Schrag
*	CS356
*	2-13-2014
*/

#ifndef DECRYPT_H 
#define	DECRYPT_H

#include <matrix.tpp>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;
using std::ofstream;
using std::ifstream;
using std::stringstream;
using std::vector;

typedef unsigned int uint;
class Decrypt {
public:
	string key1;
	string key2;
	string filename;
	ifstream file;
	string sentence;
	Matrix<char>* clearTextTable;	
	Matrix<char>* cipherTextTable;
	
	Decrypt(string k1, string k2, string filename);
	~Decrypt();

private:
	// check if key is valid: alphabetic chars, > 10 chars
	bool validate(string key);
	// remove duplicates, shorten to 10 chars, to lower case
	string modify(string key);
	string getSentence();
	void buildTable();
	int indexOf(vector<char> v, char c);
};

#endif
