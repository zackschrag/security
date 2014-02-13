/*
*	Zack Schrag
*	CS356
*	2-13-2014
*/

#include <decrypt.h>

Decrypt::Decrypt(string k1, string k2, string fn) {
	key1 = k1;
	key2 = k2;
	filename = fn;
	sentence = getSentence();
	buildTable();
}

Decrypt::~Decrypt() {
	delete clearTextTable;
	clearTextTable = NULL;
	delete cipherTextTable;
	cipherTextTable = NULL;
}

string Decrypt::getSentence() {
	string message = "";
	string line;

	file.open(filename.c_str());

	while (getline(file, line)) {
		message.append(line);
	}
	//cout << message << endl;

	file.close();
	return message;
}

int Decrypt::indexOf(vector<char> v, char c) {
	for (uint i = 0; i < v.size(); i++) {
		if (v.at(i) == c) {
			return i;
		}
	}
	return -1;
}

void Decrypt::buildTable() {
	int width = 10;
	int height;
	int sentenceLength = sentence.length();
	int indices[10];

	if (sentenceLength%10 == 0) {
		height = sentenceLength/10 + 1;
	} 
	else {
		height = sentenceLength/10 + 2;	
	}
	clearTextTable = new Matrix<char>(width, height);
	vector<char> sortedLetters;
	vector<char> letters;
	for (uint i = 0; i < key1.length(); i++) {
		letters.push_back(key1.at(i));			
	}

	sortedLetters = letters;
	std::sort(sortedLetters.begin(), sortedLetters.end());	

	for (uint i = 0; i < sortedLetters.size(); i++) {
		int index = indexOf(letters, sortedLetters.at(i));
		indices[i] = index;
	}

	for (int i = 0; i < width; i++) {
		clearTextTable->add(key2.at(i));
	}

	int size = clearTextTable->width()*clearTextTable->height();
	for (int i = 0; i < size-width; i++) {
		clearTextTable->add(sentence.at(i));
	}
	//clearTextTable->print();

	cipherTextTable = new Matrix<char>(width, height);
	// push key1 to top
	for (int i = 0; i < cipherTextTable->width(); i++) {
		cipherTextTable->add(key1.at(i));
	}
	int ctr = 0;
	for (int row = 0; row < clearTextTable->width(); row++) {
		for (int col = 1; col < clearTextTable->height(); col++) {
			cipherTextTable->set(col, indices[row], sentence.at(ctr));
			ctr++;
		}
	}
	//cout << endl;
	//cipherTextTable->print();
	ofstream outfile("Zack-Schrag-decrypted-str.txt");
	for (int i = 1; i < cipherTextTable->height(); i++) {
		for (int j = 0; j < cipherTextTable->width(); j++) {
			outfile << cipherTextTable->at(i, j);
		}
	}
}
// key1: cryptographic
// key2: networksecurity
// filename: Zack-Schrag-encrypted-str.txt