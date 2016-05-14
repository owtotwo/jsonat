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
#include <algorithm> // for all_of(), for_each()
#include <stdexcept>

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

Value::Value(const std::string& pt) : Value::Value(String(pt)) {}

Value::Value(bool x) : Value::Value(Boolean(x)) {}

#if 0
Value::Value(int pt) : Value::Value(Number(pt)) {}
Value::Value(unsigned int pt) : Value::Value(Number(pt)) {}
Value::Value(long long int pt) : Value::Value(Number(pt)) {}
Value::Value(long long unsigned int pt) : Value::Value(Number(pt)) {}
#endif

Value::Value(std::initializer_list<Value> il) {
	if (il.size() == 0) return; // set type = NULL_TYPE

	// type deduction
	// if Value is {String, Value} then create an Object, otherwise create an Array.
	auto is_kv_pair = [](const Value& x) -> bool {
		return (x.isArray() && (x.getArray().size() == 2) && x.getArray().front().isString());
	};
	
	if (std::all_of(il.begin(), il.end(), is_kv_pair)) { // create Object
		*this = Object(il);
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






Value::operator std::string() const {
	if (this->type != Value::STRING_TYPE) return std::string();
	return this->getString();
}

Value::operator double() const {
	if (this->type != Value::NUMBER_TYPE) return double();
	return this->getNumber();
}

Value::operator bool() const {
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

Value& Value::operator[](size_t pos) {
	if (type != Value::ARRAY_TYPE) throw std::domain_error("type should be value::ARRAY_TYPE");
	return (*array_ptr).at(pos);
}

Value& Value::operator[](const String& key) {
	if (type != Value::OBJECT_TYPE) throw std::domain_error("type should be value::OBJECT_TYPE");
	return (*object_ptr).at(key);
}

Value& Value::operator[](const char* key) {
	return this->operator[](String(key));
}

size_t Value::size() const {
	switch (type) {
	case Value::ARRAY_TYPE: return this->getArray().size();
	case Value::OBJECT_TYPE: return this->getObject().size();
	case Value::STRING_TYPE: return this->getString().size();
	default: throw std::domain_error("type matching error");
	}
}

bool Value::insert(const String& key, const Value& value) {
	if (type != Value::OBJECT_TYPE) return false;
	(*object_ptr).addPair(key, value);
	return true;
}

bool Value::push_back(const Value& pt) {
	if (type != Value::ARRAY_TYPE) return false;
	(*array_ptr).addValue(pt);
	return true;
}

bool Value::pop_back() {
	if (type != Value::ARRAY_TYPE || (*array_ptr).size() == 0) return false;
	(*array_ptr).pop_back();
	return true;
}

bool Value::insert(size_t pos, const Value& pt) {
	if (type != Value::ARRAY_TYPE || (*array_ptr).size() < pos) return false;
	(*array_ptr).insert((*array_ptr).begin() + pos, pt);
	return true;
}

bool Value::erase(const String& key) {
	if (type != Value::OBJECT_TYPE) return false;
	return (*object_ptr).erase(key);
}

bool Value::erase(size_t pos) {
	if (type != Value::ARRAY_TYPE || (*array_ptr).size() <= pos) return false;
	(*array_ptr).erase((*array_ptr).begin() + pos);
	return true;
}

size_t Value::push(const Value& pt) {
	this->push_back(pt);
	return this->size();
}

size_t Value::push(std::initializer_list<Value> il) {
	std::for_each(il.begin(), il.end(), [this](const Value& pt){ this->push_back(pt); });
	return this->size();
}

bool Value::pop() {
	return this->pop_back();
}

Value operator+(const Value& a, const Value& b) {
	if (a.getType() != b.getType()) throw std::domain_error("Two arguments should be the elements of same type");
	switch (a.getType()) {
	case Value::NUMBER_TYPE: return a.getNumber() + b.getNumber(); break;
	case Value::STRING_TYPE: return a.getString() + b.getString(); break;
	default: throw std::domain_error("type should be NUMBER_TYPE or STRING_TYPE");
	}
}

Value operator-(const Value& a, const Value& b) {
	if (a.getType() != Value::NUMBER_TYPE) 
		throw std::domain_error("type of left argument should be value::NUMBER_TYPE");
	if (b.getType() != Value::NUMBER_TYPE) 
		throw std::domain_error("type of right argument should be value::NUMBER_TYPE");
	return a.getNumber() - b.getNumber();
}

Value operator*(const Value& a, const Value& b) {
	if (a.getType() != Value::NUMBER_TYPE) 
		throw std::domain_error("type of left argument should be value::NUMBER_TYPE");
	if (b.getType() != Value::NUMBER_TYPE) 
		throw std::domain_error("type of right argument should be value::NUMBER_TYPE");
	return a.getNumber() * b.getNumber();
}

Value operator/(const Value& a, const Value& b) {
	if (a.getType() != Value::NUMBER_TYPE) 
		throw std::domain_error("type of left argument should be value::NUMBER_TYPE");
	if (b.getType() != Value::NUMBER_TYPE) 
		throw std::domain_error("type of right argument should be value::NUMBER_TYPE");
	return a.getNumber() / b.getNumber();
}


Value& Value::operator+=(const Value& pt) { return *this = *this + pt; }

Value& Value::operator-=(const Value& pt) { return *this = *this - pt; }

Value& Value::operator*=(const Value& pt) { return *this = *this * pt; }

Value& Value::operator/=(const Value& pt) { return *this = *this / pt; }


Value& Value::operator++() {
	if (this->type != Value::NUMBER_TYPE) {
		throw std::domain_error(
			"type of argument which calls increment operator should be value::NUMBER_TYPE"
		);
	}
	return *this += 1;
}

Value& Value::operator--() {
	if (this->type != Value::NUMBER_TYPE) {
		throw std::domain_error(
			"type of argument which calls decrement operator should be value::NUMBER_TYPE"
		);
	}
	return *this -= 1;
}
	

Value Value::operator++(int) {
	Value tmp = *this;
	return ++tmp; 
}

Value Value::operator--(int) {
	Value tmp = *this;
	return --tmp; 
}



// ------------------  friend functions ---------------------

Value operator+(const Value& pt, char c) { return std::string(pt) + c; }
Value operator+(char c, const Value& pt) { return c + std::string(pt); }
	
Value operator+(const Value& pt, const char* c) { return std::string(pt) + c; }
Value operator+(const char* c, const Value& pt) { return c + std::string(pt); }
	
Value operator+(const Value& pt, const std::string& s) { return std::string(pt) + s; }
Value operator+(const std::string& s, const Value& pt) { return s + std::string(pt); }
	

bool operator==(const Value& a, const Value& b) {
	
	if(a.getType() != b.getType()) return false;
	
	switch (a.getType()) {
	case Value::NULL_TYPE: return true;
	case Value::OBJECT_TYPE: return a.getObject() == b.getObject();
	case Value::STRING_TYPE: return a.getString() == b.getString();
	case Value::NUMBER_TYPE: return a.getNumber() == b.getNumber();
	case Value::ARRAY_TYPE: return a.getArray() == b.getArray();
	case Value::BOOLEAN_TYPE: return bool(a) == bool(b);
	default: assert("should not be here" == 0);
	}
	
	return false;
}

bool operator!=(const Value& a, const Value& b) { return !(a == b); }

bool operator<(const Value& a, const Value& b) {
	
	if(a.getType() != b.getType()) return false;
	
	switch (a.getType()) {
	case Value::NULL_TYPE: return false;
	case Value::OBJECT_TYPE: return a.getObject() < b.getObject();
	case Value::STRING_TYPE: return a.getString() < b.getString();
	case Value::NUMBER_TYPE: return a.getNumber() < b.getNumber();
	case Value::ARRAY_TYPE: return a.getArray() < b.getArray();
	case Value::BOOLEAN_TYPE: return bool(a) < bool(b);
	default: assert("should not be here" == 0);
	}
	
	return false; // should not reach here 
}

bool operator>(const Value& a, const Value& b) { return b < a; }
bool operator<=(const Value& a, const Value& b) { return !(a > b); }
bool operator>=(const Value& a, const Value& b) { return !(a < b); }

} // namespace Json