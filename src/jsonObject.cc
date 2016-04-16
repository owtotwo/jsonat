#include "jsonObject.h"
#include "jsonString.h"
#include "jsonValue.h"

#include <iostream>

namespace jsonat {

Object::Object() : Object::SuperClass() {}
Object::Object(const Object& obj) : Object::SuperClass(obj) {}

void Object::addPair(const String& key, const Value& value) {
	this->insert(Object::value_type(key, value));
}


std::ostream& operator<<(std::ostream& os, const Object& pt) {
	os << "{";
	if (pt.size() > 0) {
		auto it = pt.begin();
		os << it->first << ": " << it->second;
		for (++it; it != pt.end(); ++it) {
			os << ", " << it->first << ": " << it->second;
		}
	}
	os << "}";
	return os;
}
	

	
} // namespace jsonat