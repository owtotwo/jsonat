// Jsonat -- A Json Library in C++
// Copyright (c) 2016 sysu_AT
// All rights reserved.

#include "jsonValue.h"

#include "jsonObject.h"
#include "jsonNumber.h"
#include "jsonString.h"
#include "jsonArray.h"
#include "jsonBoolean.h"

#include <ostream>
#include <cassert>
#include <string>
#include <initializer_list>
#include <algorithm>

namespace jsonat {

Value::Value() : type(Value::NULL_TYPE) {}
	
Value::Value(const Value& pt) : type(pt.getType()) {
	
	switch (type) {
	case Value::NULL_TYPE: 
		/* do nothing */; break;
	case Value::OBJECT_TYPE:
		object_ptr = new Object(pt.getObject()); break;
	case Value::STRING_TYPE:
		string_ptr = new String(pt.getString()); break;
	case Value::NUMBER_TYPE: 
		number_ptr = new Number(pt.getNumber()); break;
	case Value::ARRAY_TYPE: 
		array_ptr = new Array(pt.getArray()); break;
	case Value::BOOLEAN_TYPE: 
		boolean_ptr = new Boolean(pt.getBoolean()); break;
	default:
		assert("should not be here" == 0); 
	}
}
	
Value::Value(Value&& pt) : type(pt.getType()) {
	
	switch (type) {
	case Value::NULL_TYPE: 
		/* do nothing */; break;
	case Value::OBJECT_TYPE:
		object_ptr = pt.object_ptr; pt.object_ptr = nullptr; break;
	case Value::STRING_TYPE:
		string_ptr = pt.string_ptr; pt.string_ptr = nullptr; break;
	case Value::NUMBER_TYPE: 
		number_ptr = pt.number_ptr; pt.number_ptr = nullptr; break;
	case Value::ARRAY_TYPE: 
		array_ptr = pt.array_ptr; pt.array_ptr = nullptr; break;
	case Value::BOOLEAN_TYPE: 
		boolean_ptr = pt.boolean_ptr; pt.boolean_ptr = nullptr; break;
	default:
		assert("should not be here" == 0); 
	}
}	


Value::Value(const String& pt) : type(Value::STRING_TYPE) {
	string_ptr = new String(pt);
}

Value::Value(const Object& pt) : type(Value::OBJECT_TYPE) {
	object_ptr = new Object(pt);
}

Value::Value(const Number& pt) : type(Value::NUMBER_TYPE) {
	number_ptr = new Number(pt);
}

Value::Value(const Array& pt) : type(Value::ARRAY_TYPE) {
	array_ptr = new Array(pt);
}

Value::Value(const Boolean& pt) : type(Value::BOOLEAN_TYPE) {
	boolean_ptr = new Boolean(pt);
}




Value::Value(const char* pt) : Value::Value(String(pt)) {}

Value::Value(int pt) : Value::Value(Number(pt)) {}


Value::Value(std::initializer_list<Value> il) {
	if (il.size() == 0) return; // set type = NULL_TYPE

	// type deduction
	// if Value is {String, Value} then create an Object, otherwise create an Array.
	auto is_kv_pair = [](const Value& x) -> bool {
		return (x.isArray() && (x.getArray().size() == 2) && x.getArray().front().isString());
	};
	
	if (std::all_of(il.begin(), il.end(), is_kv_pair)) { // create Object
		Object obj;
		auto insert_kv_pair_into_obj = [&obj](const Value& x){ obj.addPair(x.getArray()[0], x.getArray()[1]); };
		std::for_each(il.begin(), il.end(), insert_kv_pair_into_obj);
		*this = obj;
	} else { // create Array
		*this = Array(il);
	}

}




Value::Value(String&& pt) : type(Value::STRING_TYPE) {
	string_ptr = new String(std::move(pt));
}

Value::Value(Object&& pt) : type(Value::OBJECT_TYPE) {
	object_ptr = new Object(std::move(pt));
}

Value::Value(Number&& pt) : type(Value::NUMBER_TYPE) {
	number_ptr = new Number(std::move(pt));
}

Value::Value(Array&& pt) : type(Value::ARRAY_TYPE) {
	array_ptr = new Array(std::move(pt));
}

Value::Value(Boolean&& pt) : type(Value::BOOLEAN_TYPE) {
	boolean_ptr = new Boolean(std::move(pt));
}



Value& Value::operator=(Value&& pt) {
	if (this == &pt) return *this;
	
	this->~Value();
	
	type = pt.getType();
	
	switch (pt.getType()) {
	case Value::NULL_TYPE: 
		/* do nothing */; break;
	case Value::OBJECT_TYPE:
		object_ptr = pt.object_ptr; pt.object_ptr = nullptr; break;
	case Value::STRING_TYPE:
		string_ptr = pt.string_ptr; pt.string_ptr = nullptr; break;
	case Value::NUMBER_TYPE: 
		number_ptr = pt.number_ptr; pt.number_ptr = nullptr; break;
	case Value::ARRAY_TYPE: 
		array_ptr = pt.array_ptr; pt.array_ptr = nullptr; break;
	case Value::BOOLEAN_TYPE: 
		boolean_ptr = pt.boolean_ptr; pt.boolean_ptr = nullptr; break;
	default:
		assert("should not be here" == 0); 
	}
	return *this;
} 

Value& Value::operator=(String&& pt) {
	if (string_ptr == &pt) return *this;
	this->~Value();
	type = Value::STRING_TYPE;
	string_ptr = new String(std::move(pt));
	return *this;
} 

Value& Value::operator=(Array&& pt) {
	if (array_ptr == &pt) return *this;
	this->~Value();
	type = Value::ARRAY_TYPE;
	array_ptr = new Array(std::move(pt));
	return *this;
}  

Value& Value::operator=(Object&& pt) {
	if (object_ptr == &pt) return *this;
	this->~Value();
	type = Value::OBJECT_TYPE;
	object_ptr = new Object(std::move(pt));
	return *this;
} 

Value& Value::operator=(Number&& pt) {
	if (number_ptr == &pt) return *this;
	this->~Value();
	type = Value::NUMBER_TYPE;
	number_ptr = new Number(std::move(pt));
	return *this;
} 

Value& Value::operator=(Boolean&& pt) {
	if (boolean_ptr == &pt) return *this;
	this->~Value();
	type = Value::BOOLEAN_TYPE;
	boolean_ptr = new Boolean(std::move(pt));
	return *this;
} 






Value::operator std::string() {
	if (this->type != Value::STRING_TYPE) return std::string();
	return this->getString();
}

Value::operator double() {
	if (this->type != Value::NUMBER_TYPE) return double();
	return this->getNumber();
}

Value::operator int() {
	return double(*this);
}

Value::operator bool() {
	switch (this->type) {
	case Value::NULL_TYPE: 
		return false; 
	case Value::OBJECT_TYPE:
		return this->getObject().size() != 0;
	case Value::STRING_TYPE:
		return this->getString().size() != 0;
	case Value::NUMBER_TYPE: 
		return bool(this->getNumber());
	case Value::ARRAY_TYPE:
		return this->getArray().size() != 0;
	case Value::BOOLEAN_TYPE:
		return this->getBoolean();
	default:
		assert("should not be here" == 0);
	}
	return false;
}



Value::~Value() {
	switch (type) {
	case Value::NULL_TYPE: 
		/* do nothing */; break;
	case Value::OBJECT_TYPE:
		delete object_ptr; object_ptr = nullptr; break;
	case Value::STRING_TYPE:
		delete string_ptr; string_ptr = nullptr; break;
	case Value::NUMBER_TYPE: 
		delete number_ptr; number_ptr = nullptr; break;
	case Value::ARRAY_TYPE: 
		delete array_ptr; array_ptr = nullptr; break;
	case Value::BOOLEAN_TYPE: 
		delete boolean_ptr; boolean_ptr = nullptr; break;
	default:
		assert("should not be here" == 0);
	}
}

bool Value::isObject() const {
	return type == Value::OBJECT_TYPE;
}

bool Value::isString() const {
	return type == Value::STRING_TYPE;
}

bool Value::isArray() const {
	return type == Value::ARRAY_TYPE;
}

bool Value::isNumber() const {
	return type == Value::NUMBER_TYPE;
}

bool Value::isBoolean() const {
	return type == Value::BOOLEAN_TYPE;
}

bool Value::isNull() const {
	return type == Value::NULL_TYPE;
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
	case Value::NULL_TYPE:
		os << "null";
		break;
	case Value::OBJECT_TYPE:
		os << pt.getObject();
		break;
	case Value::STRING_TYPE:
		os << pt.getString();
		break;
	case Value::NUMBER_TYPE:
		os << pt.getNumber();
		break;
	case Value::ARRAY_TYPE:
		os << pt.getArray();
		break;
	case Value::BOOLEAN_TYPE:
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
	case Value::NULL_TYPE: 
		/* do nothing */; break;
	case Value::OBJECT_TYPE:
		object_ptr = new Object(pt.getObject()); break;
	case Value::STRING_TYPE:
		string_ptr = new String(pt.getString()); break;
	case Value::NUMBER_TYPE: 
		number_ptr = new Number(pt.getNumber()); break;
	case Value::ARRAY_TYPE: 
		array_ptr = new Array(pt.getArray()); break;
	case Value::BOOLEAN_TYPE: 
		boolean_ptr = new Boolean(pt.getBoolean()); break;
	default:
		assert("should not be here" == 0); 
	}

	return *this;
}

Value& Value::operator=(const String& pt) {
	if (string_ptr == &pt) return *this;
	
	this->~Value();

	type = Value::STRING_TYPE;
	string_ptr = new String(pt);

	return *this;
}

Value& Value::operator=(const Array& pt) {
	if (array_ptr == &pt) return *this;
	
	this->~Value();

	type = Value::ARRAY_TYPE;
	array_ptr = new Array(pt);

	return *this;
}

Value& Value::operator=(const Object& pt) {
	if (object_ptr == &pt) return *this;
	
	this->~Value();

	type = Value::OBJECT_TYPE;
	object_ptr = new Object(pt);

	return *this;
}

Value& Value::operator=(const Number& pt) {
	if (number_ptr == &pt) return *this;
	
	this->~Value();

	type = Value::NUMBER_TYPE;
	number_ptr = new Number(pt);

	return *this;
}

Value& Value::operator=(const Boolean& pt) {
	if (boolean_ptr == &pt) return *this;
	
	this->~Value();

	type = Value::BOOLEAN_TYPE;
	boolean_ptr = new Boolean(pt);

	return *this;
}

void toString(std::ostream& os, const Value& pt, 
		int indent, const std::string& indent_string) {
	switch (pt.getType()) {
	case Value::NULL_TYPE:
		os << "null";
		break;
	case Value::OBJECT_TYPE:
		toString(os, pt.getObject(), indent, indent_string);
		break;
	case Value::STRING_TYPE:
		toString(os, pt.getString());
		break;
	case Value::NUMBER_TYPE:
		toString(os, pt.getNumber());
		break;
	case Value::ARRAY_TYPE:
		toString(os, pt.getArray(), indent, indent_string);
		break;
	case Value::BOOLEAN_TYPE:
		toString(os, pt.getBoolean());
		break;
	default:
		assert("should not be here" == 0);
	}
	
}

} // namespace Json