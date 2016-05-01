// Jsonat -- A Json Library in C++
// Copyright (c) 2016 sysu_AT
// All rights reserved.


#ifndef JSON_ARRAY_H
#define JSON_ARRAY_H

#include <vector>
#include <ostream>
#include <initializer_list> // for initializer_list<>()

namespace jsonat {

// Forward declaration
class Value;


class Array : public std::vector<Value> {

	typedef std::vector<Value> SuperClass;

public:

	typedef Value value_type;
	
	using SuperClass::SuperClass;
	using SuperClass::operator=;
	
	Array();
	Array(const Array& pt);
	Array(Array&& pt) = default;
	Array(const Value& pt);
	Array(Value&& pt);
	Array(std::initializer_list<Value> il);
	
	Array& operator=(const Array& pt) = default;
	Array& operator=(Array&& pt) = default;
	Array& operator=(const Value& pt);
	Array& operator=(Value&& pt);
	
	void addValue(const value_type& val);
	
	friend std::ostream& operator<<(std::ostream& os, const Array& pt);
	friend void toString(std::ostream& os, const Array& pt, 
		int indent, const std::string& indent_string);
};

} // namespace Json


#endif // JSON_ARRAY_H