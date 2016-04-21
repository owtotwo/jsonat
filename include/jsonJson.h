// Json.h

#ifndef JSON_JSON_H
#define JSON_JSON_H

#include <iostream>
#include "jsonValue.h"

namespace jsonat {

class Value;

class Json : public Value {
public:

	using Value::Value;

	// ----------- API ------------
	
	
	// JavaScrpit JSON like, (Value val = Json.parse("[123, 4.5]");)
	static Value parse(const std::string& text);
	
	// Accept a stream object, such as std::cin, file in stream
	static Value parse(std::istream& is);
	
	
	// Serialize the JavaScript like Value via output stream, 
	// such as std::cout, file out stream 
	static void stringify(std::ostream& os, const Value& val);
	
	// Serialize and return C++ string  
	static std::string stringify(const Value& val);
	
	// Serialize the JavaScript like Value via output stream in a pretty format,
	static void pretty(std::ostream& os, 
		const Value& val, const std::string& indent_string = "    ");
	
	// Serialize and return formatted C++ string
	static std::string pretty(const Value& val, const std::string& indent_string = "    ");
		
private:
	/* nothing */
};	
	
using JSON = Json;
	
} // namespace jsonat


#endif // JSON_JSON_H