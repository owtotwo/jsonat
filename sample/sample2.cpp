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

void sample() {	
	using jsonat::Json;
	using jsonat::Object;
	using jsonat::Array;
	using jsonat::Value;
   Json g; // g = null;
   Json a = "string";
   Json b = 123.4e-05;
   Json c = true;
   Json d = false;
   Json e = {{"hello", 123}, {"world", true}};
   Json f = {a, b, c, d, e, g};
   std::cout << a << '\n';
   std::cout << b << '\n'; 
   std::cout << c << '\n';
   std::cout << d << '\n'; 
   std::cout << e << '\n';
   std::cout << f << '\n'; 
   std::cout << g << '\n';
   std::cout << Json::pretty( f); // jsonat::Value(f)
} 
   
int main() {
	sample();
	return 0;
}
