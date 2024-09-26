//Implementation for SubstitutionCipher class

//Copyright (c) Seungun Park <sucystem@outlook.com>

#include <string>
#include <ctime>
#include <algorithm>

#include <iostream>

#include "SubstitutionCipher.h"

cipher::SubstitutionCipher::SubstitutionCipher(int size) : alpha_size(size) {
	//size in alphabet
	if (alpha_size < 1 && alpha_size > 26) alpha_size = 26;

	//Initialize random device
	mtrand = std::mt19937((unsigned int)time(NULL));
	distribution = std::uniform_int_distribution<int>(0, alpha_size - 1);

	//Initialize key
	key = randAlpha();

	//Initialize simple table
	for (int i = 0; i < alpha_size; ++i)
		simple_table.push_back(i + 65);

	for (int i = 0; i < alpha_size * alpha_size; ++i) {
		std::iter_swap(simple_table.begin() + randAlpha(), simple_table.begin() + randAlpha());
	}

	//Initialize Vigenere Key
	for (int i = 0; i < randAlpha(); ++i) {
		polykey.push_back(randAlpha() + 65);
	}
}

int cipher::SubstitutionCipher::randAlpha() {
	return distribution(mtrand);
}

int cipher::SubstitutionCipher::getKey() {
	return key;
}

std::string cipher::SubstitutionCipher::getSimpleTable() {
	return simple_table;
}

std::string cipher::SubstitutionCipher::getPolyKey() {
	return polykey;
}

std::string cipher::SubstitutionCipher::preprocessing(std::string str) {
	std::string plaintext;
	for (auto& c : str) {
		c = std::toupper(c);
		if (c >= 65 && c < 65 + alpha_size)
			plaintext.push_back(c);
	}
	return plaintext;
}

std::string cipher::SubstitutionCipher::caesar(std::string str) {
	std::string text(preprocessing(str));

	for (auto& c : text)
		c = (c - 65 + key) % alpha_size + 65;

	return text;
}

std::string cipher::SubstitutionCipher::simple(std::string str) {
	std::string plaintext(preprocessing(str));
	std::string ciphertext;

	for (char& c : plaintext)
		ciphertext.push_back(simple_table[c - 65]);

	return ciphertext;
}

std::string cipher::SubstitutionCipher::simple(std::string str, std::string table) {
	std::string plaintext(preprocessing(str));
	std::string ciphertext;

	for (char& c : plaintext)
		ciphertext.push_back(table[c - 65]);

	return ciphertext;
}

std::string cipher::SubstitutionCipher::vigenere(std::string str) {
	std::string plaintext(preprocessing(str));
	std::string ciphertext;

	polykey = "SKY";

	for (int i = 0; i < plaintext.length(); ++i) {
		int p, k;
		p = plaintext[i] - 65;
		k = polykey[i % polykey.length()] - 65;
		ciphertext.push_back((p + k) % alpha_size + 65);
	}

	return ciphertext;
}
