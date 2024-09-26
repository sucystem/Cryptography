#include <iostream>
#include <string>
#include <ctime>
#include <random>

#include "SubstitutionCipher.h"
#include "BruteForce.h"

using namespace std;
using namespace cipher;

std::string generatePlaintext(int size) {
	std::string text;

	//Initialize random device
	mt19937 mtrand((unsigned int)time(NULL));
	uniform_int_distribution<int> dist(0, size - 1);
	uniform_int_distribution<int> text_length(1, 256);

	for (int i = 0; i < text_length(mtrand); ++i)
		text.push_back(dist(mtrand) + 65);

	return text;
}

int main() {
	int size;
	string plaintext;
	clock_t start, end;

	//Input Alphabet Size
	cout << "Alphabet Size : ";
	cin >> size;
	cin.ignore();
	SubstitutionCipher encrypt(size);
	BruteForce attack(size);

	//Input Plaintext
	//cout << "Plaintext : ";
	//getline(cin, plaintext);

	//Generate Plaintext
	plaintext = generatePlaintext(size);
	cout << "Plantext : " << plaintext << endl;

	//Encryption Phase
	cout << endl << "***** Encryption Phase *****" << endl;

	//Caesar Cipher
	cout << endl << "Caesar Cipher" << endl;
	start = clock();
	string caesar(encrypt.caesar(plaintext));
	end = clock();
	cout << "Key : " << encrypt.getKey() << endl;
	cout << "Ciphertext : " << caesar << endl;
	cout << "Process Time : " << (double)(end - start) << "ms" << endl;

	//Simple Substitution Cipher
	cout << endl << "Simple Substitution Cipher" << endl;
	start = clock();
	string simple = encrypt.simple(plaintext);
	end = clock();
	cout << "Table : " << encrypt.getSimpleTable() << endl;
	cout << "Ciphertext : " << simple << endl;
	cout << (double)(end - start) << "ms" << endl;

	//Polyalphabetic Substitution Cipher
	cout << endl << "Polyalphabetic Substitution Cipher" << endl;
	start = clock();
	string vigenere = encrypt.vigenere(plaintext);
	end = clock();
	cout << "Key : " << encrypt.getPolyKey() << endl;
	cout << "Ciphertext : " << vigenere << endl;
	cout << (double)(end - start) << "ms" << endl;


	//Attack Phase
	cout << endl << "***** Attack Phase *****" << endl;

	//Caesar Cipher
	cout << endl << "Caesar Cipher" << endl;
	start = clock();
	int key = attack.caesar(caesar, plaintext);
	end = clock();
	cout << "Key : " << key << endl;
	if (key == encrypt.getKey()) cout << "**Correct**" << endl;
	else cout << "**Wrong**" << endl;
	cout << (double)(end - start) << "ms" << endl;

	//Simple Substitution Cipher
	cout << endl << "Simple Substitution Cipher" << endl;
	start = clock();
	string table = attack.simple(simple, plaintext);
	end = clock();
	cout << "Table : " << table << endl;
	if (!simple.compare(encrypt.simple(plaintext, table))) cout << "**Correct**" << endl;
	else cout << "**Wrong**" << endl;
	cout << (double)(end - start) << "ms" << endl;

	return 0;
}