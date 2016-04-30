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
	os << '\"';
	const char* p = s.c_str();
	for (int i = 0; p[i] != '\0'; i++) {
		switch (p[i]) {
		case '\"': os << '\\' << '\"'; break;
		case '\\': os << '\\' << '\\'; break;
		case '/': os << '\\' << '/'; break;
		case '\b': os << '\\' << 'b'; break;
		case '\f': os << '\\' << 'f'; break;
		case '\n': os << '\\' << 'n'; break;
		case '\r': os << '\\' << 'r'; break;
		case '\t': os << '\\' << 't'; break;
		default: os << p[i];
		}
	}
	return os << '\"';
}

void toString(std::ostream& os, const String& pt) {
	os << pt;
}
	
} // namespace jsonat