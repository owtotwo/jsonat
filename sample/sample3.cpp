// sample for class Json

#include <iostream>
#include "Json.h"

using std::cout;
using std::endl;

void sample3() {
    using namespace jsonat;
    
    Json g; // g = null;
    Json a = "string";
    Json b = 123.4e-05;
    Json c = true;
    Json d = false;
    Json e = {{"hello", 123}, {"world", true}};
    Json f = {a, b, c, d, e, g};
    
    cout << e["world"] << endl;
    for (unsigned i = 0; i < f.size(); i++) cout << f[i] << endl;
    Json p = Json::make_object();
    int n = e["hello"];
    cout << n << endl;
    cout << b + 12 << endl;
    cout << 12 + b + 14.6 << endl;
    cout << (b + b + b) << " = " << (3 * b) << endl;
    
}

int main() {
    sample3();
    return 0;
}