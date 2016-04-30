// Jsonat -- A Json Library in C++
// Copyright (c) 2016 sysu_AT
// All rights reserved.

#include <iostream>
#include "Json.h"


int main(int argc, char* argv[]) {
	jsonat::Value val = jsonat::Json::parse(std::cin);
	jsonat::Json::pretty(std::cout, val);
	return 0;
}