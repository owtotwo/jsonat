#include <iostream>
#include "Json.h"

void test_1() {
	jsonat::Value val = jsonat::JSON::parse("[\"hello world!\", 10086]");
	std::cout << val << std::endl; 
	jsonat::Array arr = val;
	if (arr.size() > 1) {
		std::string s = arr[0];
		int a = arr[1];
		std::cout << s << ", " << a << std::endl;
		
	} else {
		std::cout << "what the hell?\n";
	}
	
}


int main() {
	test_1();
	return 0;
}