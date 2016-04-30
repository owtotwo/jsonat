// Jsonat -- A Json Library in C++
// Copyright (c) 2016 sysu_AT
// All rights reserved.

#include "jsonObject.h"
#include "jsonString.h"
#include "jsonValue.h"

#include <ostream>
#include <utility> // for move()
#include <cassert>

namespace jsonat {

Object::Object() : Object::SuperClass() {}
// Object::Object(const Object& obj) : Object::SuperClass(obj) {}

Object::Object(const Value& pt) {
	if (pt.getType() != Value::OBJECT_TYPE) return;
	*this = pt.getObject();
}

Object::Object(Value&& pt) {
	if (pt.getType() != Value::OBJECT_TYPE) return;
	*this = std::move(*pt.object_ptr);
}


Object& Object::operator=(const Value& pt) {
	if (pt.getType() != Value::OBJECT_TYPE || this == pt.object_ptr) return *this;
	return *this = pt.getObject();
}

Object& Object::operator=(Value&& pt) {
	if (pt.getType() != Value::OBJECT_TYPE || this == pt.object_ptr) return *this;
	return *this = std::move(*pt.object_ptr);
}



void Object::addPair(const String& key, const Value& value) {
	this->insert(Object::value_type(key, value));
}


std::ostream& operator<<(std::ostream& os, const Object& pt) {

	os << "{";
	if (pt.size() > 0) {
		auto it = pt.begin();
		os << it->first << ":" << it->second;
		for (++it; it != pt.end(); ++it) {
			os << "," << it->first << ":" << it->second;
		}
	}
	os << "}";

	return os;
}
	
void toString(std::ostream& os, const Object& pt, 
		int indent = 0, const std::string& indent_string = "    ") {
		
	assert(indent >= 0);

	os << "{";
	if (pt.size() > 0) {
		os << "\n";
		auto it = pt.begin();
		for (int i = 0; i < indent; i++) os << indent_string;
		
		toString(os, it->first);
		os << ": ";
		toString(os, it->second, indent + 1, indent_string);
		
		for (++it; it != pt.end(); ++it) {
			os << ", \n";
			for (int i = 0; i < indent; i++) os << indent_string;
			toString(os, it->first);
			os << ": ";
			toString(os, it->second, indent + 1, indent_string);
		}
		os << "\n";
		for (int i = 0; i < indent - 1; i++) os << indent_string;
	}
	os << "}";	
}
	
} // namespace jsonat