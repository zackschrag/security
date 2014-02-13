/*
*	Zack Schrag
*	CS356
*	2-13-2014
*/

#include <decrypt.h>

bool validate(string key);
string modify(string key);

bool validate(string key) {
	string modifiedKey;
	if (key.length() < 10) {
		cout << "Please enter a key of at least 10 characters" << endl;
		return false;
	}
	modifiedKey = modify(key);
	if (modifiedKey.length() < 10) {
		cout << "Please enter a key of at least 10 characters" << endl;
		return false;
	}
	return true;
}

string modify(string key) {
	string modifiedKey = key;
	std::transform(modifiedKey.begin(), modifiedKey.end(), modifiedKey.begin(), ::tolower);
	modifiedKey.erase( std::remove_if( modifiedKey.begin(), modifiedKey.end(), ::isspace ), modifiedKey.end() );
	vector<char> letters;
	string newKey;

	for (uint i = 0; i < modifiedKey.length(); i++) {
		bool unique = true;
		for (uint j = 0; j < letters.size(); j++) {
			if (modifiedKey.at(i) == letters[j]) {
				unique = false;
			}			
		}
		if (unique) {
			letters.push_back(modifiedKey.at(i));			
		}
	}

	uint len = letters.size();
	if (letters.size() > 10) {
		for (uint i = 0; i < (len - 10); i++) {
			letters.pop_back();
		}
	}

	for (uint i = 0; i < letters.size(); i++) {
		newKey.push_back(letters[i]);
	}
	//cout << "key: " << newKey << endl;
	return newKey;
}

int main(int argc, char* argv[]) {
	int SIZE = 2048;
	char k1[SIZE];
	char k2[SIZE];
	string filename;
	ifstream file;
	//Encrypt en;

	cout << "Enter key1: ";
	cin.getline(k1, SIZE);
	while (!validate(k1)) {
		cout << "Enter key1: ";
		cin.getline(k1, SIZE);
	}
	cout << "Enter key2: ";
	cin.getline(k2, SIZE);
	while (!validate(k2)) {
		cout << "Enter key2: ";
		cin.getline(k2, SIZE);
	}
	cout << "Enter filename: ";
	cin >> filename;
	file.open(filename.c_str());
	while (file.fail()) {
		cout << "File: \'" << filename << "\' does not exist, please enter a valid filename" << endl;
		cout << "Enter filename: ";
		cin >> filename;
		file.open(filename.c_str());
	}
	file.close();

	string newKey1(k1);
	string newKey2(k2);
	string mKey1 =	modify(newKey1);
	string mKey2 =	modify(newKey2);
	Decrypt de(mKey1, mKey2, filename);

	return 0;
}

























