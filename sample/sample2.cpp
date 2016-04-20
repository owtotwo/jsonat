#include <iostream>
#include <fstream>
#include "Json.h"

static const char* addr_sample2_data = "sample/sample2_data.json";


void sample2() {
	using namespace jsonat;
	std::ifstream fin(addr_sample2_data);
	Object obj = JSON::parse(fin);
	std::cout << "size of json : " << obj.size() << '\n'; 
	JSON::pretty(std::cout, Object(obj["query"])["results"]); // 
}

int main() {
	sample2();
	return 0;
}