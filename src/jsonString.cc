#include <string>
#include "jsonString.h"

namespace jsonat {
	
String::String() {}
String::String(const String& str) : std::string(str) {}
String::String(const char* str) : std::string(str) {}

void String::addChar(char c) { this->operator+=(c); }

std::ostream& operator<<(std::ostream& os, const String& s) {
	return os << "\"" << s.c_str() << "\"";
}
	
} // namespace jsonat