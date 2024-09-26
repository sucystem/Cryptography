//Implementation for BruteForce class

//Copyright (c) Seungun Park <sucystem@outlook.com>

#include <string>
#include <vector>

#include <iostream>

#include "BruteForce.h"

cipher::BruteForce::BruteForce(int size) : alpha_size(size) {
	//size in alphabet
	if (alpha_size < 1 && alpha_size > 26) alpha_size = 26;
}

std::string cipher::BruteForce::preprocessing(std::string str) {
	std::string plaintext;
	for (auto& c : str) {
		c = std::toupper(c);
		if (c >= 65 && c < 65 + alpha_size)
			plaintext.push_back(c);
	}
	return plaintext;
}

int cipher::BruteForce::caesar(std::string str1, std::string str2) {
	std::string ciphertext(preprocessing(str1));
	std::string answer(preprocessing(str2));
	int key = 0;

	for (key = 0; key < alpha_size; ++key) {
		for (auto& c : ciphertext)
			c = (c - 65 + 1) % alpha_size + 65;

		if (!ciphertext.compare(answer)) break;
	}

	key = alpha_size - key - 1;

	return key;
}

std::string cipher::BruteForce::simple(std::string str1, std::string str2) {
	std::string ciphertext(preprocessing(str1));
	std::string answer(preprocessing(str2));
	std::string real_table;
	std::string table;
	std::string pool;

	//Initialize pool

	for (int i = 0; i < alpha_size; ++i) {
		pool.push_back(i + 65);
		real_table.push_back(i + 65);
	}

	for (int i = 0; i < alpha_size; ++i) {
		table.push_back(i + 65);
		std::string tmp(pool);
		tmp.erase(tmp.begin() + i);
		if (simpleRecursion(ciphertext, answer, table, tmp)) break;
		table.pop_back();
	}

	for (int i = 0; i < alpha_size; ++i) {
		real_table[table[i] - 65] = i + 65;
	}

	return real_table;
}

bool cipher::BruteForce::simpleRecursion(std::string& ciphertext, std::string& answer, std::string& table, std::string pool) {
	if (pool.length() == 1) {
		table = table + pool;

		std::string test;
		for (char& c : ciphertext)
			test.push_back(table[c - 65]);
		if (!test.compare(answer)) return true;

		table.pop_back();
		return false;
	}

	for (char& c : pool) {
		table.push_back(c);
		std::string tmp(pool);
		tmp.erase(tmp.begin() + tmp.find(c));
		if (simpleRecursion(ciphertext, answer, table, tmp)) return true;
		table.pop_back();
	}

	return false;
}