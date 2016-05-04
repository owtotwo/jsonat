// Jsonat -- A Json Library in C++
// Copyright (c) 2016 sysu_AT
// All rights reserved.

#ifndef JSON_JSON_H
#define JSON_JSON_H

#include <iostream>
#include <functional> // for function<>()
#include "jsonValue.h"

namespace jsonat {

class Value;

class Json : public Value {
public:

	using Value::Value;
	using Value::operator=;

	Json();
	Json(const Value& pt);
	Json(Value&& pt);

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
		
	static Json make_object(std::initializer_list<Value> il = {});
	static Json make_array(std::initializer_list<Value> il = {});
		
private:
	/* nothing */
};	
	
using JSON = Json;

extern std::function<decltype(Json::make_object)> makeObject; // JavaScript-like API
extern std::function<decltype(Json::make_array)> makeArray; // JavaScript-like API
	
} // namespace jsonat


#endif // JSON_JSON_H