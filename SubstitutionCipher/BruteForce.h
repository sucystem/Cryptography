//BruteForce.h class header

//Copyright (c) Seungun Park <sucystem@outlook.com>

#pragma once

#include <string>

namespace cipher {
	class BruteForce {
	private:
		int alpha_size;
		std::string table;

	public:
		BruteForce(int);
		int caesar(std::string, std::string);
		std::string simple(std::string, std::string);

	private:
		BruteForce();
		std::string preprocessing(std::string);
		bool simpleRecursion(std::string&, std::string&, std::string&, std::string);
	};
}
