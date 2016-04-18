// main.cpp

#include <iostream>
#include "Json.h"


int main(int argc, char* argv[]) {
	jsonat::Value val = jsonat::Json::parse(std::cin);
	std::cout << val << std::endl;
	return 0;
}