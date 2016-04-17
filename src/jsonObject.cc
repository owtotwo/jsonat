#include "jsonObject.h"
#include "jsonString.h"
#include "jsonValue.h"

#include <iostream>
#include <cassert>

namespace jsonat {

Object::Object() : Object::SuperClass() {}
Object::Object(const Object& obj) : Object::SuperClass(obj) {}

void Object::addPair(const String& key, const Value& value) {
	this->insert(Object::value_type(key, value));
}


std::ostream& operator<<(std::ostream& os, const Object& pt) {

	static int layer = 0;
	static const std::string indent_string = "    ";

	assert(layer >= 0);
	++layer;

	os << "{\n";
	if (pt.size() > 0) {
		auto it = pt.begin();
		for (int i = 0; i < layer; i++) os << indent_string;
		os << it->first << ": " << it->second;
		for (++it; it != pt.end(); ++it) {
			os << ", \n";
			for (int i = 0; i < layer; i++) os << indent_string;
			os << it->first << ": " << it->second;
		}
	}
	os << "\n";
	for (int i = 0; i < layer - 1; i++) os << indent_string;
	os << "}";

	--layer;
	return os;
}
	

	
} // namespace jsonat