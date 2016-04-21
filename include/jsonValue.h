// Value.h

#ifndef JSON_VALUE_H
#define JSON_VALUE_H

#include <ostream>
#include <initializer_list>

#include "jsonNumber.h"

// please use nullptr(nullptr_t) instead of NULL(int)
#ifdef NULL
#undef NULL // clear macro
#endif

namespace jsonat {

// Forward declaration
class Object;
class Array;
class String;
class Boolean;


class Value {
public:
	typedef enum { NULL = 0, OBJECT = 1, ARRAY, NUMBER, STRING, BOOLEAN } Value_type;

	Value();
	Value(const Value& pt);
	Value(Value&& pt);
	
	Value(const String& pt);
	Value(const Object& pt);
	Value(const Number& pt);
	Value(const Array& pt);
	Value(const Boolean& pt);

	Value(const char* pt);
	Value(int);
	
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
	
	operator std::string();
	operator double();
	operator int();
	operator bool();
	
	friend std::ostream& operator<<(std::ostream& os, const Value& pt);
	friend void toString(std::ostream& os, const Value& pt, 
		int indent, const std::string& indent_string);
	
	friend class Object;	
	friend class Array;
	friend class String;
	
	
private:
	Value_type type = NULL;
	Object* object_ptr = nullptr;
	String* string_ptr = nullptr;
	Number* number_ptr = nullptr;
	Array* array_ptr = nullptr;
	Boolean* boolean_ptr = nullptr;
};


} // namespace Json

#endif // JSON_VALUE_H