#include <string>
#include <utility>
#include "jsonString.h"
#include "jsonValue.h"

namespace jsonat {
	
String::String() {}
String::String(const String& str) : std::string(str) {}
String::String(const Value& pt) {
	if (pt.getType() != Value::STRING) return;
	*this = pt.getString();
}
String::String(Value&& pt) {
	if (pt.getType() != Value::STRING) return;
	*this = std::move(*pt.string_ptr);
}

String& String::operator=(const Value& pt) {
	if (pt.getType() != Value::STRING || this == pt.string_ptr) return *this;
	return *this = pt.getString();
}

String& String::operator=(Value&& pt) {
	if (pt.getType() != Value::STRING || this == pt.string_ptr) return *this;
	return *this = std::move(*pt.string_ptr);
}



void String::addChar(char c) { this->operator+=(c); }

std::ostream& operator<<(std::ostream& os, const String& s) {
	return os << s.c_str();
}

void toString(std::ostream& os, const String& pt) {
	os << "\"" << pt << "\"";
}
	
} // namespace jsonat