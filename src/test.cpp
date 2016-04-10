#include <iostream>
#include "Json.h"
#include <vector>

using std::cout;
using std::endl;
using std::cin;
using namespace Json;

int main() {

	Value v;
	if (v.isNull()) cout << "Value is NULL" << endl;
	else cout << "Wrong" << endl;

	Value v1(-12.34E-02);
	cout << v1.getNumber() << endl;

	Value v2(1);
	cout << int(v2.isNumber()) << endl;
	

	Value v3("heyman");
	cout << v3.getString() << endl;

	Value v4(std::vector<Value>{1,2,3,4});
	cout << int(v4.isArray()) << endl;

	
	return 0;
}