#include "Json.h"

#include <ostream>
#include <cassert>

namespace jsonat {

Value::Value() : 
	type(Value::NULL), 
	object_ptr(nullptr), 
	string_ptr(nullptr),
	number_ptr(nullptr),
	array_ptr(nullptr),
	boolen_ptr(nullptr) {}
	
Value::Value(const Value& pt) : 
	type(pt.getType()),
	object_ptr(nullptr), 
	string_ptr(nullptr),
	number_ptr(nullptr),
	array_ptr(nullptr),
	boolen_ptr(nullptr) {

	switch (type) {
	case Value::NULL: 
		/* do nothing */; break;
	case Value::OBJECT:
		object_ptr = new Object(pt.getObject()); break;
	case Value::STRING:
		string_ptr = new String(pt.getString()); break;
	case Value::NUMBER: 
		number_ptr = new Number(pt.getNumber()); break;
	case Value::ARRAY: 
		array_ptr = new Array(pt.getArray()); break;
	case Value::BOOLEN: 
		boolen_ptr = new Boolen(pt.getBoolen()); break;
	default:
		assert("should not be here" == 0); 
	}
}
	
Value::Value(const String& pt) :
	type(Value::STRING), 
	object_ptr(nullptr), 
	string_ptr(nullptr),
	number_ptr(nullptr),
	array_ptr(nullptr),
	boolen_ptr(nullptr) {
	string_ptr = new String(pt);
}

Value::Value(const Object& pt) : 
	type(Value::OBJECT), 
	object_ptr(nullptr), 
	string_ptr(nullptr),
	number_ptr(nullptr),
	array_ptr(nullptr),
	boolen_ptr(nullptr) {
	object_ptr = new Object(pt);
}

Value::Value(const Number& pt) : 
	type(Value::NUMBER), 
	object_ptr(nullptr), 
	string_ptr(nullptr),
	number_ptr(nullptr),
	array_ptr(nullptr),
	boolen_ptr(nullptr) {
	number_ptr = new Number(pt);
}

Value::Value(const Array& pt) :
	type(Value::ARRAY), 
	object_ptr(nullptr), 
	string_ptr(nullptr),
	number_ptr(nullptr),
	array_ptr(nullptr),
	boolen_ptr(nullptr) {
	array_ptr = new Array(pt);
}

Value::Value(const Boolen& pt) :
	type(Value::BOOLEN), 
	object_ptr(nullptr), 
	string_ptr(nullptr),
	number_ptr(nullptr),
	array_ptr(nullptr),
	boolen_ptr(nullptr) {
	boolen_ptr = new Boolen(pt);
}

Value::Value(const char* pt) :
	type(Value::STRING), 
	object_ptr(nullptr), 
	string_ptr(nullptr),
	number_ptr(nullptr),
	array_ptr(nullptr),
	boolen_ptr(nullptr) {
	string_ptr = new String(pt);
}

Value::Value(int pt) :
	type(Value::NUMBER), 
	object_ptr(nullptr), 
	string_ptr(nullptr),
	number_ptr(nullptr),
	array_ptr(nullptr),
	boolen_ptr(nullptr) {
	number_ptr = new Number(pt);
}


Value::~Value() {
	switch (type) {
	case Value::NULL: 
		/* do nothing */; break;
	case Value::OBJECT:
		delete object_ptr; object_ptr = nullptr; break;
	case Value::STRING:
		delete string_ptr; string_ptr = nullptr; break;
	case Value::NUMBER: 
		delete number_ptr; number_ptr = nullptr; break;
	case Value::ARRAY: 
		delete array_ptr; array_ptr = nullptr; break;
	case Value::BOOLEN: 
		delete boolen_ptr; boolen_ptr = nullptr; break;
	default:
		break;
	}
}

bool Value::isObject() const {
	return type == Value::OBJECT;
}

bool Value::isString() const {
	return type == Value::STRING;
}

bool Value::isArray() const {
	return type == Value::ARRAY;
}

bool Value::isNumber() const {
	return type == Value::NUMBER;
}

bool Value::isBoolen() const {
	return type == Value::BOOLEN;
}

bool Value::isNull() const {
	return type == Value::NULL;
}

Value::Value_type Value::getType() const {
	return type;
}

const Object& Value::getObject() const {
	return *object_ptr;
}

const String& Value::getString() const {
	return *string_ptr;
}

const Array& Value::getArray() const {
	return *array_ptr;
}

const Number& Value::getNumber() const {
	return *number_ptr;
}

const Boolen& Value::getBoolen() const {
	return *boolen_ptr;
}

std::ostream& operator<<(std::ostream& os, const Value& pt) {
	switch (pt.getType()) {
	case Value::NULL:
		os << "null";
		break;
	case Value::OBJECT:
		os << pt.getObject();
		break;
	case Value::STRING:
		os << pt.getString();
		break;
	case Value::NUMBER:
		os << pt.getNumber();
		break;
	case Value::ARRAY:
		os << pt.getArray();
		break;
	case Value::BOOLEN:
		os << pt.getBoolen();
		break;
	default:
		assert("should not be here" == 0);
	}
	return os;
}

Value& Value::operator=(const Value& pt) {

	this->~Value();

	type = pt.getType();

	switch (type) {
	case Value::NULL: 
		/* do nothing */; break;
	case Value::OBJECT:
		object_ptr = new Object(pt.getObject()); break;
	case Value::STRING:
		string_ptr = new String(pt.getString()); break;
	case Value::NUMBER: 
		number_ptr = new Number(pt.getNumber()); break;
	case Value::ARRAY: 
		array_ptr = new Array(pt.getArray()); break;
	case Value::BOOLEN: 
		boolen_ptr = new Boolen(pt.getBoolen()); break;
	default:
		assert("should not be here" == 0); 
	}

	return *this;
}

Value& Value::operator=(const String& pt) {
	this->~Value();

	type = Value::STRING;
	string_ptr = new String(pt);

	return *this;
}

Value& Value::operator=(const Array& pt) {
	this->~Value();

	type = Value::ARRAY;
	array_ptr = new Array(pt);

	return *this;
}

Value& Value::operator=(const Object& pt) {
	this->~Value();

	type = Value::OBJECT;
	object_ptr = new Object(pt);

	return *this;
}

Value& Value::operator=(const Number& pt) {
	this->~Value();

	type = Value::NUMBER;
	number_ptr = new Number(pt);

	return *this;
}

Value& Value::operator=(const Boolen& pt) {
	this->~Value();

	type = Value::BOOLEN;
	boolen_ptr = new Boolen(pt);

	return *this;
}


} // namespace Json