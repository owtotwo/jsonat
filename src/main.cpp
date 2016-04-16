// main.cpp

#include <iostream>
#include "Json.h"
using namespace jsonat;
void parse_Json(std::istream& is);

int main(int argc, char* argv[]) {
	parse_Json(std::cin);
	return 0;
}