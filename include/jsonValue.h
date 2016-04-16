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
typedef double Number;
typedef bool Boolen;



class Value {
public:
	typedef enum { NULL = 0, OBJECT = 1, ARRAY, NUMBER, STRING, BOOLEN } Value_type;

	Value();
	Value(const Value& pt);
	Value(const String& pt);
	Value(const Object& pt);
	Value(const Number& pt);
	Value(const Array& pt);
	Value(const Boolen& pt);

	Value(const char* pt);
	Value(int);

	~Value();
	
	bool isObject() const;
	bool isString() const;
	bool isArray() const;
	bool isNumber() const;
	bool isBoolen() const;
	bool isNull() const;

	Value_type getType() const;

	const Object& getObject() const;
	const String& getString() const;
	const Array& getArray() const;
	const Number& getNumber() const;
	const Boolen& getBoolen() const;

	friend std::ostream& operator<<(std::ostream& os, const Value& pt);
	
private:
	Value_type type;
	Object* object_ptr;
	String* string_ptr;
	Number* number_ptr;
	Array* array_ptr;
	Boolen* boolen_ptr;
};


} // namespace Json

#endif // JSON_VALUE_H