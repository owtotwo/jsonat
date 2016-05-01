// sample for class Json

#include <iostream>
#include "Json.h"

using std::cout;
using std::endl;

void sample3() {
    using namespace jsonat;
    // using jsonat::Json;
    
    Json g; // g = null;
    Json a = "string";
    Json b = 123.4e-05;
    Json c = true;
    Json d = false;
    Json e = {{"hello", 123}, {"world", true}};
    Json f = {a, b, c, d, e, g};
    
    // cout << e["world"] << endl;
    for (int i = 0; i < f.size(); i++) cout << f[i] << endl;
    Json p = Json::make_object();
}

int main() {
    sample3();
    return 0;
}