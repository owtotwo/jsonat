// String.h


#ifndef JSON_STRING_H
#define JSON_STRING_H

#include <string>
#include <iostream>

namespace jsonat {

class String : public std::string {
public:

	String();
	String(const String& str);
	String(const char* str);

	void addChar(char c);

	friend std::ostream& operator<<(std::ostream& os, const String& s);
};

} // namespace Json


#endif // JSON_STRING_H