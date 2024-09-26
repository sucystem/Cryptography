//SubstitutionCipher.h class header

//Copyright (c) Seungun Park <sucystem@outlook.com>

#pragma once

#include <string>
#include <random>

namespace cipher {
	class SubstitutionCipher {
	private:
		int alpha_size, key;
		std::string simple_table, polykey;
		std::mt19937 mtrand;
		std::uniform_int_distribution<int> distribution;

	public:
		SubstitutionCipher(int);
		std::string caesar(std::string);
		std::string simple(std::string);
		std::string simple(std::string, std::string);
		std::string vigenere(std::string);

		int getKey();
		std::string getSimpleTable();
		std::string getPolyKey();

	private:
		SubstitutionCipher();
		int randAlpha();
		std::string preprocessing(std::string);
	};
}