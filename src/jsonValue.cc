#include "Json.h"

#include <ostream>
#include <cassert>

namespace jsonat {

Value::Value() : type(Value::NULL) {}
	
Value::Value(const Value& pt) : type(pt.getType()) {

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
	case Value::BOOLEAN: 
		boolean_ptr = new Boolean(pt.getBoolean()); break;
	default:
		assert("should not be here" == 0); 
	}
}
	

Value::Value(const String& pt) : type(Value::STRING) {
	string_ptr = new String(pt);
}

Value::Value(const Object& pt) : type(Value::OBJECT) {
	object_ptr = new Object(pt);
}

Value::Value(const Number& pt) : type(Value::NUMBER) {
	number_ptr = new Number(pt);
}

Value::Value(const Array& pt) : type(Value::ARRAY) {
	array_ptr = new Array(pt);
}

Value::Value(const Boolean& pt) : type(Value::BOOLEAN) {
	boolean_ptr = new Boolean(pt);
}



Value::Value(const char* pt) : Value::Value(String(pt)) {}

Value::Value(int pt) : Value::Value(Number(pt)) {}



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
	case Value::BOOLEAN: 
		delete boolean_ptr; boolean_ptr = nullptr; break;
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

bool Value::isBoolean() const {
	return type == Value::BOOLEAN;
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

const Boolean& Value::getBoolean() const {
	return *boolean_ptr;
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
	case Value::BOOLEAN:
		os << pt.getBoolean();
		break;
	default:
		assert("should not be here" == 0);
	}
	return os;
}


Value& Value::operator=(const Value& pt) {
	if (this == &pt) return *this;
	
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
	case Value::BOOLEAN: 
		boolean_ptr = new Boolean(pt.getBoolean()); break;
	default:
		assert("should not be here" == 0); 
	}

	return *this;
}

Value& Value::operator=(const String& pt) {
	if (string_ptr == &pt) return *this;
	
	this->~Value();

	type = Value::STRING;
	string_ptr = new String(pt);

	return *this;
}

Value& Value::operator=(const Array& pt) {
	if (array_ptr == &pt) return *this;
	
	this->~Value();

	type = Value::ARRAY;
	array_ptr = new Array(pt);

	return *this;
}

Value& Value::operator=(const Object& pt) {
	if (object_ptr == &pt) return *this;
	
	this->~Value();

	type = Value::OBJECT;
	object_ptr = new Object(pt);

	return *this;
}

Value& Value::operator=(const Number& pt) {
	if (number_ptr == &pt) return *this;
	
	this->~Value();

	type = Value::NUMBER;
	number_ptr = new Number(pt);

	return *this;
}

Value& Value::operator=(const Boolean& pt) {
	if (boolean_ptr == &pt) return *this;
	
	this->~Value();

	type = Value::BOOLEAN;
	boolean_ptr = new Boolean(pt);

	return *this;
}

void toString(std::ostream& os, const Value& pt, 
		int indent, const std::string& indent_string) {
	switch (pt.getType()) {
	case Value::NULL:
		os << "null";
		break;
	case Value::OBJECT:
		toString(os, pt.getObject(), indent, indent_string);
		break;
	case Value::STRING:
		toString(os, pt.getString());
		break;
	case Value::NUMBER:
		toString(os, pt.getNumber());
		break;
	case Value::ARRAY:
		toString(os, pt.getArray(), indent, indent_string);
		break;
	case Value::BOOLEAN:
		toString(os, pt.getBoolean());
		break;
	default:
		assert("should not be here" == 0);
	}
	
}

} // namespace Json