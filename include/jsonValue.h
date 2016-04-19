// Value.h

#ifndef JSON_VALUE_H
#define JSON_VALUE_H

#include <ostream>


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
typedef double Number;



class Value {
public:
	typedef enum { NULL = 0, OBJECT = 1, ARRAY, NUMBER, STRING, BOOLEAN } Value_type;

	Value();
	Value(const Value& pt);
	Value(const String& pt);
	Value(const Object& pt);
	Value(const Number& pt);
	Value(const Array& pt);
	Value(const Boolean& pt);

	Value(const char* pt);
	Value(int);

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
	
	operator std::string();
	operator double();
	operator int();
	operator bool();
	
	friend std::ostream& operator<<(std::ostream& os, const Value& pt);
	friend void toString(std::ostream& os, const Value& pt, 
		int indent, const std::string& indent_string);
	
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