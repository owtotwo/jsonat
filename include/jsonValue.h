// Jsonat -- A Json Library in C++
// Copyright (c) 2016 sysu_AT
// All rights reserved.

#ifndef JSON_VALUE_H
#define JSON_VALUE_H

#include <ostream>
#include <initializer_list>
#include <string>

// #include "jsonNumber.h"

namespace jsonat {

// Forward declaration
class Object;
class Array;
class String;
class Boolean;
typedef double Number;


class Value {
public:
	typedef enum { NULL_TYPE = 0, OBJECT_TYPE = 1, ARRAY_TYPE, NUMBER_TYPE, STRING_TYPE, BOOLEAN_TYPE } Value_type;

	Value();
	Value(const Value& pt);
	Value(Value&& pt);
	
	Value(const String& pt);
	Value(const Object& pt);
	Value(const Number& pt);
	Value(const Array& pt);
	Value(const Boolean& pt);

	Value(const char* pt);
	Value(const std::string& pt);
	Value(int n);
	Value(bool x);
	
	Value(std::initializer_list<Value> il);
	Value(String&& pt);
	Value(Object&& pt);
	Value(Number&& pt);
	Value(Array&& pt);
	Value(Boolean&& pt);

	~Value();
	
	bool isObject() const;
	bool isString() const;
	bool isArray() const;
	bool isNumber() const;
	bool isBoolean() const;
	bool isNull() const;

	Value_type getType() const;

	const Object& getObject() const;
	const String& getString() const;
	const Array& getArray() const;
	const Number& getNumber() const;
	const Boolean& getBoolean() const;

	Value& operator=(const Value& pt);
	Value& operator=(const String& pt);
	Value& operator=(const Array& pt) ;
	Value& operator=(const Object& pt);
	Value& operator=(const Number& pt);
	Value& operator=(const Boolean& pt);
	
	Value& operator=(Value&& pt);
	Value& operator=(String&& pt);
	Value& operator=(Array&& pt);
	Value& operator=(Object&& pt);
	Value& operator=(Number&& pt);
	Value& operator=(Boolean&& pt);
	
	operator std::string() const;
	operator double() const;
	operator int() const;
	operator bool() const;
	
	
	// ------------------- New part -------------------
	Value& operator[](size_t pos);
	Value& operator[](const String& key);
	Value& operator[](const char* key);
	
	size_t size() const;

	friend Value operator+(const Value& a, const Value& b);
	friend Value operator-(const Value& a, const Value& b);
	friend Value operator*(const Value& a, const Value& b);
	friend Value operator/(const Value& a, const Value& b);
	
	Value& operator+=(const Value& pt);
	Value& operator-=(const Value& pt);
	Value& operator*=(const Value& pt);
	Value& operator/=(const Value& pt);

	bool insert(const String& key, const Value& value);
	bool push_back(const Value& pt);
	bool pop_back();
	bool insert(size_t pos, const Value& pt);
	
	bool erase(const String& key);
	bool erase(size_t pos);
	
	friend Value operator+(const Value& pt, int n);
	friend Value operator+(int n, const Value& pt);
	
	friend Value operator-(const Value& pt, int n);
	friend Value operator-(int n, const Value& pt);
	
	friend Value operator*(const Value& pt, int n);
	friend Value operator*(int n, const Value& pt);
	
	friend Value operator/(const Value& pt, int n);
	friend Value operator/(int n, const Value& pt);
	
	
	friend Value operator+(const Value& pt, double n);
	friend Value operator+(double n, const Value& pt);
	
	friend Value operator-(const Value& pt, double n);
	friend Value operator-(double n, const Value& pt);
	
	friend Value operator*(const Value& pt, double n);
	friend Value operator*(double n, const Value& pt);
	
	friend Value operator/(const Value& pt, double n);
	friend Value operator/(double n, const Value& pt);
	
	
	friend Value operator+(const Value& pt, char c);
	friend Value operator+(char c, const Value& pt);
	
	friend Value operator+(const Value& pt, const char* c);
	friend Value operator+(const char* c, const Value& pt);
		
	friend Value operator+(const Value& pt, const std::string& s);
	friend Value operator+(const std::string& s, const Value& pt);

	friend std::ostream& operator<<(std::ostream& os, const Value& pt);
	friend void toString(std::ostream& os, const Value& pt, 
		int indent, const std::string& indent_string);
	
	friend class Object;	
	friend class Array;
	friend class String;
	
	
private:
	Value_type type = NULL_TYPE;
	Object* object_ptr = nullptr;
	String* string_ptr = nullptr;
	Number* number_ptr = nullptr;
	Array* array_ptr = nullptr;
	Boolean* boolean_ptr = nullptr;
};


} // namespace Json

#endif // JSON_VALUE_H