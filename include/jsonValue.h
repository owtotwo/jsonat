// Jsonat -- A Json Library in C++
// Copyright (c) 2016 sysu_AT
// All rights reserved.

#ifndef JSON_VALUE_H
#define JSON_VALUE_H

#include <iostream>
#include <initializer_list>
#include <string>
#include <type_traits> // for enable_if, is_arithmetic


namespace jsonat {

/*
 * is_arithmetic means is_integral(int, bool, char, short int ...) or 
 * is_floating_point(float, double, long double).
 * http://www.cplusplus.com/reference/type_traits/is_arithmetic/
 */
#define TEMPLATE_DECLARED_HEADER_FOR_ARITHMETIC(T) \
	template < typename T, \
	typename = typename std::enable_if<std::is_arithmetic< T >::value>::type >
#define TEMPLATE_DEFINITION_HEADER_FOR_ARITHMETIC(T) \
	template < typename T, typename >
	
/*
 * is_integral => bool, char, char16_t, char32_t, wchar_t, 
 * signed char, short int, int, long int, long long int, 
 * and their unsigned version.
 * http://www.cplusplus.com/reference/type_traits/is_integral/
 */
#define TEMPLATE_DECLARED_HEADER_FOR_INTEGRAL(T) \
	template < typename T, \
	typename = typename std::enable_if<std::is_integral< T >::value>::type >
#define TEMPLATE_DEFINITION_HEADER_FOR_INTEGRAL(T) \
	template < typename T, typename >


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
	Value(bool x);

	/* The substitution of all constructors like Value(int) or Value(unsigned long) */
	TEMPLATE_DECLARED_HEADER_FOR_ARITHMETIC(T) 
	Value(T pt);

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
	Value& operator=(Value&& pt);

	Value& operator=(const char* pt);
	Value& operator=(const std::string& pt);
	Value& operator=(bool pt);
	
	/* assignment operator template for SOME_ARITHMETIC_TYPE */
	TEMPLATE_DECLARED_HEADER_FOR_ARITHMETIC(T)
	Value& operator=(T pt);
	
	operator std::string() const;
	operator bool() const;
	operator double() const;
	
	/* type conversion template from Value(NUMBER_TYPE) to SOME_ARITHMETIC_TYPE */
	TEMPLATE_DECLARED_HEADER_FOR_ARITHMETIC(T) 
	operator T() const;
	
	// ------------------- New part -------------------
	Value& operator[](size_t pos);
	const Value& operator[](size_t pos) const;
	
	TEMPLATE_DECLARED_HEADER_FOR_INTEGRAL(T) 
	Value& operator[](T pos);
	TEMPLATE_DECLARED_HEADER_FOR_INTEGRAL(T) 
	const Value& operator[](T pos) const;
	
	
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
	
	Value& operator++();
	Value& operator--();
	
	Value operator++(int);
	Value operator--(int);

	bool insert(const String& key, const Value& value);
	bool push_back(const Value& pt);
	bool pop_back();
	bool insert(size_t pos, const Value& pt);
	
	bool erase(const String& key);
	bool erase(size_t pos);
	
	size_t push(const Value& pt);
	size_t push(std::initializer_list<Value>);
	bool pop();
	
	friend Value operator+(const Value& pt, char c);
	friend Value operator+(char c, const Value& pt);
	
	friend Value operator+(const Value& pt, const char* c);
	friend Value operator+(const char* c, const Value& pt);

	friend Value operator+(const Value& pt, const std::string& s);
	friend Value operator+(const std::string& s, const Value& pt);
	
	friend bool operator==(const Value& a, const Value& b);
	friend bool operator!=(const Value& a, const Value& b);
	
	friend bool operator<(const Value& a, const Value& b);
	friend bool operator>(const Value& a, const Value& b);
	friend bool operator<=(const Value& a, const Value& b);
	friend bool operator>=(const Value& a, const Value& b);
	

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




/*
 * Macro for the relational operators definition between 
 * Value(NUMBER_TYPE) and SOME_ARITHMETIC_TYPE, and its 
 * commutative version. 
 * (i.e. 1 < Value(1) and Value(1) >= 1)
 */
#define RELATIONAL_OPERATOR_DEFINITION(_OPERATOR) \
	\
	TEMPLATE_DECLARED_HEADER_FOR_ARITHMETIC(T) \
	bool operator _OPERATOR (const Value& a, T b) { return a _OPERATOR Value(b); } \
	\
	TEMPLATE_DECLARED_HEADER_FOR_ARITHMETIC(T) \
	bool operator _OPERATOR (T a, const Value& b) { return Value(a) _OPERATOR b; }

RELATIONAL_OPERATOR_DEFINITION(==);
RELATIONAL_OPERATOR_DEFINITION(!=);
RELATIONAL_OPERATOR_DEFINITION(<);
RELATIONAL_OPERATOR_DEFINITION(>);
RELATIONAL_OPERATOR_DEFINITION(<=);
RELATIONAL_OPERATOR_DEFINITION(>=);



/*
 * Macro for the arithmetic operators definition between 
 * Value(NUMBER_TYPE) and SOME_ARITHMETIC_TYPE, and its 
 * commutative version. 
 * (i.e. 1 + Value(1) and Value(1) / 1)
 */
#define ARITHMETIC_OPERATOR_DEFINITION(_OPERATOR) \
	\
	TEMPLATE_DECLARED_HEADER_FOR_ARITHMETIC(T) \
	Value operator _OPERATOR (const Value& pt, T num) { return pt _OPERATOR Value(num); } \
	\
	TEMPLATE_DECLARED_HEADER_FOR_ARITHMETIC(T) \
	Value operator _OPERATOR (T num, const Value& pt) { return Value(num) _OPERATOR pt; }

ARITHMETIC_OPERATOR_DEFINITION(+);
ARITHMETIC_OPERATOR_DEFINITION(-);
ARITHMETIC_OPERATOR_DEFINITION(*);
ARITHMETIC_OPERATOR_DEFINITION(/);



/* type conversion template from Value(NUMBER_TYPE) to SOME_ARITHMETIC_TYPE */
TEMPLATE_DEFINITION_HEADER_FOR_ARITHMETIC(T)
Value::operator T() const { return double(*this); }

/* The substitution of all constructors like Value(int) or Value(unsigned long) */
TEMPLATE_DEFINITION_HEADER_FOR_ARITHMETIC(T)
Value::Value(T pt) : Value::Value(Number(pt)) {}


/* i.e. : Value a({1, 2, 3}); a[1] == 2; */
TEMPLATE_DEFINITION_HEADER_FOR_INTEGRAL(T)
Value& Value::operator[](T pos) { return this->operator[](size_t(pos)); }

TEMPLATE_DEFINITION_HEADER_FOR_INTEGRAL(T)
const Value& Value::operator[](T pos) const { return this->operator[](size_t(pos)); }

/* assignment operator template for SOME_ARITHMETIC_TYPE */
TEMPLATE_DEFINITION_HEADER_FOR_ARITHMETIC(T)
Value& Value::operator=(T pt) { return *this = Value(pt); }

} // namespace Json

#endif // JSON_VALUE_H