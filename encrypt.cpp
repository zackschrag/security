#include <encrypt.h>

Encrypt::Encrypt(string k1, string k2, string fn) {
	key1 = k1;
	key2 = k2;
	filename = fn;
	sentence = getSentence();
	buildTable();
}

string Encrypt::getSentence() {
	string message = "";
	string line;

	file.open(filename.c_str());

	while (getline(file, line)) {
		message.append(line);
	}
	cout << message << endl;

	file.close();
	return message;
}

void Encrypt::buildTable() {
	int width = 10;
	int height = (sentence.length()/10) + sentence.length()%10; 
	vector<char> sortedLetters;
	vector<char> letters;
	for (uint i = 0; i < key1.length(); i++) {
		letters.push_back(key1.at(i));			
	}
	sortedLetters = letters;
	std::sort(sortedLetters.begin(), sortedLetters.end());	

	for (uint i = 0; i < sortedLetters.size(); i++) {
		//cout << sortedLetters.at(i) << endl;
	}

	cout << height << endl;
	cout << sentence.length() << endl;
	Matrix<char> m(width, height);
	for (uint i = 0; i < sentence.length(); i++) {
		//cout << sentence.at(i) << endl;
		m.add(sentence.at(i));
		//int index = std::find(letters.begin(), letters.end(), sortedLetters.at(0)) - letters.begin();
		//clearTextTable.push_back(sentence.at(i));
	}
	cout << m.at(0,0) << endl;
	m.print();
}

