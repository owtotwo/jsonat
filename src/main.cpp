// main.cpp

#include <iostream>
#include "Json.h"


int main(int argc, char* argv[]) {
	jsonat::Value val = jsonat::Json::parse(std::cin);
	jsonat::Json::pretty(std::cout, val);
	return 0;
}