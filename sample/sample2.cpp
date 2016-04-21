#include <iostream>
#include <fstream>
#include <utility>
#include <ctime>
#include <algorithm>

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
   
void sample3() {
    using jsonat::Json;
	using jsonat::Object;
	using jsonat::Array;
	using jsonat::Value;
    using jsonat::String;
    using std::cout;
    clock_t first = clock();
    Array arr1(1234567);
    std::cout << arr1.size() << '\n';
    std::generate(arr1.begin(), arr1.end(), [](){return String("hello world");});
    std::cout << "(before move)addr arr1[0] : " << &arr1[0] << '\n';
    #if 1
    Value val1 = std::move(arr1);
    Value val2 = std::move(val1);
    Array arr2 = std::move(val2);
    #else
    Value val1 = std::move(arr1);
    Value val2 = std::move(val1);
    Array arr2 = (val2);
    #endif
    std::cout << "(after move)addr arr1[0] : " << &arr1[0] << '\n';
    std::cout << "addr arr2[0] : " << &arr2[0] << '\n';
    std::cout << "size of arr2 = " << arr2.size() << '\n';
    std::cout << &arr1 << '\n';
    std::cout << "size of arr1 = " << arr1.size() << '\n';
    
    clock_t last = clock();
    std::cout << "Time waste : " << (last - first) << " ms\n";  
}
   
void sample4() {
    using jsonat::String;
    using namespace std;
    String a = "hello github";
	for (int i = 0; i < 12345; i++)
		a += "hello world";
	cout << a.length() << endl;
	String b = move(a);
    cout << a.length() << endl;
}   

int main() {
	sample3();
	return 0;
}
