// Json.h

#ifndef JSONJSON_H
#define JSONJSON_H

#include <iostream>

namespace jsonat {

class Value;

class Json {
public:
	// ----------- API ------------
	
	
	// JavaScrpit JSON like, (Value val = Json.parse("[123, 4.5]");)
	static Value parse(const std::string& text);
	
	// Accept a stream object, such as std::cin, file in stream
	static Value parse(std::istream& is);
	
	
	// Serialize the JavaScript like Value via output stream, 
	// such as std::cout, file out stream 
	static void stringify(const Value& val, std::ostream& os);
	
	// Serialize and return C++ string  
	static std::string stringify(const Value& val);
	
	
private:
	/* nothing */
};	
	
	
} // namespace jsonat


#endif // JSONJSON_H