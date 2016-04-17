// main.cpp

#include <iostream>
#include "Json.h"


namespace jsonat {
	void parse_Json(std::istream& is);
}

void func() {
	try { 
		jsonat::parse_Json(std::cin); 
	} catch (const std::string& _err) {
		std::cerr << _err << std::endl;
	} catch (const char* _err) {
		std::cerr << _err << std::endl;
	}
}

int main(int argc, char* argv[]) {
	func();
	return 0;
}